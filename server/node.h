#ifndef __NODE_H__
#define __NODE_H__

#include "file.h"
#include <json-c/json.h>

extern uint64_t PAGE_SIZE;

extern FILE* storage_file;
extern json_object* jsonn;

struct node{
	uint64_t node_id; // node's id
	uint64_t n; // amount of connected nodes
	uint64_t node_ptr; // a pointer to an array of pointers to adjacent nodes
	uint64_t n_int; // amount of integer attributes
	uint64_t int_ptr; // a pointer to an array of integer attributes
	uint64_t n_float; // amount of float attributes
	uint64_t float_ptr; // a pointer to an array of float attributes
	uint64_t n_str; // amount of string attributes;
	uint64_t str_ptr; // a pointer to an array of pointers to 0-terminated strings

	uint64_t next_ptr; // pointers for storing a node in a linked list 
	uint64_t prev_ptr; // so that we do not need to do complex graph algorithms
}__attribute__((packed));

struct str_desc{
	uint64_t str_ptr;
	uint64_t length;
};


uint64_t find_node_by_id(uint64_t id);

uint64_t find_id_by_node(uint64_t addr);

void create_new_node(uint64_t flag);

uint64_t delete_node(uint64_t id);

uint64_t connect_nodes(uint64_t id1, uint64_t id2);

void list_nodes();

void print_node_info(uint64_t id);

void print_connected_nodes(uint64_t id);

void print_int_attr(uint64_t id);

void print_float_attr(uint64_t id);

void print_str_attr(uint64_t id);

void print_help();

void edit_int_attr(uint64_t id, uint64_t pos);

void edit_float_attr(uint64_t id, uint64_t pos);

void edit_str_attr(uint64_t id, uint64_t pos);

void user(); // a user function. Will be smth like this: get command(single char), call corresponding function

#endif


// 5c