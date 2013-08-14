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

#include "config.h"
#include "smlgr.h"
#include "utils.h"
#include "socket.h"
#include "sql.h"
#include "ui.h"

int main(int argc, char **argv)
{
    smlgr();

    return 0;
}

void smlgr()
{
    int *sock;
    char *query;
    char *response;
    infos *data;

    sock = (int *) malloc(sizeof(int));

    uiMessage(UI_INFO, "Creating socket");
    sckCreate(sock, INVERTER_IP_ADDR, INVERTER_IP_PORT);

    if(*sock != -1) {
        while(1) {
            uiMessage(UI_INFO, "Creating inverter query string");
            query = strPrepare(LGR_QUERY);

            uiMessage(UI_INFO, "Sending query");
            sckSend(sock, query);

            uiMessage(UI_INFO, "Receiving response");
            response = sckRecv(sock);

            uiMessage(UI_INFO, "Parsing data");
            data = strParse(response);

            uiMessage(UI_DEBUG, "%d elements on response", infosCounting(data));

            uiMessage(UI_INFO, "Adding data to DB");
            sqlSave(data);

            uiMessage(UI_INFO, "Freeing memory");
            infosFree(data);
            free(query);
            free(response);

            uiMessage(UI_INFO, "Sleeping");
            sleep(LGR_INTERVAL);
        }
    } else {
        uiMessage(UI_ERROR, "Error creating socket.");
    }

    sckDestroy(sock);

    free(sock);
}
