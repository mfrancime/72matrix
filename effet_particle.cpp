/***************************************************
mfrancime@gmail.com
****************************************************
**                                                **
**                                                **
**            classe "effet_particle"            **
**                                                **
**                  Thomas John                   **
**           thomas.john@open-design.be           **
**                                                **
**                                                **
****************************************************
***************************************************/

// on inclut les entêtes
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <math.h>
#include "vector3f.h"

// on inclut le fichier header de cette classe
#include "effet_particle.h" //on met les guillemets car ce fichier se trouve dans le même dossier

// initialise une particle
void effet_particle::init_particle(int particlesz)
{
	
	// coordonnées de départ
	// on laisse une marge pour que les particles n'apparaissent pas toutes au même point

	// starting coordinates
	// leave a margin so that the particles do not all appear at the same point
	t_particles[particlesz].x = m_x + 0.5 + (double(rand()%1)-0.5) / 5;
	t_particles[particlesz].y = m_y - 1 - (double(rand()%1)-0.5) / 2;
	t_particles[particlesz].z = m_z + (double(rand()%1)-0.5) / 5;
		
	// direction des particles
	// direction of particles
	t_particles[particlesz].d_x = (double(rand()%50)-25)/5000;
	
	// the particlents go down a little
	t_particles[particlesz].d_y = -(double(rand()%3))/1000; //les particlent descendent un peu
	t_particles[particlesz].d_z = (double(rand()%50)-25)/5000;

	// vitesse à laquelle elles meurent
	// speed at which they die
	t_particles[particlesz].vitesse = 0.01 - ((double(rand()%5))/1000);

	// vie (opacité)
	// life (opacity)
	t_particles[particlesz].vie = 1.0;

	// taille
	// cut
	t_particles[particlesz].taille = 0.7 + (double(rand() % 7)/10);

	//couleurs
	/* SYMPA : ROUGE/ORANGE */
	//colors
	/* SYMPA: RED / ORANGE */

	t_particles[particlesz].r = 0.90;// + ((double(rand() % 10)-5)/50);
	t_particles[particlesz].g = 0.91;// + ((double(rand() % 10)-5)/50);
	t_particles[particlesz].b = 0.98;// + ((double(rand() % 10)-5)/50);
	//#declare CoolCopper = color red 0.85 green 0.53 blue 0.10
	/*
	#declare Brass = color red 0.71 green 0.65 blue 0.26
		#declare Copper = color red 0.72 green 0.45 blue 0.20
		#declare Bronze = color red 0.55 green 0.47 blue 0.14
		#declare Bronze2 = color red 0.65 green 0.49 blue 0.24
		#declare Silver = color red 0.90 green 0.91 blue 0.98
		#declare BrightGold = color red 0.85 green 0.85 blue 0.10
		#declare OldGold = color red 0.81 green 0.71 blue 0.23
	*/
	/*
	https://community.khronos.org/t/color-tables/22518/6
		#declare Red = rgb <1, 0, 0>
		#declare Green = rgb <0, 1, 0>
		#declare Blue = rgb <0, 0, 1>
		#declare Yellow = rgb <1,1,0>
		#declare Cyan = rgb <0, 1, 1>
		#declare Magenta = rgb <1, 0, 1>
		#declare Clear = rgbf 1
		#declare White = rgb 1
		#declare Black = rgb 0

		// These grays are useful for fine-tuning lighting color values
		// and for other areas where subtle variations of grays are needed.
		// PERCENTAGE GRAYS:
		#declare Gray05 = White0.05
		#declare Gray10 = White0.10
		#declare Gray15 = White0.15
		#declare Gray20 = White0.20
		#declare Gray25 = White0.25
		#declare Gray30 = White0.30
		#declare Gray35 = White0.35
		#declare Gray40 = White0.40
		#declare Gray45 = White0.45
		#declare Gray50 = White0.50
		#declare Gray55 = White0.55
		#declare Gray60 = White0.60
		#declare Gray65 = White0.65
		#declare Gray70 = White0.70
		#declare Gray75 = White0.75
		#declare Gray80 = White0.80
		#declare Gray85 = White0.85
		#declare Gray90 = White0.90
		#declare Gray95 = White*0.95

		// OTHER GRAYS
		#declare DimGray = color red 0.329412 green 0.329412 blue 0.329412
		#declare DimGrey = color red 0.329412 green 0.329412 blue 0.329412
		#declare Gray = color red 0.752941 green 0.752941 blue 0.752941
		#declare Grey = color red 0.752941 green 0.752941 blue 0.752941
		#declare LightGray = color red 0.658824 green 0.658824 blue 0.658824
		#declare LightGrey = color red 0.658824 green 0.658824 blue 0.658824
		#declare VLightGray = color red 0.80 green 0.80 blue 0.80
		#declare VLightGrey = color red 0.80 green 0.80 blue 0.80

		#declare Aquamarine = color red 0.439216 green 0.858824 blue 0.576471
		#declare BlueViolet = color red 0.62352 green 0.372549 blue 0.623529
		#declare Brown = color red 0.647059 green 0.164706 blue 0.164706
		#declare CadetBlue = color red 0.372549 green 0.623529 blue 0.623529
		#declare Coral = color red 1.0 green 0.498039 blue 0.0
		#declare CornflowerBlue = color red 0.258824 green 0.258824 blue 0.435294
		#declare DarkGreen = color red 0.184314 green 0.309804 blue 0.184314
		#declare DarkOliveGreen = color red 0.309804 green 0.309804 blue 0.184314
		#declare DarkOrchid = color red 0.6 green 0.196078 blue 0.8
		#declare DarkSlateBlue = color red 0.419608 green 0.137255 blue 0.556863
		#declare DarkSlateGray = color red 0.184314 green 0.309804 blue 0.309804
		#declare DarkSlateGrey = color red 0.184314 green 0.309804 blue 0.309804
		#declare DarkTurquoise = color red 0.439216 green 0.576471 blue 0.858824
		#declare Firebrick = color red 0.556863 green 0.137255 blue 0.137255
		#declare ForestGreen = color red 0.137255 green 0.556863 blue 0.137255
		#declare Gold = color red 0.8 green 0.498039 blue 0.196078
		#declare Goldenrod = color red 0.858824 green 0.858824 blue 0.439216
		#declare GreenYellow = color red 0.576471 green 0.858824 blue 0.439216
		#declare IndianRed = color red 0.309804 green 0.184314 blue 0.184314
		#declare Khaki = color red 0.623529 green 0.623529 blue 0.372549
		#declare LightBlue = color red 0.74902 green 0.847059 blue 0.847059
		#declare LightSteelBlue = color red 0.560784 green 0.560784 blue 0.737255
		#declare LimeGreen = color red 0.196078 green 0.8 blue 0.196078
		#declare Maroon = color red 0.556863 green 0.137255 blue 0.419608
		#declare MediumAquamarine = color red 0.196078 green 0.8 blue 0.6
		#declare MediumBlue = color red 0.196078 green 0.196078 blue 0.8
		#declare MediumForestGreen = color red 0.419608 green 0.556863 blue 0.137255
		#declare MediumGoldenrod = color red 0.917647 green 0.917647 blue 0.678431
		#declare MediumOrchid = color red 0.576471 green 0.439216 blue 0.858824
		#declare MediumSeaGreen = color red 0.258824 green 0.435294 blue 0.258824
		#declare MediumSlateBlue = color red 0.498039 blue 1.0
		#declare MediumSpringGreen = color red 0.498039 green 1.0
		#declare MediumTurquoise = color red 0.439216 green 0.858824 blue 0.858824
		#declare MediumVioletRed = color red 0.858824 green 0.439216 blue 0.576471
		#declare MidnightBlue = color red 0.184314 green 0.184314 blue 0.309804
		#declare Navy = color red 0.137255 green 0.137255 blue 0.556863
		#declare NavyBlue = color red 0.137255 green 0.137255 blue 0.556863
		#declare Orange = color red 1 green 0.5 blue 0.0
		#declare OrangeRed = color red 1.0 green 0.25
		#declare Orchid = color red 0.858824 green 0.439216 blue 0.858824
		#declare PaleGreen = color red 0.560784 green 0.737255 blue 0.560784
		#declare Pink = color red 0.737255 green 0.560784 blue 0.560784
		#declare Plum = color red 0.917647 green 0.678431 blue 0.917647
		#declare Salmon = color red 0.435294 green 0.258824 blue 0.258824
		#declare SeaGreen = color red 0.137255 green 0.556863 blue 0.419608
		#declare Sienna = color red 0.556863 green 0.419608 blue 0.137255
		#declare SkyBlue = color red 0.196078 green 0.6 blue 0.8
		#declare SlateBlue = color green 0.498039 blue 1.0
		#declare SpringGreen = color green 1.0 blue 0.498039
		#declare SteelBlue = color red 0.137255 green 0.419608 blue 0.556863
		#declare Tan = color red 0.858824 green 0.576471 blue 0.439216
		#declare Thistle = color red 0.847059 green 0.74902 blue 0.847059
		#declare Turquoise = color red 0.678431 green 0.917647 blue 0.917647
		#declare Violet = color red 0.309804 green 0.184314 blue 0.309804
		#declare VioletRed = color red 0.8 green 0.196078 blue 0.6
		#declare Wheat = color red 0.847059 green 0.847059 blue 0.74902
		#declare YellowGreen = color red 0.6 green 0.8 blue 0.196078
		#declare SummerSky = color red 0.22 green 0.69 blue 0.87
		#declare RichBlue = color red 0.35 green 0.35 blue 0.67
		#declare Brass = color red 0.71 green 0.65 blue 0.26
		#declare Copper = color red 0.72 green 0.45 blue 0.20
		#declare Bronze = color red 0.55 green 0.47 blue 0.14
		#declare Bronze2 = color red 0.65 green 0.49 blue 0.24
		#declare Silver = color red 0.90 green 0.91 blue 0.98
		#declare BrightGold = color red 0.85 green 0.85 blue 0.10
		#declare OldGold = color red 0.81 green 0.71 blue 0.23
		#declare Feldspar = color red 0.82 green 0.57 blue 0.46
		#declare Quartz = color red 0.85 green 0.85 blue 0.95
		#declare Mica = color Black // needed in textures.inc
		#declare NeonPink = color red 1.00 green 0.43 blue 0.78
		#declare DarkPurple = color red 0.53 green 0.12 blue 0.47
		#declare NeonBlue = color red 0.30 green 0.30 blue 1.00
		#declare CoolCopper = color red 0.85 green 0.53 blue 0.10
		#declare MandarinOrange = color red 0.89 green 0.47 blue 0.20
		#declare LightWood = color red 0.91 green 0.76 blue 0.65
		#declare MediumWood = color red 0.65 green 0.50 blue 0.39
		#declare DarkWood = color red 0.52 green 0.37 blue 0.26
		#declare SpicyPink = color red 1.00 green 0.11 blue 0.68
		#declare SemiSweetChoc = color red 0.42 green 0.26 blue 0.15
		#declare BakersChoc = color red 0.36 green 0.20 blue 0.09
		#declare Flesh = color red 0.96 green 0.80 blue 0.69
		#declare NewTan = color red 0.92 green 0.78 blue 0.62
		#declare NewMidnightBlue = color red 0.00 green 0.00 blue 0.61
		#declare VeryDarkBrown = color red 0.35 green 0.16 blue 0.14
		#declare DarkBrown = color red 0.36 green 0.25 blue 0.20
		#declare DarkTan = color red 0.59 green 0.41 blue 0.31
		#declare GreenCopper = color red 0.32 green 0.49 blue 0.46
		#declare DkGreenCopper = color red 0.29 green 0.46 blue 0.43
		#declare DustyRose = color red 0.52 green 0.39 blue 0.39
		#declare HuntersGreen = color red 0.13 green 0.37 blue 0.31
		#declare Scarlet = color red 0.55 green 0.09 blue 0.09

		#declare Med_Purple = colour red 0.73 green 0.16 blue 0.96
		#declare Light_Purple = colour red 0.87 green 0.58 blue 0.98
		#declare Very_Light_Purple = colour red 0.94 green 0.81 blue 0.99
	*/	
}

// constructeur par défaut
effet_particle::effet_particle( double x, double y, double z, double vitesse, int nombre_tot , struct infos_gen * infos_sz , int vitesse_emission , int nbr_emission )
{

	// on récupère notre pointeur vers la structure contenant toutes les infos utiles
	infos_tex_tmp = infos_sz;

	// on met notre état à 1
	etat = 1; // signifie que la classe est active (0 = morte)

	// on initialise les variables indiquant la position de l'émetteur de particles
	m_x = x;
	m_y = y;
	m_z = z;

	// vitesse à laquelle les particles "vivent" (se dépacent, meurent...)
	// n'est pas encore utilisée, mais on l'initialise quand même
	m_vitesse = vitesse;

	// nombre max de particles à display en même temps
	m_nombre_tot = nombre_tot;

	// nombre de particles actives
	m_nombre_actifs = 0;

	// permet de spécifier une durée entre chaque émition de particle
	m_temps = 0;
	m_temps_tot = vitesse_emission;

	// nombre de particles émises en même temps
	m_nbr_emission = nbr_emission;

	// on crée notre tableau de particles
	t_particles = new particles[nombre_tot];

}

// destructeur
effet_particle::~effet_particle( )
{

	//

}

// on calcule la position de chaque particle et on en crée une nouvelle s'il le faut
// calculate the position of each particle and create a new one if necessary
void effet_particle::calculer()
{

	int i=0;

	// on vérifie s'il faut créer une nouvelle particle
	// we check if we have to create a new particle
	if(m_nombre_actifs + m_nbr_emission <= m_nombre_tot && etat == 1)
	{

		m_temps += infos_tex_tmp->msec;

		if (m_temps >= m_temps_tot)
		{
			
			// on en crée autant qu'il le faut
			// we create as many as we need
			for(i=0 ; i<m_nbr_emission ; i++)
			{

				// on initialise la nouvelle particle
				init_particle(m_nombre_actifs);
				
				m_nombre_actifs++;

			}

			// on remet notre compteur à zéro
			m_temps = 0;

		}

	}

	// on met à jour la position et l'opacité (vie) de chaque particle en fonction de "infos_tex_tmp->msec" qui est le temps en ms passé entre l'affichage de 2 images
	// we update the position and opacity (life) of each particle according to "infos_tex_tmp-> msec" which is the time in ms passed between the display of 2 images
	for(i=0 ; i<m_nombre_actifs ; i++)
	{
		// coordonnées
		t_particles[i].x += (t_particles[i].d_x * infos_tex_tmp->msec / 10);
		t_particles[i].y += (t_particles[i].d_y * infos_tex_tmp->msec / 10);
		t_particles[i].z += (t_particles[i].d_z * infos_tex_tmp->msec / 10);

		// vie
		// life
		t_particles[i].vie -=  (t_particles[i].vitesse * infos_tex_tmp->msec / 10);

		// taille
		// cut
		t_particles[i].taille -= (t_particles[i].vitesse * infos_tex_tmp->msec / 25);

		// on vérifie que la vie de cette particle n'atteint pas 0
		// we check that the life of this particle does not reach 0
		if(t_particles[i].vie <= 0)
		{
			// on la réinitialise s'il le faut
			// reset
			if(etat == 1)
				init_particle(i);

		}
	}

}

// on affiche la particle (avec effet de type "billboarding")
// pour plus d'infos sur le billboarding (en anglais : http://www.lighthouse3d.com/opengl/billboarding/index.php3?billCheat)
// vous verrez, c'est très bien expliqué !

// we display the particle (with effect of type "billboarding")
// for more info on billboarding (http://www.lighthouse3d.com/opengl/billboarding/index.php3?billCheat)
// you'll see, it's very well explained!

void effet_particle::display()
{
	// tableau qui va contenir la matrice "MODELVIEW"
	// cette matric inscrit toutes les tranformations géométriques que l'on fait

	// array that will contain the matrix "MODELVIEW"
	// this matrix records all the geometric transformations that we do
	float mat[16];

	// on récupère la matrice
	// get the matrix
    glGetFloatv( GL_MODELVIEW_MATRIX, mat );

	// on déclare les vecteurs qui vont nous permettre de calculer le billboarding
	// // declare vectors that will allow us to calculate billboarding
    vector3f vRight( mat[0], mat[4], mat[8] );
    vector3f vUp( mat[1], mat[5], mat[9] );
    vector3f vPoint0;
    vector3f vPoint1;
    vector3f vPoint2;
    vector3f vPoint3;
    vector3f vCenter;
    
    //double fAdjustedSize = 0.4 + (double(rand() % 4)/10);
	
	glBegin(GL_QUADS);

	// on affiche toutes les particles actives
	// we display all the active particles
	for(int i = 0 ; i<m_nombre_actifs ; i++)
	{		
		// on vérifie que cette particle est toujours en vie
		// we check that this particle is still alive
		if(t_particles[i].vie > 0)
		{

			// on définit le centre
			// we define the center
			vCenter.x = t_particles[i].x;
			vCenter.y = t_particles[i].y;
			vCenter.z = t_particles[i].z;

			// on calcule les coordonnées des 4 points qui vont constituer la particle
			// calculate the coordinates of the 4 points that will constitute the particle
			vPoint0 = vCenter + ((-vRight - vUp) * t_particles[i].taille );
			vPoint1 = vCenter + (( vRight - vUp) * t_particles[i].taille );
			vPoint2 = vCenter + (( vRight + vUp) * t_particles[i].taille );
			vPoint3 = vCenter + ((-vRight + vUp) * t_particles[i].taille );
			
			// on ajuste la couleur de la particle (et son opacité --> dépend du mode de blending)
			//glColor3d( t_particles[i].vie / 4 , t_particles[i].vie / 1.1, t_particles[i].vie / 1.5 );

			// we adjust the color of the particle (and its opacity -> depends on the blending mode)
			// glColor3d (t_particles [i] .vie / 4, t_particles [i] .vie / 1.1, t_particles [i] .vie / 1.5);
			glColor3d( t_particles[i].vie * t_particles[i].r , t_particles[i].vie * t_particles[i].g, t_particles[i].vie * t_particles[i].b );

			// on dessine notre particle
			glTexCoord2d( 0.0, 0.0 );
			glVertex3d( vPoint0.x, vPoint0.y, vPoint0.z );

			glTexCoord2d( 1.0, 0.0 );
			glVertex3d( vPoint1.x, vPoint1.y, vPoint1.z );

			glTexCoord2d( 1.0, 1.0);
			glVertex3d( vPoint2.x, vPoint2.y, vPoint2.z );

			glTexCoord2d( 0.0, 1.0 );
			glVertex3d( vPoint3.x, vPoint3.y, vPoint3.z );

		}
	}

	glEnd();
}