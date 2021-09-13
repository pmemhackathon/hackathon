#include "numa_helpers.h"

#include <sys/mman.h>

int main() {
	int flags = MAP_PRIVATE | MAP_ANONYMOUS;
	size_t size = 4096;

    void *addr = mmap(NULL, size, PROT_READ | PROT_WRITE, flags, -1, 0);
    if (addr == MAP_FAILED) {
        perror("mmap");
        return -1;
    }

	printf("mmap %lu bytes, addr = %p\n", size, addr);
    
    struct bitmask *mask = get_numa_mask_for_highest_capacity_node();

	// note: this works for PRIVATE mapping but not for SHARED ones
	// for SHARED ones, set_mempolicy can be used
    int ret = mbind(addr, size, MPOL_BIND, mask->maskp, mask->size, 0);
    if (ret) {
		perror("mbind");
		return -1;
    }

	// force page allocation
	*((char*)addr) = 0;
	
	// verify node id
	int numa_node = get_numa_node_by_ptr(addr);
	printf("numa_node for ptr: %d\n", numa_node);
	
	ret = munmap(addr, size);
	if (ret) {
        perror("munmap");
		return -1;
    }

	numa_bitmask_free(mask);

	void *default_mlloc_ptr = malloc(size);

	// force page allocation
	*((char*)default_mlloc_ptr) = 0;

	// verify node id
	int malloc_numa_node = get_numa_node_by_ptr(default_mlloc_ptr);
	printf("numa_node for malloc'ed ptr: %d\n", malloc_numa_node);

	free(default_mlloc_ptr);
	
	return 0;
}
