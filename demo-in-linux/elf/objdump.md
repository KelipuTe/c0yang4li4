### demo02

#### objdump -h demo02

```
> objdump -h demo02

demo02:     file format elf64-x86-64

Sections:
Idx Name          Size      VMA               LMA               File off  Algn
  0 .interp       0000001c  0000000000000318  0000000000000318  00000318  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  1 .note.gnu.property 00000030  0000000000000338  0000000000000338  00000338  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  2 .note.gnu.build-id 00000024  0000000000000368  0000000000000368  00000368  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  3 .note.ABI-tag 00000020  000000000000038c  000000000000038c  0000038c  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  4 .gnu.hash     00000024  00000000000003b0  00000000000003b0  000003b0  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  5 .dynsym       000000a8  00000000000003d8  00000000000003d8  000003d8  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  6 .dynstr       0000008f  0000000000000480  0000000000000480  00000480  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  7 .gnu.version  0000000e  0000000000000510  0000000000000510  00000510  2**1
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  8 .gnu.version_r 00000030  0000000000000520  0000000000000520  00000520  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  9 .rela.dyn     000000c0  0000000000000550  0000000000000550  00000550  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 10 .rela.plt     00000018  0000000000000610  0000000000000610  00000610  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 11 .init         0000001b  0000000000001000  0000000000001000  00001000  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 12 .plt          00000020  0000000000001020  0000000000001020  00001020  2**4
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 13 .plt.got      00000010  0000000000001040  0000000000001040  00001040  2**4
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 14 .plt.sec      00000010  0000000000001050  0000000000001050  00001050  2**4
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 15 .text         00000189  0000000000001060  0000000000001060  00001060  2**4
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 16 .fini         0000000d  00000000000011ec  00000000000011ec  000011ec  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 17 .rodata       00000012  0000000000002000  0000000000002000  00002000  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 18 .eh_frame_hdr 00000044  0000000000002014  0000000000002014  00002014  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 19 .eh_frame     000000ec  0000000000002058  0000000000002058  00002058  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 20 .init_array   00000008  0000000000003db8  0000000000003db8  00002db8  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 21 .fini_array   00000008  0000000000003dc0  0000000000003dc0  00002dc0  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 22 .dynamic      000001f0  0000000000003dc8  0000000000003dc8  00002dc8  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 23 .got          00000048  0000000000003fb8  0000000000003fb8  00002fb8  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 24 .data         00000018  0000000000004000  0000000000004000  00003000  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 25 .bss          00000010  0000000000004018  0000000000004018  00003018  2**2
                  ALLOC
 26 .comment      0000002b  0000000000000000  0000000000000000  00003018  2**0
                  CONTENTS, READONLY
```

#### objdump -s demo02

```
> objdump -s demo02

demo02:     file format elf64-x86-64

Contents of section .interp:
 0318 2f6c6962 36342f6c 642d6c69 6e75782d  /lib64/ld-linux-
 0328 7838362d 36342e73 6f2e3200           x86-64.so.2.    
Contents of section .note.gnu.property:
 0338 04000000 20000000 05000000 474e5500  .... .......GNU.
 0348 020000c0 04000000 03000000 00000000  ................
 0358 028000c0 04000000 01000000 00000000  ................
Contents of section .note.gnu.build-id:
 0368 04000000 14000000 03000000 474e5500  ............GNU.
 0378 130dbcaa e85a3d02 4839e617 4776f39c  .....Z=.H9..Gv..
 0388 20d34f2b                              .O+            
Contents of section .note.ABI-tag:
 038c 04000000 10000000 01000000 474e5500  ............GNU.
 039c 00000000 03000000 02000000 00000000  ................
Contents of section .gnu.hash:
 03b0 02000000 06000000 01000000 06000000  ................
 03c0 00008100 00000000 06000000 00000000  ................
 03d0 d165ce6d                             .e.m            
Contents of section .dynsym:
 03d8 00000000 00000000 00000000 00000000  ................
 03e8 00000000 00000000 10000000 12000000  ................
 03f8 00000000 00000000 00000000 00000000  ................
 0408 4a000000 20000000 00000000 00000000  J... ...........
 0418 00000000 00000000 22000000 12000000  ........".......
 0428 00000000 00000000 00000000 00000000  ................
 0438 66000000 20000000 00000000 00000000  f... ...........
 0448 00000000 00000000 75000000 20000000  ........u... ...
 0458 00000000 00000000 00000000 00000000  ................
 0468 01000000 22000000 00000000 00000000  ...."...........
 0478 00000000 00000000                    ........        
Contents of section .dynstr:
 0480 005f5f63 78615f66 696e616c 697a6500  .__cxa_finalize.
 0490 5f5f6c69 62635f73 74617274 5f6d6169  __libc_start_mai
 04a0 6e007072 696e7466 006c6962 632e736f  n.printf.libc.so
 04b0 2e360047 4c494243 5f322e32 2e350047  .6.GLIBC_2.2.5.G
 04c0 4c494243 5f322e33 34005f49 544d5f64  LIBC_2.34._ITM_d
 04d0 65726567 69737465 72544d43 6c6f6e65  eregisterTMClone
 04e0 5461626c 65005f5f 676d6f6e 5f737461  Table.__gmon_sta
 04f0 72745f5f 005f4954 4d5f7265 67697374  rt__._ITM_regist
 0500 6572544d 436c6f6e 65546162 6c6500    erTMCloneTable. 
Contents of section .gnu.version:
 0510 00000200 01000300 01000100 0300      ..............  
Contents of section .gnu.version_r:
 0520 01000200 29000000 10000000 00000000  ....)...........
 0530 751a6909 00000300 33000000 10000000  u.i.....3.......
 0540 b4919606 00000200 3f000000 00000000  ........?.......
Contents of section .rela.dyn:
 0550 b83d0000 00000000 08000000 00000000  .=..............
 0560 40110000 00000000 c03d0000 00000000  @........=......
 0570 08000000 00000000 00110000 00000000  ................
 0580 08400000 00000000 08000000 00000000  .@..............
 0590 08400000 00000000 d83f0000 00000000  .@.......?......
 05a0 06000000 01000000 00000000 00000000  ................
 05b0 e03f0000 00000000 06000000 02000000  .?..............
 05c0 00000000 00000000 e83f0000 00000000  .........?......
 05d0 06000000 04000000 00000000 00000000  ................
 05e0 f03f0000 00000000 06000000 05000000  .?..............
 05f0 00000000 00000000 f83f0000 00000000  .........?......
 0600 06000000 06000000 00000000 00000000  ................
Contents of section .rela.plt:
 0610 d03f0000 00000000 07000000 03000000  .?..............
 0620 00000000 00000000                    ........        
Contents of section .init:
 1000 f30f1efa 4883ec08 488b05d9 2f000048  ....H...H.../..H
 1010 85c07402 ffd04883 c408c3             ..t...H....     
Contents of section .plt:
 1020 ff359a2f 0000f2ff 259b2f00 000f1f00  .5./....%./.....
 1030 f30f1efa 68000000 00f2e9e1 ffffff90  ....h...........
Contents of section .plt.got:
 1040 f30f1efa f2ff25ad 2f00000f 1f440000  ......%./....D..
Contents of section .plt.sec:
 1050 f30f1efa f2ff2575 2f00000f 1f440000  ......%u/....D..
Contents of section .text:
 1060 f30f1efa 31ed4989 d15e4889 e24883e4  ....1.I..^H..H..
 1070 f0505445 31c031c9 488d3d33 010000ff  .PTE1.1.H.=3....
 1080 15532f00 00f4662e 0f1f8400 00000000  .S/...f.........
 1090 488d3d81 2f000048 8d057a2f 00004839  H.=./..H..z/..H9
 10a0 f8741548 8b05362f 00004885 c07409ff  .t.H..6/..H..t..
 10b0 e00f1f80 00000000 c30f1f80 00000000  ................
 10c0 488d3d51 2f000048 8d354a2f 00004829  H.=Q/..H.5J/..H)
 10d0 fe4889f0 48c1ee3f 48c1f803 4801c648  .H..H..?H...H..H
 10e0 d1fe7414 488b0505 2f000048 85c07408  ..t.H.../..H..t.
 10f0 ffe0660f 1f440000 c30f1f80 00000000  ..f..D..........
 1100 f30f1efa 803d0d2f 00000075 2b554883  .....=./...u+UH.
 1110 3de22e00 00004889 e5740c48 8b3de62e  =.....H..t.H.=..
 1120 0000e819 ffffffe8 64ffffff c605e52e  ........d.......
 1130 0000015d c30f1f00 c30f1f80 00000000  ...]............
 1140 f30f1efa e977ffff fff30f1e fa554889  .....w.......UH.
 1150 e58b05bd 2e000089 c6488d05 a40e0000  .........H......
 1160 4889c7b8 00000000 e8e3feff ff8b05a1  H...............
 1170 2e000083 c0018905 982e0000 905dc3f3  .............]..
 1180 0f1efa55 4889e548 83ec2089 7dec8b45  ...UH..H.. .}..E
 1190 ec8945fc 8b45fc89 c6488d05 6b0e0000  ..E..E...H..k...
 11a0 4889c7b8 00000000 e8a3feff ff8b45fc  H.............E.
 11b0 c9c3f30f 1efa5548 89e5b800 000000e8  ......UH........
 11c0 85ffffff b8000000 00e87bff ffffbf01  ..........{.....
 11d0 000000e8 a7ffffff bf020000 00e89dff  ................
 11e0 ffffb800 0000005d c3                 .......].       
Contents of section .fini:
 11ec f30f1efa 4883ec08 4883c408 c3        ....H...H....   
Contents of section .rodata:
 2000 01000200 73693d25 640a0078 783d2564  ....si=%d..xx=%d
 2010 0a00                                 ..              
Contents of section .eh_frame_hdr:
 2014 011b033b 40000000 07000000 0cf0ffff  ...;@...........
 2024 74000000 2cf0ffff 9c000000 3cf0ffff  t...,.......<...
 2034 b4000000 4cf0ffff 5c000000 35f1ffff  ....L...\...5...
 2044 cc000000 6bf1ffff ec000000 9ef1ffff  ....k...........
 2054 0c010000                             ....            
Contents of section .eh_frame:
 2058 14000000 00000000 017a5200 01781001  .........zR..x..
 2068 1b0c0708 90010000 14000000 1c000000  ................
 2078 e8efffff 26000000 00440710 00000000  ....&....D......
 2088 24000000 34000000 90efffff 20000000  $...4....... ...
 2098 000e1046 0e184a0f 0b770880 003f1a3a  ...F..J..w...?.:
 20a8 2a332422 00000000 14000000 5c000000  *3$"........\...
 20b8 88efffff 10000000 00000000 00000000  ................
 20c8 14000000 74000000 80efffff 10000000  ....t...........
 20d8 00000000 00000000 1c000000 8c000000  ................
 20e8 61f0ffff 36000000 00450e10 8602430d  a...6....E....C.
 20f8 066d0c07 08000000 1c000000 ac000000  .m..............
 2108 77f0ffff 33000000 00450e10 8602430d  w...3....E....C.
 2118 066a0c07 08000000 1c000000 cc000000  .j..............
 2128 8af0ffff 37000000 00450e10 8602430d  ....7....E....C.
 2138 066e0c07 08000000 00000000           .n..........    
Contents of section .init_array:
 3db8 40110000 00000000                    @.......        
Contents of section .fini_array:
 3dc0 00110000 00000000                    ........        
Contents of section .dynamic:
 3dc8 01000000 00000000 29000000 00000000  ........).......
 3dd8 0c000000 00000000 00100000 00000000  ................
 3de8 0d000000 00000000 ec110000 00000000  ................
 3df8 19000000 00000000 b83d0000 00000000  .........=......
 3e08 1b000000 00000000 08000000 00000000  ................
 3e18 1a000000 00000000 c03d0000 00000000  .........=......
 3e28 1c000000 00000000 08000000 00000000  ................
 3e38 f5feff6f 00000000 b0030000 00000000  ...o............
 3e48 05000000 00000000 80040000 00000000  ................
 3e58 06000000 00000000 d8030000 00000000  ................
 3e68 0a000000 00000000 8f000000 00000000  ................
 3e78 0b000000 00000000 18000000 00000000  ................
 3e88 15000000 00000000 00000000 00000000  ................
 3e98 03000000 00000000 b83f0000 00000000  .........?......
 3ea8 02000000 00000000 18000000 00000000  ................
 3eb8 14000000 00000000 07000000 00000000  ................
 3ec8 17000000 00000000 10060000 00000000  ................
 3ed8 07000000 00000000 50050000 00000000  ........P.......
 3ee8 08000000 00000000 c0000000 00000000  ................
 3ef8 09000000 00000000 18000000 00000000  ................
 3f08 1e000000 00000000 08000000 00000000  ................
 3f18 fbffff6f 00000000 01000008 00000000  ...o............
 3f28 feffff6f 00000000 20050000 00000000  ...o.... .......
 3f38 ffffff6f 00000000 01000000 00000000  ...o............
 3f48 f0ffff6f 00000000 10050000 00000000  ...o............
 3f58 f9ffff6f 00000000 03000000 00000000  ...o............
 3f68 00000000 00000000 00000000 00000000  ................
 3f78 00000000 00000000 00000000 00000000  ................
 3f88 00000000 00000000 00000000 00000000  ................
 3f98 00000000 00000000 00000000 00000000  ................
 3fa8 00000000 00000000 00000000 00000000  ................
Contents of section .got:
 3fb8 c83d0000 00000000 00000000 00000000  .=..............
 3fc8 00000000 00000000 30100000 00000000  ........0.......
 3fd8 00000000 00000000 00000000 00000000  ................
 3fe8 00000000 00000000 00000000 00000000  ................
 3ff8 00000000 00000000                    ........        
Contents of section .data:
 4000 00000000 00000000 08400000 00000000  .........@......
 4010 2c010000 0a000000                    ,.......        
Contents of section .comment:
 0000 4743433a 20285562 756e7475 2031312e  GCC: (Ubuntu 11.
 0010 332e302d 31756275 6e747531 7e32322e  3.0-1ubuntu1~22.
 0020 30342920 31312e33 2e3000             04) 11.3.0. 
```

#### objdump -d demo02

```
> objdump -d demo02

demo02:     file format elf64-x86-64


Disassembly of section .init:

0000000000001000 <_init>:
    1000:	f3 0f 1e fa          	endbr64 
    1004:	48 83 ec 08          	sub    $0x8,%rsp
    1008:	48 8b 05 d9 2f 00 00 	mov    0x2fd9(%rip),%rax        # 3fe8 <__gmon_start__@Base>
    100f:	48 85 c0             	test   %rax,%rax
    1012:	74 02                	je     1016 <_init+0x16>
    1014:	ff d0                	call   *%rax
    1016:	48 83 c4 08          	add    $0x8,%rsp
    101a:	c3                   	ret    

Disassembly of section .plt:

0000000000001020 <.plt>:
    1020:	ff 35 9a 2f 00 00    	push   0x2f9a(%rip)        # 3fc0 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	f2 ff 25 9b 2f 00 00 	bnd jmp *0x2f9b(%rip)        # 3fc8 <_GLOBAL_OFFSET_TABLE_+0x10>
    102d:	0f 1f 00             	nopl   (%rax)
    1030:	f3 0f 1e fa          	endbr64 
    1034:	68 00 00 00 00       	push   $0x0
    1039:	f2 e9 e1 ff ff ff    	bnd jmp 1020 <_init+0x20>
    103f:	90                   	nop

Disassembly of section .plt.got:

0000000000001040 <__cxa_finalize@plt>:
    1040:	f3 0f 1e fa          	endbr64 
    1044:	f2 ff 25 ad 2f 00 00 	bnd jmp *0x2fad(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    104b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .plt.sec:

0000000000001050 <printf@plt>:
    1050:	f3 0f 1e fa          	endbr64 
    1054:	f2 ff 25 75 2f 00 00 	bnd jmp *0x2f75(%rip)        # 3fd0 <printf@GLIBC_2.2.5>
    105b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .text:

0000000000001060 <_start>:
    1060:	f3 0f 1e fa          	endbr64 
    1064:	31 ed                	xor    %ebp,%ebp
    1066:	49 89 d1             	mov    %rdx,%r9
    1069:	5e                   	pop    %rsi
    106a:	48 89 e2             	mov    %rsp,%rdx
    106d:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    1071:	50                   	push   %rax
    1072:	54                   	push   %rsp
    1073:	45 31 c0             	xor    %r8d,%r8d
    1076:	31 c9                	xor    %ecx,%ecx
    1078:	48 8d 3d 33 01 00 00 	lea    0x133(%rip),%rdi        # 11b2 <main>
    107f:	ff 15 53 2f 00 00    	call   *0x2f53(%rip)        # 3fd8 <__libc_start_main@GLIBC_2.34>
    1085:	f4                   	hlt    
    1086:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
    108d:	00 00 00 

0000000000001090 <deregister_tm_clones>:
    1090:	48 8d 3d 81 2f 00 00 	lea    0x2f81(%rip),%rdi        # 4018 <__TMC_END__>
    1097:	48 8d 05 7a 2f 00 00 	lea    0x2f7a(%rip),%rax        # 4018 <__TMC_END__>
    109e:	48 39 f8             	cmp    %rdi,%rax
    10a1:	74 15                	je     10b8 <deregister_tm_clones+0x28>
    10a3:	48 8b 05 36 2f 00 00 	mov    0x2f36(%rip),%rax        # 3fe0 <_ITM_deregisterTMCloneTable@Base>
    10aa:	48 85 c0             	test   %rax,%rax
    10ad:	74 09                	je     10b8 <deregister_tm_clones+0x28>
    10af:	ff e0                	jmp    *%rax
    10b1:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    10b8:	c3                   	ret    
    10b9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000010c0 <register_tm_clones>:
    10c0:	48 8d 3d 51 2f 00 00 	lea    0x2f51(%rip),%rdi        # 4018 <__TMC_END__>
    10c7:	48 8d 35 4a 2f 00 00 	lea    0x2f4a(%rip),%rsi        # 4018 <__TMC_END__>
    10ce:	48 29 fe             	sub    %rdi,%rsi
    10d1:	48 89 f0             	mov    %rsi,%rax
    10d4:	48 c1 ee 3f          	shr    $0x3f,%rsi
    10d8:	48 c1 f8 03          	sar    $0x3,%rax
    10dc:	48 01 c6             	add    %rax,%rsi
    10df:	48 d1 fe             	sar    %rsi
    10e2:	74 14                	je     10f8 <register_tm_clones+0x38>
    10e4:	48 8b 05 05 2f 00 00 	mov    0x2f05(%rip),%rax        # 3ff0 <_ITM_registerTMCloneTable@Base>
    10eb:	48 85 c0             	test   %rax,%rax
    10ee:	74 08                	je     10f8 <register_tm_clones+0x38>
    10f0:	ff e0                	jmp    *%rax
    10f2:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    10f8:	c3                   	ret    
    10f9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001100 <__do_global_dtors_aux>:
    1100:	f3 0f 1e fa          	endbr64 
    1104:	80 3d 0d 2f 00 00 00 	cmpb   $0x0,0x2f0d(%rip)        # 4018 <__TMC_END__>
    110b:	75 2b                	jne    1138 <__do_global_dtors_aux+0x38>
    110d:	55                   	push   %rbp
    110e:	48 83 3d e2 2e 00 00 	cmpq   $0x0,0x2ee2(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    1115:	00 
    1116:	48 89 e5             	mov    %rsp,%rbp
    1119:	74 0c                	je     1127 <__do_global_dtors_aux+0x27>
    111b:	48 8b 3d e6 2e 00 00 	mov    0x2ee6(%rip),%rdi        # 4008 <__dso_handle>
    1122:	e8 19 ff ff ff       	call   1040 <__cxa_finalize@plt>
    1127:	e8 64 ff ff ff       	call   1090 <deregister_tm_clones>
    112c:	c6 05 e5 2e 00 00 01 	movb   $0x1,0x2ee5(%rip)        # 4018 <__TMC_END__>
    1133:	5d                   	pop    %rbp
    1134:	c3                   	ret    
    1135:	0f 1f 00             	nopl   (%rax)
    1138:	c3                   	ret    
    1139:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001140 <frame_dummy>:
    1140:	f3 0f 1e fa          	endbr64 
    1144:	e9 77 ff ff ff       	jmp    10c0 <register_tm_clones>

0000000000001149 <func1>:
    1149:	f3 0f 1e fa          	endbr64 
    114d:	55                   	push   %rbp
    114e:	48 89 e5             	mov    %rsp,%rbp
    1151:	8b 05 bd 2e 00 00    	mov    0x2ebd(%rip),%eax        # 4014 <si.1>
    1157:	89 c6                	mov    %eax,%esi
    1159:	48 8d 05 a4 0e 00 00 	lea    0xea4(%rip),%rax        # 2004 <_IO_stdin_used+0x4>
    1160:	48 89 c7             	mov    %rax,%rdi
    1163:	b8 00 00 00 00       	mov    $0x0,%eax
    1168:	e8 e3 fe ff ff       	call   1050 <printf@plt>
    116d:	8b 05 a1 2e 00 00    	mov    0x2ea1(%rip),%eax        # 4014 <si.1>
    1173:	83 c0 01             	add    $0x1,%eax
    1176:	89 05 98 2e 00 00    	mov    %eax,0x2e98(%rip)        # 4014 <si.1>
    117c:	90                   	nop
    117d:	5d                   	pop    %rbp
    117e:	c3                   	ret    

000000000000117f <func2>:
    117f:	f3 0f 1e fa          	endbr64 
    1183:	55                   	push   %rbp
    1184:	48 89 e5             	mov    %rsp,%rbp
    1187:	48 83 ec 20          	sub    $0x20,%rsp
    118b:	89 7d ec             	mov    %edi,-0x14(%rbp)
    118e:	8b 45 ec             	mov    -0x14(%rbp),%eax
    1191:	89 45 fc             	mov    %eax,-0x4(%rbp)
    1194:	8b 45 fc             	mov    -0x4(%rbp),%eax
    1197:	89 c6                	mov    %eax,%esi
    1199:	48 8d 05 6b 0e 00 00 	lea    0xe6b(%rip),%rax        # 200b <_IO_stdin_used+0xb>
    11a0:	48 89 c7             	mov    %rax,%rdi
    11a3:	b8 00 00 00 00       	mov    $0x0,%eax
    11a8:	e8 a3 fe ff ff       	call   1050 <printf@plt>
    11ad:	8b 45 fc             	mov    -0x4(%rbp),%eax
    11b0:	c9                   	leave  
    11b1:	c3                   	ret    

00000000000011b2 <main>:
    11b2:	f3 0f 1e fa          	endbr64 
    11b6:	55                   	push   %rbp
    11b7:	48 89 e5             	mov    %rsp,%rbp
    11ba:	b8 00 00 00 00       	mov    $0x0,%eax
    11bf:	e8 85 ff ff ff       	call   1149 <func1>
    11c4:	b8 00 00 00 00       	mov    $0x0,%eax
    11c9:	e8 7b ff ff ff       	call   1149 <func1>
    11ce:	bf 01 00 00 00       	mov    $0x1,%edi
    11d3:	e8 a7 ff ff ff       	call   117f <func2>
    11d8:	bf 02 00 00 00       	mov    $0x2,%edi
    11dd:	e8 9d ff ff ff       	call   117f <func2>
    11e2:	b8 00 00 00 00       	mov    $0x0,%eax
    11e7:	5d                   	pop    %rbp
    11e8:	c3                   	ret    

Disassembly of section .fini:

00000000000011ec <_fini>:
    11ec:	f3 0f 1e fa          	endbr64 
    11f0:	48 83 ec 08          	sub    $0x8,%rsp
    11f4:	48 83 c4 08          	add    $0x8,%rsp
    11f8:	c3                   	ret   
```
