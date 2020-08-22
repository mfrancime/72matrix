/***************************************************
****************************************************
**                                                **
**                                                **
**            ent�te classe "structures"          **
**                                                **
**                  Thomas John                   **
**           thomas.john@open-design.be           **
**                                                **
**                                                **
****************************************************
***************************************************/

#ifndef C_STRUCTURES_H

	#define C_STRUCTURES_H
	
	#include	<gl\gl.h>

	// structure contenant les infos sur la cam�ra
	struct infos_cam
	{

		// �tat de la classe
		int etat;
			
		// les coordonn�es du point vers lequel la cam�ra "regarde"
		// the coordinates of the point to which the camera "looks"
		double m_x_t;
		double m_y_t;
		double m_z_t;

		// les coordonn�es de la cam�ra (l'oeuil)
		// the coordinates of the camera (the eye)
		double m_x_v;
		double m_y_v;
		double m_z_v;

		// la distance qui s�pare la cible de la cam�ra
		// the distance that separates the target from the camera
		double m_distance;

		// la rotation en �
		double rot;

	};
	
	// structure contenant l'index et la coordonn�e z d'un ligne 3D
	// en cr�ant un tableau de cette structure, il va �tre possible de classer chaque ligne selon leur ordre
	// dans ce cas, l'ordre �quivaut � la coordonn�e "z" de chaque ligne afin d'display chaque ligne depuis
	// la plus �loign�e jusqu'� la plus proche de la cam�ra

	// structure containing the index and the z coordinate of a 3D line
	// by creating a table of this structure, it will be possible to classify each line according to their order
	// in this case, the order equals the "z" coordinate of each line to display each line from
	// the farthest to the nearest camera
	struct ordre_z
	{

		// index de l'instance de la classe "ligne3d1"
		// index of the instance of the class "line3d1"
		int index;

		// sa coordonn�e "z"
		double ordre;

	};

	// infos sur les coordonn�es des diff�rentes lettre de la texture comportant les caract�res "bizares"
	// ces coordonn�es pr�-enregistr�es vont nous permettre de gagner du temps lors du rendu de la sc�ne
	// les listes d'affichage auraient pu �tre utilis�es, mais elles nous obligent � utiliser la fonction
	// de translation "glTranslate" qui, lorsque utilis�e trop souvent, r�duit la vitesse d'ex�cution du
	// programme (ici une dizaine de fps)

	// info on the coordinates of the different letter of the texture with the characters "bizarre"
	// these pre-recorded coordinates will allow us to save time when rendering the scene
	// the display lists could have been used, but they require us to use the function
	// translation "glTranslate" which, when used too often, reduces the execution speed of the
	// program (here about ten fps)

	struct infos_tex_vertes{

		float x1;
		float y1;

		float x2;
		float y2;

		float x3;
		float y3;

		float x4;
		float y4;

	};
	
	// la structure qui va contenir toutes les informations g�n�rales que les classes ont besoin de se partager entre elles

	// the structure that will contain all the general information that classes need to share with each other

	// the structure that will contain all the general information that classes need to share with each other
	// the structure that will contain all the information

	struct infos_gen{


		//######	LISTES D'AFFICHAGE
		// on n'utilise plus les listes d'affichage -> perte de vitesse d'ex�cution
		// lettres vertes
		GLuint lst_lettres_vertes[72];


		// ###### DISPLAY LISTS
		// we no longer use display lists -> loss of execution speed
		// green letters
		// GLuint lst_lettres_vertes [72];

		//######	TEXTURES
		// lettres blanches
		//tex white letters
		GLuint tex_lettres_blanches;

		// lettres vertes
		//	green letters
		GLuint tex_lettres_vertes;

		// particle 1
		GLuint tex_part_1;



		//######	COORDONNEES DE TEXTURES
		// coordonn�es pour les textures aux caract�res bizares (d'autres viendront)
		// coordinates for textures with bizarre characters (others will come)
		infos_tex_vertes info_tex_vertes_sz[72];


		
		//######	AUTRES DONNEES
		// temps �coul� entre l'affichage de deux images (sc�nes)
		// time elapsed between displaying two images (scenes)
		ULONGLONG msec;

		// sert pour le debuggage
		double dist_ttmp;

		// permet de jongler entre diff�rentes fonctions de blending
		// allows you to juggle different blending functions
		GLenum prem;
		GLenum deux;



		//######	LISTE CONTENANT L'INDEX DE CHAQUE LIGNE ET LEUR COORDONNEE Z
		ordre_z * ordre_sz;



		//######	INFOS SUR LA CAMERA
		infos_cam infos_cam_sz;


	};



#endif