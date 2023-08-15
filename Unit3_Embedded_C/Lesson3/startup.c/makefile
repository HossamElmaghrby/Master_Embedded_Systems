#@copyright: Hossam Elmaghraby
CC=arm-none-eabi-
CFLAGS=-mcpu=cortex-m3 -gdwarf-2
FINCS=-I .
LIBS=
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
AS=$(wildcard *.s)
OBJAS=$(AS:.s=.o)
Project_name=toggle_led_from_Scratch

all: $(Project_name).bin
	@echo "=============build done================="

%.o: %.c
	$(CC)gcc.exe -c $(INCS) $(CFLAGS) $< -o $@

#@startup.o: startup.s
#@	$(CC)as.exe  $(CFLAGS) $< -o $@

$(Project_name).elf: $(OBJ) $(OBJAS)
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) $(OBJAS) -o $@ -Map=output.map	

$(Project_name).bin: $(Project_name).elf
	$(CC)objcopy.exe -O binary $< $@

clean_all:
	rm *.o *.map *.bin *.elf

clean:
	rm *.elf *.bin *.map 