/* GPLv2 (c) Airbus */
#include <debug.h>
#include <info.h>

extern info_t   *info;
extern uint32_t __kernel_start__;
extern uint32_t __kernel_end__;

void tp() {
   debug("kernel mem [0x%p - 0x%p]\n", &__kernel_start__, &__kernel_end__);
   debug("MBI flags 0x%x\n", info->mbi->flags);

   multiboot_memory_map_t* entry = (multiboot_memory_map_t*)info->mbi->mmap_addr;
   while((uint32_t)entry < (info->mbi->mmap_addr + info->mbi->mmap_length)) {
      // TODO print "[start - end] type" for each entry
			debug("entry %d [start %x - end %x]\n", entry->type, (unsigned int) entry->addr, (unsigned int) (entry->addr + entry->len));
      entry++;
   }


   // lisant/écrivant dans une zone de mémoire libre

	int *ptr_in_available_mem;
	ptr_in_available_mem = (int*)0x0;
	debug("Available mem (0x0): before: 0x%x ", *ptr_in_available_mem); // read
	*ptr_in_available_mem = 0xaaaaaaaa;                           // write
	debug("after: 0x%x\n", *ptr_in_available_mem);                // check

   // lisant/écrivant dans une zone de mémoire réservée

	int *ptr_in_reserved_mem;
	ptr_in_reserved_mem = (int*)0xf0000;
	debug("Reserved mem (at: 0xf0000):  before: 0x%x ", *ptr_in_reserved_mem); // read
	*ptr_in_reserved_mem = 0xaaaaaaaa;                           // write
	debug("after: 0x%x\n", *ptr_in_reserved_mem);                // check

   // lisant/écrivant en dehors d'une zone de mémoire
   int *ptr_out_of_mem;
   ptr_out_of_mem = (int*)0xffffffffff;
   debug("Out of mem (at: 0xffffffffff):  before: 0x%x ", *ptr_out_of_mem); // read
   *ptr_out_of_mem = 0xff;
   debug("after: 0x%x\n", *ptr_out_of_mem);                // check


/*
   
      multiboot_memory_map_t* last_entry = entry;

   debug("Avant lire à une adresse en dehors de la mémoire physique disponible : %lld\n",  (last_entry->addr+last_entry->len + 10) );
   debug("Après lire à une adresse en dehors de la mémoire physique disponible\n");
   
   // long long unsigned int * p = (long long unsigned int *) (last_entry->addr+last_entry->len + 10);
   // long long unsigned int * p;
   // p = (last_entry->addr+last_entry->len + 10);
   // *p = 1;
   

//   printf("écrire à une adresse en dehors de la mémoire physique disponible:\n");
//   scanf(last_entry->addr+last_entry->size*last_entry->len);

*/
}


/*
0x2000
*/