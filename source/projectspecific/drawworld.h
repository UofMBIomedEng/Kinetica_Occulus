	static const GLfloat g_vertex_buffer_data[] = { 
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f
	};

	// One color for each vertex. They were generated randomly.
	static const GLfloat g_color_buffer_data[] = { 
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f
	};

	GLuint vertexbuffer;
	GLuint colorbuffer;

void setupdraw()
{
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
}

extern double dyndist;
void drawworld(Eye LorR){
	//glUseProgram(program_object);
	//set the draw distance for clipping and fog


	float camnear=0.1f;
	float camfar=worldtilesize*worldtileviewrange;

	//get cam view range
	int lowxview=highint(0,playerxgridpos-worldtileviewrange);
	int highxview=lowint(worldgridsizex,playerxgridpos+worldtileviewrange+1);
	int lowyview=highint(0,playerygridpos-worldtileviewrange);
	int highyview=lowint(worldgridsizey,playerygridpos+worldtileviewrange+1);
	int lowzview=highint(0,playerzgridpos-worldtileviewrange);
	int highzview=lowint(worldgridsizez,playerzgridpos+worldtileviewrange+1);

	//setup the camera
	//set3dcamera(camxpos,camypos,camzpos,-camxang,camyang+90*radiansindegree,camzang,45,4/3); //screena);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//set3dcamera(playerxpos, playerypos, playerzpos, 0, nav_camyang, 0, 45, 4/3);
	float eyedist=dyndist/2;
	if(LorR==Left)
		set3dcamera(camxpos-(cos(camyang)*eyedist),camypos,camzpos-(sin(camyang)*eyedist),camxang,camyang,camzang,50,screena);
	else
		set3dcamera(camxpos+(cos(camyang)*eyedist),camypos,camzpos+(sin(camyang)*eyedist),camxang,camyang,camzang,50,screena);
	//prep for drawing
	if(usetextures==1)glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	SKYBOX_Render(camyang*degreesinradian,camxang*degreesinradian,camzang*degreesinradian);
    //turn on lighting

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat light_position0[] = {camxpos,camypos,camzpos,1.0};
	GLfloat light_ambient0[] = {1.0,1.0,1.0,1.0};
	GLfloat light_diffuse0[] = {1.0,1.0,1.0,1.0};
	GLfloat light_specular0[] = {1.0,1.0,1.0,1.0};
	glLightfv(GL_LIGHT0,GL_POSITION,light_position0);
	glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient0);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse0);
	glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular0);
//	glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION,0.005f);
	glEnableClientState(GL_NORMAL_ARRAY);

	/*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(-(playerxpos*10)+1, -playerypos, -playerzpos*10);
	glBegin(GL_TRIANGLES);
	glVertex3f( 0.0f, 1.5f,0.0f);
	glVertex3f(-1.0f,-1.0f,0.0f);
	glVertex3f( 1.0f,-1.0f,0.0f);
	glEnd();*/

	//draw the world tiles
	for(int x=lowxview; x<highxview; x++)
		for(int y=lowyview; y<highyview; y++)
			for(int z=lowzview; z<highzview; z++){
				int b=worldgrid[x][y][z][0];
				if(b>0){
					int c=worldgrid[x][y][z][1];
					glPushMatrix();
					glBindTexture(GL_TEXTURE_2D,worldtiletexture[b]);
					glTranslatef(x*worldtilesize,y*worldtilesize,z*worldtilesize);	
					draw3dtrianglemesh(worldtilevertexcount[b],	worldtilevertexarray[b][c],worldtiletexturearray[b],NULL,worldtilenormalarray[b][c]);
					glPopMatrix();
				}
			}

	//done drawing
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	

	//turn off lighting
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

	//turn off fog
	glDisable(GL_FOG);

}

void drawworld_backup(){
	//glUseProgram(program_object);
	//set the draw distance for clipping and fog
	float camnear=0.1f;
	float camfar=worldtilesize*worldtileviewrange;

	//get cam view range
	int lowxview=highint(0,playerxgridpos-worldtileviewrange);
	int highxview=lowint(worldgridsizex,playerxgridpos+worldtileviewrange+1);
	int lowyview=highint(0,playerygridpos-worldtileviewrange);
	int highyview=lowint(worldgridsizey,playerygridpos+worldtileviewrange+1);
	int lowzview=highint(0,playerzgridpos-worldtileviewrange);
	int highzview=lowint(worldgridsizez,playerzgridpos+worldtileviewrange+1);

	//setup the camera
	set3dcamera(camxpos,camypos,camzpos,-camxang,camyang+90*radiansindegree,camzang,50,screena);
	
	//prep for drawing
	if(usetextures==1)glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    SKYBOX_Render(camyang*degreesinradian,-camxang*degreesinradian,camzang*degreesinradian);
    //turn on lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat light_position0[] = {camxpos,camypos,camzpos,1.0};
	GLfloat light_ambient0[] = {1.0,1.0,1.0,1.0};
	GLfloat light_diffuse0[] = {1.0,1.0,1.0,1.0};
	GLfloat light_specular0[] = {1.0,1.0,1.0,1.0};
	glLightfv(GL_LIGHT0,GL_POSITION,light_position0);
	glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient0);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse0);
	glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular0);
//	glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION,0.005f);
	glEnableClientState(GL_NORMAL_ARRAY);

/*
	//turn on fog
	GLfloat fogColor[4]= {fog_color[0],fog_color[1],fog_color[2],fog_color[3]};             //fog color
	glFogi(GL_FOG_MODE,GL_LINEAR);
	glFogfv(GL_FOG_COLOR,fogColor);
	glFogf(GL_FOG_DENSITY,0.25f);
	glHint(GL_FOG_HINT,GL_DONT_CARE);
	glFogf(GL_FOG_START,0.1f);
	glFogf(GL_FOG_END,worldtilesize*worldtileviewrange);
	glEnable(GL_FOG);
	*/

	//SKYBOX_Render(camyang*degreesinradian,camxang*degreesinradian);

	//draw the world tiles
	for(int x=lowxview; x<highxview; x++)
		for(int y=lowyview; y<highyview; y++)
			for(int z=lowzview; z<highzview; z++){
				int b=worldgrid[x][y][z][0];
				if(b>0){
					int c=worldgrid[x][y][z][1];
					glPushMatrix();
					glBindTexture(GL_TEXTURE_2D,worldtiletexture[b]);
					glTranslatef(x*worldtilesize,y*worldtilesize,z*worldtilesize);	
					draw3dtrianglemesh(worldtilevertexcount[b],	worldtilevertexarray[b][c],worldtiletexturearray[b],NULL,worldtilenormalarray[b][c]);
					glPopMatrix();
				}
			}

	//done drawing
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);

//	SKYBOX_Finalize();
	
	//turn off lighting
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

	//turn off fog
	glDisable(GL_FOG);

}
