#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <numa.h>

#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

void print_csizes(void);
int cache_sizes(uint32_t*, int);

int main(void)
{
    if(numa_available() == -1) {
        puts("No NUMA support available.");
        print_csizes();
        return 0;
    }

    // We have NUMA here
    int max_node = numa_max_node();
    for(int i = 0; i <= max_node; i++) {
        printf("Running on NUMA node #%d...\n", i);
        numa_run_on_node(i);
        print_csizes();
        printf("\n");
    }

    return 0;
}

void print_csizes(void) {
    uint32_t cache_sz[4] = { 0 };
    int n = cache_sizes(cache_sz, NELEMS(cache_sz));

    for(int i = 0; i < n; i++) {
        printf("Cache level %u, size %u\n", i+1, cache_sz[i]);
    }
}

int cache_sizes(uint32_t *arr, int sz)
{
    int args[4] = { _SC_LEVEL1_DCACHE_SIZE,
                    _SC_LEVEL2_CACHE_SIZE,
                    _SC_LEVEL3_CACHE_SIZE,
                    _SC_LEVEL4_CACHE_SIZE
    };

    int i = 0;
    for(i = 0; i < NELEMS(args) && i < sz; i++) {
        long sz = sysconf(args[i]);
        if(sz == 0)
            break;
        arr[i] = sz;
    }
    return i;
}
