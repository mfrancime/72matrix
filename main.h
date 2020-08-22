/***************************************************
****************************************************
**                                                **
**                                                **
**              entête classe "main"              **
**                                                **
**                  Thomas John                   **
**           thomas.john@open-design.be           **
**                                                **
**                                                **
****************************************************
***************************************************/

#ifndef C_MAIN_H

	#define C_MAIN_H




//##### LIBRAIRIES

	//on inclut les librairies
	#pragma comment( lib, "opengl32.lib" )
	#pragma comment( lib, "glu32.lib" )
	



//##### ENTETES

	//la librairie windows est à inclure avant celle d'opengl
	#include	<windows.h>

	//permet de lire les fichiers .png
	#include	"glpng.h"

	//entêtes opengl
	#include	<gl\gl.h>
	#include	<gl\glu.h>

	//entrée/sortie
	//#include	<stdio.h>

	//permet d'effectuer certaines opérations mathématiques
	#include	<math.h>

	//entête de la classe "camera"
	#include	"camera.h"

	//entête de la classe "Ligne3D1"
	#include	"Ligne3D1.h"

	//contient les structures regroupant toutes sortes d'informations (textures, temps, liste d'affichage...)
	#include	"structures.h"

	//on crée une structure qui va contenir les infos sur les textures et les liste d'affichage
	// we create a structure that will contain the infos about the textures and the list of display
	infos_gen	s_infos_gen;




//##### DEFINITIONS

	//définit le nombre de lignes à display
	// set the number of lines to display
	#define		NBR_LIGNES_MAX_DEF 1000
	int			NBR_LIGNES_MAX = NBR_LIGNES_MAX_DEF;

	//nom de l'application
	#define		NOM_APP "[SSH] Skynet Soul Harvester"
	#define		NOM_APP_FENETRE "[SSH] Skynet Soul Harvester"




//##### VARIABLES (de tout ici)

	//tableau représentant les différentes touches du clavier
	// table representing the different keys of the keyboard
	bool		touche[256];

	//contient l'hwnd de la fenêtre
	HWND		hWnd;

	//contient l'hdc
	HDC			DC;
	HGLRC		RC;

	HINSTANCE	hInstance;

	//spécifie si on est en mode Fullscreen ou en mode fenêtre (par défaut -> fenêtre)
	bool		fullscreen=TRUE;

	//spécifie si le programme est actif (la boucle d'affichage se termine quand b_actif est à false)
	// specify if the program is active (the display loop ends when b_active is false)
	bool		b_actif=FALSE;

	//permet de calculer le nombre de millisecondes écoulées entre chaque rendu de scène
	// calculate the number of milliseconds elapsed between each scene rendering
	char images_sec[256];
	ULONGLONG temps_1;
	ULONGLONG temps_2;
	ULONGLONG temps_x;

	//permet de calculer le nombre d'images affichées par seconde 
	// calculate the number of images displayed per second
	ULONGLONG fps_1;
	ULONGLONG fps_2;
	ULONGLONG fps_img_1;
	ULONGLONG fps_img_2;




//##### INSTANCES DE CLASSES

	//classe ligne3d (on les initialisera plus tard)
	Ligne3D1 * ligne_1[NBR_LIGNES_MAX_DEF];

	//classe "camera"
	//camera* camera_1 = new camera(0, 0, 0, 0, 0, 0, 175, &s_infos_gen);
	camera * camera_1 = new camera( 0 , 0 , 0 , 0 , 0 , 0 , 72 , &s_infos_gen );
	//double(rand() % 10) - 5)


//##### CHARGEMENT DES BMP
	//ce bout de code a été repris d'une source : http://www.cppfrance.com/code.aspx?ID=11002

	
		// ##### LOADING BMP
		// this piece of code has been taken from a source: http://www.cppfrance.com/code.aspx?ID=11002

	struct PropPicture {

		unsigned char   Header[0x36];
		GLuint          DataPos,DataSize;
		GLint           Components;
		GLsizei         Width,Height;
		GLenum          Format,Type;
		GLuint          Name[1];
		unsigned char   *Data;

	};

	#define EXIT {fclose(fichier);return -1;}
	#define CTOI(C) (*(int*)&C)



#endif
