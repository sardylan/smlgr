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


#ifndef __CFG_H
#define __CFG_H

struct cfg_s {
    int debug_level;
    char *inv_addr;
    int inv_port;
    int inv_num;
    char *lgr_query;
    int lgr_interval;
    char *mysql_addr;
    int mysql_port;
    char *mysql_user;
    char *mysql_password;
    char *mysql_database;
    char *mysql_table;
};

typedef struct cfg_s cfg;

void cfgInit();
void cfgFree();
int cfgParse(int, char **);

#endif
