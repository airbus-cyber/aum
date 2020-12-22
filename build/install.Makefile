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

ifndef RESULTS_DIR
  $(error "Variable RESULTS_DIR should be defined")
endif

ifndef RESULTS_BINARY
  $(error "Variable RESULTS_BINARY should be defined")
endif

ifndef DESCRIPTION
  $(error "Variable DESCRIPTION should be defined")
endif

ifndef VERSION
  $(error "Variable VERSION should be defined")
endif

RESULTS_PKG_DIR=$(RESULTS_DIR)/package
RESULTS_PKG_PKGCONFIG_DIR=$(RESULTS_PKG_DIR)/pkgconfig
RESULTS_PKG_PKGCONFIG_NAME=$(NAME).pc
RESULTS_PKG_PKGCONFIG=$(RESULTS_PKG_PKGCONFIG_DIR)/$(RESULTS_PKG_PKGCONFIG_NAME)

$(RESULTS_PKG_PKGCONFIG): $(RESULTS_PKG_PKGCONFIG_DIR)
	$(V) $(SCRIPT_DIR)/create_pc.sh $(NAME) $(VERSION) $(DESCRIPTION) $(DEPENDS) > $(RESULTS_PKG_PKGCONFIG)

$(RESULTS_PKG_PKGCONFIG_DIR):
	$(V) $(MKDIR) $@

RESULTS_PKG_CONTENT_DIR=$(RESULTS_PKG_DIR)/content

.PHONY: install

$(RESULTS_PKG_CONTENT_DIR): DESTDIR=$(RESULTS_PKG_CONTENT_DIR)
$(RESULTS_PKG_CONTENT_DIR): install

install: $(RESULTS_PKG_PKGCONFIG) $(RESULTS_DOC) $(RESULTS_BINARY)
	$(V) $(MKDIR) $(DESTDIR)/$(CONFIG_INCLUDEDIR)
	$(V) cp -r $(PUBLIC_INCLUDE_DIR)/* $(DESTDIR)/$(CONFIG_INCLUDEDIR)
	$(V) $(MKDIR) $(DESTDIR)/$(CONFIG_LIBDIR)
	$(V) cp $(RESULTS_BINARY) $(DESTDIR)/$(CONFIG_LIBDIR)
	$(V) $(MKDIR) $(DESTDIR)/$(CONFIG_LIBDIR)/pkgconfig
	$(V) cp $(RESULTS_PKG_PKGCONFIG) $(DESTDIR)/$(CONFIG_LIBDIR)/pkgconfig
	$(V) $(MKDIR) $(DESTDIR)/$(CONFIG_PREFIX)/share/doc/$(NAME)
	$(V) cp -r $(RESULTS_DOC) $(DESTDIR)/$(CONFIG_PREFIX)/share/doc/$(NAME)

help::
	$(info install        Installs everything relative to DESTDIR)

