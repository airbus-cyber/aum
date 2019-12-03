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
 * \file main_page.h
 * \brief Page principale de la documentation Doxygen
 *
 * \mainpage AUM : All Ur Mocks are belongs to us
 *
 * \section aum_intro Introduction
 *
 * Le paquet AUM fournit une bibliothèque implémentant un framework de tests unitaires en C avec une
 * fonctionnalité de mock.
 *
 * \section aum_compile Compilation et installation
 *
 * \subsection aum_compile_depends Dépendances
 *
 * Pour compiler AUM et générer l'ensemble des artifacts, les paquets suivants sont nécessaires:
 * \li <b>CUnit</b>: utilisé comme moteur de gestion des suites de tests. \b ATTENTION : seule la version 2.1-2
 *     est compatible avec AUM, la version suivante (2.1-3) introduisant une rupture d'API.
 * \li <b>doxygen</b>: utilisé pour générer la documentation de l'API et du code source
 * \li <b>graphviz</b>: utilisé par doxygen pour la génération des graphiques de dépendances
 * \li <b>make</b>: pour gestion de la compilation
 * \li <b>equivs</b>: utilitaire utilisé pour la génération du paquet Debian
 * \li <b>pkg-config</b>: utilitaire utilisé pour la gestion des dépendances
 *
 * Utiliser la commande suivante pour installer l'ensemble des dépendances (ou demander à votre administrateur
 * système si vous ne possédez pas un compte privilégié):
 * \verbatim
$ sudo apt-get install libcunit1-dev equivs doxygen graphviz pkg-config
\endverbatim
 *
 * <b>ATTENTION :</b>
 * A partir de Ubuntu 16 (et variantes XUbuntu, etc..), la version par défaut de CUnit est la 2.1-3, incompatible
 * à l'heure actuelle avec AUM. Les paquets libcunit1-dev et libcunit1 ne doivent donc pas être installé par 
 * apt-get mais manuellement.
 *
 * \subsection aum_compile_compile Compilation
 *
 * Les sources de AUM doivent être configuré préalablement à la compilation, à l'aide de la commande suivante:
 * \verbatim
$ ./configure
\endverbatim
 *
 * La commande <i>configure</i> prend des paramètres permettant de spécifier des chemins d'installation
 * non-standards, et génére le fichier <i>Makefile.defs</i>, inclus par le fichier <i>Makefile</i>.
 *
 * Une fois les sources configurées, AUM peut être compilé à l'aide de la commande suivante:
 * \verbatim
$ make
\endverbatim
 *
 * L'exécution réussie de la commande précédente produit le binaire de la bibliothèque, <i>libaum.so</i> dans
 * le répertoire <i>results/pkg/bin</i>.
 *
 * Le fichier <i>Makefile.generic</i>, inclus par le fichier <i>Makefile</i>, fournit d'autres cibles pour la
 * compilation, notamment des tests unitaires, listées par la commande suivante:
 * \verbatim
$ make help
\endverbatim
 *
 * \subsection aum_compile_delivery Livraison
 *
 * Le fichier <i>Makefile.generic</i> fournit les règles de livraison suivantes:
 * \li <i>deb</i> : génération d'un paquet Debian
 *
 * \subsection aum_compile_install Installation
 *
 * Pour installer AUM à partir des sources, exécutez la commande suivante:
 * \verbatim
$ make install
\endverbatim
 *
 * L'exécution réussie de cette commande installe le binaire de la biblitohèque <i>libaum.so</i>, ainsi que les
 * fichiers annexes - fichier de configuration <i>pkgconfig</i>, en-tête de développement, etc... -  dans les
 * chemins spécifiés lors de l'appel au script <i>configure</i>.
 *
 * Pour installer AUM à partir du paquetage Debian de livraison, exécutez la commande suivante:
 * \verbatim
$ sudo dpkg -i aum_0.1.0_all.deb
\endverbatim
 */
