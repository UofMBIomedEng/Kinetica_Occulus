float dashonpercent=0;
bool dashon=0;

SDL_Surface *screenshot_sprite = NULL;
SDL_Surface *dash_background_sprite = NULL;
SDL_Surface *dash_backgroundblurred_sprite = NULL;

Uint8* dash_background_opengl;

int dashonslide(int onpos,int offpos){
	return(int)((float)onpos*dashonpercent*0.01f+(float)offpos*(1.f-dashonpercent*0.01f));
}

void setupdashonoff(){
	dashonpercent=0;
	dashon=0;
	dash_background_opengl = new Uint8 [(unsigned int)(4*screenw*screenh)];
}

void dashonoff(float dashspeed){

	if(keystate[SDLK_ESCAPE]==2){
		if(dashon==0){
			dashon=1;
			if(dashonpercent==0){
				glReadPixels(0,0,(int)screenw,(int)screenh,GL_RGBA,GL_UNSIGNED_BYTE,dash_background_opengl);

				screenshot_sprite = SDL_CreateRGBSurface(SDL_SWSURFACE, (int)screenw, (int)screenh, 24, 0x000000FF, 0x0000FF00, 0x00FF0000, 0);
				char * pixels = new char [3 * (int)screenw * (int)screenh];
				glReadPixels(0, 0, (int)screenw, (int)screenh, GL_RGB, GL_UNSIGNED_BYTE, pixels);
				for (int i = 0 ; i < (int)screenh ; i++)
					std::memcpy( ((char *) screenshot_sprite->pixels) + screenshot_sprite->pitch * i, pixels + 3 * (int)screenw * ((int)screenh-i - 1), (int)screenw*3 );
				delete [] pixels;

			}
		}else{
			dashon=0;
			menu_tree_par=1;
		}
	}

	if(dashonpercent!=0){
		glDrawPixels((int)screenw,(int)screenh,GL_RGBA,GL_UNSIGNED_BYTE,dash_background_opengl);
	}

	if(dashon){
		dashonpercent+=5.f*dashspeed;
		//if(dashonpercent>100)dashonpercent=100;
	}else{
		dashonpercent-=5.f*dashspeed;
		//if(dashonpercent<0)dashonpercent=0;
	}
	if(dashonpercent>100)dashonpercent=100;
	if(dashonpercent<0)dashonpercent=0;
	if(dashonpercent!=dashonpercent)dashonpercent=0;

}
