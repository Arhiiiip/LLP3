#include "ast_tree.h"
#include <stdio.h>


static void print_schema(struct create_schema_s schema) {
	printf("CREATE SCHEMA: \"%s\"", schema.name);
	if (!schema.attributes) {
		printf(" {\n");
		printf("NO ATTRIBUTES\n}\n");
		return;
	}
	printf(" {\n");
	for (int i = 0; i < get_array_size(schema.attributes); i++) {
		struct attribute *cur_attr = get_from_array(schema.attributes, i);
		switch (cur_attr->attr_type) {
			case INTEGER_AT: {
				printf("\t\"%s\": INTEGER\n", cur_attr->attr_name);
				break;
			}
			case BOOL_AT: {
				printf("\t\"%s\": BOOLEAN\n", cur_attr->attr_name);
				break;
			}
			case FLOAT_AT: {
				printf("\t\"%s\": FLOAT\n", cur_attr->attr_name);
				break;
			}
			case STRING_AT: {
				printf("\t\"%s\": STRING\n", cur_attr->attr_name);
				break;
			}
			case REF_AT: {
				printf("\t\"%s\": REFERENCE TO %s\n", cur_attr->attr_name, cur_attr->schema_ref_name);
				break;
			}
		}
	}
	printf("}\n");
}

static void print_condition(struct select_condition condition) {
	switch (condition.attr_type) {
		case INTEGER_AT: {
			printf("\t\"%s\" %s %d\n", condition.attr_name, select_condition_as_strings[condition.option],
				   condition.value.integer_value);
			break;
		}
		case BOOL_AT: {
			printf("\t\"%s\" %s %s\n", condition.attr_name, select_condition_as_strings[condition.option],
				   condition.value.bool_value ? "TRUE" : "FALSE");
			break;
		}
		case FLOAT_AT: {
			printf("\t\"%s\" %s %.4f\n", condition.attr_name, select_condition_as_strings[condition.option],
				   condition.value.float_value);
			break;
		}
		case STRING_AT: {
			printf("\t\"%s\" %s %s\n", condition.attr_name, select_condition_as_strings[condition.option],
				   condition.value.string_value);
			break;
		}
		case REF_AT:
			break;
	}
}

static void print_statement(struct statement stmt) {
	switch (stmt.type) {
		case SELECT_CONDITION_TYPE: {
			printf("\tFILTER:\n");
			for (int i = 0; i < get_array_size(stmt.conditions); i++) {
				struct select_condition *condition = get_from_array(stmt.conditions, i);
				print_condition(*condition);
			}
			break;
		}
		case OUT_TYPE: {
			printf("\tOUT BY:\"%s\"\n", stmt.attr_name);
			break;
		}
		case DELETE_TYPE: {
			printf("\tDELETE\n");
			break;
		}
	}
}

static void print_statements(struct array *statements) {
	if (statements == NULL) return;
	printf("!!!%ld\n", get_array_size(statements));
	for (int i = 0; i < get_array_size(statements); i++) {
		struct statement *cur_stmt = get_from_array(statements, i);
		print_statement(*cur_stmt);
	}
}

static void print_node(struct add_vertex_s node) {
	printf("CREATE NODE IN SCHEMA: %s\n", node.name);
	for (int i = 0; i < get_array_size(node.attribute_values); ++i) {
		struct attribute_value *cur_attr = get_from_array(node.attribute_values, i);
		switch (cur_attr->attr_type) {
			case INTEGER_AT: {
				printf("\"%s\": %d\n", cur_attr->attr_name, cur_attr->value.integer_value);
				break;
			}
			case BOOL_AT: {
				printf("\"%s\": %s\n", cur_attr->attr_name, cur_attr->value.bool_value ? "true" : "false");
				break;
			}
			case FLOAT_AT: {
				printf("\"%s\": %f\n", cur_attr->attr_name, cur_attr->value.float_value);
				break;
			}
			case STRING_AT: {
				printf("\"%s\": %s\n", cur_attr->attr_name, cur_attr->value.string_value);
				break;
			}
			case REF_AT: {
				printf("\"%s\": %d\n", cur_attr->attr_name, cur_attr->value.integer_value);
				break;
			}
		}
	}
}

void print_request_tree(struct ast_tree tree) {
	switch (tree.type) {
		case OPEN_FILE_REQ: {
			printf("OPEN FILE: \"%s\"\n", tree.file.filename);
			break;
		}
		case CREATE_FILE_REQ: {
			printf("CREATE FILE: \"%s\"\n", tree.file.filename);
			break;
		}
		case CLOSE_FILE_REQ: {
			printf("CLOSE FILE: \n");
			break;
		}
		case CREATE_SCHEMA_REQ: {
			print_schema(tree.create_schema);
			break;
		}
		case DELETE_SCHEMA_REQ: {
			printf("DELETE SCHEMA: \"%s\"\n", tree.delete_schema.name);
			break;
		}
		case ADD_VERTEX_REQ: {
			print_node(tree.add_vertex);
			break;
		}
		case SELECT_REQ: {
			printf("SELECT FROM \"%s\" {\n", tree.schema_name);
			print_statements(tree.statements);
			printf("}\n");
			break;
		}
		case UNDEFINED:
			printf("NULL TREE\n");
			break;
	}
}

void free_tree(struct ast_tree* tree){
	//printf("!?!?!\n");
	free(tree->schema_name);
	switch(tree->type){
		case OPEN_FILE_REQ: {
			free(tree->file.filename);
			tree->file.filename = NULL;
			break;
		}
		case CREATE_FILE_REQ: {
			free(tree->file.filename);
			tree->file.filename = NULL;
			break;
		}
		case CLOSE_FILE_REQ: {
			//free(tree->file.filename);
			break;
		}
		case CREATE_SCHEMA_REQ: {
			free(tree->create_schema.name);
			tree->create_schema.name = NULL;
			destroy_array(tree->create_schema.attributes);
			tree->create_schema.attributes = NULL;
			break;
		}
		case DELETE_SCHEMA_REQ: {
			free(tree->delete_schema.name);
			tree->delete_schema.name = NULL;
			break;
		}
		case ADD_VERTEX_REQ: {
			free(tree->add_vertex.name);	
			tree->add_vertex.name = NULL;
			destroy_array(tree->add_vertex.attribute_values);	
			tree->add_vertex.attribute_values = NULL;
			break;
		}
		case SELECT_REQ: {
			destroy_array(tree->statements);
			tree->statements = NULL;
			break;
		}
		case UNDEFINED:
			printf("NULL TREE\n");
			break;
	}       
}




