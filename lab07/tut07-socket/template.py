#!/usr/bin/env python2

from pwn import *

if __name__ == '__main__':
    # open a socket
    s = remote("localhost", 9736)

    # eat banner
    print s.recvline()

    # send name
    s.send("test\n")

    i = 1
    while i <= 5:
        # send my decision
        s.send("rock\n")

        # eat result
        result = s.recvline()
        print(result)

        # check result
        if "win" in result.lower():
            i += 1
            continue
        if "tie" in result.lower():
            continue
        else:
            s.close()
            exit(1)

