/*
 *    SPDX-FileCopyrightText: 2021 Monaco F. J. <monaco@usp.br>
 *    SPDX-FileCopyrightText: 2024 Arthur Vergaças <arthurvdm@gmail.com>
 *
 *    SPDX-License-Identifier: GPL-3.0-or-later
 *
 *  This file is a derivative work from SYSeg (https://gitlab.com/monaco/syseg)
 *  and contains modifications carried out by the following author(s):
 *  Arthur Vergaças <arthurvdm@gmail.com>
 */

/* This source file implements the kernel entry function 'kmain' called
   by the bootloader, and the command-line interpreter. Other kernel functions
   were implemented separately in another source file for legibility. */

#include "bios1.h"  /* For kwrite() etc.            */
#include "bios2.h"  /* For kread() etc.             */
#include "kernel.h" /* Essential kernel functions.  */
#include "kaux.h"   /* Auxiliary kernel functions.  */
#include "file_system.h"

/* Kernel's entry function. */

void kmain(void) {
  register_syscall_handler(); /* Register syscall handler at int 0x21.*/

  // splash(); /* Uncessary spash screen.              */

  shell(); /* Invoke the command-line interpreter. */

  halt(); /* On exit, halt.                       */
}

/* Tiny Shell (command-line interpreter). */

char buffer[BUFF_SIZE];
int go_on = 1;

void shell() {
  int i;
  clear();
  kwrite("ArjuDOS 1.0\n");

  while (go_on) {

    /* Read the user input.
       Commands are single-word ASCII tokens with no blanks. */
    do {
      kwrite(PROMPT);
      kread(buffer);
    } while (!buffer[0]);

    /* Check for matching built-in commands */

    i = 0;
    while (cmds[i].funct) {
      if (!strcmp(buffer, cmds[i].name)) {
        cmds[i].funct();
        break;
      }
      i++;
    }

    /* If the user input does not match any built-in command name, just
       ignore and read the next command. If we were to execute external
       programs, on the other hand, this is where we would search for a
       corresponding file with a matching name in the storage device,
       load it and transfer it the execution. Left as exercise. */

    if (!cmds[i].funct)
      kwrite("Command not found\n");
  }
}

/* Array with built-in command names and respective function pointers.
   Function prototypes are in kernel.h. */

struct cmd_t cmds[] =
    {
        {"help", f_help}, /* Print a help message.       */
        {"quit", f_quit}, /* Exit TyDOS.                 */
        {"list", f_list}, /* List files.                 */
        {"exec", f_exec}, /* Execute an example program. */
        {0, 0}};

/* Build-in shell command: help. */

void f_help() {
  kwrite("...me, Obi-Wan, you're my only hope!\n\n");
  kwrite("   But we can try also some commands:\n");
  kwrite("      exec    (to execute an user program example\n");
  kwrite("      list    (to list files in ArjuDOS)\n");
  kwrite("      quit    (to exit ArjuDOS)\n");
}

void f_quit() {
  kwrite("Program halted. Bye.");
  go_on = 0;
}

void f_list() {
  struct fs_header_t *fs_header = get_fs_header();

  int sector_coordinate = 1 + fs_header->number_of_boot_sectors;
  int sectors_to_read = fs_header->number_of_file_entries * DIR_ENTRY_LEN / SECTOR_SIZE;

  extern byte _MEM_POOL;
  void *directory_section = (void *)&_MEM_POOL;

  load_disk_into_memory(sector_coordinate, sectors_to_read, directory_section);

  for (int i = 0; i < fs_header->number_of_file_entries; i++) {
    char *file_name = directory_section + i * DIR_ENTRY_LEN;
    if (file_name[0]) {
      kwrite(file_name);
      kwrite("\n");
    }
  }
}

void f_exec() {
  char *binary_file_name = "prog.bin";

  // achar o binario do cara
  struct fs_header_t *fs_header = get_fs_header();

  int directory_sector_coordinate = 1 + fs_header->number_of_boot_sectors;
  int sectors_to_read = fs_header->number_of_file_entries * DIR_ENTRY_LEN / SECTOR_SIZE + 1;

  int memoryOffset = fs_header->number_of_file_entries * DIR_ENTRY_LEN - (sectors_to_read - 1) * 512;

  extern byte _MEM_POOL;
  void *directory_section = (void *)&_MEM_POOL;

  load_disk_into_memory(directory_sector_coordinate, sectors_to_read, directory_section);

  int bin_sector_coordinate;
  for (int i = 0; i < fs_header->number_of_file_entries; i++) {
    char *file_name = directory_section + i * DIR_ENTRY_LEN;
    if (!strcmp(file_name, binary_file_name)) {
      // executar esse cara
      bin_sector_coordinate = directory_sector_coordinate + sectors_to_read + fs_header->max_file_size * i - 1;
      break;
    }
  }

  void *program = (void *)(0xFE00);
  void *program_sector_start = program - memoryOffset;

  load_disk_into_memory(bin_sector_coordinate, fs_header->max_file_size, program_sector_start);

  __asm__(
      // "oi_message: .string \"oi \" \n"
      // "call get_ip_into_ax \n"  // coloca o return address em ax

      // "push %%cx \n"
      // "push %%ax \n"
      // "lea oi_message, %%cx \n"
      // "call kwrite \n"
      // "pop %%ax \n"
      // "pop %%cx \n"

      // "mov $finish, %ax \n"

      "push %ax \n"  // colocar o ax na stack

      "mov $0xFE00, %bx \n"
      "jmp *%bx \n"  // jump pra main

      // "finish: \n"

      // "get_ip_into_ax: \n"
      // "  mov %sp, %bp \n"
      // "  mov (%bp), %ax \n"
      // "  add $0x5, %ax \n"
      // "  ret \n"
  );

  kwrite("ue\n");
}
