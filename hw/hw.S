###    SPDX-FileCopyrightText: 2021 Monaco F. J. <monaco@usp.br>
###    SPDX-FileCopyrightText: 2024 Arthur Vergaças <arthurvdm@gmail.com>
###
###    SPDX-License-Identifier: GPL-3.0-or-later
###
###  This file is a derivative work from SYSeg (https://gitlab.com/monaco/syseg)
###  and contains modifications carried out by the following author(s):
###  Arthur Vergaças <arthurvdm@gmail.com>

	## Boot, say hello, and halt
	## AT&T assembly, translated from NASM

	.code16  		   # Set 16-bit mode

	.global _start # default entry point, used by the linker

_start:

	movb $0xe, %ah		# set BIOS teletype mode

	movb $'H', %al 		# Load 'H' ascii code
	int $0x10	  	    # Issue BIOS interrupt

	movb $'e', %al 		# Load 'e' ascii code
	int $0x10		      # Issue BIOS interrupt

	movb $'l', %al 		# Load 'l' ascii code
	int $0x10		      # Issue BIOS interrupt

	movb $'l', %al 		# Load 'l' ascii code
	int $0x10		      # Issue BIOS interrupt

	movb $'o', %al 		# Load 'o' ascii code
	int $0x10		      # Issue BIOS interrupt

	movb $' ', %al 		# Load ' ' ascii code
	int $0x10		      # Issue BIOS interrupt

	movb $'W', %al 		# Load 'W' ascii code
	int $0x10		      # Issue BIOS interrupt

	movb $'o', %al 		# Load 'o' ascii code
	int $0x10		      # Issue BIOS interrupt

	movb $'r', %al 		# Load 'r' ascii code
	int $0x10		      # Issue BIOS interrupt

	movb $'l', %al 		# Load 'l' ascii code
	int $0x10		      # Issue BIOS interrupt

	movb $'d', %al 		# Load 'd' ascii code
	int $0x10		      # Issue BIOS interrupt

halt:
	hlt			  # Halt the machine
	jmp halt  # Safeguard

	.fill 510 - (. - _start), 1, 0  # Pad with zeros
	.word 0xaa55		                # Boot signature

