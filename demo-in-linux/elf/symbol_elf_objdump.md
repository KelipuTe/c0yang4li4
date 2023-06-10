```text
> objdump -s symbol.elf

symbol.elf:     file format elf64-x86-64

Contents of section .interp:
 0318 2f6c6962 36342f6c 642d6c69 6e75782d  /lib64/ld-linux-
 0328 7838362d 36342e73 6f2e3200           x86-64.so.2.    
Contents of section .note.gnu.property:
 0338 04000000 20000000 05000000 474e5500  .... .......GNU.
 0348 020000c0 04000000 03000000 00000000  ................
 0358 028000c0 04000000 01000000 00000000  ................
Contents of section .note.gnu.build-id:
 0368 04000000 14000000 03000000 474e5500  ............GNU.
 0378 0b119da3 3203c157 acb8fdb3 c2d9e149  ....2..W.......I
 0388 e15ac794                             .Z..            
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
 1070 f0505445 31c031c9 488d3d6c 010000ff  .PTE1.1.H.=l....
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
 1150 e54883ec 20897dec 8b45ec89 45fc8b55  .H.. .}..E..E..U
 1160 fc8b45ec 89c6488d 059b0e00 004889c7  ..E...H......H..
 1170 b8000000 00e8d6fe ffff8b45 fcc9c3f3  ...........E....
 1180 0f1efa55 4889e58b 05872e00 0089c648  ...UH..........H
 1190 8d05990e 00004889 c7b80000 0000e8ad  ......H.........
 11a0 feffff8b 056b2e00 0083c001 8905622e  .....k........b.
 11b0 0000905d c3f30f1e fa554889 e58b054d  ...].....UH....M
 11c0 2e000089 c6488d05 7d0e0000 4889c7b8  .....H..}...H...
 11d0 00000000 e877feff ff8b0531 2e000083  .....w.....1....
 11e0 c0018905 282e0000 905dc3f3 0f1efa55  ....(....].....U
 11f0 4889e5bf 01000000 e84cffff ffbf0200  H........L......
 1200 0000e842 ffffffb8 00000000 e86effff  ...B.........n..
 1210 ffb80000 0000e864 ffffffb8 00000000  .......d........
 1220 e890ffff ffb80000 0000e886 ffffffb8  ................
 1230 00000000 5dc3                        ....].          
Contents of section .fini:
 1238 f30f1efa 4883ec08 4883c408 c3        ....H...H....   
Contents of section .rodata:
 2000 01000200 00000000 66756e63 74696f6e  ........function
 2010 412c206c 6f63616c 496e7449 3d25642c  A, localIntI=%d,
 2020 206c6f63 616c496e 74493d25 640a0066   localIntI=%d..f
 2030 756e6374 696f6e58 2c207374 61746963  unctionX, static
 2040 496e7442 3d25640a 0066756e 6374696f  IntB=%d..functio
 2050 6e432c20 676c6f62 616c496e 74423d25  nC, globalIntB=%
 2060 640a00                               d..             
Contents of section .eh_frame_hdr:
 2064 011b033b 48000000 08000000 bcefffff  ...;H...........
 2074 7c000000 dcefffff a4000000 ecefffff  |...............
 2084 bc000000 fcefffff 64000000 e5f0ffff  ........d.......
 2094 d4000000 1bf1ffff f4000000 51f1ffff  ............Q...
 20a4 14010000 87f1ffff 34010000           ........4...    
Contents of section .eh_frame:
 20b0 14000000 00000000 017a5200 01781001  .........zR..x..
 20c0 1b0c0708 90010000 14000000 1c000000  ................
 20d0 90efffff 26000000 00440710 00000000  ....&....D......
 20e0 24000000 34000000 38efffff 20000000  $...4...8... ...
 20f0 000e1046 0e184a0f 0b770880 003f1a3a  ...F..J..w...?.:
 2100 2a332422 00000000 14000000 5c000000  *3$"........\...
 2110 30efffff 10000000 00000000 00000000  0...............
 2120 14000000 74000000 28efffff 10000000  ....t...(.......
 2130 00000000 00000000 1c000000 8c000000  ................
 2140 09f0ffff 36000000 00450e10 8602430d  ....6....E....C.
 2150 066d0c07 08000000 1c000000 ac000000  .m..............
 2160 1ff0ffff 36000000 00450e10 8602430d  ....6....E....C.
 2170 066d0c07 08000000 1c000000 cc000000  .m..............
 2180 35f0ffff 36000000 00450e10 8602430d  5...6....E....C.
 2190 066d0c07 08000000 1c000000 ec000000  .m..............
 21a0 4bf0ffff 4b000000 00450e10 8602430d  K...K....E....C.
 21b0 0602420c 07080000 00000000           ..B.........    
Contents of section .init_array:
 3db8 40110000 00000000                    @.......        
Contents of section .fini_array:
 3dc0 00110000 00000000                    ........        
Contents of section .dynamic:
 3dc8 01000000 00000000 29000000 00000000  ........).......
 3dd8 0c000000 00000000 00100000 00000000  ................
 3de8 0d000000 00000000 38120000 00000000  ........8.......
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

```text
> objdump -d symbol.elf

symbol.elf:     file format elf64-x86-64


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
    1078:	48 8d 3d 6c 01 00 00 	lea    0x16c(%rip),%rdi        # 11eb <main>
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

0000000000001149 <functionA>:
    1149:	f3 0f 1e fa          	endbr64 
    114d:	55                   	push   %rbp
    114e:	48 89 e5             	mov    %rsp,%rbp
    1151:	48 83 ec 20          	sub    $0x20,%rsp
    1155:	89 7d ec             	mov    %edi,-0x14(%rbp)
    1158:	8b 45 ec             	mov    -0x14(%rbp),%eax
    115b:	89 45 fc             	mov    %eax,-0x4(%rbp)
    115e:	8b 55 fc             	mov    -0x4(%rbp),%edx
    1161:	8b 45 ec             	mov    -0x14(%rbp),%eax
    1164:	89 c6                	mov    %eax,%esi
    1166:	48 8d 05 9b 0e 00 00 	lea    0xe9b(%rip),%rax        # 2008 <_IO_stdin_used+0x8>
    116d:	48 89 c7             	mov    %rax,%rdi
    1170:	b8 00 00 00 00       	mov    $0x0,%eax
    1175:	e8 d6 fe ff ff       	call   1050 <printf@plt>
    117a:	8b 45 fc             	mov    -0x4(%rbp),%eax
    117d:	c9                   	leave  
    117e:	c3                   	ret    

000000000000117f <functionB>:
    117f:	f3 0f 1e fa          	endbr64 
    1183:	55                   	push   %rbp
    1184:	48 89 e5             	mov    %rsp,%rbp
    1187:	8b 05 87 2e 00 00    	mov    0x2e87(%rip),%eax        # 4014 <staticIntB.1>
    118d:	89 c6                	mov    %eax,%esi
    118f:	48 8d 05 99 0e 00 00 	lea    0xe99(%rip),%rax        # 202f <_IO_stdin_used+0x2f>
    1196:	48 89 c7             	mov    %rax,%rdi
    1199:	b8 00 00 00 00       	mov    $0x0,%eax
    119e:	e8 ad fe ff ff       	call   1050 <printf@plt>
    11a3:	8b 05 6b 2e 00 00    	mov    0x2e6b(%rip),%eax        # 4014 <staticIntB.1>
    11a9:	83 c0 01             	add    $0x1,%eax
    11ac:	89 05 62 2e 00 00    	mov    %eax,0x2e62(%rip)        # 4014 <staticIntB.1>
    11b2:	90                   	nop
    11b3:	5d                   	pop    %rbp
    11b4:	c3                   	ret    

00000000000011b5 <functionC>:
    11b5:	f3 0f 1e fa          	endbr64 
    11b9:	55                   	push   %rbp
    11ba:	48 89 e5             	mov    %rsp,%rbp
    11bd:	8b 05 4d 2e 00 00    	mov    0x2e4d(%rip),%eax        # 4010 <globalIntB>
    11c3:	89 c6                	mov    %eax,%esi
    11c5:	48 8d 05 7d 0e 00 00 	lea    0xe7d(%rip),%rax        # 2049 <_IO_stdin_used+0x49>
    11cc:	48 89 c7             	mov    %rax,%rdi
    11cf:	b8 00 00 00 00       	mov    $0x0,%eax
    11d4:	e8 77 fe ff ff       	call   1050 <printf@plt>
    11d9:	8b 05 31 2e 00 00    	mov    0x2e31(%rip),%eax        # 4010 <globalIntB>
    11df:	83 c0 01             	add    $0x1,%eax
    11e2:	89 05 28 2e 00 00    	mov    %eax,0x2e28(%rip)        # 4010 <globalIntB>
    11e8:	90                   	nop
    11e9:	5d                   	pop    %rbp
    11ea:	c3                   	ret    

00000000000011eb <main>:
    11eb:	f3 0f 1e fa          	endbr64 
    11ef:	55                   	push   %rbp
    11f0:	48 89 e5             	mov    %rsp,%rbp
    11f3:	bf 01 00 00 00       	mov    $0x1,%edi
    11f8:	e8 4c ff ff ff       	call   1149 <functionA>
    11fd:	bf 02 00 00 00       	mov    $0x2,%edi
    1202:	e8 42 ff ff ff       	call   1149 <functionA>
    1207:	b8 00 00 00 00       	mov    $0x0,%eax
    120c:	e8 6e ff ff ff       	call   117f <functionB>
    1211:	b8 00 00 00 00       	mov    $0x0,%eax
    1216:	e8 64 ff ff ff       	call   117f <functionB>
    121b:	b8 00 00 00 00       	mov    $0x0,%eax
    1220:	e8 90 ff ff ff       	call   11b5 <functionC>
    1225:	b8 00 00 00 00       	mov    $0x0,%eax
    122a:	e8 86 ff ff ff       	call   11b5 <functionC>
    122f:	b8 00 00 00 00       	mov    $0x0,%eax
    1234:	5d                   	pop    %rbp
    1235:	c3                   	ret    

Disassembly of section .fini:

0000000000001238 <_fini>:
    1238:	f3 0f 1e fa          	endbr64 
    123c:	48 83 ec 08          	sub    $0x8,%rsp
    1240:	48 83 c4 08          	add    $0x8,%rsp
    1244:	c3                   	ret  
```

```text
> objdump -d -M intel symbol.elf

symbol.elf:     file format elf64-x86-64


Disassembly of section .init:

0000000000001000 <_init>:
    1000:	f3 0f 1e fa          	endbr64 
    1004:	48 83 ec 08          	sub    rsp,0x8
    1008:	48 8b 05 d9 2f 00 00 	mov    rax,QWORD PTR [rip+0x2fd9]        # 3fe8 <__gmon_start__@Base>
    100f:	48 85 c0             	test   rax,rax
    1012:	74 02                	je     1016 <_init+0x16>
    1014:	ff d0                	call   rax
    1016:	48 83 c4 08          	add    rsp,0x8
    101a:	c3                   	ret    

Disassembly of section .plt:

0000000000001020 <.plt>:
    1020:	ff 35 9a 2f 00 00    	push   QWORD PTR [rip+0x2f9a]        # 3fc0 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	f2 ff 25 9b 2f 00 00 	bnd jmp QWORD PTR [rip+0x2f9b]        # 3fc8 <_GLOBAL_OFFSET_TABLE_+0x10>
    102d:	0f 1f 00             	nop    DWORD PTR [rax]
    1030:	f3 0f 1e fa          	endbr64 
    1034:	68 00 00 00 00       	push   0x0
    1039:	f2 e9 e1 ff ff ff    	bnd jmp 1020 <_init+0x20>
    103f:	90                   	nop

Disassembly of section .plt.got:

0000000000001040 <__cxa_finalize@plt>:
    1040:	f3 0f 1e fa          	endbr64 
    1044:	f2 ff 25 ad 2f 00 00 	bnd jmp QWORD PTR [rip+0x2fad]        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    104b:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]

Disassembly of section .plt.sec:

0000000000001050 <printf@plt>:
    1050:	f3 0f 1e fa          	endbr64 
    1054:	f2 ff 25 75 2f 00 00 	bnd jmp QWORD PTR [rip+0x2f75]        # 3fd0 <printf@GLIBC_2.2.5>
    105b:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]

Disassembly of section .text:

0000000000001060 <_start>:
    1060:	f3 0f 1e fa          	endbr64 
    1064:	31 ed                	xor    ebp,ebp
    1066:	49 89 d1             	mov    r9,rdx
    1069:	5e                   	pop    rsi
    106a:	48 89 e2             	mov    rdx,rsp
    106d:	48 83 e4 f0          	and    rsp,0xfffffffffffffff0
    1071:	50                   	push   rax
    1072:	54                   	push   rsp
    1073:	45 31 c0             	xor    r8d,r8d
    1076:	31 c9                	xor    ecx,ecx
    1078:	48 8d 3d 6c 01 00 00 	lea    rdi,[rip+0x16c]        # 11eb <main>
    107f:	ff 15 53 2f 00 00    	call   QWORD PTR [rip+0x2f53]        # 3fd8 <__libc_start_main@GLIBC_2.34>
    1085:	f4                   	hlt    
    1086:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    108d:	00 00 00 

0000000000001090 <deregister_tm_clones>:
    1090:	48 8d 3d 81 2f 00 00 	lea    rdi,[rip+0x2f81]        # 4018 <__TMC_END__>
    1097:	48 8d 05 7a 2f 00 00 	lea    rax,[rip+0x2f7a]        # 4018 <__TMC_END__>
    109e:	48 39 f8             	cmp    rax,rdi
    10a1:	74 15                	je     10b8 <deregister_tm_clones+0x28>
    10a3:	48 8b 05 36 2f 00 00 	mov    rax,QWORD PTR [rip+0x2f36]        # 3fe0 <_ITM_deregisterTMCloneTable@Base>
    10aa:	48 85 c0             	test   rax,rax
    10ad:	74 09                	je     10b8 <deregister_tm_clones+0x28>
    10af:	ff e0                	jmp    rax
    10b1:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    10b8:	c3                   	ret    
    10b9:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]

00000000000010c0 <register_tm_clones>:
    10c0:	48 8d 3d 51 2f 00 00 	lea    rdi,[rip+0x2f51]        # 4018 <__TMC_END__>
    10c7:	48 8d 35 4a 2f 00 00 	lea    rsi,[rip+0x2f4a]        # 4018 <__TMC_END__>
    10ce:	48 29 fe             	sub    rsi,rdi
    10d1:	48 89 f0             	mov    rax,rsi
    10d4:	48 c1 ee 3f          	shr    rsi,0x3f
    10d8:	48 c1 f8 03          	sar    rax,0x3
    10dc:	48 01 c6             	add    rsi,rax
    10df:	48 d1 fe             	sar    rsi,1
    10e2:	74 14                	je     10f8 <register_tm_clones+0x38>
    10e4:	48 8b 05 05 2f 00 00 	mov    rax,QWORD PTR [rip+0x2f05]        # 3ff0 <_ITM_registerTMCloneTable@Base>
    10eb:	48 85 c0             	test   rax,rax
    10ee:	74 08                	je     10f8 <register_tm_clones+0x38>
    10f0:	ff e0                	jmp    rax
    10f2:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
    10f8:	c3                   	ret    
    10f9:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]

0000000000001100 <__do_global_dtors_aux>:
    1100:	f3 0f 1e fa          	endbr64 
    1104:	80 3d 0d 2f 00 00 00 	cmp    BYTE PTR [rip+0x2f0d],0x0        # 4018 <__TMC_END__>
    110b:	75 2b                	jne    1138 <__do_global_dtors_aux+0x38>
    110d:	55                   	push   rbp
    110e:	48 83 3d e2 2e 00 00 	cmp    QWORD PTR [rip+0x2ee2],0x0        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    1115:	00 
    1116:	48 89 e5             	mov    rbp,rsp
    1119:	74 0c                	je     1127 <__do_global_dtors_aux+0x27>
    111b:	48 8b 3d e6 2e 00 00 	mov    rdi,QWORD PTR [rip+0x2ee6]        # 4008 <__dso_handle>
    1122:	e8 19 ff ff ff       	call   1040 <__cxa_finalize@plt>
    1127:	e8 64 ff ff ff       	call   1090 <deregister_tm_clones>
    112c:	c6 05 e5 2e 00 00 01 	mov    BYTE PTR [rip+0x2ee5],0x1        # 4018 <__TMC_END__>
    1133:	5d                   	pop    rbp
    1134:	c3                   	ret    
    1135:	0f 1f 00             	nop    DWORD PTR [rax]
    1138:	c3                   	ret    
    1139:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]

0000000000001140 <frame_dummy>:
    1140:	f3 0f 1e fa          	endbr64 
    1144:	e9 77 ff ff ff       	jmp    10c0 <register_tm_clones>

0000000000001149 <functionA>:
    1149:	f3 0f 1e fa          	endbr64 
    114d:	55                   	push   rbp
    114e:	48 89 e5             	mov    rbp,rsp
    1151:	48 83 ec 20          	sub    rsp,0x20
    1155:	89 7d ec             	mov    DWORD PTR [rbp-0x14],edi
    1158:	8b 45 ec             	mov    eax,DWORD PTR [rbp-0x14]
    115b:	89 45 fc             	mov    DWORD PTR [rbp-0x4],eax
    115e:	8b 55 fc             	mov    edx,DWORD PTR [rbp-0x4]
    1161:	8b 45 ec             	mov    eax,DWORD PTR [rbp-0x14]
    1164:	89 c6                	mov    esi,eax
    1166:	48 8d 05 9b 0e 00 00 	lea    rax,[rip+0xe9b]        # 2008 <_IO_stdin_used+0x8>
    116d:	48 89 c7             	mov    rdi,rax
    1170:	b8 00 00 00 00       	mov    eax,0x0
    1175:	e8 d6 fe ff ff       	call   1050 <printf@plt>
    117a:	8b 45 fc             	mov    eax,DWORD PTR [rbp-0x4]
    117d:	c9                   	leave  
    117e:	c3                   	ret    

000000000000117f <functionB>:
    117f:	f3 0f 1e fa          	endbr64 
    1183:	55                   	push   rbp
    1184:	48 89 e5             	mov    rbp,rsp
    1187:	8b 05 87 2e 00 00    	mov    eax,DWORD PTR [rip+0x2e87]        # 4014 <staticIntB.1>
    118d:	89 c6                	mov    esi,eax
    118f:	48 8d 05 99 0e 00 00 	lea    rax,[rip+0xe99]        # 202f <_IO_stdin_used+0x2f>
    1196:	48 89 c7             	mov    rdi,rax
    1199:	b8 00 00 00 00       	mov    eax,0x0
    119e:	e8 ad fe ff ff       	call   1050 <printf@plt>
    11a3:	8b 05 6b 2e 00 00    	mov    eax,DWORD PTR [rip+0x2e6b]        # 4014 <staticIntB.1>
    11a9:	83 c0 01             	add    eax,0x1
    11ac:	89 05 62 2e 00 00    	mov    DWORD PTR [rip+0x2e62],eax        # 4014 <staticIntB.1>
    11b2:	90                   	nop
    11b3:	5d                   	pop    rbp
    11b4:	c3                   	ret    

00000000000011b5 <functionC>:
    11b5:	f3 0f 1e fa          	endbr64 
    11b9:	55                   	push   rbp
    11ba:	48 89 e5             	mov    rbp,rsp
    11bd:	8b 05 4d 2e 00 00    	mov    eax,DWORD PTR [rip+0x2e4d]        # 4010 <globalIntB>
    11c3:	89 c6                	mov    esi,eax
    11c5:	48 8d 05 7d 0e 00 00 	lea    rax,[rip+0xe7d]        # 2049 <_IO_stdin_used+0x49>
    11cc:	48 89 c7             	mov    rdi,rax
    11cf:	b8 00 00 00 00       	mov    eax,0x0
    11d4:	e8 77 fe ff ff       	call   1050 <printf@plt>
    11d9:	8b 05 31 2e 00 00    	mov    eax,DWORD PTR [rip+0x2e31]        # 4010 <globalIntB>
    11df:	83 c0 01             	add    eax,0x1
    11e2:	89 05 28 2e 00 00    	mov    DWORD PTR [rip+0x2e28],eax        # 4010 <globalIntB>
    11e8:	90                   	nop
    11e9:	5d                   	pop    rbp
    11ea:	c3                   	ret    

00000000000011eb <main>:
    11eb:	f3 0f 1e fa          	endbr64 
    11ef:	55                   	push   rbp
    11f0:	48 89 e5             	mov    rbp,rsp
    11f3:	bf 01 00 00 00       	mov    edi,0x1
    11f8:	e8 4c ff ff ff       	call   1149 <functionA>
    11fd:	bf 02 00 00 00       	mov    edi,0x2
    1202:	e8 42 ff ff ff       	call   1149 <functionA>
    1207:	b8 00 00 00 00       	mov    eax,0x0
    120c:	e8 6e ff ff ff       	call   117f <functionB>
    1211:	b8 00 00 00 00       	mov    eax,0x0
    1216:	e8 64 ff ff ff       	call   117f <functionB>
    121b:	b8 00 00 00 00       	mov    eax,0x0
    1220:	e8 90 ff ff ff       	call   11b5 <functionC>
    1225:	b8 00 00 00 00       	mov    eax,0x0
    122a:	e8 86 ff ff ff       	call   11b5 <functionC>
    122f:	b8 00 00 00 00       	mov    eax,0x0
    1234:	5d                   	pop    rbp
    1235:	c3                   	ret    

Disassembly of section .fini:

0000000000001238 <_fini>:
    1238:	f3 0f 1e fa          	endbr64 
    123c:	48 83 ec 08          	sub    rsp,0x8
    1240:	48 83 c4 08          	add    rsp,0x8
    1244:	c3                   	ret    
```