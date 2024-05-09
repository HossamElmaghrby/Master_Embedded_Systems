#@copyright: Hossam Elmaghraby
CC=
CFLAGS= --coverage -g -O0
FINCS=-I .
LIBS=
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
AS=$(wildcard *.s)
OBJAS=$(AS:.s=.o)
Project_name=pressure_detection

all: $(Project_name).elf
	@echo "=============build done================="


#@startup.o: startup.s
#@	$(CC)as.exe  $(CFLAGS) $< -o $@

$(Project_name).elf:
	$(CC)gcc.exe $(SRC)  $(CFLAGS) -o $@	

gcov:  *.gcda *gcno
	gcov -a -b -c -d *.c

gcovr:  *.gcov
	gcovr -r . --html --html-details -o $(Project_name)-detailes.html
	

clean:
	rm *.elf *.html *.gcno *.gdata *.gcov *.CSS

