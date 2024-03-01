#ifndef __FILE_H__
#define __FILE_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "defines.h"
#include "platform.h"

extern uint64_t PAGE_SIZE;

//#include <sys/time.h>
//long long int current_timestamp(); // solely for test purposes!
//FILE* __testfile;



struct holes_list_entry{ 
	uint64_t sz;
	uint64_t hole_ptr;
	uint64_t prev_ptr;
	uint64_t next_ptr;
}__attribute__((packed));


struct file_header{
	uint16_t signature;
	struct holes_list_entry first_hole;
	uint64_t root_node_ptr;
	uint64_t node_id;
}__attribute__((packed));

struct map{
	void* page;
	void* data;
	uint64_t size;
};

extern FILE* storage_file;

uint64_t file_sz(FILE* file);

FILE* open_storage_file(char* path, char* flg);

uint64_t write_to_file(void* buf, uint64_t size, uint64_t flag);

void delete_from_file(uint64_t d_ptr, uint64_t size);

void* extract_data(uint64_t d_ptr, uint64_t size);

void check_holes(); // a very brute force approach function, that checks all holes so that any of adjacent ones are combined into a single hole and the leftover hole descriptor becomes an SRH. O(N^2), so should only be ran occasionally to keep the holes in check.

struct map* map_in_file(uint64_t d_ptr, uint64_t size);

void unmap_in_file(struct map* map);

#endif




///home/adivanced/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/usr/local/pspdev/bin:/home/adivanced/.local/share/JetBrains/Toolbox/scripts:/usr/local/pspdev/bin:/usr/local/pspdev/psp/sdk/bin