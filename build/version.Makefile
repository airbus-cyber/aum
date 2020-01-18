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


ifndef RESULTS_ARTIFACTS_DIR
  $(error "Variable RESULTS_ARTIFACTS_DIR should be defined")
endif

ifndef NAME
  $(error "Variable NAME should be defined")
endif

ifndef VERSION
  $(error "Variable VERSION should be defined")
endif

ifndef REPOSITORY
  $(error "Variable REPOSITORY should be defined")
endif

ifndef GIT
  $(error "Variable GIT should be defined")
endif

RESULTS_VERSION_FILE=$(RESULTS_ARTIFACTS_DIR)/version.txt

$(RESULTS_VERSION_FILE): | $(RESULTS_ARTIFACTS_DIR)
	$(V) echo "NAME="$(NAME) > $(RESULTS_VERSION_FILE)
	$(V) echo "VERSION="$(VERSION) >> $(RESULTS_VERSION_FILE)
	$(V) echo "REPOSITORY=$(REPOSITORY)" >> $(RESULTS_VERSION_FILE)
	$(V) echo "REVISION="$(shell $(GIT) rev-parse HEAD^{commit}) >> $(RESULTS_VERSION_FILE)

.PHONY: version

version: $(RESULTS_VERSION_FILE)

help::
	$(info version        Creates version file)

