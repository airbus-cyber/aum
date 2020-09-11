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

RESULTS_RPM_METADATA_DIR=$(RESULTS_DIR)/rpm

.PHONY: rpm

rpm: $(RESULTS_PKG_CONTENT_DIR) | $(RESULTS_ARTIFACTS_DIR)
	$(V) $(MKDIR) $(RESULTS_RPM_METADATA_DIR)
	$(V) $(MKDIR) /root/rpmbuild/BUILD
	$(V) cp -r $(PUBLIC_INCLUDE_DIR)/ /root/rpmbuild/BUILD
	$(V) cp $(RESULTS_BINARY) /root/rpmbuild/BUILD
	$(V) sed 's|{NAME}|$(NAME)|; s|{VERSION}|$(VERSION)|; s|{DESCRIPTION}|$(DESCRIPTION)|; s|{DEPENDS}|$(DEPENDS)|;' $(SCRIPT_DIR)/packaging/rpm/aum.spec.tpl > $(RESULTS_RPM_METADATA_DIR)/aum.spec
	$(V) rpmbuild -bb $(RESULTS_RPM_METADATA_DIR)/aum.spec
	$(V) cp /root/rpmbuild/RPMS/x86_64/aum-$(VERSION)-1.x86_64.rpm $(RESULTS_ARTIFACTS_DIR)

help::
	$(info rpm         Generates rpm package in $(RESULTS_ARTIFACTS_DIR))


