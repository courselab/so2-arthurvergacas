/*
 *    SPDX-FileCopyrightText: 2024 Arthur Vergaças <arthurvdm@gmail.com>
 *    SPDX-FileCopyrightText: 2024 Monaco F. J. <monaco@usp.br>
 *
 *    SPDX-License-Identifier: GPL-3.0-or-later
 *
 *  This file is a derivative work from SYSeg (https://gitlab.com/monaco/syseg)
 *  and contains modifications carried out by the following author(s):
 *  Arthur Vergaças <arthurvdm@gmail.com>
 */

#include "file_system.h"
#include "kaux.h"

struct fs_header_t *get_fs_header() {
  return (struct fs_header_t *)0x7c00;
}

void load_disk_into_memory(byte sector_coordinate, byte sectors_to_read, void *target_addres) {
  __asm__ volatile(
      "pusha \n"
      "mov boot_drive, %%dl \n"    /* Select the boot drive (from rt0.o). */
      "mov $0x2, %%ah \n"          /* BIOS disk service: op. read sector. */
      "mov %[sectToRead], %%al \n" /* How many sectors to read          */
      "mov $0x0, %%ch \n"          /* Cylinder coordinate (starts at 0).  */
      "mov %[sectCoord], %%cl \n"  /* Sector coordinate   (starts at 1).  */
      "mov $0x0, %%dh \n"          /* Head coordinate     (starts at 0).      */
      "mov %[targetAddr], %%bx \n" /* Where to load the file system (rt0.o).   */
      "int $0x13 \n"               /* Call BIOS disk service 0x13.        */
      "popa \n" ::
          [sectCoord] "g"(sector_coordinate),
      [sectToRead] "g"(sectors_to_read),
      [targetAddr] "g"(target_addres));
}
