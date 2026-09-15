#include "src.hpp"
#include <iostream>

#define BITS_PER_BYTE 8

// Return the virtual page number associated with the given virtual address
void split_virtual_address(int virtual_address, int page_size, int* VPN, int* offset)
{
  int n = sizeof(int) * BITS_PER_BYTE; // 4 * 8 = 32 = n

  // get exponent representing number of bits in offset
  short p = -1;
  while (page_size > 0) { // assuming page size given is always positive
    page_size = page_size >> 1; // right shift
    p++;			// increment
  } // end loop

    
  // 0 -> p - 1 is the offset, and p -> n - 1 is the vpn
  int mask = 0xFFFFFFFF;
  mask = mask << p; // shift p times to get mask for VPN

  (*VPN) = (virtual_address & mask) >> p; // grab the VPN with mask
    
  (*offset) = virtual_address & (~mask); // grab the VPO with ~mask, shift right to adjust

}



// Split VPN into index and tag
// Assuming k-way associative TLB
void split_VPN(int VPN, int k, int* index, int* tag)
{
  short t = -1;
  while (k > 0) { // assuming page size given is always positive
    k = k >> 1; // right shift
    t++;                        // increment
  } // end loop


  int mask = 0xFFFFFFFF; // use our handy mask
  mask = mask << t; // shift over k bits
  //std::cout << mask << std::endl;

  (*tag) = (VPN & mask) >> t; // grab the tag and adjust
  (*index) = VPN & (~mask); // grab the index

}





// Find PFN from TLB (if it exists and is accessible)
int TLB_lookup(TLB* tlb, int VPN)
{

  int *idx = (int *)malloc(sizeof(int));
  int *tag = (int *)malloc(sizeof(int));
  
  split_VPN(VPN, tlb->k, idx, tag); // split the vpn
  
  PTE* entry = (PTE*)malloc(sizeof(PTE)); // create space for PTE return
  
  bool tlb_hit = tlb->lookup((*idx), (*tag), &entry); // lookup the pte
  
  if (tlb_hit) {
   
    // check the bits returned and and assert access
    if (entry->valid_bit && (!entry->protect_bit) && entry->present_bit) {

      return entry->PFN;
    
    }
    
    // not accessible, throw protection fault
    protection_fault(); 

  } else {
    
    // tlb miss! throw miss exception
    tlb_miss(); 

  }

  return 0; // purely to hush warnings
}





// Find PFN in PageTable (if it exists and is accessible)
int table_lookup(PageTable* table, TLB* tlb, int VPN)
{

  PTE* entry = (PTE*)malloc(sizeof(PTE)); // create space for PTE return

  table->lookup(VPN, &entry); // look up pte associated with VPN

  if (!entry->valid_bit) { // if not valid
    segmentation_fault(); // throw a seg fault
  }

  if (entry->protect_bit) { // if protected access
    protection_fault(); // throw a protection fault
  }

  if (!entry->present_bit) { // if page not present
    page_fault(); // throw a page fault
  }

  // holders for index and tage for tlb add_entry
  int *idx = (int *)malloc(sizeof(int));
  int *tag = (int *)malloc(sizeof(int));

  split_VPN(VPN, tlb->k, idx, tag); // split the vpn


  tlb->add_entry(*idx, *tag, entry); // add this entry to the tlb
  
  return entry->PFN; // return page frame number
}





// Convert PFN and Offset to Physical Address
int get_physical_address(int PFN, int offset, int page_size)
{
  
 // get exponent representing number of bits in offset
  short p = -1;
  while (page_size > 0) { // assuming page size given is always positive
    page_size = page_size >> 1; // right shift
    p++;                        // increment
  } // end loop

  int phys_addr = PFN << p; // right shift the page frame number.
  phys_addr += offset;	    // add in the offset.
  return phys_addr;

}





// Put everything together to get physical address from virtual
int virtual_to_physical(int virtual_address, int page_size, TLB* tlb, PageTable* table)
{

  // split the virtual address
  int *VPN = (int *)malloc(sizeof(int));
  int *offset = (int *)malloc(sizeof(int));
  split_virtual_address(virtual_address, page_size, VPN, offset);

  // then, split the vpn for tlb
  int *idx = (int *)malloc(sizeof(int));
  int *tag = (int *)malloc(sizeof(int));
  split_VPN((*VPN), tlb->k, idx, tag);

  try { 
    // lookup in the tlb (this may throw a miss!)
    int PFN = TLB_lookup(tlb, (*VPN));
    
    // finally, build the physical address
    return get_physical_address(PFN, (*offset), page_size);

  } catch (const char* msg) {
    if (strcmp(msg, TLB_MISS) == 0) {
    // tlb miss! look for it in the page table instead!
    int PFN = table_lookup(table, tlb, (*VPN));

    // finally, build the physical address
    return get_physical_address(PFN, (*offset), page_size);

    } else {
      throw; // throw anything else up the line.
    }
  } catch(...) {
    // continue to throw all other exceptions
    throw;
  }

  return 0; // for avoiding warnings

}

