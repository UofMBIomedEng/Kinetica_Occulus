struct InterleavedVertex{
	float px,py,pz;	//Vertex
	float nx,ny,nz;	//Normal
	float tx,ty;	//Texcoord
};

float* morph(float* mesh1,float* mesh2,int arraysize,float progress){
	float *finalarray = new float[arraysize];
	for(int a=0; a<arraysize; a++)
		finalarray[a]=mesh1[a]*(1-progress)+mesh2[a]*(progress);
	return finalarray;
}

void set3dcamera(float xpos,float ypos,float zpos,float xang,float yang,float zang,float fov,float aspect)
{
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//enable depth test
	//glEnable(GL_DEPTH_TEST);
	//setup the camera
	gluPerspective(fov,aspect,1.f,1000.f);
	//glFrustum(
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//rotate
	glRotatef(zang*degreesinradian,0,0,1);
	glRotatef(xang*degreesinradian,1,0,0);
	glRotatef(yang*degreesinradian,0,1,0);
	//position

	SKYBOX_Render();

	glTranslatef(-xpos,-ypos,-zpos);
}

void set2dcamera(float top,float bottom,float left,float right){
	//disable depth test
	glDisable(GL_DEPTH_TEST);
	//setup the camera
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//apply the top, bottom, left and right settings
	glScalef(1.f,-1.f,1.f);
	glTranslatef(-1,-1,0);
	glScalef(1/((right-left)*0.5f),1/((bottom-top)*0.5f),1.f);
	glTranslatef(left,top,0);
}

void draw2dquad(float posx,float posy,float sizex,float sizey,float *texturecoords){
	float verts[]={
		posx,		posy+sizey,
		posx+sizex,	posy+sizey,
		posx+sizex,	posy,
		posx,		posy,};
	glVertexPointer(2,GL_FLOAT,0,verts);
	glTexCoordPointer(2,GL_FLOAT,0,texturecoords);

	glDrawArrays(GL_QUADS,0,4);
}

void draw2dquad2(float posx,float posy,float sizex,float sizey,float *texturecoords,bool centerandrotate=0,float angle=0){
	if(centerandrotate==0){
		float verts[]={posx,posy+sizey,posx+sizex,posy+sizey,posx+sizex,posy,posx,posy,};
		glVertexPointer(2,GL_FLOAT,0,verts);
		glTexCoordPointer(2,GL_FLOAT,0,texturecoords);
		glDrawArrays(GL_QUADS,0,4);
	}else if(angle==0){
		sizex*=0.5f;
		sizey*=0.5f;
		float verts[]={posx-sizex,posy+sizey,posx+sizex,posy+sizey,posx+sizex,posy-sizey,posx-sizex,posy-sizey,};
		glVertexPointer(2,GL_FLOAT,0,verts);
		glTexCoordPointer(2,GL_FLOAT,0,texturecoords);
		glDrawArrays(GL_QUADS,0,4);
	}else{
		sizex*=0.5f;
		sizey*=0.5f;
		float verts[]={0-sizex,0+sizey,0+sizex,0+sizey,0+sizex,0-sizey,0-sizex,0-sizey,};
		glPushMatrix();
		glTranslatef(posx,posy,0);
		glRotatef(angle*degreesinradian,0,0,1);
		glVertexPointer(2,GL_FLOAT,0,verts);
		glTexCoordPointer(2,GL_FLOAT,0,texturecoords);
		glDrawArrays(GL_QUADS,0,4);
		glPopMatrix();
	}
}

void draw3dquadmesh(int vertexcount,float *verts,float *texturecoords,float *colors = NULL,float *normals = NULL){
	glVertexPointer(3,GL_FLOAT,0,verts);
	glTexCoordPointer(2,GL_FLOAT,0,texturecoords);
	if(colors!=NULL)glColorPointer(3,GL_FLOAT,0,colors);
	if(normals!=NULL)glNormalPointer(GL_FLOAT,0,normals);
	glDrawArrays(GL_QUADS,0,vertexcount);
}

void draw3dtrianglemesh(int vertexcount,float *verts,float *texturecoords,float *colors = NULL,float *normals = NULL){
	glVertexPointer(3,GL_FLOAT,0,verts);
	glTexCoordPointer(2,GL_FLOAT,0,texturecoords);
	if(colors!=NULL)glColorPointer(3,GL_FLOAT,0,colors);
	if(normals!=NULL)glNormalPointer(GL_FLOAT,0,normals);
	glDrawArrays(GL_TRIANGLES,0,vertexcount);
}
