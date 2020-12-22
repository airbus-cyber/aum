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
#include <mock_library.h>
#include <mock_list.h>

struct mock_library_s {
    mock_list_t *mock_list;
};

mock_library_t *mock_library_create(void)
{
    mock_library_t *this = malloc(sizeof(mock_library_t));
    if (this == NULL) {
        return NULL;
    }

    this->mock_list = NULL;

    return this;
}

static mock_t *_add_mock(mock_library_t *this, const char *function_name)
{
    mock_t *mock = mock_alloc(function_name);
    if (mock == NULL) {
        return NULL;
    }
    mock_list_t *new_mock_list = mock_list_append(this->mock_list, mock);
    if (new_mock_list == NULL) {
        mock_free(mock);
        return NULL;
    }
    this->mock_list = new_mock_list;
    return mock;
}

mock_t *mock_library_search_mock(mock_library_t *this, const char *name)
{
    mock_t *mock = mock_list_search(this->mock_list, name);
    if (mock == NULL) {
        mock = _add_mock(this, name);
    }
    return mock;
}

void mock_library_reset(mock_library_t *this)
{
    mock_list_destroy(this->mock_list);
    this->mock_list = NULL;
}

void mock_library_destroy(mock_library_t *this)
{
    mock_library_reset(this);
    free(this);
}

