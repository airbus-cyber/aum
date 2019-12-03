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

#include <stdint.h>
#include <stdarg.h>
#include <aum/mock.h>
#include <mock_call_sequence.h>


/******************************************************************************
 * Fonctions                                                                  *
 ******************************************************************************/

/*! \brief Allocation d'un descripteur de mock
 *
 * \param[in]    function_name      Nom de la fonction mockée
 *
 * \return       Pointeur sur le descripteur de mock alloué
 *               NULL si échec
 */
mock_t *mock_alloc(const char *function_name);

mock_call_sequence_t *mock_get_calls(mock_t *this);

/*! \brief Désallocation d'un descripteur de mock
 *
 * \param[in]    mock               Descripteur de mock à désallouer
 */
void mock_free(mock_t *mock);

void mock_return_set(mock_t *mock, unsigned long    return_value);

/*! \brief Configuration du code de retour du wrapper de mock
 *
 * \param[in]    mock               Descripteur de mock à configurer
 * \param[in]    return_value       Valeur à retourner lors de l'appel de la fonction
 *                                  mockée
 * \param[in]    call_number        Occurence de l'appel à la fonction mockée
 *                                  pour laquelle forcer un retour. Commence à 1
 *                                  pour le premier appel
 */
void mock_return_set_at(mock_t *mock, unsigned long return_value, size_t call_number);

/*! \brief Récupération du code de retour du wrapper de mock
 *
 * \param[in]    mock               Descripteur de mock cible
 *
 * \param[out]   return_value       Valeur de retour à retourner par le wrapper
 *                                  de mock
 *
 * \retval       true        Pas de retour
 * \retval       false       Retour forcé à effectuer avec la valeur
 *                           retournée dans `return_value`
 */
bool mock_return_get(mock_t *mock, unsigned long *return_value);

/*! \brief Récupération de la fausse fonction à exécuter par le wrapper de mock
 *
 * \param[in]    mock               Descripteur de mock cible
 *
 * \return       Adresse de la fonction à exécuter
 *               NULL si pas de fausse fonction configurée
 */
void *mock_fake_function_get(mock_t *mock);

/*! \brief Configuration de la fausse fonction à exécuter par le wrapper de mock
 *
 * \param[in]    mock               Descripteur de mock cible
 * \param[in]    fake_function      Adresse de la fausse fonction à installer
 */
void mock_fake_function_set(mock_t *mock, void *fake_function);

/*! \brief Récupère le compteur d'appels du mock cible
 *
 * \param[in]   mock                Descripteur de mock cible
 *
 * \return      Nombre d'appels effectués à la fonction mockée depuis le
 *              dernier reset
 */
size_t mock_call_count_get(mock_t *mock);

/*! \brief Incrémente le compteur d'appels du mock cible
 *
 * \param[in]   mock                Descripteur de mock cible
 */
void mock_call_count_increment(mock_t *mock);

/*! \brief Enregistrement des arguments de l'appel dans le descripteur de mock
 *
 * \param[in]   mock                Descripteur de mock cible
 * \param[in]   arguments           Arguments à enregistrer
 *
 * \retval      true                Succès de l'enregistrement des arguments
 * \retval      false               Echec de l'enregistrement des arguments
 */
bool mock_register_arguments(mock_t *mock, size_t arguments_count, va_list arguments);

/*! \brief Récupération des arguments du dernier appel à la fonction mockée
 */
bool mock_get_argument(mock_t *mock, uint32_t position, mock_argument_t *argument);

bool mock_has_name(mock_t *this, const char *name);

const char *mock_get_function_name(mock_t *this);
