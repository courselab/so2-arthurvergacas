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

#ifndef UTILS_H
#define UTILS_H

int __attribute__((fastcall)) strcmp(const char *s1, const char *s2, int n);

int __attribute__((fastcall)) str_to_int(const char *s);

#endif /* UTILS_H  */
