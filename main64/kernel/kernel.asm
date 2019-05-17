
kernel.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <k_main>:
   0:	55                   	push   rbp
   1:	48 89 e5             	mov    rbp,rsp
   4:	b8 00 00 00 00       	mov    eax,0x0
   9:	48 ba 00 00 00 00 00 	movabs rdx,0x0
  10:	00 00 00 
  13:	ff d2                	call   rdx
  15:	b8 00 00 00 00       	mov    eax,0x0
  1a:	48 ba 00 00 00 00 00 	movabs rdx,0x0
  21:	00 00 00 
  24:	ff d2                	call   rdx
  26:	b8 00 00 00 00       	mov    eax,0x0
  2b:	48 ba 00 00 00 00 00 	movabs rdx,0x0
  32:	00 00 00 
  35:	ff d2                	call   rdx
  37:	be 28 00 00 00       	mov    esi,0x28
  3c:	bf 20 00 00 00       	mov    edi,0x20
  41:	b8 00 00 00 00       	mov    eax,0x0
  46:	48 ba 00 00 00 00 00 	movabs rdx,0x0
  4d:	00 00 00 
  50:	ff d2                	call   rdx
  52:	bf fa 00 00 00       	mov    edi,0xfa
  57:	48 b8 00 00 00 00 00 	movabs rax,0x0
  5e:	00 00 00 
  61:	ff d0                	call   rax
  63:	b8 00 00 00 00       	mov    eax,0x0
  68:	48 ba 00 00 00 00 00 	movabs rdx,0x0
  6f:	00 00 00 
  72:	ff d2                	call   rdx
  74:	b8 00 00 00 00       	mov    eax,0x0
  79:	48 ba 00 00 00 00 00 	movabs rdx,0x0
  80:	00 00 00 
  83:	ff d2                	call   rdx
  85:	bf 00 00 00 40       	mov    edi,0x40000000
  8a:	b8 00 00 00 00       	mov    eax,0x0
  8f:	48 ba 00 00 00 00 00 	movabs rdx,0x0
  96:	00 00 00 
  99:	ff d2                	call   rdx
  9b:	b8 00 00 00 00       	mov    eax,0x0
  a0:	48 ba 00 00 00 00 00 	movabs rdx,0x0
  a7:	00 00 00 
  aa:	ff d2                	call   rdx
  ac:	b8 00 00 00 00       	mov    eax,0x0
  b1:	48 ba 00 00 00 00 00 	movabs rdx,0x0
  b8:	00 00 00 
  bb:	ff d2                	call   rdx
  bd:	b8 00 00 00 00       	mov    eax,0x0
  c2:	48 ba 00 00 00 00 00 	movabs rdx,0x0
  c9:	00 00 00 
  cc:	ff d2                	call   rdx
  ce:	b8 00 00 00 00       	mov    eax,0x0
  d3:	48 ba 00 00 00 00 00 	movabs rdx,0x0
  da:	00 00 00 
  dd:	ff d2                	call   rdx
  df:	b8 00 00 00 00       	mov    eax,0x0
  e4:	48 ba 00 00 00 00 00 	movabs rdx,0x0
  eb:	00 00 00 
  ee:	ff d2                	call   rdx
  f0:	48 b8 00 00 00 00 00 	movabs rax,0x0
  f7:	00 00 00 
  fa:	8b 00                	mov    eax,DWORD PTR [rax]
  fc:	83 f8 01             	cmp    eax,0x1
  ff:	75 24                	jne    125 <k_main+0x125>
 101:	b8 00 00 00 00       	mov    eax,0x0
 106:	48 ba 00 00 00 00 00 	movabs rdx,0x0
 10d:	00 00 00 
 110:	ff d2                	call   rdx
 112:	b8 00 00 00 00       	mov    eax,0x0
 117:	48 ba 00 00 00 00 00 	movabs rdx,0x0
 11e:	00 00 00 
 121:	ff d2                	call   rdx
 123:	eb 11                	jmp    136 <k_main+0x136>
 125:	b8 00 00 00 00       	mov    eax,0x0
 12a:	48 ba 00 00 00 00 00 	movabs rdx,0x0
 131:	00 00 00 
 134:	ff d2                	call   rdx
 136:	b8 00 00 00 00       	mov    eax,0x0
 13b:	48 ba 00 00 00 00 00 	movabs rdx,0x0
 142:	00 00 00 
 145:	ff d2                	call   rdx
 147:	eb fe                	jmp    147 <k_main+0x147>

0000000000000149 <InitWindowSystem>:
 149:	55                   	push   rbp
 14a:	48 89 e5             	mov    rbp,rsp
 14d:	48 b9 00 00 00 e8 00 	movabs rcx,0xffff8000e8000000
 154:	80 ff ff 
 157:	48 ba 00 00 00 08 00 	movabs rdx,0xffff800008000000
 15e:	80 ff ff 
 161:	be 00 04 00 00       	mov    esi,0x400
 166:	bf 00 05 00 00       	mov    edi,0x500
 16b:	48 b8 00 00 00 00 00 	movabs rax,0x0
 172:	00 00 00 
 175:	ff d0                	call   rax
 177:	48 ba 00 00 00 00 00 	movabs rdx,0x0
 17e:	00 00 00 
 181:	48 89 02             	mov    QWORD PTR [rdx],rax
 184:	48 b8 00 00 00 00 00 	movabs rax,0x0
 18b:	00 00 00 
 18e:	48 8b 00             	mov    rax,QWORD PTR [rax]
 191:	be ff 05 00 00       	mov    esi,0x5ff
 196:	48 89 c7             	mov    rdi,rax
 199:	48 b8 00 00 00 00 00 	movabs rax,0x0
 1a0:	00 00 00 
 1a3:	ff d0                	call   rax
 1a5:	48 ba 00 00 00 00 00 	movabs rdx,0x0
 1ac:	00 00 00 
 1af:	48 89 02             	mov    QWORD PTR [rdx],rax
 1b2:	48 b8 00 00 00 00 00 	movabs rax,0x0
 1b9:	00 00 00 
 1bc:	48 8b 00             	mov    rax,QWORD PTR [rax]
 1bf:	c7 40 70 32 00 00 00 	mov    DWORD PTR [rax+0x70],0x32
 1c6:	48 b8 00 00 00 00 00 	movabs rax,0x0
 1cd:	00 00 00 
 1d0:	48 8b 00             	mov    rax,QWORD PTR [rax]
 1d3:	c7 40 74 32 00 00 00 	mov    DWORD PTR [rax+0x74],0x32
 1da:	5d                   	pop    rbp
 1db:	c3                   	ret    

00000000000001dc <InitKPCR>:
 1dc:	55                   	push   rbp
 1dd:	48 89 e5             	mov    rbp,rsp
 1e0:	48 83 ec 10          	sub    rsp,0x10
 1e4:	bf 18 00 00 00       	mov    edi,0x18
 1e9:	48 b8 00 00 00 00 00 	movabs rax,0x0
 1f0:	00 00 00 
 1f3:	ff d0                	call   rax
 1f5:	48 89 45 f8          	mov    QWORD PTR [rbp-0x8],rax
 1f9:	48 8b 45 f8          	mov    rax,QWORD PTR [rbp-0x8]
 1fd:	48 c7 00 00 80 09 00 	mov    QWORD PTR [rax],0x98000
 204:	48 8b 45 f8          	mov    rax,QWORD PTR [rbp-0x8]
 208:	48 89 c7             	mov    rdi,rax
 20b:	48 b8 00 00 00 00 00 	movabs rax,0x0
 212:	00 00 00 
 215:	ff d0                	call   rax
 217:	c9                   	leave  
 218:	c3                   	ret    

0000000000000219 <Dummy>:
 219:	55                   	push   rbp
 21a:	48 89 e5             	mov    rbp,rsp
 21d:	48 83 ec 10          	sub    rsp,0x10
 221:	c7 45 fc 00 00 00 00 	mov    DWORD PTR [rbp-0x4],0x0
 228:	83 45 fc 01          	add    DWORD PTR [rbp-0x4],0x1
 22c:	48 b8 00 00 70 00 00 	movabs rax,0xffff800000700000
 233:	80 ff ff 
 236:	48 89 45 f0          	mov    QWORD PTR [rbp-0x10],rax
 23a:	8b 45 fc             	mov    eax,DWORD PTR [rbp-0x4]
 23d:	48 63 d0             	movsxd rdx,eax
 240:	48 8b 45 f0          	mov    rax,QWORD PTR [rbp-0x10]
 244:	48 89 10             	mov    QWORD PTR [rax],rdx
 247:	bf ff e0 f5 05       	mov    edi,0x5f5e0ff
 24c:	b8 00 00 00 00       	mov    eax,0x0
 251:	48 ba 00 00 00 00 00 	movabs rdx,0x0
 258:	00 00 00 
 25b:	ff d2                	call   rdx
 25d:	eb c9                	jmp    228 <InitWindowSystem+0xdf>

000000000000025f <ButtonOnClick>:
 25f:	55                   	push   rbp
 260:	48 89 e5             	mov    rbp,rsp
 263:	48 83 ec 10          	sub    rsp,0x10
 267:	48 89 7d f8          	mov    QWORD PTR [rbp-0x8],rdi
 26b:	89 75 f4             	mov    DWORD PTR [rbp-0xc],esi
 26e:	89 55 f0             	mov    DWORD PTR [rbp-0x10],edx
 271:	48 b8 00 00 00 00 00 	movabs rax,0x0
 278:	00 00 00 
 27b:	48 8b 00             	mov    rax,QWORD PTR [rax]
 27e:	48 be 00 00 00 00 00 	movabs rsi,0x0
 285:	00 00 00 
 288:	48 89 c7             	mov    rdi,rax
 28b:	48 b8 00 00 00 00 00 	movabs rax,0x0
 292:	00 00 00 
 295:	ff d0                	call   rax
 297:	c9                   	leave  
 298:	c3                   	ret    

0000000000000299 <DesktopWindow1>:
 299:	55                   	push   rbp
 29a:	48 89 e5             	mov    rbp,rsp
 29d:	53                   	push   rbx
 29e:	48 81 ec 88 00 00 00 	sub    rsp,0x88
 2a5:	48 c7 45 98 00 00 00 	mov    QWORD PTR [rbp-0x68],0x0
 2ac:	00 
 2ad:	48 c7 45 a0 00 00 00 	mov    QWORD PTR [rbp-0x60],0x0
 2b4:	00 
 2b5:	48 c7 45 a8 00 00 00 	mov    QWORD PTR [rbp-0x58],0x0
 2bc:	00 
 2bd:	48 c7 45 b0 00 00 00 	mov    QWORD PTR [rbp-0x50],0x0
 2c4:	00 
 2c5:	48 c7 85 78 ff ff ff 	mov    QWORD PTR [rbp-0x88],0x0
 2cc:	00 00 00 00 
 2d0:	48 c7 45 80 00 00 00 	mov    QWORD PTR [rbp-0x80],0x0
 2d7:	00 
 2d8:	48 c7 45 88 00 00 00 	mov    QWORD PTR [rbp-0x78],0x0
 2df:	00 
 2e0:	48 c7 45 90 00 00 00 	mov    QWORD PTR [rbp-0x70],0x0
 2e7:	00 
 2e8:	c7 45 ec 00 00 00 00 	mov    DWORD PTR [rbp-0x14],0x0
 2ef:	48 b8 00 00 00 00 00 	movabs rax,0x0
 2f6:	00 00 00 
 2f9:	48 8b 00             	mov    rax,QWORD PTR [rax]
 2fc:	49 b9 00 00 00 00 00 	movabs r9,0x0
 303:	00 00 00 
 306:	41 b8 d0 02 00 00    	mov    r8d,0x2d0
 30c:	b9 90 01 00 00       	mov    ecx,0x190
 311:	ba 32 00 00 00       	mov    edx,0x32
 316:	be 32 00 00 00       	mov    esi,0x32
 31b:	48 89 c7             	mov    rdi,rax
 31e:	48 b8 00 00 00 00 00 	movabs rax,0x0
 325:	00 00 00 
 328:	ff d0                	call   rax
 32a:	48 89 45 e0          	mov    QWORD PTR [rbp-0x20],rax
 32e:	b8 00 00 00 00       	mov    eax,0x0
 333:	48 ba 00 00 00 00 00 	movabs rdx,0x0
 33a:	00 00 00 
 33d:	ff d2                	call   rdx
 33f:	48 89 c2             	mov    rdx,rax
 342:	48 8b 45 e0          	mov    rax,QWORD PTR [rbp-0x20]
 346:	48 89 50 68          	mov    QWORD PTR [rax+0x68],rdx
 34a:	b9 23 00 00 00       	mov    ecx,0x23
 34f:	ba 64 00 00 00       	mov    edx,0x64
 354:	be 64 00 00 00       	mov    esi,0x64
 359:	bf 0a 00 00 00       	mov    edi,0xa
 35e:	48 b8 00 00 00 00 00 	movabs rax,0x0
 365:	00 00 00 
 368:	ff d0                	call   rax
 36a:	48 89 45 d8          	mov    QWORD PTR [rbp-0x28],rax
 36e:	48 8b 45 d8          	mov    rax,QWORD PTR [rbp-0x28]
 372:	48 bb 00 00 00 00 00 	movabs rbx,0x0
 379:	00 00 00 
 37c:	48 89 58 60          	mov    QWORD PTR [rax+0x60],rbx
 380:	48 8b 45 d8          	mov    rax,QWORD PTR [rbp-0x28]
 384:	48 bb 00 00 00 00 00 	movabs rbx,0x0
 38b:	00 00 00 
 38e:	48 89 58 78          	mov    QWORD PTR [rax+0x78],rbx
 392:	48 8b 55 d8          	mov    rdx,QWORD PTR [rbp-0x28]
 396:	48 8b 45 e0          	mov    rax,QWORD PTR [rbp-0x20]
 39a:	48 89 d6             	mov    rsi,rdx
 39d:	48 89 c7             	mov    rdi,rax
 3a0:	48 b8 00 00 00 00 00 	movabs rax,0x0
 3a7:	00 00 00 
 3aa:	ff d0                	call   rax
 3ac:	be 05 00 00 00       	mov    esi,0x5
 3b1:	bf 05 00 00 00       	mov    edi,0x5
 3b6:	48 b8 00 00 00 00 00 	movabs rax,0x0
 3bd:	00 00 00 
 3c0:	ff d0                	call   rax
 3c2:	48 89 45 d0          	mov    QWORD PTR [rbp-0x30],rax
 3c6:	48 8b 45 d0          	mov    rax,QWORD PTR [rbp-0x30]
 3ca:	48 bb 00 00 00 00 00 	movabs rbx,0x0
 3d1:	00 00 00 
 3d4:	48 89 58 60          	mov    QWORD PTR [rax+0x60],rbx
 3d8:	48 8b 55 d0          	mov    rdx,QWORD PTR [rbp-0x30]
 3dc:	48 8b 45 e0          	mov    rax,QWORD PTR [rbp-0x20]
 3e0:	48 89 d6             	mov    rsi,rdx
 3e3:	48 89 c7             	mov    rdi,rax
 3e6:	48 b8 00 00 00 00 00 	movabs rax,0x0
 3ed:	00 00 00 
 3f0:	ff d0                	call   rax
 3f2:	be 05 00 00 00       	mov    esi,0x5
 3f7:	bf 19 00 00 00       	mov    edi,0x19
 3fc:	48 b8 00 00 00 00 00 	movabs rax,0x0
 403:	00 00 00 
 406:	ff d0                	call   rax
 408:	48 89 45 c8          	mov    QWORD PTR [rbp-0x38],rax
 40c:	48 8b 45 e0          	mov    rax,QWORD PTR [rbp-0x20]
 410:	48 8b 40 68          	mov    rax,QWORD PTR [rax+0x68]
 414:	8b 80 b0 00 00 00    	mov    eax,DWORD PTR [rax+0xb0]
 41a:	48 8d 55 98          	lea    rdx,[rbp-0x68]
 41e:	be 0a 00 00 00       	mov    esi,0xa
 423:	89 c7                	mov    edi,eax
 425:	b8 00 00 00 00       	mov    eax,0x0
 42a:	48 b9 00 00 00 00 00 	movabs rcx,0x0
 431:	00 00 00 
 434:	ff d1                	call   rcx
 436:	48 8b 45 c8          	mov    rax,QWORD PTR [rbp-0x38]
 43a:	48 8d 55 98          	lea    rdx,[rbp-0x68]
 43e:	48 89 50 60          	mov    QWORD PTR [rax+0x60],rdx
 442:	48 8b 55 c8          	mov    rdx,QWORD PTR [rbp-0x38]
 446:	48 8b 45 e0          	mov    rax,QWORD PTR [rbp-0x20]
 44a:	48 89 d6             	mov    rsi,rdx
 44d:	48 89 c7             	mov    rdi,rax
 450:	48 b8 00 00 00 00 00 	movabs rax,0x0
 457:	00 00 00 
 45a:	ff d0                	call   rax
 45c:	be 0f 00 00 00       	mov    esi,0xf
 461:	bf 05 00 00 00       	mov    edi,0x5
 466:	48 b8 00 00 00 00 00 	movabs rax,0x0
 46d:	00 00 00 
 470:	ff d0                	call   rax
 472:	48 89 45 c0          	mov    QWORD PTR [rbp-0x40],rax
 476:	48 8b 45 c0          	mov    rax,QWORD PTR [rbp-0x40]
 47a:	48 bb 00 00 00 00 00 	movabs rbx,0x0
 481:	00 00 00 
 484:	48 89 58 60          	mov    QWORD PTR [rax+0x60],rbx
 488:	48 8b 55 c0          	mov    rdx,QWORD PTR [rbp-0x40]
 48c:	48 8b 45 e0          	mov    rax,QWORD PTR [rbp-0x20]
 490:	48 89 d6             	mov    rsi,rdx
 493:	48 89 c7             	mov    rdi,rax
 496:	48 b8 00 00 00 00 00 	movabs rax,0x0
 49d:	00 00 00 
 4a0:	ff d0                	call   rax
 4a2:	be 0f 00 00 00       	mov    esi,0xf
 4a7:	bf 73 00 00 00       	mov    edi,0x73
 4ac:	48 b8 00 00 00 00 00 	movabs rax,0x0
 4b3:	00 00 00 
 4b6:	ff d0                	call   rax
 4b8:	48 89 45 b8          	mov    QWORD PTR [rbp-0x48],rax
 4bc:	48 8b 45 b8          	mov    rax,QWORD PTR [rbp-0x48]
 4c0:	48 b9 00 00 00 00 00 	movabs rcx,0x0
 4c7:	00 00 00 
 4ca:	48 89 48 60          	mov    QWORD PTR [rax+0x60],rcx
 4ce:	48 8b 55 b8          	mov    rdx,QWORD PTR [rbp-0x48]
 4d2:	48 8b 45 e0          	mov    rax,QWORD PTR [rbp-0x20]
 4d6:	48 89 d6             	mov    rsi,rdx
 4d9:	48 89 c7             	mov    rdi,rax
 4dc:	48 b8 00 00 00 00 00 	movabs rax,0x0
 4e3:	00 00 00 
 4e6:	ff d0                	call   rax
 4e8:	b9 14 00 00 00       	mov    ecx,0x14
 4ed:	ba 64 00 00 00       	mov    edx,0x64
 4f2:	be 96 00 00 00       	mov    esi,0x96
 4f7:	bf 0a 00 00 00       	mov    edi,0xa
 4fc:	48 b8 00 00 00 00 00 	movabs rax,0x0
 503:	00 00 00 
 506:	ff d0                	call   rax
 508:	48 ba 00 00 00 00 00 	movabs rdx,0x0
 50f:	00 00 00 
 512:	48 89 02             	mov    QWORD PTR [rdx],rax
 515:	48 b8 00 00 00 00 00 	movabs rax,0x0
 51c:	00 00 00 
 51f:	48 8b 00             	mov    rax,QWORD PTR [rax]
 522:	48 bb 00 00 00 00 00 	movabs rbx,0x0
 529:	00 00 00 
 52c:	48 89 58 60          	mov    QWORD PTR [rax+0x60],rbx
 530:	48 b8 00 00 00 00 00 	movabs rax,0x0
 537:	00 00 00 
 53a:	48 8b 10             	mov    rdx,QWORD PTR [rax]
 53d:	48 8b 45 e0          	mov    rax,QWORD PTR [rbp-0x20]
 541:	48 89 d6             	mov    rsi,rdx
 544:	48 89 c7             	mov    rdi,rax
 547:	48 b8 00 00 00 00 00 	movabs rax,0x0
 54e:	00 00 00 
 551:	ff d0                	call   rax
 553:	83 45 ec 01          	add    DWORD PTR [rbp-0x14],0x1
 557:	48 8b 45 e0          	mov    rax,QWORD PTR [rbp-0x20]
 55b:	48 8b 40 68          	mov    rax,QWORD PTR [rax+0x68]
 55f:	48 8b 80 c0 00 00 00 	mov    rax,QWORD PTR [rax+0xc0]
 566:	48 8d 95 78 ff ff ff 	lea    rdx,[rbp-0x88]
 56d:	be 0a 00 00 00       	mov    esi,0xa
 572:	48 89 c7             	mov    rdi,rax
 575:	b8 00 00 00 00       	mov    eax,0x0
 57a:	48 b9 00 00 00 00 00 	movabs rcx,0x0
 581:	00 00 00 
 584:	ff d1                	call   rcx
 586:	48 8b 45 b8          	mov    rax,QWORD PTR [rbp-0x48]
 58a:	48 8d 95 78 ff ff ff 	lea    rdx,[rbp-0x88]
 591:	48 89 50 60          	mov    QWORD PTR [rax+0x60],rdx
 595:	bf ff e0 f5 05       	mov    edi,0x5f5e0ff
 59a:	b8 00 00 00 00       	mov    eax,0x0
 59f:	48 ba 00 00 00 00 00 	movabs rdx,0x0
 5a6:	00 00 00 
 5a9:	ff d2                	call   rdx
 5ab:	eb a6                	jmp    553 <InitWindowSystem+0x40a>

00000000000005ad <DesktopWindow2>:
 5ad:	55                   	push   rbp
 5ae:	48 89 e5             	mov    rbp,rsp
 5b1:	53                   	push   rbx
 5b2:	48 81 ec 88 00 00 00 	sub    rsp,0x88
 5b9:	48 c7 45 98 00 00 00 	mov    QWORD PTR [rbp-0x68],0x0
 5c0:	00 
 5c1:	48 c7 45 a0 00 00 00 	mov    QWORD PTR [rbp-0x60],0x0
 5c8:	00 
 5c9:	48 c7 45 a8 00 00 00 	mov    QWORD PTR [rbp-0x58],0x0
 5d0:	00 
 5d1:	48 c7 45 b0 00 00 00 	mov    QWORD PTR [rbp-0x50],0x0
 5d8:	00 
 5d9:	48 c7 85 78 ff ff ff 	mov    QWORD PTR [rbp-0x88],0x0
 5e0:	00 00 00 00 
 5e4:	48 c7 45 80 00 00 00 	mov    QWORD PTR [rbp-0x80],0x0
 5eb:	00 
 5ec:	48 c7 45 88 00 00 00 	mov    QWORD PTR [rbp-0x78],0x0
 5f3:	00 
 5f4:	48 c7 45 90 00 00 00 	mov    QWORD PTR [rbp-0x70],0x0
 5fb:	00 
 5fc:	c7 45 ec 00 00 00 00 	mov    DWORD PTR [rbp-0x14],0x0
 603:	48 b8 00 00 00 00 00 	movabs rax,0x0
 60a:	00 00 00 
 60d:	48 8b 00             	mov    rax,QWORD PTR [rax]
 610:	49 b9 00 00 00 00 00 	movabs r9,0x0
 617:	00 00 00 
 61a:	41 b8 d0 02 00 00    	mov    r8d,0x2d0
 620:	b9 90 01 00 00       	mov    ecx,0x190
 625:	ba c8 00 00 00       	mov    edx,0xc8
 62a:	be c8 00 00 00       	mov    esi,0xc8
 62f:	48 89 c7             	mov    rdi,rax
 632:	48 b8 00 00 00 00 00 	movabs rax,0x0
 639:	00 00 00 
 63c:	ff d0                	call   rax
 63e:	48 89 45 e0          	mov    QWORD PTR [rbp-0x20],rax
 642:	b8 00 00 00 00       	mov    eax,0x0
 647:	48 ba 00 00 00 00 00 	movabs rdx,0x0
 64e:	00 00 00 
 651:	ff d2                	call   rdx
 653:	48 89 c2             	mov    rdx,rax
 656:	48 8b 45 e0          	mov    rax,QWORD PTR [rbp-0x20]
 65a:	48 89 50 68          	mov    QWORD PTR [rax+0x68],rdx
 65e:	b9 23 00 00 00       	mov    ecx,0x23
 663:	ba 64 00 00 00       	mov    edx,0x64
 668:	be 64 00 00 00       	mov    esi,0x64
 66d:	bf 0a 00 00 00       	mov    edi,0xa
 672:	48 b8 00 00 00 00 00 	movabs rax,0x0
 679:	00 00 00 
 67c:	ff d0                	call   rax
 67e:	48 89 45 d8          	mov    QWORD PTR [rbp-0x28],rax
 682:	48 8b 45 d8          	mov    rax,QWORD PTR [rbp-0x28]
 686:	48 bb 00 00 00 00 00 	movabs rbx,0x0
 68d:	00 00 00 
 690:	48 89 58 60          	mov    QWORD PTR [rax+0x60],rbx
 694:	48 8b 55 d8          	mov    rdx,QWORD PTR [rbp-0x28]
 698:	48 8b 45 e0          	mov    rax,QWORD PTR [rbp-0x20]
 69c:	48 89 d6             	mov    rsi,rdx
 69f:	48 89 c7             	mov    rdi,rax
 6a2:	48 b8 00 00 00 00 00 	movabs rax,0x0
 6a9:	00 00 00 
 6ac:	ff d0                	call   rax
 6ae:	be 05 00 00 00       	mov    esi,0x5
 6b3:	bf 05 00 00 00       	mov    edi,0x5
 6b8:	48 b8 00 00 00 00 00 	movabs rax,0x0
 6bf:	00 00 00 
 6c2:	ff d0                	call   rax
 6c4:	48 89 45 d0          	mov    QWORD PTR [rbp-0x30],rax
 6c8:	48 8b 45 d0          	mov    rax,QWORD PTR [rbp-0x30]
 6cc:	48 bb 00 00 00 00 00 	movabs rbx,0x0
 6d3:	00 00 00 
 6d6:	48 89 58 60          	mov    QWORD PTR [rax+0x60],rbx
 6da:	48 8b 55 d0          	mov    rdx,QWORD PTR [rbp-0x30]
 6de:	48 8b 45 e0          	mov    rax,QWORD PTR [rbp-0x20]
 6e2:	48 89 d6             	mov    rsi,rdx
 6e5:	48 89 c7             	mov    rdi,rax
 6e8:	48 b8 00 00 00 00 00 	movabs rax,0x0
 6ef:	00 00 00 
 6f2:	ff d0                	call   rax
 6f4:	be 05 00 00 00       	mov    esi,0x5
 6f9:	bf 19 00 00 00       	mov    edi,0x19
 6fe:	48 b8 00 00 00 00 00 	movabs rax,0x0
 705:	00 00 00 
 708:	ff d0                	call   rax
 70a:	48 89 45 c8          	mov    QWORD PTR [rbp-0x38],rax
 70e:	48 8b 45 e0          	mov    rax,QWORD PTR [rbp-0x20]
 712:	48 8b 40 68          	mov    rax,QWORD PTR [rax+0x68]
 716:	8b 80 b0 00 00 00    	mov    eax,DWORD PTR [rax+0xb0]
 71c:	48 8d 55 98          	lea    rdx,[rbp-0x68]
 720:	be 0a 00 00 00       	mov    esi,0xa
 725:	89 c7                	mov    edi,eax
 727:	b8 00 00 00 00       	mov    eax,0x0
 72c:	48 b9 00 00 00 00 00 	movabs rcx,0x0
 733:	00 00 00 
 736:	ff d1                	call   rcx
 738:	48 8b 45 c8          	mov    rax,QWORD PTR [rbp-0x38]
 73c:	48 8d 55 98          	lea    rdx,[rbp-0x68]
 740:	48 89 50 60          	mov    QWORD PTR [rax+0x60],rdx
 744:	48 8b 55 c8          	mov    rdx,QWORD PTR [rbp-0x38]
 748:	48 8b 45 e0          	mov    rax,QWORD PTR [rbp-0x20]
 74c:	48 89 d6             	mov    rsi,rdx
 74f:	48 89 c7             	mov    rdi,rax
 752:	48 b8 00 00 00 00 00 	movabs rax,0x0
 759:	00 00 00 
 75c:	ff d0                	call   rax
 75e:	be 0f 00 00 00       	mov    esi,0xf
 763:	bf 05 00 00 00       	mov    edi,0x5
 768:	48 b8 00 00 00 00 00 	movabs rax,0x0
 76f:	00 00 00 
 772:	ff d0                	call   rax
 774:	48 89 45 c0          	mov    QWORD PTR [rbp-0x40],rax
 778:	48 8b 45 c0          	mov    rax,QWORD PTR [rbp-0x40]
 77c:	48 bb 00 00 00 00 00 	movabs rbx,0x0
 783:	00 00 00 
 786:	48 89 58 60          	mov    QWORD PTR [rax+0x60],rbx
 78a:	48 8b 55 c0          	mov    rdx,QWORD PTR [rbp-0x40]
 78e:	48 8b 45 e0          	mov    rax,QWORD PTR [rbp-0x20]
 792:	48 89 d6             	mov    rsi,rdx
 795:	48 89 c7             	mov    rdi,rax
 798:	48 b8 00 00 00 00 00 	movabs rax,0x0
 79f:	00 00 00 
 7a2:	ff d0                	call   rax
 7a4:	be 0f 00 00 00       	mov    esi,0xf
 7a9:	bf 73 00 00 00       	mov    edi,0x73
 7ae:	48 b8 00 00 00 00 00 	movabs rax,0x0
 7b5:	00 00 00 
 7b8:	ff d0                	call   rax
 7ba:	48 89 45 b8          	mov    QWORD PTR [rbp-0x48],rax
 7be:	48 8b 45 b8          	mov    rax,QWORD PTR [rbp-0x48]
 7c2:	48 b9 00 00 00 00 00 	movabs rcx,0x0
 7c9:	00 00 00 
 7cc:	48 89 48 60          	mov    QWORD PTR [rax+0x60],rcx
 7d0:	48 8b 55 b8          	mov    rdx,QWORD PTR [rbp-0x48]
 7d4:	48 8b 45 e0          	mov    rax,QWORD PTR [rbp-0x20]
 7d8:	48 89 d6             	mov    rsi,rdx
 7db:	48 89 c7             	mov    rdi,rax
 7de:	48 b8 00 00 00 00 00 	movabs rax,0x0
 7e5:	00 00 00 
 7e8:	ff d0                	call   rax
 7ea:	83 45 ec 01          	add    DWORD PTR [rbp-0x14],0x1
 7ee:	48 8b 45 e0          	mov    rax,QWORD PTR [rbp-0x20]
 7f2:	48 8b 40 68          	mov    rax,QWORD PTR [rax+0x68]
 7f6:	48 8b 80 c0 00 00 00 	mov    rax,QWORD PTR [rax+0xc0]
 7fd:	48 8d 95 78 ff ff ff 	lea    rdx,[rbp-0x88]
 804:	be 0a 00 00 00       	mov    esi,0xa
 809:	48 89 c7             	mov    rdi,rax
 80c:	b8 00 00 00 00       	mov    eax,0x0
 811:	48 b9 00 00 00 00 00 	movabs rcx,0x0
 818:	00 00 00 
 81b:	ff d1                	call   rcx
 81d:	48 8b 45 b8          	mov    rax,QWORD PTR [rbp-0x48]
 821:	48 8d 95 78 ff ff ff 	lea    rdx,[rbp-0x88]
 828:	48 89 50 60          	mov    QWORD PTR [rax+0x60],rdx
 82c:	bf ff e0 f5 05       	mov    edi,0x5f5e0ff
 831:	b8 00 00 00 00       	mov    eax,0x0
 836:	48 ba 00 00 00 00 00 	movabs rdx,0x0
 83d:	00 00 00 
 840:	ff d2                	call   rdx
 842:	eb a6                	jmp    7ea <InitWindowSystem+0x6a1>

0000000000000844 <DesktopWindow3>:
 844:	55                   	push   rbp
 845:	48 89 e5             	mov    rbp,rsp
 848:	53                   	push   rbx
 849:	48 81 ec 88 00 00 00 	sub    rsp,0x88
 850:	48 c7 45 90 00 00 00 	mov    QWORD PTR [rbp-0x70],0x0
 857:	00 
 858:	48 c7 45 98 00 00 00 	mov    QWORD PTR [rbp-0x68],0x0
 85f:	00 
 860:	48 c7 45 a0 00 00 00 	mov    QWORD PTR [rbp-0x60],0x0
 867:	00 
 868:	48 c7 45 a8 00 00 00 	mov    QWORD PTR [rbp-0x58],0x0
 86f:	00 
 870:	48 c7 85 70 ff ff ff 	mov    QWORD PTR [rbp-0x90],0x0
 877:	00 00 00 00 
 87b:	48 c7 85 78 ff ff ff 	mov    QWORD PTR [rbp-0x88],0x0
 882:	00 00 00 00 
 886:	48 c7 45 80 00 00 00 	mov    QWORD PTR [rbp-0x80],0x0
 88d:	00 
 88e:	48 c7 45 88 00 00 00 	mov    QWORD PTR [rbp-0x78],0x0
 895:	00 
 896:	c7 45 ec 00 00 00 00 	mov    DWORD PTR [rbp-0x14],0x0
 89d:	48 b8 00 00 00 00 00 	movabs rax,0x0
 8a4:	00 00 00 
 8a7:	48 8b 00             	mov    rax,QWORD PTR [rax]
 8aa:	49 b9 00 00 00 00 00 	movabs r9,0x0
 8b1:	00 00 00 
 8b4:	41 b8 d0 02 00 00    	mov    r8d,0x2d0
 8ba:	b9 90 01 00 00       	mov    ecx,0x190
 8bf:	ba 2c 01 00 00       	mov    edx,0x12c
 8c4:	be 2c 01 00 00       	mov    esi,0x12c
 8c9:	48 89 c7             	mov    rdi,rax
 8cc:	48 b8 00 00 00 00 00 	movabs rax,0x0
 8d3:	00 00 00 
 8d6:	ff d0                	call   rax
 8d8:	48 89 45 e0          	mov    QWORD PTR [rbp-0x20],rax
 8dc:	b8 00 00 00 00       	mov    eax,0x0
 8e1:	48 ba 00 00 00 00 00 	movabs rdx,0x0
 8e8:	00 00 00 
 8eb:	ff d2                	call   rdx
 8ed:	48 89 c2             	mov    rdx,rax
 8f0:	48 8b 45 e0          	mov    rax,QWORD PTR [rbp-0x20]
 8f4:	48 89 50 68          	mov    QWORD PTR [rax+0x68],rdx
 8f8:	b9 23 00 00 00       	mov    ecx,0x23
 8fd:	ba 64 00 00 00       	mov    edx,0x64
 902:	be 64 00 00 00       	mov    esi,0x64
 907:	bf 0a 00 00 00       	mov    edi,0xa
 90c:	48 b8 00 00 00 00 00 	movabs rax,0x0
 913:	00 00 00 
 916:	ff d0                	call   rax
 918:	48 89 45 d8          	mov    QWORD PTR [rbp-0x28],rax
 91c:	48 8b 45 d8          	mov    rax,QWORD PTR [rbp-0x28]
 920:	48 bb 00 00 00 00 00 	movabs rbx,0x0
 927:	00 00 00 
 92a:	48 89 58 60          	mov    QWORD PTR [rax+0x60],rbx
 92e:	48 8b 55 d8          	mov    rdx,QWORD PTR [rbp-0x28]
 932:	48 8b 45 e0          	mov    rax,QWORD PTR [rbp-0x20]
 936:	48 89 d6             	mov    rsi,rdx
 939:	48 89 c7             	mov    rdi,rax
 93c:	48 b8 00 00 00 00 00 	movabs rax,0x0
 943:	00 00 00 
 946:	ff d0                	call   rax
 948:	be 05 00 00 00       	mov    esi,0x5
 94d:	bf 05 00 00 00       	mov    edi,0x5
 952:	48 b8 00 00 00 00 00 	movabs rax,0x0
 959:	00 00 00 
 95c:	ff d0                	call   rax
 95e:	48 89 45 d0          	mov    QWORD PTR [rbp-0x30],rax
 962:	48 8b 45 d0          	mov    rax,QWORD PTR [rbp-0x30]
 966:	48 bb 00 00 00 00 00 	movabs rbx,0x0
 96d:	00 00 00 
 970:	48 89 58 60          	mov    QWORD PTR [rax+0x60],rbx
 974:	48 8b 55 d0          	mov    rdx,QWORD PTR [rbp-0x30]
 978:	48 8b 45 e0          	mov    rax,QWORD PTR [rbp-0x20]
 97c:	48 89 d6             	mov    rsi,rdx
 97f:	48 89 c7             	mov    rdi,rax
 982:	48 b8 00 00 00 00 00 	movabs rax,0x0
 989:	00 00 00 
 98c:	ff d0                	call   rax
 98e:	be 05 00 00 00       	mov    esi,0x5
 993:	bf 19 00 00 00       	mov    edi,0x19
 998:	48 b8 00 00 00 00 00 	movabs rax,0x0
 99f:	00 00 00 
 9a2:	ff d0                	call   rax
 9a4:	48 89 45 c8          	mov    QWORD PTR [rbp-0x38],rax
 9a8:	48 8b 45 e0          	mov    rax,QWORD PTR [rbp-0x20]
 9ac:	48 8b 40 68          	mov    rax,QWORD PTR [rax+0x68]
 9b0:	8b 80 b0 00 00 00    	mov    eax,DWORD PTR [rax+0xb0]
 9b6:	48 8d 55 90          	lea    rdx,[rbp-0x70]
 9ba:	be 0a 00 00 00       	mov    esi,0xa
 9bf:	89 c7                	mov    edi,eax
 9c1:	b8 00 00 00 00       	mov    eax,0x0
 9c6:	48 b9 00 00 00 00 00 	movabs rcx,0x0
 9cd:	00 00 00 
 9d0:	ff d1                	call   rcx
 9d2:	48 8b 45 c8          	mov    rax,QWORD PTR [rbp-0x38]
 9d6:	48 8d 55 90          	lea    rdx,[rbp-0x70]
 9da:	48 89 50 60          	mov    QWORD PTR [rax+0x60],rdx
 9de:	48 8b 55 c8          	mov    rdx,QWORD PTR [rbp-0x38]
 9e2:	48 8b 45 e0          	mov    rax,QWORD PTR [rbp-0x20]
 9e6:	48 89 d6             	mov    rsi,rdx
 9e9:	48 89 c7             	mov    rdi,rax
 9ec:	48 b8 00 00 00 00 00 	movabs rax,0x0
 9f3:	00 00 00 
 9f6:	ff d0                	call   rax
 9f8:	be 0f 00 00 00       	mov    esi,0xf
 9fd:	bf 05 00 00 00       	mov    edi,0x5
 a02:	48 b8 00 00 00 00 00 	movabs rax,0x0
 a09:	00 00 00 
 a0c:	ff d0                	call   rax
 a0e:	48 89 45 c0          	mov    QWORD PTR [rbp-0x40],rax
 a12:	48 8b 45 c0          	mov    rax,QWORD PTR [rbp-0x40]
 a16:	48 bb 00 00 00 00 00 	movabs rbx,0x0
 a1d:	00 00 00 
 a20:	48 89 58 60          	mov    QWORD PTR [rax+0x60],rbx
 a24:	48 8b 55 c0          	mov    rdx,QWORD PTR [rbp-0x40]
 a28:	48 8b 45 e0          	mov    rax,QWORD PTR [rbp-0x20]
 a2c:	48 89 d6             	mov    rsi,rdx
 a2f:	48 89 c7             	mov    rdi,rax
 a32:	48 b8 00 00 00 00 00 	movabs rax,0x0
 a39:	00 00 00 
 a3c:	ff d0                	call   rax
 a3e:	be 0f 00 00 00       	mov    esi,0xf
 a43:	bf 73 00 00 00       	mov    edi,0x73
 a48:	48 b8 00 00 00 00 00 	movabs rax,0x0
 a4f:	00 00 00 
 a52:	ff d0                	call   rax
 a54:	48 89 45 b8          	mov    QWORD PTR [rbp-0x48],rax
 a58:	48 8b 45 b8          	mov    rax,QWORD PTR [rbp-0x48]
 a5c:	48 b9 00 00 00 00 00 	movabs rcx,0x0
 a63:	00 00 00 
 a66:	48 89 48 60          	mov    QWORD PTR [rax+0x60],rcx
 a6a:	48 8b 55 b8          	mov    rdx,QWORD PTR [rbp-0x48]
 a6e:	48 8b 45 e0          	mov    rax,QWORD PTR [rbp-0x20]
 a72:	48 89 d6             	mov    rsi,rdx
 a75:	48 89 c7             	mov    rdi,rax
 a78:	48 b8 00 00 00 00 00 	movabs rax,0x0
 a7f:	00 00 00 
 a82:	ff d0                	call   rax
 a84:	83 45 ec 01          	add    DWORD PTR [rbp-0x14],0x1
 a88:	48 b8 00 00 70 00 00 	movabs rax,0xffff800000700000
 a8f:	80 ff ff 
 a92:	48 89 45 b0          	mov    QWORD PTR [rbp-0x50],rax
 a96:	8b 45 ec             	mov    eax,DWORD PTR [rbp-0x14]
 a99:	48 63 d0             	movsxd rdx,eax
 a9c:	48 8b 45 b0          	mov    rax,QWORD PTR [rbp-0x50]
 aa0:	48 89 10             	mov    QWORD PTR [rax],rdx
 aa3:	48 8b 45 e0          	mov    rax,QWORD PTR [rbp-0x20]
 aa7:	48 8b 40 68          	mov    rax,QWORD PTR [rax+0x68]
 aab:	48 8b 80 c0 00 00 00 	mov    rax,QWORD PTR [rax+0xc0]
 ab2:	48 8d 95 70 ff ff ff 	lea    rdx,[rbp-0x90]
 ab9:	be 0a 00 00 00       	mov    esi,0xa
 abe:	48 89 c7             	mov    rdi,rax
 ac1:	b8 00 00 00 00       	mov    eax,0x0
 ac6:	48 b9 00 00 00 00 00 	movabs rcx,0x0
 acd:	00 00 00 
 ad0:	ff d1                	call   rcx
 ad2:	48 8b 45 b8          	mov    rax,QWORD PTR [rbp-0x48]
 ad6:	48 8d 95 70 ff ff ff 	lea    rdx,[rbp-0x90]
 add:	48 89 50 60          	mov    QWORD PTR [rax+0x60],rdx
 ae1:	bf ff e0 f5 05       	mov    edi,0x5f5e0ff
 ae6:	b8 00 00 00 00       	mov    eax,0x0
 aeb:	48 ba 00 00 00 00 00 	movabs rdx,0x0
 af2:	00 00 00 
 af5:	ff d2                	call   rdx
 af7:	eb 8b                	jmp    a84 <InitWindowSystem+0x93b>

0000000000000af9 <MouseHandler>:
 af9:	55                   	push   rbp
 afa:	48 89 e5             	mov    rbp,rsp
 afd:	48 83 ec 20          	sub    rsp,0x20
 b01:	c7 45 fc 32 00 00 00 	mov    DWORD PTR [rbp-0x4],0x32
 b08:	c7 45 f8 32 00 00 00 	mov    DWORD PTR [rbp-0x8],0x32
 b0f:	c7 45 f4 00 00 00 00 	mov    DWORD PTR [rbp-0xc],0x0
 b16:	c7 45 f0 00 00 00 00 	mov    DWORD PTR [rbp-0x10],0x0
 b1d:	48 b8 00 00 00 00 00 	movabs rax,0x0
 b24:	00 00 00 
 b27:	48 8b 00             	mov    rax,QWORD PTR [rax]
 b2a:	ba 00 00 00 00       	mov    edx,0x0
 b2f:	be 00 00 00 00       	mov    esi,0x0
 b34:	48 89 c7             	mov    rdi,rax
 b37:	48 b8 00 00 00 00 00 	movabs rax,0x0
 b3e:	00 00 00 
 b41:	ff d0                	call   rax
 b43:	b8 00 00 00 00       	mov    eax,0x0
 b48:	48 ba 00 00 00 00 00 	movabs rdx,0x0
 b4f:	00 00 00 
 b52:	ff d2                	call   rdx
 b54:	88 45 ef             	mov    BYTE PTR [rbp-0x11],al
 b57:	0f be 45 ef          	movsx  eax,BYTE PTR [rbp-0x11]
 b5b:	89 c7                	mov    edi,eax
 b5d:	48 b8 00 00 00 00 00 	movabs rax,0x0
 b64:	00 00 00 
 b67:	ff d0                	call   rax
 b69:	88 45 ef             	mov    BYTE PTR [rbp-0x11],al
 b6c:	80 7d ef 61          	cmp    BYTE PTR [rbp-0x11],0x61
 b70:	75 09                	jne    b7b <InitWindowSystem+0xa32>
 b72:	83 6d fc 01          	sub    DWORD PTR [rbp-0x4],0x1
 b76:	e9 52 01 00 00       	jmp    ccd <InitWindowSystem+0xb84>
 b7b:	80 7d ef 6a          	cmp    BYTE PTR [rbp-0x11],0x6a
 b7f:	75 09                	jne    b8a <InitWindowSystem+0xa41>
 b81:	83 6d fc 0a          	sub    DWORD PTR [rbp-0x4],0xa
 b85:	e9 43 01 00 00       	jmp    ccd <InitWindowSystem+0xb84>
 b8a:	80 7d ef 66          	cmp    BYTE PTR [rbp-0x11],0x66
 b8e:	75 09                	jne    b99 <InitWindowSystem+0xa50>
 b90:	83 45 fc 01          	add    DWORD PTR [rbp-0x4],0x1
 b94:	e9 34 01 00 00       	jmp    ccd <InitWindowSystem+0xb84>
 b99:	80 7d ef 6c          	cmp    BYTE PTR [rbp-0x11],0x6c
 b9d:	75 09                	jne    ba8 <InitWindowSystem+0xa5f>
 b9f:	83 45 fc 0a          	add    DWORD PTR [rbp-0x4],0xa
 ba3:	e9 25 01 00 00       	jmp    ccd <InitWindowSystem+0xb84>
 ba8:	80 7d ef 65          	cmp    BYTE PTR [rbp-0x11],0x65
 bac:	75 09                	jne    bb7 <InitWindowSystem+0xa6e>
 bae:	83 6d f8 01          	sub    DWORD PTR [rbp-0x8],0x1
 bb2:	e9 16 01 00 00       	jmp    ccd <InitWindowSystem+0xb84>
 bb7:	80 7d ef 69          	cmp    BYTE PTR [rbp-0x11],0x69
 bbb:	75 09                	jne    bc6 <InitWindowSystem+0xa7d>
 bbd:	83 6d f8 0a          	sub    DWORD PTR [rbp-0x8],0xa
 bc1:	e9 07 01 00 00       	jmp    ccd <InitWindowSystem+0xb84>
 bc6:	80 7d ef 78          	cmp    BYTE PTR [rbp-0x11],0x78
 bca:	75 09                	jne    bd5 <InitWindowSystem+0xa8c>
 bcc:	83 45 f8 01          	add    DWORD PTR [rbp-0x8],0x1
 bd0:	e9 f8 00 00 00       	jmp    ccd <InitWindowSystem+0xb84>
 bd5:	80 7d ef 6d          	cmp    BYTE PTR [rbp-0x11],0x6d
 bd9:	75 09                	jne    be4 <InitWindowSystem+0xa9b>
 bdb:	83 45 f8 0a          	add    DWORD PTR [rbp-0x8],0xa
 bdf:	e9 e9 00 00 00       	jmp    ccd <InitWindowSystem+0xb84>
 be4:	80 7d ef 20          	cmp    BYTE PTR [rbp-0x11],0x20
 be8:	75 0c                	jne    bf6 <InitWindowSystem+0xaad>
 bea:	c7 45 f4 01 00 00 00 	mov    DWORD PTR [rbp-0xc],0x1
 bf1:	e9 d7 00 00 00       	jmp    ccd <InitWindowSystem+0xb84>
 bf6:	80 7d ef 41          	cmp    BYTE PTR [rbp-0x11],0x41
 bfa:	75 17                	jne    c13 <InitWindowSystem+0xaca>
 bfc:	83 6d fc 01          	sub    DWORD PTR [rbp-0x4],0x1
 c00:	c7 45 f4 01 00 00 00 	mov    DWORD PTR [rbp-0xc],0x1
 c07:	c7 45 f0 01 00 00 00 	mov    DWORD PTR [rbp-0x10],0x1
 c0e:	e9 ba 00 00 00       	jmp    ccd <InitWindowSystem+0xb84>
 c13:	80 7d ef 4a          	cmp    BYTE PTR [rbp-0x11],0x4a
 c17:	75 17                	jne    c30 <InitWindowSystem+0xae7>
 c19:	83 6d fc 0a          	sub    DWORD PTR [rbp-0x4],0xa
 c1d:	c7 45 f4 01 00 00 00 	mov    DWORD PTR [rbp-0xc],0x1
 c24:	c7 45 f0 01 00 00 00 	mov    DWORD PTR [rbp-0x10],0x1
 c2b:	e9 9d 00 00 00       	jmp    ccd <InitWindowSystem+0xb84>
 c30:	80 7d ef 46          	cmp    BYTE PTR [rbp-0x11],0x46
 c34:	75 17                	jne    c4d <InitWindowSystem+0xb04>
 c36:	83 45 fc 01          	add    DWORD PTR [rbp-0x4],0x1
 c3a:	c7 45 f4 01 00 00 00 	mov    DWORD PTR [rbp-0xc],0x1
 c41:	c7 45 f0 01 00 00 00 	mov    DWORD PTR [rbp-0x10],0x1
 c48:	e9 80 00 00 00       	jmp    ccd <InitWindowSystem+0xb84>
 c4d:	80 7d ef 4c          	cmp    BYTE PTR [rbp-0x11],0x4c
 c51:	75 14                	jne    c67 <InitWindowSystem+0xb1e>
 c53:	83 45 fc 0a          	add    DWORD PTR [rbp-0x4],0xa
 c57:	c7 45 f4 01 00 00 00 	mov    DWORD PTR [rbp-0xc],0x1
 c5e:	c7 45 f0 01 00 00 00 	mov    DWORD PTR [rbp-0x10],0x1
 c65:	eb 66                	jmp    ccd <InitWindowSystem+0xb84>
 c67:	80 7d ef 45          	cmp    BYTE PTR [rbp-0x11],0x45
 c6b:	75 14                	jne    c81 <InitWindowSystem+0xb38>
 c6d:	83 6d f8 01          	sub    DWORD PTR [rbp-0x8],0x1
 c71:	c7 45 f4 01 00 00 00 	mov    DWORD PTR [rbp-0xc],0x1
 c78:	c7 45 f0 01 00 00 00 	mov    DWORD PTR [rbp-0x10],0x1
 c7f:	eb 4c                	jmp    ccd <InitWindowSystem+0xb84>
 c81:	80 7d ef 49          	cmp    BYTE PTR [rbp-0x11],0x49
 c85:	75 14                	jne    c9b <InitWindowSystem+0xb52>
 c87:	83 6d f8 0a          	sub    DWORD PTR [rbp-0x8],0xa
 c8b:	c7 45 f4 01 00 00 00 	mov    DWORD PTR [rbp-0xc],0x1
 c92:	c7 45 f0 01 00 00 00 	mov    DWORD PTR [rbp-0x10],0x1
 c99:	eb 32                	jmp    ccd <InitWindowSystem+0xb84>
 c9b:	80 7d ef 58          	cmp    BYTE PTR [rbp-0x11],0x58
 c9f:	75 14                	jne    cb5 <InitWindowSystem+0xb6c>
 ca1:	83 45 f8 01          	add    DWORD PTR [rbp-0x8],0x1
 ca5:	c7 45 f4 01 00 00 00 	mov    DWORD PTR [rbp-0xc],0x1
 cac:	c7 45 f0 01 00 00 00 	mov    DWORD PTR [rbp-0x10],0x1
 cb3:	eb 18                	jmp    ccd <InitWindowSystem+0xb84>
 cb5:	80 7d ef 4d          	cmp    BYTE PTR [rbp-0x11],0x4d
 cb9:	75 12                	jne    ccd <InitWindowSystem+0xb84>
 cbb:	83 45 f8 0a          	add    DWORD PTR [rbp-0x8],0xa
 cbf:	c7 45 f4 01 00 00 00 	mov    DWORD PTR [rbp-0xc],0x1
 cc6:	c7 45 f0 01 00 00 00 	mov    DWORD PTR [rbp-0x10],0x1
 ccd:	83 7d fc 00          	cmp    DWORD PTR [rbp-0x4],0x0
 cd1:	79 07                	jns    cda <InitWindowSystem+0xb91>
 cd3:	c7 45 fc 00 00 00 00 	mov    DWORD PTR [rbp-0x4],0x0
 cda:	83 7d f8 00          	cmp    DWORD PTR [rbp-0x8],0x0
 cde:	79 07                	jns    ce7 <InitWindowSystem+0xb9e>
 ce0:	c7 45 f8 00 00 00 00 	mov    DWORD PTR [rbp-0x8],0x0
 ce7:	81 7d fc f5 04 00 00 	cmp    DWORD PTR [rbp-0x4],0x4f5
 cee:	7e 07                	jle    cf7 <InitWindowSystem+0xbae>
 cf0:	c7 45 fc f5 04 00 00 	mov    DWORD PTR [rbp-0x4],0x4f5
 cf7:	81 7d f8 fb 03 00 00 	cmp    DWORD PTR [rbp-0x8],0x3fb
 cfe:	7e 07                	jle    d07 <InitWindowSystem+0xbbe>
 d00:	c7 45 f8 fb 03 00 00 	mov    DWORD PTR [rbp-0x8],0x3fb
 d07:	48 b8 00 00 00 00 00 	movabs rax,0x0
 d0e:	00 00 00 
 d11:	48 8b 00             	mov    rax,QWORD PTR [rax]
 d14:	8b 7d f0             	mov    edi,DWORD PTR [rbp-0x10]
 d17:	8b 4d f4             	mov    ecx,DWORD PTR [rbp-0xc]
 d1a:	8b 55 f8             	mov    edx,DWORD PTR [rbp-0x8]
 d1d:	8b 75 fc             	mov    esi,DWORD PTR [rbp-0x4]
 d20:	41 89 f8             	mov    r8d,edi
 d23:	48 89 c7             	mov    rdi,rax
 d26:	48 b8 00 00 00 00 00 	movabs rax,0x0
 d2d:	00 00 00 
 d30:	ff d0                	call   rax
 d32:	c7 45 f4 00 00 00 00 	mov    DWORD PTR [rbp-0xc],0x0
 d39:	c7 45 f0 00 00 00 00 	mov    DWORD PTR [rbp-0x10],0x0
 d40:	8b 45 fc             	mov    eax,DWORD PTR [rbp-0x4]
 d43:	be 10 00 00 00       	mov    esi,0x10
 d48:	89 c7                	mov    edi,eax
 d4a:	b8 00 00 00 00       	mov    eax,0x0
 d4f:	48 ba 00 00 00 00 00 	movabs rdx,0x0
 d56:	00 00 00 
 d59:	ff d2                	call   rdx
 d5b:	48 bf 00 00 00 00 00 	movabs rdi,0x0
 d62:	00 00 00 
 d65:	48 b8 00 00 00 00 00 	movabs rax,0x0
 d6c:	00 00 00 
 d6f:	ff d0                	call   rax
 d71:	8b 45 f8             	mov    eax,DWORD PTR [rbp-0x8]
 d74:	be 10 00 00 00       	mov    esi,0x10
 d79:	89 c7                	mov    edi,eax
 d7b:	b8 00 00 00 00       	mov    eax,0x0
 d80:	48 ba 00 00 00 00 00 	movabs rdx,0x0
 d87:	00 00 00 
 d8a:	ff d2                	call   rdx
 d8c:	48 bf 00 00 00 00 00 	movabs rdi,0x0
 d93:	00 00 00 
 d96:	48 b8 00 00 00 00 00 	movabs rax,0x0
 d9d:	00 00 00 
 da0:	ff d0                	call   rax
 da2:	e9 9c fd ff ff       	jmp    b43 <InitWindowSystem+0x9fa>

0000000000000da7 <CreateTasksVGA>:
 da7:	55                   	push   rbp
 da8:	48 89 e5             	mov    rbp,rsp
 dab:	48 ba 00 00 10 01 00 	movabs rdx,0xffff800001100000
 db2:	80 ff ff 
 db5:	be 01 00 00 00       	mov    esi,0x1
 dba:	48 bf 00 00 00 00 00 	movabs rdi,0x0
 dc1:	00 00 00 
 dc4:	48 b8 00 00 00 00 00 	movabs rax,0x0
 dcb:	00 00 00 
 dce:	ff d0                	call   rax
 dd0:	48 b9 00 00 02 00 00 	movabs rcx,0xffff800000020000
 dd7:	80 ff ff 
 dda:	48 ba 00 00 20 01 00 	movabs rdx,0xffff800001200000
 de1:	80 ff ff 
 de4:	be 02 00 00 00       	mov    esi,0x2
 de9:	48 bf 00 00 00 00 00 	movabs rdi,0x0
 df0:	00 00 00 
 df3:	48 b8 00 00 00 00 00 	movabs rax,0x0
 dfa:	00 00 00 
 dfd:	ff d0                	call   rax
 dff:	48 b9 00 00 03 00 00 	movabs rcx,0xffff800000030000
 e06:	80 ff ff 
 e09:	48 ba 00 00 30 01 00 	movabs rdx,0xffff800001300000
 e10:	80 ff ff 
 e13:	be 03 00 00 00       	mov    esi,0x3
 e18:	48 bf 00 00 00 00 00 	movabs rdi,0x0
 e1f:	00 00 00 
 e22:	48 b8 00 00 00 00 00 	movabs rax,0x0
 e29:	00 00 00 
 e2c:	ff d0                	call   rax
 e2e:	48 b9 00 00 04 00 00 	movabs rcx,0xffff800000040000
 e35:	80 ff ff 
 e38:	48 ba 00 00 40 01 00 	movabs rdx,0xffff800001400000
 e3f:	80 ff ff 
 e42:	be 04 00 00 00       	mov    esi,0x4
 e47:	48 bf 00 00 00 00 00 	movabs rdi,0x0
 e4e:	00 00 00 
 e51:	48 b8 00 00 00 00 00 	movabs rax,0x0
 e58:	00 00 00 
 e5b:	ff d0                	call   rax
 e5d:	5d                   	pop    rbp
 e5e:	c3                   	ret    

0000000000000e5f <CreateTasks>:
 e5f:	55                   	push   rbp
 e60:	48 89 e5             	mov    rbp,rsp
 e63:	48 ba 00 00 10 01 00 	movabs rdx,0xffff800001100000
 e6a:	80 ff ff 
 e6d:	be 01 00 00 00       	mov    esi,0x1
 e72:	48 bf 00 00 00 00 00 	movabs rdi,0x0
 e79:	00 00 00 
 e7c:	48 b8 00 00 00 00 00 	movabs rax,0x0
 e83:	00 00 00 
 e86:	ff d0                	call   rax
 e88:	48 b9 00 00 02 00 00 	movabs rcx,0xffff800000020000
 e8f:	80 ff ff 
 e92:	48 ba 00 00 20 01 00 	movabs rdx,0xffff800001200000
 e99:	80 ff ff 
 e9c:	be 02 00 00 00       	mov    esi,0x2
 ea1:	48 bf 00 00 00 00 00 	movabs rdi,0x0
 ea8:	00 00 00 
 eab:	48 b8 00 00 00 00 00 	movabs rax,0x0
 eb2:	00 00 00 
 eb5:	ff d0                	call   rax
 eb7:	5d                   	pop    rbp
 eb8:	c3                   	ret    
