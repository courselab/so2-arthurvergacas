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

int __attribute__((fastcall)) strcmp(const char *s1, const char *s2, int n) {
  int i = 0;
  while (*s1 && *s2 && *s1 == *s2 && (n == -1 || i < n)) {
    s1++;
    s2++;
    i++;
  }
  return (*s1 - *s2);
}

int __attribute__((fastcall)) str_to_int(const char *s) {
  int n = 0;
  while (*s) {
    n = n * 10 + (*s++ - '0');
  }
  return n;
}
