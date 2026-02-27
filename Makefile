ARCH = armv7-a
MPCU = cortex-a8

TARGET = rvpb

CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OC = arm-none-eabi-objcopy

LINKER_SCRIPT = ./navilos.ld
MAP_FILE = build/navilos.map

ARM_SRCS = $(wildcard boot/*.S)
ARM_OBJS = $(patsubst boot/%.S, build/%.os, $(ARM_SRCS))

VPATH = boot \
		hal/$(TARGET)

# collect C sources by basename; VPATH lets make find them in boot/ or hal/$(TARGET)
C_SRCS  = $(notdir $(wildcard boot/*.c))
C_SRCS += $(notdir $(wildcard hal/$(TARGET)/*.c))

# objects live under build/ with the same basename
C_OBJS  = $(patsubst %.c, build/%.o, $(C_SRCS))


INC_DIRS = 	-I include \
			-I hal \
			-I hal/$(TARGET)

CFLAGS = -c -g -std=c11

navilos = build/navilos.axf
navilos_bin = build/navilos.bin

.PHONY: all clean urn debug gdb

all: $(navilos)

clean:
	@rm -rf build

run: $(navilos)
	qemu-system-arm -M realview-pb-a8 -kernel $(navilos) -nographic

debug: $(navilos)
	qemu-system-arm -M realview-pb-a8 -kernel $(navilos) -nographic -S -gdb tcp::1234,ipv4 < /dev/null &

gdb:
	gdb-multiarch

kill:
	kill `ps aux |grep qemu |awk 'NR==1{print $$2}'`

$(navilos): $(ARM_OBJS) $(C_OBJS) $(LINKER_SCRIPT)
	$(LD) -n -T $(LINKER_SCRIPT) -Map $(MAP_FILE) -o $(navilos) $(ARM_OBJS) $(C_OBJS)
	$(OC) -O binary $(navilos) $(navilos_bin)

build/%.os: %.S
	@mkdir -p $(shell dirname $@)
	$(CC) -march=$(ARCH) $(INC_DIRS) -c -g -o $@ $<

build/%.o: %.c
	@mkdir -p $(shell dirname $@)
	$(CC) -march=$(ARCH) $(INC_DIRS) -c -g -o $@ $<

