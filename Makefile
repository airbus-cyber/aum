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


##
## Makefile Projet
##
## Variables prises en compte sur la ligne de commande:
##
## PKG_CUNIT_OUTPUT=XML    Génération des rapports CUnit en XML
## VERBOSE=1               Affichage des commandes
## DESTDIR=/path           Pour règle install
##

# Nom du paquet
NAME=aum
REPOSITORY=aum
# Description du paquet
DESCRIPTION="AUM Testing Framework"
# Version du paquet
VERSION=0.10.0
# Dépendances du paquet - Ces dépendances doivent fournir un fichier pkgconfig
DEPENDS=cunit
# Dépendances Debian du paquet - Ces dépendances seront renseignées dans le fichier control du paquet Debian
DEB_DEPENDS=libcunit1, libcunit1-dev
# Flags de compilation additionnels
CFLAGS+=-D_AUM_VERSION=\"$(VERSION)\" -D_GNU_SOURCE
# Additional link options for unit tests
TESTU_LDFLAGS+=-Wl,-wrap,chmod
TESTC_LDFLAGS+=-Wl,-wrap,getuid -Wl,-wrap,malloc -Wl,-wrap,chmod -Wl,-wrap,vasprintf -Wl,-wrap,longjmp

include Makefile.generic

