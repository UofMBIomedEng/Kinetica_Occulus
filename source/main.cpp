#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "OVR.h"
#pragma comment(lib,"libovr.lib")

const float PI=3.14159265f;
const float degreesinradian=360/(2*PI); 
const float radiansindegree=(2*PI)/360;

double dyneye = 0.05;
double dyntest = 1;
double dynasp = 1.6;
double dyndist = 0.6;
int    eye_offset = 86;



enum Eye {
        Left, Right
    };

using namespace OVR;

float                camxpos=0,camypos=0,camzpos=0;
float                camxang=0,camyang=90*radiansindegree,camzang=0;
int vp;
bool shutdownprogram = 0;
Ptr<HMDDevice>      pHMD;
Quatf               Rot;
float               LastSensorYaw;
Vector3f            EyePos;
float               EyeYaw;
float               EyePitch;       
float               EyeRoll;   
float               tyaw,yaw, pitch, roll,Start_yaw=0;
static OVR::SensorDevice* pSensor;
static OVR::SensorFusion fusion;
static OVR::DeviceManager* pManager;
static OVR::Quatf q;

bool useshaders = true;

#include <GL\glew.h>
#include <GL\glut.h>

#include "generic.h"
#include "settings.h"
#include "projectsetup.h"
#include "projectloop.h"
#include "projectshaders.h"

const Quatf&   GetOrientation()  { return Rot; }
const float    YawInitial  = 3.141592f;





static void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	beginOffScreenRenderPass();

	glEnable(GL_SCISSOR_TEST);

	//render left half
	glViewport(eye_offset, 0, (int)((screenw/2)-eye_offset), screenh);
	glScissor(eye_offset, 0, (int)((screenw/2)-eye_offset), screenh);
	
	drawworld(Left);
//	drawhud();

	glDisable(GL_SCISSOR_TEST);

	glEnable(GL_SCISSOR_TEST);
	//render right half
	glViewport((int)screenw/2, 0, (int)((screenw/2)-eye_offset), screenh);
	glScissor((int)screenw/2, 0, (int)((screenw/2)-eye_offset), screenh);
	drawworld(Right);
//	drawhud();

	glDisable(GL_SCISSOR_TEST);

	//apply post distortion via shaders
	glViewport(0, 0, screenw, screenh);
	renderToScreen();

	glDisable(GL_SCISSOR_TEST);
}


int main(int argc,char **argv){

	for(int i=1;i<argc;i++){
		if(!strcmp(argv[i],"/TEST")) test=atoi(argv[i+1]);
	}
	System::Init(Log::ConfigureDefaultLog(LogMask_All));

	EyeYaw = YawInitial;
	EyePitch = 0;
	EyeRoll = 0;
	LastSensorYaw = 0;

	pManager = OVR::DeviceManager::Create();
	if(pManager)
	{
		OVR::DeviceEnumerator<OVR::SensorDevice> dEnum = pManager->EnumerateDevices<OVR::SensorDevice>();
		while(dEnum)
		{
			OVR::DeviceInfo info;
			if (dEnum.GetDeviceInfo(&info))
			{
				if(strstr(info.ProductName, "Tracker"))
				{
					break;
				}
			}
			dEnum.Next();
		}
		if(dEnum)
		{
			pSensor = dEnum.CreateDevice();
		}
		if (pSensor)
		{
			bool bWaitForSuccessfulRange = true;
			float maxAcceleration = 4 * 9.81f;
			float maxRotationRate = 8 * OVR::Math<float>::Pi;
			float maxMagneticField = 1.0f;
			pSensor->SetRange(OVR::SensorRange(maxAcceleration,maxRotationRate,maxMagneticField), bWaitForSuccessfulRange);
		}
		if(dEnum)
		{
			dEnum.Clear();
		}
		if(pSensor)
		{
			fusion.AttachToSensor(pSensor);
		}
	}


	loadgenericsettings();									//load the generic settings

	genericsetup();											//generic setup

	dashsetup();											//setup the dashboard

	projectsetup();											//setup for the project

	GLenum res = glewInit();

	updateinput();										//get controller input

	Start_yaw=camyang-(90*radiansindegree);

	initShaders(file2string("k.vert"), file2string("k.frag"));
	initFBO(screenw, screenh);

	//game loop
	while(!shutdownprogram)
	{
		/*
		if (GetAsyncKeyState(VK_F3) != 0)
		{
			dyneye += 0.001;
		}
		if (GetAsyncKeyState(VK_F4) != 0)
		{
			dyneye -= 0.001;
		}
		if (GetAsyncKeyState(VK_F5) != 0)
		{
			dyntest += 0.001;
		}
		if (GetAsyncKeyState(VK_F6) != 0)
		{
			dyntest -= 0.001;
		}
	
		if (GetAsyncKeyState(VK_F6) != 0)
		{
			dynasp -= 0.01;
		}
		if (GetAsyncKeyState(VK_F7) != 0)
		{
			dynasp += 0.01;
		}
		
		if (GetAsyncKeyState(VK_F8) != 0)
		{
			dyndist -= 0.1;
		}
		if (GetAsyncKeyState(VK_F9) != 0)
		{
			dyndist += 0.1;
		}		
		//decrease view range
		if(keystate[SDLK_9]==2){
			eye_offset++;
		}
		//increase view range
		if(keystate[SDLK_0]==2){
			eye_offset--;
		}
		*/

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

		//if(!dashonpercent)RenderSceneCB_L();					//update the game
		//if(!dashonpercent)RenderSceneCB_R();					//update the game

		//glViewport(0,0,screenw,screenh);
		//renderToScreen();

		//dashloop();		//update the dashboard

		//SDL_GL_SwapBuffers();								//show the frame

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
