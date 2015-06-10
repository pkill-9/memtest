ENTRY("_startc");
OUTPUT_FORMAT("binary")
SECTIONS
{
    . = 0x7C00;

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
        NUMSECTORS = 0x7DFD;
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
