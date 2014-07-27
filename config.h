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


#ifndef __CONFIG_H
#define __CONFIG_H

#define DEFAULT_UI_DEBUG_LEVEL 4

#define DEFAULT_INVERTER_IP_ADDR "172.16.83.2"
#define DEFAULT_INVERTER_IP_PORT 12345
#define DEFAULT_INVERTER_NUM 1

#define DEFAULT_LGR_QUERY "UDC;IDC;UL1;IL1;PAC;PRL;TKK;TNF;KDY;KLD"
#define DEFAULT_LGR_INTERVAL 10

#define DEFAULT_MYSQL_ADDR "127.0.0.1"
#define DEFAULT_MYSQL_PORT 3306
#define DEFAULT_MYSQL_USER "smlgr"
#define DEFAULT_MYSQL_PASSWORD "smlgr"
#define DEFAULT_MYSQL_DATABASE "smlgr"

#define DEFAULT_MYSQL_TABLE "invdata"

#endif
