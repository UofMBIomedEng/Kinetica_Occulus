SDL_Rect dash_button_frame[2][9];

GLuint spritesheettexture = NULL;
GLuint tilebrighttexture = NULL;
GLuint tiledarktexture = NULL;

float wallbordertexturecoords[8];



float dash_button_texturecoords[2][9][8];

void setupdashbutton(){

	for(int a=0; a<2; a++)for(int b=0; b<3; b++)for(int c=0; c<3; c++){
		dash_button_frame[a][b*3+c].x=b*20+60*a;
		dash_button_frame[a][b*3+c].y=c*20+60;
		dash_button_frame[a][b*3+c].w=20;
		dash_button_frame[a][b*3+c].h=20;
	}
	
	for(int a=0; a<2; a++)for(int b=0; b<3; b++)for(int c=0; c<3; c++){
		dashgentexturecoords(dash_button_texturecoords[a][b*3+c],(float)b*20+60*a,(float)c*20+60,20,20);
	}

}

void dashdrawbutton(int x, int y,int w,int h,bool glow){

	//start
	dashprepdraw();
	//corners
	draw2dquad((float)x-20,(float)y-20,20,20,dash_button_texturecoords[glow][0]);
	draw2dquad((float)x-20,(float)y+h,20,20,dash_button_texturecoords[glow][2]);
	draw2dquad((float)x+w,(float)y-20,20,20,dash_button_texturecoords[glow][6]);
	draw2dquad((float)x+w,(float)y+h,20,20,dash_button_texturecoords[glow][8]);
	//edge 1
	for(int a=0; a<w/20; a++)
		draw2dquad((float)x+a*20,(float)y+h,20,20,dash_button_texturecoords[glow][5]);
	draw2dquad((float)x+w/20*20,(float)y+h,(float)w-w/20*20,20,dash_button_texturecoords[glow][5]);
	//edge 2
	for(int a=0; a<w/20; a++)
		draw2dquad((float)x+a*20,(float)y-20,20,20,dash_button_texturecoords[glow][3]);
	draw2dquad((float)x+w/20*20,(float)y-20,(float)w-w/20*20,20,dash_button_texturecoords[glow][3]);
	//edge 3
	for(int a=0; a<h/20; a++)
		draw2dquad((float)x+w,(float)y+a*20,20,20,dash_button_texturecoords[glow][7]);
	draw2dquad((float)x+w,(float)y+h/20*20,20,(float)h-h/20*20,dash_button_texturecoords[glow][7]);
	//edge 4
	for(int a=0; a<h/20; a++)
		draw2dquad((float)x-20,(float)y+a*20,20,20,dash_button_texturecoords[glow][1]);
	draw2dquad((float)x-20,(float)y+h/20*20,20,(float)h-h/20*20,dash_button_texturecoords[glow][1]);
	//insides
	for(int a=0; a<h/20; a++)for(int b=0; b<w/20; b++)
		draw2dquad((float)x+b*20,(float)y+a*20,20,20,dash_button_texturecoords[glow][4]);
	for(int a=0; a<h/20; a++)
		draw2dquad((float)x+w/20*20,(float)y+a*20,(float)w-w/20*20,20,dash_button_texturecoords[glow][4]);
	for(int a=0; a<w/20; a++)
		draw2dquad((float)x+a*20,(float)y+h/20*20,20,(float)h-h/20*20,dash_button_texturecoords[glow][4]);
	draw2dquad((float)x+w/20*20,(float)y+h/20*20,(float)w-w/20*20,(float)h-h/20*20,dash_button_texturecoords[glow][4]);
	//done
	dashdonedraw();

}

bool dashbutton(int x, int y,int w,int h,bool center,bool clickable,char* text){

	bool clicked=0;
	bool glow=0;

	if(center){
		x=x-w/2;
		y=y-h/2;
	}
	
	if(clickable
	&& cursorx[0]>x-14 && cursory[0]>y-14 && cursorx[0]<x+w+13 && cursory[0]<y+h+13){
		if(mousestate[SDL_BUTTON_LEFT]==2)clicked=1;
		glow=1;
	}
	
	dashdrawbutton(x,y,w,h,glow);

	x=x+w/2;
	y=y+h/2;

	dashtextcenter(x,y-21/2,text);

	return clicked;

}

// added for the progress bar

void init_progressbar(void){

	spritesheettexture=loadtexture((char*)"Media/spritesheettexture.png",mipmapping);
	tilebrighttexture=loadtexture((char*)"Media/tilebrighttexture.png",mipmapping);
	tiledarktexture=loadtexture((char*)"Media/tiledarktexture.png",mipmapping);

}

void drawtileblack(float posx1,float posy1,float posx2,float posy2){
	draw2dquad2(
		posx1,posy1,
		posx2-posx1,posy2-posy1,
		wallbordertexturecoords,
		0,0.f);
}

void drawtilebright(float posx1,float posy1,float posx2,float posy2){
	glBindTexture(GL_TEXTURE_2D,tilebrighttexture);
	float scale=1.f/64.f;
	float temptexturecoords[] = {
		posx1*scale,posy2*scale,
		posx2*scale,posy2*scale,
		posx2*scale,posy1*scale,
		posx1*scale,posy1*scale,};
	draw2dquad2(posx1,posy1,posx2-posx1,posy2-posy1,temptexturecoords,0,0.f);
	
	glBindTexture(GL_TEXTURE_2D,spritesheettexture);
}

void drawtiledark(float posx1,float posy1,float posx2,float posy2){
	glBindTexture(GL_TEXTURE_2D,tiledarktexture);
	float scale=1.f/64.f;
	float temptexturecoords[] = {
		posx1*scale,posy2*scale,
		posx2*scale,posy2*scale,
		posx2*scale,posy1*scale,
		posx1*scale,posy1*scale,};
	draw2dquad2(posx1,posy1,posx2-posx1,posy2-posy1,temptexturecoords,0,0.f);
	glBindTexture(GL_TEXTURE_2D,spritesheettexture);
}

void drawprogressbar(float posx1,float posy1,float posx2,float posy2,float border,float progress){
	drawtileblack(posx1-border,posy1-border,posx2+border,posy2+border);
	drawtiledark(posx1,posy1,posx2,posy2);
	progress=posx2*progress+posx1*(1.f-progress);
	drawtilebright(posx1,posy1,progress,posy2);
}
