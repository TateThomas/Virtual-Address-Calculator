#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAGE_UNITS (1) 	// 0 = B, 1 = KB, 2 = MB, 3 = GB, ...
#define PAGE_SIZE (4) 	// in defined units

#define HEX_DIGITS (8) 	// how many hex digits are shown
#define ADDR_SPACE (HEX_DIGITS * 4) 	// address space in bits


int main(int argc, char** argv) {

	if (argc == 1) {
		char* units[] = {"B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"};
		printf("Usage: $%s <hex address (%d bit address space, %d%s pages)\n",
			argv[0], ADDR_SPACE, PAGE_SIZE, units[PAGE_UNITS]);
		return 1;
	}
	if (strlen(argv[1]) > HEX_DIGITS) {
                printf("Address 0x%s is out of range (%d bit address space).\n", argv[1], ADDR_SPACE);
                return 2;
        }

	char* ptr;
        unsigned long long int logical, page, index, offset;

	logical = strtoull(argv[1], &ptr, 16); 	// convert hex string

	page = PAGE_SIZE << ((PAGE_UNITS == 0) ? 8 : (PAGE_UNITS * 10)); 	// calculate page size (PAGE_SIZE Units, i.e. 4 KB)
	index = logical / page;
	offset = logical % page;

	printf("Logical Addr:0x%2$0*1$llX - Page Index:0x%3$0*1$llX - Offset:0x%4$0*1$llX\n", HEX_DIGITS, logical, index, offset);

	return 0;
}
