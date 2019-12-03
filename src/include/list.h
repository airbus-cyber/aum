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


#pragma once

#include <stdbool.h>


typedef struct list_s list_t;

list_t *list_append(list_t *this, void *element);

void list_destroy(list_t *this);

typedef void (operation_t)(void* element);

void list_apply(list_t *this, operation_t *operation);

typedef void (iter_closure_t)(void* element, void *data);

void list_iter(list_t *this, iter_closure_t *closure, void *data);

typedef bool (predicate_t)(void *element, const char *criteria);

void *list_search(list_t *this, predicate_t *matches, const char *criteria);

