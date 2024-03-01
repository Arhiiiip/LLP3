/* %define parse.error verbose */

%{
    #include "ast_tree.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>

    int yylex();
    int yyparse();
    void yyerror(const char *s);
    extern char *yytext;

    struct ast_tree tree = {.type = UNDEFINED};
    bool array_list_created = false;
    struct statement *cur_statement = NULL;

    char *file_name;
    int opened = 0;
%}

%union
{
    /* types */
    char *string;
	int integer;
	double decimal;
	int boolean;

	char *ref_name;
	int data_type;
	int cmp_type;
}

/* reserved words */
%token VERTEX HAS OUT
%token OPEN CREATE CLOSE DELETE
%token CREATE_SCHEMA DELETE_SCHEMA
%token ADD_VERTEX TOK_NODES
%token EQUALS GREATER GREATER_EQUALS LESS LESS_EQUALS NOT_EQUALS CONTAINS

/* values types */
%token <integer> INTEGER
%token <decimal> DECIMAL
%token <boolean> BOOLEAN
%token <string> WORD
%token <string> FILENAME

%token MY_INTEGER
%token MY_FLOAT
%token MY_STRING
%token MY_BOOLEAN
%token MY_REF

/* other */
%token VALUES
%token OTHER
%token RIGHT_BRACE LEFT_BRACE QUOTE DOT COMMA SEMICOLON

/* types */
%type <cmp_type> cmp_type
%type <string> argument
%type <data_type> data_type

%start commands

%%

commands: /* empty */
|   commands command SEMICOLON { YYACCEPT; }
;

command:
	open_file
|   create_file
|   close_file
| 	create_schema
|   delete_schema
|   add_vertex
|   select
;

select:
	select_nodes { tree.type = SELECT_REQ; }
|   select select_condition
|   select join
|   select delete_command
;

open_file:
	OPEN LEFT_BRACE QUOTE FILENAME QUOTE RIGHT_BRACE {
		tree.type = OPEN_FILE_REQ;
		tree.file.filename = malloc(sizeof(char) * strlen($4));
		strcpy(tree.file.filename, $4);
	}
;

create_file:
	CREATE LEFT_BRACE QUOTE FILENAME QUOTE RIGHT_BRACE {
		tree.type = CREATE_FILE_REQ;
		tree.file.filename = malloc(sizeof(char) * strlen($4));
		strcpy(tree.file.filename, $4);
	}
;

close_file:
	CLOSE LEFT_BRACE QUOTE FILENAME QUOTE RIGHT_BRACE {
		tree.type = CLOSE_FILE_REQ;
		tree.file.filename = malloc(sizeof(char) * strlen($4));
        strcpy(tree.file.filename, $4);
	}
;

create_schema:
	CREATE_SCHEMA LEFT_BRACE argument attribute_pairs RIGHT_BRACE {
		tree.type = CREATE_SCHEMA_REQ;
		tree.create_schema.name = malloc(sizeof(char) * strlen($3));
		strcpy(tree.create_schema.name, $3);
}
;

delete_schema:
	DELETE_SCHEMA LEFT_BRACE argument RIGHT_BRACE {
		tree.type = DELETE_SCHEMA_REQ;
		tree.create_schema.name = malloc(sizeof(char) * strlen($3));
		strcpy(tree.create_schema.name, $3);
}
;

add_vertex:
	ADD_VERTEX LEFT_BRACE argument attribute_value_pairs RIGHT_BRACE {
		tree.type = ADD_VERTEX_REQ;
		tree.add_vertex.name = malloc(sizeof(char) * strlen($3));
		strcpy(tree.add_vertex.name, $3);
	}
;

select_nodes:
	VERTEX LEFT_BRACE argument RIGHT_BRACE {
		tree.schema_name = malloc(sizeof(char) * strlen($3));
		strcpy(tree.schema_name, $3);
	}
;

select_condition:
|   DOT HAS LEFT_BRACE select_statements RIGHT_BRACE {
		if(!array_list_created) {
			tree.statements = create_array();
			array_list_created = true;
		}
		add_to_array(tree.statements, cur_statement);
		cur_statement = NULL;
	}
;

join:
|   DOT OUT LEFT_BRACE argument RIGHT_BRACE {
		if(!array_list_created) {
			tree.statements = create_array();
			array_list_created = true;
		}
		cur_statement = malloc(sizeof(struct statement));
		cur_statement->type = OUT_TYPE;
		cur_statement->attr_name = malloc(sizeof(char) * strlen($4));
		strcpy(cur_statement->attr_name, $4);
		add_to_array(tree.statements, cur_statement);
		cur_statement = NULL;
	}
;

delete_command:
|   DOT DELETE {
		if(!array_list_created) {
			tree.statements = create_array();
			array_list_created = true;
		}
		cur_statement = malloc(sizeof(struct statement));
		cur_statement->type = DELETE_TYPE;
		add_to_array(tree.statements, cur_statement);
		cur_statement = NULL;
	}
;

select_statements:
|   select_statements select_statement COMMA { }
|   select_statements select_statement { }
;

select_statement:
	argument COMMA cmp_type LEFT_BRACE INTEGER RIGHT_BRACE {
		if(cur_statement == NULL) {
			cur_statement = malloc(sizeof(struct statement));
			cur_statement->type = SELECT_CONDITION_TYPE;
			cur_statement->conditions = create_array();
		}
		struct select_condition *cond = malloc(sizeof(struct select_condition));
		cond->attr_name = malloc(sizeof(char) * strlen($1));
		strcpy(cond->attr_name, $1);
		cond->option = $3;
		cond->attr_type = INTEGER_AT;
		cond->value.integer_value = $5;
		add_to_array(cur_statement->conditions, cond);
	}
|   argument COMMA cmp_type LEFT_BRACE DECIMAL RIGHT_BRACE {
		if(cur_statement == NULL) {
			cur_statement = malloc(sizeof(struct statement));
			cur_statement->type = SELECT_CONDITION_TYPE;
			cur_statement->conditions = create_array();
		}
		struct select_condition *cond = malloc(sizeof(struct select_condition));
		cond->attr_name = malloc(sizeof(char) * strlen($1));
		strcpy(cond->attr_name, $1);
		cond->option = $3;
		cond->attr_type = FLOAT_AT;
		cond->value.float_value = $5;
		add_to_array(cur_statement->conditions, cond);
	}
|   argument COMMA cmp_type LEFT_BRACE BOOLEAN RIGHT_BRACE {
		if(cur_statement == NULL) {
			cur_statement = malloc(sizeof(struct statement));
			cur_statement->type = SELECT_CONDITION_TYPE;
			cur_statement->conditions = create_array();
		}
		struct select_condition *cond = malloc(sizeof(struct select_condition));
		cond->attr_name = malloc(sizeof(char) * strlen($1));
		strcpy(cond->attr_name, $1);
		cond->option = $3;
		cond->attr_type = BOOL_AT;
		cond->value.bool_value = $5;
		add_to_array(cur_statement->conditions, cond);
}
|    argument COMMA cmp_type LEFT_BRACE argument RIGHT_BRACE {
		if(cur_statement == NULL) {
			cur_statement = malloc(sizeof(struct statement));
			cur_statement->type = SELECT_CONDITION_TYPE;
			cur_statement->conditions = create_array();
		}
		struct select_condition *cond = malloc(sizeof(struct select_condition));
		cond->attr_name = malloc(sizeof(char) * strlen($1));
		strcpy(cond->attr_name, $1);
		cond->option = $3;
		cond->attr_type = STRING_AT;
		cond->value.string_value = $5;
		add_to_array(cur_statement->conditions, cond);
	}
;

attribute_value_pairs:
|   attribute_value_pairs COMMA attribute_value_pair { }
;

attribute_value_pair:
	argument COMMA INTEGER {
		if(!array_list_created) {
			tree.add_vertex.attribute_values = create_array();
			array_list_created = true;
		}
		struct attribute_value *attr_val = malloc(sizeof(struct attribute_value));
		*attr_val = (struct attribute_value) {.attr_name = malloc(sizeof(char) * strlen($1)), .attr_type = INTEGER_AT, .value = (union value) {.integer_value = $3}};
		strcpy(attr_val->attr_name, $1);
		add_to_array(tree.add_vertex.attribute_values, attr_val);
	}
|   argument COMMA DECIMAL{
		if(!array_list_created) {
			tree.add_vertex.attribute_values = create_array();
			array_list_created = true;
		}
		struct attribute_value *attr_val = malloc(sizeof(struct attribute_value));
		*attr_val = (struct attribute_value) {.attr_name = malloc(sizeof(char) * strlen($1)), .attr_type = FLOAT_AT, .value = (union value) {.float_value = $3}}; 
		strcpy(attr_val->attr_name, $1);
		add_to_array(tree.add_vertex.attribute_values, attr_val);
	}
|   argument COMMA BOOLEAN{
		if(!array_list_created) {
			tree.add_vertex.attribute_values = create_array();
			array_list_created = true;
		}
		struct attribute_value *attr_val = malloc(sizeof(struct attribute_value));
		*attr_val = (struct attribute_value) {.attr_name = malloc(sizeof(char) * strlen($1)), .attr_type = BOOL_AT, .value = (union value) {.bool_value = $3}};
		strcpy(attr_val->attr_name, $1);
		add_to_array(tree.add_vertex.attribute_values, attr_val);
	}
|   argument COMMA argument{
		if(!array_list_created) {
			tree.add_vertex.attribute_values = create_array();
			array_list_created = true;
		}
		struct attribute_value *attr_val = malloc(sizeof(struct attribute_value));
		*attr_val = (struct attribute_value) {.attr_name = malloc(sizeof(char) * strlen($1)), .attr_type = STRING_AT, .value = (union value) {.string_value = malloc(sizeof(char) * strlen($3))}};
		strcpy(attr_val->value.string_value, $3);
		strcpy(attr_val->attr_name, $1);
		add_to_array(tree.add_vertex.attribute_values, attr_val);
}
;

attribute_pairs:
|   attribute_pairs COMMA attribute_pair { }
;

data_type:
	MY_INTEGER { $$ = INTEGER_AT; }
| MY_STRING { $$ = STRING_AT; }
| MY_FLOAT { $$ = FLOAT_AT; }
| MY_BOOLEAN { $$ = BOOL_AT; }
| MY_REF { $$ = REF_AT; }
;

attribute_pair:
	argument COMMA data_type {
		if (!array_list_created) {
		tree.create_schema.attributes = create_array();
		array_list_created = true;
		}
		struct attribute* attr_decl = malloc(sizeof(struct attribute));
		*attr_decl = (struct attribute) {.attr_name = malloc(sizeof(char) * strlen($1)), .attr_type = $3,};
		strcpy(attr_decl->attr_name, $1);
		add_to_array(tree.create_schema.attributes, attr_decl);
	}
|   argument COMMA MY_REF LEFT_BRACE argument RIGHT_BRACE {
		if (!array_list_created) {
		tree.create_schema.attributes = create_array();
		printf("array created\n");
		array_list_created = true;
		}
		struct attribute* attr_decl = malloc(sizeof(struct attribute));
		*attr_decl = (struct attribute) {.attr_name = malloc(sizeof(char) * strlen($1)), .attr_type = REF_AT, .schema_ref_name = malloc(sizeof(char) * strlen($5))};
		strcpy(attr_decl->attr_name, $1);
		strcpy(attr_decl->schema_ref_name, $5);
		add_to_array(tree.create_schema.attributes, attr_decl);
	}
;

cmp_type:
	EQUALS { $$ = EQUALS_CMP; }
|   GREATER { $$ = GREATER_CMP; }
|   GREATER_EQUALS { $$ = GREATER_EQUALS_CMP; }
|   LESS { $$ = LESS_CMP; }
|   LESS_EQUALS { $$ = LESS_EQUALS_CMP; }
|   NOT_EQUALS { $$ = NOT_EQUALS_CMP; }
|   CONTAINS { $$ = CONTAINS_CMP; }
;

argument:
	QUOTE WORD QUOTE { $$ = $2; }
;

%%

void yyerror (char const *s) {
   fprintf (stderr, "%s undeclared", s);
}

int yywrap() {
	return 1;
}

struct ast_tree get_request_tree(){
	array_list_created = 0;
	struct ast_tree rtree;
	rtree = tree;

	//free_tree(&tree);
	tree.type = UNDEFINED;
	tree.statements = 0;

	return rtree;
}
