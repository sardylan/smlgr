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
#include <getopt.h>

#include "config.h"
#include "ui.h"
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



/**
 * Parsing options
 * @param[in] argc Number of arguments in command line
 * @param[in] argv Arguments strings in command line
 * @param[out] ret Returns 0 in case of error, 1 if not
 */

int cfgParse(int argc, char **argv)
{
    int ret = 0;
    int option_index = 0;
    int c;
    int ln;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"version", no_argument, 0, 'V'},
        {"quiet", no_argument, 0, 'q'},
        {"verbose", no_argument, 0, 'v'},
        {"debug", required_argument, 0, 'd'},
        {"inv-addr", required_argument, 0, 'a'},
        {"inv-port", required_argument, 0, 'p'},
        {"inv-num", required_argument, 0, 'n'},
        {"query", required_argument, 0, 'k'},
        {"interval", required_argument, 0, 'i'},
        {"mysql-addr", required_argument, 0, 's'},
        {"mysql-port", required_argument, 0, 't'},
        {"mysql-user", required_argument, 0, 'u'},
        {"mysql-password", required_argument, 0, 'w'},
        {"mysql-database", required_argument, 0, 'b'},
        {"mysql-table", required_argument, 0, 'l'},
        {0, 0, 0, 0}
    };

    while(1) {
        c = getopt_long(argc, argv, "hVqvd:a:p:n:k:i:s:t:u:w:b:l:", long_options, &option_index);

        if(c == -1) {
            ret = 1;
            break;
        }

        if(c == '?') {
            uiHelp();
            break;
        }

        if(c == 'h') {
            uiHelp();
            break;
        }

        if(c == 'V') {
            uiVersion();
            break;
        }

        if(c == 'q') {
            conf->debug_level = 0;
        }

        if(c == 'v') {
            conf->debug_level = 4;
        }

        if(c == 'd') {
            conf->debug_level = atoi(optarg);
        }

        if(c == 'a') {
            ln = strlen(optarg) + 1;
            conf->inv_addr = (char *) realloc((void *) conf->inv_addr, sizeof(char) * ln);
            strcpy(conf->inv_addr, optarg);
        }

        if(c == 'p') {
            conf->inv_port = atoi(optarg);
        }

        if(c == 'n') {
            conf->inv_num = atoi(optarg);
        }

        if(c == 'k') {
            ln = strlen(optarg) + 1;
            conf->lgr_query = (char *) realloc((void *) conf->lgr_query, sizeof(char) * ln);
            strcpy(conf->lgr_query, optarg);
        }

        if(c == 'i') {
            conf->lgr_interval = atoi(optarg);
        }

        if(c == 's') {
            ln = strlen(optarg) + 1;
            conf->mysql_addr = (char *) realloc((void *) conf->mysql_addr, sizeof(char) * ln);
            strcpy(conf->mysql_addr, optarg);
        }

        if(c == 't') {
            conf->mysql_port = atoi(optarg);
        }

        if(c == 'u') {
            ln = strlen(optarg) + 1;
            conf->mysql_user = (char *) realloc((void *) conf->mysql_user, sizeof(char) * ln);
            strcpy(conf->mysql_user, optarg);
        }

        if(c == 'w') {
            ln = strlen(optarg) + 1;
            conf->mysql_password = (char *) realloc((void *) conf->mysql_password, sizeof(char) * ln);
            strcpy(conf->mysql_password, optarg);
        }

        if(c == 'b') {
            ln = strlen(optarg) + 1;
            conf->mysql_database = (char *) realloc((void *) conf->mysql_database, sizeof(char) * ln);
            strcpy(conf->mysql_database, optarg);
        }

        if(c == 'l') {
            ln = strlen(optarg) + 1;
            conf->mysql_table = (char *) realloc((void *) conf->mysql_table, sizeof(char) * ln);
            strcpy(conf->mysql_table, optarg);
        }
    }

    return ret;
}
