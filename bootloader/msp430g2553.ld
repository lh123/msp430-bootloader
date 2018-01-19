
OUTPUT_ARCH(msp430)
ENTRY(_start)

_stack_size = 80 * 2;

MEMORY {
	SFR				: ORIGIN = 0x0000, LENGTH = 0x0010 /* END=0x0010, size 16 */
	MODE_FLAG		: ORIGIN = 0x0200, LENGTH = 0x0002 /* END=0x021D, size 2 */
	RAM				: ORIGIN = 0x0202, LENGTH = 0x01FE /* END=0x03FF, size 482 */
	INFOMEM			: ORIGIN = 0x1000, LENGTH = 0x0100 /* END=0x10FF, size 256 as 4 64-byte segments */
	INFOA			: ORIGIN = 0x10C0, LENGTH = 0x0040 /* END=0x10FF, size 64 */
	INFOB			: ORIGIN = 0x1080, LENGTH = 0x0040 /* END=0x10BF, size 64 */
	INFOC			: ORIGIN = 0x1040, LENGTH = 0x0040 /* END=0x107F, size 64 */
	INFOD			: ORIGIN = 0x1000, LENGTH = 0x0040 /* END=0x103F, size 64 */
	ROM (rx)		: ORIGIN = 0xC000, LENGTH = 0x0A00 /* END=0xC3FF, size 1024 */
	APP_ROM (rx)	: ORIGIN = 0xCA20, LENGTH = 0x33E0 /* END=0xFDFF, size 13792 */
	BSLSIGNATURE	: ORIGIN = 0xFFDE, LENGTH = 0x0002
	VECT1			: ORIGIN = 0xFFE0, LENGTH = 0x0002
	VECT2			: ORIGIN = 0xFFE2, LENGTH = 0x0002
	VECT3			: ORIGIN = 0xFFE4, LENGTH = 0x0002
	VECT4			: ORIGIN = 0xFFE6, LENGTH = 0x0002
	VECT5			: ORIGIN = 0xFFE8, LENGTH = 0x0002
	VECT6			: ORIGIN = 0xFFEA, LENGTH = 0x0002
	VECT7			: ORIGIN = 0xFFEC, LENGTH = 0x0002
	VECT8			: ORIGIN = 0xFFEE, LENGTH = 0x0002
	VECT9			: ORIGIN = 0xFFF0, LENGTH = 0x0002
	VECT10			: ORIGIN = 0xFFF2, LENGTH = 0x0002
	VECT11			: ORIGIN = 0xFFF4, LENGTH = 0x0002
	VECT12			: ORIGIN = 0xFFF6, LENGTH = 0x0002
	VECT13			: ORIGIN = 0xFFF8, LENGTH = 0x0002
	VECT14			: ORIGIN = 0xFFFA, LENGTH = 0x0002
	VECT15			: ORIGIN = 0xFFFC, LENGTH = 0x0002
	RESET			: ORIGIN = 0xFFFE, LENGTH = 0x0002

	APP_VECT1		: ORIGIN = 0xCA00, LENGTH = 0x0002
	APP_VECT2		: ORIGIN = 0xCA02, LENGTH = 0x0002
	APP_VECT3		: ORIGIN = 0xCA04, LENGTH = 0x0002
	APP_VECT4		: ORIGIN = 0xCA06, LENGTH = 0x0002
	APP_VECT5		: ORIGIN = 0xCA08, LENGTH = 0x0002
	APP_VECT6		: ORIGIN = 0xCA0A, LENGTH = 0x0002
	APP_VECT7		: ORIGIN = 0xCA0C, LENGTH = 0x0002
	APP_VECT8		: ORIGIN = 0xCA0E, LENGTH = 0x0002
	APP_VECT9		: ORIGIN = 0xCA10, LENGTH = 0x0002
	APP_VECT10		: ORIGIN = 0xCA12, LENGTH = 0x0002
	APP_VECT11		: ORIGIN = 0xCA14, LENGTH = 0x0002
	APP_VECT12		: ORIGIN = 0xCA16, LENGTH = 0x0002
	APP_VECT13		: ORIGIN = 0xCA18, LENGTH = 0x0002
	APP_VECT14		: ORIGIN = 0xCA1A, LENGTH = 0x0002
	APP_VECT15		: ORIGIN = 0xCA1C, LENGTH = 0x0002
	APP_RESET		: ORIGIN = 0xCA1E, LENGTH = 0x0002
}

SECTIONS
{
	.bslsignature	: {} > BSLSIGNATURE

    TRAPINT			: { KEEP(*(.int01)) KEEP(*(__interrupt_vector_1)) } >VECT1
    .int01			: {}               >VECT2
    PORT1			: { KEEP(*(.int03)) KEEP(*(__interrupt_vector_3)) } >VECT3
    PORT2			: { KEEP(*(.int04)) KEEP(*(__interrupt_vector_4)) } >VECT4
    .int04			: {}               >VECT5
    ADC10			: { KEEP(*(.int06)) KEEP(*(__interrupt_vector_6)) } >VECT6
    USCIAB0TX		: { KEEP(*(.int07)) KEEP(*(__interrupt_vector_7)) } >VECT7
    USCIAB0RX		: { KEEP(*(.int08)) KEEP(*(__interrupt_vector_8)) } >VECT8
    TIMER0_A1		: { KEEP(*(.int09)) KEEP(*(__interrupt_vector_9)) } >VECT9
	TIMER0_A0		: { KEEP(*(.int10)) KEEP(*(__interrupt_vector_10)) } >VECT10
    WDT				: { KEEP(*(.int11)) KEEP(*(__interrupt_vector_11)) } >VECT11
    COMPARATORA		: { KEEP(*(.int12)) KEEP(*(__interrupt_vector_12)) } >VECT12
    TIMER1_A1		: { KEEP(*(.int13)) KEEP(*(__interrupt_vector_13)) } >VECT13
    TIMER1_A0		: { KEEP(*(.int14)) KEEP(*(__interrupt_vector_14)) } >VECT14
    NMI				: { KEEP(*(.int15)) KEEP(*(__interrupt_vector_15)) } >VECT15
	.reset			: { KEEP(*(.reset)) } >RESET

	.rodata :
	{
		. = ALIGN(2);
		*(.rodata)
	} >ROM

	.text :
	{
		. = ALIGN(2);
		*(.text)
	} >ROM

	.mode_flag :
	{
		*(.app_vect)
	} >MODE_FLAG

	.data :
	{
		PROVIDE(_sdata = .);
		. = ALIGN(2);
		*(.data)
		. = ALIGN(2);
		PROVIDE(_edata = .);
	} >RAM AT>ROM
	PROVIDE(_rom_data_start = LOADADDR(.data));
	PROVIDE(_rom_data_end = _rom_data_start + SIZEOF(.data));

	.bss :
	{
		. = ALIGN(2);
		PROVIDE(_sbss = .);
		*(.bss)
		. = ALIGN(2);
		*(COMMON)
		. = ALIGN(2);
		PROVIDE(_ebss = .);
	} >RAM
	PROVIDE(_bss_size = SIZEOF(.bss));

	.stack ORIGIN(RAM) + LENGTH(RAM) - _stack_size :
	{
		. = ALIGN(2);
		*(.stack)
		. += _stack_size;
		. = ALIGN(2);
		PROVIDE(_stack = .);
	}
}

/****************************************************************************/
/* Include peripherals memory map                                           */
/****************************************************************************/

INCLUDE msp430g2553_symbols.ld

