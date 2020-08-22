/***************************************************
****************************************************
**                                                **
**                                                **
**         entête classe "effet_particle"        **
**                                                **
**                  Thomas John                   **
**           thomas.john@open-design.be           **
**                                                **
**                                                **
****************************************************
***************************************************/

// ceci sert à ce qu'on ne charge pas deux fois le même header
#ifndef C_EFFET_particle_H

	#define C_EFFET_particle_H

	#include "structures.h"

	class effet_particle

	{
		
		// les données "privées" (variables, fonctions...)
		private:
			
			// structure qui va contenir les informations sur chaque particles
			struct particles {
				// coordonnées
				double x;
				double y;
				double z;
				// vitesse
				// speed
				double vitesse;
				// direction
				double d_x;
				double d_y;
				double d_z;
				// vie
				double vie;
				//taille
				double taille;
				// couleur
				double r;
				double g;
				double b;
			};

			// on déclare la variable qui va contenir notre tableau de particles
			particles* t_particles;

			// fonction d'initialisation d'une particle
			void init_particle( int particlesz );

			// structure qui contient toutes les infos générales
			infos_gen * infos_tex_tmp;

		
		// les données publiques
		public:
			
			// état de la classe
			// state of the class
			int etat;

			// les coordonnées (x, y, z)
			double m_x;
			double m_y;
			double m_z;

			// la vitesse des particles
			// the speed of the particles
			double m_vitesse;

			// le nombre max de particles à display en même temps
			// the max number of particles to display at the same time
			int m_nombre_tot;

			// le nombre de particles couramment affichées
			// the number of particles currently displayed
			int m_nombre_actifs;

			// le temps qu'il faut (en unité) pour créer une(de) nouvelle(s) particle(s)
			// the time it takes (in units) to create a new particle (s)
			ULONGLONG m_temps_tot;
			ULONGLONG m_temps;

			// nombre de particles émises en même temps
			// number of particles emitted at the same time
			int m_nbr_emission;



			// le constructeur par défaut
			effet_particle( double x, double y, double z, double vitesse, int nombre_tot , struct infos_gen * , int vitesse_emission , int nbr_emission );

			// le destructeur
			~effet_particle( );
			
			// calcul de la position des particles
			void calculer();
		
			// affichage des particles
			void display();
			

	};


#endif