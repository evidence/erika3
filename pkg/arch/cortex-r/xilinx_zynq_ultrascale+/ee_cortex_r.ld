/* Specify the default entry point to the program */
ENTRY(_boot)

MEMORY
{
  SRAM (rwx) : ORIGIN = 0xffff0100, LENGTH = 0x8000
}

SECTIONS
{
  .vectors 0x0 : {
    KEEP(*(.vectors))
  }

  .text : {
    *(.boot)
    *(.text)
    *(.text.*)
    *(.gnu.linkonce.t.*)
    *(.plt)
    *(.gnu_warning)
    *(.gcc_execpt_table)
    *(.glue_7)
    *(.glue_7t)
    *(.vfp11_veneer)
    *(.ARM.extab)
    *(.gnu.linkonce.armextab.*)
  } > SRAM

  .init : {
    KEEP (*(.init))
  } > SRAM

  .fini : {
    KEEP (*(.fini))
  } > SRAM

  .interp : {
    KEEP (*(.interp))
  } > SRAM

  .note-ABI-tag : {
    KEEP (*(.note-ABI-tag))
  } > SRAM

  .ctors : {
    __CTOR_LIST__ = .;
    ___CTORS_LIST___ = .;
    KEEP (*crtbegin.o(.ctors))
    KEEP (*(EXCLUDE_FILE(*crtend.o) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
    __CTOR_END__ = .;
    ___CTORS_END___ = .;
  } > SRAM

  .dtors : {
    __DTOR_LIST__ = .;
    ___DTORS_LIST___ = .;
    KEEP (*crtbegin.o(.dtors))
    KEEP (*(EXCLUDE_FILE(*crtend.o) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
    __DTOR_END__ = .;
    ___DTORS_END___ = .;
  } > SRAM

  .fixup : {
    *(.fixup)
  } > SRAM

  .eh_frame : {
    *(.eh_frame)
  } > SRAM

  .eh_framehdr : {
    *(.eh_framehdr)
  } > SRAM

  .gcc_except_table : {
    *(.gcc_except_table)
  } > SRAM

  .rodata : ALIGN(4) {
    *(.rodata)
    *(.rodata.*)
    *(.gnu.linkonce.r.*)
  } > SRAM

  .rodata1 : ALIGN(4) {
    *(.rodata1)
    *(.rodata1.*)
  } > SRAM

  .sdata2 : ALIGN(4) {
   *(.sdata2)
   *(.sdata2.*)
   *(.gnu.linkonce.s2.*)
  } > SRAM

  .sbss2 : {
    *(.sbss2)
    *(.sbss2.*)
    *(.gnu.linkonce.sb2.*)
  } > SRAM

  .data : ALIGN(4) {
    *(.data)
    *(.data.*)
    *(.gnu.linkonce.d.*)
    *(.jcr)
    *(.got)
    *(.got.plt)
  } > SRAM

  .data1 : ALIGN(4) {
    *(.data1)
    *(.data1.*)
  } > SRAM

  .got : {
    *(.got)
  } > SRAM

  .mmu_tbl (ALIGN(16384)) : {
   *(.mmu_tbl)
  } > SRAM

  .ARM.exidx : {
    *(.ARM.exidx*)
    *(.gnu.linkonce.armexidix.*.*)
  } > SRAM

  .preinit_array : {
    KEEP (*(SORT(.preinit_array.*)))
    KEEP (*(.preinit_array))
  } > SRAM

  .init_array : {
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array))
  } > SRAM

  .fini_array : {
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array))
  } > SRAM

  .ARM.attributes : {
    *(.ARM.attributes)
  } > SRAM

  .sdata : ALIGN(4) {
    osEE_sdata_start = .;
    *(.sdata)
    *(.sdata.*)
    *(.gnu.linkonce.s.*)
    osEE_sdata_end = .;
  } > SRAM

  .sbss (NOLOAD) : ALIGN(4) {
    osEE_sbss_start = .;
    *(.sbss)
    *(.sbss.*)
    *(.gnu.linkonce.sb.*)
    osEE_sbss_end = .;
  } > SRAM

  .tdata : ALIGN(4) {
    *(.tdata)
    *(.tdata.*)
    *(.gnu.linkonce.td.*)
  } > SRAM

  .tbss : ALIGN(4) {
    *(.tbss)
    *(.tbss.*)
    *(.gnu.linkonce.tb.*)
  } > SRAM

  .bss (NOLOAD) : ALIGN(4) {
    osEE_bss_start = .;
    *(.bss)
    *(.bss.*)
    *(.gnu.linkonce.b.*)
    *(COMMON)
    osEE_bss_end = .;
  } > SRAM

  _SDA_BASE_ =
    ADDR(.sdata) + ((ADDR(.sbss) + SIZEOF(.sbss) - ADDR(.sdata)) / 2);

  _SDA2_BASE_ =
    ADDR(.sdata2) + ((ADDR(.sbss2) + SIZEOF(.sbss2) - ADDR(.sdata2)) / 2 );

  /* Allocate Stack and Heap definitions */

  .heap (NOLOAD) : ALIGN(16) {
    *(.heap)
  } > SRAM

  .stack (NOLOAD) : ALIGN(16) {
    *(.stack)
  } > SRAM
}
