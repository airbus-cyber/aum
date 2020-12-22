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
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <mock.h>
#include <mock_call_sequence.h>


// TODO do a review of API and remove dead functions

typedef struct {
  bool always;           /* si vrai, la valeur de retour va être utilisée à chaque appel */
  unsigned int call_number;      /* Index de l'appel auquel la valeur de retour sera utilisée. 
                                    La valeur -1 indique qu'il n'y a pas de valeur de retour */
  unsigned long return_value;
} _return_t;

/******************************************************************************
 * Types & Structures                                                         *
 ******************************************************************************/
/*! \brief Structure interne d'un descripteur de mock */
struct mock_s {
  const char *name;                    /*!< Nom de la fonction mockée */
  void *fake_function;                 /*!< Adresse de la fausse fonction */
  unsigned int call_count;             /*!< Compteur d'appel à la fonction mockée */
  _return_t mock_return;               /*!< Configuration du retour forcé */
  mock_call_sequence_t *calls;         /*!< Sauvegarde des appels */
};

/******************************************************************************
 * Implémentation des fonctions publiques de l'interface                      *
 ******************************************************************************/

mock_t *mock_alloc(const char *function_name)
{
    mock_t *mock = (mock_t *) calloc(1, sizeof(mock_t));
    mock_call_sequence_t *calls = mock_call_sequence_alloc();
    if ((mock == NULL) || (calls == NULL)) {
        free(calls);
        free(mock);
        return NULL;
    }

    mock->name = function_name;
    mock->calls = calls;
    mock->fake_function = NULL;
    mock->mock_return.call_number = -1;
    mock->mock_return.always = false;
    mock->call_count = 0;
    return mock;
}

mock_call_sequence_t *mock_get_calls(mock_t *this)
{
  return this->calls;
}

void mock_free(mock_t *mock)
{
  mock_call_sequence_empty(mock->calls);
  free(mock->calls);
  free(mock);
}

void mock_return_set(mock_t *mock, unsigned long return_value)
{
  mock->mock_return.always = true;
  mock->mock_return.return_value = return_value;
}

void mock_return_set_at(mock_t *mock, unsigned long return_value, size_t call_number)
{
  mock->mock_return.always = false;
  mock->mock_return.return_value = return_value;
  mock->mock_return.call_number = mock->call_count + call_number;
}

bool mock_return_get(mock_t *mock, unsigned long *return_value)
{
  if (mock->mock_return.always == false && mock->mock_return.call_number != mock->call_count) {
    return false;
  }
  *return_value = mock->mock_return.return_value;
  return true;
}

void *mock_fake_function_get(mock_t *mock)
{
    return mock->fake_function;
}

void mock_fake_function_set(mock_t *mock, void *fake_function)
{
  mock->fake_function = fake_function;
}

size_t mock_call_count_get(mock_t *mock)
{
  return mock->call_count;
}

void mock_call_count_increment(mock_t *mock)
{
    mock->call_count++;
}

bool mock_register_arguments(mock_t *mock, size_t arguments_count, mock_argument_t *values)
{
    return mock_call_sequence_add(mock->calls, arguments_count, values);
}

bool mock_get_argument(mock_t *mock, uint32_t position, mock_argument_t *argument)
{
    return mock_call_sequence_get_last(mock->calls, position, argument);
}

bool mock_has_name(mock_t *this, const char *name)
{
    return !strcmp(this->name, name);
}

const char *mock_get_function_name(mock_t *this)
{
    return this->name;
}

