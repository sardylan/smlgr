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

// {01;FB;70|64:IDC=2A5;UL1=952;TKK=31;IL1=356;SYS=4E28,0;TNF=138E;UDC=C2F;PAC=FBC;PRL=3D;KT0=2F16;SYS=4E28,0|1A79}
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "smlgr.h"
#include "utils.h"

int main(int argc, char** argv)
{
    infos* data;

    data = strParse("{01;FB;70|64:IDC=2A5;UL1=952;TKK=31;IL1=356;SYS=4E28,0;TNF=138E;UDC=C2F;PAC=FBC;PRL=3D;KT0=2F16;SYS=4E28,0|1A79}");
    infosPrint(data);
    infosFree(data);

    return 0;
}
