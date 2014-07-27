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
extern const char *smlgr_program_name;


/**
 * Usage information message
 */

void uiUsage()
{
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "    %s [<option> <value> ...]\n", smlgr_program_name);
}



/**
 * Version information
 */

void uiVersion()
{
    fprintf(stderr, "SolarMax Logger\n");
}



/**
 * Help information message with all command line options
 */

void uiHelp()
{
    fprintf(stderr, "SolarMax S3000 DB Logger\n");
    fprintf(stderr, "\n");

    uiUsage();

    fprintf(stderr, "\n");
    fprintf(stderr, "Options list with default values:\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "    -c | --config            Config file (overwrite all other options)\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "    -h | --help              This message\n");
    fprintf(stderr, "    -V | --version           Print Version and exit\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "    -q | --quiet             Disable output (debug level 0)\n");
    fprintf(stderr, "    -v | --verbose           Verbose output (debug level 4)\n");
    fprintf(stderr, "    -d | --debug             Debug level (%d)\n", DEFAULT_UI_DEBUG_LEVEL);
    fprintf(stderr, "                             0 DISABLE (quiet)\n");
    fprintf(stderr, "                             1 ERROR\n");
    fprintf(stderr, "                             2 WARNING\n");
    fprintf(stderr, "                             3 INFO\n");
    fprintf(stderr, "                             4 DEBUG (verbose)\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "    -a | --inv-addr          Inverter IP Address (%s)\n", DEFAULT_INVERTER_IP_ADDR);
    fprintf(stderr, "    -p | --inv-port          Inverter TCP Port (%d)\n", DEFAULT_INVERTER_IP_PORT);
    fprintf(stderr, "    -n | --inv-num           Inverter number (%d)\n", DEFAULT_INVERTER_NUM);
    fprintf(stderr, "\n");
    fprintf(stderr, "    -k | --query             Logger query (%s)\n", DEFAULT_LGR_QUERY);
    fprintf(stderr, "    -i | --interval          Logger interval in seconds (%d)\n", DEFAULT_LGR_INTERVAL);
    fprintf(stderr, "\n");
    fprintf(stderr, "    -s | --mysql-addr        MySQL Server IP Address (%s)\n", DEFAULT_MYSQL_ADDR);
    fprintf(stderr, "    -t | --mysql-port        MySQL Server TCP port (%d)\n", DEFAULT_MYSQL_PORT);
    fprintf(stderr, "    -u | --mysql-user        MySQL Server Username (%s)\n", DEFAULT_MYSQL_USER);
    fprintf(stderr, "    -w | --mysql-password    MySQL Server Password (%s)\n", DEFAULT_MYSQL_PASSWORD);
    fprintf(stderr, "    -b | --mysql-database    MySQL Server Database name (%s)\n", DEFAULT_MYSQL_DATABASE);
    fprintf(stderr, "\n");
    fprintf(stderr, "    -l | --mysql-table       Database table name (%s)\n", DEFAULT_MYSQL_TABLE);
    fprintf(stderr, "\n");
    fprintf(stderr, "All outputs are on Standard Error.\n");
}



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
    uiMessage(UI_ERROR, "%s (%d): %s", text, errnum, errtext);
}
