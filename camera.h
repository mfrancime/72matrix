/***************************************************
****************************************************
**                                                **
**                                                **
**             entête classe "camera"             **
**                                                **
**                  Thomas John                   **
**           thomas.john@open-design.be           **
**                                                **
**                                                **
****************************************************
***************************************************/

// ceci sert à ce qu'on ne charge pas deux fois le même header
#ifndef C_CAMERA_H

	#define C_CAMERA_H
	
	#include "structures.h"
	
	class camera

	{
		
		// les données "privées" (variables, fonctions...)
		private:
			
			// structure qui contient les infos générales et notamment celles de la caméra
			infos_gen * infos_tex_tmp;
 
		// les données publiques
		public:

			// le constructeur par défaut
			camera( double x_t, double y_t, double z_t, double x_v, double y_v, double z_v , double distance , struct infos_gen * );

			// le destructeur
			~camera();
			
			// calcul de la position de la caméra
			void calculer();

	};


#endif