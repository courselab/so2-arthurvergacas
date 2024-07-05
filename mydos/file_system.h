/*
 *    SPDX-FileCopyrightText: 2024 Arthur Vergaças <arthur.vergacas@usp.br>
 *    SPDX-FileCopyrightText: 2024 Maria Júlia De Grandi <maju.degrandi@usp.br>
 *    SPDX-FileCopyrightText: 2024 Monaco F. J. <monaco@usp.br>
 *
 *    SPDX-License-Identifier: GPL-3.0-or-later
 *
 *  This file is a derivative work from SYSeg (https://gitlab.com/monaco/syseg)
 *  and contains modifications carried out by the following author(s):
 *  Arthur Vergaças <arthur.vergacas@usp.br>
 *  Maria Júlia De Grandi <maju.degrandi@usp.br>
 */
#ifndef KFILE_SYSTEM_H
#define KFILE_SYSTEM_H

#include "kaux.h"

#define FS_SIGLEN 4      /* Signature length.                        */
#define DIR_ENTRY_LEN 32 /* Max file name length in bytes.           */
#define SECTOR_SIZE 512

/* The file header. */

struct fs_header_t {
  unsigned char signature[FS_SIGLEN];     /* The file system signature.              */
  unsigned short total_number_of_sectors; /* Number of 512-byte disk blocks.         */
  unsigned short number_of_boot_sectors;  /* Sectors reserved for boot code.         */
  unsigned short number_of_file_entries;  /* Maximum number of files in the disk.    */
  unsigned short max_file_size;           /* Maximum size of a file in blocks.       */
  unsigned int unused_space;              /* Remaining space less than max_file_size.*/
} __attribute__((packed));                /* Disable alignment to preserve offsets.  */

struct fs_header_t *get_fs_header();

void load_disk_into_memory(int sector_coordinate, int sectors_to_read, void *target_addres);

#endif /* KFILE_SYSTEM_H  */
