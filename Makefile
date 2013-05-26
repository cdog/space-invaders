all: main.hex

main.elf: main.c assets/fonts.c assets/img.c includes/GLI.c includes/NT7108.c
	avr-gcc -mmcu=atmega324p -Os -Wall -o $@ $^

main.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex $< $@
	avr-size main.elf

clean:
	$(RM) main.elf main.hex

.PHONY: all clean
