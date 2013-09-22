float gamespeed;



void projectloop(){
	
	//adjust the speed of the game based on the frame rate
	gamespeed=60.f/dash_framerate;
	if(gamespeed<0.2f)gamespeed=0.2f;
	if(gamespeed>2.0f)gamespeed=2.0f;

	//play
	play(gamespeed);
	//glViewport(0, 0, (int)screenw, (int)screenh); 
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	drawworld(Left);
	drawhud();

//	glutSwapBuffers();


}
