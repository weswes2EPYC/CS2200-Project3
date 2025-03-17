#pragma once

#include "mmu.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

/**
 * --------------------------------- PROBLEM 1 --------------------------------------
 * Checkout PDF Section 3 For this Problem
 *
 * Split the virtual address into its virtual page number and offset.
 *
 * HINT:
 *      -Examine the global defines in pagesim.h, which will be necessary in
 *      implementing these functions.
 * ----------------------------------------------------------------------------------
 */

static inline vpn_t get_vaddr_vpn(vaddr_t addr)
{
    return (vpn_t)(addr >> OFFSET_LEN);
}

static inline uint16_t get_vaddr_offset(vaddr_t addr)
{
    return (uint16_t)(addr & (PAGE_SIZE - 1));
}

static inline pte_t *get_page_table(pfn_t ptbr, uint8_t *memory)
{
    return (pte_t *)(memory + (ptbr * PAGE_SIZE));
}

static inline pte_t *get_page_table_entry(vpn_t vpn, pfn_t ptbr, uint8_t *memory)
{
    return (pte_t *)(get_page_table(ptbr, memory) + vpn);
}

static inline paddr_t get_physical_address(pfn_t pfn, uint16_t offset)
{
    return (paddr_t)((pfn * PAGE_SIZE) + offset);
}

#pragma GCC diagnostic pop
