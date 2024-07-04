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
  kwrite("      quit    (to exit TyDOS)\n");
}

void f_quit() {
  kwrite("Program halted. Bye.");
  go_on = 0;
}

void f_list() {
  struct fs_header_t *fs_header = get_fs_header();

  byte sector_coordinate = 1 + fs_header->number_of_boot_sectors;
  byte sectors_to_read = fs_header->number_of_file_entries * DIR_ENTRY_LEN / 512;

  extern int _MEM_POOL;
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

/* Built-in shell command: example.

   Execute an example user program which invokes a syscall.

   The example program (built from the source 'prog.c') is statically linked
   to the kernel by the linker script (tydos.ld). In order to extend the
   example, and load and external C program, edit 'f_exec' and 'prog.c' choosing
   a different name for the entry function, such that it does not conflict with
   the 'main' function of the external program.  Even better: remove 'f_exec'
   entirely, and suppress the 'example_program' section from the tydos.ld, and
   edit the Makefile not to include 'prog.o' and 'libtydos.o' from 'tydos.bin'.

  */

// extern int main();
void f_exec() {
  // main();			/* Call the user program's 'main' function. */
}
