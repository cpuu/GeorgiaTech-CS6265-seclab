#!/bin/bash

dump() {
  gdb -batch $1 -ex 'disassemble main' \
    | cut -d":" -f2- \
    | grep -v "\(lea\|jmp\|jne\|je\|xchg\)"
}

diff -urN <(dump $1) <(dump $2)
