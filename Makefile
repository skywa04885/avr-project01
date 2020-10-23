DEVICE_PATH=/dev/ttyACM0
MMCU=atmega2560
PROGRAMMER=wiring

C_ARGS=-mmcu=$(MMCU) -Os -DLOGGER_ERRORS_ENABLE -DLOGGER_INFO_ENABLE -DLOGGER_DEBUG_ENABLE
C_MODULES=a1602 io status usart dht11
C_MODULE_SOURCES=$(foreach module,$(C_MODULES),modules/$(module).c)

prepare:
	mkdir -p build
all: prepare
	avr-gcc main.c $(C_MODULE_SOURCES) $(C_ARGS) -o build/main.elf
	avr-objcopy -O ihex build/main.elf build/main.hex
	avr-size --mcu=$(MMCU) -C build/main.elf
flash: all
	avrdude -P $(DEVICE_PATH) -p $(MMCU) -c $(PROGRAMMER) -D -U flash:w:build/main.hex
dev: flash
	sudo cat $(DEVICE_PATH) 9600
clean:
	rm -R build