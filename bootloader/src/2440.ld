
OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)

MEMORY
{
    ROM (rx)  : ORIGIN = 0x00000000, LENGTH = 4k
    RAM (rwx) : ORIGIN = 0x30000000, LENGTH = 64M
}

SECTIONS
{
    .reset :
    {
        __reset_start = . ;
        *startup.o (.text)
        . = ALIGN(4);
     } >ROM

    .text :
    {
        __text_start = . ;
        *(.text*)
        . = ALIGN(4);
        *(.rodata*)
        __text_end = . ;
    } >ROM

    .data :
    {
        __data_start = . ;
        *(.data*)
        . = ALIGN(4);
        __data_end = . ;
    } >RAM /*AT>ROM*/

    .bss :
    {
        __bss_start = . ;
        *(.bss*)
        . = ALIGN(8);
        __bss_end = . ;
    } >RAM

    _end = . ;
    __end = . ;
    PROVIDE(end = .) ;
}
