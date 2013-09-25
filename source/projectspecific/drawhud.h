//extern int eye_offset;
void drawhud(){

	set2dcamera(0,screenh,0,screenw);
	//set3dcamera(camxpos,camypos,camzpos,-camxang,camyang+90*radiansindegree,camzang,50,screena);

	if(showminimap)drawminimap();

	if(1){
		char temptext[256];
		sprintf_s(temptext,"%s%2.0f","FPS: ",dash_framerate);
		dashbutton(25,75,200,10,0,0,(char*)temptext);
	}

	char temptext[256];
	sprintf_s(temptext,"%s%i%s","Collectables: ",collectablesfound,"/1000");
	dashbutton(25,105,200,10,0,0,(char*)temptext);

	sprintf_s(temptext,"%s%1d%s%1d%s%1d%s%1d","Stat: M=",usemouse," P=",showplayer, " E=", autoexit, " J=", usejoystick);
	dashbutton(25,135,200,10,0,0,(char*)temptext);

	sprintf_s(temptext,"%s%3.f%s%3.f%s%3.f","P:X=",playerxpos," Y=",playerypos, " Z=", playerzpos);
	dashbutton(25,165,200,10,0,0,(char*)temptext);

	sprintf_s(temptext,"%s%3.f%s%3.f%s%3.f","R:R=",roll*degreesinradian," P=",pitch*degreesinradian, " Y=", yaw*degreesinradian);
	dashbutton(25,195,200,10,0,0,(char*)temptext);

	sprintf_s(temptext,"%s%3.2f%s%3.2f%s%3.2f","R:R=",camxang," P=",camyang, " Y=", camzang);
	dashbutton(25,195,200,10,0,0,(char*)temptext);

//	sprintf_s(temptext,"Test=%.5f",dyneye );
//	dashbutton(25,225,200,10,0,0,(char*)temptext);
	//danyal added win_clue as a char...I hope that's ok!
	sprintf(temptext,"%d",worldgrid[(int)(playerxpos/10)][(int)(playerypos/10)][(int)(playerzpos/10)][0]);
	dashbutton(25,255,200,10,0,0,(char*)temptext);
	sprintf(temptext,"%c",win_clue);
	dashbutton(25,285,200,10,0,0,(char*)temptext);
	
	//...

	//danyal added
	/* We want to put in DirectX instead of this stuff
	float target_x=0,target_y=0,target_z=0;
	const int target_offset=3;
	if(allocentric){
			switch(targetwin){
			case 0:
				target_x=(a_win_pos[0]*worldtilesize);
				target_y=(a_win_pos[1]*worldtilesize)-4;
				target_z=(a_win_pos[2]*worldtilesize);
				break;
			case 1:
				target_x=(b_win_pos[0]*worldtilesize);
				target_y=(b_win_pos[1]*worldtilesize)-4;
				target_z=(b_win_pos[2]*worldtilesize);
				break;
			case 2:
				target_x=(c_win_pos[0]*worldtilesize);
				target_y=(c_win_pos[1]*worldtilesize)-4;
				target_z=(c_win_pos[2]*worldtilesize);
				break;
			}
		}
		else{
			target_x=(a_win_pos[0]*worldtilesize);
			target_y=(a_win_pos[1]*worldtilesize)-4;
			target_z=(a_win_pos[2]*worldtilesize);
		}
	if((target_x-target_offset<playerxpos)&&(target_x+target_offset>playerxpos)&&(target_y-target_offset<(playerypos))&&(target_y+target_offset>(playerypos))&&(target_z-target_offset<playerzpos)&&(target_z+target_offset>playerzpos)){
					PlaySound((LPCWSTR)"media/applause.wav", NULL, SND_FILENAME | SND_SYNC);//something is really messed up here
				}
	*/
}