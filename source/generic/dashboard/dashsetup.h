SDL_Surface *dash_sprite = NULL;

GLuint dash_texture = NULL;

int menu_tree_par=1;

void dashgentexturecoords(float* texturecoords,float x,float y,float w,float h){
	texturecoords[0]=x;
	texturecoords[1]=y+h;
	texturecoords[2]=x+w;
	texturecoords[3]=y+h;
	texturecoords[4]=x+w;
	texturecoords[5]=y;
	texturecoords[6]=x;
	texturecoords[7]=y;
	for(int a=0; a<4; a++){
		texturecoords[a*2+0]/=1024;
		texturecoords[a*2+1]/=256;
	}
}

void dashprepdraw(){
	
	set2dcamera(0,screenh,0,screenw);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindTexture(GL_TEXTURE_2D,dash_texture);

}

void dashdonedraw(){

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);

}

#include "dashtime.h"
#include "dashcursor.h"
#include "dashtext.h"
#include "dashbutton.h"
#include "dashonoff.h"
#include "dashbars.h"
#include "dashmenu.h"

void dashsetup(){

	SDL_Surface *tempsurface = IMG_LoadOptimizeAlpha("Media/dashboard.png");
	dash_sprite = SDL_CreateRGBSurface(
		tempsurface->flags,
		//rounduptopowof2(tempsurface->w),
		1024,
		//rounduptopowof2(tempsurface->h),
		256,
		tempsurface->format->BitsPerPixel,
		tempsurface->format->Rmask,
		tempsurface->format->Gmask,
		tempsurface->format->Bmask,
		tempsurface->format->Amask);
	//tempsurface = SDL_DisplayFormatAlpha( tempsurface );
	//dash_sprite = SDL_DisplayFormatAlpha( dash_sprite );
	//SDL_SetAlpha(tempsurface,SDL_SRCALPHA,255);
	//SDL_SetAlpha(dash_sprite,SDL_SRCALPHA,255);
	SDL_SetAlpha(tempsurface,SDL_RLEACCEL,0);
	SDL_SetAlpha(dash_sprite,SDL_RLEACCEL,0);
	apply_surface(0,0,tempsurface,dash_sprite,NULL);
	SDL_FreeSurface(tempsurface);
	dash_texture=maketexturefromsurface(dash_sprite,0);

	setupdashcursor();
	setupdashtext();
	setupdashbutton();
	setupdashonoff();
	setupdashbars();
}
