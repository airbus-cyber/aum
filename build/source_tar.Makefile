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


ifndef MKDIR
  $(error "Variable MKDIR should be defined")
endif

ifndef GIT
  $(error "Variable GIT should be defined")
endif

ifndef RESULTS_ARTIFACTS_DIR
  $(error "Variable RESULTS_ARTIFACTS_DIR should be defined")
endif

ifndef RESULTS_DEBIAN_PKG_NAME
  $(error "Variable RESULTS_DEBIAN_PKG_NAME should be defined")
endif

RESULTS_SOURCE_ARCHIVE=$(RESULTS_ARTIFACTS_DIR)$(RESULTS_DEBIAN_PKG_NAME).tar

.PHONY: source_tar

source_tar: $(RESULTS_SOURCE_ARCHIVE)

$(RESULTS_SOURCE_ARCHIVE): | $(RESULTS_ARTIFACTS_DIR)
	@ echo "Building archive '$(RESULTS_SOURCE_ARCHIVE)'"
	$(V) $(GIT) archive --format=tar --prefix=$(RESULTS_DEBIAN_PKG_NAME)/ HEAD > $(RESULTS_SOURCE_ARCHIVE)

help::
	$(info source_tar     Generation of source package in $(RESULTS_ARTIFACTS_DIR))

