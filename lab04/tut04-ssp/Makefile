CFLAGS := -m32 -g -O0 -mpreferred-stack-boundary=2

ifeq ($(shell expr `gcc -dumpversion | cut -f1 -d.` \>= 5), 1)
	LDFLAGS += -no-pie
endif

ALL := crackme0x00-nossp-exec crackme0x00-nossp-noexec crackme0x00-ssp-exec crackme0x00-ssp-noexec

all: $(ALL)

crackme0x00-nossp-exec: crackme0x00.c
	$(CC) $(CFLAGS) -fno-stack-protector -z execstack -o $@ $<
	checksec --file $@

crackme0x00-nossp-noexec: crackme0x00.c
	$(CC) $(CFLAGS) -fno-stack-protector -o $@ $<
	checksec --file $@

crackme0x00-ssp-exec: crackme0x00.c
	$(CC) $(CFLAGS) -fstack-protector -o $@ -z execstack $<
	checksec --file $@

crackme0x00-ssp-noexec: crackme0x00.c
	$(CC) $(CFLAGS) -fstack-protector -o $@ $<
	checksec --file $@

target-ssp: _crackme0x00-modified.c
	$(CC) $(CFLAGS) -z execstack -fno-stack-protector -mpreferred-stack-boundary=2 -g -O0 -o $@ $<

.PHONY: all clean
