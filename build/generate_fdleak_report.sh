#!/bin/sh
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


set -e

VALGRIND_LOG_PATH=$1
VALGRIND_REPORT_PATH=$2
FDLEAK_REPORT_PATH=$3

if [ "$(egrep 'FILE DESCRIPTORS:' ${VALGRIND_LOG_PATH} | grep -v -E ' [0-5] open at exit')" = "" ]
then
	HAS_LEAKS=0
else
	HAS_LEAKS=0
fi

echo "<?xml version=\"1.0\" ?>" > ${FDLEAK_REPORT_PATH}
echo "<REPORT><FD_LEAK>${HAS_LEAKS}</FD_LEAK><VALGRIND_REPORT_PATH>${VALGRIND_REPORT_PATH}</VALGRIND_REPORT_PATH></REPORT>" >> ${FDLEAK_REPORT_PATH}

