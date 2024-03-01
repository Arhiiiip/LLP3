#ifndef __AST_TREE_H__
#define __AST_TREE_H__

#include <stdbool.h>
#include "stdlib.h"
#include "array.h"

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

static char *const select_condition_as_strings[] = {
        [EQUALS_CMP] = "=",
        [GREATER_CMP] = ">",
        [GREATER_EQUALS_CMP] = ">=",
        [LESS_CMP] = "<",
        [LESS_EQUALS_CMP] = "<=",
        [NOT_EQUALS_CMP] = "!=",
        [CONTAINS_CMP] = "CONTAINS SUBSTRING"
};

enum statement_type {
    SELECT_CONDITION_TYPE,
    OUT_TYPE,
    DELETE_TYPE
};

struct file_s {
    char *filename;
};

struct attribute {
    char *attr_name;
    enum data_type attr_type;
    char *schema_ref_name;
};

struct create_schema_s {
    char *name;
    struct array *attributes;
};

struct delete_schema_s{
    char *name;
};

union value {
    int integer_value;
    bool bool_value;
    char *string_value;
    float float_value;
};

struct attribute_value {
    char *attr_name;
    enum data_type attr_type;
    union value value;
};

struct add_vertex_s{
    char *name;
    struct array *attribute_values;
};

struct select_condition {
    char *attr_name;
    enum compare_option option;
    enum data_type attr_type;
    union value value;
};

struct statement {
    enum statement_type type;
    union {
        struct array *conditions;
        char *attr_name;
    };
};

struct ast_tree {
    enum request_type type;
    char *schema_name;
    union {
        struct file_s file;
        struct create_schema_s create_schema;
        struct delete_schema_s delete_schema;
        struct add_vertex_s add_vertex;
        struct array *statements;
    };
};

inline unsigned int get_array_size(struct array *l);

void print_request_tree(struct ast_tree tree);

struct ast_tree get_request_tree();

void free_tree(struct ast_tree* tree);

#endif
