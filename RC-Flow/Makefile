
TARGET_NAME=spi-slave
TARGET=$(TARGET_NAME).hex
BINARY=$(TARGET_NAME).bin
EXECUTABLE=$(TARGET_NAME).elf

CC=arm-none-eabi-gcc
LD=arm-none-eabi-ld 
#LD=arm-none-eabi-gcc
AR=arm-none-eabi-ar
AS=arm-none-eabi-as
CP=arm-none-eabi-objcopy
OD=arm-none-eabi-objdump

BIN=$(CP) -O ihex 

DEFS = -DUSE_STDPERIPH_DRIVER -DSTM32F4XX -DMANGUSTA_DISCOVERY -DUSE_USB_OTG_FS -DHSE_VALUE=12000000

MCU = cortex-m4
MCFLAGS = -mcpu=$(MCU) -mthumb -mlittle-endian -mfpu=fpv4-sp-d16 -mfloat-abi=soft -mthumb-interwork
STM32_INCLUDES = -ILibraries/CMSIS/ST/STM32F4xx/Include/ \
	-ILibraries/CMSIS/Include/ \
	-ILibraries/STM32F4xx_StdPeriph_Driver/inc/ \
	-ILibraries/STM32_USB_Device_Library/Class/hid/inc \
	-ILibraries/STM32_USB_Device_Library/Core/inc/ \
	-ILibraries/STM32_USB_OTG_Driver/inc/ \



OPTIMIZE       = -Os

CFLAGS	= $(MCFLAGS)  $(OPTIMIZE)  $(DEFS) -I./ -I./ $(STM32_INCLUDES)  -Wl,-T,stm32_flash.ld
AFLAGS	= $(MCFLAGS) 
#-mapcs-float use float regs. small increase in code size

STM32_USB_OTG_SRC = Libraries/STM32_USB_OTG_Driver/src/usb_dcd_int.c \
	Libraries/STM32_USB_OTG_Driver/src/usb_core.c \
	Libraries/STM32_USB_OTG_Driver/src/usb_dcd.c \

STM32_USB_DEVICE_SRC = Libraries/STM32_USB_Device_Library/Class/hid/src/usbd_hid_core.c \
	Libraries/STM32_USB_Device_Library/Core/src/usbd_req.c \
	Libraries/STM32_USB_Device_Library/Core/src/usbd_core.c \
	Libraries/STM32_USB_Device_Library/Core/src/usbd_ioreq.c

SRC = main.c \
	adc.c \
	sw.c \
	ppm.c \
	usart.c \
	rcflow.c \
	stm32f4xx_it.c \
	system_stm32f4xx.c \
	syscalls+printf.c \
	Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.c \
	Libraries/STM32F4xx_StdPeriph_Driver/src/misc.c \
	Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c \
	Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c \
	Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.c \
	Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.c \
	Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.c \
	Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_adc.c \
	Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.c \
	Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_i2c.c \
	Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.c \
	Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.c \
#	Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dac.c \



STARTUP = startup_stm32f4xx.s

OBJDIR = .
OBJ = $(SRC:%.c=$(OBJDIR)/%.o) 
OBJ += Startup.o

all: $(TARGET) $(BINARY)

$(TARGET): $(EXECUTABLE)
	$(CP) -O ihex $^ $@

$(BINARY): $(EXECUTABLE)
	$(CP) -O binary $^ $@

$(EXECUTABLE): $(SRC) $(STARTUP)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f Startup.lst $(OBJ) \
	 $(TARGET)  $(BINARY) $(EXECUTABLE)

_flash: $(BINARY)
	st-flash write $(BINARY) 0x08000000

flash: $(BINARY)
	../dfuse-dfu-util/src/dfu-util --dfuse-address 0x8000000 -a 0 -R -D $(BINARY)


