/*
 *    SPDX-FileCopyrightText: 2024 Arthur Vergaças <arthur.vergacas@usp.br>
 *    SPDX-FileCopyrightText: 2024 Maria Júlia De Grandi <maju.degrandi@usp.br>
 *
 *    SPDX-License-Identifier: GPL-3.0-or-later
 *
 *  This file is a derivative work from SYSeg (https://gitlab.com/monaco/syseg)
 *  and contains modifications carried out by the following author(s):
 *  Arthur Vergaças <arthur.vergacas@usp.br>
 *  Maria Júlia De Grandi <maju.degrandi@usp.br>
 */

#include "tydos.h"

int main() {
  char name[GETS_BUFFER_MAX_SIZE];
  puts("What's your name? ");
  gets(name);

  puts("Hello ");
  puts(name);
  puts("\n");

  return 0;
}
