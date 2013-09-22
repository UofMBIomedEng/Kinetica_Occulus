const int streetlevel=3;
const int minbuildingheight=3;
const int maxbuildingheight=9;

const int worldgridsizex = 50;
const int worldgridsizey = 15;
const int worldgridsizez = 50;

//street width setting
const int streetwidth  = 2;

#define GRASS_TILE				10
#define SIDEWALK_CORNER_TILE	9
#define SIDEWALK_TILE			8


char worldgrid[worldgridsizex][worldgridsizey][worldgridsizez][2];

//clean up
void genworldgrid_cleanup(){

	//clean the world grid
	for(int x=0; x<worldgridsizex; x++)
		for(int y=0; y<worldgridsizey; y++)
			for(int z=0; z<worldgridsizez; z++){
				worldgrid[x][y][z][0]=0;
				worldgrid[x][y][z][1]=0;
			}

}

//island streets and sidewalks
void genworldgrid_street(){
	
	//mid point position
	int worldmidposx = worldgridsizex / 2;
	int worldmidposz = worldgridsizez / 2;

	for(int x=0; x<worldgridsizex; x++)
		for(int z=0; z<worldgridsizez; z++)
			worldgrid[x][streetlevel][z][0]=GRASS_TILE;

	for(int x=0; x<worldgridsizex; x++)
		for(int z=0; z<worldgridsizez; z++)
			worldgrid[x][streetlevel][z][0]=GRASS_TILE;
		
	
	
}

//Foundation of the building
void genworldgrid_sidewalk(){

	

	//sidewalks
	for(int z=house_low_z+1; z<=(house_high_z-1); z++){
		worldgrid[house_low_x][streetlevel][z][0]=8;
		worldgrid[house_low_x][streetlevel][z][1]=0;
		worldgrid[house_high_x][streetlevel][z][0]=8;
		worldgrid[house_high_x][streetlevel][z][1]=2;
	}
	for(int x=house_low_x+1; x<=(house_high_x-1); x++){
		worldgrid[x][streetlevel][house_low_z][0]=8;
		worldgrid[x][streetlevel][house_low_z][1]=3;
		worldgrid[x][streetlevel][house_high_z][0]=8;
		worldgrid[x][streetlevel][house_high_z][1]=1;
	}

	//sidewalk corners
	worldgrid[house_high_z][streetlevel][house_low_z][0]=9;
	worldgrid[house_high_z][streetlevel][house_low_z][1]=3;
	worldgrid[house_low_z][streetlevel][house_low_z][0]=9;
	worldgrid[house_low_z][streetlevel][house_low_z][1]=0;
	worldgrid[house_low_z][streetlevel][house_high_z][0]=9;
	worldgrid[house_low_z][streetlevel][house_high_z][1]=1;
	worldgrid[house_high_z][streetlevel][house_high_z][0]=9;
	worldgrid[house_high_z][streetlevel][house_high_z][1]=2;
}

//buildings
void genworldgrid_building(){

	
	//wall
	for (int y=0;y<=2;y++)
	{
		for(int z=house_low_z+2; z<=(house_high_z-2); z++){
			worldgrid[house_low_x+1][streetlevel+y][z][0]=72;
			worldgrid[house_low_x+1][streetlevel+y][z][1]=0;
			worldgrid[house_high_x-1][streetlevel+y][z][0]=72;
			worldgrid[house_high_x-1][streetlevel+y][z][1]=2;
		}
		for(int x=house_low_x+2; x<=(house_high_x-2); x++){
			worldgrid[x][streetlevel+y][house_low_z+1][0]=72;
			worldgrid[x][streetlevel+y][house_low_z+1][1]=3;
			worldgrid[x][streetlevel+y][house_high_z-1][0]=72;
			worldgrid[x][streetlevel+y][house_high_z-1][1]=1;
		}

		worldgrid[house_high_z-1][streetlevel+y][house_low_z+1][0]=71;
		worldgrid[house_high_z-1][streetlevel+y][house_low_z+1][1]=2;
		worldgrid[house_low_z+1][streetlevel+y][house_low_z+1][0]=71;
		worldgrid[house_low_z+1][streetlevel+y][house_low_z+1][1]=3;
		worldgrid[house_low_z+1][streetlevel+y][house_high_z-1][0]=71;
		worldgrid[house_low_z+1][streetlevel+y][house_high_z-1][1]=0;
		worldgrid[house_high_z-1][streetlevel+y][house_high_z-1][0]=71;
		worldgrid[house_high_z-1][streetlevel+y][house_high_z-1][1]=1;
	}

	//building windows
	for(int y=0;y<=2;y++)
	{
		for(int j=1;j<4;j++)worldgrid[house_high_x-1][streetlevel+y][house_low_z+(j*(house_high_z-house_low_z)/4)][0]=69;
		for(int j=1;j<4;j++)worldgrid[house_low_x+1][streetlevel+y][house_low_z+(j*(house_high_z-house_low_z)/4)][0]=69;
		for(int j=1;j<4;j++)worldgrid[house_low_x+(j*(house_high_x-house_low_x)/4)][streetlevel+y][house_high_z-1][0]=69;
		for(int j=1;j<4;j++)worldgrid[house_low_x+(j*(house_high_x-house_low_x)/4)][streetlevel+y][house_low_z+1][0]=69;
	}

	expectdist=0;    //reset the expected distance value

	if(allocentric){

		//5
		a_win_pos[0]=house_low_x+(2)*(house_high_x-house_low_x)/4;
		a_win_pos[1]=streetlevel+1;
		a_win_pos[2]=house_low_z+1;
		//5

		//2
		b_win_pos[0]=house_low_x+((3)*(house_high_x-house_low_x)/4);
		b_win_pos[1]=streetlevel+2;
		b_win_pos[2]=house_high_z-1;
		//2

		//6
		c_win_pos[0]=house_high_x-1;
		c_win_pos[1]=streetlevel+2;
		c_win_pos[2]=house_low_z+(2)*(house_high_z-house_low_z)/4;
		//6

		if(kidmode){
			worldgrid[a_win_pos[0]][a_win_pos[1]][a_win_pos[2]][0]=kittenwall_tile; 	
			worldgrid[b_win_pos[0]][b_win_pos[1]][b_win_pos[2]][0]=puppywall_tile; 
			worldgrid[c_win_pos[0]][c_win_pos[1]][c_win_pos[2]][0]=cowwall_tile;
		}
		else
		{
			worldgrid[a_win_pos[0]][a_win_pos[1]][a_win_pos[2]][0]=circle_window_tile; 	
			worldgrid[b_win_pos[0]][b_win_pos[1]][b_win_pos[2]][0]=X_window_tile; 
			worldgrid[c_win_pos[0]][c_win_pos[1]][c_win_pos[2]][0]=triangle_window_tile;
		}
		switch(((trial-1)%3)+1){
			case 1:
				//climb the stairs
				expectdist += 6;
				//for the clue chart resembles letter W
				win_clue=87;
			break;
			case 2:
				//climb the stairs
				expectdist += 12;
				//for the clue chart resembles letter F
				win_clue=70;
			break;
			case 3:
				//climb the stairs
				expectdist += 13;
				//for the clue chart resembles letter H
				win_clue=72;
			break;
		}	
	}
	else{
		//objective windows
		switch(trial){
			case 1:

				//climb the stairs
				expectdist += 2.6;

				rand_sel=((int)rand()%3)+1;
				win_clue=76+rand_sel;
				//1
				a_win_pos[0]=house_low_x+1;
				a_win_pos[1]=streetlevel+1;
				a_win_pos[2]=house_low_z+((rand_sel)*(house_high_z-house_low_z)/4);
				//1

				//to the target window
				expectdist += 1 + sqrt(((22.7-a_win_pos[0])*(22.7-a_win_pos[0]))+((26-a_win_pos[2])*(26-a_win_pos[2])));

				//4
				b_win_pos[0]=house_high_x-1;
				b_win_pos[1]=streetlevel+1;
				b_win_pos[2]=house_low_z+((((int)rand()%3)+1)*(house_high_z-house_low_z)/4);
				//4

				//3
				c_win_pos[0]=house_low_x+((((int)rand()%3)+1)*(house_high_x-house_low_x)/4);
				c_win_pos[1]=streetlevel+2;
				c_win_pos[2]=house_low_z+1;
				//3

			break;
			case 2:
				//climb the stairs
				expectdist += (2.6*2);

				rand_sel=((int)rand()%3)+1;
				win_clue=67+rand_sel;
				//2
				a_win_pos[0]=house_low_x+((rand_sel)*(house_high_x-house_low_x)/4);
				a_win_pos[1]=streetlevel+2;
				a_win_pos[2]=house_high_z-1;
				//2

				//to the target window
				expectdist += 3 + sqrt(((22.3-a_win_pos[0])*(22.3-a_win_pos[0]))+((25.5-a_win_pos[2])*(25.5-a_win_pos[2])));

				//7
				b_win_pos[0]=house_low_x+((((int)rand()%3)+1)*(house_high_x-house_low_x)/4);
				b_win_pos[1]=streetlevel+1;
				b_win_pos[2]=house_high_z-1;
				//7

				//8
				c_win_pos[0]=house_low_x+1;
				c_win_pos[1]=streetlevel+2;
				c_win_pos[2]=house_low_z+((((int)rand()%3)+1)*(house_high_z-house_low_z)/4);
				//8
			break;
			case 3:
				//climb the stairs
				expectdist += (2.6*2)+(1.3);

				rand_sel=((int)rand()%3)+1;
				win_clue=77-rand_sel;
				//3
				a_win_pos[0]=house_low_x+((rand_sel)*(house_high_x-house_low_x)/4);
				a_win_pos[1]=streetlevel+2;
				a_win_pos[2]=house_low_z+1;
				//3

				//to the target window
				expectdist += sqrt(((22.8-a_win_pos[0])*(22.8-a_win_pos[0]))+((23.6-a_win_pos[2])*(23.6-a_win_pos[2])));

				//6
				b_win_pos[0]=house_high_x-1;
				b_win_pos[1]=streetlevel+2;
				b_win_pos[2]=house_low_z+((((int)rand()%3)+1)*(house_high_z-house_low_z)/4);
				//6
			
				//5
				c_win_pos[0]=house_low_x+((((int)rand()%3)+1)*(house_high_x-house_low_x)/4);
				c_win_pos[1]=streetlevel+1;
				c_win_pos[2]=house_low_z+1;
				//5

			break;
			case 4:
				//climb the stairs
				expectdist += 2.6;

				rand_sel=((int)rand()%3)+1;
				win_clue=86-rand_sel;
				//4
				a_win_pos[0]=house_high_x-1;
				a_win_pos[1]=streetlevel+1;
				a_win_pos[2]=house_low_z+((rand_sel)*(house_high_z-house_low_z)/4);
				//4

				//to the target window
				expectdist += 2.5 + sqrt(((26.5-a_win_pos[0])*(26.5-a_win_pos[0]))+((25.7-a_win_pos[2])*(25.7-a_win_pos[2])));

				//3
				b_win_pos[0]=house_low_x+((((int)rand()%3)+1)*(house_high_x-house_low_x)/4);
				b_win_pos[1]=streetlevel+2;
				b_win_pos[2]=house_low_z+1;
				//3

				//6
				c_win_pos[0]=house_high_x-1;
				c_win_pos[1]=streetlevel+2;
				c_win_pos[2]=house_low_z+((((int)rand()%3)+1)*(house_high_z-house_low_z)/4);
				//6

			break;
			case 5:
				//climb the stairs
				expectdist += 2.6;

				rand_sel=((int)rand()%3)+1;
				win_clue=89-rand_sel;
				//5
				a_win_pos[0]=house_low_x+((rand_sel)*(house_high_x-house_low_x)/4);
				a_win_pos[1]=streetlevel+1;
				a_win_pos[2]=house_low_z+1;
				//5

				//to the target window
				expectdist += 3.8 + sqrt(((22.1-a_win_pos[0])*(22.1-a_win_pos[0]))+((23.4-a_win_pos[2])*(23.4-a_win_pos[2])));

				//1
				b_win_pos[0]=house_low_x+1;
				b_win_pos[1]=streetlevel+1;
				b_win_pos[2]=house_low_z+((((int)rand()%3)+1)*(house_high_z-house_low_z)/4);
				//1

				//4
				c_win_pos[0]=house_high_x-1;
				c_win_pos[1]=streetlevel+1;
				c_win_pos[2]=house_low_z+((((int)rand()%3)+1)*(house_high_z-house_low_z)/4);
				//4

			break;
			case 6:
				//climb the stairs
				expectdist += (2.6*2)+(1.3);

				rand_sel=((int)rand()%3)+1;
				win_clue=74-rand_sel;
				//6
				a_win_pos[0]=house_high_x-1;
				a_win_pos[1]=streetlevel+2;
				a_win_pos[2]=house_low_z+((rand_sel)*(house_high_z-house_low_z)/4);
				//6

				//to the target window
				expectdist += 2.5 + sqrt(((26.3-a_win_pos[0])*(26.3-a_win_pos[0]))+((23-a_win_pos[2])*(23-a_win_pos[2])));

				//8
				b_win_pos[0]=house_low_x+1;
				b_win_pos[1]=streetlevel+2;
				b_win_pos[2]=house_low_z+((((int)rand()%3)+1)*(house_high_z-house_low_z)/4);
				//8

				//2
				c_win_pos[0]=house_low_x+((((int)rand()%3)+1)*(house_high_x-house_low_x)/4);
				c_win_pos[1]=streetlevel+2;
				c_win_pos[2]=house_high_z-1;
				//2

			break;
			case 7:
				//climb the stairs
				expectdist += 2.6;

				rand_sel=((int)rand()%3)+1;
				win_clue=79+rand_sel;
				//7
				a_win_pos[0]=house_low_x+((rand_sel)*(house_high_x-house_low_x)/4);
				a_win_pos[1]=streetlevel+1;
				a_win_pos[2]=house_high_z-1;
				//7

				//to the target window
				expectdist += sqrt(((22.7-a_win_pos[0])*(22.7-a_win_pos[0]))+((26-a_win_pos[2])*(26-a_win_pos[2])));

				//5
				b_win_pos[0]=house_low_x+((((int)rand()%3)+1)*(house_high_x-house_low_x)/4);
				b_win_pos[1]=streetlevel+1;
				b_win_pos[2]=house_low_z+1;
				//5

				//3
				c_win_pos[0]=house_low_x+((((int)rand()%3)+1)*(house_high_x-house_low_x)/4);
				c_win_pos[1]=streetlevel+2;
				c_win_pos[2]=house_low_z+1;
				//3

			break;
			case 8:
				//climb the stairs
				expectdist += (2.6*2)+(1.3);

				rand_sel=((int)rand()%3)+1;
				win_clue=64+rand_sel;
				//8
				a_win_pos[0]=house_low_x+1;
				a_win_pos[1]=streetlevel+2;
				a_win_pos[2]=house_low_z+((rand_sel)*(house_high_z-house_low_z)/4);
				//8

				//to the target window
				expectdist += sqrt(((22.8-a_win_pos[0])*(22.8-a_win_pos[0]))+((23.6-a_win_pos[2])*(23.6-a_win_pos[2])));

				//2
				b_win_pos[0]=house_low_x+((((int)rand()%3)+1)*(house_high_x-house_low_x)/4);
				b_win_pos[1]=streetlevel+2;
				b_win_pos[2]=house_high_z-1;
				//2

				//6
				c_win_pos[0]=house_high_x-1;
				c_win_pos[1]=streetlevel+2;
				c_win_pos[2]=house_low_z+((((int)rand()%3)+1)*(house_high_z-house_low_z)/4);
				//6

			break;
		}

		if(kidmode){
			switch(targetwin)
			{
			case 0:	worldgrid[a_win_pos[0]][a_win_pos[1]][a_win_pos[2]][0]=kittenwall_tile; 	
				worldgrid[b_win_pos[0]][b_win_pos[1]][b_win_pos[2]][0]=puppywall_tile;  
				worldgrid[c_win_pos[0]][c_win_pos[1]][c_win_pos[2]][0]=cowwall_tile;  
						break; 

			case 1:	worldgrid[a_win_pos[0]][a_win_pos[1]][a_win_pos[2]][0]=puppywall_tile; 	
				worldgrid[b_win_pos[0]][b_win_pos[1]][b_win_pos[2]][0]=kittenwall_tile; 
				worldgrid[c_win_pos[0]][c_win_pos[1]][c_win_pos[2]][0]=cowwall_tile;  
						break;

			case 2:	worldgrid[a_win_pos[0]][a_win_pos[1]][a_win_pos[2]][0]=cowwall_tile; 	
				worldgrid[b_win_pos[0]][b_win_pos[1]][b_win_pos[2]][0]=puppywall_tile; 
				worldgrid[c_win_pos[0]][c_win_pos[1]][c_win_pos[2]][0]=kittenwall_tile;  
						break;
			}
		}
		else
		{
			switch(targetwin)
			{
			case 0:	worldgrid[a_win_pos[0]][a_win_pos[1]][a_win_pos[2]][0]=circle_window_tile; 	
				worldgrid[b_win_pos[0]][b_win_pos[1]][b_win_pos[2]][0]=X_window_tile; 
				worldgrid[c_win_pos[0]][c_win_pos[1]][c_win_pos[2]][0]=triangle_window_tile;  
						break;

			case 1:	worldgrid[a_win_pos[0]][a_win_pos[1]][a_win_pos[2]][0]=X_window_tile; 	
				worldgrid[b_win_pos[0]][b_win_pos[1]][b_win_pos[2]][0]=circle_window_tile; 
				worldgrid[c_win_pos[0]][c_win_pos[1]][c_win_pos[2]][0]=triangle_window_tile;  
						break;

			case 2:	worldgrid[a_win_pos[0]][a_win_pos[1]][a_win_pos[2]][0]=triangle_window_tile; 	
				worldgrid[b_win_pos[0]][b_win_pos[1]][b_win_pos[2]][0]=X_window_tile; 
				worldgrid[c_win_pos[0]][c_win_pos[1]][c_win_pos[2]][0]=circle_window_tile;  
						break;
			}
		}
	}

	//building door
	worldgrid[house_high_x-3-(rand()%(house_high_x-house_low_x-6))][streetlevel][house_low_z+1][0]=door_tile;
	worldgrid[house_high_x-3-(rand()%(house_high_x-house_low_x-6))][streetlevel][house_high_z-1][0]=door_tile;
	int entrydoorz=house_high_z-3-(rand()%(house_high_z-house_low_z-6));
	worldgrid[house_low_x+1][streetlevel][entrydoorz][0]=door_tile;
	worldgrid[house_high_x-1][streetlevel][house_high_z-3-(rand()%(house_high_z-house_low_z-6))][0]=door_tile;

	//calculated the expected distance
	//to the entrance door
	expectdist += sqrt(((float)((worldgridsizex/2)-((worldgridsizex/3))-(house_low_x+1))*((worldgridsizex/2)-((worldgridsizex/3))-(house_low_x+1))) 
					+(((worldgridsizex/2)-(entrydoorz))*((worldgridsizex/2)-(entrydoorz))));
	//to the stairs
	expectdist += sqrt((((23.6)-(house_low_x+1))*((23.6)-(house_low_x+1)))
					+(((23.3)-(entrydoorz))*((23.3)-(entrydoorz))));
	

	//floor base
	for(int y=0;y<=2;y++)
		for(int z=house_low_z+2; z<=(house_high_z-2); z++)
			for(int x=house_low_x+2; x<=(house_high_x-2); x++)
				worldgrid[x][streetlevel+y][z][0]=hardwood_tile;
	switch(stairtype){
	case 1:

	//stairs at 180 degrees
		worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=stairs_tile;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=stairs_tile;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][0]=stairs_tile;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][1]=2;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=stairs_tile;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][1]=2;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	break;
	case 2:
	//stairs at 90 degrees (floor not fixed for this configuration)
	//holes in floor
	//second floor floor
	worldgrid[25][streetlevel+1][24][0]=empty_tile;//top of stairs...
	worldgrid[25][streetlevel+1][25][0]=empty_tile;
	worldgrid[24][streetlevel+1][24][0]=empty_tile;
	worldgrid[24][streetlevel+1][25][0]=empty_tile;//...
	worldgrid[26][streetlevel+1][23][0]=empty_tile;//bottom of stairs...
	worldgrid[27][streetlevel+1][23][0]=empty_tile;
	worldgrid[23][streetlevel+1][26][0]=empty_tile;
	worldgrid[22][streetlevel+1][26][0]=empty_tile;//...
	//3rd floor floor
	worldgrid[26][streetlevel+2][23][0]=empty_tile;
	worldgrid[27][streetlevel+2][23][0]=empty_tile;
	worldgrid[23][streetlevel+2][26][0]=empty_tile;
	worldgrid[22][streetlevel+2][26][0]=empty_tile;
	//isolators

	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=stairs_tile;//first floor up
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=0;//bottom of first floor stairs
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][1]=2;//first floor up rotation
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=stairs_tile;//first floor up
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;//bottom of first floor stairs
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)-1][0]=stairs2_tile;//second floor up//was plus 1 z
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)-1][1]=1;//was2;//second floor up rotation
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+2][0]=stairs2_tile;//second floor up//was plus 1 z
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+2][1]=3;//was2;//second floor up rotation
	break;
	case 3:

	//stairs at 180 degrees
		worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=ramp_tile;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=ramp_tile;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][0]=ramp_tile;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][1]=2;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=ramp_tile;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][1]=2;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=0;

	break;
	
	case 4:
	//stairs at 90 degrees (floor not fixed for this configuration)
	//holes in floor
	//second floor floor
	worldgrid[25][streetlevel+1][24][0]=empty_tile;//top of stairs...
	worldgrid[25][streetlevel+1][25][0]=empty_tile;
	worldgrid[24][streetlevel+1][24][0]=empty_tile;
	worldgrid[24][streetlevel+1][25][0]=empty_tile;//...
	worldgrid[26][streetlevel+1][23][0]=empty_tile;//bottom of stairs...
	worldgrid[27][streetlevel+1][23][0]=empty_tile;
	worldgrid[23][streetlevel+1][26][0]=empty_tile;
	worldgrid[22][streetlevel+1][26][0]=empty_tile;//...
	//3rd floor floor
	worldgrid[26][streetlevel+2][23][0]=empty_tile;
	worldgrid[27][streetlevel+2][23][0]=empty_tile;
	worldgrid[23][streetlevel+2][26][0]=empty_tile;
	worldgrid[22][streetlevel+2][26][0]=empty_tile;
	
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=ramp_tile;//first floor up
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=0;//bottom of first floor stairs
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][1]=2;//first floor up rotation
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=ramp_tile;//first floor up
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;//bottom of first floor stairs
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)-1][0]=ramp2_tile;//second floor up//was plus 1 z
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)-1][1]=1;//was2;//second floor up rotation
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+2][0]=ramp2_tile;//second floor up//was plus 1 z
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+2][1]=3;//was2;//second floor up rotation
	break;
	}
	//roof
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel+3][house_low_z+((house_high_z-house_low_z)/2)][0]=roof_tile;

	

	if(allocentric)
	{
		worldgrid[1+house_low_x+(2)*(house_high_x-house_low_x)/4][streetlevel+1][house_high_z-1][0]=timhortonswall_tile;
		worldgrid[house_high_x-2][streetlevel+2][house_high_z-1][0]=atmmachinewall_tile;
	}
	
}
/*
// box
void genworldgrid_box(){
	worldgrid[worldgridsizex/2][streetlevel+1][worldgridsizez/2][0]=7;
}
//catacombs
void genworldgrid_part4(){

	//sewer to catacombs
	for(int n=0; n<(float)worldgridsizex*(float)worldgridsizez*0.06; n++){
		int x=rand()%(worldgridsizex-20)+10;
		int z=rand()%(worldgridsizez-20)+10;
		if(worldgrid[x][streetlevel-1][z][0]==12){
			if(worldgrid[x][streetlevel-1][z][1]==0){
				bool emptyspace=1;
				for(int a=0; a<5; a++)for(int b=0; b<6; b++)if(a>0 || b>0)
					if(worldgrid[x-b][streetlevel-1-a][z][0])emptyspace=0;
				for(int a=0; a<7; a++)for(int b=0; b<7; b++)
					if(worldgrid[x-3+a-7][streetlevel-3][z-3+b][0])emptyspace=0;
				if(emptyspace){
					worldgrid[x][streetlevel-1][z][0]=21;
					worldgrid[x-2][streetlevel-2][z][0]=22;
					worldgrid[x-2][streetlevel-2][z][1]=3;
					worldgrid[x-5][streetlevel-3][z][0]=22;
					worldgrid[x-5][streetlevel-3][z][1]=3;
					worldgrid[x-7][streetlevel-3][z][0]=17;
					worldgrid[x-7][streetlevel-3][z][1]=3;
					worldgrid[x-8][streetlevel-3][z][0]=18;
					//placeholders
					worldgrid[x-3][streetlevel-3][z][0]=1;
					worldgrid[x-4][streetlevel-3][z][0]=1;
					worldgrid[x-6][streetlevel-3][z][0]=1;
					worldgrid[x-3][streetlevel-3][z-1][0]=1;
					worldgrid[x-4][streetlevel-3][z-1][0]=1;
					worldgrid[x-5][streetlevel-3][z-1][0]=1;
					worldgrid[x-6][streetlevel-3][z-1][0]=1;
					worldgrid[x-7][streetlevel-3][z-1][0]=1;
					worldgrid[x-3][streetlevel-3][z+1][0]=1;
					worldgrid[x-4][streetlevel-3][z+1][0]=1;
					worldgrid[x-5][streetlevel-3][z+1][0]=1;
					worldgrid[x-6][streetlevel-3][z+1][0]=1;
					worldgrid[x-7][streetlevel-3][z+1][0]=1;
				}
			}
			if(worldgrid[x][streetlevel-1][z][1]==2){
				bool emptyspace=1;
				for(int a=0; a<5; a++)for(int b=0; b<6; b++)if(a>0 || b>0)
					if(worldgrid[x+b][streetlevel-1-a][z][0])emptyspace=0;
				for(int a=0; a<7; a++)for(int b=0; b<7; b++)
					if(worldgrid[x-3+a+7][streetlevel-3][z-3+b][0])emptyspace=0;
				if(emptyspace){
					worldgrid[x][streetlevel-1][z][0]=21;
					worldgrid[x+2][streetlevel-2][z][0]=22;
					worldgrid[x+2][streetlevel-2][z][1]=1;
					worldgrid[x+5][streetlevel-3][z][0]=22;
					worldgrid[x+5][streetlevel-3][z][1]=1;
					worldgrid[x+7][streetlevel-3][z][0]=17;
					worldgrid[x+7][streetlevel-3][z][1]=1;
					worldgrid[x+8][streetlevel-3][z][0]=18;
					//placeholders
					worldgrid[x+3][streetlevel-3][z][0]=1;
					worldgrid[x+4][streetlevel-3][z][0]=1;
					worldgrid[x+6][streetlevel-3][z][0]=1;
					worldgrid[x+3][streetlevel-3][z-1][0]=1;
					worldgrid[x+4][streetlevel-3][z-1][0]=1;
					worldgrid[x+5][streetlevel-3][z-1][0]=1;
					worldgrid[x+6][streetlevel-3][z-1][0]=1;
					worldgrid[x+6][streetlevel-3][z-1][0]=1;
					worldgrid[x+7][streetlevel-3][z-1][0]=1;
					worldgrid[x+3][streetlevel-3][z+1][0]=1;
					worldgrid[x+4][streetlevel-3][z+1][0]=1;
					worldgrid[x+5][streetlevel-3][z+1][0]=1;
					worldgrid[x+6][streetlevel-3][z+1][0]=1;
					worldgrid[x+7][streetlevel-3][z+1][0]=1;
				}
			}
			if(worldgrid[x][streetlevel-1][z][1]==3){
				bool emptyspace=1;
				for(int a=0; a<5; a++)for(int b=0; b<6; b++)if(a>0 || b>0)
					if(worldgrid[x][streetlevel-1-a][z-b][0])emptyspace=0;
				for(int a=0; a<7; a++)for(int b=0; b<7; b++)
					if(worldgrid[x-3+a][streetlevel-3][z-3+b-7][0])emptyspace=0;
				if(emptyspace){
					worldgrid[x][streetlevel-1][z][0]=21;
					worldgrid[x][streetlevel-2][z-2][0]=22;
					worldgrid[x][streetlevel-2][z-2][1]=2;
					worldgrid[x][streetlevel-3][z-5][0]=22;
					worldgrid[x][streetlevel-3][z-5][1]=2;
					worldgrid[x][streetlevel-3][z-7][0]=17;
					worldgrid[x][streetlevel-3][z-7][1]=2;
					worldgrid[x][streetlevel-3][z-8][0]=18;
					//placeholders
					worldgrid[x][streetlevel-3][z-3][0]=1;
					worldgrid[x][streetlevel-3][z-4][0]=1;
					worldgrid[x][streetlevel-3][z-6][0]=1;
					worldgrid[x-1][streetlevel-3][z-3][0]=1;
					worldgrid[x-1][streetlevel-3][z-4][0]=1;
					worldgrid[x-1][streetlevel-3][z-5][0]=1;
					worldgrid[x-1][streetlevel-3][z-6][0]=1;
					worldgrid[x-1][streetlevel-3][z-7][0]=1;
					worldgrid[x+1][streetlevel-3][z-3][0]=1;
					worldgrid[x+1][streetlevel-3][z-4][0]=1;
					worldgrid[x+1][streetlevel-3][z-5][0]=1;
					worldgrid[x+1][streetlevel-3][z-6][0]=1;
					worldgrid[x+1][streetlevel-3][z-7][0]=1;
				}
			}
			if(worldgrid[x][streetlevel-1][z][1]==1){
				bool emptyspace=1;
				for(int a=0; a<5; a++)for(int b=0; b<6; b++)if(a>0 || b>0)
					if(worldgrid[x][streetlevel-1-a][z+b][0])emptyspace=0;
				for(int a=0; a<7; a++)for(int b=0; b<7; b++)
					if(worldgrid[x-3+a][streetlevel-3][z-3+b+7][0])emptyspace=0;
				if(emptyspace){
					worldgrid[x][streetlevel-1][z][0]=21;
					worldgrid[x][streetlevel-2][z+2][0]=22;
					worldgrid[x][streetlevel-2][z+2][1]=0;
					worldgrid[x][streetlevel-3][z+5][0]=22;
					worldgrid[x][streetlevel-3][z+5][1]=0;
					worldgrid[x][streetlevel-3][z+7][0]=17;
					worldgrid[x][streetlevel-3][z+7][1]=0;
					worldgrid[x][streetlevel-3][z+8][0]=18;
					//placeholders
					worldgrid[x][streetlevel-3][z+3][0]=1;
					worldgrid[x][streetlevel-3][z+4][0]=1;
					worldgrid[x][streetlevel-3][z+6][0]=1;
					worldgrid[x-1][streetlevel-3][z+3][0]=1;
					worldgrid[x-1][streetlevel-3][z+4][0]=1;
					worldgrid[x-1][streetlevel-3][z+5][0]=1;
					worldgrid[x-1][streetlevel-3][z+6][0]=1;
					worldgrid[x-1][streetlevel-3][z+7][0]=1;
					worldgrid[x+1][streetlevel-3][z+3][0]=1;
					worldgrid[x+1][streetlevel-3][z+4][0]=1;
					worldgrid[x+1][streetlevel-3][z+5][0]=1;
					worldgrid[x+1][streetlevel-3][z+6][0]=1;
					worldgrid[x+1][streetlevel-3][z+7][0]=1;
				}
			}
		}
	}

	//expand the catacombs
	for(int x=0; x<worldgridsizex; x++)
	for(int z=0; z<worldgridsizez; z++)
	if(worldgrid[x][streetlevel-3][z][0]==0)
		worldgrid[x][streetlevel-3][z][0]=18;

	//remove the placeholders
	for(int x=0; x<worldgridsizex; x++)
	for(int z=0; z<worldgridsizez; z++)
	if(worldgrid[x][streetlevel-3][z][0]==1)
		worldgrid[x][streetlevel-3][z][0]=0;

	//create walls max lengths and with or without empty centers
	for(int n=0; n<(float)worldgridsizex*(float)worldgridsizez*0.075; n++){
		int startx,startz,x,z;
		//horizontal line
		startx=rand()%(worldgridsizex-2)+1;
		startz=rand()%(worldgridsizez-2)+1;
		if(worldgrid[startx][streetlevel-3][startz][0]==18
		&& worldgrid[startx][streetlevel-3][startz-1][0]==18
		&& worldgrid[startx][streetlevel-3][startz+1][0]==18){
			if(rand()%2==0)
				worldgrid[startx][streetlevel-3][startz][0]=18;
			else
				worldgrid[startx][streetlevel-3][startz][0]=0;
			x=startx;z=startz;
			int length=0;
			while(worldgrid[x-1][streetlevel-3][z][0]==18 && length<6){
				x--;length++;worldgrid[x][streetlevel-3][z][0]=0;}
			x=startx;z=startz;
			while(worldgrid[x+1][streetlevel-3][z][0]==18 && length<6){
				x++;length++;worldgrid[x][streetlevel-3][z][0]=0;}
		}
		//verticle line
		startx=rand()%(worldgridsizex-2)+1;
		startz=rand()%(worldgridsizez-2)+1;
		if(worldgrid[startx][streetlevel-3][startz][0]==18
		&& worldgrid[startx-1][streetlevel-3][startz][0]==18
		&& worldgrid[startx+1][streetlevel-3][startz][0]==18){
			if(rand()%2==0)
				worldgrid[startx][streetlevel-3][startz][0]=18;
			else
				worldgrid[startx][streetlevel-3][startz][0]=0;
			x=startx;z=startz;
			int length=0;
			while(worldgrid[x][streetlevel-3][z-1][0]==18 && length<6){
				z--;length++;worldgrid[x][streetlevel-3][z][0]=0;}
			x=startx;z=startz;
			while(worldgrid[x][streetlevel-3][z+1][0]==18 && length<6){
				z++;length++;worldgrid[x][streetlevel-3][z][0]=0;}
		}
	}

	//always have a piece of ground infront of a door
	for(int x=0; x<worldgridsizex; x++)
	for(int z=0; z<worldgridsizez; z++)
	if(worldgrid[x][streetlevel-3][z][0]==17){
		if(worldgrid[x][streetlevel-3][z][1]==3)
			worldgrid[x-1][streetlevel-3][z][0]=18;
		if(worldgrid[x][streetlevel-3][z][1]==1)
			worldgrid[x+1][streetlevel-3][z][0]=18;
		if(worldgrid[x][streetlevel-3][z][1]==2)
			worldgrid[x][streetlevel-3][z-1][0]=18;
		if(worldgrid[x][streetlevel-3][z][1]==0)
			worldgrid[x][streetlevel-3][z+1][0]=18;
	}

	//always have walls preventing the catacombs from reaching the edges of the game world
	for(int x=0; x<worldgridsizex; x++)
	for(int z=0; z<worldgridsizez; z++)
	if(x==0 || x==worldgridsizex-1
	|| z==0 || z==worldgridsizez-1
	|| x==1 || x==worldgridsizex-2
	|| z==1 || z==worldgridsizez-2
	|| x==2 || x==worldgridsizex-3
	|| z==2 || z==worldgridsizez-3){
		worldgrid[x][streetlevel-3][z][0]=0;
	}

	//remove blocked off sections of the catacombs
	bool catacombgrid[worldgridsizex][worldgridsizez];
	for(int x=0; x<worldgridsizex; x++)
	for(int z=0; z<worldgridsizez; z++)
	if(worldgrid[x][streetlevel-3][z][0]==17){
		catacombgrid[x][z]=1;
	}else{
		catacombgrid[x][z]=0;
	}
	for(int x=1; x<worldgridsizex-1; x++)
	for(int z=1; z<worldgridsizez-1; z++)
	if(worldgrid[x][streetlevel-3][z][0]==18)
	if(catacombgrid[x][z]==0)
	if(catacombgrid[x-1][z]==1 || catacombgrid[x+1][z]==1
	|| catacombgrid[x][z-1]==1 || catacombgrid[x][z+1]==1){
		catacombgrid[x][z]=1;
		x=0;z=0;
	}
	for(int x=0; x<worldgridsizex; x++)
	for(int z=0; z<worldgridsizez; z++)
	if(catacombgrid[x][z]==0 && worldgrid[x][streetlevel-3][z][0]!=22){
		worldgrid[x][streetlevel-3][z][0]=0;
	}

	//catacomb walls
	for(int x=1; x<worldgridsizex-1; x++)
	for(int z=1; z<worldgridsizez-1; z++)
	if(worldgrid[x][streetlevel-3][z][0]==0){
		int sidecount=0;
		if(worldgrid[x-1][streetlevel-3][z][0]==18)sidecount+=1;
		if(worldgrid[x+1][streetlevel-3][z][0]==18)sidecount+=1;
		if(worldgrid[x][streetlevel-3][z-1][0]==18)sidecount+=1;
		if(worldgrid[x][streetlevel-3][z+1][0]==18)sidecount+=1;
		if(worldgrid[x-1][streetlevel-3][z-1][0]==18
		|| worldgrid[x-1][streetlevel-3][z+1][0]==18
		|| worldgrid[x+1][streetlevel-3][z-1][0]==18
		|| worldgrid[x+1][streetlevel-3][z+1][0]==18){
			if(worldgrid[x-1][streetlevel-3][z][0]==17)sidecount=4;
			if(worldgrid[x+1][streetlevel-3][z][0]==17)sidecount=4;
			if(worldgrid[x][streetlevel-3][z-1][0]==17)sidecount=4;
			if(worldgrid[x][streetlevel-3][z+1][0]==17)sidecount=4;
		}
		if(sidecount==1){
			worldgrid[x][streetlevel-3][z][0]=6;
			if(worldgrid[x-1][streetlevel-3][z][0]==18)
				worldgrid[x][streetlevel-3][z][1]=3;
			if(worldgrid[x+1][streetlevel-3][z][0]==18)
				worldgrid[x][streetlevel-3][z][1]=1;
			if(worldgrid[x][streetlevel-3][z-1][0]==18)
				worldgrid[x][streetlevel-3][z][1]=2;
			if(worldgrid[x][streetlevel-3][z+1][0]==18)
				worldgrid[x][streetlevel-3][z][1]=0;
		}
		if(sidecount==2){
			worldgrid[x][streetlevel-3][z][0]=30;
			if(worldgrid[x-1][streetlevel-3][z][0]==18
			&& worldgrid[x+1][streetlevel-3][z][0]==18){
				worldgrid[x][streetlevel-3][z][1]=1;
			}else if(worldgrid[x][streetlevel-3][z-1][0]==18
			&& worldgrid[x][streetlevel-3][z+1][0]==18){
				worldgrid[x][streetlevel-3][z][1]=0;
			}else{
				sidecount=4;
			}
		}
		if(sidecount>2){
			worldgrid[x][streetlevel-3][z][0]=19;
		}
	}

	//tunnels
	for(int n=0; n<(float)worldgridsizex*(float)worldgridsizez*1.5; n++){
		int x=rand()%(worldgridsizex-2)+1;
		int z=rand()%(worldgridsizez-2)+1;
		if(worldgrid[x][streetlevel-3][z][0]==19
		&& worldgrid[x+1][streetlevel-3][z][0]==19
		&& worldgrid[x-1][streetlevel-3][z][0]==19
		&& worldgrid[x][streetlevel-3][z+1][0]==18
		&& worldgrid[x][streetlevel-3][z-1][0]==18){
			worldgrid[x][streetlevel-3][z][0]=15;
			worldgrid[x][streetlevel-3][z][1]=0;
		}
		if(worldgrid[x][streetlevel-3][z][0]==19
		&& worldgrid[x][streetlevel-3][z+1][0]==19
		&& worldgrid[x][streetlevel-3][z-1][0]==19
		&& worldgrid[x+1][streetlevel-3][z][0]==18
		&& worldgrid[x-1][streetlevel-3][z][0]==18){
			worldgrid[x][streetlevel-3][z][0]=15;
			worldgrid[x][streetlevel-3][z][1]=1;
		}
	}

	//add catacomb pillars
	for(int x=0; x<worldgridsizex; x++)
	for(int z=0; z<worldgridsizez; z++){
		//if(x%2 && z%2)
		if(worldgrid[x][streetlevel-3][z][0]==18)
		if(worldgrid[x-1][streetlevel-3][z][0]==18)
		if(worldgrid[x+1][streetlevel-3][z][0]==18)
		if(worldgrid[x][streetlevel-3][z-1][0]==18)
		if(worldgrid[x][streetlevel-3][z+1][0]==18)
		if(worldgrid[x-1][streetlevel-3][z-1][0]==18)
		if(worldgrid[x-1][streetlevel-3][z+1][0]==18)
		if(worldgrid[x+1][streetlevel-3][z-1][0]==18)
		if(worldgrid[x+1][streetlevel-3][z+1][0]==18)
		worldgrid[x][streetlevel-3][z][0]=16;
	}

}

//skywalks
void genworldgrid_part5(){

	//skywalks
	for(int y=streetlevel+2; y<streetlevel+9; y++)
	for(int n=0; n<(float)worldgridsizex*(float)worldgridsizez*0.35; n++){
		int startx=rand()%(worldgridsizex-2)+1;
		int startz=rand()%(worldgridsizez-2)+1;
		int x=startx;
		int z=startz;
		int length=0;
		if(worldgrid[x][y][z][0]==3 || worldgrid[x][y][z][0]==4){
			//check if its a good idea
			bool keepgoing=1;
			bool doit=0;
			if(worldgrid[x][y][z][1]==0)while(keepgoing){x-=1;
				if(worldgrid[x][y][z][0]==0){
					length+=1;
					if(length>12 || x<=0)keepgoing=0;
				}else{keepgoing=0;}
			}
			if(worldgrid[x][y][z][1]==3)while(keepgoing){z-=1;
				if(worldgrid[x][y][z][0]==0){
					length+=1;
					if(length>12 || z<=0)keepgoing=0;
				}else{keepgoing=0;}
			}
			if(worldgrid[x][y][z][0]==3 || worldgrid[x][y][z][0]==4)doit=1;
			if(x==startx && z==startz)doit=0;
			//then do it if it is
			if(doit==1){
				x=startx;
				z=startz;
				if(length==1){
					worldgrid[x][y][z][0]=0;
					if(worldgrid[x][y][z][1]==0){
						x-=1;
						worldgrid[x][y][z][0]=31;
						worldgrid[x][y][z][1]=0;
						x-=1;
					}
					if(worldgrid[x][y][z][1]==3){
						z-=1;
						worldgrid[x][y][z][0]=31;
						worldgrid[x][y][z][1]=1;
						z-=1;
					}
					worldgrid[x][y][z][0]=0;
				}else{
					worldgrid[x][y][z][0]=36;
					if(worldgrid[x][y][z][1]==0){
						for(int b=0; b<length; b++){x-=1;
						worldgrid[x][y][z][0]=37;
						worldgrid[x][y][z][1]=0;
						}x-=1;
					}
					if(worldgrid[x][y][z][1]==3){
						for(int b=0; b<length; b++){z-=1;
						worldgrid[x][y][z][0]=37;
						worldgrid[x][y][z][1]=1;
						}z-=1;
					}
					worldgrid[x][y][z][0]=36;
				}
			}
		}
	}

}

//doors and elevators
void genworldgrid_part6(){

	bool buildinggrid[worldgridsizex][worldgridsizez];

	//doors
	for(int x=0; x<worldgridsizex; x++)
	for(int z=0; z<worldgridsizez; z++){
		if(worldgrid[x][streetlevel][z][0]==27){
			buildinggrid[x][z]=1;
		}else{
			buildinggrid[x][z]=0;
		}
	}
	for(int x=0; x<worldgridsizex; x++)
	for(int z=0; z<worldgridsizez; z++){
		if(buildinggrid[x][z]){
			//remember the starting position
			int startx=x;
			int startz=z;
			//get the size of the building
			int buildingxsize=0;
			int buildingzsize=0;
			while(worldgrid[x][streetlevel][z][0]==27){
				x++;buildingxsize++;}
			x=startx;
			while(worldgrid[x][streetlevel][z][0]==27){
				z++;buildingzsize++;}
			//clear out the building from the grid
			for(x=startx; x<startx+buildingxsize+1; x++)
			for(z=startz; z<startz+buildingzsize+1; z++)buildinggrid[x][z]=0;
			//choose a random position inside the building
			int middlex=startx+rand()%buildingxsize;
			int middlez=startz+rand()%buildingzsize;
			//place the door(s) facing the street
			int doorcount=0;
			if(worldgrid[startx-3][streetlevel][middlez][0]==10){
				worldgrid[startx-1][streetlevel][middlez][0]=26;
				doorcount++;}
			if(worldgrid[startx+buildingxsize+2][streetlevel][middlez][0]==10){
				worldgrid[startx+buildingxsize][streetlevel][middlez][0]=26;
				doorcount++;}
			if(worldgrid[middlex][streetlevel][startz-3][0]==10){
				worldgrid[middlex][streetlevel][startz-1][0]=26;
				doorcount++;}
			if(worldgrid[middlex][streetlevel][startz+buildingzsize+2][0]==10){
				worldgrid[middlex][streetlevel][startz+buildingzsize][0]=26;
				doorcount++;}
			//choose a random position inside the building
			middlex=startx+rand()%buildingxsize;
			middlez=startz+rand()%buildingzsize;
			//place the door(s) facing anywhere
			if(doorcount==0 || rand()%5==0){
				worldgrid[startx-1][streetlevel][middlez][0]=26;
				doorcount++;}
			if(doorcount==0 || rand()%5==0){
				worldgrid[startx+buildingxsize][streetlevel][middlez][0]=26;
				doorcount++;}
			if(doorcount==0 || rand()%5==0){
				worldgrid[middlex][streetlevel][startz-1][0]=26;
				doorcount++;}
			if(doorcount==0 || rand()%5==0){
				worldgrid[middlex][streetlevel][startz+buildingzsize][0]=26;
				doorcount++;}
			//reset the position
			x=startx;
			z=startz;
		}
	}

	//elevators
	for(int x=0; x<worldgridsizex; x++)
	for(int z=0; z<worldgridsizez; z++){
		if(worldgrid[x][streetlevel][z][0]==27){
			buildinggrid[x][z]=1;
		}else{
			buildinggrid[x][z]=0;
		}
	}
	for(int x=0; x<worldgridsizex; x++)
	for(int z=0; z<worldgridsizez; z++){
		if(buildinggrid[x][z]){
			//remember the starting position
			int startx=x;
			int startz=z;
			//get the size of the building
			int buildingxsize=0;
			int buildingzsize=0;
			while(worldgrid[x][streetlevel][z][0]==27){
				x++;buildingxsize++;}
			x=startx;
			while(worldgrid[x][streetlevel][z][0]==27){
				z++;buildingzsize++;}
			//clear out the building from the grid
			for(x=startx; x<startx+buildingxsize+1; x++)
			for(z=startz; z<startz+buildingzsize+1; z++)buildinggrid[x][z]=0;
			//choose a random position inside the building
			x=startx+rand()%buildingxsize;
			z=startz+rand()%buildingzsize;
			//place the elevator
			int y=streetlevel;
			int direction=rand()%4;
			worldgrid[x][y][z][0]=32;
			worldgrid[x][y][z][1]=direction;
			worldgrid[x][y+1][z][0]=34;
			worldgrid[x][y+1][z][1]=direction;
			while(worldgrid[x][y+2][z][0]==27 || worldgrid[x][y+2][z][0]==5){
				worldgrid[x][y+1][z][0]=33;
				worldgrid[x][y+2][z][0]=34;
				worldgrid[x][y+2][z][1]=direction;
				y++;
			}
			//reset the position
			x=startx;
			z=startz;
		}
	}

}

//everything else
void genworldgrid_part7(){

	//remove the top layer of water
	for(int x=0; x<worldgridsizex; x++)
	for(int z=0; z<worldgridsizez; z++)
	if(worldgrid[x][streetlevel][z][0]==20)worldgrid[x][streetlevel][z][0]=0;

	//water walls
	for(int x=1; x<worldgridsizex-1; x++)
	for(int z=1; z<worldgridsizez-1; z++)
	if(worldgrid[x][streetlevel-1][z][0]==20){
		if(worldgrid[x-1][streetlevel][z][0]==8){
			worldgrid[x][streetlevel-1][z][0]=35;
			worldgrid[x][streetlevel-1][z][1]=0;
		}
		if(worldgrid[x+1][streetlevel][z][0]==8){
			worldgrid[x][streetlevel-1][z][0]=35;
			worldgrid[x][streetlevel-1][z][1]=2;
		}
		if(worldgrid[x][streetlevel][z-1][0]==8){
			worldgrid[x][streetlevel-1][z][0]=35;
			worldgrid[x][streetlevel-1][z][1]=3;
		}
		if(worldgrid[x][streetlevel][z+1][0]==8){
			worldgrid[x][streetlevel-1][z][0]=35;
			worldgrid[x][streetlevel-1][z][1]=1;
		}
		if(worldgrid[x-1][streetlevel][z][0]==8
		&& worldgrid[x][streetlevel][z+1][0]==8){
			worldgrid[x][streetlevel-1][z][0]=38;
			worldgrid[x][streetlevel-1][z][1]=0;
		}
		if(worldgrid[x+1][streetlevel][z][0]==8
		&& worldgrid[x][streetlevel][z-1][0]==8){
			worldgrid[x][streetlevel-1][z][0]=38;
			worldgrid[x][streetlevel-1][z][1]=2;
		}
		if(worldgrid[x-1][streetlevel][z][0]==8
		&& worldgrid[x][streetlevel][z-1][0]==8){
			worldgrid[x][streetlevel-1][z][0]=38;
			worldgrid[x][streetlevel-1][z][1]=3;
		}
		if(worldgrid[x+1][streetlevel][z][0]==8
		&& worldgrid[x][streetlevel][z+1][0]==8){
			worldgrid[x][streetlevel-1][z][0]=38;
			worldgrid[x][streetlevel-1][z][1]=1;
		}
	}

	//building stairs to roof
	for(int x=2; x<worldgridsizex-2; x++)
	for(int y=1; y<worldgridsizey-1; y++)
	for(int z=2; z<worldgridsizez-2; z++)
	if(worldgrid[x][y+0][z][0]==5
	&& worldgrid[x][y+1][z][0]==0){
		bool doit=1;
		for(int x2=x-2; x2<x+3; x2++)
		for(int z2=z-2; z2<z+3; z2++){if(worldgrid[x2][y][z2][0]==34)doit=0;}
		for(int x2=x-3; x2<x+4; x2++)
		for(int z2=z-3; z2<z+4; z2++){if(worldgrid[x2][y][z2][0]==40)doit=0;}
		if(doit==1){
			if(worldgrid[x+0][y+0][z+1][0]==5
			&& worldgrid[x+0][y+1][z+1][0]==0
			&& worldgrid[x+0][y+1][z+2][0]==0){
				worldgrid[x+0][y][z+0][0]=40;
				worldgrid[x+0][y][z+0][1]=0;
				worldgrid[x+0][y][z+1][0]=0;
			}else
			if(worldgrid[x+1][y+0][z+0][0]==5
			&& worldgrid[x+1][y+1][z+0][0]==0
			&& worldgrid[x+2][y+1][z+0][0]==0){
				worldgrid[x+0][y][z+0][0]=40;
				worldgrid[x+0][y][z+0][1]=1;
				worldgrid[x+1][y][z+0][0]=0;
			}else
			if(worldgrid[x+0][y+0][z-1][0]==5
			&& worldgrid[x+0][y+1][z-1][0]==0
			&& worldgrid[x+0][y+1][z-2][0]==0){
				worldgrid[x+0][y][z+0][0]=40;
				worldgrid[x+0][y][z+0][1]=2;
				worldgrid[x+0][y][z-1][0]=0;
			}else
			if(worldgrid[x-1][y+0][z+0][0]==5
			&& worldgrid[x-1][y+1][z+0][0]==0
			&& worldgrid[x-2][y+1][z+0][0]==0){
				worldgrid[x+0][y][z+0][0]=40;
				worldgrid[x+0][y][z+0][1]=3;
				worldgrid[x-1][y][z+0][0]=0;
			}
		}
	}

	//billboards and signs
	for(int y=streetlevel+1; y<streetlevel+7; y++)
	for(int n=0; n<(float)worldgridsizex*(float)worldgridsizez*0.95; n++){
		int x=rand()%(worldgridsizex-2)+1;
		int z=rand()%(worldgridsizez-2)+1;
		if(worldgrid[x][y][z][0]==4){
			if(worldgrid[x+0][y+1][z+0][0]==0
			&& worldgrid[x+1][y+1][z+0][0]==0
			&& worldgrid[x-1][y+1][z+0][0]==0
			&& worldgrid[x+0][y+1][z+1][0]==0
			&& worldgrid[x+0][y+1][z-1][0]==0
			&& worldgrid[x+0][y+2][z+0][0]==0
			&& worldgrid[x+1][y+2][z+0][0]==0
			&& worldgrid[x-1][y+2][z+0][0]==0
			&& worldgrid[x+0][y+2][z+1][0]==0
			&& worldgrid[x+0][y+2][z-1][0]==0){
				worldgrid[x+0][y+1][z+0][0]=45;
				worldgrid[x+0][y+1][z+0][1]=worldgrid[x][y][z][1];
			}
		}
	}
	for(int y=streetlevel+1; y<streetlevel+6; y++)
	for(int n=0; n<(float)worldgridsizex*(float)worldgridsizez*0.8; n++){
		int x=rand()%(worldgridsizex-2)+1;
		int z=rand()%(worldgridsizez-2)+1;
		if(worldgrid[x][y][z][0]==4){
			int signtoplace=41+rand()%4;
			bool placed=0;
			bool doit=1;
			if(signtoplace==44){
				if(worldgrid[x][y][z][1]==0){
					if(worldgrid[x-1][y+0][z+2][0]==44
					|| worldgrid[x-1][y+0][z-2][0]==44)doit=0;
				}
				if(doit && worldgrid[x][y][z][1]==1){
					if(worldgrid[x+2][y+0][z+1][0]==44
					|| worldgrid[x-2][y+0][z+1][0]==44)doit=0;
				}
				if(worldgrid[x][y][z][1]==2){
					if(worldgrid[x+1][y+0][z+2][0]==44
					|| worldgrid[x+1][y+0][z-2][0]==44)doit=0;
				}
				if(doit && worldgrid[x][y][z][1]==3){
					if(worldgrid[x+2][y+0][z-1][0]==44
					|| worldgrid[x-2][y+0][z-1][0]==44)doit=0;
				}
			}
			if(doit && worldgrid[x][y][z][1]==0){
				if(worldgrid[x-1][y+0][z+0][0]==0
				&& worldgrid[x-1][y+0][z+1][0]==0
				&& worldgrid[x-1][y+0][z-1][0]==0
				&& worldgrid[x-1][y+1][z+0][0]==0
				&& worldgrid[x-1][y+1][z+1][0]==0
				&& worldgrid[x-1][y+1][z-1][0]==0
				&& worldgrid[x-1][y-1][z+0][0]==0
				&& worldgrid[x-1][y-1][z+1][0]==0
				&& worldgrid[x-1][y-1][z-1][0]==0){placed=1;
					worldgrid[x-1][y][z][0]=signtoplace;
					worldgrid[x-1][y][z][1]=worldgrid[x][y][z][1];
				}
			}
			if(doit && worldgrid[x][y][z][1]==1){
				if(worldgrid[x+0][y+0][z+1][0]==0
				&& worldgrid[x+1][y+0][z+1][0]==0
				&& worldgrid[x-1][y+0][z+1][0]==0
				&& worldgrid[x+0][y+1][z+1][0]==0
				&& worldgrid[x+1][y+1][z+1][0]==0
				&& worldgrid[x-1][y+1][z+1][0]==0
				&& worldgrid[x+0][y-1][z+1][0]==0
				&& worldgrid[x+1][y-1][z+1][0]==0
				&& worldgrid[x-1][y-1][z+1][0]==0){placed=1;
					worldgrid[x][y][z+1][0]=signtoplace;
					worldgrid[x][y][z+1][1]=worldgrid[x][y][z][1];
				}
			}
			if(doit && worldgrid[x][y][z][1]==2){
				if(worldgrid[x+1][y+0][z+0][0]==0
				&& worldgrid[x+1][y+0][z+1][0]==0
				&& worldgrid[x+1][y+0][z-1][0]==0
				&& worldgrid[x+1][y+1][z+0][0]==0
				&& worldgrid[x+1][y+1][z+1][0]==0
				&& worldgrid[x+1][y+1][z-1][0]==0
				&& worldgrid[x+1][y-1][z+0][0]==0
				&& worldgrid[x+1][y-1][z+1][0]==0
				&& worldgrid[x+1][y-1][z-1][0]==0){placed=1;
					worldgrid[x+1][y][z][0]=signtoplace;
					worldgrid[x+1][y][z][1]=worldgrid[x][y][z][1];
				}
			}
			if(doit && worldgrid[x][y][z][1]==3){
				if(worldgrid[x+0][y+0][z-1][0]==0
				&& worldgrid[x+1][y+0][z-1][0]==0
				&& worldgrid[x-1][y+0][z-1][0]==0
				&& worldgrid[x+0][y+1][z-1][0]==0
				&& worldgrid[x+1][y+1][z-1][0]==0
				&& worldgrid[x-1][y+1][z-1][0]==0
				&& worldgrid[x+0][y-1][z-1][0]==0
				&& worldgrid[x+1][y-1][z-1][0]==0
				&& worldgrid[x-1][y-1][z-1][0]==0){placed=1;
					worldgrid[x][y][z-1][0]=signtoplace;
					worldgrid[x][y][z-1][1]=worldgrid[x][y][z][1];
				}
			}
			if(placed==1){
				worldgrid[x][y][z][0]=3;
				if(signtoplace==44){
					if(worldgrid[x+1][y][z][0]==4)worldgrid[x+1][y][z][0]=3;
					if(worldgrid[x-1][y][z][0]==4)worldgrid[x-1][y][z][0]=3;
					if(worldgrid[x][y][z+1][0]==4)worldgrid[x][y][z+1][0]=3;
					if(worldgrid[x][y][z-1][0]==4)worldgrid[x][y][z-1][0]=3;
				}
			}
		}
	}

	//zero sided sidewalks
	for(int x=0; x<worldgridsizex; x++)
	for(int z=0; z<worldgridsizez; z++)
	if(worldgrid[x][streetlevel][z][0]==8
	&& worldgrid[x-1][streetlevel][z][0]!=10
	&& worldgrid[x+1][streetlevel][z][0]!=10
	&& worldgrid[x][streetlevel][z-1][0]!=10
	&& worldgrid[x][streetlevel][z+1][0]!=10)worldgrid[x][streetlevel][z][0]=39;

	//middle of the street
	for(int x=0; x<worldgridsizex; x++)
	for(int z=0; z<worldgridsizez; z++)
	if(worldgrid[x][streetlevel][z][0]==10)
	if((worldgrid[x-2][streetlevel][z][0]==8 && worldgrid[x+2][streetlevel][z][0]==8)
	|| (worldgrid[x][streetlevel][z-2][0]==8 && worldgrid[x][streetlevel][z+2][0]==8))
		worldgrid[x][streetlevel][z][0]=7;

	//remove any placeholders
	for(int x=0; x<worldgridsizex; x++)
	for(int y=0; y<worldgridsizey; y++)
	for(int z=0; z<worldgridsizez; z++)
	if(worldgrid[x][y][z][0]==1)worldgrid[x][y][z][0]=0;

	//block the edges of the world
	for(int x=0; x<worldgridsizex; x++)
	for(int y=0; y<worldgridsizey; y++)
	for(int z=0; z<worldgridsizez; z++)
	if(x==0	|| x==worldgridsizex-1
			|| y==worldgridsizey-1
	|| z==0	|| z==worldgridsizez-1){
		worldgrid[x][y][z][0]=1;
		worldgrid[x][y][z][1]=0;
	}
	
}
*/