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
#include <time.h>

#include "config.h"
#include "ui.h"
#include "cfg.h"

extern cfg *conf;



/**
 * Debugging function
 * @param[in] level Level of the messages
 * @param[in] text Text message
 */

void uiMessage(int level, char *text, ...)
{
    va_list args;
    char datetime[20];
    time_t rawtime;
    struct tm *timeinfo;

    rawtime = time(NULL);
    timeinfo = localtime(&rawtime);
    strftime(datetime, 20, "%Y-%m-%d %H:%M:%S", timeinfo);

    va_start(args, text);

    if(level <= conf->debug_level)
        if(level == 1)
            fprintf(stderr, "%s [ERROR] ", datetime);
        if(level == 2)
            fprintf(stderr, "%s [WARN]  ", datetime);
        if(level == 3)
            fprintf(stderr, "%s [INFO]  ", datetime);
        if(level == 4)
            fprintf(stderr, "%s [DEBUG] ", datetime);

        vfprintf(stderr, text, args);
        fprintf(stderr, "\n");

    va_end(args);
}


/**
 * Error message function
 * @param[in] text Generic message
 * @param[in] errnum Error code
 * @param[in] errtext Error text
 */

void uiError(char *text, int errnum, char *errtext)
{
    uiMessage(4, "%s (%d): %s", text, errnum, errtext);
}
