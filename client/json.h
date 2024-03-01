#include <json-c/json.h>
#include <string.h>
#include <stdlib.h>



char* ast2json(struct ast_tree* tree){
	json_object* resjobj = json_object_new_array();

	json_object* jobj = json_object_new_object();


	json_object_object_add(jobj, "qtype", json_object_new_int(tree->type));
	switch(tree->type){
		case OPEN_FILE_REQ:{
			json_object_object_add(jobj, "fname", json_object_new_string(tree->file.filename));
			json_object_array_add(resjobj, jobj);
			break;
		}
		case CLOSE_FILE_REQ:{
			json_object_object_add(jobj, "fname", json_object_new_string(tree->file.filename));
			json_object_array_add(resjobj, jobj);
			break;
		}
		case CREATE_FILE_REQ:{
			json_object_object_add(jobj, "fname", json_object_new_string(tree->file.filename));
			json_object_array_add(resjobj, jobj);
			break;
		}
		case CREATE_SCHEMA_REQ:{

		}
		case DELETE_SCHEMA_REQ:{

		}
		case SELECT_REQ:{
			json_object_array_add(resjobj, jobj);
			json_object* jarr = json_object_new_array();			

			for(uint64_t i = 0; i < tree->statements->size; i++){
				struct statement* curstmnt = get_from_array(tree->statements, i);
				json_object_array_add(jarr, json_object_new_int(curstmnt->type));
				switch(curstmnt->type){
					case SELECT_CONDITION_TYPE:{
						json_object* jarr2 = json_object_new_array();
						for(uint64_t j = 0; j < curstmnt->conditions->size; j++){
							struct select_condition* curcond = get_from_array(curstmnt->conditions, j);
							json_object_array_add(jarr2, json_object_new_int(curcond->option));
							json_object_array_add(jarr2, json_object_new_int(curcond->attr_type));
							json_object_array_add(jarr2, json_object_new_string(curcond->attr_name));
							switch(curcond->attr_type){
								case INTEGER_AT:{
									json_object_array_add(jarr2, json_object_new_int64(curcond->value.integer_value));
									break;
								}
								case BOOL_AT:{
									json_object_array_add(jarr2, json_object_new_int64(curcond->value.bool_value));
									break;
								}
								case FLOAT_AT:{
									json_object_array_add(jarr2, json_object_new_double(curcond->value.float_value));
									break;
								}	
								case STRING_AT:{
									json_object_array_add(jarr2, json_object_new_string(curcond->value.string_value));
									break;
								}
								case REF_AT:{

									break;
								}

							}
						}
						json_object_array_add(jarr, jarr2);
						break;
					}
					case OUT_TYPE:{
						json_object_array_add(jarr, json_object_new_string(curstmnt->attr_name));
						break;
					}
					case DELETE_TYPE:{
						json_object_array_add(jarr, json_object_new_string("DELETE"));
						break;
					}
				}
			}
			json_object_array_add(resjobj, jarr);
			break;
		}
		case ADD_VERTEX_REQ:{
			json_object_object_add(jobj, "vid", json_object_new_string(tree->add_vertex.name));

			json_object_array_add(resjobj, jobj);

			json_object* jarr = json_object_new_array();

			for(uint64_t i = 0; i < tree->add_vertex.attribute_values->size; i++){
				struct attribute_value* curattr = get_from_array(tree->add_vertex.attribute_values, i);
				switch(curattr->attr_type){
					case INTEGER_AT:{
						if(!strcmp("vid", curattr->attr_name)){
							json_object_array_add(jarr, json_object_new_string("vid"));
							json_object_array_add(jarr, json_object_new_int64(curattr->value.integer_value));							
						}else{
							json_object_array_add(jarr, json_object_new_string("int"));
							json_object_array_add(jarr, json_object_new_int64(curattr->value.integer_value));
						}
						break;
					}
					case BOOL_AT:{
						json_object_array_add(jarr, json_object_new_string("int"));
						json_object_array_add(jarr, json_object_new_int64(curattr->value.bool_value));
						break;
					}
					case FLOAT_AT:{
						json_object_array_add(jarr, json_object_new_string("flt"));
						json_object_array_add(jarr, json_object_new_double(curattr->value.float_value));
						break;
					}
					case STRING_AT:{
						json_object_array_add(jarr, json_object_new_string("str"));
						json_object_array_add(jarr, json_object_new_string(curattr->value.string_value));
						break;
					}
					case REF_AT:{

						break;
					}	
				}
			}
			json_object_array_add(resjobj, jarr);
			break;
		}
		case UNDEFINED:{

		}
	}

	const char* jsonstr = json_object_to_json_string_ext(resjobj, JSON_C_TO_STRING_PRETTY);
	char* retstr = (char*)malloc(strlen(jsonstr));
	memcpy(retstr, jsonstr, strlen(jsonstr));
	json_object_put(resjobj);
	return retstr;
}


struct ast_tree* json2ast(char* json){
	
}