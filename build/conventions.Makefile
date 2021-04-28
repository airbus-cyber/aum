#    AUM: Airbus Unit tests with Mocks for C. AUM is a unit testing framework for C that allows the easy definition and request of mocks.
#    Copyright (C) 2019  Airbus Defence and Space
#
#    You should have received a copy of the AUTHORS.md file which lists all contributors.
#
#    This library is free software; you can redistribute it and/or
#    modify it under the terms of the GNU Lesser General Public
#    License as published by the Free Software Foundation; either
#    version 2.1 of the License, or (at your option) any later version.
#
#    This library is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#    Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public
#    License along with this library; if not, write to the Free Software
#    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA


PUBLIC_INCLUDE_DIR=./include
SRC_DIR=./src
SRC_INCLUDE_DIR=$(SRC_DIR)/include

RESULTS_DIR=./results
RESULTS_REPORT_DIR=$(RESULTS_DIR)/reports
RESULTS_ARTIFACTS_DIR=$(RESULTS_DIR)/artifacts/

PKG_SRC=$(wildcard $(SRC_DIR)/*.c)

CFLAGS+=-Wall -Wextra -Werror -Wformat=2 -Wstrict-prototypes -Wcast-qual
CFLAGS+=-Wvla -Wstack-protector -fstack-protector-all -fPIC
CFLAGS+=-fno-builtin-strlen -fno-common -std=c99
CFLAGS+=-I$(PUBLIC_INCLUDE_DIR) -I$(SRC_INCLUDE_DIR)

CC=gcc
LD=gcc
GIT=git

MKDIR=mkdir -p

$(RESULTS_ARTIFACTS_DIR) $(RESULTS_REPORT_DIR):
	$(V) $(MKDIR) $@

