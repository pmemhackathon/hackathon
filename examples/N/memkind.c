#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <memkind.h>

#include "numa_helpers.h"

/* Single-argument wrappers for Memkind's malloc and free */
void* lowest_latency_malloc(size_t size)
{
    return memkind_malloc(MEMKIND_LOWEST_LATENCY_LOCAL, size);
}

void lowest_latency_free(void* ptr)
{
    memkind_free(MEMKIND_LOWEST_LATENCY_LOCAL, ptr);
}

void* highest_capacity_malloc(size_t size)
{
    return memkind_malloc(MEMKIND_HIGHEST_CAPACITY, size);
}

void highest_capacity_free(void* ptr)
{
    memkind_free(MEMKIND_HIGHEST_CAPACITY, ptr);
}

int main(void)
{
	size_t size = PAGE_SIZE;
    void *ptr_capacity = highest_capacity_malloc(size);

	// force page allocation
	*((char*)ptr_capacity) = 0;
	
	// check node id
	int capacity_numa_node = get_numa_node_by_ptr(ptr_capacity);
	printf("numa_node for capacity alloc: %d\n", capacity_numa_node);
	
	void *ptr_latency = lowest_latency_malloc(size);
	
	// force page allocation
	*((char*)ptr_latency) = 0;

	// check node id
	int latency_numa_node = get_numa_node_by_ptr(ptr_latency);
	printf("numa_node for latency alloc: %d\n", latency_numa_node);
    
    highest_capacity_free(ptr_capacity);
	lowest_latency_free(ptr_latency);
    return 0;
}
