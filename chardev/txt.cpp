//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <queue>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 1400;
const int SCREEN_HEIGHT = 700;
const int CHAR_WIDTH = 60;
const int CHAR_HEIGHT = 60;
const int bullet_WIDTH = 60;
const int bullet_HEIGHT = 10;
const int SCREEN_FPS = 60;
const int FIRE_RATE = 7;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;
const double pi = 3.141592653589793238462643383279;

//INIT WINDOWN:
//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

TTF_Font* gFont = NULL;

//Starts up SDL and creates window
bool init();
#include "init.h"

struct bulletstate
{
    int x=0,y=0;
    int stx = 0, sty = 0;
    int dis = 0;
    double angle = 0;
    bool state = 0;
    bool shooter = 0;
};

#include "LTextureclass.h"//class LTexture
#include "LTextureclassfunction.h"

//init texture
LTexture crt;
LTexture background;
LTexture mbullet;
LTexture gBackgroundTexture;
LTexture gFPSTextTexture;
LTexture object;

#include "bulletclass.h"//class bulletcontrol
#include "bulletclassfunction.h"

//init bullet handle queue
bulletcontrol listbl;

#include "Charclass.h"//class Charater
#include "Charclassfunction.h"


#include "LTimerclass.h"

#include "loadmedia.h"

void close()
{
    //Free loaded images
	listbl.deletelist();
	background.free();
	crt.free();
	mbullet.free();
	gBackgroundTexture.free();
	gFPSTextTexture.free();
	object.free();

	TTF_CloseFont( gFont );
	gFont = NULL;

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
    if( !init() )
    {
        printf( "Fail to initialize!\n" );
    }
    else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			Character mainchar;

			LTimer fpsTimer;

			LTimer capTimer;

			std::stringstream timeText;
			SDL_Color textColor = { 0, 0, 0, 255 };

			int countedFrames = 0;
			fpsTimer.start();

			//While application is running
			while( !quit )
			{
			    capTimer.start();

				while( SDL_PollEvent( &e ) != 0 )
				{
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//Handle input for the dot
					mainchar.acthandleEvent( e );
				}

                //Move the dot
				mainchar.charmove();

				//Calculate and correct fps
				float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
				if( avgFPS > 2000000 )
				{
					avgFPS = 0;
				}

                //timeText.str( "" );
				//timeText << "Average Frames Per Second (With Cap) " << avgFPS;

				//Render text
				/*
				if( !gFPSTextTexture.loadFromRenderedText( timeText.str().c_str(), textColor ) )
				{
					printf( "Unable to render FPS texture!\n" );
				}*/

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
				SDL_RenderClear( gRenderer );

                background.renderMAP(0,0);

                listbl.move();//locate all bullet new pos



				//Render objects
				mainchar.charrender();

				mainchar.charcountdown();

				object.renderMAP(0,0);

				//gFPSTextTexture.renderfps( ( SCREEN_WIDTH - gFPSTextTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gFPSTextTexture.getHeight() ) / 2 );

				//Update screen
				SDL_RenderPresent( gRenderer );

				//SDL_Delay(500);
				++countedFrames;

				//If frame finished early
				int frameTicks = capTimer.getTicks();
				if( frameTicks < SCREEN_TICK_PER_FRAME )
				{
					//Wait remaining time
					SDL_Delay(max( 0, SCREEN_TICK_PER_FRAME - frameTicks ));
				}
			}
		}
	}

	//Free resources and close SDL
	close();


}
