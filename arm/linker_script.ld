/* linker_script.ld - LPC2129 memory layout */
ENTRY(_start)

MEMORY
{
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 128K
    RAM   (rwx) : ORIGIN = 0x00004000, LENGTH = 16K
}

SECTIONS
{
    .text : {
        KEEP(*(.vectors))
        *(.text*)
        *(.rodata*)
    } > FLASH

    .data : {
        *(.data*)
    } > RAM AT> FLASH

    .bss : {
        *(.bss*)
        *(COMMON)
    } > RAM
}

