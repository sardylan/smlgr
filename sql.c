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
#include "sql.h"
#include "utils.h"
#include "ui.h"

/**
 * Main function called to save data into DB
 * @param[in] data data struct of a valid data list
 */

void sqlSave(infos *data)
{
    char sql_query[2048];
    char params[1024];
    char values[1024];
    int i;

    memset(params, '\0', sizeof(params));
    memset(values, '\0', sizeof(values));

    data = data->next;

    i = 0;

    while(strlen(data->param) > 0) {
        if(i > 0) {
            strcat(params, ", ");
            strcat(values, ", ");
        }

        strcat(params, "'");
        strcat(params, data->param);
        strcat(params, "'");

        strcat(values, "'");
        strcat(values, data->value);
        strcat(values, "'");

        data = data->next;
        i++;
    }

    uiMessage(UI_DEBUG, "SQL params: %s", params);
    uiMessage(UI_DEBUG, "SQL values: %s", values);

    sprintf(sql_query, "INSERT INTO %s (%s) VALUES (%s);", MYSQL_TABLE, params, values);
    uiMessage(UI_DEBUG, "SQL Query: %s", sql_query);
}
