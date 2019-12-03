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

#include <mock.h>
#include <list.h>

/*! \brief Liste de mocks */
typedef list_t mock_list_t;

/*! \brief Ajoute un mock dans la liste
 *
 * \param[in]   list            Liste de destination
 * \param[in]   mock            Mock à ajouter dans `list`
 */
mock_list_t *mock_list_append(mock_list_t *list, mock_t *mock);

/*! \brief Recherche un mock dans la liste
 *
 * \param[in]   list            Liste où rechercher
 * \param[in]   name            Nom de la fonction à rechercher
 *
 * \return      Pointeur sur le mock ou NULL si aucun mock pour `name`
 */
mock_t *mock_list_search(mock_list_t *list, const char *name);

/*! \brief Destruction de la liste de mock
 *
 * \param[in]   list            Liste à détruire
 */
void mock_list_destroy(mock_list_t *list);

