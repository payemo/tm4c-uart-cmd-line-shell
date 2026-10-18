
MEMORY
{
	FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 256K
	SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 32K
}

_estack = ORIGIN(SRAM) + LENGTH(SRAM);

/* SECTIONS */
/* { */
/* 	.text : */
/* 	{ */
/* 		_text = . */
/* 		KEEP(*(.isr_vector)) */
/* 		*(.text*) */
/* 		*(.rodata*) */
/* 		_etext = . */
/* 	} > FLASH */

/* 	.data : */
/* 	{ */
/* 		_data = . */
/* 		*(.data*) */
/* 		.edata = . */
/* 	} > SRAM AT > FLASH */

/* 	.bss : */
/* 	{ */
/* 		_bss = . */
/* 		*(.*bss) */
/* 		*(COMMON) */
/* 		_ebss = . */
/* 	} > SRAM */
/* } */
		

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
