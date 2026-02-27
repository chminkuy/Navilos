ARCH = armv7-a
MPCU = cortex-a8

CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OC = arm-none-eabi-objcopy

LINKER_SCRIPT = ./navilos.ld
MAP_FILE = build/navilos.map

ARM_SRCS = $(wildcard boot/*.S)
ARM_OBJS = $(patsubst boot/%.S, build/%.os, $(ARM_SRCS))

C_SRCS = $(wildcard boot/*.c)
C_OBJS = $(patsubst boot/%.c, build/%.o, $(C_SRCS))

INC_DIRS = include

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

$(navilos): $(ARM_OBJS) $(C_OBJS)
	$(LD) -T $(LINKER_SCRIPT) -Map $(MAP_FILE) -o $(navilos) $(ARM_OBJS) $(C_OBJS)
	$(OC) -O binary $(navilos) $(navilos_bin)

build/%.os: $(ARM_SRCS)
	@mkdir -p $(shell dirname $@)
	$(CC) -march=$(ARCH) -I $(INC_DIRS) -c -g -o $@ $<

build/%.o: $(C_SRCS)
	@mkdir -p $(shell dirname $@)
	$(CC) -march=$(ARCH) -I $(INC_DIRS) -c -g -o $@ $<

