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

ifndef PUBLIC_INCLUDE_DIR
  $(error "Variable PUBLIC_INCLUDE_DIR should be defined")
endif

ifndef RESULTS_REPORT_DIR
  $(error "Variable RESULTS_REPORT_DIR should be defined")
endif

ifndef RESULTS_DIR
  $(error "Variable RESULTS_DIR should be defined")
endif

ifndef CONFIG_INCLUDEDIR
  $(error "Variable CONFIG_INCLUDEDIR should be defined")
endif

ifndef SCRIPT_DIR
  $(error "Variable SCRIPT_DIR should be defined")
endif

SLOCCOUNT=sloccount
RESULTS_SLOCCOUNT_DATA_DIR=$(RESULTS_DIR)/slocdata
SLOCCOUNT_OPTIONS=--datadir $(RESULTS_SLOCCOUNT_DATA_DIR) --details --wide $(SRC_DIR) $(PUBLIC_INCLUDE_DIR)

.PHONY: sloccount

sloccount: | $(RESULTS_SLOCCOUNT_DATA_DIR) $(RESULTS_REPORT_DIR)
	$(V) $(SLOCCOUNT) $(SLOCCOUNT_OPTIONS) > $(RESULTS_REPORT_DIR)/sloccount.sc

$(RESULTS_SLOCCOUNT_DATA_DIR):
	$(V) $(MKDIR) $@

help::
	$(info sloccount      Counts lines of code)

.PHONY: cppcheck

CPPCHECK=cppcheck \
         --enable=all --force --suppress=autovarInvalidDeallocation --suppress=missingIncludeSystem --suppress=redundantAssignment \
         --inconclusive --xml --xml-version=2 --verbose --inline-suppr 

cppcheck: | $(RESULTS_REPORT_DIR)
	$(V) $(CPPCHECK) -I $(CONFIG_INCLUDEDIR) $(SRC_DIR) 2> $(RESULTS_REPORT_DIR)/cppcheck.xml

help::
	$(info cppcheck       Runs cppcheck)

.PHONY: customcheck

customcheck:
	$(V) $(SCRIPT_DIR)/customcheck.sh

help::
	$(info customcheck    Runs custom checks)

