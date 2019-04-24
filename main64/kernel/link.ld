ENTRY(k_main)

SECTIONS
{
    . = 0xFFFF800000110000;
    .text : AT(ADDR(.text) - 0xFFFF800000000000)
    {
        *(.text .text.*)
        *(.rodata .rodata.*)
        . = ALIGN(4K);
    }

    .data : AT(ADDR(.data) - 0xFFFF800000000000)
    {
        *(.data .data.*)
    }

    .bss : AT(ADDR(.bss) - 0xFFFF800000000000)
    {
        *(.bss .bss.*)
    }

    .eh_frame : AT(ADDR(.eh_frame) - 0xFFFF800000000000)
    {
        *(.eh_frame .eh_frame.*)
    }
}