#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#include "glaux.h"
#include "SDL.h"

#define GL_TEXTURE_CUBE_MAP_ARB             0x8513
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB  0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB  0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB  0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB  0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB  0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB  0x851A

bool SKYBOX_Initialize(){

	GLenum cube_map_target[6] = {           
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB,
		GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB
	};

	AUX_RGBImageRec * texture_image[6];

	char sky_tex_name[6][20]={"Media/sky/XN.bmp",
		"Media/sky/XP.bmp",
		"Media/sky/YN.bmp",
		"Media/sky/YP.bmp",
		"Media/sky/ZN.bmp",
		"Media/sky/ZP.bmp"};
	WCHAR TMP[20];
	for (int i = 0; i < 6; i++){
		OemToCharW(sky_tex_name[i], TMP);
		texture_image[i] = auxDIBImageLoad(TMP);
	}

	glGenTextures(1, &cube_map_texture_ID);

	glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, cube_map_texture_ID);

	for (int i = 0; i < 6; i++)
		glTexImage2D(cube_map_target[i], 0, GL_RGB, texture_image[i]->sizeX, texture_image[i]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_image[i]->data);

	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE );

	return true;

}

void SKYBOX_DrawSkyBox(void){
	// Cube size
	float t = 1.5f;

	//use of the cube map texture
	glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, cube_map_texture_ID);

	//setting the orientation
//	glPushMatrix();
//	glLoadIdentity();
//	glRotatef( camera_pitch, 1.0f, 0.0f, 0.0f );
//	glRotatef( camera_yaw, 0.0f, 1.0f, 0.0f );	
//	glRotatef(camera_roll,0.0f,0.0f,1.0f);

	 // glRotated(90,0,1,0);

	// Rendering the geometry
	glBegin(GL_TRIANGLE_STRIP);			                // X Negative	
	glTexCoord3f(-t,-t,-t); glVertex3f(-t,-t,-t); 	
	glTexCoord3f(-t,t,-t); glVertex3f(-t,t,-t);
	glTexCoord3f(-t,-t,t); glVertex3f(-t,-t,t);
	glTexCoord3f(-t,t,t); glVertex3f(-t,t,t);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);			// X Positive
	glTexCoord3f(t, -t,-t); glVertex3f(t,-t,-t);
	glTexCoord3f(t,-t,t); glVertex3f(t,-t,t);
	glTexCoord3f(t,t,-t); glVertex3f(t,t,-t); 
	glTexCoord3f(t,t,t); glVertex3f(t,t,t); 	
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);			// Y Negative	
	glTexCoord3f(-t,-t,-t); glVertex3f(-t,-t,-t);
	glTexCoord3f(-t,-t,t); glVertex3f(-t,-t,t);
	glTexCoord3f(t, -t,-t); glVertex3f(t,-t,-t);
	glTexCoord3f(t,-t,t); glVertex3f(t,-t,t);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);			// Y Positive		
	glTexCoord3f(-t,t,-t); glVertex3f(-t,t,-t);
	glTexCoord3f(t,t,-t); glVertex3f(t,t,-t); 
	glTexCoord3f(-t,t,t); glVertex3f(-t,t,t);
	glTexCoord3f(t,t,t); glVertex3f(t,t,t); 	
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);			// Z Negative		
	glTexCoord3f(-t,-t,-t); glVertex3f(-t,-t,-t);
	glTexCoord3f(t, -t,-t); glVertex3f(t,-t,-t);
	glTexCoord3f(-t,t,-t); glVertex3f(-t,t,-t);
	glTexCoord3f(t,t,-t); glVertex3f(t,t,-t); 
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);			// Z Positive	
	glTexCoord3f(-t,-t,t); glVertex3f(-t,-t,t);
	glTexCoord3f(-t,t,t); glVertex3f(-t,t,t);
	glTexCoord3f(t,-t,t); glVertex3f(t,-t,t);
	glTexCoord3f(t,t,t); glVertex3f(t,t,t); 	
	glEnd();

	// Reinitialization of the the mode view matrix
	//glPopMatrix();
}


void SKYBOX_Render(){
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_CUBE_MAP_ARB); 
	glDisable(GL_LIGHTING);

	glDepthMask(GL_FALSE);

	SKYBOX_DrawSkyBox();  

	glDepthMask(GL_TRUE);

	glDisable(GL_TEXTURE_CUBE_MAP_ARB); 
	glEnable(GL_LIGHTING);
}

void SKYBOX_Finalize(){
	// Suppression de la skybox
	glDeleteTextures( 1, &cube_map_texture_ID );
}


#endif