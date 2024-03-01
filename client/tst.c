#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>


int main(int argc, char** argv){
	FILE* outf = fopen(argv[1], "w+");

	FILE* inpf = fopen("export (copy).csv", "r+");

	char inpbuf[512];

	uint64_t cnt = 0;

	char cmd[512];
	char* iter = cmd;

	uint64_t totallen = 0;

	while(fgets(inpbuf, 512, inpf)){
		printf("%s", inpbuf);
		uint64_t len = strlen(inpbuf);
		memcpy(iter, "add_vertex(\'vertex\', ", 21);
		iter += 21;
		memcpy(iter, inpbuf, len-1);
		iter += len-1;
		memcpy(iter, ");", 2);
		iter += 2;
		*iter = '\n';
		iter++;
		*iter = '\0';
		fwrite(cmd, 1, iter-cmd, outf);
		iter = cmd;
	}

	return 0;
}