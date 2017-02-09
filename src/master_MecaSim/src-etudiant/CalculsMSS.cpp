/*
 * CalculsMSS.cpp :
 * Copyright (C) 2016 Florence Zara, LIRIS
 *               florence.zara@liris.univ-lyon1.fr
 *               http://liris.cnrs.fr/florence.zara/
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/** \file CalculsMSS.cpp
Programme calculant pour chaque particule i d un MSS son etat au pas de temps suivant 
 (methode d 'Euler semi-implicite) : principales fonctions de calculs.
\brief Fonctions de calculs de la methode semi-implicite sur un systeme masses-ressorts.
*/ 

#include <stdio.h>
#include <math.h>
#include <vector>
#include <iostream>

#include "vec.h"
#include "ObjetSimule.h"
#include "ObjetSimuleMSS.h"
#include "Viewer.h"

using namespace std;





/**
* Calcul des forces appliquees sur les particules du systeme masses-ressorts.
 */
void ObjetSimuleMSS::CalculForceSpring()
{
	/// f = somme_i (ki * (l(i,j)-l_0(i,j)) * uij ) + (nuij * (vi - vj) * uij) + (m*g) + force_ext
	
	/// Rq : Les forces dues a la gravite et au vent sont ajoutees lors du calcul de l acceleration
	
	
	std::vector<Ressort *>  listRessorts = _SytemeMasseRessort->GetRessortList();
	
	Particule * A;
	Particule * B;

	float raideur;
	float longrepos;
	for(unsigned int i=0;i<listRessorts.size();i++){
		//Raideur du ressort
		raideur = listRessorts[i]->GetRaideur();
		//longueur au repos du ressort
		longrepos=listRessorts[i]->GetLrepos();

		//récupération des particules liées au ressort
		A = listRessorts[i]->GetParticuleA();
		B = listRessorts[i]->GetParticuleB();

		//Récupération des positions des particules
		Vector posA =A->GetPosition();
		Vector posB = B->GetPosition();

		//Calcul des forces pour chaque coordonnées.
		float forceX=-raideur*((posB.x - posA.x)-longrepos);
		float forceY=-raideur*((posB.y - posA.y)-longrepos);
		float forceZ=-raideur*((posB.z - posA.z)-longrepos);


		//Ajout des forces dans le tableau des forces. A + et B a l'inverse de la force calculée
		Force[A->GetId()].x += forceX;
		Force[A->GetId()].y += forceY;
		Force[A->GetId()].z += forceZ;

		Force[B->GetId()].x -= forceX;
		Force[B->GetId()].y -= forceY;
		Force[B->GetId()].z -= forceZ;
    }
		
}//void


/**
 * Gestion des collisions avec le sol - plan (x,y,z).
 */
void ObjetSimuleMSS::CollisionPlan(float x, float y, float z)
{
    /// Arret de la vitesse quand touche le plan
   
    
}// void

