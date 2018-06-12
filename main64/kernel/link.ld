ENTRY(k_main)

SECTIONS
{
    . = 0xFFFF800000100000;
    .text : AT(ADDR(.text) - 0xFFFF800000000000)
    {
        *(.text .text.*)
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
}