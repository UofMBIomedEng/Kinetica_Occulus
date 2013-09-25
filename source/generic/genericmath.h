int rounduptopowof2(int num){
	int powof2=2;
	while(powof2<num)powof2*=2;
	return powof2;
}

int lowint(int a,int b){
	if(a<b){return a;}else{return b;}
}

int highint(int a,int b){
	if(a>b){return a;}else{return b;}
}

float lowfloat(float a,float b){
	if(a<b){return a;}else{return b;}
}

float highfloat(float a,float b){
	if(a>b){return a;}else{return b;}
}

int inintrange(int num,int high,int low){
	if(num>high)num=high;
	if(num<low)num=low;
	return num;
}

float infloatrange(float num,float high,float low){
	if(num>high)num=high;
	if(num<low)num=low;
	return num;
}

Uint8 in8bitrange(int num){
	if(num<=0) return 0;
	else if(num>=255) return 255;
	else return num;
}

void movein2dspace(float &xpos,float &ypos,float ang,float speed){
	xpos+=speed*cos(ang);
	ypos+=speed*sin(ang);
}

void movein3dspace(float &xpos,float &ypos,float &zpos,float yang,float xang,float speed){
	ypos+=speed*sin(xang);
	xpos+=speed*cos(xang)*cos(yang);
	zpos+=speed*cos(xang)*sin(yang);
}

float dist2d(float x,float y,float x2,float y2){
	x-=x2;
	y-=y2;
	return sqrt(x*x+y*y);
}

float dist3d(float x,float y,float z,float x2,float y2,float z2){
	x-=x2;
	y-=y2;
	z-=z2;
	return sqrt(x*x+y*y+z*z);
}

float mindist2d(float x,float y,float x2,float y2,float minimumdistance){
	if(x<x2+minimumdistance && y<y2+minimumdistance
	&& x>x2-minimumdistance && y>y2-minimumdistance){
		x-=x2;
		y-=y2;
		return sqrt(x*x+y*y);
	}else{
		return minimumdistance;
	}
}

float mindist3d(float x,float y,float z,float x2,float y2,float z2,float minimumdistance){
	if(x<x2+minimumdistance && y<y2+minimumdistance && z<z2+minimumdistance
	&& x>x2-minimumdistance && y>y2-minimumdistance && z>z2-minimumdistance){
		x-=x2;
		y-=y2;
		z-=z2;
		return sqrt(x*x+y*y+z*z);
	}else{
		return minimumdistance;
	}
}

float angledifference(float startangle,float endangle){
	while(startangle<endangle-180*radiansindegree)startangle+=360*radiansindegree;
	while(startangle>endangle+180*radiansindegree)startangle-=360*radiansindegree;
	return (endangle-startangle);
}

float turntoangle(float startangle,float endangle,float speed){
	return startangle+angledifference(startangle,endangle)*speed;
}

float randangle(){
	float angle=(float)(rand()%(360*100))*0.01f*radiansindegree;
	return angle;
}