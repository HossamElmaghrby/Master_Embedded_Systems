#@copyright: Hossam Elmaghraby
CC=arm-none-eabi-
CFLAGS=-mcpu=cortex-m4 -gdwarf-2 -g
FINCS=-I .
LIBS=
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
AS=$(wildcard *.s)
OBJAS=$(AS:.s=.o)
Project_name=Lab4_toggle_led_using_cortexm4

all: $(Project_name).bin
	@echo "=============build done================="

%.o: %.c
	$(CC)gcc.exe -c $(INCS) $(CFLAGS) $< -o $@

#@startup.o: startup.s
#@	$(CC)as.exe  $(CFLAGS) $< -o $@

$(Project_name).elf: $(OBJ) $(OBJAS)
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) $(OBJAS) -o $@ -Map=output.map
	cp $(Project_name).elf	$(Project_name).axf	

$(Project_name).bin: $(Project_name).elf
	$(CC)objcopy.exe -O binary $< $@

clean_all:
	rm *.o *.map *.bin *.elf

clean:
	rm *.elf *.bin *.map 