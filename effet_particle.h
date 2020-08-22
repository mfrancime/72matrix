/***************************************************
****************************************************
**                                                **
**                                                **
**         ent�te classe "effet_particle"        **
**                                                **
**                  Thomas John                   **
**           thomas.john@open-design.be           **
**                                                **
**                                                **
****************************************************
***************************************************/

// ceci sert � ce qu'on ne charge pas deux fois le m�me header
#ifndef C_EFFET_particle_H

	#define C_EFFET_particle_H

	#include "structures.h"

	class effet_particle

	{
		
		// les donn�es "priv�es" (variables, fonctions...)
		private:
			
			// structure qui va contenir les informations sur chaque particles
			struct particles {
				// coordonn�es
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

			// on d�clare la variable qui va contenir notre tableau de particles
			particles* t_particles;

			// fonction d'initialisation d'une particle
			void init_particle( int particlesz );

			// structure qui contient toutes les infos g�n�rales
			infos_gen * infos_tex_tmp;

		
		// les donn�es publiques
		public:
			
			// �tat de la classe
			// state of the class
			int etat;

			// les coordonn�es (x, y, z)
			double m_x;
			double m_y;
			double m_z;

			// la vitesse des particles
			// the speed of the particles
			double m_vitesse;

			// le nombre max de particles � display en m�me temps
			// the max number of particles to display at the same time
			int m_nombre_tot;

			// le nombre de particles couramment affich�es
			// the number of particles currently displayed
			int m_nombre_actifs;

			// le temps qu'il faut (en unit�) pour cr�er une(de) nouvelle(s) particle(s)
			// the time it takes (in units) to create a new particle (s)
			ULONGLONG m_temps_tot;
			ULONGLONG m_temps;

			// nombre de particles �mises en m�me temps
			// number of particles emitted at the same time
			int m_nbr_emission;



			// le constructeur par d�faut
			effet_particle( double x, double y, double z, double vitesse, int nombre_tot , struct infos_gen * , int vitesse_emission , int nbr_emission );

			// le destructeur
			~effet_particle( );
			
			// calcul de la position des particles
			void calculer();
		
			// affichage des particles
			void display();
			

	};


#endif