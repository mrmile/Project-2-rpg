#include "App.h"
#include "Window.h"

#include "Defs.h"
#include "Log.h"

// NOTE: SDL redefines main function
#include "SDL/include/SDL.h"

// NOTE: Library linkage is configured in Linker Options
//#pragma comment(lib, "../Game/Source/External/SDL/libx86/SDL2.lib")
//#pragma comment(lib, "../Game/Source/External/SDL/libx86/SDL2main.lib")

#include "Optick/include/optick.h"

#ifdef _DEBUG
#pragma comment( lib, "../Game/Source/External/Optick/lib/Debug/OptickCore.lib" )
#else 
#pragma comment( lib, "../Game/Source/External/Optick/lib/Release/OptickCore.lib" )
#endif

#ifdef _DEBUG
#pragma comment( lib, "../Game/Source/External/SDL/libx86/SDL2.lib" )
#else 
#pragma comment( lib, "../Game/Source/External/SDL/libx86/SDL2.lib" )
#endif

#ifdef _DEBUG
#pragma comment( lib, "../Game/Source/External/SDL/libx86/SDL2main.lib" )
#else 
#pragma comment( lib, "../Game/Source/External/SDL/libx86/SDL2main.lib" )
#endif

#ifdef _DEBUG
#pragma comment( lib, "../Game/Source/External/SDL_image/libx86/SDL2_image.lib" )
#else 
#pragma comment( lib, "../Game/Source/External/SDL_image/libx86/SDL2_image.lib" )
#endif


#ifdef _DEBUG
#pragma comment( lib, "../Game/Source/External/SDL_mixer/libx86/SDL2_mixer.lib" )
#else 
#pragma comment( lib, "../Game/Source/External/SDL_mixer/libx86/SDL2_mixer.lib" )
#endif


#include <stdlib.h>

enum MainState
{
	CREATE = 1,
	AWAKE,
	START,
	LOOP,
	CLEAN,
	FAIL,
	EXIT
};

App* app = NULL;

int main(int argc, char* args[])
{
	LOG("Engine starting ...");

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint64 frameStart;
	int frameTime;

	MainState state = CREATE;
	int result = EXIT_FAILURE;

	while(state != EXIT)
	{
		switch(state)
		{
			// Allocate the engine --------------------------------------------
			case CREATE:
			{
				LOG("CREATION PHASE ===============================");

				app = new App(argc, args);

				if (app != NULL)
					state = AWAKE;
				else
					state = FAIL;
				break;
			}

			

			// Awake all modules -----------------------------------------------
			case AWAKE:
			{
				LOG("AWAKE PHASE ===============================");
				if (app->Awake() == true)
					state = START;
				else
				{
					LOG("ERROR: Awake failed");
					state = FAIL;
				}

				break;
			}

			// Call all modules before first frame  ----------------------------
			case START:
			{
				LOG("START PHASE ===============================");
				if (app->Start() == true)
				{
					state = LOOP;
					LOG("UPDATE PHASE ===============================");
				}
				else
				{
					state = FAIL;
					LOG("ERROR: Start failed");
				}
				break;

				// Loop all modules until we are asked to leave ---------------------
			}
			case LOOP:
			{
				OPTICK_FRAME("Main Loop");
				frameStart = SDL_GetTicks();

				if (app->Update() == false)
					state = CLEAN;

				frameTime = SDL_GetTicks() - frameStart;

				if (frameDelay > frameTime)
				{
					SDL_Delay(frameDelay - frameTime);
				}
				
				if (app->AppTitleScreenFull == false)
				{
					//SDL_SetWindowSize(app->win->window, 1280, 720); <-- Ya se hace desde el XML
					SDL_SetWindowFullscreen(app->win->window, 0);
				}
				else if (app->AppTitleScreenFull == true)
				{
					SDL_SetWindowFullscreen(app->win->window, SDL_WINDOW_FULLSCREEN);
					
				}

				break;
			}

			// Cleanup allocated memory -----------------------------------------
			case CLEAN:
			{
				LOG("CLEANUP PHASE ===============================");
				if (app->CleanUp() == true)
				{
					RELEASE(app);
					result = EXIT_SUCCESS;
					state = EXIT;
				}
				else
					state = FAIL;

				break;
			}

			// Exit with errors and shame ---------------------------------------
			case FAIL:
			{
				LOG("Exiting with errors :(");
				result = EXIT_FAILURE;
				state = EXIT;
				break;
			}
		}
	}

	LOG("... Bye! :)\n");

	// Dump memory leaks
	return result;
}