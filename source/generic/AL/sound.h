#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alut.h"
#include "AL/efx.h"
#include "AL/EFX-Util.h"
#include "AL/efx-presets.h"
#include "AL/efx-creative.h"
#include "AL/alext.h"

//#define PI 3.141592654

#define NUM_BUFFERS 7	// Number of buffers to be Generated

// Global variables
ALuint	g_Buffers[NUM_BUFFERS];		// Array of Buffer IDs

ALuint	source[2];


// Function prototypes
ALvoid DisplayALError(ALubyte *szText, ALint errorCode);

// Test Function prototypes
ALvoid PositionTest(ALvoid);
ALvoid LoopingTest(ALvoid);
ALvoid FreqTest(ALvoid);
ALvoid StereoTest(ALvoid);
ALvoid GainTest(ALvoid);
ALvoid RelativeTest(ALvoid);
ALvoid MultipleSourcesTest(ALvoid);
ALvoid SourceRollOffTest(ALvoid);

#ifndef ALC_EXT_EFX
#define AL_FILTER_TYPE                                     0x8001
#define AL_EFFECT_TYPE                                     0x8001
#define AL_FILTER_NULL                                     0x0000
#define AL_FILTER_LOWPASS                                  0x0001
#define AL_FILTER_HIGHPASS                                 0x0002
#define AL_FILTER_BANDPASS                                 0x0003
#define AL_EFFECT_NULL                                     0x0000
#define AL_EFFECT_EAXREVERB                                0x8000
#define AL_EFFECT_REVERB                                   0x0001
#define AL_EFFECT_CHORUS                                   0x0002
#define AL_EFFECT_DISTORTION                               0x0003
#define AL_EFFECT_ECHO                                     0x0004
#define AL_EFFECT_FLANGER                                  0x0005
#define AL_EFFECT_FREQUENCY_SHIFTER                        0x0006
#define AL_EFFECT_VOCAL_MORPHER                            0x0007
#define AL_EFFECT_PITCH_SHIFTER                            0x0008
#define AL_EFFECT_RING_MODULATOR                           0x0009
#define AL_EFFECT_AUTOWAH                                  0x000A
#define AL_EFFECT_COMPRESSOR                               0x000B
#define AL_EFFECT_EQUALIZER                                0x000C
#define ALC_EFX_MAJOR_VERSION                              0x20001
#define ALC_EFX_MINOR_VERSION                              0x20002
#define ALC_MAX_AUXILIARY_SENDS                            0x20003
#endif
ALvoid (AL_APIENTRY *p_alGenFilters)(ALsizei,ALuint*);
ALvoid (AL_APIENTRY *p_alDeleteFilters)(ALsizei,ALuint*);
ALvoid (AL_APIENTRY *p_alFilteri)(ALuint,ALenum,ALint);
ALvoid (AL_APIENTRY *p_alGenEffects)(ALsizei,ALuint*);
ALvoid (AL_APIENTRY *p_alDeleteEffects)(ALsizei,ALuint*);
ALvoid (AL_APIENTRY *p_alEffecti)(ALuint,ALenum,ALint);

static const int indentation = 4;
static const int maxmimumWidth = 79;




void init_sound(void){
	ALint	error;
	
	ALCcontext *Context;
	ALCdevice *Device;
	
	ALfloat listenerPos[]={0.0,0.0,0.0};
	ALfloat listenerVel[]={0.0,0.0,0.0};
	ALfloat	listenerOri[]={0.0,0.0,-1.0, 0.0,1.0,0.0};	// Listener facing into the screen


	printf("OpenAL Test application\n\n");

	// Initialize Open AL manually

	//Open device
	Device = alcOpenDevice(NULL); // this is supposed to select the "preferred device"	
	//Create context(s)
	Context=alcCreateContext(Device,NULL);
	//Set active context
	alcMakeContextCurrent(Context);
	

	// Set Listener attributes
	alListenerfv(AL_POSITION,listenerPos); 	// Position ...
	alListenerfv(AL_VELOCITY,listenerVel); 	// Velocity ...
	alListenerfv(AL_ORIENTATION,listenerOri); 	// Orientation ...
	alGenBuffers(NUM_BUFFERS, g_Buffers);  // Generate Buffers

	// Load in samples to be used by Test functions
	ALsizei size,freq;
	ALenum	format;
	ALvoid	*data;
	ALboolean loop;
		
	// Load WaveNames[which_wave]
	alutLoadWAVFile((ALbyte*)"Media/ding.wav",&format,&data,&size,&freq,&loop);
	// an example of error checking
	if ((error = alGetError()) != AL_NO_ERROR)
	{
		printf("alutLoadWAVFile : ", error);
		// Delete Buffers
		alDeleteBuffers(NUM_BUFFERS, g_Buffers);
		exit(-1);
	}

	// Copy WaveNames[which_wave] data into AL Buffer which_wave
	alBufferData(g_Buffers[1],format,data,size,freq);

	// Unload WaveNames[which_wave]
	alutUnloadWAV(format,data,size,freq);
	

}

/*
	Position Test
	Creates 2 Sources - one to the front right of the listener, and one to the rear left of the listener
*/
ALvoid PositionTest(ALvoid)
{	
	ALint	error;
	
//	ALuint	source[2];

	ALfloat source0Pos[]={ -2.0, 0.0, 2.0};	// Behind and to the left of the listener
	ALfloat source0Vel[]={ 0.0, 0.0, 0.0};

	ALfloat source1Pos[]={ 2.0, 0.0, -2.0};	// Front and to the right of the listener
	ALfloat source1Vel[]={ 0.0, 0.0, 0.0};

	alGenSources(2,source);

	alSourcef(source[0],AL_PITCH,1.0f);
	alSourcef(source[0],AL_GAIN,1.0f);
	alSourcefv(source[0],AL_POSITION,source0Pos);
	alSourcefv(source[0],AL_VELOCITY,source0Vel);
	alSourcei(source[0],AL_BUFFER, g_Buffers[1]);
	alSourcei(source[0],AL_LOOPING,AL_TRUE);

	alSourcePlay(source[0]);



}

static void die(const char *kind, const char *description)
{
    fprintf(stderr, "%s error %s occured\n", kind, description);
    exit(EXIT_FAILURE);
}

static void checkForErrors(void)
{
    {
        ALCdevice *device = alcGetContextsDevice(alcGetCurrentContext());
        ALCenum error = alcGetError(device);
        if(error != ALC_NO_ERROR)
            die("ALC", (const char*)alcGetString(device, error));
    }
    {
        ALenum error = alGetError();
        if(error != AL_NO_ERROR)
            die("AL", (const char*)alGetString(error));
    }
}

static void printDevices(ALCenum which, const char *kind)
{
    const char *s = alcGetString(NULL, which);
    checkForErrors();

    printf("Available %sdevices:\n", kind);
    while(*s != '\0')
    {
        printf("    %s\n", s);
        while(*s++ != '\0')
            ;
    }
}

static void printALCInfo (void)
{
    ALCint major, minor;
    ALCdevice *device;

    if(alcIsExtensionPresent(NULL, (const ALCchar*)"ALC_ENUMERATION_EXT") == AL_TRUE)
    {
        if(alcIsExtensionPresent(NULL, (const ALCchar*)"ALC_ENUMERATE_ALL_EXT") == AL_TRUE)
            printDevices(ALC_ALL_DEVICES_SPECIFIER, "playback ");
        else
            printDevices(ALC_DEVICE_SPECIFIER, "playback ");
        printDevices(ALC_CAPTURE_DEVICE_SPECIFIER, "capture ");
    }
    else
        printf("No device enumeration available\n");

    device = alcGetContextsDevice(alcGetCurrentContext());
    checkForErrors();

    printf("Default device: %s\n",
           alcGetString(device, ALC_DEFAULT_DEVICE_SPECIFIER));

    printf("Default capture device: %s\n",
           alcGetString(device, ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER));

    alcGetIntegerv(device, ALC_MAJOR_VERSION, 1, &major);
    alcGetIntegerv(device, ALC_MINOR_VERSION, 1, &minor);
    checkForErrors();
    printf("ALC version: %d.%d\n", (int)major, (int)minor);

    printf("ALC extensions", ' ',
                    alcGetString(device, ALC_EXTENSIONS));
    checkForErrors();
}

static void printALInfo(void)
{
    printf("OpenAL vendor string: %s\n", alGetString(AL_VENDOR));
    printf("OpenAL renderer string: %s\n", alGetString(AL_RENDERER));
    printf("OpenAL version string: %s\n", alGetString(AL_VERSION));
    printf("OpenAL extensions", ' ', alGetString(AL_EXTENSIONS));
    checkForErrors();
}

static void printEFXInfo(void)
{
    ALCint major, minor, sends;
    ALCdevice *device;
    ALuint obj;
    int i;
    const struct {
        ALenum type;
        const char *name;
    } effects[] = {
        { AL_EFFECT_EAXREVERB,         "EAX Reverb"        },
        { AL_EFFECT_REVERB,            "Reverb"            },
        { AL_EFFECT_CHORUS,            "Chorus"            },
        { AL_EFFECT_DISTORTION,        "Distortion"        },
        { AL_EFFECT_ECHO,              "Echo"              },
        { AL_EFFECT_FLANGER,           "Flanger"           },
        { AL_EFFECT_FREQUENCY_SHIFTER, "Frequency Shifter" },
        { AL_EFFECT_VOCAL_MORPHER,     "Vocal Morpher"     },
        { AL_EFFECT_PITCH_SHIFTER,     "Pitch Shifter"     },
        { AL_EFFECT_RING_MODULATOR,    "Ring Modulator"    },
        { AL_EFFECT_AUTOWAH,           "Autowah"           },
        { AL_EFFECT_COMPRESSOR,        "Compressor"        },
        { AL_EFFECT_EQUALIZER,         "Equalizer"         },
        { AL_EFFECT_NULL, NULL }
    };
    const struct {
        ALenum type;
        const char *name;
    } filters[] = {
        { AL_FILTER_LOWPASS,  "Low-pass"  },
        { AL_FILTER_HIGHPASS, "High-pass" },
        { AL_FILTER_BANDPASS, "Band-pass" },
        { AL_FILTER_NULL, NULL }
    };

    device = alcGetContextsDevice(alcGetCurrentContext());

    if(alcIsExtensionPresent(device, (const ALCchar*)"ALC_EXT_EFX") == AL_FALSE)
    {
        printf("EFX not available\n");
        return;
    }

    alcGetIntegerv(device, ALC_EFX_MAJOR_VERSION, 1, &major);
    alcGetIntegerv(device, ALC_EFX_MINOR_VERSION, 1, &minor);
    checkForErrors();
    printf("EFX version: %d.%d\n", (int)major, (int)minor);

    alcGetIntegerv(device, ALC_MAX_AUXILIARY_SENDS, 1, &sends);
    checkForErrors();
    printf("Max auxiliary sends: %d\n", (int)sends);
/*
    p_alGenFilters = alGetProcAddress("alGenFilters");
    p_alDeleteFilters = alGetProcAddress("alDeleteFilters");
    p_alFilteri = alGetProcAddress("alFilteri");
    p_alGenEffects = alGetProcAddress("alGenEffects");
    p_alDeleteEffects = alGetProcAddress("alDeleteEffects");
    p_alEffecti = alGetProcAddress("alEffecti");
*/  
    checkForErrors();
    if(!p_alGenEffects || !p_alDeleteEffects || !p_alEffecti ||
       !p_alGenFilters || !p_alDeleteFilters || !p_alFilteri)
    {
        printf("Missing EFX functions!\n");
        return;
    }

    p_alGenFilters(1, &obj);
    checkForErrors();
    printf("Available filters:\n");
    for(i = 0;filters[i].type != AL_FILTER_NULL;i++)
    {
        p_alFilteri(obj, AL_FILTER_TYPE, filters[i].type);
        if(alGetError() == AL_NO_ERROR)
            printf("    %s\n", filters[i].name);
    }
    p_alDeleteFilters(1, &obj);
    checkForErrors();

    p_alGenEffects(1, &obj);
    checkForErrors();
    printf("Available effects:\n");
    for(i = 0;effects[i].type != AL_EFFECT_NULL;i++)
    {
        p_alEffecti(obj, AL_EFFECT_TYPE, effects[i].type);
        if(alGetError() == AL_NO_ERROR)
            printf("    %s\n", effects[i].name);
    }
    p_alDeleteEffects(1, &obj);
    checkForErrors();
}