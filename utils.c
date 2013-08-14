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
#include "ui.h"

char *decToHex(int input, int dim)
{
    char *ret;
    char pattern[8];
    int i;

    sprintf(pattern, "%%%dX", dim);

    ret = (char *) calloc(dim+1, sizeof(char));

    for(i=0; i<dim; i++)
        *(ret + i) = '0';

    *(ret + dim) = '\0';

    sprintf(ret, pattern, input);

    for(i=0; i<dim; i++)
        if(*(ret+i) == ' ')
            *(ret+i) = '0';

    return ret;
}

char *checksum16(char *input)
{
    char *ret;
    int i;
    size_t ln;
    int sum;

    sum = 0;

    if(input != NULL) {
        ln = strlen(input);

        for(i=0; i<ln; i++) {
            sum += input[i];
            sum %= (int) pow(2, 16);
        }
    }

    ret = decToHex(sum, 4);

    return ret;
}

char *strPrepare(char *query)
{
    char *ret;
    size_t ln;
    char *inv_id;
    char *len;
    char *checksum;
    char tmp[1024];

    ret = NULL;

    if(query != NULL) {
        uiMessage(UI_DEBUG, "Preparing query %s", query);

        ln = strlen(query);

        if(ln >= 3) {
            ret = (char *) calloc(13 + ln + 6 + 1, sizeof(char));

            inv_id = decToHex(INVERTER_NUM, 2);
            len = decToHex(13 + ln + 6, 2);

            sprintf(tmp, "FB;%s;%s|64:%s|", inv_id, len, query);
            checksum = checksum16(tmp);

            sprintf(ret, "{%s%s}", tmp, checksum);

            free(inv_id);
            free(len);
            free(checksum);
        }
    }

    uiMessage(UI_DEBUG, "Preparing query %s", ret);

    return ret;
}

infos *strParse(char *response)
{
    infos *ret;
    infos *first;
    char c;
    int i;
    int j;
    int mode;
    char param[8];
    char value[16];

    uiMessage(UI_DEBUG, "Parsing response %s", response);

    ret = (infos *) malloc(sizeof(infos));
    first = ret;

    ret->param = (char *) malloc(sizeof(char));
    ret->value = (char *) malloc(sizeof(char));
    strcpy(ret->param, "");
    strcpy(ret->value, "");
    ret->next = ret;

    if(strlen(response) > 23) {
        i = 0;
        j = 0;
        mode = 0;
        param[0] = '\0';
        value[0] = '\0';

        while((c = *(response + 13 + i)) != '|') {
            if(c == '=') {
                mode = 1;
                j = 0;
            } else if(c == ';') {
                ret->next = (infos *) malloc(sizeof(infos));
                ret = ret->next;
                ret->next = first;

                ret->param = (char *) calloc(strlen(param)+1, sizeof(char));
                ret->value = (char *) calloc(strlen(value)+1, sizeof(char));
                strcpy(ret->param, param);
                strcpy(ret->value, value);

                uiMessage(UI_DEBUG, "Parsing response %s = ", ret->param, ret->value);

                mode = 0;
                j = 0;
                param[0] = '\0';
                value[0] = '\0';
            } else {
                if(mode == 0) {
                    param[j] = c;
                    param[j+1] = '\0';
                } else {
                    value[j] = c;
                    value[j+1] = '\0';
                }
                j++;
            }
            i++;
        }
    }

    return first;
}

void infosPrint(infos *input)
{
    input = input->next;

    while(strlen(input->param) > 0) {
        printf("%s = %s\n", input->param, input->value);
        input = input->next;
    }
}

void infosFree(infos *input)
{
    infos *prev;
    infos *first;

    first = input;

    while(input->next != first) {
        free(input->param);
        free(input->value);
        prev = input;
        input = input->next;
        free(prev);
    }

    free(input->param);
    free(input->value);
    free(input);
}
