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

ifndef NAME
  $(error "Variable NAME should be defined")
endif

ifndef VERSION
  $(error "Variable VERSION should be defined")
endif

ifndef RESULTS_ARTIFACTS_DIR
  $(error "Variable RESULTS_ARTIFACTS_DIR should be defined")
endif

ifndef RESULTS_PKG_CONTENT_DIR
  $(error "Variable RESULTS_PKG_CONTENT_DIR should be defined")
endif

ifndef DESCRIPTION
  $(error "Variable DESCRIPTION should be defined")
endif

RESULTS_DEBIAN_BUILD_DIR=$(RESULTS_DIR)/debian
RESULTS_DEBIAN_PKG_NAME=$(NAME)_$(VERSION)
RESULTS_DEBIAN_DIR=$(RESULTS_DEBIAN_BUILD_DIR)/$(RESULTS_DEBIAN_PKG_NAME)
RESULTS_DEBIAN_PKG=$(RESULTS_DEBIAN_BUILD_DIR)/$(RESULTS_DEBIAN_PKG_NAME).deb
RESULTS_DEBIAN_METADATA_DIR=$(RESULTS_DEBIAN_DIR)/DEBIAN/

.PHONY: debian

debian: $(RESULTS_PKG_CONTENT_DIR) | $(RESULTS_ARTIFACTS_DIR)
	$(V) $(MKDIR) $(RESULTS_DEBIAN_DIR)
	$(V) $(MKDIR) $(RESULTS_DEBIAN_METADATA_DIR)
	$(V) $(SCRIPT_DIR)/create_md5sums.sh $(RESULTS_PKG_CONTENT_DIR) > $(RESULTS_DEBIAN_METADATA_DIR)/md5sums
	$(V) $(SCRIPT_DIR)/create_control.sh $(NAME) $(VERSION) $(DESCRIPTION) "$(DEB_DEPENDS)" > $(RESULTS_DEBIAN_METADATA_DIR)control
	$(V) cp debian/postinst $(RESULTS_DEBIAN_METADATA_DIR)
	$(V) cp -r $(RESULTS_PKG_CONTENT_DIR)/* $(RESULTS_DEBIAN_DIR)
	$(V) cd $(RESULTS_DEBIAN_BUILD_DIR); fakeroot dpkg --build $(RESULTS_DEBIAN_PKG_NAME)
	$(V) cp $(RESULTS_DEBIAN_PKG) $(RESULTS_ARTIFACTS_DIR)

help::
	$(info debian         Generation of Debian package in $(RESULTS_ARTIFACTS_DIR))

help_variables::
	$(info DEB_DEPENDS       Dependence for debian packaging. Will be present in control file)

