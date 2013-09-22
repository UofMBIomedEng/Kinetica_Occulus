SDL_Rect dash_bars_frame[2];
float dash_bars_texturecoords[2][8];

char dash_bars_credits[2][256];

char dash_bars_gamename[256];
float dash_bars_gameversion=0.5;

void setupdashbars(){

	dash_bars_frame[0].x=0;
	dash_bars_frame[0].y=120;
	dash_bars_frame[0].w=640;
	dash_bars_frame[0].h=60;
	dash_bars_frame[1].x=0;
	dash_bars_frame[1].y=180;
	dash_bars_frame[1].w=640;
	dash_bars_frame[1].h=60;
	
	dashgentexturecoords(dash_bars_texturecoords[0],0,120,640,60);
	dashgentexturecoords(dash_bars_texturecoords[1],0,180,640,60);
	
	sprintf_s(dash_bars_credits[0],"%s","");
	sprintf_s(dash_bars_credits[1],"%s","The Kinetica Game Engin");
}

void dashbars(){

	int trans=dashonslide(0,60);

	dashprepdraw();
	draw2dquad(0,(float)-trans,screenw,60,dash_bars_texturecoords[0]);
	dashdonedraw();

	//dashtext(20,-70-trans+131-43,dash_bars_gamename);
	//if(dash_bars_gameversion || dash_bars_gamename){
	char temptext[256];
	sprintf_s(temptext,"%s [v%.1f]",dash_bars_gamename,dash_bars_gameversion);
	/*while(strlen(temptext)>2
	&& temptext[strlen(temptext)-2]!='.'
	&& temptext[strlen(temptext)-1]=='0'){
		//temptext[strlen(temptext)-1]=NULL;
		temptext[strlen(temptext)-1]='\0';
	}*/
	dashtext(20,-70-trans+131-43,temptext);
	//}

	dashtextright((int)screenw-20,-70-trans+131-43,dash_composedtext_date);
	

	dashprepdraw();
	draw2dquad(0,screenh-60+trans,screenw,60,dash_bars_texturecoords[1]);
	dashdonedraw();

	dashtext(20,(int)screenh-61+trans+3,(char*)dash_bars_credits[0]);
	dashtext(20,(int)screenh-61+trans+23,(char*)dash_bars_credits[1]);
	dashtextright((int)screenw-20,(int)screenh-61+trans+23,dash_composedtext_time);  //time

}
