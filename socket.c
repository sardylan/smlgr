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
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

#include "config.h"
#include "socket.h"
#include "ui.h"

void sckCreate(int *sock, char *addr, int port)
{
    struct sockaddr_in serv_addr;

    uiMessage(UI_DEBUG, "Creating socket %s:%d", addr, port);

    *sock = socket(AF_INET, SOCK_STREAM, 0);

    if(*sock != -1) {
        memset(&serv_addr, '0', sizeof(serv_addr));

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(port);

        if(inet_pton(AF_INET, addr, &serv_addr.sin_addr) > 0) {
            if(connect(*sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1)
                *sock = -1;
        } else
            *sock = -1;
    }
}

void sckDestroy(int *sock)
{
    close(*sock);
}

void sckSend(int *sock, char *buff)
{
    uiMessage(UI_DEBUG, "Sending query %s", buff);

    write(*sock, buff, strlen(buff));
}

char* sckRecv(int *sock)
{
    char *ret;
    char buff[1024];
    int bytes;

    ret = (char *) malloc(sizeof(char));
    *ret = '\0';

    memset(buff, '\0', sizeof(buff));

    bytes = read(*sock, buff, sizeof(buff)-1);

    if(bytes > 0) {
        buff[bytes] = '\0';

        ret = (char *) realloc(ret, bytes+1);
        strcpy(ret, buff);
    }

    uiMessage(UI_DEBUG, "Receiving response %s", ret);

    return ret;
}
