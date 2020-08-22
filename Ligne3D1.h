/* ***************************************************
****************************************************
****
****
**class header "Ligne3D1"**
****
** Thomas John**
** thomas.john@open-design.be**
****
****
****************************************************
*************************************************** */

// this is used so that we do not load the same header twice
#ifndef C_LIGNE3D1_H

#define C_LIGNE3D1_H

#include "structures.h"
// # include <math.h>
// # include <windows.h>

#include "effet_particle.h"

class Ligne3D1
{

	// "private" data (variables, functions ...)
private:

	struct Lettre3D1 {

		// position of the letter
		double pos_x;
		double pos_y;
		double pos_z;

		// state of the letter
		int etat;

		// timer 1
		ULONGLONG temps;
		ULONGLONG temps_tot;

		// timer 2 (time_tot_2 = time to wait before changing the character, if the letter can change in time)
		ULONGLONG temps_2;
		ULONGLONG temps_tot_2;

		// character to display (56 different characters)
		// this int represents a position in the table grouping all the texture coordinates
		int caractere;

		// opacity of the letter
		double opacite;

		// distance from the letter to the eye of the camera
		double dist_tmp;

		// specify if the letter can change in time
		int change_sz;

	};

	// the structure that will contain the info on each letter of this line
	Lettre3D1* lettre_1;

	// the current number of active letters
	int m_nbr_actif;

	// the time it takes to create a new letter
	ULONGLONG m_temps_tot;
	ULONGLONG m_temps;

	// pointer to the structure containing info of all kinds
	infos_gen* infos_gen_tmp;

	// index of this class
	int index_tmp;

	// max number of letters for this line
	int nbr_max_lettres;

	// number of letters displayed (used for counting)
	int decpt_nbr_lettres;

	// duration of the fade between the white letter and the green letter (this to keep the same duration for all the letters of the line)
	ULONGLONG m_temps_fondu;

	// specify if this line uses the class "effect_particle"
	bool m_effet_particle;

	// the particle effect is only activated if the speed of this line (m_test_time) is fast (m_total_time <30)
	// when all the letters have finished their "life", the line is reset
	// it is important not to load an instance of the "effect_particle" class multiple times

	// specify if an instance of the class "item_effect" has been loaded
	bool m_charge_part;

	// we already declare a pointer that will point to an instance of the class "effect_particle"
	effet_particle* particles_1;

	// the distance from the line to the camera could have been used to gain speed
	// instead, this distance is calculated for each letter of each line
	// this increases the calculation time, but it will be useful for later (some effects)

	// distance from the line to the camera (the eye)
	double dist_tmp;

	// opacity of the line
	// double opacite_gen;

	// initialization of a letter
	void init_lettre(int index_sz);



	// public data
public:

	// state of the class
	int m_etat;

	// the coordinates of the line
	double m_x;
	double m_y;
	double m_z;

	// the default constructor
	Ligne3D1(double x, double y, double z, struct infos_gen*, int index);

	// the destroyer
	~Ligne3D1();

	// calculate the position and state of the particles
	void calculer();

	// display elements
	void display();

};


#endif