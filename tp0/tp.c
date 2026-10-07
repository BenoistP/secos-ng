/* GPLv2 (c) Airbus */
#include <debug.h>
#include <info.h>
#include <stdio.h>

extern info_t   *info;
extern uint32_t __kernel_start__;
extern uint32_t __kernel_end__;

void tp() {
   debug("kernel mem [0x%p - 0x%p]\n", &__kernel_start__, &__kernel_end__);
   debug("MBI flags 0x%x\n", info->mbi->flags);

   multiboot_memory_map_t* entry = (multiboot_memory_map_t*)info->mbi->mmap_addr;
   while((uint32_t)entry < (info->mbi->mmap_addr + info->mbi->mmap_length)) {
      // TODO print "[start - end] type" for each entry
      // printf("entry %d [start %lld - end %lld]\n", entry->type, entry->addr, entry->addr+entry->len*entry->size);



      entry++;
   }

   multiboot_memory_map_t* last_entry = entry;

   printf("lire à une adresse en dehors de la mémoire physique disponible %d\n", last_entry->addr+last_entry->size*last_entry->len );

   printf("écrire à une adresse en dehors de la mémoire physique disponible:\n");
   scanf(last_entry->addr+last_entry->size*last_entry->len);

}
