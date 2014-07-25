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
#include <string.h>

#include "config.h"
#include "smlgr.h"
#include "utils.h"
#include "socket.h"
#include "sql.h"
#include "ui.h"
#include "cfg.h"

cfg *conf;
char *smlgr_program_name;


int main(int argc, char **argv)
{
    smlgr_program_name = argv[0];

    cfgInit();

    if(cfgParse(argc, argv))
        smlgr();

    return 0;
}



/**
 * Main program function
 */

void smlgr()
{
    int *sock;
    int sock_ret;
    char *query;
    char *response;
    infos *data;

    while(1) {
        sock = (int *) malloc(sizeof(int));

        uiMessage(UI_INFO, "Creating socket");
        sock_ret = sckCreate(sock, conf->inv_addr, conf->inv_port);

        if(sock_ret == 0) {
            uiMessage(UI_INFO, "Creating inverter query string");
            query = strPrepare(conf->lgr_query);

            uiMessage(UI_INFO, "Sending query");
            sckSend(sock, query);

            free(query);

            uiMessage(UI_INFO, "Receiving response");
            response = sckRecv(sock);

            if(strlen(response) > 0) {
                uiMessage(UI_INFO, "Parsing data");
                data = strParse(response);

                uiMessage(UI_DEBUG, "%d elements on response", infosCounting(data));

                uiMessage(UI_INFO, "Adding data to DB");
                sqlSave(data);

                uiMessage(UI_INFO, "Freeing memory");
                infosFree(data);
            } else {
                uiMessage(UI_WARNING, "Inverter doesn't answer");
            }

            free(response);

            uiMessage(UI_INFO, "Destroying socket");
        } else {
            uiMessage(UI_ERROR, "Error creating socket.");
        }

        sckDestroy(sock);
        free(sock);

        uiMessage(UI_INFO, "Sleeping");
        sleep(conf->lgr_interval);
    }

    cfgFree();
}
