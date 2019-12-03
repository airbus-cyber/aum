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


ifndef SRC_DIR
  $(error "Variable SRC_DIR should be defined")
endif

ifndef PKG_SRC
  $(error "Variable PKG_SRC should be defined")
endif

ifndef RESULTS_DIR
  $(error "Variable RESULTS_DIR should be defined")
endif

ifndef RESULTS_REPORT_DIR
  $(error "Variable RESULTS_REPORT_DIR should be defined")
endif

ifndef LD
  $(error "Variable LD should be defined")
endif

ifndef PKGCONFIG
  $(error "Variable PKGCONFIG should be defined")
endif

ifndef COMMAND_SUCCESS
  $(error "Variable COMMAND_SUCCESS should be defined")
endif

ifndef PKG_DEPENDS_CFLAGS
  $(error "Variable PKG_DEPENDS_CFLAGS should be defined")
endif

ifndef PKG_DEPENDS_LIBRARY_PATH
  $(error "Variable PKG_DEPENDS_LIBRARY_PATH should be defined")
endif

RESULTS_TESTU_REPORT=$(RESULTS_REPORT_DIR)/testu.xml

TESTU_DEPENDS+=cunit
# TODO most probably move this out in configure?
TESTU_DEPENDS_RESULTS=$(shell $(PKGCONFIG) --cflags $(TESTU_DEPENDS) 2>&1 > /dev/null ; echo $$?)

ifneq ($(TESTU_DEPENDS_RESULTS), $(COMMAND_SUCCESS))
$(error Unknown dependence among test dependences: $(TESTU_DEPENDS))
endif

TESTU_DIR=./tests/unit
TESTU_INCLUDE_DIR=$(TESTU_DIR)/include

# Build tests

RESULTS_TESTU_DIR=$(RESULTS_DIR)/testu
RESULTS_TESTU_OBJ_DIR=$(RESULTS_TESTU_DIR)/obj
RESULTS_TESTU_BIN_DIR=$(RESULTS_TESTU_DIR)/bin
RESULTS_TESTU_BINARY_NAME=testu
RESULTS_TESTU_BINARY=$(RESULTS_TESTU_BIN_DIR)/$(RESULTS_TESTU_BINARY_NAME)

TESTU_SRC=$(wildcard $(TESTU_DIR)/*.c)

TESTU_PKG_OBJ=$(patsubst $(SRC_DIR)/%.c,$(RESULTS_TESTU_OBJ_DIR)/%.o,$(PKG_SRC))
TESTU_OBJ=$(patsubst $(TESTU_DIR)/%.c,$(RESULTS_TESTU_OBJ_DIR)/%.o,$(TESTU_SRC))

TESTU_DEPENDS_CFLAGS=$(shell $(PKGCONFIG) --cflags $(TESTU_DEPENDS) 2> /dev/null)
TESTU_DEPENDS_LDFLAGS=$(shell $(PKGCONFIG) --libs $(TESTU_DEPENDS) 2> /dev/null)

GCOV_CFLAGS=-fprofile-arcs -ftest-coverage
TESTU_CFLAGS+=-I$(TESTU_INCLUDE_DIR)
TESTU_CFLAGS+=-ggdb3 -O0 $(GCOV_CFLAGS)
TESTU_CFLAGS+=$(PKG_DEPENDS_CFLAGS) $(TESTU_DEPENDS_CFLAGS)

GCOV_LDFLAGS=-lgcov -coverage
TESTU_LDFLAGS+=$(TESTU_DEPENDS_LDFLAGS) $(GCOV_LDFLAGS)

$(RESULTS_TESTU_BINARY): $(TESTU_PKG_OBJ) $(TESTU_OBJ) | $(RESULTS_TESTU_BIN_DIR)
	@ echo "LD	$@"
	$(V) $(LD) $(TESTU_PKG_OBJ) $(TESTU_OBJ) $(LDFLAGS) $(TESTU_LDFLAGS) -o $@

$(RESULTS_TESTU_OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(RESULTS_TESTU_OBJ_DIR)
	@ echo "CC	$<"
	$(V) $(CC) $(CFLAGS) $(TESTU_CFLAGS) -c $< -o $@

$(RESULTS_TESTU_OBJ_DIR)/%.o: $(TESTU_DIR)/%.c | $(RESULTS_TESTU_OBJ_DIR)
	@ echo "CC	$<"
	$(V) $(CC) $(CFLAGS) $(TESTU_CFLAGS) -c $< -o $@

$(RESULTS_TESTU_OBJ_DIR) $(RESULTS_TESTU_BIN_DIR):
	@ $(MKDIR) $@

# Run tests
TESTU_DEPENDS_LIBRARY_PATH=$(shell $(PKGCONFIG) --variable=libdir $(TESTU_DEPENDS) | tr ' ' ':')

TESTU_LIBRARY_PATH=$(LD_LIBRARY_PATH):$(CONFIG_LIBDIR):$(TESTU_DEPENDS_LIBRARY_PATH):$(PKG_DEPENDS_LIBRARY_PATH)

.PHONY: runtestu

runtestu: $(RESULTS_TESTU_BINARY) | $(RESULTS_REPORT_DIR)
	$(V) LD_LIBRARY_PATH=$(TESTU_LIBRARY_PATH) $(RESULTS_TESTU_BINARY) -o $(RESULTS_TESTU_REPORT)

.PHONY: valgrindu

VALGRIND_TESTU_LOG_PATH=$(RESULTS_REPORT_DIR)/$(RESULTS_TESTU_BINARY_NAME)-valgrind.log
VALGRIND_TESTU_REPORT_PATH=$(RESULTS_REPORT_DIR)/$(RESULTS_TESTU_BINARY_NAME)-valgrind.xml
VALGRIND_TESTU_OPTIONS=--log-file=$(VALGRIND_TESTU_LOG_PATH) --xml-file=$(VALGRIND_TESTU_REPORT_PATH)
FDLEAK_TESTU_REPORT_PATH=$(RESULTS_REPORT_DIR)/valgrind-testu-fdleak.xml

# TODO clean this up by having a script to wrap call to valgrind...
# TODO then, if necessary add some check towards missing dependences
valgrindu: $(RESULTS_TESTU_BINARY) | $(RESULTS_REPORT_DIR)
	$(V) LD_LIBRARY_PATH=$(TESTU_LIBRARY_PATH) $(VALGRIND) $(VALGRIND_TESTU_OPTIONS) $(RESULTS_TESTU_BINARY) -o $(RESULTS_TESTU_REPORT)
	$(V) $(CLEAN_VALGRIND_REPORT) $(VALGRIND_TESTU_REPORT_PATH)
	$(V) $(GENERATE_FDLEAK_REPORT) $(VALGRIND_TESTU_LOG_PATH) $(VALGRIND_TESTU_REPORT_PATH) $(FDLEAK_TESTU_REPORT_PATH)

.PHONY: rungcov 

GCOV=gcovr --xml
GCOV_REPORT_PATH=$(RESULTS_REPORT_DIR)/coverage.xml

rungcov: $(RESULTS_TESTU_BINARY) | $(RESULTS_REPORT_DIR)
	$(V) LD_LIBRARY_PATH=$(TESTU_LIBRARY_PATH) $(RESULTS_TESTU_BINARY) -o $(RESULTS_TESTU_REPORT)
	$(V) $(GCOV) --root=. --output=$(GCOV_REPORT_PATH)

help::
	$(info runtestu       Exécution de la suite de tests unitaires - Rapport CUnit : '$(RESULTS_REPORT_DIR)')
	$(info valgrindu      Exécution de la suite de tests unitaires par Valgrind - Rapport Valgrind : '$(VALGRIND_TESTU_REPORT_PATH)')
	$(info rungcov        Exécution de la suite de tests unitaires avec gcov - Rapport GCov : '$(GCOV_REPORT_PATH)')

help_variables::
	$(info TESTU_DEPENDS     Additional dependences for tests)
	$(info TESTU_LDFLAGS     Linker flags for unit tests compilation)

