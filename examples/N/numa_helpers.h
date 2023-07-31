#include <numa.h>
#include <numaif.h>
#include <stdio.h>
#include <stdint.h>

#define PAGE_SIZE 4096

void *align_to_page(void *addr)
{
	return (void*) (((uintptr_t) addr) & (~(PAGE_SIZE - 1)));
}

// returns bitmask for highest capacity nodes(s)
struct bitmask *get_numa_mask_for_highest_capacity_node() {
  long long best = 0;
  long long free_best = 0;
  int node;
  int best_node;
  struct bitmask* numa_nodes = numa_allocate_nodemask();

  if (numa_nodes == NULL) {
      fprintf(stderr, "numa_bitmask_alloc() failed.");
      return NULL;
  }

  for (node = 0; node <= numa_nodes->size; ++node) {
      long long freep = 0;
      long long current = numa_node_size64(node, &freep);

      if (current == -1) {
          continue;
      }

      if (current > best) {
          best = current;
          free_best = freep;
          best_node = node;
          numa_bitmask_clearall(numa_nodes);
      }

      if (current == best) {
          numa_bitmask_setbit(numa_nodes, node);
      }
  }

  if (numa_bitmask_weight(numa_nodes) == 0) {
      numa_free_nodemask(numa_nodes);
      return NULL;
  }

  printf("biggest node has id: %d, capacity of: %llu B and has : %llu B free memory.\n", best_node, best, free_best);
  return numa_nodes;
}

// returns the node where page starting at 'ptr' resides
int get_numa_node_by_ptr(void *ptr)
{
    ptr = align_to_page(ptr);

    const int pid = 0;
    const unsigned long count = 1;
    int status[1];
    void* pages[1] = {ptr};
    const int *nodes = NULL;
    const int flags = MPOL_MF_MOVE;
    
    long ret = move_pages(pid, count, pages, nodes, status, flags);
    if (ret) {
        perror("move_pages");
        abort();
    }

    if (status[0] < 0) {
        printf("move_pages failed with err: %s\n", strerror(-status[0]));
        abort();
    }

    return status[0];
}
