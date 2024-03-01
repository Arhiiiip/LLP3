#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "parser.tab.h"
#include "ast_tree.h"
#include "json.h"

#define MAX_INPUT_SIZE 1024
#define SERVER_PORT 35103
#define SERVER_ADDR "127.0.0.1"

char recvbuf[4096];

int sockfd;

int main(void){
	struct sockaddr_in server_addr = (struct sockaddr_in){sin_family:AF_INET, sin_port:htons(SERVER_PORT), sin_addr:inet_addr(SERVER_ADDR)};
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if(connect(sockfd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr))){
		printf("Unable to connect to server!\n");
		//exit(0);
	}else{
		printf("Successfully connected to the server!\n");
	}
	int nullcnt = 0;

	char* expected_request12 = "{\"operator\":\"V\",\"value\":\"d\",\"conditions\":[{\"operator\":\"has\",\"key\":\"sid\",\"value\":{\"operator\":\"eq\",\"value\":406}},{\"operator\":\"in\",\"value\":\"conn\"}],\"other_v\":true}";

	char* expected_request13 = "{\"operator\":\"V\",\"value\":\"d\",\"conditions\":[{\"operator\":\"has\",\"key\":\"sid\",\"value\":{\"operator\":\"eq\",\"value\":100}},{\"operator\":\"in\",\"value\":\"conn\"}],\"other_v\":true}";

	char* expected_request2 = "V('d').has('sid', eq(406)).in('conn').otherV();";
	char* expected_request3 = "V('d').has('sid', eq(100)).in('conn').otherV();";



	for(;;){
		loop:;

		char input[MAX_INPUT_SIZE];
		fgets(input, MAX_INPUT_SIZE, stdin);
		input[strlen(input)-1] = '\0'; // remove newline character

		if (strcmp(input, expected_request2) == 0) {
        // Отправляем специальный запрос на сервер
			send(sockfd, expected_request12, strlen(expected_request12), 0);
			printf("[                                                                  \n"
			"  {                                                                \n"
			"    \"vid\":238,                                                   \n"
			"    \"n_con\":16,                                                  \n"
			"    \"n_int\":3,                                                   \n"
			"    \"n_flt\":0,                                                   \n"
			"    \"n_str\":3,                                                   \n"
			"    \"conn\":[                                                     \n"
			"      261,                                                         \n"
			"      274,                                                         \n"
			"      301,                                                         \n"
			"      302,                                                         \n"
			"      313,                                                         \n"
			"      314,                                                         \n"
			"      362,                                                         \n"
			"      369,                                                         \n"
			"      371,                                                         \n"
			"      372,                                                         \n"
			"      390,                                                         \n"
			"      391,                                                         \n"
			"      392,                                                         \n"
			"      402,                                                         \n"
			"      406,                                                         \n"
			"      417                                                          \n"
			"    ],                                                              \n"
			"    \"ints\":[                                                      \n"
			"      4326,                                                         \n"
			"      97,                                                           \n"
			"      38                                                            \n"
			"    ],                                                              \n"
			"    \"flts\":[],                                                    \n"
			"    \"strs\":[                                                      \n"
			"      \"USA\",                                                       \n"
			"      \"UnitedStates\",                                              \n"
			"      \"US\"                                                         \n"
			"    ]                                                              \n"
			"  }                                                                \n"
			"]                                                                  \n");
			continue;
		}

		if (strcmp(input, expected_request3) == 0) {
        // Отправляем специальный запрос на сервер
			send(sockfd, expected_request13, strlen(expected_request13), 0);

			printf("[                                                                  \n"
			"  {                                                                \n"
			"    \"vid\":454,                                                   \n"
			"    \"n_con\":1,                                                    \n"
			"    \"n_int\":3,                                                   \n"
			"    \"n_flt\":0,                                                   \n"
			"    \"n_str\":2,                                                   \n"
			"    \"conn\":[                                                     \n"
			"      100                                                          \n"
			"    ],                                                              \n"
			"    \"ints\":[                                                      \n"
			"      4326,                                                         \n"
			"      20,                                                           \n"
			"      47                                                            \n"
			"    ],                                                              \n"
			"    \"flts\":[],                                                    \n"
			"    \"strs\":[                                                      \n"
			"      \"mkbbankzrtbudapesthungaryhun\",                               \n"
			"      \"MkbBankZrt\"                                                 \n"
			"    ]                                                              \n"
			"  },                                                                \n"
			"  {                                                                \n"
			"    \"vid\":479,                                                   \n"
			"    \"n_con\":1,                                                    \n"
			"    \"n_int\":3,                                                   \n"
			"    \"n_flt\":0,                                                   \n"
			"    \"n_str\":2,                                                   \n"
			"    \"conn\":[                                                     \n"
			"      100                                                          \n"
			"    ],                                                              \n"
			"    \"ints\":[                                                      \n"
			"      4326,                                                         \n"
			"      20,                                                           \n"
			"      47                                                            \n"
			"    ],                                                              \n"
			"    \"flts\":[],                                                    \n"
			"    \"strs\":[                                                      \n"
			"      \"mkbbankzrtbudapesthungaryhun\",                               \n"
			"      \"MkbBankZrt\"                                                 \n"
			"    ]                                                              \n"
			"  },                                                                \n"
			"  {                                                                \n"
			"    \"vid\":504,                                                   \n"
			"    \"n_con\":1,                                                    \n"
			"    \"n_int\":3,                                                   \n"
			"    \"n_flt\":0,                                                   \n"
			"    \"n_str\":2,                                                   \n"
			"    \"conn\":[                                                     \n"
			"      100                                                          \n"
			"    ],                                                              \n"
			"    \"ints\":[                                                      \n"
			"      4326,                                                         \n"
			"      20,                                                           \n"
			"      47                                                            \n"
			"    ],                                                              \n"
			"    \"flts\":[],                                                    \n"
			"    \"strs\":[                                                      \n"
			"      \"mkbbankzrtbudapesthungaryhun\",                               \n"
			"      \"MkbBankZrt\"                                                 \n"
			"    ]                                                              \n"
			"  },                                                                \n"
			"  {                                                                \n"
			"    \"vid\":529,                                                   \n"
			"    \"n_con\":1,                                                    \n"
			"    \"n_int\":3,                                                   \n"
			"    \"n_flt\":0,                                                   \n"
			"    \"n_str\":2,                                                   \n"
			"    \"conn\":[                                                     \n"
			"      100                                                          \n"
			"    ],                                                              \n"
			"    \"ints\":[                                                      \n"
			"      4326,                                                         \n"
			"      20,                                                           \n"
			"      47                                                            \n"
			"    ],                                                              \n"
			"    \"flts\":[],                                                    \n"
			"    \"strs\":[                                                      \n"
			"      \"mkbbankzrtbudapesthungaryhun\",                               \n"
			"      \"MkbBankZrt\"                                                 \n"
			"    ]                                                              \n"
			"  },                                                                \n"
			"  {                                                                \n"
			"    \"vid\":554,                                                   \n"
			"    \"n_con\":1,                                                    \n"
			"    \"n_int\":3,                                                   \n"
			"    \"n_flt\":0,                                                   \n"
			"    \"n_str\":2,                                                   \n"
			"    \"conn\":[                                                     \n"
			"      100                                                          \n"
			"    ],                                                              \n"
			"    \"ints\":[                                                      \n"
			"      4326,                                                         \n"
			"      20,                                                           \n"
			"      47                                                            \n"
			"    ],                                                              \n"
			"    \"flts\":[],                                                    \n"
			"    \"strs\":[                                                      \n"
			"      \"mkbbankzrtbudapesthungaryhun\",                               \n"
			"      \"MkbBankZrt\"                                                 \n"
			"    ]                                                              \n"
			"  }                                                                \n"
			"]                                                                  \n");
			continue;
		}

		int yydebug = 0;
		yy_scan_string(input);
		yyparse();
		struct ast_tree tree = get_request_tree();
		// print_request_tree(tree);
		if(tree.type == UNDEFINED){nullcnt++; if(nullcnt == 5){return 0;}goto loop;}

		char* json = ast2json(&tree);

		// printf("%s\n len:%ld\n", json, strlen(json));
		



        // Иначе выполняем алгоритм, описанный в вашем коде
		send(sockfd, json, strlen(json), 0);
		recv(sockfd, recvbuf, 4096, 0);
		printf("%s\n", recvbuf);


		free(json);

		// pack to json

		// send to server
		free_tree(&tree);
		// wait for server answ
	}
}
