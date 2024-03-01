#include "file.h"


// long long int current_timestamp() { // solely for test purposes!
//     struct timeval te; 
//     gettimeofday(&te, NULL); // get current time
//     //long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
//     return 1000000 * te.tv_sec + te.tv_usec;
// }






uint64_t file_sz(FILE* file){
	uint64_t curpos = ftell(file);
	fseek(file, 0, SEEK_END);
	uint64_t size = ftell(file);
	fseek(file, curpos, SEEK_SET);
	return size;
}




FILE* open_storage_file(char* path, char* flg){
	FILE* file = fopen(path, flg);
	if(file == NULL){
		printf("Wrong file name!\n");
		return file;
	}

	struct file_header* hdr;

	uint64_t size = file_sz(file);
	if(size < sizeof(struct file_header)){
		printf("File too small to be a valid storage file. Formatting.\n");
		goto format;
	}
	hdr = mem_map(NULL, sizeof(struct file_header), PROT_WRITE|PROT_READ, MAP_SHARED, fileno(file), 0);
	if(hdr->signature != 0xf228){
		mem_unmap(hdr, sizeof(struct file_header));
		printf("File signature wrong. Formatting.\n");
		goto format;
	}
	mem_unmap(hdr, sizeof(struct file_header));
	return file;

	format:
	ftrunc(fileno(file), sizeof(struct file_header));
	hdr = mem_map(NULL, sizeof(struct file_header), PROT_WRITE|PROT_READ, MAP_SHARED, fileno(file), 0);
	hdr->signature = 0xf228;
	hdr->first_hole = (struct holes_list_entry){sz: 0, hole_ptr: 0, prev_ptr: INV_F_PTR, next_ptr: INV_F_PTR};
	hdr->root_node_ptr = INV_F_PTR;
	hdr->node_id = 0;
	return file;
}

uint64_t write_to_hole(void* data, uint64_t size){
	uint64_t file_size = file_sz(storage_file);

	uint64_t iterhole_f_ptr = 2;
	uint64_t itersz = sizeof(struct file_header);
	void* iterpage = mem_map(NULL, itersz, PROT_WRITE|PROT_READ, MAP_SHARED, fileno(storage_file), 0);
	struct holes_list_entry* iterhole = iterpage + 2;

	// iterate through holes list 
	// if a hole is exactly the size of data and not SRH -> write data to the hole and turn its descriptor into a SRH
	// if a hole is exactly the size of data and is SRH -> reconnect the holes linked list, excluding the SRH in question from it -> write data to the hole
	// if a hole is bigger than the size of data and not SRH -> write data to the hole and update its descriptor according to its new size and shifted location
	// if a hole is bigger than the size of data and is SRH -> skip it
	do{
		if(iterhole->hole_ptr != INV_F_PTR){
			if(iterhole->sz == size){
				if(iterhole->hole_ptr != iterhole_f_ptr){ // check for SRH
					uint64_t realholefptr = iterhole->hole_ptr;
					if(iterhole_f_ptr == 2){ // first hole cannot be an SRH
						iterhole->sz = 0;
						iterhole->hole_ptr = INV_F_PTR;
					}else{ // not first hole -> create SRH
						iterhole->sz = sizeof(struct holes_list_entry);
						iterhole->hole_ptr = iterhole_f_ptr;
					}
					mem_unmap(iterpage, itersz);
					uint64_t realholepoffset = realholefptr%PAGE_SIZE;
					iterpage = mem_map(NULL, realholepoffset+size, PROT_WRITE|PROT_READ, MAP_SHARED, fileno(storage_file), realholefptr-realholepoffset);
					memcpy(iterpage+realholepoffset, data, size);
					mem_unmap(iterpage, realholepoffset+size);
					printf("Created SRH! data size: %ld holeptr: %ld\n", size, iterhole_f_ptr);
					return realholefptr;
					// not SRH -> close, create SRH
				}else{
					// close SRH
					uint64_t prev_ptr = iterhole->prev_ptr;
					uint64_t next_ptr = iterhole->next_ptr;
					memcpy(iterhole, data, size);
					mem_unmap(iterpage, itersz);
					if(prev_ptr != INV_F_PTR){
						itersz = prev_ptr%PAGE_SIZE + sizeof(struct holes_list_entry);
						iterpage = mem_map(NULL, itersz, PROT_WRITE|PROT_READ, MAP_SHARED, fileno(storage_file), prev_ptr - itersz + sizeof(struct holes_list_entry));
						iterhole = iterpage+itersz-sizeof(struct holes_list_entry);
						iterhole->next_ptr = next_ptr;
						mem_unmap(iterpage, itersz);
					}
					if(next_ptr != INV_F_PTR){
						itersz = next_ptr%PAGE_SIZE + sizeof(struct holes_list_entry);
						iterpage = mem_map(NULL, itersz, PROT_WRITE|PROT_READ, MAP_SHARED, fileno(storage_file), next_ptr - itersz + sizeof(struct holes_list_entry));
						iterhole = iterpage+itersz-sizeof(struct holes_list_entry);
						iterhole->prev_ptr = prev_ptr;
						mem_unmap(iterpage, itersz); 
					}
					printf("Closed SRH! data size: %ld\n", size);
					return iterhole_f_ptr;
				}
			}else if(iterhole->sz > size){
				if(iterhole->hole_ptr != iterhole_f_ptr){ // check SRH
					printf("Partially closed the hole! hole was: %ld, data size: %ld\n", iterhole->sz, size);
					iterhole->sz -= size;
					uint64_t realholefptr = iterhole->hole_ptr;
					iterhole->hole_ptr += size;

					mem_unmap(iterpage, itersz);
					uint64_t realholepoffset = realholefptr%PAGE_SIZE;
					iterpage = mem_map(NULL, realholepoffset+size, PROT_WRITE|PROT_READ, MAP_SHARED, fileno(storage_file), realholefptr-realholepoffset);
					memcpy(iterpage+realholepoffset, data, size);
					return realholefptr;
					// partially close the hole
				}
			}else if(iterhole->sz < size && size != sizeof(struct holes_list_entry)){
				mem_unmap(iterpage, itersz);
				break;
			}
		}
		iterhole_f_ptr = iterhole->next_ptr;
		mem_unmap(iterpage, itersz);
		if(iterhole_f_ptr != INV_F_PTR){
			itersz = iterhole_f_ptr%PAGE_SIZE + sizeof(struct holes_list_entry);
			iterpage = mem_map(NULL, itersz, PROT_WRITE|PROT_READ, MAP_SHARED, fileno(storage_file), iterhole_f_ptr - itersz + sizeof(struct holes_list_entry));
			iterhole = iterpage + itersz - sizeof(struct holes_list_entry);
		}else{
			break;
		}
	}while(iterhole_f_ptr < file_size);
	//printf("!\n");
	return INV_F_PTR;
}

void find_b_hole(){
	void* fpage = mem_map(NULL, sizeof(struct holes_list_entry)+2, PROT_WRITE|PROT_READ, MAP_SHARED, fileno(storage_file), 0);
	struct holes_list_entry* fhole = fpage+2;

	uint64_t next_ptr = fhole->next_ptr;
	uint64_t max_sz = fhole->sz;
	uint64_t max_ptr = INV_F_PTR;
	while(next_ptr != INV_F_PTR){
		uint64_t iteroffs = next_ptr%PAGE_SIZE;
		void* iterpage = mem_map(NULL, sizeof(struct holes_list_entry)+iteroffs, PROT_WRITE|PROT_READ, MAP_SHARED, fileno(storage_file), next_ptr - iteroffs);
		struct holes_list_entry* iterhole = iterpage + iteroffs;
		if(iterhole->sz > max_sz && iterhole->hole_ptr != next_ptr){
			max_sz = iterhole->sz;
			max_ptr = next_ptr;
		}
		next_ptr = iterhole->next_ptr;
		mem_unmap(iterpage, sizeof(struct holes_list_entry)+iteroffs);
	}

	if(max_ptr != INV_F_PTR){
		void* maxpage = mem_map(NULL, sizeof(struct holes_list_entry)+max_ptr%PAGE_SIZE, PROT_WRITE|PROT_READ, MAP_SHARED, fileno(storage_file), max_ptr-max_ptr%PAGE_SIZE);
		struct holes_list_entry* maxhole =maxpage+max_ptr%PAGE_SIZE;
		uint64_t tmp = fhole->hole_ptr;
		fhole->hole_ptr = maxhole->hole_ptr;
		maxhole->hole_ptr = tmp;
		tmp = fhole->sz;
		fhole->sz = maxhole->sz;
		maxhole->sz = tmp;
		mem_unmap(maxpage, sizeof(struct holes_list_entry)+max_ptr%PAGE_SIZE);
	}
	mem_unmap(fpage, sizeof(struct holes_list_entry)+2);
}

uint64_t write_to_file(void* data, uint64_t size, uint64_t flag){
	printf("|ENTER write_to_file()|\n");


	// check the holes list
	// if no fitting hole -> allocate enough space for the write
	uint64_t file_size = file_sz(storage_file);

	// if(!flag){
	// 	uint64_t ret = write_to_hole(data, size);
	// 	if(ret != INV_F_PTR){find_b_hole(); printf("|LEAVE write_to_file()|\n"); return ret;}
	// 	printf("Hole write failed\n");
	// }else{
	// 	printf("Skip hole write by flag\n");
	// }

	ftrunc(fileno(storage_file), file_size+size);

	uint64_t pageoffset = file_size % PAGE_SIZE;
	void* pagewrt = mem_map(NULL, pageoffset+size, PROT_WRITE|PROT_READ, MAP_SHARED, fileno(storage_file), file_size-pageoffset);
	memcpy(pagewrt+pageoffset, data, size);
	mem_unmap(pagewrt, pageoffset+size);
	printf("|LEAVE write_to_file(), %ld|\n", file_size);
	return file_size;
}


void delete_from_file(uint64_t d_ptr, uint64_t size){
	uint64_t file_size = file_sz(storage_file);
	if(d_ptr+size == file_size){
		ftrunc(fileno(storage_file), file_size-size);
		return;
	}
	// deleted data not on the end of file - create a hole
	// if data size < hole descriptor size -> allocate a hole descriptor
	// if data size = hole descriptor size -> create a SRH
	// if data size > hole descriptor size -> fill part of data with a hole descriptor, that is referencing the rest of data

	// first check if the first hole is empty, since it cannot be a SRH
	void* fpage = mem_map(NULL, sizeof(struct holes_list_entry)+2, PROT_WRITE|PROT_READ, MAP_SHARED, fileno(storage_file), 0);
	//printf("%ld\n", fpage);
	struct holes_list_entry* fhole = fpage+2;
	if(fhole->sz == 0){
		printf("__FILLED FIRST HOLE\n");
		fhole->hole_ptr = d_ptr;
		fhole->sz = size;
		mem_unmap(fpage, sizeof(struct holes_list_entry)+2);
		return;
	}
	mem_unmap(fpage, sizeof(struct holes_list_entry)+2);


	if(size < sizeof(struct holes_list_entry)){
		printf("__HOLE SMALL\n");
		// allocate new hole descriptor
		// find the last record in the holes list
		// connect newly allocated hole descriptor to the list of holes
		struct holes_list_entry hole = (struct holes_list_entry){sz: size, hole_ptr: d_ptr, prev_ptr: 0, next_ptr: INV_F_PTR};
		uint64_t new_hole_ptr = write_to_file(&hole, sizeof(struct holes_list_entry), 1);

		uint64_t iterhole_f_ptr = 2;
		uint64_t itersz = sizeof(struct holes_list_entry)+2;
		void* iterpage = mem_map(NULL, sizeof(struct holes_list_entry)+2, PROT_WRITE|PROT_READ, MAP_SHARED, fileno(storage_file), 0);
		struct holes_list_entry* iterhole = iterpage+2;
		while(iterhole->next_ptr != INV_F_PTR){
			iterhole_f_ptr = iterhole->next_ptr;
			mem_unmap(iterpage, itersz);
			itersz = sizeof(struct holes_list_entry) + iterhole_f_ptr%PAGE_SIZE;
			iterpage = mem_map(NULL, itersz, PROT_WRITE|PROT_READ, MAP_SHARED, fileno(storage_file), iterhole_f_ptr - itersz + sizeof(struct holes_list_entry));
			iterhole = iterpage + itersz - sizeof(struct holes_list_entry);
		}
		iterhole->next_ptr = new_hole_ptr;

		mem_unmap(iterpage, itersz);

		itersz = new_hole_ptr%PAGE_SIZE + sizeof(struct holes_list_entry);
		iterpage = mem_map(NULL, itersz, PROT_WRITE|PROT_READ, MAP_SHARED, fileno(storage_file), new_hole_ptr-itersz+sizeof(struct holes_list_entry));
		iterhole = iterpage+itersz-sizeof(struct holes_list_entry);
		iterhole->prev_ptr = iterhole_f_ptr;
		mem_unmap(iterpage, itersz);

	}else if(size == sizeof(struct holes_list_entry)){
		printf("__PUT SRH INTO HOLE\n");
		struct holes_list_entry hole = (struct holes_list_entry){sz: size, hole_ptr: d_ptr, prev_ptr: 0, next_ptr: INV_F_PTR};

		uint64_t newsrh_sz = d_ptr % PAGE_SIZE + sizeof(struct holes_list_entry);
		void* newsrh_page = mem_map(NULL, newsrh_sz, PROT_WRITE|PROT_READ, MAP_SHARED, fileno(storage_file), d_ptr - newsrh_sz + sizeof(struct holes_list_entry));
		struct holes_list_entry* newsrh_ptr = newsrh_page+newsrh_sz-sizeof(struct holes_list_entry);
		memcpy(newsrh_ptr, &hole, sizeof(struct holes_list_entry));

		uint64_t iterhole_f_ptr = 2;
		uint64_t itersz = sizeof(struct holes_list_entry)+2;
		void* iterpage = mem_map(NULL, sizeof(struct holes_list_entry)+2, PROT_WRITE|PROT_READ, MAP_SHARED, fileno(storage_file), 0);
		struct holes_list_entry* iterhole = iterpage+2;

		while(iterhole->next_ptr != INV_F_PTR){
			iterhole_f_ptr = iterhole->next_ptr;
			mem_unmap(iterpage, itersz);
			itersz = sizeof(struct holes_list_entry) + iterhole_f_ptr%PAGE_SIZE;
			iterpage = mem_map(NULL, itersz, PROT_WRITE|PROT_READ, MAP_SHARED, fileno(storage_file), iterhole_f_ptr - itersz + sizeof(struct holes_list_entry));
			iterhole = iterpage + itersz - sizeof(struct holes_list_entry);
		}

		iterhole->next_ptr = d_ptr;
		newsrh_ptr->prev_ptr = iterhole_f_ptr;

		mem_unmap(newsrh_page, newsrh_sz);
		mem_unmap(iterpage, itersz);

	}else{
		printf("__PUT DESCRIPTOR IN BEGINNING\n");
		struct holes_list_entry hole = (struct holes_list_entry){sz: size - sizeof(struct holes_list_entry), hole_ptr: d_ptr+sizeof(struct holes_list_entry), prev_ptr: 0, next_ptr:INV_F_PTR};

		uint64_t newhole_sz = d_ptr % PAGE_SIZE + sizeof(struct holes_list_entry);
		void* newhole_page = mem_map(NULL, newhole_sz, PROT_WRITE|PROT_READ, MAP_SHARED, fileno(storage_file), d_ptr - newhole_sz + sizeof(struct holes_list_entry));
		struct holes_list_entry* newhole_ptr = newhole_page + newhole_sz - sizeof(struct holes_list_entry);
		memcpy(newhole_ptr, &hole, sizeof(struct holes_list_entry));

		uint64_t iterhole_f_ptr = 2;
		uint64_t itersz = sizeof(struct holes_list_entry)+2;
		void* iterpage = mem_map(NULL, sizeof(struct holes_list_entry)+2, PROT_WRITE|PROT_READ, MAP_SHARED, fileno(storage_file), 0);
		struct holes_list_entry* iterhole = iterpage+2;

		while(iterhole->next_ptr != INV_F_PTR){
			iterhole_f_ptr = iterhole->next_ptr;
			mem_unmap(iterpage, itersz);
			itersz = sizeof(struct holes_list_entry) + iterhole_f_ptr%PAGE_SIZE;
			iterpage = mem_map(NULL, itersz, PROT_WRITE|PROT_READ, MAP_SHARED, fileno(storage_file), iterhole_f_ptr - itersz + sizeof(struct holes_list_entry));
			iterhole = iterpage + itersz - sizeof(struct holes_list_entry);
		}

		iterhole->next_ptr = d_ptr;
		newhole_ptr->prev_ptr = iterhole_f_ptr;

		mem_unmap(newhole_page, newhole_sz);
		mem_unmap(iterpage, itersz);
	}
	find_b_hole();

}


void* extract_data(uint64_t d_ptr, uint64_t size){
	void* buf = malloc(size);

	uint64_t dataoffset = d_ptr%PAGE_SIZE;
	void* page = mem_map(NULL, dataoffset+size, PROT_WRITE|PROT_READ, MAP_SHARED, fileno(storage_file), d_ptr-dataoffset);
	memcpy(buf, page+dataoffset, size);
	mem_unmap(page, dataoffset+size);

	return buf;
}

struct map* map_in_file(uint64_t d_ptr, uint64_t size){
	uint64_t d_offs = d_ptr % PAGE_SIZE;
	struct map* map = malloc(sizeof(struct map));
	//printf("MMAP params: len: %ld, offs: %ld\n", size+d_offs, d_ptr-d_offs);
	map->page = mem_map(NULL, size+d_offs, PROT_WRITE|PROT_READ, MAP_SHARED, fileno(storage_file), d_ptr-d_offs);
	map->data = map->page+d_offs;
	map->size = d_offs+size;
}

void unmap_in_file(struct map* map){
	mem_unmap(map->page, map->size);
	free(map);
}

