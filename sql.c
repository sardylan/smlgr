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
#include <mysql/mysql.h>

#include "config.h"
#include "sql.h"
#include "utils.h"
#include "ui.h"


/**
 * Function used to escape a string according to connection parameters
 * @param[in] mysql_connection MySQL connector
 * @param[in] input Unescaped input string
 * @param[out] ret Escaped string
 */

char *mysqlStringEscape(MYSQL *mysql_connection, const char *input)
{
    char *ret;
    char output[1024];
    size_t ln;

    if(input == NULL) { // If input string is NULL (not empty string) we return an empty string
        ret = (char *) malloc(sizeof(char));
        *(ret) = '\0';
    } else { // else we use the mysql_real_escape_string to escape problem-generating characters
        mysql_real_escape_string(mysql_connection, output, input, (unsigned long) strlen(input));
        ln = strlen(output) + 1;
        ret = (char *) calloc(ln, sizeof(char));
        strcpy(ret, output);
    }

    return ret;
}


/**
 * Main function called to save data into DB
 * @param[in] data data struct of a valid data list
 */

void sqlSave(infos *data)
{
    MYSQL *temp_connection;
    MYSQL *mysql_connection;
    unsigned int mysql_timeout;
    char sql_query[2048];
    int sql_return;
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

        strcat(params, "`");
        strcat(params, data->param);
        strcat(params, "`");

        strcat(values, "0x");
        strcat(values, data->value);
//         strcat(values, "");

        data = data->next;
        i++;
    }

    uiMessage(UI_DEBUG, "SQL params: %s", params);
    uiMessage(UI_DEBUG, "SQL values: %s", values);

    sprintf(sql_query, "INSERT INTO %s (%s) VALUES (%s);", MYSQL_TABLE, params, values);

    uiMessage(UI_INFO, "Connecting to MySQL DB");

    mysql_timeout = 2;

    uiMessage(UI_DEBUG, "Creating MySQL connection");

    temp_connection = mysql_init(NULL);

    if(temp_connection != NULL) {
        mysql_options(temp_connection, MYSQL_OPT_CONNECT_TIMEOUT, (char *) &mysql_timeout);
        uiMessage(UI_DEBUG, "Connecting to mysql://%s:%s@%s:%d/%s", MYSQL_USER, MYSQL_PASSWORD, MYSQL_SERVER, MYSQL_PORT, MYSQL_DB);

        mysql_connection = mysql_real_connect(temp_connection, MYSQL_SERVER, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DB, MYSQL_PORT, NULL, 0);

        if(mysql_connection != NULL) {
            uiMessage(UI_DEBUG, "SQL Query: %s", sql_query);

            sql_return = mysql_query(mysql_connection, sql_query);

            if(sql_return == 0) {
                uiMessage(UI_INFO, "Data added to DB");
            } else {
                uiMessage(UI_WARNING, "Error executing query");
            }

            mysql_close(mysql_connection);
        } else {
            uiMessage(UI_WARNING, "Can't connect to MySQL DB");
        }
    }
}
