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

ifndef RESULTS_DIR
  $(error "Variable RESULTS_DIR should be defined")
endif

DOC_DIR=./doc

RESULTS_DOC_DIR=$(RESULTS_DIR)/doc
RESULTS_DOC=$(RESULTS_DOC_DIR)/html

DOXYGEN=doxygen

.PHONY: doc

doc: $(RESULTS_DOC)

$(RESULTS_DOC): | $(RESULTS_DOC_DIR)
	$(V) ( cat $(DOC_DIR)/Doxyfile; echo "OUTPUT_DIRECTORY=$(RESULTS_DOC_DIR)") | $(DOXYGEN) -

$(RESULTS_DOC_DIR):
	$(V) $(MKDIR) $(RESULTS_DOC_DIR)

help::
	$(info doc            Génération de la documentation Doxygen dans '$(RESULTS_DOC_DIR)')

