ENTRY("_startc");
OUTPUT_FORMAT("binary")
SECTIONS
{
    . = 0x7E00;

    .text . : 
    {
        *(.text);
    }

    .data . :
    {
        *(.bss);
        *(.bss*);
        *(.data);
        *(.rodata*);
        *(COMMON);
    }

    /DISCARD/ :
    {
        *(.note*);
        *(.iplt*);
        *(.igot*);
        *(.rel*);
        *(.comment);
    }
}
