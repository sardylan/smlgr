#
#   SolarMax S3000 DB logger
#   Copyright (C) 2013  Luca Cireddu
#   sardylan@gmail.com
#
#   This program is free software; you can redistribute it and/or
#   modify it under the terms of the GNU General Public License
#   as published by the Free Software Foundation; either version 2
#   of the License, or (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License along
#   with this program; if not, write to the Free Software Foundation, Inc.,
#   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#


CC =		gcc
STRIP =		strip

CFLAGS =	-O0 -ggdb -Wall
LDFLAGS =	-lmysqlclient
STRIPFLAGS =	--strip-all

TARGET =	smlgr

OBJS =		smlgr.o \
		utils.o \
		socket.o \
		sql.o \
		ui.o \
		cfg.o


all: debug

debug: $(TARGET)

release: $(TARGET) strip-all

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

strip-all:
	$(STRIP) $(STRIPFLAGS) $(TARGET)

clean:
	rm -rf *.o $(TARGET)
