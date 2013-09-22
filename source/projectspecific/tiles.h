const int worldtilecount=max_number_tile;
const float worldtilesize=10;

float *worldtilevertexarray[worldtilecount][4];
float *worldtiletexturearray[worldtilecount];
float *worldtilenormalarray[worldtilecount][4];
int worldtilevertexcount[worldtilecount];
collisionmesh *worldtilecollisionmesh[worldtilecount][4];

GLuint worldtiletexture[worldtilecount]; // added for the texture

void loadtiles(){

	//generic reusable char array for filenames
	char filename[256];

	// preparing
	dashprepdraw();
	dashdrawbutton(10,10,20,20,1);


	//init progress bar
	init_progressbar();

	//setup each tile
	for(int a=0; a<worldtilecount; a++){
		//get the file name
		sprintf_s(filename,"%s%i%s","Media/worldtiles/",a,".obj");
		//load the file
		loadobj((char*)filename,
			worldtilevertexarray[a][0],
			worldtiletexturearray[a],
			worldtilenormalarray[a][0],
			worldtilevertexcount[a],1.0);
		//create the alternate rotations however, this part can be modified in a way to rotate an arbitrary angle
		for(int b=1; b<4; b++){
			worldtilevertexarray[a][b]=new float[worldtilevertexcount[a]*3];
			for(int c=0; c<worldtilevertexcount[a]; c++){
				float angle = b*90*radiansindegree;
				float tempposx=worldtilevertexarray[a][0][c*3+0];
				float tempposy=worldtilevertexarray[a][0][c*3+1];
				float tempposz=worldtilevertexarray[a][0][c*3+2];
				worldtilevertexarray[a][b][c*3+0] = tempposz*sin(angle)+tempposx*cos(angle);
				worldtilevertexarray[a][b][c*3+1] = tempposy;
				worldtilevertexarray[a][b][c*3+2] = tempposz*cos(angle)-tempposx*sin(angle);
			}
		}
	
		//set normals for the alternate rotation
		for(int b=0; b<4; b++){
			if(b!=0)worldtilenormalarray[a][b] = new float[worldtilevertexcount[a]*3];
			for(int c=0; c<worldtilevertexcount[a]; c++){
				worldtilenormalarray[a][b][c*3+0]=worldtilenormalarray[a][0][c*3+0];
				worldtilenormalarray[a][b][c*3+1]=worldtilenormalarray[a][0][c*3+1];
				worldtilenormalarray[a][b][c*3+2]=worldtilenormalarray[a][0][c*3+2];
			}
		}

		//rig the normals
		for(int b=0; b<4; b++)
			for(int c=0; c<worldtilevertexcount[a]/3; c++){
				CVector3 g_vTriangle[3];
				g_vTriangle[0]=CVector3(worldtilevertexarray[a][b][c*9+0],worldtilevertexarray[a][b][c*9+1],worldtilevertexarray[a][b][c*9+2]);
				g_vTriangle[1]=CVector3(worldtilevertexarray[a][b][c*9+3],worldtilevertexarray[a][b][c*9+4],worldtilevertexarray[a][b][c*9+5]);
				g_vTriangle[2]=CVector3(worldtilevertexarray[a][b][c*9+6],worldtilevertexarray[a][b][c*9+7],worldtilevertexarray[a][b][c*9+8]);
				CVector3 vNormal = Normal(g_vTriangle);
				worldtilenormalarray[a][b][c*9+0]=-vNormal.x;//vert1
				worldtilenormalarray[a][b][c*9+1]=-vNormal.y;
				worldtilenormalarray[a][b][c*9+2]=-vNormal.z;
				worldtilenormalarray[a][b][c*9+3]=-vNormal.x;//vert2
				worldtilenormalarray[a][b][c*9+4]=-vNormal.y;
				worldtilenormalarray[a][b][c*9+5]=-vNormal.z;
				worldtilenormalarray[a][b][c*9+6]=-vNormal.x;//vert3
				worldtilenormalarray[a][b][c*9+7]=-vNormal.y;
				worldtilenormalarray[a][b][c*9+8]=-vNormal.z;
			}

		//create the collision meshes
		for(int b=0; b<4; b++)
			worldtilecollisionmesh[a][b] = new collisionmesh(worldtilevertexcount[a],worldtilevertexarray[a][b]);


		//load the textures
		sprintf_s(filename,"%s%i%s","Media/worldtiles/",a,".bmp");
		worldtiletexture[a]=loadbmp((char*)filename,mipmapping);

		//update progress bar

		//drawprogressbar(10.f,280.f,200,310.f,3.f,a/worldtilecount*0.01f);
	}

	
	

	

}
