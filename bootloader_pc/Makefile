GCC = gcc
OutputDir = Build
Sources = $(wildcard *.c)
Objects = $(patsubst %.c,$(OutputDir)/%.o,$(Sources))
Target = $(OutputDir)/bootloader_pc.exe


CFLAGS = -g -Wall

all: $(Target)

$(Target): $(Objects)
	$(GCC) $(CFLAGS) $^ -o $@

$(Objects): $(OutputDir)/%.o : %.c
	$(GCC) $(CFLAGS) -c $< -o $@

clean :
	cd $(OutputDir)&&del *.o *.exe
