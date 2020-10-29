#!/usr/bin/python2

from pwn import *

context.log_level = 'error'

def to_printable(i):
    if 0x20 <= i < 0x7f:
        return "%c" % chr(i)
    return "-"

if __name__ == '__main__':

    whitespace = []
    for i in range(256):
        inp = "AAAA" + chr(i) + "AAAA"

        p = process("./test")
        p.sendline(inp)
        outp = p.recv().strip()

        pos = outp.rindex("41414141")
        if pos == 0:
            whitespace.append(i)

        print("%02x %s %s -> %s (%d)" %
              (i, to_printable(i),
               inp.encode("hex"), outp, pos))

    print("> whitespace chars: %s" % ", ".join("%02x" % c for c in whitespace))