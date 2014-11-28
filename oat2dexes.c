#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void write_to_file (unsigned char *data, int size, int file_count)
{
	char filename[16];
	sprintf(filename, "dex%02d.dex", file_count);
	printf("Writing %d bytes to %s\n", size, filename);
	FILE *fp = fopen(filename, "wb");
	fwrite(data, 1, size, fp);
	fclose(fp);
}

int main (int argc, char *argv[])
{
	if (argc != 2) {
		printf("Usage: %s file.oat\n", argv[0]);
		return 1;
	}

	FILE *infp = fopen(argv[1], "rb");
	if (infp == NULL) {
		printf("can't open %s\n", argv[1]);
		return 1;
	}

	fseek(infp, 0, SEEK_END);
	int insize = ftell(infp);
	fseek(infp, 0, SEEK_SET);
	unsigned char *indata = malloc(insize);
	fread(indata, 1, insize, infp);
	fclose(infp);

	int file_count = 0;
	int ptr;
	for (ptr = 0; ptr < insize; ptr ++) {
		if (memcmp(indata+ptr, "dex\n035", 8) != 0)
			continue;
		unsigned int dexsize = *(unsigned int *)(indata+ptr+32); // the 'file_size_' field in the header
		if (ptr + dexsize > insize)
			continue;
		write_to_file(indata+ptr, dexsize, ++file_count);
	}
	return 0;
}
