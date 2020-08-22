/***************************************************
****************************************************
**                                                **
**                                                **
**               classe "Ligne3D1"                **
**                                                **
**                  Thomas John                   **
**           thomas.john@open-design.be           **
**                                                **
**                                                **
****************************************************
***************************************************/

// on inclut les ent�tes
#include <windows.h>
#include <gl\gl.h>
//#include <gl\glu.h>
#include <math.h>

#include <stdio.h>

// on inclut le fichier header de cette classe
#include "Ligne3D1.h" //on met les guillemets car ce fichier se trouve dans le m�me dossier

// initialisation d'une lettre
// initialization of a letter
void Ligne3D1::init_lettre( int index_sz )
{

	// on initialise toutes les variables de cette lettre
	// il est important d'initialiser toutes les variable d'une structure ou d'une classe lorsqu'elle est cr��e
	// avant de les utiliser

	// les coordonn�es


	// we initialize all the variables of this letter
	// it is important to initialize all the variables of a structure or a class when it is created
	// before using them

	// the coordinates

	lettre_1[index_sz].pos_x = m_x;
	// chaque lettre se trouve plus bas de 0.7
	// each letter is lower than 0.7
	lettre_1[index_sz].pos_y = m_y - (0.7 * m_nbr_actif); 

	lettre_1[index_sz].pos_z = m_z;
	
	// �tat de la lettre 1 = d�but
	// state of the letter 1 = start
	lettre_1[index_sz].etat = 1;

	// timer 1
	lettre_1[index_sz].temps = 0;
	lettre_1[index_sz].temps_tot = m_temps_tot;

	// le caract�re que cette lettre va display (parmi 56)
	// the character that this letter will display (among 56)
	lettre_1[index_sz].caractere = rand()%71;

	// l'opacit� de cette lettre
	// the opacity of this letter
	//lettre_1[index_sz].opacite = 100;
	lettre_1[index_sz].opacite = 100;
	// la distance qui la s�pare de l'oeuil de la cam�ra
	// the distance that separates it from the eye of the camera
	lettre_1[index_sz].dist_tmp = 0;

	// sp�cifie si le caract�re de la lettre peut changer dans le temps
	// specify if the character of the letter can change in time
	lettre_1[index_sz].change_sz = rand() % 3;

	// timer 2 (changement de caract�re)
	// timer 2 (change of character)
	lettre_1[index_sz].temps_2 = 0;
	lettre_1[index_sz].temps_tot_2 = 72 + (rand() % 500);

}

// constructeur par d�faut
Ligne3D1::Ligne3D1( double x, double y, double z , struct infos_gen * infos_sz , int index)
{
	// on initialise toutes les variables globales

	// pointeur vers structure contenant les infos g�n�rales

	// initialize all global variables

	// pointer to structure containing general info
	infos_gen_tmp = infos_sz;



	// les coordonn�es
	// the coordinates
	//m_y = double((rand()%100)-50) + infos_gen_tmp->infos_cam_sz.m_y_v;
	//m_z = double((rand()%100)) + infos_gen_tmp->infos_cam_sz.m_z_v;
	
	m_y = double((rand() % 50) - 25) + infos_gen_tmp->infos_cam_sz.m_y_v;
	m_z = double((rand() % 50)) + infos_gen_tmp->infos_cam_sz.m_z_v;

	// au plus la ligne est �loign�e de la cam�ra, au sa marge sur la coordonn�e x sera grande
	// at most the line is away from the camera, at its margin on the x coordinate will be large
	//m_x = double((rand()%100)-50) + infos_gen_tmp->infos_cam_sz.m_x_v;

	m_x = double((rand() % 50) - 30) + infos_gen_tmp->infos_cam_sz.m_x_v;

/*
	// sert pour les tests
	// serves for testing
	m_x = infos_gen_tmp->infos_cam_sz.m_x_t;
	m_y = infos_gen_tmp->infos_cam_sz.m_y_t;
	m_z = infos_gen_tmp->infos_cam_sz.m_z_t;
*/
	// l'�tat de la classe (1 = active)
	// the state of the class (1 = active)
	m_etat = 1;

	// le nombre max de lettres � display
	// the max number of letters to display
	//nbr_max_lettres = 20 + int(rand()%100);
	nbr_max_lettres = 72 + int(rand() % 270);

	// sert pour le d�compte
	// serves for counting
	decpt_nbr_lettres = nbr_max_lettres;

	// on cr�e notre tableau qui va contenir les infos concernant chaque lettre
	// we create our table which will contain information about each letter
	lettre_1 = new Lettre3D1[nbr_max_lettres+1];

	// le nombre de lettres actives
	// the number of active letters
	m_nbr_actif = 0;

	// timer 1
	m_temps = 0;
	m_temps_tot = 1 + (rand()%300);

	// index de cette instance de classe
	// index of this class instance
	index_tmp = index;

	// dur�e du fondu blanc->vert
	// duration of the white fade-> green
	m_temps_fondu = m_temps_tot;

	// aucune instance de la classe "effet_particle" n'a encore �t� charg�e
	// no instance of class "particle_effect" has been loaded yet
	m_charge_part = FALSE;

	// si la vitesse d'affichage des lettres est rapide (<30) et si on affiche plus de 60 lettres, on affiche les particles
	// if the letter display speed is fast (<30) and if more than 60 letters are displayed, the particles are displayed
	if(m_temps_tot<30 && nbr_max_lettres>60)
	{
		// on met la variable � TRUE
		m_effet_particle = TRUE;

		// on cr�e la classe
		// create the class
		particles_1 = new effet_particle( 0 , 0 , 0 , 1 , 200 , infos_sz , 1 , 1);
		particles_1->m_x = m_x;
		particles_1->m_y = m_y;
		particles_1->m_z = m_z;

		// une instance de cette classe a �t� charg�e
		// an instance of this class has been loaded
		m_charge_part = TRUE;

	}else{

		// sinon on met la variable � FALSE
		// else we put the variable at FALSE
		m_effet_particle = FALSE;

	}

	// distance ligne-cam�ra
	// distance line-camera
	dist_tmp = 0;

}

// destructeur
Ligne3D1::~Ligne3D1( )
{

	// on d�charge l'instance de de la classe "effet_particle" si elle a �t� charg�e
	// unload the instance of the class "particle_effect" if it has been loaded
	if(m_charge_part == TRUE)
		delete particles_1;

}

// on calcule la position et l'�tat de chaque �l�ment de cette ligne
// we calculate the position and the state of each element of this line
void Ligne3D1::calculer()
{
	
	// % calcul� en fonction des donn�es du timer de chaque lettre (temps et temps_tot)
	//% calculated according to the data of the timer of each letter (time and time_tot)
	double prct_sz;
	//char oki[256] = "";

	// on v�rifie s'il faut cr�er une nouvelle lettre
	// we check whether to create a new letter
	if(m_nbr_actif < nbr_max_lettres)
	{

		// on incr�mente notre timer
		m_temps += infos_gen_tmp->msec;

		// on v�rifie si notre timer n'est pas arriv� au bout
		// check if our timer has not reached the end
		if (m_temps >= m_temps_tot)
		{
			
			// on cr�e une nouvelle lettre
			// create a new letter
			m_nbr_actif++;

			// on initialise la nouvelle lettre
			// we initialize the new letter
			init_lettre(m_nbr_actif);

			// on r�-initialise notre timer
			// we reset our timer
			m_temps = 0;

		}

	}


	// ces variables vont nous permettre de calculer la distance qui s�pare chaque lettre de l'oeuil de la cam�ra
	// these variables will allow us to calculate the distance between each letter of the eye of the camera
	double dist_x;
	double dist_y;
	double dist_z;


	

	//// ce bout de code permet de calculer la distance qui s�pare la ligne de l'oeuil de la cam�ra
	//// d�sormais, cette distance est calcul�e pour chaque lettre
	//// je laisse toujours le code pour ceux qui n'ont pas besoin de le calculer pour chaque lettre et
	//// ainsi gagner quelques fps

	//// on modifie l'opacit� de la ligne en fonction de la distance qui la s�pare de la cam�ra


	//// this piece of code can calculate the distance between the line of the eye of the camera
	//// now, this distance is calculated for each letter
	//// I always leave the code for those who do not need to calculate it for each letter and
	//// so win some fps

	//// we modify the opacity of the line according to the distance that separates it from the camera

	//dist_x = infos_gen_tmp->infos_cam_sz.m_x_v - m_x;
	//dist_y = infos_gen_tmp->infos_cam_sz.m_y_v - m_y;
	//dist_z = infos_gen_tmp->infos_cam_sz.m_z_v - m_z;
	//		
	//dist_tmp = sqrt( (dist_x * dist_x) + (dist_y * dist_y) + (dist_z * dist_z));

	//infos_gen_tmp->dist_ttmp = dist_tmp;

	//if(dist_tmp > 200)
	//{

	//	opacite_gen = 0;
	//
	//}else if( dist_tmp < 100 ){

	//	opacite_gen = 1;

	//}else{

	//	opacite_gen = 1 - ((dist_tmp-100) / 100);

	//}
	




	int	i;

	// on calcule l'�tat des lettres
	// we calculate the state of the letters
	for ( i = 1 ; i <= m_nbr_actif ; i++)
	{
		
		// on v�rifie que la lettre est encore active
		// we check that the letter is still active
		if(lettre_1[i].etat > 0)
		{
			
			// on incr�mente le timer
			lettre_1[i].temps += infos_gen_tmp->msec;

			// ok, on fait ce qu'il faut en fonction de l'�tat de la lettre
			// ok, we do the right thing depending on the state of the letter
			switch(lettre_1[i].etat)
			{
				// we show the white letter
				case 1:	// on fait appara�tre la lettre blanche
					
					// on calcule le pourcentage
					prct_sz = (double(lettre_1[i].temps) / double(lettre_1[i].temps_tot));

					// on change l'opacit�
					lettre_1[i].opacite = prct_sz;
					//lettre_1[i].opacite = prct_sz * opacite_gen; // sert uniquement si on ne calcule que la distance ligne-cam�ra
					// only used if only the line-camera distance is calculated
					break;

				// show the white letter
				case 2: // on affiche la lettre blanche
					
					// on change l'opacit� (qui reste � 1 en fait)
					lettre_1[i].opacite = 1.0;
					//lettre_1[i].opacite = opacite_gen; // sert uniquement si on ne calcule que la distance ligne-cam�ra
					// only used if only the line-camera distance is calculated
					break;

				// transition between the white and green letter
				case 3: // transition entre la lettre blanche et verte

					// on calcule le pourcentage
					prct_sz = (double(lettre_1[i].temps) / double(lettre_1[i].temps_tot));
					
					// on change l'opacit�
					lettre_1[i].opacite = prct_sz;
					//lettre_1[i].opacite = prct_sz * opacite_gen; // sert uniquement si on ne calcule que la distance ligne-cam�ra

					break;
				

				// we display the green letter
				case 4:	// on affiche la lettre verte
					
					// on change l'opacit�
					lettre_1[i].opacite = 1.0;
					//lettre_1[i].opacite = opacite_gen; // sert uniquement si on ne calcule que la distance ligne-cam�ra

					break;

				// decrease the opacity of the letter
				case 5: // on diminue l'opacit� de la lettre
					
					// on calcule le pourcentage
					prct_sz = 1.0 - (double(lettre_1[i].temps) / double(lettre_1[i].temps_tot));
		
					// on change l'opacit�
					lettre_1[i].opacite = prct_sz;
					//lettre_1[i].opacite = prct_sz * opacite_gen; // sert uniquement si on ne calcule que la distance ligne-cam�ra

					break;

			}
			
			// on v�rifie si la lettre peut changer
			// we check if the letter can change
			if( lettre_1[i].change_sz == 1 )
			{

				// oui, on incr�mente le timer ad�quat
				// yes, we increment the appropriate timer
				lettre_1[i].temps_2 += infos_gen_tmp->msec;

				// si le timer arrive � la fin, on change le caract�re
				// if the timer comes to the end, we change the character
				if ( lettre_1[i].temps_2 >= lettre_1[i].temps_tot_2 )
				{

					// on re-initialise le timer
					lettre_1[i].temps_2 = 0;

					// et on change de caract�re
					lettre_1[i].caractere = int(rand()%71);

				}

			}

			// on modifie l'opacit� de la lettre en fonction de la distance qui la s�pare de la cam�ra
			// we modify the opacity of the letter according to the distance that separates it from the camera
			dist_x = infos_gen_tmp->infos_cam_sz.m_x_v - m_x;
			dist_y = infos_gen_tmp->infos_cam_sz.m_y_v - m_y;
			dist_z = infos_gen_tmp->infos_cam_sz.m_z_v - m_z;

			// ici, c'est de l'oeuil de la cam�ra
			// here is the eye of the camera
			//dist_x = infos_gen_tmp->infos_cam_sz.m_x_t - m_x;
			//dist_y = infos_gen_tmp->infos_cam_sz.m_y_t - m_y;
			//dist_z = infos_gen_tmp->infos_cam_sz.m_z_t - m_z;
				
			// on calcule la distance
			lettre_1[i].dist_tmp = sqrt( (dist_x * dist_x) + (dist_y * dist_y) + (dist_z * dist_z));

			// serves for line-camera distance
			//dist_tmp = sqrt( (dist_x * dist_x) + (dist_y * dist_y) + (dist_z * dist_z)); // sert pour distance ligne-cam�ra

			// debug
			//infos_gen_tmp->dist_ttmp = dist_tmp;

			// on v�rifie si la lettre n'est pas trop loin
			// check if the letter is not too far
			if(lettre_1[i].dist_tmp > 200)
			{

				// si, alors on ne l'affiche pas
				// check if the letter is not too far
				lettre_1[i].opacite = 0;
			
			}else if( lettre_1[i].dist_tmp > 100 ){

				// non, on peut encore la voir, on calcule sont opacit� en fonction de sa distance (entre 100 et 200)
				// no, we can still see it, we calculate its opacity according to its distance (between 100 and 200)
				lettre_1[i].opacite = (1 - ((lettre_1[i].dist_tmp-100) / 100)) * lettre_1[i].opacite;

			}


		}

	}

	//on r�cup�re la distance lettre-cam�ra de la derni�re lettre
	// get the letter-camera distance from the last letter
	dist_tmp = lettre_1[i-1].dist_tmp;

	// si cette ligne utilise une classe "effet_particle", on la calcule
	// if this line uses a class "particle_effect", we calculate it
	if(m_effet_particle == TRUE)
	{

		// on v�rifie si toutes les lettres de la ligne ont �t� cr��es
		// check if all the letters in the line have been created
		if(m_nbr_actif >= nbr_max_lettres)
		{

			//oui, on stoppe l'�mission de nouvelles particles
			// yes, we stop the emission of new particles
			particles_1->etat = 2;

		}

		// on met � jour la coordonn�e y de la classe d'�mission de particle
		// update the y coordinate of the particle emission class
		particles_1->m_y = m_y - (0.7 * m_nbr_actif);

		// et on effectue les calculs
		// and we do the calculations
		particles_1->calculer();

	}

	// on sp�cifie la coordonn�e z de cette ligne dans notre tableau qui va servir � trier toutes les lignes
	// de sorte � les display de la plus �loign�e � la plus proche

	// we specify the z coordinate of this line in our table which will be used to sort all the lines
	// so to display them from the farthest to the nearest
	infos_gen_tmp->ordre_sz[index_tmp].index = index_tmp;
	infos_gen_tmp->ordre_sz[index_tmp].ordre = m_z;

}

// affichage des �l�ments
// display elements
void Ligne3D1::display()
{

	int i=0 , i2=0 , i3=0;
	//double db_tmp;

	// debug
	char oki[256] = "";

	// on parcoure toutes les lettres
	for ( i = 1 ; i <= m_nbr_actif ; i++)
	{
		
		// ## ! ##
		// on ne v�rifie plus s'il faut display la lettre ou pas ici
		// cela posait probl�me avec l'�tat n�3 de la lettre car m�me si l'opacit� de la lettre verte �tait de z�ro,
		// l'opacit� de la lettre blanche �quivalait � (1 - opacit� lettre verte) donc 1
		// comme cette v�rification n'est effectu�e que sur la lettre principale (en fait la structure contenant les infos sur
		// chaque lettre ne prend pas en compte le fait qu'il puisse y avoir deux lettres), la lettre blanche qui avait comme
		// opacit� 1 n'�tait pas affich�e, causant de ce fait un effet de scintillement
		// ##   ##

		// on v�rifie que la lettre est encore active


		// ##! ##
		// we do not check whether to display the letter or not here
		// that posed a problem with state 3 of the letter because even if the opacity of the green letter was zero,
		// the opacity of the white letter was equivalent to (1 - green letter opacity) so 1
		// as this check is only performed on the main letter (actually the structure containing the info on
		// each letter does not take into account the fact that there may be two letters), the white letter that had
		// opacity 1 was not displayed, thus causing a flicker effect
		// ## ##

		// we check that the letter is still active

		//if(lettre_1[i].etat > 0 && lettre_1[i].opacite > 0)
		//{
			
			// en fonction de l'�tat de la lettre

			// depending on the state of the letter
			switch (lettre_1[i].etat)
			{

				// we do nothing
				case 0: // on ne fait rien
					break;


				// display of the white letter
				case 1: // affichage de la lettre blanche
					
					// on v�rifie s'il faut display cette lettre

					// we check if we have to display this letter
					if(lettre_1[i].opacite > 0)
					{

						// on sp�cifie la texture � utiliser
						// we specify the texture to use
						glBindTexture(GL_TEXTURE_2D, infos_gen_tmp->tex_lettres_blanches);

					}

					// on v�rifie si cette partie n'est pas termin�e

					// check if this part is not finished
					if ( lettre_1[i].temps >= lettre_1[i].temps_tot )
					{

						// on change l'�tat de la lettre
						// change the state of the letter
						lettre_1[i].etat++;

						// on remet le compteur � z�ro
						// reset the counter
						lettre_1[i].temps = 0;

						// on sp�cifie une nouvelle dur�e pour le timer
						// we specify a new duration for the timer
						lettre_1[i].temps_tot = 1;

					}

					break;


				// display of the white letter
				case 2: // affichage de la lettre blanche

					if(lettre_1[i].opacite > 0)
					{

						// on sp�cifie la texture � utiliser
						glBindTexture(GL_TEXTURE_2D, infos_gen_tmp->tex_lettres_blanches);

					}
	
					// on v�rifie si cette partie n'est pas termin�e

					// check if this part is not finished
					if ( lettre_1[i].temps >= lettre_1[i].temps_tot )
					{

						// on change l'�tat de la lettre
						// change the state of the letter
						lettre_1[i].etat++;

						// on remet le compteur � z�ro
						lettre_1[i].temps = 0;

						// on sp�cifie une nouvelle dur�e (celle de la transition blanc->vert)
						// we specify a new duration (that of the transition white-> green)
						lettre_1[i].temps_tot = m_temps_fondu;

						// debug
						//sprintf(oki, "on commence...\n");
						//OutputDebugString(oki);

					}

					break;


				// fade from white to green
				case 3: // fondu du blanc au vert

					// debug
					//sprintf(oki, "opacite = %f ", lettre_1[i].opacite);
					//OutputDebugString(oki);
					
					// on v�rifie si la distance lettre-cam�ra est inf�rieure � 201 (sinon on affiche rien)
					// we check if the letter-camera distance is less than 201 (otherwise we display nothing)
					if(lettre_1[i].dist_tmp < 201)
					{

						// on affiche la lettre blanche

						// on sp�cifie la texture � utiliser (caract�res blancs)

						// show the white letter

						// we specify the texture to use (white characters)
						glBindTexture(GL_TEXTURE_2D, infos_gen_tmp->tex_lettres_blanches);

						// l'opacit� de la lettre blanche est la diff�rence de celle de la verte par rapport � 1
						// donc quand l'opacit� de la lettre verte augmente (pour appara�tre), l'opacit� de la lettre
						// blanche diminue (disparait)
						// on prend aussi en compte la distance lettre-cam�ra

						// the opacity of the white letter is the difference of that of the green compared to 1
						// so when the opacity of the green letter increases (to appear), the opacity of the letter
						// white decreases (disappears)
						// we also take into account the letter-camera distance
						if( lettre_1[i].dist_tmp < 200 && lettre_1[i].dist_tmp > 100 )
						{

							// on csp�cifie l'opacit�
							glColor4d( 1.0 , 1.0 , 1.0 , (1 - ((lettre_1[i].dist_tmp-100) / 100)) - lettre_1[i].opacite);
							/*
							for (int z = 0; z < 72; z++)
							{
								glColor4d(0.5, 0.3 - z / 100.0, 0.5 + z / 150.0, (1 - ((lettre_1[i].dist_tmp - 100) / 100)) - lettre_1[i].opacite);
							}
							*/
							// debug
							//sprintf(oki, " || entre deux : %f \n", (1 - ((lettre_1[i].dist_tmp-100) / 100)) - lettre_1[i].opacite);
							//OutputDebugString(oki);

						}else{

							// on sp�cifie l'opacit�
							glColor4d( 1.0 , 1.0 , 1.0 , (1 - lettre_1[i].opacite));
							/*
							for (int z = 0; z < 72; z++)
							{								
								glColor4d(0.5, 0.3 - z / 100.0, 0.5 + z / 150.0, (1 - lettre_1[i].opacite));
							}
							*/
							// debug
							//sprintf(oki, " || dedans : %f \n", (1 - lettre_1[i].opacite));
							//OutputDebugString(oki);

						}
						
						// debug
						//infos_gen_tmp->dist_ttmp = lettre_1[i].opacite;

						// on dessine la lettre blanche

						// we draw the white letter
						glBegin(GL_QUADS);

							glTexCoord2f( infos_gen_tmp->info_tex_vertes_sz[lettre_1[i].caractere].x1 , infos_gen_tmp->info_tex_vertes_sz[lettre_1[i].caractere].y1 );
							glVertex3d( lettre_1[i].pos_x, lettre_1[i].pos_y , lettre_1[i].pos_z);

							glTexCoord2f( infos_gen_tmp->info_tex_vertes_sz[lettre_1[i].caractere].x2 , infos_gen_tmp->info_tex_vertes_sz[lettre_1[i].caractere].y2 );
							glVertex3d( lettre_1[i].pos_x, lettre_1[i].pos_y + 1.0 , lettre_1[i].pos_z);

							glTexCoord2f( infos_gen_tmp->info_tex_vertes_sz[lettre_1[i].caractere].x3 , infos_gen_tmp->info_tex_vertes_sz[lettre_1[i].caractere].y3 );
							glVertex3d( lettre_1[i].pos_x + 1.0, lettre_1[i].pos_y + 1.0 , lettre_1[i].pos_z);

							glTexCoord2f( infos_gen_tmp->info_tex_vertes_sz[lettre_1[i].caractere].x4 , infos_gen_tmp->info_tex_vertes_sz[lettre_1[i].caractere].y4 );
							glVertex3d( lettre_1[i].pos_x + 1.0, lettre_1[i].pos_y , lettre_1[i].pos_z);

						glEnd();

						// on sp�cifie la texture � utiliser (cette fois, la texture pour les caract�res verts)

						// we specify the texture to use (this time, the texture for green characters)
						glBindTexture(GL_TEXTURE_2D, infos_gen_tmp->tex_lettres_vertes);

					}

					// on v�rifie si cette partie n'est pas termin�e

					// check if this part is not finished
					if ( lettre_1[i].temps >= lettre_1[i].temps_tot )
					{

						// on change l'�tat de la lettre
						lettre_1[i].etat++;

						// on remet le compteur � z�ro
						lettre_1[i].temps = 0;

						// on sp�cifie une nouvelle dur�e

						// we specify a new duration
						lettre_1[i].temps_tot = 500 + (rand() % 2000);

						// debug
						//sprintf(oki, "on termine...\n\n");
						//OutputDebugString(oki);

					}

					break;


				// we display the green letter
				case 4: // on affiche la lettre verte

					if(lettre_1[i].opacite > 0)
					{

						// on sp�cifie la texture � utiliser
						glBindTexture(GL_TEXTURE_2D, infos_gen_tmp->tex_lettres_vertes);

					}

					// on v�rifie si cette partie n'est pas termin�e
					// check if this part is not finished
					if ( lettre_1[i].temps >= lettre_1[i].temps_tot )
					{

						// on change l'�tat de la lettre
						lettre_1[i].etat++;

						// on remet le compteur � z�ro
						lettre_1[i].temps = 0;

					}

					break;


				// decrease the opacity of the green letter
				case 5: // on diminue l'opacit� de la lettre verte

					if(lettre_1[i].opacite > 0)
					{

						// on sp�cifie la texture � utiliser
						glBindTexture(GL_TEXTURE_2D, infos_gen_tmp->tex_lettres_vertes);

					}

					// on v�rifie si cette partie n'est pas termin�e
					// check if this part is not finished
					if ( lettre_1[i].temps >= lettre_1[i].temps_tot )
					{

						// on change l'�tat de la lettre
						lettre_1[i].etat = 0;

						// on remet le compteur � z�ro
						lettre_1[i].temps = 0;

						// une lettre active en moins
						decpt_nbr_lettres--;

						// debug
						//sprintf(oki, "nombre de lettres restantes : %i\n" , decpt_nbr_lettres);
						//OutputDebugString(oki);

						// on v�rifie si toutes les lettres sont d�sactiv�es

						// check if all letters are disabled
						if(decpt_nbr_lettres == 0)
						{

							// on r�initialise la ligne

							// we reset the line
							m_y = double((rand()%150)-50.0) + infos_gen_tmp->infos_cam_sz.m_y_t;
							i3 = (rand()%200)-100;
							m_z = i3 + infos_gen_tmp->infos_cam_sz.m_z_t;
							// on d�finit la position x en fonction de z
							// au plus la ligne est proche de la cam�ra au moins sa position x pourra �tre grande


							// we define the position x according to z
							// at most the line is close to the camera at least its x position will be large

							m_x = double((rand()%100)-50.0) + infos_gen_tmp->infos_cam_sz.m_x_t;
							//if(i3 < 0){ i3 = 0; }
							//m_x = double((rand() % (100 + (i3*10))) - (50 + (i3*5))) + infos_gen_tmp->infos_cam_sz.m_x_t;

/*
							m_x = infos_gen_tmp->infos_cam_sz.m_x_t;
							m_y = infos_gen_tmp->infos_cam_sz.m_y_t;
							m_z = infos_gen_tmp->infos_cam_sz.m_z_t;
*/

							// debug
							//infos_gen_tmp->dist_ttmp = index_tmp;
							sprintf_s(oki, "diff : %i\n" , i3);
							OutputDebugString(oki);

							// l'�tat de la classe (1 = active)
							m_etat = 1;

							// le nombre max de lettres
							//nbr_max_lettres = 50;

							// sert pour le d�compte
							// serves for counting
							decpt_nbr_lettres = nbr_max_lettres;

							// on cr�e notre tableau qui va contenir les infos concernant chaque lettre

							// we create our table which will contain information about each letter
							//lettre_1 = new Lettre3D1[nbr_max_lettres];

							// le nombre de lettres actives
							m_nbr_actif = 0;

							// timer � z�ro
							m_temps = 0;
/*
							if(m_effet_particle == TRUE)
							{

								particles_1->m_x = m_x;
								particles_1->m_y = m_y;
								particles_1->m_z = m_z;
								particles_1->etat = 1;
								particles_1->m_nombre_actifs=0;

							}
*/

							// vitesse � laquelle de nouvelles lettres sont cr��es
							// speed at which new letters are created
							m_temps_tot = 1 + int((rand()%300));

							// si la vitesse d'affichage des lettres est rapide (<30) et si la ligne est suffisamment grande, 
							// on affiche les particles


							// if the letter display speed is fast (<30) and the line is large enough,
							// we display the particles

							if(m_temps_tot<30 && nbr_max_lettres>60)
							{

								// on v�rifie si une instance de la classe "effet_particle" a d�j� �t� charg�e

								// check if an instance of the class "particle_effect" has already been loaded
								if(m_charge_part == FALSE)
								{
									
									// non, on la charge
									particles_1 = new effet_particle( 0 , 0 , 0 , 1 , 200 , infos_gen_tmp , 1 , 1);

									m_charge_part = TRUE;

								}

								// on met la variable � TRUE
								m_effet_particle = TRUE;

								// on initialise l'�metteur de particle

								// we initialize the particle emitter
								particles_1->m_x = m_x;
								particles_1->m_y = m_y;
								particles_1->m_z = m_z;
								particles_1->etat = 1;
								particles_1->m_nombre_actifs=0;

							}else{

								// sinon on met la variable � FALSE
								// otherwise we put the variable at FALSE
								m_effet_particle = FALSE;

							}

						}

					}

					break;

			}
			
			// on v�rifie s'il faut display cette lettre

			// we check if we have to display this letter
			if(lettre_1[i].etat > 0 && lettre_1[i].opacite > 0)
			{

				// l'opacit�
				glColor4d( 1.0 , 1.0 , 1.0 , lettre_1[i].opacite );

				/*
				for (int i = 0; i < 72; i++) 
				{
					glColor4d(0.5, 0.3 - i / 100.0, 0.5 + i / 150.0, lettre_1[i].opacite);
				}
				*/
				// on dessine la lettre
				// we draw the letter
				glBegin(GL_QUADS);
						
					glTexCoord2f( infos_gen_tmp->info_tex_vertes_sz[lettre_1[i].caractere].x1 , infos_gen_tmp->info_tex_vertes_sz[lettre_1[i].caractere].y1 );
					glVertex3d( lettre_1[i].pos_x, lettre_1[i].pos_y , lettre_1[i].pos_z);

					glTexCoord2f( infos_gen_tmp->info_tex_vertes_sz[lettre_1[i].caractere].x2 , infos_gen_tmp->info_tex_vertes_sz[lettre_1[i].caractere].y2 );
					glVertex3d( lettre_1[i].pos_x, lettre_1[i].pos_y + 1.0 , lettre_1[i].pos_z);

					glTexCoord2f( infos_gen_tmp->info_tex_vertes_sz[lettre_1[i].caractere].x3 , infos_gen_tmp->info_tex_vertes_sz[lettre_1[i].caractere].y3 );
					glVertex3d( lettre_1[i].pos_x + 1.0, lettre_1[i].pos_y + 1.0 , lettre_1[i].pos_z);

					glTexCoord2f( infos_gen_tmp->info_tex_vertes_sz[lettre_1[i].caractere].x4 , infos_gen_tmp->info_tex_vertes_sz[lettre_1[i].caractere].y4 );
					glVertex3d( lettre_1[i].pos_x + 1.0, lettre_1[i].pos_y , lettre_1[i].pos_z);

				glEnd();			

			}

		//}

	}

	/*
	// si cette ligne utilise une classe "effet_particle", on l'affiche
	if(m_effet_particle == TRUE && dist_tmp < 201)
	{

		// on change le mode de blending pour l'affichage des particles
		//glBlendFunc(GL_SRC_ALPHA,GL_ONE);
		//glBlendFunc(GL_ONE,GL_ONE);
		glBlendFunc(GL_SRC_COLOR,GL_ONE);

		// sert pour les tests
		// les modes de "blending" peuvent �tre chang� via le pav� num�rique du clavier et les chiffres
		// se trouvant au-dessus des lettres (ceux accessible avec shift enfonc�)
		// tous les modes ne sont pas pr�sents (il en manque 1 de chaque, le 11�me)
		//glBlendFunc(infos_gen_tmp->prem,infos_gen_tmp->deux);

		// on sp�cifie la texture � utiliser
		glBindTexture(GL_TEXTURE_2D, infos_gen_tmp->tex_part_1);

		// on affiche les particles
		particles_1->display();

		// on remet le mode de blending initial
		glBlendFunc(GL_SRC_ALPHA,GL_DST_ALPHA);

	}
	*/

	/*
	// if this line uses a class "particle_effect", it is displayed
	if (m_effet_particle == TRUE && dist_tmp < 201)
	{

		// we change the blending mode for particle display
		// glBlendFunc (GL_SRC_ALPHA, GL_ONE);
		// glBlendFunc (GL_ONE, GL_ONE);
		glBlendFunc(GL_SRC_COLOR, GL_ONE);

		// serves for testing
		// blending modes can be changed via keypad and numbers
		// located above the letters (those accessible with shift pressed)
		// not all modes are present (missing 1 each, the 11th)
		// glBlendFunc (infos_gen_tmp-> prem, infos_gen_tmp-> both);

		// we specify the texture to use
		glBindTexture(GL_TEXTURE_2D, infos_gen_tmp->tex_part_1);

		// we display the particles
		particles_1->display();

		// reset the initial blending mode
		glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);

	}
	*/

	// if this line uses a class "particle_effect", it is displayed
	if (m_effet_particle == TRUE && dist_tmp < 201)
	{

		// we change the blending mode for particle display
		glBlendFunc (GL_SRC_ALPHA, GL_ONE);
		glBlendFunc (GL_ONE, GL_ONE);
		glBlendFunc(GL_SRC_COLOR, GL_ONE);

		// serves for testing
		// blending modes can be changed via keypad and numbers
		// located above the letters (those accessible with shift pressed)
		// not all modes are present (missing 1 each, the 11th)
		glBlendFunc (infos_gen_tmp-> prem, infos_gen_tmp->tex_part_1);

		// we specify the texture to use
		glBindTexture(GL_TEXTURE_2D, infos_gen_tmp->tex_part_1);

		// we display the particles
		particles_1->display();

		// reset the initial blending mode
		glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);

	}

}