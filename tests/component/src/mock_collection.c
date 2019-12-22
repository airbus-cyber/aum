/*
    AUM: Airbus Unit tests with Mocks for C. AUM is a unit testing framework for C that allows the easy definition and request of mocks.
    Copyright (C) 2019  Airbus Defence and Space

    You should have received a copy of the AUTHORS.md file which lists all contributors.

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <aum.h>
#include <aum_mock_create.h>

/******************************************************************************
 * Création des wrappers de la collection de mocks                            *
 ******************************************************************************/
AUM_MOCK_CREATE_VOID(uid_t, getuid);
AUM_MOCK_CREATE(void *, malloc, size_t);
AUM_MOCK_CREATE(int, chmod, const char *, mode_t);

