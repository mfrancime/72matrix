﻿/***************************************************
mfrancime@gmail.com
****************************************************
**                                                **
**                                                **
**              MATRIX FALL main.cpp              **
**                  Version 9.0                   **
**                  Thomas John                   **
**           thomas.john@open-design.be           **
**                                                **
**                                                **
****************************************************
***************************************************/

// réalisé avec l'aide des tutoriaux de Jeff Molofee disponibles à l'adresse suivante :
// nehe.gamedev.net

// ainsi que sur d'autres basés sur ces premiers que vous pouvez consulter à cette adresse :
// glinfrench.apinc.org

// made with the help of Jeff Molofee tutorials available at the following address:
// nehe.gamedev.net

// as well as others based on these first ones that you can consult at this address:
// glinfrench.apinc.org

#include "main.h"


//****************************************************************************************
//              **************************************************************************
//  procédures
//              **************************************************************************
//****************************************************************************************

//permet de s'amuser avec les options de blending

// have fun with the blending options
GLenum blend_sz(int varsz)
{

	switch(varsz)
	{

		case 1:
			return GL_ZERO;
			break;

		case 2:
			return GL_ONE;
			break;

		case 3:
			return GL_SRC_COLOR;
			break;

		case 4:
			return GL_ONE_MINUS_SRC_COLOR;
			break;

		case 5:
			return GL_DST_COLOR;
			break;

		case 6:
			return GL_ONE_MINUS_DST_COLOR;
			break;

		case 7:
			return GL_SRC_ALPHA;
			break;

		case 8:
			return GL_ONE_MINUS_SRC_ALPHA;
			break;

		case 9:
			return GL_DST_ALPHA;
			break;

		case 10:
			return GL_ONE_MINUS_DST_ALPHA;
			break;

		case 11:
			return GL_SRC_ALPHA_SATURATE;
			break;

		default:
			return GL_ZERO;

	}

}

// dessine la scène
// draw the scene
int RePaint()
{	
	// on initialise notre premier compteur qui va nous permettre de connaître le temps écoulé entre chaque scène
	// we initialize our first counter which will allow us to know the time elapsed between each scene
	temps_1 = GetTickCount64();

	// ceci est la différence entre le moment où la dernière scène a été rendue et "maintenant"
	// this is the difference between when the last scene was rendered and "now"
	s_infos_gen.msec = temps_1 - temps_2;
	

	// on efface notre écran	
	// we clear our screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	// on remet à zéro les entités
	// we reset the entities
	glLoadIdentity();


	// on calcule le nombre d'images par seconde affichées
	// calculate the number of frames per second displayed
	if(GetTickCount64() - fps_2 >= 1000)
	{
		fps_2 = GetTickCount64();

		fps_img_2 = fps_img_1;

		fps_img_1 = 0;
	}

	// on augmente le nombre d'images qui ont été affichées
	// increase the number of images that have been displayed
	fps_img_1++;
	

	// on affiche les infos dans la barre des titres
	// show the info in the title bar
	//sprintf(images_sec, "%s - fps = %d - dist = %f - msec = %i", NOM_APP_FENETRE, fps_img_2 , s_infos_gen.dist_ttmp , s_infos_gen.msec);
	//SetWindowText(hWnd, images_sec);
		
		
	//camera* camera_1 = new camera(0, 0, 0, 0, 0, 0, 72, &s_infos_gen);
	// on calcule la position de la caméra
	// calculate the position of the camera
	camera_1->calculer();
		
	// ces variables vont servir à ordonner toutes les lignes du tableau contenant leurs index et coordonnées z
	// these variables will be used to order all rows in the table containing their indexes and z coordinates
	int i=0,i2=0;
	double ordre_cour;

	// on calcule chaque ligne
	// calculate each line
	for (i=0 ; i<NBR_LIGNES_MAX ; i++)
	{

		ligne_1[i]->calculer();

	}
			
	// on trie la liste selon leur coordonnée z (méthode dite "bubble sort")
	// we sort the list according to their z coordinates (so-called "bubble sort" method)
	for (int i4 = 0; i4 < NBR_LIGNES_MAX-1; i4++)
	{
		for (int j4 = i4+1; j4 < NBR_LIGNES_MAX; j4++)
		{
			if (s_infos_gen.ordre_sz[i4].ordre > s_infos_gen.ordre_sz[j4].ordre)
			{

				// on interverti les données
				// we invert the data
				ordre_cour = s_infos_gen.ordre_sz[i4].ordre;
				i2 = s_infos_gen.ordre_sz[i4].index,
				s_infos_gen.ordre_sz[i4].ordre = s_infos_gen.ordre_sz[j4].ordre;
				s_infos_gen.ordre_sz[i4].index = s_infos_gen.ordre_sz[j4].index;
				s_infos_gen.ordre_sz[j4].ordre = ordre_cour;
				s_infos_gen.ordre_sz[j4].index = i2;

			}
		}
	}

	// et on les affiche en fonction de la position de la caméra et de sa direction
	// and show them according to the position of the camera and its direction
	if((s_infos_gen.infos_cam_sz.m_z_v - s_infos_gen.infos_cam_sz.m_z_t) < 0)
	{

		for (i=NBR_LIGNES_MAX-1 ; i>=0 ; i--)
		{
			//i2 = s_infos_gen.ordre_sz[i].index;
			//ordre_cour = s_infos_gen.ordre_sz[i].ordre;
			ligne_1[s_infos_gen.ordre_sz[i].index]->display();

		}

	}else{

			
		for (i=0 ; i<NBR_LIGNES_MAX ; i++)
		{
			//i2 = s_infos_gen.ordre_sz[i].index;
			//ordre_cour = s_infos_gen.ordre_sz[i].ordre;
			ligne_1[s_infos_gen.ordre_sz[i].index]->display();

		}

	}
		


	// on vérifie si la touche escape a été enfoncée
	// check if the escape key has been pressed
	if( touche[27] == TRUE )
	{

		// on stoppe la boucle
		// stop the loop
		b_actif=FALSE;

	}



	// permet de s'amuser avec les options de blending
	// pour ce faire, il faut dé-commenter une ligne à la fin du fichier "Ligne3D1.cpp" (c'est expliqué)

	// have fun with the blending options
	// to do this, you must uncomment a line at the end of the file "Ligne3D1.cpp" (it's explained)
	for(i=48 ; i<58 ; i++)
	{

		if( touche[i] == TRUE)
			s_infos_gen.prem = blend_sz(i-47);

	}

	for(i=96 ; i<106 ; i++)
	{

		if( touche[i] == TRUE)
			s_infos_gen.deux = blend_sz(i-95);

	}


	// on interverti nos buffers
	// il faut savoir qu'avant d'être affichés à l'écran, tous les éléments d'une scène sont dessinés un à un dans un buffer
	// ensuite l'adresse de ce buffer est interverti avec celle du buffer qui est visible à l'écran
	// cela permet d'éviter quelques effets visuels dérangeant (il serait alors possible de voir à quel moment chaque élément
	// est affiché)


	// we invert our buffers
	// you must know that before being displayed on the screen, all the elements of a scene are drawn one by one in a buffer
	// then the address of this buffer is inverted with the address of the buffer which is visible on the screen
	// this avoids some disturbing visual effects (it would then be possible to see when each element
	// is posted)
	SwapBuffers(DC);

	//on réinitialise notre compteur (temps entre deux affichages)
	// we reset our counter (time between two displays)
	temps_2 = temps_1;

	return TRUE;
}


// comme son nom l'indique, elle permet de fermer correctement le programme en vidant de la mémoire les différents
// éléments qu'il a fallu créer

// as its name suggests, it allows you to close the program correctly by emptying the memory
// elements that had to be created
void Shutdown()
{
	if (fullscreen)
	{
		ChangeDisplaySettings(NULL,0);
		ShowCursor(TRUE);
	}

	wglMakeCurrent(NULL,NULL);
	
	wglDeleteContext(RC);
	RC=NULL;

	ReleaseDC(hWnd,DC);
	DC=NULL;
	
	DestroyWindow(hWnd);
	hWnd=NULL;

	UnregisterClass(NOM_APP, hInstance);
	hInstance=NULL;
}


// charge une texture de type PNG dans la variable indiquée dans le paramètre "texturesz"
// utilise une partie du code de la lib "glpng" (--> glpng.c)

// load a PNG texture into the variable specified in the "texturesz" parameter
// use some of the code of the lib "glpng" (-> glpng.c)
int LoadTexture( unsigned &texture_sz , char * fichier_sz)
{
	
	pngInfo info;

	glGenTextures(1, &texture_sz);
	glBindTexture(GL_TEXTURE_2D, texture_sz);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (pngLoad(fichier_sz, PNG_BUILDMIPMAPS, PNG_ALPHA, &info)) {
	   
		return TRUE;

	}else{

		return FALSE;

	}

}


// charge une texture de type BMP dans la variable indiquée dans le paramètre "texturesz"
// load a texture of type BMP in the variable indicated in the "texturesz" parameter
int LoadTextureBMP( unsigned &texture_sz , char * fichier_sz)
{
	
	// partie du code provient de : http://www.cppfrance.com/code.aspx?ID=11002
	// part of the code comes from: http://www.cppfrance.com/code.aspx?ID=11002

	FILE * fichier;
	PropPicture pStruct;

	// on ouvre le fichier
	// open the file
    fichier = fopen( fichier_sz,"rb" );

	// on vérifie qu'il est bien ouvert
	// check that it is open
	if ( !fichier )
		return FALSE;

	// and the information in the header is correct
	// et que les informations contenues dans l'entête sont correctes
    if ( fread(pStruct.Header,1,0x36,fichier)!=0x36 )
		return FALSE;

    if ( pStruct.Header[0]!='B' || pStruct.Header[1]!='M' )
		return FALSE;

    if ( CTOI(pStruct.Header[0x1E])!=0 )
		return FALSE;

    if ( CTOI(pStruct.Header[0x1C])!=24 )
		return FALSE;

	// Récupère les infos du fichier
	// Get the info from the file
    pStruct.DataPos = CTOI( pStruct.Header[0x0A] );
    pStruct.DataSize = CTOI( pStruct.Header[0x22] );

	// Récupère les infos de l'image
	// Get image info
    pStruct.Width = CTOI( pStruct.Header[0x12] );
    pStruct.Height = CTOI( pStruct.Header[0x16] );
    pStruct.Type = GL_UNSIGNED_BYTE;
    pStruct.Format = GL_RGB;
    pStruct.Components = 3;
    
    // !!!!
    if( pStruct.DataSize==0 )
		pStruct.DataSize = pStruct.Width * pStruct.Height * pStruct.Components;

    if( pStruct.DataPos==0 )
		pStruct.DataPos = 0x36;

	// charge l'image
    fseek(fichier,pStruct.DataPos,0);

    pStruct.Data = new unsigned char[pStruct.DataSize];

    if (!pStruct.Data)
		return FALSE;

    if (fread(pStruct.Data,1,pStruct.DataSize,fichier)!=pStruct.DataSize)
    {
        delete pStruct.Data;
        fclose(fichier);
        return FALSE;
    }
    
    fclose(fichier);

	// inverse R et B
	// dans un fichier bmp, les couleurs sont enregistrée dans cet ordre : bgr
	// pour qu'opengl puisse les lire correctement, il faut les remettre dans cet ordre : rgb

	// inverse R and B
	// in a bmp file, the colors are saved in this order: bgr
	// so that opengl can read them correctly, you have to put them in this order: rgb
    unsigned char t;
    for (int x=0; x<(pStruct.Width * pStruct.Height) ; x++)
    {
        t = pStruct.Data[x*3];
        pStruct.Data[x*3] = pStruct.Data[x*3+2];
        pStruct.Data[x*3+2] = t;
    }

	// on génère une texture opengl
	// generate an opengl texture
    glGenTextures (1, &texture_sz);

	glBindTexture(GL_TEXTURE_2D, texture_sz);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, pStruct.Components, pStruct.Width, pStruct.Height, 0,
	pStruct.Format, pStruct.Type, pStruct.Data);

	// on retourne TRUE si tout s'est bien passé
	// return TRUE if everything went well
	return TRUE;

}

// intialisation des textures
int InitTextures()
{

	float i=0.0 , i2=1.0 , i3=0.0;
	
	// on charge les textures

	if(!LoadTexture( s_infos_gen.tex_lettres_vertes , "alpha_skyblue_fonts.png" ))
		return FALSE;

	if(!LoadTexture( s_infos_gen.tex_lettres_blanches , "alpha_sky_white_fonts.png" ))
	//if(!LoadTexture( s_infos_gen.tex_lettres_blanches , "HEBREW.png" ))
		return FALSE;


	if(!LoadTextureBMP( s_infos_gen.tex_part_1 , "skycloud.bmp" ))
		return FALSE;

	// on crée une liste d'affichage pour chaque case (0 -> 55)
	// l'idée de la liste d'affichage a été abandonnée pour plusieurs raisons
	// néanmoins, je laisse le code pour ceux que ça intéresse
	// une liste d'affichage permet de pré-compiler une série d'instruction pour ensuite
	// les appeler d'une simple fonction (gain de temps et de vitesse)
	// mais ces listes ne permettent plus un contrôle absolu sur les éléments qu'elle affiche

	// à la place, cette boucle va se charger de générer les coordonnées de texture qui vont servir à display
	// les différents caractères des lettres


	// create a display list for each box (0 -> 55)
	// the idea of ​​the display list was abandoned for several reasons
	// nevertheless, I leave the code for those interested
	// a display list allows you to pre-compile a series of instructions for
	// call them with a simple function (saving time and speed)
	// but these lists no longer allow absolute control over the elements it displays

	// instead, this loop will be responsible for generating the texture coordinates that will be used to display
	// the different characters of the letters

	for(int i=0 ; i<72 ; i++)
	{
		
		s_infos_gen.lst_lettres_vertes[i] = glGenLists(1);

		// on commence notre nouvelle liste
		// we start our new list
		glNewList(s_infos_gen.lst_lettres_vertes[i],GL_COMPILE);
				
			// on spécifie la texture
			// we specify the texture
			glBindTexture(GL_TEXTURE_2D, s_infos_gen.tex_lettres_vertes);
				
			// les coordonnées de cette texture ainsi que le polygone sur lequel elle sera placée
			// the coordinates of this texture as well as the polygon on which it will be placed
			glBegin(GL_QUADS);
					
				glTexCoord2f(double(0.0976 * i3), double(0.113 * i2));
				glVertex3d( 0.0, 0.0, 0.0);

				glTexCoord2f(double(0.0976 * i3), double(0.113 * (i2-1)));
				glVertex3d( 0.0, 1.0, 0.0);

				glTexCoord2f(double(0.0976 * (i3+1)), double(0.113 * (i2-1)));
				glVertex3d( 1.0, 1.0, 0.0);

				glTexCoord2f(double(0.0976 * (i3+1)), double(0.113 * i2));
				glVertex3d( 1.0, 0.0, 0.0);

			glEnd();
			
		// la liste ce termine ici

// the list ends here
		glEndList();
		

		// on enregister les coordonnées
		// we register the coordinates
		s_infos_gen.info_tex_vertes_sz[i].x1 = float(0.0976 * i3);
		s_infos_gen.info_tex_vertes_sz[i].y1 = float(0.113 * i2);

		s_infos_gen.info_tex_vertes_sz[i].x2 = float(0.0976 * i3);
		s_infos_gen.info_tex_vertes_sz[i].y2 = float(0.113 * (i2-1.0));

		s_infos_gen.info_tex_vertes_sz[i].x3 = float(0.0976 * (i3+1.0));
		s_infos_gen.info_tex_vertes_sz[i].y3 = float(0.113 * (i2-1.0));

		s_infos_gen.info_tex_vertes_sz[i].x4 = float(0.0976 * (i3+1.0));
		s_infos_gen.info_tex_vertes_sz[i].y4 = float(0.113 * i2);

		// on incrémente i3 (spécifie la colonne dans laquelle on se trouve)
		// we increment i3 (specifies the column in which we are)
		i3++;

		// on vérifie que i3 ne dépasse pas 3
		// we check that i3 does not exceed 3
		if( i3 > 9 )
		{
			// on remet i3 à zéro (colonne)
			// reset i3 (column)
			i3 = 0;

			// on passe à la ligne suivante
			// go to the next line
			i2++;

		}

	}

	return TRUE;

}

// on initialise le programme (chargement des textures, on détermine certains paramètres,...)
// we initialize the program (loading textures, we determine certain parameters, ...)
int InitGL()
{

	// on spécifie le type de texture qu'on utilise
	// we specify the type of texture we use
	glEnable(GL_TEXTURE_2D);
	
	// on initialise les textures
	if (!InitTextures())
		return FALSE;

	// la couleur par laquelle la scène sera effacée avant chaque rendu
	// (peut être perçu comme le fond)
	// ici, noir


	// the color by which the scene will be erased before each rendering
	// (can be perceived as the background)
	// here, black

	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glColor4f(0.0f, 1.0f, 1.0f, 1.0f);//light blue
	// on active le "blending"
	glEnable(GL_BLEND);

	// et on spécifie son mode
	// and we specify its mode
	glBlendFunc(GL_SRC_ALPHA,GL_DST_ALPHA);

	//glDisable(GL_DEPTH_TEST);
	//glClearDepth(1.0);
	//glDepthFunc(GL_LESS);
	//glEnable(GL_DEPTH_TEST);

	glShadeModel(GL_SMOOTH);

	// calcul de la perspective (la meilleure)
	// calculating the perspective (the best)
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// si on arrive jusqu'ici, on retourne TRUE (tout s'est bien passé)
	// if we get here, we return TRUE (everything went well)

	return TRUE;
}


// ReSize : permet de redimensionner la taille de l'affichage
// ReSize: Resize the size of the display
void ReSize(int width, int height)
{
	glViewport(0,0,width,height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective (45,(double)width/(double)height,1,100000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


// Cette fonction est appelée par Windows (c'est via celle-ci que tous les messages sont envoyés à l'application)
// This function is called by Windows (it is via this that all messages are sent to the application)
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam,LPARAM	lParam)
{
	switch (uMsg)
	{
		case WM_SYSCOMMAND:
		{
			switch (wParam)
			{
				case SC_SCREENSAVE:
				case SC_MONITORPOWER:
				return 0;
			}
			break;
		}

		case WM_CLOSE:
		{
			b_actif=FALSE;
			return 0;
		}

		case WM_KEYDOWN:
		{
			touche[wParam] = TRUE;
			return 0;
		}

		case WM_KEYUP:
		{
			touche[wParam] = FALSE;
			return 0;
		}

		case WM_SIZE:
		{
			ReSize(LOWORD(lParam),HIWORD(lParam));
			return 0;
		}
	}

	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}


// CreateGLWindow : crée la fenêtre sur laquelle on va pouvoir dessiner
// CreateGLWindow: creates the window on which we will be able to draw
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	WNDCLASS	wc;
	DWORD		dwExStyle;
	DWORD		dwStyle;
	RECT		WindowRect;
	WindowRect.left=(long)0;
	WindowRect.right=(long)width;
	WindowRect.top=(long)0;
	WindowRect.bottom=(long)height;
	fullscreen=fullscreenflag;

	hInstance			= GetModuleHandle(NULL);
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc		= (WNDPROC) WndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= hInstance;
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= NULL;
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= NOM_APP;

	RegisterClass(&wc);
	
	if (fullscreen)
	{
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth	= width;
		dmScreenSettings.dmPelsHeight	= height;
		dmScreenSettings.dmBitsPerPel	= bits;
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN);
	}

	if (fullscreen)
	{
		dwExStyle=WS_EX_APPWINDOW;
		dwStyle=WS_POPUP;
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle=WS_OVERLAPPEDWINDOW;
	}

	ShowCursor(TRUE);

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);

	hWnd=CreateWindowEx(dwExStyle, NOM_APP, title,	dwStyle | WS_CLIPSIBLINGS |	WS_CLIPCHILDREN,
						0, 0, WindowRect.right-WindowRect.left,	WindowRect.bottom-WindowRect.top,
						NULL, NULL,	hInstance, NULL);

	static PIXELFORMATDESCRIPTOR pfd=
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		bits,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
	
	DC=GetDC(hWnd);
	
	SetPixelFormat(DC,ChoosePixelFormat(DC,&pfd),&pfd);

	RC=wglCreateContext(DC);

	wglMakeCurrent(DC,RC);

	ShowWindow(hWnd,SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);
	
	return TRUE;
}


// WinMain : c'est la fonction appelée lors du lancement du programme
// WinMain: this is the function called when launching the program
int WINAPI WinMain(HINSTANCE hInstance,	HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// contient les messages provenant de Windows
	MSG	msg;

	// on crée la fenêtre
	// create the window
	if(!CreateGLWindow(NOM_APP_FENETRE,1024,768,32,fullscreen))
	{
		// il y a eu un problème lors de la création de la fenêtre
		// there was a problem creating the window
		MessageBox (HWND_DESKTOP, "Impossible de créer la fenêtre principale", "Erreur", MB_OK | MB_ICONEXCLAMATION);

		// on quitte le programme
		return -1;

	}
	
	// la fenêtre est créée, on continue

	// on initialise le programme
	if(!InitGL())
	{
		// il y a eu un problème lors de l'initialisation
		MessageBox (HWND_DESKTOP, "Impossible d'initialiser le programme", "Erreur", MB_OK | MB_ICONEXCLAMATION);

		// on quitte le programme
		return -1;

	}

	// on crée notre tableau qui va contenir l'index et la coo z de chaque ligne
	// we create our table which will contain the index and the coo z of each line
	s_infos_gen.ordre_sz = new ordre_z[NBR_LIGNES_MAX];


	// on charge les lignes
	// load the lines
	for (int i=0 ; i<NBR_LIGNES_MAX ; i++)
	{

		ligne_1[i] = new Ligne3D1( double((rand()%200)-100) , double((rand()%200)-100) , double((rand()%200)-100) , &s_infos_gen , i);

	}


	// on redimensionne l'affichage (en fait ici on l'initialise, cette fonction va permettre de redimensionner
	// l'affichage pendant que le programme tourne)

	// we resize the display (in fact here we initialize it, this function will allow to resize
	// the display while the program is running)
	ReSize(1024, 768);

	// tout s'est bien passé, on active la boucle
	// everything went well, we activate the loop
	b_actif = TRUE;

	// on commence la boucle
	while(b_actif)
	{

		// on intercepte les messages envoyés au programme
		// intercept the messages sent to the program
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			// on vérifie si ce n'est pas une demande de fermeture
			// check if it's not a closing request
			if (msg.message==WM_QUIT)
			{
				// oui, on stoppe la boucle
				b_actif=FALSE;
			}
			else
			{
				// non, on passe le message
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			//camera* camera_1 = new camera(0, 0, 0, 0, 0, 0, 72, &s_infos_gen);
			// on dessine la scène
			RePaint();

		}
	}

	// on décharge tout ce qu'il faut décharger
	Shutdown();

	// on quitte le programme
	return (msg.wParam);
}