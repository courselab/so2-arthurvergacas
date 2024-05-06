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

#include "bios.h"
#include "utils.h"

#define PROMPT "$ " /* Prompt sign.      */
#define SIZE 10     /* Read buffer size. */

char buffer[SIZE]; /* Read buffer.      */

void add_1(int n) {
  if (n <= 0 || n >= 10) {
    println("I can't :(");
    return;
  }

  char number[2] = {'0' + n + 1, '\0'};
  println(number);
}

int main() {
  clear();

  println("Boot Command 1.0");

  while (1) {
    print(PROMPT);  /* Show prompt.               */
    readln(buffer); /* Read use input.            */

    if (buffer[0]) /* Execute built-in command.  */
    {
      if (!strcmp(buffer, "add1 ", 4)) {
        int n = str_to_int(&buffer[5]);
        add_1(n);
      }
    }
  }

  return 0;
}
