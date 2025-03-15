#include "mmu.h"
#include "pagesim.h"
#include "swapops.h"
#include "stats.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

/**
 * --------------------------------- PROBLEM 6 --------------------------------------
 * Checkout PDF section 7 for this problem
 *
 * Page fault handler.
 *
 * When the CPU encounters an invalid address mapping in a page table, it invokes the
 * OS via this handler. Your job is to put a mapping in place so that the translation
 * can succeed.
 *
 * @param addr virtual address in the page that needs to be mapped into main memory.
 *
 * HINTS:
 *      - You will need to use the global variable current_process when
 *      altering the frame table entry.
 *      - Use swap_exists() and swap_read() to update the data in the
 *      frame as it is mapped in.
 * ----------------------------------------------------------------------------------
 */
void page_fault(vaddr_t address)
{
    // TODO: Get a new frame, then correctly update the page table and frame table
    vpn_t vpn = get_vaddr_vpn(address);
    pte_t *pte = get_page_table_entry(vpn, PTBR, mem);
    pfn_t new_frame = free_frame();

    if (swap_exists(pte))
    {
        swap_read(pte, new_frame);
    }
    else
    {
        memset(mem + (new_frame * PAGE_SIZE), 0, PAGE_SIZE);
    }

    pte->valid = 1;
    pte->pfn = new_frame;

    frame_table[new_frame].mapped = 1;
    frame_table[new_frame].process = current_process;
    frame_table[new_frame].vpn = vpn;
    frame_table[new_frame].ref_count = 1;
}

#pragma GCC diagnostic pop
