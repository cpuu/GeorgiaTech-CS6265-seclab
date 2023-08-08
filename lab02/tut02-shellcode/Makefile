CFLAGS := -m32 -std=gnu99 -g -O0 -fno-stack-protector -fno-PIE -fno-pie -z execstack

ALL := shellcode.bin target

all: $(ALL)

target: target.c
	$(CC) $(CFLAGS) -o $@ $<

CHAL_META: target

%.o: %.S
	$(CC) -m32 -c -o $@ $<

%.bin: %.o
	objcopy -S -O binary -j .text $< $@

test: $(ALL)
	cat shellcode.bin | disasm -c i386
	bash -c '(cat shellcode.bin; echo; cat) | strace -e execve ./target'

readflag: $(ALL)
	bash -c 'echo "cat /proc/flag" | (cat shellcode.bin; echo; cat) | ./target'

clean:
	rm -f $(ALL) *.bin

.PHONY: all clean
