    symbol-file /home/sirjanh/nanobyte_os-Part11/build/i686_debug/kernel/kernel.elf
    set disassembly-flavor intel
    target remote | qemu-system-i386 -S -gdb stdio -m 32 -fda /home/sirjanh/nanobyte_os-Part11/build/i686_debug/image.img
