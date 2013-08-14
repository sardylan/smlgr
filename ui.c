/*
 *   SolarMax S3000 DB logger
 *   Copyright (C) 2013  Luca Cireddu
 *   sardylan@gmail.com
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License along
 *   with this program; if not, write to the Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

#include "config.h"
#include "ui.h"

void uiMessage(int level, char *text, ...)
{
    va_list args;

    va_start(args, text);

    if(level <= UI_DEBUG_LEVEL)
        if(level == 1)
            fprintf(stderr, "[ERROR] ");
        if(level == 2)
            fprintf(stderr, "[WARN]  ");
        if(level == 3)
            fprintf(stderr, "[INFO]  ");
        if(level == 4)
            fprintf(stderr, "[DEBUG] ");

        vfprintf(stderr, text, args);
        fprintf(stderr, "\n");

    va_end(args);
}
