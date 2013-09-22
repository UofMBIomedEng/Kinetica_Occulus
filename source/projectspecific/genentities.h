void genentities(){

	//clear the entities lists
	for(int x=0; x<worldgridsizex; x++)
	for(int y=0; y<worldgridsizey; y++)
	for(int z=0; z<worldgridsizez; z++)
		entitycount[x][y][z]=0;
	for(int x=0; x<worldgridsizex; x++)
	for(int y=0; y<worldgridsizey; y++)
	for(int z=0; z<worldgridsizez; z++)
	for(int a=0; a<maxentities; a++)
		entitylist[x][y][z][a]=NULL;
	
	//place collectables
	int count=0;
	while(count<1000){
		int x=rand()%(worldgridsizex-2)+1;
		int y=rand()%(worldgridsizey-1);
		int z=rand()%(worldgridsizez-2)+1;
		if(worldgrid[x][y][z][0]==3
		|| worldgrid[x][y][z][0]==4
		|| worldgrid[x][y][z][0]==5
		|| worldgrid[x][y][z][0]==7
		|| worldgrid[x][y][z][0]==8
		|| worldgrid[x][y][z][0]==9
		|| worldgrid[x][y][z][0]==10
		|| worldgrid[x][y][z][0]==11
		|| worldgrid[x][y][z][0]==13
		|| worldgrid[x][y][z][0]==16
		|| worldgrid[x][y][z][0]==17
		|| worldgrid[x][y][z][0]==18
		|| worldgrid[x][y][z][0]==27
		|| (y>0 && worldgrid[x][y-1][z][0]==5))
		if(entitycount[x][y][z]==0){
			entitylist[x][y][z][(int)entitycount[x][y][z]] = new entity;
			entitylist[x][y][z][(int)entitycount[x][y][z]]->type = entitytype_disccartridge;
			entitylist[x][y][z][(int)entitycount[x][y][z]]->xpos = x*worldtilesize;
			entitylist[x][y][z][(int)entitycount[x][y][z]]->ypos = y*worldtilesize-worldtilesize*0.3f;
			entitylist[x][y][z][(int)entitycount[x][y][z]]->zpos = z*worldtilesize;
			entitylist[x][y][z][(int)entitycount[x][y][z]]->yang = (float)(rand()%1000);
			entitylist[x][y][z][(int)entitycount[x][y][z]]->yangmov = 0.05f;
			entitycount[x][y][z]+=1;
			count++;
		}
	}
	//place elevators
	for(int x=0; x<worldgridsizex; x++)
	for(int y=0; y<worldgridsizey; y++)
	for(int z=0; z<worldgridsizez; z++){
		if(worldgrid[x][y][z][0]==32)
		if(entitycount[x][y][z]<maxentities){
			entitylist[x][y][z][(int)entitycount[x][y][z]] = new entity;
			entitylist[x][y][z][(int)entitycount[x][y][z]]->type = entitytype_elevator;
			entitylist[x][y][z][(int)entitycount[x][y][z]]->xpos = x*worldtilesize;
			entitylist[x][y][z][(int)entitycount[x][y][z]]->ypos = y*worldtilesize;
			entitylist[x][y][z][(int)entitycount[x][y][z]]->zpos = z*worldtilesize;
			entitylist[x][y][z][(int)entitycount[x][y][z]]->yang = 90.f*(float)worldgrid[x][y][z][1]*radiansindegree;
			entitylist[x][y][z][(int)entitycount[x][y][z]]->yposmov = 0.075f;
			entitycount[x][y][z]+=1;
		}
	}
	//place trashcans
	for(int n=0; n<(float)worldgridsizex*(float)worldgridsizez*0.075; n++){
		int x=rand()%worldgridsizex;
		int y=streetlevel;
		int z=rand()%worldgridsizez;
		if(worldgrid[x][y][z][0]==8
		|| worldgrid[x][y][z][0]==39)
		if(entitycount[x][y][z]<maxentities){
			entitylist[x][y][z][(int)entitycount[x][y][z]] = new entity;
			entitylist[x][y][z][(int)entitycount[x][y][z]]->type = entitytype_trashcan;
			entitylist[x][y][z][(int)entitycount[x][y][z]]->xpos = (float)(x*worldtilesize+(rand()%80)*0.1-4.0);
			entitylist[x][y][z][(int)entitycount[x][y][z]]->ypos = y*worldtilesize-4.0f;
			entitylist[x][y][z][(int)entitycount[x][y][z]]->zpos = (float)(z*worldtilesize+(rand()%80)*0.1-4.0);
			entitylist[x][y][z][(int)entitycount[x][y][z]]->yang = (float)(rand()%360)*radiansindegree;
			entitycount[x][y][z]+=1;
		}
	}
	
}
