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


/*!
 * \file
 * \brief Interface sur les mocks interne à la bibliothèque
 */

#pragma once

#include <stddef.h>

/******************************************************************************
 * Types & Structures                                                         *
 ******************************************************************************/

/*! \brief Liste des arguments */
typedef struct mock_call_sequence_s mock_call_sequence_t;

/******************************************************************************
 * Fonctions                                                                  *
 ******************************************************************************/

mock_call_sequence_t *mock_call_sequence_alloc(void);

/*! \brief Enregistrement des arguments dans la liste
 *
 * \param[in]   arguments_list  Liste d'arguments dans laquelle enregistrer
 * \param[in]   arguments       Arguments à enregistrer
 *
 * \retval      true  Succès
 * \retval      false     Echec
 */
bool mock_call_sequence_add(mock_call_sequence_t *this, size_t arguments_count, mock_argument_t *values);

bool mock_call_sequence_contains(mock_call_sequence_t *this, va_list arguments);

bool mock_call_sequence_contains_at(mock_call_sequence_t *this, aum_parameter_t *param, unsigned int position);

/*! \brief Récupération d'un argument dans une liste d'arguments
 */
bool mock_call_sequence_get_last(mock_call_sequence_t *this, unsigned int position, mock_argument_t *argument);

/*! \brief Vide la liste des appels
 *
 * \param[in]   arguments_list  Liste d'arguments à détruire
 */
void mock_call_sequence_empty(mock_call_sequence_t *this);

