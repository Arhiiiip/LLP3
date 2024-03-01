#include "user.h"

uint64_t PAGE_SIZE;
FILE* storage_file;


#define SERVER_PORT 35103
#define SERVER_ADDR "0.0.0.0"//"77.234.196.4"

json_object* jsonn;

int main(int argc, char** argv){
	//__testfile = fopen("tst.csv", "r+"); //uncomment for testing
	//json_object* dummy = json_tokener_parse("{}");
	//printf("%ld\n", validate_json(dummy));


	find_page_size();

	struct sockaddr_in server_addr = (struct sockaddr_in){sin_family:AF_INET, sin_port:htons(SERVER_PORT), sin_addr:inet_addr(SERVER_ADDR)}; jsonn = json_tokener_parse("{}");

	struct sockaddr_in client_addr;

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	server_addr.sin_port = htons(SERVER_PORT);
	bind(sockfd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr));

	if(listen(sockfd, 10) < 0){
		printf("Error while listening\n");
	}

	int client_sock;
	int client_sock_len;

	listen_loop:;

	client_sock = accept(sockfd, (struct sockaddr*)&client_addr, &client_sock_len);
	if(client_sock > 0){
		if(!(fork())){
			printf("Got connection!\n");
			handle_client(client_sock, client_addr);
		}else{
			goto listen_loop;
		}
	}else{
		goto listen_loop;
	}


	return 0;

	//storage_file = open_storage_file(argv[1]);

	//print_help();
	//create_new_node(1);
	//user();

	//delete_node(1);
	//connect_nodes(0, 2);
	

	// list_nodes();
	// print_node_info(0);
	// print_connected_nodes(0);
	// print_int_attr(0);
	// print_float_attr(0);
	// print_str_attr(0);

	// char blablo[10] = "123456789";
	// char blabla[10] = "!PPAAPPBB";

	// char big[20] = "?????????<<<<<<<<<<";
	// char srh[32] = "!PPAAPPBB!PPAAPPBB!PPAAPPBB()ll";

	// //for(int i = 0; i < 10; i++){
	// //	write_to_file(blablo, 10, 0);
	// //}

	// //delete_from_file(210, 20);
	// write_to_file(srh, 5, 0);

	// //delete_from_file(72, 10);
	// //void* buf = extract_data(42, 10);
	// //printf("%s\n", buf);
}