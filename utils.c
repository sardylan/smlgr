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
#include <math.h>
#include <string.h>

#include "config.h"
#include "utils.h"

char* checksum16(char* input)
{
    int i;
    int ln;
    int sum;
    char* ret;

    ret = (char *) calloc(5, sizeof(char));

    *ret = '0';
    *(ret + 1) = '0';
    *(ret + 2) = '0';
    *(ret + 3) = '0';
    *(ret + 4) = '\0';

    sum = 0;

    if(input != NULL) {
        ln = strlen(input);

        for(i=0; i<ln; i++) {
            sum += input[i];
            sum %= (int) pow(2, 16);
        }
    }

    sprintf(ret, "%4X", sum);

    for(i=0; i<4; i++)
        if(*(ret+i) == ' ')
            *(ret+i) = '0';

    return ret;
}
