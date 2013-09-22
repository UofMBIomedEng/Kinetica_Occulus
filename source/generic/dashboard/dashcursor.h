SDL_Rect dash_cursor_frame[5];

float dash_cursor_texturecoords[5][8];

bool dashusecursors=0;
bool dashusecursor[4]={0,0,0,0};

void setupdashcursor(){

	for(int a=0; a<5; a++){
		dash_cursor_frame[a].x=440+a*40;
		dash_cursor_frame[a].y=60;
		dash_cursor_frame[a].w=40;
		dash_cursor_frame[a].h=60;
	}
	
	for(int a=0; a<5; a++){
		dashgentexturecoords(dash_cursor_texturecoords[a],(float)440+a*40,60,40,60);
	}

}

void dashdrawcursor(int x, int y,int cursornum){

	dashprepdraw();
	draw2dquad((float)x-12,(float)y-10,40,60,dash_cursor_texturecoords[cursornum]);
	dashdonedraw();
	
}

void dashcursors(){

	for(int a=0;a<4;a++)
		dashusecursor[a]=0;

	if(SDL_GetAppState() & SDL_APPMOUSEFOCUS)dashusecursor[0]=1;

	if(dashusecursors)	if(dashusecursor[0])dashdrawcursor(cursorx[0],cursory[0],0);
		
	dashusecursors=1;	
}
