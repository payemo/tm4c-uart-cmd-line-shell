ENTRY(Reset_Handler)

MEMORY
{
	FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 256K
	SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 32K
}

_estack = ORIGIN(SRAM) + LENGTH(SRAM);

SECTIONS
{
	.isr_vector :
	{
		KEEP(*(.isr_vector))
	} > FLASH

	.text :
	{
		*(.text*)
		*(.rodata*)
	} > FLASH

	.data :
	{
		_sdata = .;
		*(.data*)
		_edata = .;
	} > SRAM AT > FLASH

	_sidata = LOADADDR(.data);

	.bss :
	{
		_sbss = .;
		*(.bss*)
		*(COMMON)
		_ebss = .;
	} > SRAM
}
