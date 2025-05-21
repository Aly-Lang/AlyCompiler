#include <stdio.h>

void print_usage(char** argv) {
	printf("USAGE: %s <path_to_file_to_compile>\n", argv[0]);
}

int main(int argc, char** argv) {
	if (argc < 2) {
		print_usage(argv);
		exit(0);
	}
	return 0;
}