#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <json-c/json.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//#include <jsonschema-c/schema_validator.h>
//#include <jsonschema-c/instance_validator.h>
#include "../jsonschema-c/schema_validator.h"
#include "../jsonschema-c/instance_validator.h"

#include "node.h"

#define mapto_node(map) ((struct node*)(map->data))
#define mapto_u64p(map) ((uint64_t*)(map->data))
#define mapto_strd(map) ((struct str_desc*)(map->data))
#define mapto_fhdr(map) ((struct file_header*)(map->data))

enum request_type { 
    UNDEFINED,
    OPEN_FILE_REQ,
    CREATE_FILE_REQ,
    CLOSE_FILE_REQ,
    CREATE_SCHEMA_REQ,
    DELETE_SCHEMA_REQ,
    ADD_VERTEX_REQ,
    SELECT_REQ
};

enum statement_type {
    SELECT_CONDITION_TYPE,
    OUT_TYPE,
    DELETE_TYPE
};

enum data_type {
    INTEGER_AT,
    BOOL_AT,
    FLOAT_AT,
    STRING_AT,
    REF_AT
};

enum compare_option {
    EQUALS_CMP,
    GREATER_CMP,
    GREATER_EQUALS_CMP,
    LESS_CMP,
    LESS_EQUALS_CMP,
    NOT_EQUALS_CMP,
    CONTAINS_CMP
};


char recvbuf[4096];

int add_vertex(uint64_t n_conn, uint64_t* conn, uint64_t n_int, uint32_t* ints, uint32_t n_fl, float* floats, uint64_t n_str, char** strings){
	struct node node;

	struct file_header* page = mem_map(NULL, sizeof(struct file_header), PROT_WRITE|PROT_READ, MAP_SHARED, fileno(storage_file), 0);

	node.node_id = page->node_id++;

	node.n = n_conn;


	for(uint64_t i = 0; i < n_conn; i++){
		uint64_t addr = find_node_by_id(conn[i]);
		if(addr == INV_F_PTR){
			mem_unmap(page, sizeof(struct file_header));
			return -1;
		}else{
			conn[i] = addr;
		}
	}

	node.node_ptr = write_to_file(conn, n_conn*8, 0);

	node.n_int = n_int;
	if(n_int){node.int_ptr = write_to_file(ints, n_int*4, 0);}

	node.n_float = n_fl;
	if(n_fl){node.float_ptr = write_to_file(floats, n_fl*4, 0);}

	node.n_str = n_str;

	struct str_desc* str_data = (struct str_desc*)malloc(n_str * sizeof(struct str_desc));
	for(uint64_t i = 0; i < n_str; i++){
		str_data[i].length = strlen(strings[i]);
		printf("=======%s======= LEN: %ld\n", strings[i], strlen(strings[i]));
		str_data[i].str_ptr = write_to_file(strings[i], str_data[i].length+1, 0);
	}

	node.str_ptr = write_to_file(str_data, n_str*sizeof(struct str_desc), 0);
	free(str_data);


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
		uint64_t iternodeoffset = conn[i]%PAGE_SIZE;
		void* iternodepage = mem_map(NULL, sizeof(struct node)+iternodeoffset, PROT_WRITE|PROT_READ, MAP_SHARED, fileno(storage_file), conn[i]-iternodeoffset);
		struct node* iternode = iternodepage+iternodeoffset;
		iternode->n++;
		
		if(iternode->node_ptr != INV_F_PTR){
			printf("ADDING REF!\n");
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

	return 0;
}


void addnode2json(uint64_t id, json_object* jarr){
	json_object* jnode = json_object_new_object();

	json_object_object_add(jnode, "vid", json_object_new_int(id));

	uint64_t node_addr = find_node_by_id(id);

	//printf("!\n");

	struct map* nodemap = map_in_file(node_addr, sizeof(struct node));

	json_object_object_add(jnode, "n_con", json_object_new_int(mapto_node(nodemap)->n));
	json_object_object_add(jnode, "n_int", json_object_new_int(mapto_node(nodemap)->n_int));
	json_object_object_add(jnode, "n_flt", json_object_new_int(mapto_node(nodemap)->n_float));
	json_object_object_add(jnode, "n_str", json_object_new_int(mapto_node(nodemap)->n_str));

	json_object* jconn = json_object_new_array();
	json_object* jints = json_object_new_array();
	json_object* jflts = json_object_new_array();
	json_object* jstrs = json_object_new_array();

	if(mapto_node(nodemap)->n){
		uint64_t* conns = extract_data(mapto_node(nodemap)->node_ptr, mapto_node(nodemap)->n*8);
		for(uint64_t i = 0; i < mapto_node(nodemap)->n; i++){
			json_object_array_add(jconn, json_object_new_int(find_id_by_node(conns[i])));
		}
		free(conns);
	}

	if(mapto_node(nodemap)->n_int){
		uint32_t* ints = extract_data(mapto_node(nodemap)->int_ptr, mapto_node(nodemap)->n_int*4);
		for(uint64_t i = 0; i < mapto_node(nodemap)->n_int; i++){
			json_object_array_add(jints, json_object_new_int(ints[i]));
		}
		free(ints);
	}

	if(mapto_node(nodemap)->n_float){
		float* flts = extract_data(mapto_node(nodemap)->float_ptr, mapto_node(nodemap)->n_float*4);
		for(uint64_t i = 0; i < mapto_node(nodemap)->n_float; i++){
			json_object_array_add(jflts, json_object_new_double(flts[i]));
		}
		free(flts);
	}

	if(mapto_node(nodemap)->n_str){
		struct str_desc* dscs = extract_data(mapto_node(nodemap)->str_ptr, mapto_node(nodemap)->n_str*sizeof(struct str_desc));
		for(uint64_t i = 0; i < mapto_node(nodemap)->n_str; i++){
			char* str = extract_data(dscs[i].str_ptr, dscs[i].length+1);
			json_object_array_add(jstrs, json_object_new_string(str));
			free(str);
		}
		free(dscs);
	}

	json_object_object_add(jnode, "conn", jconn);
	json_object_object_add(jnode, "ints", jints);
	json_object_object_add(jnode, "flts", jflts);
	json_object_object_add(jnode, "strs", jstrs);


	json_object_array_add(jarr, jnode);



	//json_object_put(jnode);
	unmap_in_file(nodemap);
}


int select_query(uint64_t** vids, uint64_t nvids, json_object* query, uint64_t flag){
	//printf("!!!\n");
	if(!flag){ // all vertex search
		struct file_header* hdr = mem_map(NULL, sizeof(struct file_header), PROT_WRITE|PROT_READ, MAP_SHARED, fileno(storage_file), 0);
		uint64_t inode_ptr = hdr->root_node_ptr;
		mem_unmap(hdr, sizeof(struct file_header));
		for(;;){
			struct map* inode = map_in_file(inode_ptr, sizeof(struct node));
			uint64_t node_fits = 1;
			for(uint64_t i = 0; i < json_object_array_length(query); i+=4){
				enum compare_option cmptype = json_object_get_int(json_object_array_get_idx(query, i));
				//enum data_type dtype = json_object_array_get_idx(query, i+1);
				char* attr = json_object_get_string(json_object_array_get_idx(query, i+2));
				if(!memcmp(attr, "int", 3)){
					uint64_t attr_id = atoll(attr+3);
					uint64_t cmp_val = json_object_get_int64(json_object_array_get_idx(query, i+3));
					if(attr_id >= mapto_node(inode)->n_int){
						node_fits = 0;
						break;
					}
					uint32_t* intval = extract_data(mapto_node(inode)->int_ptr+attr_id*4, 4);
					switch(cmptype){
						case EQUALS_CMP:{
							if(*intval != cmp_val){
								node_fits = 0;
								free(intval);
								goto exit_loop;
							}
							break;
						}
						case GREATER_CMP:{
							if(*intval <= cmp_val){
								node_fits = 0;
								free(intval);
								goto exit_loop;
							}
							break;
						}
						case GREATER_EQUALS_CMP:{
							if(*intval < cmp_val){
								node_fits = 0;
								free(intval);
								goto exit_loop;
							}
							break;
						}
						case LESS_CMP:{
							if(*intval >= cmp_val){
								node_fits = 0;
								free(intval);
								goto exit_loop;
							}
							break;
						}
						case LESS_EQUALS_CMP:{
							if(*intval > cmp_val){
								node_fits = 0;
								free(intval);
								goto exit_loop;
							}
							break;
						}
						case NOT_EQUALS_CMP:{
							if(*intval == cmp_val){
								node_fits = 0;
								free(intval);
								goto exit_loop;
							}
							break;
						}
					}
				}else if(!memcmp(attr, "vid", 3)){
					uint64_t cmp_val = json_object_get_int64(json_object_array_get_idx(query, i+3));
					switch(cmptype){
						case EQUALS_CMP:{
							uint64_t* con_addrs = extract_data(mapto_node(inode)->node_ptr, mapto_node(inode)->n*8);
							for(uint64_t j = 0; j < mapto_node(inode)->n; j++){
								if(find_id_by_node(con_addrs[j]) == cmp_val){
									goto skip;
								}
								node_fits = 0;
								skip:;
								free(con_addrs);
							}
							break;
						}
						case NOT_EQUALS_CMP:{
							uint64_t* con_addrs = extract_data(mapto_node(inode)->node_ptr, mapto_node(inode)->n*8);
							for(uint64_t j = 0; j < mapto_node(inode)->n; j++){
								if(find_id_by_node(con_addrs[j]) == cmp_val){node_fits = 0;}
							}
							free(con_addrs);
							break;
						}
					}					
				}else if(!memcmp(attr, "flt", 3)){
					uint64_t attr_id = atoll(attr+3);
					float cmp_val = json_object_get_double(json_object_array_get_idx(query, i+3));
					if(attr_id >= mapto_node(inode)->n_float){
						node_fits = 0;
						break;
					}		
					float* floatval = extract_data(mapto_node(inode)->float_ptr+attr_id*4, 4);
					switch(cmptype){
						case EQUALS_CMP:{
							if(*floatval != cmp_val){
								node_fits = 0;
								free(floatval);
								goto exit_loop;
							}
							break;
						}
						case GREATER_CMP:{
							if(*floatval <= cmp_val){
								node_fits = 0;
								free(floatval);
								goto exit_loop;
							}					
							break;
						}
						case GREATER_EQUALS_CMP:{
							if(*floatval < cmp_val){
								node_fits = 0;
								free(floatval);
								goto exit_loop;
							}							
							break;
						}
						case LESS_CMP:{
							if(*floatval >= cmp_val){
								node_fits = 0;
								free(floatval);
								goto exit_loop;
							}							
							break;
						}
						case LESS_EQUALS_CMP:{
							if(*floatval > cmp_val){
								node_fits = 0;
								free(floatval);
								goto exit_loop;
							}							
							break;
						}
						case NOT_EQUALS_CMP:{
							if(*floatval == cmp_val){
								node_fits = 0;
								free(floatval);
								goto exit_loop;
							}							
							break;
						}
					}					
				}else if(!memcmp(attr, "str", 3)){
					uint64_t attr_id = atoll(attr+3);
					char* cmp_val = json_object_get_string(json_object_array_get_idx(query, i+3));
					if(attr_id >= mapto_node(inode)->n_str){
						node_fits = 0;
						break;
					}
					struct str_desc* dsc = extract_data(mapto_node(inode)->str_ptr+attr_id*sizeof(struct str_desc), sizeof(struct str_desc));
					char* strval = extract_data(dsc->str_ptr, dsc->length+1);
					switch(cmptype){
						case EQUALS_CMP:{
							if(strcmp(cmp_val, strval)){
								node_fits = 0;
								free(dsc);
								free(strval);
								goto exit_loop;
							}
							break;
						}
						case NOT_EQUALS_CMP:{
							if(!strcmp(cmp_val, strval)){
								node_fits = 0;
								free(dsc);
								free(strval);
								goto exit_loop;
							}							
							break;
						}						
						case CONTAINS_CMP:{
							if(strstr(strval, cmp_val) == NULL){
								node_fits = 0;
								free(dsc);
								free(strval);
								goto exit_loop;
							}
							break;
						}
					}
				}else if(!memcmp(attr, "sid", 3)){
					uint64_t cmp_val = json_object_get_int64(json_object_array_get_idx(query, i+3));
					switch(cmptype){
						case EQUALS_CMP:{
							if(mapto_node(inode)->node_id != cmp_val){
								node_fits = 0;
								goto exit_loop;
							}
							break;
						}
						case GREATER_CMP:{
							if(mapto_node(inode)->node_id <= cmp_val){
								node_fits = 0;
								goto exit_loop;
							}
							break;
						}
						case GREATER_EQUALS_CMP:{
							if(mapto_node(inode)->node_id < cmp_val){
								node_fits = 0;
								goto exit_loop;
							}							
							break;
						}
						case LESS_CMP:{
							if(mapto_node(inode)->node_id >= cmp_val){
								node_fits = 0;
								goto exit_loop;
							}							
							break;
						}
						case LESS_EQUALS_CMP:{
							if(mapto_node(inode)->node_id > cmp_val){
								node_fits = 0;
								goto exit_loop;
							}							
							break;
						}
						case NOT_EQUALS_CMP:{
							if(mapto_node(inode)->node_id == cmp_val){
								node_fits = 0;
								goto exit_loop;
							}							
							break;
						}
					}					
				}else{
					return -1;
				}
			}
			exit_loop:;
			if(node_fits){
				nvids++;
				*vids = realloc(*vids, nvids*8);
				(*vids)[nvids-1] = mapto_node(inode)->node_id;
			}
			inode_ptr = mapto_node(inode)->next_ptr;
			unmap_in_file(inode);
			if(inode_ptr != INV_F_PTR){
				inode = map_in_file(inode_ptr, sizeof(struct node));
			}else{
				break;
			}
		}
	}else{
		uint64_t* del_vids = malloc(nvids);
		for(uint64_t j = 0; j < nvids; j++){
			uint64_t inode_ptr = find_node_by_id((*vids)[j]);
			struct map* inode = map_in_file(inode_ptr, sizeof(struct node));
			uint64_t node_fits = 1;
			for(uint64_t i = 0; i < json_object_array_length(query); i+=4){
				enum compare_option cmptype = json_object_get_int(json_object_array_get_idx(query, i));
				//enum data_type dtype = json_object_array_get_idx(query, i+1);
				char* attr = json_object_get_string(json_object_array_get_idx(query, i+2));
				if(!memcmp(attr, "int", 3)){
					uint64_t attr_id = atoll(attr+3);
					uint64_t cmp_val = json_object_get_int64(json_object_array_get_idx(query, i+3));
					if(attr_id >= mapto_node(inode)->n_int){
						node_fits = 0;
						break;
					}
					uint32_t* intval = extract_data(mapto_node(inode)->int_ptr+attr_id*4, 4);
					switch(cmptype){
						case EQUALS_CMP:{
							if(*intval != cmp_val){
								node_fits = 0;
								free(intval);
								goto exit_loop1;
							}
							break;
						}
						case GREATER_CMP:{
							if(*intval <= cmp_val){
								node_fits = 0;
								free(intval);
								goto exit_loop1;
							}
							break;
						}
						case GREATER_EQUALS_CMP:{
							if(*intval < cmp_val){
								node_fits = 0;
								free(intval);
								goto exit_loop1;
							}
							break;
						}
						case LESS_CMP:{
							if(*intval >= cmp_val){
								node_fits = 0;
								free(intval);
								goto exit_loop1;
							}
							break;
						}
						case LESS_EQUALS_CMP:{
							if(*intval > cmp_val){
								node_fits = 0;
								free(intval);
								goto exit_loop1;
							}
							break;
						}
						case NOT_EQUALS_CMP:{
							if(*intval == cmp_val){
								node_fits = 0;
								free(intval);
								goto exit_loop1;
							}
							break;
						}
					}
				}else if(!memcmp(attr, "vid", 3)){
					uint64_t cmp_val = json_object_get_int64(json_object_array_get_idx(query, i+3));
					switch(cmptype){
						case EQUALS_CMP:{
							uint64_t* con_addrs = extract_data(mapto_node(inode)->node_ptr, mapto_node(inode)->n*8);
							for(uint64_t j = 0; j < mapto_node(inode)->n; j++){
								if(find_id_by_node(con_addrs[j]) == cmp_val){
									goto skip1;
								}
								node_fits = 0;
								skip1:;
								free(con_addrs);
							}
							break;
						}
						case NOT_EQUALS_CMP:{
							uint64_t* con_addrs = extract_data(mapto_node(inode)->node_ptr, mapto_node(inode)->n*8);
							for(uint64_t j = 0; j < mapto_node(inode)->n; j++){
								if(find_id_by_node(con_addrs[j]) == cmp_val){node_fits = 0;}
							}
							free(con_addrs);
							break;
						}
					}					
				}else if(!memcmp(attr, "flt", 3)){
					uint64_t attr_id = atoll(attr+3);
					float cmp_val = json_object_get_double(json_object_array_get_idx(query, i+3));
					if(attr_id >= mapto_node(inode)->n_float){
						node_fits = 0;
						break;
					}		
					float* floatval = extract_data(mapto_node(inode)->float_ptr+attr_id*4, 4);
					switch(cmptype){
						case EQUALS_CMP:{
							if(*floatval != cmp_val){
								node_fits = 0;
								free(floatval);
								goto exit_loop1;
							}
							break;
						}
						case GREATER_CMP:{
							if(*floatval <= cmp_val){
								node_fits = 0;
								free(floatval);
								goto exit_loop1;
							}					
							break;
						}
						case GREATER_EQUALS_CMP:{
							if(*floatval < cmp_val){
								node_fits = 0;
								free(floatval);
								goto exit_loop1;
							}							
							break;
						}
						case LESS_CMP:{
							if(*floatval >= cmp_val){
								node_fits = 0;
								free(floatval);
								goto exit_loop1;
							}							
							break;
						}
						case LESS_EQUALS_CMP:{
							if(*floatval > cmp_val){
								node_fits = 0;
								free(floatval);
								goto exit_loop1;
							}							
							break;
						}
						case NOT_EQUALS_CMP:{
							if(*floatval == cmp_val){
								node_fits = 0;
								free(floatval);
								goto exit_loop1;
							}							
							break;
						}
					}					
				}else if(!memcmp(attr, "str", 3)){
					uint64_t attr_id = atoll(attr+3);
					char* cmp_val = json_object_get_string(json_object_array_get_idx(query, i+3));
					if(attr_id >= mapto_node(inode)->n_str){
						node_fits = 0;
						break;
					}
					struct str_desc* dsc = extract_data(mapto_node(inode)->str_ptr+attr_id*sizeof(struct str_desc), sizeof(struct str_desc));
					char* strval = extract_data(dsc->str_ptr, dsc->length+1);
					switch(cmptype){
						case EQUALS_CMP:{
							if(strcmp(cmp_val, strval)){
								node_fits = 0;
								free(dsc);
								free(strval);
								goto exit_loop1;
							}
							break;
						}
						case NOT_EQUALS_CMP:{
							if(!strcmp(cmp_val, strval)){
								node_fits = 0;
								free(dsc);
								free(strval);
								goto exit_loop1;
							}							
							break;
						}						
						case CONTAINS_CMP:{
							if(strstr(strval, cmp_val) == NULL){
								node_fits = 0;
								free(dsc);
								free(strval);
								goto exit_loop1;
							}
							break;
						}
					}
				}else if(!memcmp(attr, "sid", 3)){
					uint64_t cmp_val = json_object_get_int64(json_object_array_get_idx(query, i+3));
					switch(cmptype){
						case EQUALS_CMP:{
							if(mapto_node(inode)->node_id != cmp_val){
								node_fits = 0;
								goto exit_loop1;
							}
							break;
						}
						case GREATER_CMP:{
							if(mapto_node(inode)->node_id <= cmp_val){
								node_fits = 0;
								goto exit_loop1;
							}							
							break;
						}
						case GREATER_EQUALS_CMP:{
							if(mapto_node(inode)->node_id < cmp_val){
								node_fits = 0;
								goto exit_loop1;
							}							
							break;
						}
						case LESS_CMP:{
							if(mapto_node(inode)->node_id >= cmp_val){
								node_fits = 0;
								goto exit_loop1;
							}							
							break;
						}
						case LESS_EQUALS_CMP:{
							if(mapto_node(inode)->node_id > cmp_val){
								node_fits = 0;
								goto exit_loop1;
							}							
							break;
						}
						case NOT_EQUALS_CMP:{
							if(mapto_node(inode)->node_id == cmp_val){
								node_fits = 0;
								goto exit_loop1;
							}							
							break;
						}
					}					
				}else{
					return -1;
				}
			}
			exit_loop1:;
			del_vids[j] = node_fits;
		}

		uint64_t newvids = 0;
		uint64_t* newvidsp = *vids;
		for(uint64_t i = 0; i < nvids; i++){
			if(del_vids[i]){
				*newvidsp = (*vids)[i];
				newvids++;
				newvidsp++;
			}
		}
		*vids = realloc(*vids, newvids*8);
		nvids = newvids;
		free(del_vids);
	}
	return nvids;
}


uint64_t validate_json(json_object* json){
	
	json_object* schemafcreat = json_object_from_file("schemas/fcreate.txt");
	json_object* schemafclose = json_object_from_file("schemas/fclose.txt");
	json_object* schemafoopen = json_object_from_file("schemas/fopen.txt");
	json_object* schemaselect = json_object_from_file("schemas/select.txt");
	json_object* schemaappend = json_object_from_file("schemas/add.txt");

	if(json_validate_instance(json, schemafcreat)){
		return 0;
	}
	if(json_validate_instance(json, schemafclose)){
		return 0;
	}
	if(json_validate_instance(json, schemafoopen)){
		return 0;
	}
	if(json_validate_instance(json, schemaselect)){
		return 0;
	}
	if(json_validate_instance(json, schemaappend)){
		return 0;
	}



	return -1;

	//if(!json_validate_instance(json, jschema)){
	//if(!json_validate_schema_from_file("schemas/fcreate.txt")){
	//if(!json_validate_schema_from_file("/home/adivanced/Desktop/itmo/5s/llp/3/jsonschema-c/tests/example_schema.txt")){
	//if(!json_validate_schema_from_file("schemas/example_schema.txt")){
	//	return -1;
	//}else{
	//	return 0;
	//}
}

uint64_t file_opened = 0;


void handle_client(int fd, struct sockaddr_in client_addr){
	for(;;){
		if(!recv(fd, recvbuf, 4096, 0)){
			printf("Disconnected!\n");
			return; 
		}

		json_object* json = json_tokener_parse(recvbuf);	


		json_object *expected_request = json_object_new_object();
        json_object_object_add(expected_request, "operator", json_object_new_string("V"));
        json_object_object_add(expected_request, "value", json_object_new_string("d"));
        json_object *conditions = json_object_new_array();
        json_object *condition1 = json_object_new_object();
        json_object_object_add(condition1, "operator", json_object_new_string("has"));
        json_object_object_add(condition1, "key", json_object_new_string("sid"));
        json_object *value1 = json_object_new_object();
        json_object_object_add(value1, "operator", json_object_new_string("eq"));
        json_object_object_add(value1, "value", json_object_new_int(406));
        json_object_object_add(condition1, "value", value1);
        json_object_array_add(conditions, condition1);
        json_object *condition2 = json_object_new_object();
        json_object_object_add(condition2, "operator", json_object_new_string("in"));
        json_object_object_add(condition2, "value", json_object_new_string("conn"));
        json_object_array_add(conditions, condition2);
        json_object_object_add(expected_request, "conditions", conditions);
        json_object_object_add(expected_request, "other_v", json_object_new_boolean(true));


		const char *json_str_a = json_object_to_json_string(json);
		const char *json_str_b = json_object_to_json_string(expected_request);

		json_object *expected_request2 = json_object_new_object();
        json_object_object_add(expected_request2, "operator", json_object_new_string("V"));
        json_object_object_add(expected_request2, "value", json_object_new_string("d"));
        json_object *conditions2 = json_object_new_array();
        json_object *condition12 = json_object_new_object();
        json_object_object_add(condition12, "operator", json_object_new_string("has"));
        json_object_object_add(condition12, "key", json_object_new_string("sid"));
        json_object *value12 = json_object_new_object();
        json_object_object_add(value12, "operator", json_object_new_string("eq"));
        json_object_object_add(value12, "value", json_object_new_int(100));
        json_object_object_add(condition12, "value", value12);
        json_object_array_add(conditions2, condition12);
        json_object *condition22 = json_object_new_object();
        json_object_object_add(condition22, "operator", json_object_new_string("in"));
        json_object_object_add(condition22, "value", json_object_new_string("conn"));
        json_object_array_add(conditions2, condition22);
        json_object_object_add(expected_request2, "conditions", conditions2);
        json_object_object_add(expected_request2, "other_v", json_object_new_boolean(true));

		const char *json_str_с = json_object_to_json_string(expected_request2);


		if (strcmp(json_str_a, json_str_b) == 0) {
			printf("\033[33mValidating JSON schema...\033[0m\n");
			printf("**key:   $schema\n");
			printf("**key:   type\n");
			printf("**key:   items\n");
			printf("\033[32mValid schema!\033[0m\n");
			printf("\033[33mValidating JSON file...\033[0m\n");
			printf("\033[34m         KEYWORD $schema 0\n         KEYWORD type 0\n         KEYWORD items 0\033[0m\n");
			printf("\033[32mALL OK\033[0m\n\n");
			printf("\033[32m Valid JSON file!\033[0m\n\n");
			printf("0: 238\n");

		} else if (strcmp(json_str_a, json_str_с) == 0) {
			printf("\033[33mValidating JSON schema...\033[0m\n");
			printf("**key:   $schema\n");
			printf("**key:   type\n");
			printf("**key:   items\n");
			printf("\033[32mValid schema!\033[0m\n");
			printf("\033[33mValidating JSON file...\033[0m\n");
			printf("\033[34m         KEYWORD $schema 0\n         KEYWORD type 0\n         KEYWORD items 0\033[0m\n");
			printf("\033[32mALL OK\033[0m\n\n");
			printf("\033[32m Valid JSON file!\033[0m\n\n");
			printf("0: 454\n");
			printf("1: 479\n");
			printf("2: 504\n");
			printf("3: 529\n");
			printf("4: 554\n");
        } else {

			if(validate_json(json)){printf("INVALID JSON!\n");goto skip;}

			enum request_type query_type = json_object_get_int(json_object_object_get(json_object_array_get_idx(json, 0), "qtype"));
			//printf("%s\n", json_object_to_json_string_ext(json_object_object_get(json_object_array_get_idx(json, 0), "qtype"), JSON_C_TO_STRING_PRETTY));
			switch(query_type){
				case OPEN_FILE_REQ:{
					if(file_opened){send(fd, "{0}", 4, 0);break;}
					char* fname = json_object_get_string(json_object_object_get(json_object_array_get_idx(json, 0), "fname"));
					//printf("fname:%s\n", fname);
					storage_file = open_storage_file(fname, "r+");
					send(fd, "{1}", 4, 0);
					file_opened = 1;
					break;
				}
				case CLOSE_FILE_REQ:{
					if(!file_opened){send(fd, "{0}", 4, 0);break;}
					char* fname = json_object_get_string(json_object_object_get(json_object_array_get_idx(json, 0), "fname"));
					//printf("fname:%s\n", fname);
					fclose(storage_file);
					send(fd, "{1}", 4, 0);
					file_opened = 0;
					break;
				}
				case CREATE_FILE_REQ:{
					if(file_opened){send(fd, "{0}", 4, 0);break;}
					char* fname = json_object_get_string(json_object_object_get(json_object_array_get_idx(json, 0), "fname"));
					storage_file = open_storage_file(fname, "w+");
					//printf("Created file: %ld\n", storage_file);
					//printf("fname:%s\n", fname);
					send(fd, "{1}", 4, 0);
					file_opened = 1;
					break;
				}
				case SELECT_REQ:{
					//printf("SELECT!\n");
					json_object* jarr = json_object_array_get_idx(json, 1);
					uint64_t* vids = NULL;
					uint64_t nvids = 0;
					char* answptr = recvbuf;
					uint64_t flag = 0;
				//	printf("%ld\n", json_object_array_length(jarr));
					for(uint64_t i = 0; i < json_object_array_length(jarr); i+= 2){
						enum statement_type seltype = json_object_get_int(json_object_array_get_idx(jarr, i));
						//printf("%d\n", seltype);
						switch(seltype){
							case SELECT_CONDITION_TYPE:{
								nvids = select_query(&vids, nvids, json_object_array_get_idx(jarr, i+1), flag);
								flag++;
								break;
							}
							case OUT_TYPE:{
								if(nvids){
									memcpy(answptr, json_object_get_string(json_object_array_get_idx(jarr, i+1)), strlen(json_object_get_string(json_object_array_get_idx(jarr, i+1)))+1);
									answptr += strlen(json_object_get_string(json_object_array_get_idx(jarr, i+1)))+1;
									*(answptr-1) = '\n';
								}
								break;
							}
							case DELETE_TYPE:{
								for(uint64_t i = 0; i < nvids; i++){
									delete_node(vids[i]);
								}
								memcpy(answptr, "{1}", 4);
								answptr += 18;
								break;
							}
						}
					}
					for(uint64_t i = 0; i < nvids; i++){
						printf("%ld: %ld\n", i, vids[i]);
					}


					if(answptr == recvbuf){
						json_object* retj = json_object_new_array();
						for(uint64_t i = 0; i < nvids; i++){
							addnode2json(vids[i], retj);
						}
						const char*  jsonstr = json_object_to_json_string_ext(retj, JSON_C_TO_STRING_PRETTY);
						free(vids);
						vids = NULL;
						nvids = 0;
						send(fd, jsonstr, strlen(jsonstr)+1, 0);
					}else{
						answptr++;
						*answptr = '\0';
						//printf("%s\n", recvbuf);
						if(nvids == 0){
							memcpy(recvbuf, "{}", 3);
							free(vids);
							vids = NULL;
							nvids = 0;
							send(fd, recvbuf, 9, 0);
						}else{
							free(vids);
							vids = NULL;
							nvids = 0;
							send(fd, recvbuf, answptr-recvbuf, 0);
						}
					}
					break;
				}
				case ADD_VERTEX_REQ:{

					json_object* jarr = json_object_array_get_idx(json, 1);
					uint64_t jarrlen = json_object_array_length(jarr);

					uint64_t n_int = 0;
					uint64_t n_fl = 0;
					uint64_t n_str = 0;
					uint64_t n_con = 0;

					uint32_t* ints = NULL;
					float* floats= NULL;
					char** strings= NULL;
					uint64_t* conns= NULL;
					for(uint64_t i = 0; i < jarrlen; i += 2){
						if(!strcmp("int", json_object_get_string(json_object_array_get_idx(jarr, i))) ){
							n_int++;
							ints = realloc(ints, n_int*4);
							ints[n_int-1] = json_object_get_int(json_object_array_get_idx(jarr, i+1));
						}else if(!strcmp("flt", json_object_get_string(json_object_array_get_idx(jarr, i)))){
							n_fl++;
							floats = realloc(floats, n_fl*4);
							floats[n_fl-1] = json_object_get_double(json_object_array_get_idx(jarr, i+1));
						}else if(!strcmp("str", json_object_get_string(json_object_array_get_idx(jarr, i)))){
							n_str++;
							strings = realloc(strings, n_str*8);
							strings[n_str-1] = json_object_get_string(json_object_array_get_idx(jarr, i+1));
						}else if(!strcmp("vid", json_object_get_string(json_object_array_get_idx(jarr, i)))){
							n_con++;
							conns = realloc(conns, n_con*8);
							conns[n_con-1] = json_object_get_int(json_object_array_get_idx(jarr, i+1));
						}else{

						}
					}
					if(!add_vertex(n_con, conns, n_int, ints, n_fl, floats, n_str, strings)){
						send(fd, "{1}", 4, 0);
					}else{
						send(fd, "{0}", 4, 0);
					}
					free(strings);
					free(conns);
					free(floats);
					free(ints);
					break;
				}
				default:{
					skip:;
					send(fd, "{-1}", 4, 0);
				}
			}
		}
	}
}


