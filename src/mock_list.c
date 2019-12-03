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


#include <stdio.h>
#include <mock_list.h>

mock_list_t *mock_list_append(mock_list_t *this, mock_t *mock)
{
    return (mock_list_t *) list_append(this, mock);
}

static bool _mock_has_name(void *element, const char *name)
{
    return mock_has_name((mock_t *) element, name);
}

mock_t *mock_list_search(mock_list_t *this, const char *name)
{
    return list_search(this, _mock_has_name, name);
}

static void _free_mock(void *element)
{
    mock_free((mock_t *) element);
}

void mock_list_destroy(mock_list_t *this)
{
    list_apply(this, _free_mock);
    list_destroy(this);
}

