
app.o:     file format elf32-littlearm


Disassembly of section .text:

00000000 <main>:
   0:	e92d4800 	push	{fp, lr}
   4:	e28db004 	add	fp, sp, #4
   8:	e59f000c 	ldr	r0, [pc, #12]	; 1c <main+0x1c>
   c:	ebfffffe 	bl	0 <Uart_Send_Stirng>
  10:	e24bd004 	sub	sp, fp, #4
  14:	e8bd4800 	pop	{fp, lr}
  18:	e12fff1e 	bx	lr
  1c:	00000000 	andeq	r0, r0, r0

Disassembly of section .data:

00000000 <string_buffer>:
   0:	7261656c 	rsbvc	r6, r1, #108, 10	; 0x1b000000
   4:	6e692d6e 	cdpvs	13, 6, cr2, cr9, cr14, {3}
   8:	7065642d 	rsbvc	r6, r5, sp, lsr #8
   c:	483a6874 	ldmdami	sl!, {r2, r4, r5, r6, fp, sp, lr}
  10:	6173736f 	cmnvs	r3, pc, ror #6
  14:	6c45206d 	mcrrvs	0, 6, r2, r5, cr13
  18:	6867616d 	stmdavs	r7!, {r0, r2, r3, r5, r6, r8, sp, lr}^
  1c:	00796272 	rsbseq	r6, r9, r2, ror r2
	...

Disassembly of section .rodata:

00000000 <string_buffer2>:
   0:	7261656c 	rsbvc	r6, r1, #108, 10	; 0x1b000000
   4:	6e692d6e 	cdpvs	13, 6, cr2, cr9, cr14, {3}
   8:	7065642d 	rsbvc	r6, r5, sp, lsr #8
   c:	483a6874 	ldmdami	sl!, {r2, r4, r5, r6, fp, sp, lr}
  10:	6173736f 	cmnvs	r3, pc, ror #6
  14:	6c45206d 	mcrrvs	0, 6, r2, r5, cr13
  18:	6867616d 	stmdavs	r7!, {r0, r2, r3, r5, r6, r8, sp, lr}^
  1c:	00796272 	rsbseq	r6, r9, r2, ror r2
	...

Disassembly of section .comment:

00000000 <.comment>:
   0:	43434700 	movtmi	r4, #14080	; 0x3700
   4:	4728203a 			; <UNDEFINED> instruction: 0x4728203a
   8:	2029554e 	eorcs	r5, r9, lr, asr #10
   c:	2e372e34 	mrccs	14, 1, r2, cr7, cr4, {1}
  10:	Address 0x00000010 is out of bounds.


Disassembly of section .ARM.attributes:

00000000 <.ARM.attributes>:
   0:	00002f41 	andeq	r2, r0, r1, asr #30
   4:	61656100 	cmnvs	r5, r0, lsl #2
   8:	01006962 	tsteq	r0, r2, ror #18
   c:	00000025 	andeq	r0, r0, r5, lsr #32
  10:	4d524105 	ldfmie	f4, [r2, #-20]	; 0xffffffec
  14:	4d445437 	cfstrdmi	mvd5, [r4, #-220]	; 0xffffff24
  18:	02060049 	andeq	r0, r6, #73	; 0x49
  1c:	01090108 	tsteq	r9, r8, lsl #2
  20:	01140412 	tsteq	r4, r2, lsl r4
  24:	03170115 	tsteq	r7, #1073741829	; 0x40000005
  28:	01190118 	tsteq	r9, r8, lsl r1
  2c:	061e011a 			; <UNDEFINED> instruction: 0x061e011a

app.o:     file format elf32-littlearm


Disassembly of section .text:

00000000 <main>:
   0:	e92d4800 	push	{fp, lr}
   4:	e28db004 	add	fp, sp, #4
   8:	e59f000c 	ldr	r0, [pc, #12]	; 1c <main+0x1c>
   c:	ebfffffe 	bl	0 <Uart_Send_String>
  10:	e24bd004 	sub	sp, fp, #4
  14:	e8bd4800 	pop	{fp, lr}
  18:	e12fff1e 	bx	lr
  1c:	00000000 	andeq	r0, r0, r0

Disassembly of section .data:

00000000 <string_buffer>:
   0:	7261656c 	rsbvc	r6, r1, #108, 10	; 0x1b000000
   4:	6e692d6e 	cdpvs	13, 6, cr2, cr9, cr14, {3}
   8:	7065642d 	rsbvc	r6, r5, sp, lsr #8
   c:	483a6874 	ldmdami	sl!, {r2, r4, r5, r6, fp, sp, lr}
  10:	6173736f 	cmnvs	r3, pc, ror #6
  14:	6c45206d 	mcrrvs	0, 6, r2, r5, cr13
  18:	6867616d 	stmdavs	r7!, {r0, r2, r3, r5, r6, r8, sp, lr}^
  1c:	00796272 	rsbseq	r6, r9, r2, ror r2
	...

Disassembly of section .rodata:

00000000 <string_buffer2>:
   0:	7261656c 	rsbvc	r6, r1, #108, 10	; 0x1b000000
   4:	6e692d6e 	cdpvs	13, 6, cr2, cr9, cr14, {3}
   8:	7065642d 	rsbvc	r6, r5, sp, lsr #8
   c:	483a6874 	ldmdami	sl!, {r2, r4, r5, r6, fp, sp, lr}
  10:	6173736f 	cmnvs	r3, pc, ror #6
  14:	6c45206d 	mcrrvs	0, 6, r2, r5, cr13
  18:	6867616d 	stmdavs	r7!, {r0, r2, r3, r5, r6, r8, sp, lr}^
  1c:	00796272 	rsbseq	r6, r9, r2, ror r2
	...

Disassembly of section .comment:

00000000 <.comment>:
   0:	43434700 	movtmi	r4, #14080	; 0x3700
   4:	4728203a 			; <UNDEFINED> instruction: 0x4728203a
   8:	2029554e 	eorcs	r5, r9, lr, asr #10
   c:	2e372e34 	mrccs	14, 1, r2, cr7, cr4, {1}
  10:	Address 0x00000010 is out of bounds.


Disassembly of section .ARM.attributes:

00000000 <.ARM.attributes>:
   0:	00002f41 	andeq	r2, r0, r1, asr #30
   4:	61656100 	cmnvs	r5, r0, lsl #2
   8:	01006962 	tsteq	r0, r2, ror #18
   c:	00000025 	andeq	r0, r0, r5, lsr #32
  10:	4d524105 	ldfmie	f4, [r2, #-20]	; 0xffffffec
  14:	4d445437 	cfstrdmi	mvd5, [r4, #-220]	; 0xffffff24
  18:	02060049 	andeq	r0, r6, #73	; 0x49
  1c:	01090108 	tsteq	r9, r8, lsl #2
  20:	01140412 	tsteq	r4, r2, lsl r4
  24:	03170115 	tsteq	r7, #1073741829	; 0x40000005
  28:	01190118 	tsteq	r9, r8, lsl r1
  2c:	061e011a 			; <UNDEFINED> instruction: 0x061e011a
