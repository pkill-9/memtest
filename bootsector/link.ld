ENTRY("_start");
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

    .signature 0x7DFE :
    {
        SHORT(0xAA55);
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
