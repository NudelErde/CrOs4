source_dir := $(shell pwd)
object_dir := $(source_dir)/build

LD := ld
CXX := clang++
CXXFLAGS := -std=c++17 -fpie -fno-strict-aliasing -fno-asynchronous-unwind-tables -fno-exceptions -fno-rtti -fno-common -mno-red-zone -mgeneral-regs-only -ffreestanding -O2 -g -Wall -Wextra -Wno-reserved-identifier -I$(source_dir)/include

source_files := $(shell find $(source_dir) -type f -name "*.cpp")
object_files := $(patsubst $(source_dir)/%,$(object_dir)/%.o,$(source_files))

$(object_files): $(object_dir)%.o : $(source_dir)%
	@mkdir -p $(dir $@)
	@echo "Compiling $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

kernel.bin: $(object_files)
	@mkdir -p output
	@echo "Linking kernel"
	@$(LD) --build-id=none --no-relax -nostdlib -o output/kernel.bin -T $(source_dir)/linker.ld $(object_files)
	@echo "Disassembling kernel"
	@objdump -dC output/kernel.bin > output/kernel.asm


iso: kernel.bin
	@echo "Creating ISO"
	@cp output/kernel.bin iso/boot/kernel.bin
	@grub-mkrescue -d /usr/lib/grub/i386-pc -o output/kernel.iso iso

all: kernel.bin iso

clean:
	@rm -rf $(object_dir) output iso/boot/kernel.bin