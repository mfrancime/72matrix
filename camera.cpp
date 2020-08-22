/***************************************************
****************************************************
**                                                **
**                                                **
**                 classe "camera"                **
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


// where you included the file header of this class
#include "camera.h" 

// constructeur par défaut
camera::camera( double x_t, double y_t, double z_t, double x_v, double y_v, double z_v , double distance , struct infos_gen * infos_sz)
{
	// on initialise toutes les variables globales de cette classe

	// pointeur vers la structure contenant toutes les infos générales
	infos_tex_tmp = infos_sz;

	// le point "cible" de la caméra (là où elle regarde, sa cible)
	// the "target" point of the camera (where it looks, its target)
	infos_tex_tmp->infos_cam_sz.m_x_t = x_t;
	infos_tex_tmp->infos_cam_sz.m_y_t = y_t;
	infos_tex_tmp->infos_cam_sz.m_z_t = z_t;
	
	// la position de la caméra (l'oeuil)
	infos_tex_tmp->infos_cam_sz.m_x_v = x_v;
	infos_tex_tmp->infos_cam_sz.m_y_v = y_v;
	infos_tex_tmp->infos_cam_sz.m_z_v = z_v;

	// la distance qui sépare la cible de la caméra
	// the distance that separates the target from the camera
	infos_tex_tmp->infos_cam_sz.m_distance = distance;
	
	// la rotation en °
	// rotation in °
	infos_tex_tmp->infos_cam_sz.rot = 270;

	// l'état de la caméra (1 = active)
	// the state of the camera (1 = active)
	infos_tex_tmp->infos_cam_sz.etat = 1;

}

// destructeur
camera::~camera()
{

	//rien pour le moment

}

// on calcule la position de la caméra
// calculate the position of the camera
void camera::calculer()
{
	/*infos_tex_tmp->infos_cam_sz.m_z_v += ((double)(infos_tex_tmp->msec) / 120.0);
	infos_tex_tmp->infos_cam_sz.m_z_t += ((double)(infos_tex_tmp->msec) / 120.0);*/

	infos_tex_tmp->infos_cam_sz.m_z_v += ((double)(infos_tex_tmp->msec) / 72);
	infos_tex_tmp->infos_cam_sz.m_z_t += ((double)(infos_tex_tmp->msec) / 72);

	// on augmente le degré de rotation de la caméra
	//we increase the degree of rotation of the camera
	//infos_tex_tmp->infos_cam_sz.rot += ((double)(infos_tex_tmp->msec) / (281.0));
	infos_tex_tmp->infos_cam_sz.rot += ((double)(infos_tex_tmp->msec) / (720.0));
	//int rot = 270;
	//on vérifie qu'on ne va pas trop loin
	// we check that we do not go too far
	//if(rot > 360)
	//{
	//	rot = rot - 360;
	//}

	//double m_distance = 0;
	//m_distance -= ((double)(infos_tex_tmp->msec) / 50000.0f);

	//if(m_distance > 250)
	//	m_distance = -3000;

	double pi = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067;
	// we calculate the coordinates of the camera according to the position of its target and its eye and its degree of rotation
	//infos_tex_tmp->infos_cam_sz.m_x_v = (double)cos((infos_tex_tmp->infos_cam_sz.rot / 360.0) * 2.0 * 3.141) * infos_tex_tmp->infos_cam_sz.m_distance + infos_tex_tmp->infos_cam_sz.m_x_t;
    //infos_tex_tmp->infos_cam_sz.m_z_v = (double)sin((infos_tex_tmp->infos_cam_sz.rot / 360.0) * 2.0 * 3.141) * infos_tex_tmp->infos_cam_sz.m_distance + infos_tex_tmp->infos_cam_sz.m_z_t;
	infos_tex_tmp->infos_cam_sz.m_x_v = (double)cos((infos_tex_tmp->infos_cam_sz.rot / 180.0) *  pi) * infos_tex_tmp->infos_cam_sz.m_distance + infos_tex_tmp->infos_cam_sz.m_x_t;	
	infos_tex_tmp->infos_cam_sz.m_z_v = (double)sin((infos_tex_tmp->infos_cam_sz.rot / 180.0) *  pi) * infos_tex_tmp->infos_cam_sz.m_distance + infos_tex_tmp->infos_cam_sz.m_z_t;
	//m_x_v = m_distance;
	//m_z_v = m_distance;
	//m_y_v = y_v;
	//m_y_v = sin((rot / 360) * 2 * 3.141) * m_distance + m_z_t;
	
	// on informe opengl de la position de la caméra
	// opengl is informed of the position of the camera
	//gluLookAt(infos_tex_tmp->infos_cam_sz.m_x_v, infos_tex_tmp->infos_cam_sz.m_y_v, infos_tex_tmp->infos_cam_sz.m_z_v, infos_tex_tmp->infos_cam_sz.m_x_t, infos_tex_tmp->infos_cam_sz.m_y_t, infos_tex_tmp->infos_cam_sz.m_z_t, 0, 1, 0);

	gluLookAt ( infos_tex_tmp->infos_cam_sz.m_x_v , infos_tex_tmp->infos_cam_sz.m_y_v , infos_tex_tmp->infos_cam_sz.m_z_v , infos_tex_tmp->infos_cam_sz.m_x_t , infos_tex_tmp->infos_cam_sz.m_y_t , infos_tex_tmp->infos_cam_sz.m_z_t , 0 , -1 , 0 );


	//gluLookAt(infos_tex_tmp->infos_cam_sz.m_x_v+3, infos_tex_tmp->infos_cam_sz.m_y_v+3, infos_tex_tmp->infos_cam_sz.m_z_v+3, infos_tex_tmp->infos_cam_sz.m_x_t, infos_tex_tmp->infos_cam_sz.m_y_t, infos_tex_tmp->infos_cam_sz.m_z_t, 0, -1, 0);

}
