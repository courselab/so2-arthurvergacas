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

#ifndef BIOS_H
#define BIOS_H

void __attribute__((fastcall)) clear(void);
void __attribute__((fastcall)) print(const char *);
void __attribute__((fastcall)) println(const char *);
void __attribute__((fastcall)) readln(char *);

#endif
