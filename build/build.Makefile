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


ifndef NAME
  $(error "Variable NAME should be defined")
endif

ifndef PKG_SRC
  $(error "Variable PKG_SRC should be defined")
endif

ifndef SRC_DIR
  $(error "Variable SRC_DIR should be defined")
endif

ifndef LD
  $(error "Variable LD should be defined")
endif

ifndef MKDIR
  $(error "Variable MKDIR should be defined")
endif

ifndef PKG_DEPENDS_CFLAGS
  $(error "Variable PKG_DEPENDS_CFLAGS should be defined")
endif

RESULTS_SRC_DIR=$(RESULTS_DIR)/src
RESULTS_OBJ_DIR=$(RESULTS_SRC_DIR)/obj
RESULTS_BIN_DIR=$(RESULTS_SRC_DIR)/bin
RESULTS_BINARY_NAME=lib$(NAME).so
RESULTS_BINARY=$(RESULTS_BIN_DIR)/$(RESULTS_BINARY_NAME)

SRC_LDFLAGS+=-shared -Wl,-soname,$(RESULTS_BINARY_NAME)
SRC_CFLAGS+=-O2
SRC_CFLAGS+=-D_FORTIFY_SOURCE=2
SRC_CFLAGS+=$(PKG_DEPENDS_CFLAGS)

OBJ=$(patsubst $(SRC_DIR)/%.c,$(RESULTS_OBJ_DIR)/%.o,$(PKG_SRC))

.PHONY: build

build: $(RESULTS_BINARY)

$(RESULTS_BINARY): $(OBJ) | $(RESULTS_BIN_DIR)
	@ echo "LD	$@"
	$(V) $(LD) $(OBJ) $(LDFLAGS) $(SRC_LDFLAGS) -o $@

$(RESULTS_OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(RESULTS_OBJ_DIR)
	@ echo "CC	$<"
	$(V) $(CC) $(CFLAGS) $(SRC_CFLAGS) -c $< -o $@

$(RESULTS_BIN_DIR) $(RESULTS_OBJ_DIR):
	@ $(MKDIR) $@

help::
	$(info build          Builds binary '$(RESULTS_BINARY)')

