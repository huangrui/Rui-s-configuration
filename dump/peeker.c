/*
 * Accessing a physical memory region using mmap() on /dev/mem
 * Compile with 'gcc -Wall -O peeker.c -o peeker' (-O *is* mandatory)
 *
 */


#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <linux/pci.h>
#include <sys/io.h>
#include <sys/mman.h>
#include <errno.h>

typedef unsigned int u32;

/*
static void dump_memory(void *mem, u32 len)
{
	int i, j;
	int left;
	u8 *addr;
	printf("dump begins@%p, len %d\n", mem, len);

	left = len;
	j = 0, addr = mem;
	while (left > 0) {
		printf("%08x: ", j++);
		for (i = 0; i < 0x10; i++)
			printf("%02x ", *addr++);
		printf("\n");
		left -= 0x10;
	}
}
*/
static void save_dump(void *mem, u32 len, const char *saved_file)
{
	int fd;

	fd = open(saved_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1) {
		perror("can't open file for write");
		return;
	}

	if (write(fd, mem, len) != len)
		perror("write to file failed\n");

	close(fd);
}

int main( int argc, char *argv[])
{
	u32 addr;	/* the mem_addr */  
	u32 map_len; 	/* the length */
	u32 dump_off; 	/* from where to dump */
	u32 dump_len; 	/* dump len */
	int fd; 	/* The file descriptor */
	char *ptr;

	if(argc != 6){
		fprintf(stderr, "usage:./peeker mem_addr map_length dump_off dump_len saved_file_path\n");
		return -1;
	} else {
		sscanf(argv[1], "0x%x", &addr);
		sscanf(argv[2], "0x%x", &map_len);
		sscanf(argv[3], "0x%x", &dump_off);
		sscanf(argv[4], "0x%x", &dump_len);
	}


	/* Check IO permissions to be able to open /dev/mem */
	if(iopl(3)) {
		fprintf(stderr, "Cannot get I/O permissions (being root helps)\n");
		return -1;
	}

	/* We now open the memory... */
	fd = open ( "/dev/mem", O_RDWR);
	if (fd == -1) {
		perror("can't open /dev/mem");
		return -1;
	}

	/* ...and map the memory area (man 2 mmap for more info) */
	ptr = mmap(NULL, map_len, PROT_READ, MAP_SHARED, fd, (off_t)addr);
	if (ptr == MAP_FAILED) {
		perror("map failed");
		close(fd);
		return -1;
	}

	printf("virtual memory pointer: %p for memory addr 0x%x\n", ptr, addr);

	//dump_memory((char *)ptr + dump_off, dump_len);

	save_dump(ptr + dump_off, dump_len, argv[5]);

	munmap(ptr, map_len);
	close(fd);

	return 0;
}

