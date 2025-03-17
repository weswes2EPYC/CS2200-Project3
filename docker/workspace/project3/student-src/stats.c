#include "stats.h"

/* The stats. See the definition in stats.h. */
stats_t stats;

/**
 * --------------------------------- PROBLEM 10 --------------------------------------
 * Checkout PDF section 10 for this problem
 * 
 * Calulate the total average time it takes for an access
 * 
 * HINTS:
 * 		- You may find the #defines in the stats.h file useful.
 * 		- You will need to include code to increment many of these stats in
 * 		the functions you have written for other parts of the project.
 * -----------------------------------------------------------------------------------
 */
void compute_stats() {
    if (stats.accesses == 0) {
        stats.amat = 0;
        return;
    }

    double miss_rate = (double)stats.page_faults / stats.accesses;
    double miss_penalty = DISK_PAGE_READ_TIME + ((stats.page_faults > 0) ? ((double)stats.writebacks / stats.page_faults) * DISK_PAGE_WRITE_TIME : 0);
    stats.amat = MEMORY_ACCESS_TIME + (miss_rate * miss_penalty);
}
