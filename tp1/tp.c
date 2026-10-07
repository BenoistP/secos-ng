/* GPLv2 (c) Airbus */
#include <debug.h>
#include <segmem.h>

void userland() {
   asm volatile ("mov %eax, %cr0");
}

void print_gdt_content(gdt_reg_t gdtr_ptr) {
    seg_desc_t* gdt_ptr;
    gdt_ptr = (seg_desc_t*)(gdtr_ptr.addr);
    int i=0;
    while ((uint32_t)gdt_ptr < ((gdtr_ptr.addr) + gdtr_ptr.limit)) {
        uint32_t start = gdt_ptr->base_3<<24 | gdt_ptr->base_2<<16 | gdt_ptr->base_1;
        uint32_t end;
        if (gdt_ptr->g) {
            end = start + ( (gdt_ptr->limit_2<<16 | gdt_ptr->limit_1) <<12) + 4095;
        } else {
            end = start + (gdt_ptr->limit_2<<16 | gdt_ptr->limit_1);
        }
        debug("%d ", i);
        debug("[0x%x ", start);
        debug("- 0x%x] ", end);
        debug("seg_t: 0x%x ", gdt_ptr->type);
        debug("desc_t: %d ", gdt_ptr->s);
        debug("priv: %d ", gdt_ptr->dpl);
        debug("present: %d ", gdt_ptr->p);
        debug("avl: %d ", gdt_ptr->avl);
        debug("longmode: %d ", gdt_ptr->l);
        debug("default: %d ", gdt_ptr->d);
        debug("gran: %d ", gdt_ptr->g);
        debug("\n");
        gdt_ptr++;
        i++;
    }
}


void tp() {
    
  gdt_reg_t gdt;
  get_gdtr(gdt);
  print_gdt_content( gdt );

  debug("================================\n");


  /*
    Q3 : Lire les valeurs des sélecteurs de segment à l'aide des macros prévues à cet effet dans kernel/include/segmem.h, et en déduire quels descripteurs de cette GDT sont en cours d'utilisation pour :

    Le segment de code (sélecteur cs)
    Le segment de données (sélecteur ds)
    Le segment de pile (sélecteur ss)
    D'autres segments (sélecteurs autres : es, fs, gs, etc.)
*/

  uint16_t dseg = get_ds();
  debug("dseg = %x\n", dseg>>3);
  debug("----------------------\n");

  uint16_t cseg = get_seg_sel(cs);
  debug("cseg = %x\n", cseg>>3);
  debug("----------------------\n");

  uint16_t sseg = get_ss();
  debug("sseg = %x\n", sseg>>3);
  debug("----------------------\n");

  uint16_t eseg = get_es();
  debug("eseg = %x\n", eseg>>3);
  debug("----------------------\n");

  uint16_t fseg = get_fs();
  debug("fseg = %x\n", fseg>>3);

  debug("================================\n");


  // 05

  seg_desc_t my_gdt[7];
  my_gdt[0].raw = 0ULL;
  




}
