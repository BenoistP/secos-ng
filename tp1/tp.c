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

  // return; // code after return will not be executed

  // 04

  /*
    ================================
    dseg = 2
    ----------------------
    cseg = 10x600000
    ----------------------
    sseg = 2
    ----------------------
    eseg = 2
    ----------------------
    fseg = 2
    ================================

    les segments sont les mêmes

  */


  // 05

   seg_desc_t my_gdt[7];
    my_gdt[0].raw = 0ULL; // raw non reconnu par vscode

    my_gdt[1].limit_1 = 0xffff;   //:16;     /* bits 00-15 of the segment limit */
    my_gdt[1].base_1 = 0x0000;    //:16;     /* bits 00-15 of the base address */
    my_gdt[1].base_2 = 0x00;      //:8;      /* bits 16-23 of the base address */
    my_gdt[1].type = 11;//Code,RX //:4;      /* segment type */
    my_gdt[1].s = 1;              //:1;      /* descriptor type */
    my_gdt[1].dpl = 0; //ring0    //:2;      /* descriptor privilege level */
    my_gdt[1].p = 1;              //:1;      /* segment present flag */
    my_gdt[1].limit_2 = 0xf;      //:4;      /* bits 16-19 of the segment limit */
    my_gdt[1].avl = 1;            //:1;      /* available for fun and profit */
    my_gdt[1].l = 0; //32bits     //:1;      /* longmode */
    my_gdt[1].d = 1;              //:1;      /* default length, depend on seg type */
    my_gdt[1].g = 1;              //:1;      /* granularity */
    my_gdt[1].base_3 = 0x00;      //:8;      /* bits 24-31 of the base address */
                                                                  //
    my_gdt[2].limit_1 = 0xffff;   //:16;     /* bits 00-15 of the segment limit */
    my_gdt[2].base_1 = 0x0000;    //:16;     /* bits 00-15 of the base address */
    my_gdt[2].base_2 = 0x00;      //:8;      /* bits 16-23 of the base address */
    my_gdt[2].type = 3; //data,RW //:4;      /* segment type */
    my_gdt[2].s = 1;              //:1;      /* descriptor type */
    my_gdt[2].dpl = 0; //ring0    //:2;      /* descriptor privilege level */
    my_gdt[2].p = 1;              //:1;      /* segment present flag */
    my_gdt[2].limit_2 = 0xf;      //:4;      /* bits 16-19 of the segment limit */
    my_gdt[2].avl = 1;            //:1;      /* available for fun and profit */
    my_gdt[2].l = 0; // 32 bits   //:1;      /* longmode */
    my_gdt[2].d = 1;              //:1;      /* default length, depend on seg type */
    my_gdt[2].g = 1;              //:1;      /* granularity */
    my_gdt[2].base_3 = 0x00;      //:8;      /* bits 24-31 of the base address */


  return; // code after return will not be executed

  // ...


  // 6
  gdt_reg_t my_gdtr;
  my_gdtr.addr = (long unsigned int)my_gdt;
  my_gdtr.limit = sizeof(my_gdt);
  // my_gdtr.desc = gdt_desc;
  set_gdtr(my_gdtr);

  // 7 ?

  get_gdtr(my_gdtr);
  debug("GDT addr: 0x%x\n", (unsigned int) my_gdtr.addr);
  debug("GDT limit: %d\n", (unsigned int) my_gdtr.limit);
  print_gdt_content(my_gdtr);

  // 8 


  // 9
    my_gdt[3].limit_1 = 0x20;   //:16;     /* bits 00-15 of the segment limit */

    // my_gdt[3].base_1 = 0x600000;    //:16;     /* bits 00-15 of the base address */
    // my_gdt[3].base_2 = 0x00;      //:8;      /* bits 16-23 of the base address */
    // my_gdt[3].type = 3; //data,RW //:4;      /* segment type */
    // my_gdt[3].s = 1;              //:1;      /* descriptor type */
    // my_gdt[3].dpl = 0; //ring0    //:2;      /* descriptor privilege level */
    // my_gdt[3].p = 1;              //:1;      /* segment present flag */
    // my_gdt[3].limit_2 = 0xf;      //:4;      /* bits 16-19 of the segment limit */
    // my_gdt[3].avl = 1;            //:1;      /* available for fun and profit */
    // my_gdt[3].l = 0; // 32 bits   //:1;      /* longmode */
    // my_gdt[3].d = 1;              //:1;      /* default length, depend on seg type */
    // my_gdt[3].g = 1;              //:1;      /* granularity */
    // my_gdt[3].base_3 = 0x00;      //:8;      /* bits 24-31 of the base address */


    // 10



}
