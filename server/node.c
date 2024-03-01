#include "node.h"

#define mapto_node(map) ((struct node*)(map->data))
#define mapto_u64p(map) ((uint64_t*)(map->data))
#define mapto_strd(map) ((struct str_desc*)(map->data))
#define mapto_fhdr(map) ((struct file_header*)(map->data))

//uint64_t __oper = 0;

char* read_var_string(){
	char* inp = NULL;
	char tmp[128];
	uint64_t inplen = 0;
	uint64_t tmplen = 0;

	do{
		fgets(tmp, 128, stdin);
		tmp[strcspn(tmp, "\n")] = 0;
		tmplen = strlen(tmp);
		inp = realloc(inp, inplen+tmplen+1);
		//tmp[tmplen-1] = '\0';
		strcpy(inp+inplen, tmp);
		inplen += tmplen;
	}while(tmplen == 128-1 && tmp[126] != '\n');
	//inp[inplen] = '\n';
	return inp;
}


uint64_t find_node_by_id(uint64_t id){ // returns node's address in the file. if doesnt exist -> INV_F_PTR
	struct file_header* hdr = mem_map(NULL, sizeof(struct file_header), PROT_WRITE|PROT_READ, MAP_SHARED, fileno(storage_file), 0);
	if(hdr->root_node_ptr == INV_F_PTR){mem_unmap(hdr, sizeof(struct file_header)); return INV_F_PTR;}
	
	uint64_t iternodeptr = hdr->root_node_ptr;
	uint64_t iternodeoffs = hdr->root_node_ptr%PAGE_SIZE;
	void* iterpage = mem_map(NULL, iternodeoffs+sizeof(struct node), PROT_WRITE|PROT_READ, MAP_SHARED, fileno(storage_file), iternodeptr-iternodeoffs);
	struct node* iternode = iterpage+iternodeoffs;
	do{
		//printf("%ld\n", iternode->node_id);
		if(iternode->node_id == id){
			mem_unmap(iterpage, sizeof(struct node)+iternodeoffs);
			mem_unmap(hdr, sizeof(struct file_header));
			return iternodeptr;
		}
		if(iternode->next_ptr != INV_F_PTR){
			iternodeptr = iternode->next_ptr;
			mem_unmap(iterpage, sizeof(struct node)+iternodeoffs);
			iternodeoffs = iternodeptr%PAGE_SIZE;
			iterpage = mem_map(NULL, iternodeoffs+sizeof(struct node), PROT_WRITE|PROT_READ, MAP_SHARED, fileno(storage_file), iternodeptr-iternodeoffs);
			iternode = iterpage + iternodeoffs;
		}
	}while(1);
	mem_unmap(iterpage, sizeof(struct node)+iternodeoffs);
	mem_unmap(hdr, sizeof(struct file_header));
	return INV_F_PTR;
}

uint64_t find_id_by_node(uint64_t addr){
	struct map* nodemap = map_in_file(addr, sizeof(struct node));
	uint64_t id = mapto_node(nodemap)->node_id;
	unmap_in_file(nodemap);
	return id;
}


void create_new_node(uint64_t flag){ // if 1 -> root node, nothing to connect to it
	//uint64_t __time = current_timestamp();
	//uint64_t __time_2;

	struct node node;

	struct file_header* page = mem_map(NULL, sizeof(struct file_header), PROT_WRITE|PROT_READ, MAP_SHARED, fileno(storage_file), 0);

	printf("file node id %ld\n", page->node_id);
	node.node_id = page->node_id++;
	printf("node node id %ld\n", node.node_id);
	printf("file node id %ld\n", page->node_id);
	//mem_unmap(page, sizeof(struct file_header));


	uint64_t answ;
	printf("How many nodes do you want to connect this node to?: ");
	scanf("%ld", &answ);
	printf("\n");
	uint64_t* node_ptrs = (uint64_t*)malloc(answ*8);
	node.n = answ;

	for(uint64_t i = 0; i < answ; i++){
		retry:
		printf("Enter %ld node's id: ", i);
		scanf("%ld", &(node_ptrs[i]));
		printf("\n");
		// check the existence of user's node id
		if(node.node_id == node_ptrs[i]){goto retry;}
		uint64_t found_addr = find_node_by_id(node_ptrs[i]);
		if(found_addr == INV_F_PTR){
			printf("Node by this id does not exist! type the id again!\n");
			goto retry;
		}else{
			node_ptrs[i] = found_addr;
		}
	}

	printf("How many integer attributes do you wish this node to have?: ");
	scanf("%ld", &answ);
	printf("\n");
	uint32_t* int_data = (uint32_t*)malloc(answ*4);
	node.n_int = answ;

	for(uint64_t i = 0; i < answ; i++){
		printf("Enter %ld integer argument: ", i);
		scanf("%d", &(int_data[i]));
		printf("\n");
	}

	printf("How many float attributes do you wish this node to have?: ");
	scanf("%ld", &answ);
	printf("\n");
	float* float_data = (float*)malloc(answ*4);
	node.n_float = answ;

	for(uint64_t i = 0; i < answ; i++){
		printf("Enter %ld float argument: ", i);
		scanf("%f", &(float_data[i]));
		printf("\n");
	}

	printf("How many string attributes do you wish this node to have?: ");
	scanf("%ld", &answ);
	printf("\n");
	struct str_desc* str_data = (struct str_desc*)malloc(answ*sizeof(struct str_desc));
	node.n_str = answ;

	free(read_var_string());

	for(uint64_t i = 0; i < answ; i++){
		printf("Enter %ld string argument: ", i);
		//fflush(stdin);
		str_data[i].str_ptr = (uint64_t)read_var_string();
		str_data[i].length = strlen((char*)str_data[i].str_ptr);
		printf("%s\n", (char*)str_data[i].str_ptr);
	}

	if(node.n_int){node.int_ptr =  write_to_file(int_data, node.n_int*4, 0);}else{node.int_ptr = INV_F_PTR;}
	if(node.n_float){node.float_ptr = write_to_file(float_data, node.n_float*4, 0);}else{node.float_ptr = INV_F_PTR;}
	for(uint64_t i = 0; i < node.n_str; i++){
		char* res = (char*)write_to_file((char*)str_data[i].str_ptr, str_data[i].length+1, 0);
		free((char*)str_data[i].str_ptr);
		str_data[i].str_ptr = (uint64_t)res;
	}
	if(node.n_str){node.str_ptr = write_to_file(str_data, node.n_str*sizeof(struct str_desc), 0);}else{node.str_ptr = INV_F_PTR;}
	if(node.n){node.node_ptr = write_to_file(node_ptrs, node.n*8, 0);}else{node.node_ptr = INV_F_PTR;}

	// find the last node list entry
	node.next_ptr = INV_F_PTR;

	uint64_t node_addr;//= write_to_file(&node, sizeof(struct node), 0);

	if(page->root_node_ptr != INV_F_PTR){
		printf("Root node adr in hdr %ld\n", page->root_node_ptr);
		struct map* fnode = map_in_file(page->root_node_ptr, sizeof(struct node));
		node.next_ptr = page->root_node_ptr;
		node.prev_ptr = INV_F_PTR;
		//printf("??? %ld\n",  mapto_node(fnode)->prev_ptr);
		printf("fnode map: struct adr: %ld, page adr: %ld, data adr: %ld, size: %ld", fnode, fnode->page, fnode->data, fnode->size);
		//uint64_t wrt_adr = write_to_file(&node, sizeof(struct node), 0);
		printf("!!! !!! !!! !!!\n");
		mapto_node(fnode)->prev_ptr = write_to_file(&node, sizeof(struct node), 0);
		node_addr = mapto_node(fnode)->prev_ptr;
		page->root_node_ptr = mapto_node(fnode)->prev_ptr;
		unmap_in_file(fnode);
	}else{
		node.prev_ptr = INV_F_PTR;
		node_addr = write_to_file(&node, sizeof(struct node), 0);
	}


	if(page->root_node_ptr == INV_F_PTR){page->root_node_ptr=node_addr;}

	for(uint64_t i = 0; i < node.n; i++){
		uint64_t iternodeoffset = node_ptrs[i]%PAGE_SIZE;
		void* iternodepage = mem_map(NULL, sizeof(struct node)+iternodeoffset, PROT_WRITE|PROT_READ, MAP_SHARED, fileno(storage_file), node_ptrs[i]-iternodeoffset);
		struct node* iternode = iternodepage+iternodeoffset;
		iternode->n++;
		
		if(iternode->node_ptr != INV_F_PTR){
			uint64_t* iternode_nodes = extract_data(iternode->node_ptr, (iternode->n-1)*8);
			delete_from_file(iternode->node_ptr, (iternode->n-1)*8);
			iternode_nodes = realloc(iternode_nodes, (iternode->n)*8);
			iternode_nodes[iternode->n-1] = node_addr;
			iternode->node_ptr = write_to_file(iternode_nodes, (iternode->n)*8, 0);
			free(iternode_nodes);
			mem_unmap(iternodepage, sizeof(struct node)+iternodeoffset);
		}else{
			iternode->node_ptr = write_to_file(&node_addr, 8, 0);
		}
	}

	mem_unmap(page, sizeof(struct file_header));

	free(float_data);
	free(int_data);
	free(str_data);




	//struct file_header* __hdr = mem_map(NULL, sizeof(struct file_header), PROT_WRITE|PROT_READ, MAP_SHARED, fileno(storage_file), 0);

	//__time_2 = current_timestamp();
	// uint64_t __n_nodes = 0;
	// uint64_t __node_ptr = __hdr->root_node_ptr;
	// while(__node_ptr != INV_F_PTR){
	// 	__n_nodes++;
	// 	struct map* __node = map_in_file(__node_ptr, sizeof(struct node));
	// 	__node_ptr = mapto_node(__node)->next_ptr;
	// 	unmap_in_file(__node);
	// }
	//fprintf(__testfile, "%ld, %ld\n", __time_2-__time, __oper);
	//mem_unmap(__hdr, sizeof(struct file_header));
	//__oper++;
}

uint64_t delete_node(uint64_t id){ // if no such node-> return 1
	//uint64_t __time = current_timestamp();
	//uint64_t __time_2;




	printf("--------------------------DELETE NODE %ld------------------------\n", id);


	uint64_t node_addr = find_node_by_id(id);
	if(node_addr == INV_F_PTR){return 1;}


	struct map* nodemap = map_in_file(node_addr, sizeof(struct node));

	printf("-----------Fix header\n");
	struct file_header* hdr= mem_map(NULL, sizeof(struct file_header), PROT_WRITE|PROT_READ, MAP_SHARED, fileno(storage_file), 0);
	if(hdr->root_node_ptr == node_addr){hdr->root_node_ptr = mapto_node(nodemap)->next_ptr; mem_unmap(hdr, sizeof(struct file_header));}else{mem_unmap(hdr, sizeof(struct file_header));}

	printf("-----------Bind list\n");
	if(mapto_node(nodemap)->next_ptr != INV_F_PTR){struct map* nextnodemap = map_in_file(mapto_node(nodemap)->next_ptr, sizeof(struct node)); mapto_node(nextnodemap)->prev_ptr = mapto_node(nodemap)->prev_ptr; unmap_in_file(nextnodemap);}
	if(mapto_node(nodemap)->prev_ptr != INV_F_PTR){struct map* prevnodemap = map_in_file(mapto_node(nodemap)->prev_ptr, sizeof(struct node)); mapto_node(prevnodemap)->next_ptr = mapto_node(nodemap)->next_ptr; unmap_in_file(prevnodemap);}

	printf("-----------Fix neighbours\n");
	if(mapto_node(nodemap)->node_ptr != INV_F_PTR){
		//struct map* node_ptrs_map = map_in_file(mapto_node(nodemap)->node_ptr, mapto_node(nodemap)->n*8);

		uint64_t* node_ptrs = extract_data(mapto_node(nodemap)->node_ptr, mapto_node(nodemap)->n*8);

		for(uint64_t* i = node_ptrs; i < node_ptrs+mapto_node(nodemap)->n; i++){printf("%ld\n", *i);}

		//extract_data()

		for(uint64_t i = 0; i < mapto_node(nodemap)->n; i++){
			//struct map* iternodemap = map_in_file(mapto_u64p(node_ptrs_map)[i], sizeof(struct node));
			struct map* iternodemap = map_in_file(node_ptrs[i], sizeof(struct node));
			//printf("%ld\n", node_ptrs_map->data+8*i);
			//printf("!!!!\n");
			if(mapto_node(iternodemap)->n == 1){
				//printf("!!!?\n");
				delete_from_file(mapto_node(iternodemap)->node_ptr, 8);
				mapto_node(iternodemap)->node_ptr = INV_F_PTR;
				mapto_node(iternodemap)->n = 0;
			}else{
				//printf("!!?!\n");
				mapto_node(iternodemap)->n--;
				uint64_t* iternode_node_ptrs = extract_data(mapto_node(iternodemap)->node_ptr, 8*(mapto_node(iternodemap)->n+1));
				uint64_t* iternode_new_node_ptrs = (uint64_t*)malloc(mapto_node(iternodemap)->n-1);
				uint64_t* iteriternode_new_node_ptrs = iternode_new_node_ptrs;
				for(uint64_t i = 0; i < mapto_node(iternodemap)->n+1; i++){
					if(iternode_node_ptrs[i] != node_addr){
						*iteriternode_new_node_ptrs = iternode_node_ptrs[i];
					}
				}
				free(iternode_node_ptrs);
				delete_from_file(mapto_node(iternodemap)->node_ptr, (mapto_node(iternodemap)->n+1)*8);
				mapto_node(iternodemap)->node_ptr = write_to_file(iternode_new_node_ptrs, mapto_node(iternodemap)->n*8, 0);
				free(iternode_new_node_ptrs);
			}
			unmap_in_file(iternodemap);
		}
		//unmap_in_file(node_ptrs_map);
		free(node_ptrs);
	}
	printf("-----------Delete node array\n");
	if(mapto_node(nodemap)->node_ptr != INV_F_PTR){delete_from_file(mapto_node(nodemap)->node_ptr, mapto_node(nodemap)->n*8); printf("DELETED node ptrs\n");}
	printf("-----------Delete int array\n");
	if(mapto_node(nodemap)->int_ptr != INV_F_PTR){delete_from_file(mapto_node(nodemap)->int_ptr, mapto_node(nodemap)->n_int*4);printf("DELETED int array %ld\n", mapto_node(nodemap)->n_int*4);}
	printf("-----------Delete float array\n");
	if(mapto_node(nodemap)->float_ptr != INV_F_PTR){delete_from_file(mapto_node(nodemap)->float_ptr, mapto_node(nodemap)->n_float*4);printf("DELETED float array\n");}
	printf("-----------Delete strings\n");
	if(mapto_node(nodemap)->str_ptr != INV_F_PTR){
		struct map* node_str_dsc_map = map_in_file(mapto_node(nodemap)->str_ptr, mapto_node(nodemap)->n_str*sizeof(struct str_desc));
		for(uint64_t i = 0; i < mapto_node(nodemap)->n_str; i++){
			printf("-----------Deleting string %ld, len %ld\n", i, mapto_strd(node_str_dsc_map)[i].length);
			delete_from_file(mapto_strd(node_str_dsc_map)[i].str_ptr, mapto_strd(node_str_dsc_map)[i].length+1); printf("DELETED string %ld\n", i);
		}
		unmap_in_file(node_str_dsc_map);
		printf("-----------Delete strings array\n");
		delete_from_file(mapto_node(nodemap)->str_ptr, (mapto_node(nodemap)->n_str)*sizeof(struct str_desc)); printf("DELETED str desc array\n");
	}
	unmap_in_file(nodemap);
	printf("-----------Delete node itself\n");
	delete_from_file(node_addr, sizeof(struct node)); 


	//struct file_header* __hdr = mem_map(NULL, sizeof(struct file_header), PROT_WRITE|PROT_READ, MAP_SHARED, fileno(storage_file), 0);

	//__time_2 = current_timestamp();
	// uint64_t __n_nodes = 0;
	// uint64_t __node_ptr = __hdr->root_node_ptr;
	// while(__node_ptr != INV_F_PTR){
	// 	__n_nodes++;
	// 	struct map* __node = map_in_file(__node_ptr, sizeof(struct node));
	// 	__node_ptr = mapto_node(__node)->next_ptr;
	// 	unmap_in_file(__node);
	// }
	//fprintf(__testfile, "%ld, %ld\n", __time_2-__time, __oper);
	//__oper++;
	//mem_unmap(__hdr, sizeof(struct file_header));

	return 0;
}

uint64_t connect_nodes(uint64_t id1, uint64_t id2){ // returns 1 if bad id, 2 if already connected, 0 if success
	if(id1 == id2){return 1;}
	uint64_t adr1 = find_node_by_id(id1);
	uint64_t adr2 = find_node_by_id(id2);

	if(adr1 == INV_F_PTR || adr2 == INV_F_PTR){return 1;}

	struct map* nodemap1 = map_in_file(adr1, sizeof(struct node));
	struct map* nodemap2 = map_in_file(adr2, sizeof(struct node));

	if(mapto_node(nodemap1)->n == 0){
		mapto_node(nodemap1)->node_ptr = write_to_file(&adr2, 8, 0);
		mapto_node(nodemap1)->n = 1;
	}else{
		uint64_t* node_ptrs1 = extract_data(mapto_node(nodemap1)->node_ptr, mapto_node(nodemap1)->n*8);
		for(uint64_t i = 0; i < mapto_node(nodemap1)->n; i++){
			if(node_ptrs1[i] == adr2){
				free(node_ptrs1);
				unmap_in_file(nodemap1);
				unmap_in_file(nodemap2);
				return 2;
			}
		}
		mapto_node(nodemap1)->n++;
		node_ptrs1 = realloc(node_ptrs1, mapto_node(nodemap1)->n*8);
		node_ptrs1[mapto_node(nodemap1)->n-1] = adr2;
		delete_from_file(mapto_node(nodemap1)->node_ptr, (mapto_node(nodemap1)->n-1)*8);
		mapto_node(nodemap1)->node_ptr = write_to_file(node_ptrs1, mapto_node(nodemap1)->n*8, 0);
		free(node_ptrs1);
	}

	if(mapto_node(nodemap2)->n == 0){
		mapto_node(nodemap2)->node_ptr = write_to_file(&adr1, 8, 0);
		mapto_node(nodemap2)->n = 1;
	}else{
		uint64_t* node_ptrs2 = extract_data(mapto_node(nodemap2)->node_ptr, mapto_node(nodemap2)->n*8);
		mapto_node(nodemap2)->n++;
		node_ptrs2 = realloc(node_ptrs2, mapto_node(nodemap2)->n*8);
		node_ptrs2[mapto_node(nodemap2)->n-1] = adr1;
		delete_from_file(mapto_node(nodemap2)->node_ptr, (mapto_node(nodemap2)->n-1)*8);
		mapto_node(nodemap2)->node_ptr = write_to_file(node_ptrs2, mapto_node(nodemap2)->n*8, 0);
		free(node_ptrs2);
	}

	unmap_in_file(nodemap1);
	unmap_in_file(nodemap2);
	return 0;
}

void list_nodes(){
	struct map* hdr = map_in_file(0, sizeof(struct file_header));

	if(mapto_fhdr(hdr)->root_node_ptr == INV_F_PTR){printf("No nodes found\n"); unmap_in_file(hdr); return;}

	printf("Found nodes by ids: ");

	struct map* iternodemap = map_in_file(mapto_fhdr(hdr)->root_node_ptr, sizeof(struct node));
	do{
		printf("%ld ", mapto_node(iternodemap)->node_id);
		if(mapto_node(iternodemap)->next_ptr != INV_F_PTR){
			uint64_t next_ptr = mapto_node(iternodemap)->next_ptr;
			unmap_in_file(iternodemap);
			iternodemap = map_in_file(next_ptr, sizeof(struct node));
		}else{
			break;
		}

	}while(iternodemap != NULL);
	printf("\n");
	unmap_in_file(iternodemap);
	unmap_in_file(hdr);
}

void edit_int_attr(uint64_t id, uint64_t pos){
	uint64_t adr = find_node_by_id(id);

	if(adr == INV_F_PTR){return;}

	struct map* nodemap = map_in_file(adr, sizeof(struct node));
	if(mapto_node(nodemap)->n_int-1 >= pos){
		struct map* intmap = map_in_file(mapto_node(nodemap)->int_ptr+pos*4, 4);
		printf("Enter new int value of int attribute №%ld of node №%ld: ", pos, id);
		scanf("%d", (uint32_t*)(intmap->data));
		printf("\n");
		unmap_in_file(intmap);
	}else{printf("Wrong pos!\n");}
	unmap_in_file(nodemap);
}

void edit_float_attr(uint64_t id, uint64_t pos){
	uint64_t adr = find_node_by_id(id);

	if(adr == INV_F_PTR){return;}

	struct map* nodemap = map_in_file(adr, sizeof(struct node));
	if(mapto_node(nodemap)->n_float-1 >= pos){
		struct map* flmap = map_in_file(mapto_node(nodemap)->float_ptr+pos*4, 4);
		printf("Enter new float value of int attribute №%ld of node №%ld: ", pos, id);
		scanf("%f", (float*)(flmap->data));
		printf("\n");
		unmap_in_file(flmap);
	}else{printf("Wrong pos!\n");}
	unmap_in_file(nodemap);	
}

void edit_str_attr(uint64_t id, uint64_t pos){
	uint64_t adr = find_node_by_id(id);	

	if(adr == INV_F_PTR){return;}

	struct map* nodemap = map_in_file(adr, sizeof(struct node));
	if(mapto_node(nodemap)->n_str-1 >= pos){
		struct map* descmap = map_in_file(mapto_node(nodemap)->str_ptr+pos*sizeof(struct str_desc), sizeof(struct str_desc));
		struct str_desc* dsc = descmap->data;
		free(read_var_string());
		char* newstr = read_var_string();
		delete_from_file(dsc->str_ptr, dsc->length+1);
		dsc->length = strlen(newstr);
		dsc->str_ptr = write_to_file(newstr, dsc->length+1, 0);
		unmap_in_file(descmap);
		free(newstr);
	}else{printf("Wrong pos!\n");}
	unmap_in_file(nodemap);
}

void print_node_info(uint64_t id){
	uint64_t adr = find_node_by_id(id); if(adr == INV_F_PTR){printf("Wrog id!\n");return;}

	struct map* nodemap = map_in_file(adr, sizeof(struct node));

	printf("_________________________________________________\n");
	printf("Node id: %ld\n", mapto_node(nodemap)->node_id);
	printf("Connected to %ld nodes\n", mapto_node(nodemap)->n);
	printf("Has %ld integer attributes\n", mapto_node(nodemap)->n_int);
	printf("Has %ld float attributes\n", mapto_node(nodemap)->n_float);
	printf("Has %ld string attributes\n", mapto_node(nodemap)->n_str);
	printf("_________________________________________________\n");

	unmap_in_file(nodemap);
}

void print_connected_nodes(uint64_t id){
	uint64_t adr = find_node_by_id(id); if(adr == INV_F_PTR){printf("Wrog id!\n");return;}

	struct map* nodemap = map_in_file(adr, sizeof(struct node));
	uint64_t* node_ptrs = extract_data(mapto_node(nodemap)->node_ptr, mapto_node(nodemap)->n*8);

	printf("Node %ld is connected to nodes: ", id);
	for(uint64_t i = 0; i < mapto_node(nodemap)->n; i++){
		struct map* iternodemap = map_in_file(node_ptrs[i], sizeof(struct node));
		printf("%ld ", mapto_node(iternodemap)->node_id);
		unmap_in_file(iternodemap);
	}
	free(node_ptrs);
	printf("\n");
	unmap_in_file(nodemap);
}

void print_int_attr(uint64_t id){
	uint64_t adr = find_node_by_id(id); if(adr == INV_F_PTR){printf("Wrog id!\n");return;}

	struct map* nodemap = map_in_file(adr, sizeof(struct node));

	uint32_t* ints = extract_data(mapto_node(nodemap)->int_ptr, mapto_node(nodemap)->n_int*4);

	printf("Integer attributes of node %ld: ", id);
	for(uint64_t i = 0; i < mapto_node(nodemap)->n_int; i++){
		printf("%d ", ints[i]);		
	}
	printf("\n");

	free(ints);
	unmap_in_file(nodemap);
}

void print_float_attr(uint64_t id){
	uint64_t adr = find_node_by_id(id); if(adr == INV_F_PTR){printf("Wrog id!\n");return;}

	struct map* nodemap = map_in_file(adr, sizeof(struct node));

	float* floats = extract_data(mapto_node(nodemap)->float_ptr, mapto_node(nodemap)->n_float*4);

	printf("Float attributes of node %ld: ", id);
	for(uint64_t i = 0; i < mapto_node(nodemap)->n_int; i++){
		printf("%f ", floats[i]);		
	}
	printf("\n");

	free(floats);
	unmap_in_file(nodemap);
}

void print_str_attr(uint64_t id){
	uint64_t adr = find_node_by_id(id); if(adr == INV_F_PTR){printf("Wrog id!\n");return;}

	struct map* nodemap = map_in_file(adr, sizeof(struct node));	

	struct str_desc* strdscs = extract_data(mapto_node(nodemap)->str_ptr, mapto_node(nodemap)->n_str*sizeof(struct str_desc));

	printf("String attributes of node %ld:\n", id);
	for(uint64_t i = 0; i < mapto_node(nodemap)->n_str; i++){
		char* string = extract_data(strdscs[i].str_ptr, strdscs[i].length+1);
		printf("%s\n", string);
		free(string);
	}
	free(strdscs);
	unmap_in_file(nodemap);
}

void print_help(){
	printf("9999 - exit, 1 - new node, 2 - connect nodes, 3 - delete node, 4 - list nodes, 5 - help, 6 - print node-specific{0 - general info, 1 - int attributes, 2 - float attributes, 3 - str attributes, 4 - connected nodes}, 7 - edit node data{0 - int, 1 - float, 2 - str}.\n");
}

void user(){ // a user function. Will be smth like this: get command(single char), call corresponding function
	int inp = 228;
	uint64_t id1;
	uint64_t id2;
	uint64_t id;
	uint64_t pos;
	while(inp != 9999){
		printf("Enter a command: ");
		//inp = getc(stdin);
		scanf("%d", &inp);
		printf("\n");
		switch(inp){
		case 1:
			create_new_node(1);
			break;
		case 2:
			printf("Enter first id: ");
			scanf("%ld", &id1);
			printf("\n");
			printf("Enter second id: ");
			printf("\n");
			scanf("%ld", &id2);
			connect_nodes(id1, id2);
			break;
		case 3:
			printf("Enter node id: ");
			scanf("%ld", &id);
			printf("\n");
			delete_node(id);
			break;
		case 4:
			list_nodes();
			break;
		case 5:
			print_help();
			break;
		case 6:
			printf("What do you want to print?: ");
			//inp = getc(stdin);
			scanf("%d", &inp);
			switch(inp){
			case 0:
				printf("\n");				
				printf("Enter node id: ");
				scanf("%ld", &id);
				printf("\n");
				print_node_info(id);
				break;
			case 1:
				printf("\n");				
				printf("Enter node id: ");
				scanf("%ld", &id);
				printf("\n");
				print_int_attr(id);
				break;
			case 2:
				printf("\n");				
				printf("Enter node id: ");
				scanf("%ld", &id);
				printf("\n");
				print_float_attr(id);
				break;
			case 3:
				printf("\n");				
				printf("Enter node id: ");
				scanf("%ld", &id);
				printf("\n");
				print_str_attr(id);
				break;
			case 4:
				printf("\n");				
				printf("Enter node id: ");
				scanf("%ld", &id);
				printf("\n");
				print_connected_nodes(id);
				break;
			}
			break;
		case 7:
			printf("What do you want to edit?: ");
			//inp = getc(stdin);
			scanf("%d", &inp);
			switch(inp){
			case 0:
				printf("\n");				
				printf("Enter node id: ");
				scanf("%ld", &id);
				printf("\n");
				printf("Enter item pos: ");
				scanf("%ld", &pos);
				printf("\n");				
				edit_int_attr(id, pos);
				break;
			case 1:
				printf("\n");				
				printf("Enter node id: ");
				scanf("%ld", &id);
				printf("\n");
				printf("Enter item pos: ");
				scanf("%ld", &pos);
				printf("\n");				
				edit_float_attr(id, pos);
				break;
			case 2:
				printf("\n");				
				printf("Enter node id: ");
				scanf("%ld", &id);
				printf("\n");
				printf("Enter item pos: ");
				scanf("%ld", &pos);
				printf("\n");								
				edit_str_attr(id, pos);
				break;
			}
			break;			
		}
	//fflush(stdin);
	//inp = getc(stdin);
	}
	exit(0);
}

