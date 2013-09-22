//controller input variables
int cursorx[4];
int cursory[4];
int cursorxmov[4];
int cursorymov[4];
bool centercursor=0;

const int keycount=500;
int keystate[keycount];
const int buttoncount=20;
int buttonstate[keycount];
const int mousecount=10;
int mousestate[mousecount];

// Initialize input device
void setupinput(){

}

void updateinput(){
	if (pSensor)
	{        
		Quatf    hmdOrient = fusion.GetOrientation();
		float    yaw = 0.0f;

		hmdOrient.GetEulerAngles<Axis_Y, Axis_X, Axis_Z>(&yaw, &pitch, &roll);

		EyeYaw += (yaw - LastSensorYaw);
		LastSensorYaw = yaw;    
		roll=roll;
		//EyeYaw=EyeYaw;
		//pitch=pitch;

		camxang = -pitch; 
		camyang = -yaw-Start_yaw; 
		camzang = -roll;
	}


	
   
    //*** Adjust 0.5,0.5 according to how you render
   

	SDL_Event event;

	for(int a=0;a<keycount;a++)if(keystate[a]==2)keystate[a]=1;
	while(SDL_PeepEvents(&event,1,SDL_GETEVENT,SDL_EVENTMASK(SDL_KEYDOWN)))
		keystate[event.key.keysym.sym]=2;
	while(SDL_PeepEvents(&event,1,SDL_GETEVENT,SDL_EVENTMASK(SDL_KEYUP)))
		keystate[event.key.keysym.sym]=0;
	
	for(int a=0;a<buttoncount;a++)if(buttonstate[a]==2)buttonstate[a]=1;
	while(SDL_PeepEvents(&event,1,SDL_GETEVENT,SDL_EVENTMASK(SDL_JOYBUTTONDOWN)))
		buttonstate[event.jbutton.button]=2;
	while(SDL_PeepEvents(&event,1,SDL_GETEVENT,SDL_EVENTMASK(SDL_JOYBUTTONUP)))
		buttonstate[event.jbutton.button]=0;

	for(int a=0;a<mousecount;a++)if(mousestate[a]==2)mousestate[a]=1;
	while(SDL_PeepEvents(&event,1,SDL_GETEVENT,SDL_EVENTMASK(SDL_MOUSEBUTTONDOWN)))
		mousestate[event.button.button]=2;
	while(SDL_PeepEvents(&event,1,SDL_GETEVENT,SDL_EVENTMASK(SDL_MOUSEBUTTONUP)))
		mousestate[event.button.button]=0;

	if(centercursor){
		//SDL_WM_GrabInput(SDL_GRAB_ON);
		SDL_GetMouseState(&cursorx[0],&cursory[0]);
		//SDL_GetRelativeMouseState(&cursorxmov[0],&cursorymov[0]);
		SDL_WarpMouse(screen->w/2,screen->h/2);
		cursorxmov[0]=cursorx[0]-screen->w/2;
		cursorymov[0]=cursory[0]-screen->h/2;
	}else{
		int oldx=cursorx[0];
		int oldy=cursory[0];
		SDL_GetMouseState(&cursorx[0],&cursory[0]);
		cursorxmov[0]=cursorx[0]-oldx;
		cursorymov[0]=cursory[0]-oldy;
	}
}

