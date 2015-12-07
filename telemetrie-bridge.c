
#include <all.h>

Model ModelData[MODELS_MAX];

void sys_message (char *msg) {
}

int file_exists (char *fileName) {
	struct stat buf;
	int i = stat(fileName, &buf);
	if (i == 0) {
		return 1;
	}
	return 0;
}

int main ( int argc, char *argv[] ) {

	mavlink_init(0, "/dev/ttyS0", 57600);


	printf("hallo shell :)\n");


	mavlink_exit(0);


}

