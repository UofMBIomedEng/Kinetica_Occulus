#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <GL/glew.h>
#include <GL/glut.h>

using namespace std;

static const GLchar *vsSource;
static const GLchar *fsSource;

GLuint shader = 0;
GLuint vertShader = 0;
GLuint fragShader = 0;

GLuint colorTextureID;
GLuint framebufferID;
GLuint depthRenderBufferID;

int LensCenterLocation;
int ScreenCenterLocation;
int ScaleLocation;
int ScaleInLocation;
int HmdWarpParamLocation;

float K0 = 1.0f;
float K1 = 0.22f;
float K2 = 0.24f;
float K3 = 0.0f;

//#define EyeLeft 1
//#define EyeRight 0




void error(string msg)
{
	fprintf(stderr, "Error: '%s'\n", msg);
}

void error(GLenum res)
{
	fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
}

char *file2string(const char *path)
{
	FILE *fd;
	long len,
		r;
	char *str;

	if (!(fd = fopen(path, "r")))
	{
		fprintf(stderr, "Can't open file '%s' for reading\n", path);
		exit(11);
		return NULL;
	}

	fseek(fd, 0, SEEK_END);
	len = ftell(fd);

	printf("File '%s' is %ld long\n", path, len);

	fseek(fd, 0, SEEK_SET);

	if (!(str = (char *)malloc(len * sizeof(char))))
	{
		fprintf(stderr, "Can't malloc space for '%s'\n", path);
		return NULL;
	}

	r = fread(str, sizeof(char), len, fd);

	str[r - 1] = '\0'; /* Shader sources have to term with null */

	fclose(fd);

	return str;
}

int createVertShader(string vert_code)
{
    vertShader=glCreateShader(GL_VERTEX_SHADER);
    if (vertShader==0) 
	{
		error("Could not create vert shader");
        return 0;
    }

	const char *c_str = vert_code.c_str();
    glShaderSource(vertShader, 1, &c_str, NULL);
    glCompileShader(vertShader);


	GLint success;
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		GLchar infolog[1024];
		glGetShaderInfoLog(vertShader, 1024, NULL, infolog);
		error(infolog);
		exit(1);
	}

    return vertShader;
}

int createFragShader(string fragCode)
{

    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    if (fragShader==0) 
	{
		error("Could not create frag shader");
        return 0;
    }

	const char *c_str = fragCode.c_str();
	glShaderSource(fragShader, 1, &c_str, NULL);
    glCompileShader(fragShader);

	GLint success;
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		GLchar infolog[1024];
		glGetShaderInfoLog(fragShader, 1024, NULL, infolog);
		error(infolog);
		exit(1);
	}

    return fragShader;
}

void initShaders(string vertexShader, string fragmentShader) 
{
	GLint success = 0;
	GLchar errorlog[1024] = {0};

	shader = glCreateProgram();
	if(shader == 0)
	{
		error("could not create shader program");
		exit(12);
	}

	vertShader=createVertShader(vertexShader);
	fragShader=createFragShader(fragmentShader);

	if (vertShader != 0 && fragShader != 0) {
		glAttachShader(shader, vertShader);
		glAttachShader(shader, fragShader);

		glLinkProgram(shader);
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if(success == 0)
		{
			glGetProgramInfoLog(shader, sizeof(errorlog), NULL, errorlog);
			error(errorlog);
			exit(13);
		}

		glValidateProgram(shader);
		glGetProgramiv(shader, GL_VALIDATE_STATUS, &success);
		if(!success)
		{
			glGetProgramInfoLog(shader, sizeof(errorlog), NULL, errorlog);
			error(errorlog);
			exit(14);
		}
	} 
	else 
	{
		error("shaders critical error");
		exit(15);
	}

}
extern double dyneye;
extern double dyntest;
extern double dynasp;
void renderDistortedEye(int eye, float x, float y, float w, float h) 
{
        float as = dynasp;
        
        float scaleFactor = dyntest;
        
		glValidateProgram(shader);
        
        float DistortionXCenterOffset;
        if (eye == Left) {
            DistortionXCenterOffset = dyneye;
        }
        else {
            DistortionXCenterOffset = -dyneye;
        }
        
        glUniform2f(LensCenterLocation, x + (w + DistortionXCenterOffset * 0.5f)*0.5f, y + h*0.5f);
        glUniform2f(ScreenCenterLocation, x + w*0.5f, y + h*0.5f);
        glUniform2f(ScaleLocation, (w/2.0f) * 0.552, (h/2.0f) * 0.891 * as);
        glUniform2f(ScaleInLocation, (2.0f/w), (2.0f/h) / as);

        glUniform4f(HmdWarpParamLocation, K0, K1, K2, K3);
        
        if(eye == Left) {
            glBegin(GL_TRIANGLE_STRIP);
                glTexCoord2f(0.0f, 0.0f);   glVertex2f(-1.0f, -1.0f);
                glTexCoord2f(0.5f, 0.0f);   glVertex2f(0.0f, -1.0f);
                glTexCoord2f(0.0f, 1.0f);   glVertex2f(-1.0f, 1.0f);
                glTexCoord2f(0.5f, 1.0f);   glVertex2f(0.0f, 1.0f);
            glEnd();
        }
        else {
            glBegin(GL_TRIANGLE_STRIP);
                glTexCoord2f(0.5f, 0.0f);   glVertex2f(0.0f, -1.0f);
                glTexCoord2f(1.0f, 0.0f);   glVertex2f(1.0f, -1.0f);
                glTexCoord2f(0.5f, 1.0f);   glVertex2f(0.0f, 1.0f);
                glTexCoord2f(1.0f, 1.0f);   glVertex2f(1.0f, 1.0f);
            glEnd();            
        }
    }

void initFBO(int screenWidth, int screenHeight) 
{
	glGenFramebuffers(1, &framebufferID);
	glGenTextures(1, &colorTextureID);
	glGenRenderbuffers(1, &depthRenderBufferID);
    
	//init frame buffer
    glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);                                               

    // initialize color texture
    glBindTexture(GL_TEXTURE_2D, colorTextureID);                                                                  
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);                               
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, screenWidth, screenHeight, 0,GL_RGBA, GL_INT, NULL); 
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D, colorTextureID, 0);

    // initialize depth renderbuffer
    glBindRenderbuffer(GL_RENDERBUFFER, depthRenderBufferID);                               
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, screenWidth, screenHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER, depthRenderBufferID); 

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		error("could not create frame buffer");
		exit(1);
	}

    glBindFramebuffer(GL_FRAMEBUFFER, 0); 

	LensCenterLocation = glGetUniformLocation(shader, "LensCenter");
    ScreenCenterLocation = glGetUniformLocation(shader, "ScreenCenter");
    ScaleLocation = glGetUniformLocation(shader, "Scale");
    ScaleInLocation = glGetUniformLocation(shader, "ScaleIn");
    HmdWarpParamLocation = glGetUniformLocation(shader, "HmdWarpParam");
}

void beginOffScreenRenderPass() 
{     
    glBindTexture(GL_TEXTURE_2D, 0);         
    glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);
}

void renderToScreen() 
{
    if(useshaders) glUseProgram(shader);
        
    glEnable(GL_TEXTURE_2D);    
    glDisable(GL_DEPTH_TEST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);                                    

    glClearColor (1.0f, 0.0f, 0.0f, 0.5f);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindTexture(GL_TEXTURE_2D, colorTextureID);   

    renderDistortedEye(Left, 0.0f, 0.0f, 0.5f, 1.0f);
    renderDistortedEye(Right, 0.5f, 0.0f, 0.5f, 1.0f);

    glUseProgram(0);
    glEnable(GL_DEPTH_TEST);
}