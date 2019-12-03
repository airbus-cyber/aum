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
 * \brief Interface pour implémentation des suites et tests
 */

#pragma once

#include <stdbool.h>
#include <aum/test_suite.h>


typedef enum {
  AUM_SUCCESS,
  AUM_FAILURE,
  AUM_ERROR
} aum_runner_result_t;

typedef struct aum_runner_s aum_runner_t;

/******************************************************************************
 * Fonctions                                                                  *
 ******************************************************************************/

/*! \brief Initialisation de l'application de test
 *
 * \param[in]           output_path       Chemin pour génération du rapport
 */
aum_runner_t *aum_runner_create(void);

/*! \brief Enregistrement d'une suites de tests
 *
 * \return              true     Succès
 * \return              false    Echec de l'enregistrement de la suite
 */
bool aum_runner_register_suite(aum_runner_t *this, aum_test_suite_t *suite);

/*! \brief Exécution des suites de tests
 *
 * \return              AUM_SUCCESS     Tous les tests en succès
 * \return              AUM_FAILURE     Au moins un test a échoué
 * \return              AUM_ERROR       Erreur fatale lors de l'exécution des tests
 */
aum_runner_result_t aum_runner_execute_tests(aum_runner_t *this);

aum_runner_result_t aum_runner_execute_single_test(__attribute__((unused)) aum_runner_t *this, const char *suite_name, const char *test_name);

bool aum_runner_print_xml_report(aum_runner_t *this, const char *path);

void aum_runner_destroy(aum_runner_t *this);

