
tmp.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <.text>:
   0:	c7 04 24 39 62 39 35 	movl   $0x35396239,(%rsp)
   7:	c7 44 24 04 61 66 37 	movl   $0x39376661,0x4(%rsp)
   e:	39 
   f:	c6 44 24 08 00       	movb   $0x0,0x8(%rsp)
  14:	48 8d 3c 24          	lea    (%rsp),%rdi
  18:	68 fa 18 40 00       	pushq  $0x4018fa
  1d:	c3                   	retq   
