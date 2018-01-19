GCC = D:/msp430-gcc/msp430-gcc-6.4.0.32_win32/bin/msp430-elf-gcc.exe
OBJCPY = D:/msp430-gcc/msp430-gcc-6.4.0.32_win32/bin/msp430-elf-objcopy.exe
OutputDir = Build
Sources = $(wildcard *.c)
Objects = $(patsubst %.c,$(OutputDir)/%.o,$(Sources))
Assembers = $(wildcard *.asm)
AssembersObj = $(patsubst %.asm,$(OutputDir)/%.o,$(Assembers))
Target = bootloader.elf
Hex = bootloader.hex

CFLAGS = -g -Wall -mmcu=msp430g2553 -L. -LD:\msp430-gcc\include

all: $(OutputDir)/$(Target) $(OutputDir)/$(Hex)

$(OutputDir)/$(Target): $(Objects) $(AssembersObj)
	$(GCC) $(CFLAGS) $^ -o $@ -T ./msp430g2553.ld -nostdlib -lgcc

$(OutputDir)/$(Hex): $(OutputDir)/$(Target)
	$(OBJCPY) -O ihex $< $@


$(Objects): $(OutputDir)/%.o : %.c
	$(GCC) $(CFLAGS) -c $< -o $@

$(AssembersObj): $(OutputDir)/%.o : %.asm
	$(GCC) $(CFLAGS) -c -x assembler $^ -o $@

clean :
	cd $(OutputDir) && del *.o *.exe *.elf
