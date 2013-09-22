SDL_Rect dash_text_frame[95];

float dash_text_texturecoords[95][8];

void setupdashtext(){
	int a=0;
	for(int b=0; b<3; b++)for(int c=0; c<32; c++)if(a<95){
		dash_text_frame[a].x=c*20;
		dash_text_frame[a].y=b*20;
		dash_text_frame[a].w=20;
		dash_text_frame[a].h=20;
		a++;
	}
	a=0;
	for(int b=0; b<3; b++)for(int c=0; c<32; c++)if(a<95){
		dashgentexturecoords(dash_text_texturecoords[a],(float)c*20,(float)b*20,20,20);
		a++;
	}
}

void dashtext(int posx,int posy,char* text){

	dashprepdraw();
	for(int a=0;a<(signed)strlen(text);a++){
		draw2dquad((float)posx-5,(float)posy,20,20,dash_text_texturecoords[text[a]-' ']);
		posx+=10;
	}
	dashdonedraw();
	
}

void dashtextcenter(int posx,int posy,char* text){
	posx-=(int)((float)((signed)strlen(text))*10.f*0.5f);
	dashtext(posx,posy,text);
}

void dashtextright(int posx,int posy,char* text){
	posx-=(int)((float)((signed)strlen(text))*10.f);
	dashtext(posx,posy,text);
}
