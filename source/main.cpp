#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "OVR.h"
#include "generic.h"
#include "settings.h"
#include "projectsetup.h"
#include "projectloop.h"
#include "projectshaders.h"
#pragma comment(lib,"libovr.lib")


int main(int argc,char **argv){

	for(int i=1;i<argc;i++){
		if(!strcmp(argv[i],"/TEST")) test=atoi(argv[i+1]);
	}
	System::Init(Log::ConfigureDefaultLog(LogMask_All));

	load_OVR();

	loadgenericsettings();									//load the generic settings

	genericsetup();											//generic setup

	dashsetup();											//setup the dashboard

	projectsetup();											//setup for the project

	updateinput();										    //get the initial value of the HMD
	Start_yaw=camyang-(90*radiansindegree);

	initShaders(file2string("k.vert"), file2string("k.frag"));
	initFBO(screenw, screenh);
	
	//game loop
	while(!shutdownprogram)
	{

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//clear the screen

		SDL_PumpEvents();									//get what events have occured

		updateinput();										//get controller input

		gamespeed=60.f/dash_framerate;
		if(gamespeed<0.2f)gamespeed=0.2f;
		if(gamespeed>2.0f)gamespeed=2.0f;

		//play
		play(gamespeed);

		if(!dashonpercent) RenderScene();

		dashloop();

		SDL_GL_SwapBuffers();

		//clear out left over events and shut down when appropriate
		SDL_Event event;
		while(SDL_PeepEvents(&event,1,SDL_GETEVENT,SDL_ALLEVENTS)>0)
			if(event.type==SDL_QUIT)shutdownprogram=1;
	}

	// Clean up
	SKYBOX_Finalize();
	SDL_Quit();
	return 0;
}
