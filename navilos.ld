ENTRY(vector_start)
SECTIONS
{
    . = 0x0;

    .text :
    {
        *(vector_start)
        *(.text .rodata)
    }
    .data :
    {
        *(.data)
    }
    .bss :
    {
        __bss_start__ = .;
        *(.bss)
        __bss_end__ = .;
    }
}
