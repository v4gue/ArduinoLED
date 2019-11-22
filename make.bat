 avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o dfjd.o dfjd.c
 avr-gcc -mmcu=atmega328p dfjd.o -o dfjd
 avr-objcopy -O ihex -R .eeprom dfjd dfjd.hex
 avrdude -F -V -c arduino -p ATMEGA328P -P COM3 -b 115200 -U flash:w:dfjd.hex

pause