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
#include <malloc.h>
#include <string.h>

#include "config.h"
#include "cfg.h"

extern cfg *conf;



/**
 * Configuration init with default values
 */

void cfgInit()
{
    int ln;

    conf = (cfg *) malloc(sizeof(cfg));

    conf->debug_level = DEFAULT_UI_DEBUG_LEVEL;

    ln = strlen(DEFAULT_INVERTER_IP_ADDR) + 1;
    conf->inv_addr = (char *) calloc(sizeof(char), ln);
    strcpy(conf->inv_addr, DEFAULT_INVERTER_IP_ADDR);

    conf->inv_port = DEFAULT_INVERTER_IP_PORT;
    conf->inv_num = DEFAULT_INVERTER_NUM;

    ln = strlen(DEFAULT_LGR_QUERY) + 1;
    conf->lgr_query = (char *) calloc(sizeof(char), ln);
    strcpy(conf->lgr_query, DEFAULT_LGR_QUERY);

    conf->lgr_interval = DEFAULT_LGR_INTERVAL;

    ln = strlen(DEFAULT_MYSQL_ADDR) + 1;
    conf->mysql_addr = (char *) calloc(sizeof(char), ln);
    strcpy(conf->mysql_addr, DEFAULT_MYSQL_ADDR);

    conf->mysql_port = DEFAULT_MYSQL_PORT;

    ln = strlen(DEFAULT_MYSQL_USER) + 1;
    conf->mysql_user = (char *) calloc(sizeof(char), ln);
    strcpy(conf->mysql_user, DEFAULT_MYSQL_USER);

    ln = strlen(DEFAULT_MYSQL_PASSWORD) + 1;
    conf->mysql_password = (char *) calloc(sizeof(char), ln);
    strcpy(conf->mysql_password, DEFAULT_MYSQL_PASSWORD);

    ln = strlen(DEFAULT_MYSQL_DATABASE) + 1;
    conf->mysql_database = (char *) calloc(sizeof(char), ln);
    strcpy(conf->mysql_database, DEFAULT_MYSQL_DATABASE);

    ln = strlen(DEFAULT_MYSQL_TABLE) + 1;
    conf->mysql_table = (char *) calloc(sizeof(char), ln);
    strcpy(conf->mysql_table, DEFAULT_MYSQL_TABLE);
}



/**
 * Configuration free
 */

void cfgFree()
{
    free(conf->inv_addr);
    free(conf->lgr_query);
    free(conf->mysql_addr);
    free(conf->mysql_user);
    free(conf->mysql_password);
    free(conf->mysql_database);
    free(conf->mysql_table);

    free(conf);
}
