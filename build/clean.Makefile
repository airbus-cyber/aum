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


ifndef RESULTS_DIR
  $(error "Variable RESULTS_DIR should be defined")
endif

ifndef MAKEFILE_DEFS_FILE
  $(error "Variable MAKEFILE_DEFS_FILE should be defined")
endif

RM=rm -rf

.PHONY: clean

clean:
	@ echo "RM	$(RESULTS_DIR)"
	$(V) $(RM) $(RESULTS_DIR)
	$(V) find . -name "*~" -type f -delete

.PHONY: distclean

distclean: clean
	@ echo "RM	$(MAKEFILE_DEFS_FILE)"
	$(V) $(RM) $(MAKEFILE_DEFS_FILE)

help::
	$(info clean          Deletes all files that are created by building)
	$(info distclean      Deletes all files that are created by configuring or building)

