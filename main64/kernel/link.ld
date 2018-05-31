ENTRY(k_main)

SECTIONS
{
    . = 0x100000;
    .text :
    {
        *(.text .text.*)
        . = ALIGN(4K);
    }

    .data :
    {
        *(.data)
    }
    .bss :
    {
        *(.bss)
    }
}