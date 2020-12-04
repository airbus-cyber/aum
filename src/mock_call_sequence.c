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


#include <stdarg.h>
#include <stdlib.h>
#include <setjmp.h>
#include <aum/mock.h>
#include <mock_call_sequence.h>

// this module defines a structure which represents a sequence of calls for a given function

/******************************************************************************
 * Types & Structures                                                         *
 ******************************************************************************/
struct mock_call_s {
  mock_argument_t             *value;  /*!< Tableau des arguments */
  struct mock_call_s *next;   /*!< Pointeur sur les arguments de l'appel suivant */
};

/*! \brief Type opaque des arguments des mocks */
typedef struct mock_call_s mock_call_t;

struct mock_call_sequence_s {
  size_t                count;   /*!< Nombre d'arguments */
  mock_call_t *last_call;    /*!< The list is in reverse: the last_call first */
};

/******************************************************************************
 * Implémentation des fonctions locales à cette interface                     *
 ******************************************************************************/

static mock_call_t *_mock_call_alloc(size_t count)
{
  mock_call_t *mock_arguments = (mock_call_t *) calloc(1, sizeof(mock_call_t));
  mock_argument_t *value = (mock_argument_t *) malloc(count * sizeof(mock_argument_t));
  if (mock_arguments == NULL || value == NULL) {
    free(mock_arguments);
    free(value);
    return NULL;
  }

  mock_arguments->value = value;
  return mock_arguments;
}

static void _mock_call_free(mock_call_t *mock_arguments)
{
  free(mock_arguments->value);
  free(mock_arguments);
}

static mock_call_t *_mock_arguments_create(size_t arguments_count, mock_argument_t *values)
{
  mock_call_t *mock_arguments = _mock_call_alloc(arguments_count);
  if (mock_arguments == NULL) {
    return NULL;
  }

  memcpy(mock_arguments->value, values, arguments_count * sizeof(mock_argument_t));

  return mock_arguments;
}

/******************************************************************************
 * Implémentation des fonctions publiques de l'interface                      *
 ******************************************************************************/

mock_call_sequence_t *mock_call_sequence_alloc() {
    return (mock_call_sequence_t *) calloc(1, sizeof(mock_call_sequence_t));
}

bool mock_call_sequence_add(mock_call_sequence_t *this, size_t arguments_count, mock_argument_t *values)
{
    mock_call_t *mock_arguments = _mock_arguments_create(arguments_count, values);
    if (mock_arguments == NULL) {
        return false;
    }
    this->count = arguments_count;

    mock_arguments->next = this->last_call;
    this->last_call = mock_arguments;
    return true;
}

bool mock_call_sequence_get_last(mock_call_sequence_t *this, uint32_t position, mock_argument_t *argument)
{
    mock_call_t *call = this->last_call;
    if (call == NULL) {
        return false;
    }
    *argument = call->value[position];
    return true;
}

static bool _argument_matches(mock_argument_t arg, aum_parameter_t *param)
{
  switch (param->type) {
  case AUM_PARAMETER_TYPE_STRING:
    if (strncmp(param->value.ptr, (char *)arg, strlen(param->value.ptr) + 1)) {
      return false;
    }
    break;
  case AUM_PARAMETER_TYPE_RAW:
    if (arg != param->value.raw) return false;
    break;
  }
  return true;
}

static bool _all_arguments_match(size_t count, mock_argument_t *value, va_list expected_arguments)
{
  size_t i;
  for (i = 0; i < count; i++)
  {
    aum_parameter_t *expected_argument = va_arg(expected_arguments, aum_parameter_t *);
    if (!_argument_matches(value[i], expected_argument)) return false;
  }
  return true;
}

bool mock_call_sequence_contains_at(mock_call_sequence_t *this, aum_parameter_t *param, int position)
{
  mock_call_t *current_call = this->last_call;

  while (current_call != NULL)
  {
    mock_argument_t *call_value = current_call->value;

    mock_argument_t current_argument = call_value[position];
    bool arguments_matches = _argument_matches(current_argument, param);

    if (arguments_matches) return true;
    current_call = current_call->next;
  }
  return false;
}

bool mock_call_sequence_contains(mock_call_sequence_t *this, va_list arguments)
{
  mock_call_t *current_call = this->last_call;

  while (current_call != NULL)
  {
    mock_argument_t *call_value = current_call->value;

    va_list expected_arguments;
    va_copy(expected_arguments, arguments);
    bool call_matches = _all_arguments_match(this->count, call_value, expected_arguments);
    va_end(expected_arguments);

    if (call_matches) return true;
    current_call = current_call->next;
  }
  return false;
}

void mock_call_sequence_empty(mock_call_sequence_t *this)
{
  mock_call_t *current_call = this->last_call;

  while (current_call != NULL) {
    mock_call_t *next_call = current_call->next;
    _mock_call_free(current_call);
    current_call = next_call;
  }
  this->last_call = NULL;
}

