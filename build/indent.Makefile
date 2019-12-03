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


ifndef PKG_SRC
  $(error "Variable PKG_SRC should be defined")
endif

ifndef TESTU_SRC
  $(error "Variable TESTU_SRC should be defined")
endif

INDENT=indent
INDENT_OPTIONS=-bap -br -blf -bli0 -bls -cbi0 -cdw -ce -ci0 -cli4 -cs
INDENT_OPTIONS+= -di4 -hnl -i4 -ip8 -l160 -lc160 -nbc -ncdb -ndj -nfc1 -nfca
INDENT_OPTIONS+= -npcs -nprs -npsl -saf -sai -saw -nsc -nut

.PHONY: indent

indent:
	$(V) $(INDENT) $(INDENT_OPTIONS) $(PKG_SRC) $(TESTU_SRC)

help::
	$(info indent         Automatic code indentation)
