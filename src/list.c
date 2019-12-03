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


#include <list.h>
#include <stdlib.h>

struct list_s {
    void *element;
    struct list_s *next;
};

static list_t *_list_alloc(void *element)
{
    list_t *result = (list_t *) calloc(1, sizeof(list_t));
    if (result == NULL) {
        return result;
    }
    result->element = element;
    result->next = NULL;
    return result;
}

list_t *list_append(list_t *this, void *element)
{
    list_t *new_list = _list_alloc(element);
    if (new_list == NULL) {
        return NULL;
    }
    new_list->next = this;
    return new_list;
}

void list_iter(list_t *this, iter_closure_t *closure, void *data)
{
    while (this != NULL) {
        closure(this->element, data);
        this = this->next;
    }
}

static void _apply(void *element, void *data) {
    operation_t *operation = (operation_t *) data;
    operation(element);
}

void list_apply(list_t *this, operation_t *operation)
{
    list_iter(this, _apply, operation);
}

void *list_search(list_t *this, predicate_t *matches, const char *criteria)
{
    while (this != NULL) {
        void *current_element = this->element;
        if (matches(current_element, criteria)) {
            return current_element;
        }
        this = this->next;
    }
    return NULL;
}

void list_destroy(list_t *this)
{
    list_t *next;
    while (this != NULL) {
        next = this->next;
        free(this);
        this = next;
    }
}
