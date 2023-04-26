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
#include <algorithm>
#include <cstdlib> // for rand() and srand()
#include <ctime>
#include <SDL_mixer.h>

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 1400;
const int SCREEN_HEIGHT = 700;
const int CHAR_WIDTH = 60;
const int CHAR_HEIGHT = 60;
const int bullet_WIDTH = 80;
const int bullet_HEIGHT = 27;
const int SCREEN_FPS = 60;
const int FIRE_RATE = 6;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;
const double pi = 3.141592653589793238462643383279;
const int tilemap_WIDTH = 40;
const int tilemap_HEIGHT = 20;
const int square_SIZE = SCREEN_HEIGHT / tilemap_HEIGHT;
const int TOTAL_ENEMY = 5;
const int bullet_VEL = 44;
const int TEXT_HEIGHT = 45;
const int TEXT_WIDTH = 20;

bool tile[44][44];
bool charvision[TOTAL_ENEMY];
bool enemyvision[TOTAL_ENEMY];
int enemyalive;
int type = 0;
string s;

//INIT WINDOWN:
//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

TTF_Font* gFont = NULL;

Mix_Chunk *fire_sound = NULL;

Mix_Chunk *ouch_sound = NULL;

Mix_Chunk *reloading_sound = NULL;

Mix_Chunk *click_sound = NULL;

Mix_Chunk *victory_sound = NULL;

Mix_Chunk *defeat_sound = NULL;

//Starts up SDL and creates window
bool init();
#include "init.h"

struct bulletstate
{
    double x=0,y=0;
    double stx = 0, sty = 0;
    int dis = 0;
    double angle = 0;
    bool state = 0;
    bool shooter = 0;
};

struct tilemap_POS
{
    int x = 0;
    int y = 0;
};

#include "collision.h"

#include "LTextureclass.h"//class LTexture
#include "LTextureclassfunction.h"

//init texture
LTexture crt;
LTexture background;
LTexture mbullet;
LTexture gBackgroundTexture;
LTexture gFPSTextTexture;
LTexture object;
LTexture EnemyTexture;
LTexture HPTexture;
LTexture FireEffectTexture;
LTexture HPiconTexture;
LTexture BULLETiconTexture;
LTexture ENEMYiconTexture;
LTexture MENUTexture;
LTexture MENU_TEXTTexture;
LTexture BUTTON_EFFECTTexture;
LTexture TUTORIALTexture;
LTexture TUTORIAL_TEXTTexture;
LTexture VICTORYTexture;
LTexture ENDGAME_TEXTTextute;
LTexture DEFEATTexture;
LTexture PAUSETexture;
LTexture PAUSE_BUTTONTexture;
LTexture PAUSE_EFFECTTexture;
LTexture PAUSE_BUTTON1Texture;

#include "bulletclass.h"//class bulletcontrol

//init bullet handle queue
bulletcontrol listbl;

#include "Charclass.h"//class Charater
#include "Enemy.h"

Character mainchar;
Enemy p[TOTAL_ENEMY];

#include "Buttonclass.h"

Buttonclass menu_play, menu_tutorial, menu_exit;
Buttonclass tutorial_back;
Buttonclass endgame_replay, endgame_quit;
Buttonclass play_pause;
Buttonclass pause_resume, pause_quit;

#include "Buttonclassfunction.h"

#include "bulletclassfunction.h"
#include "Charclassfunction.h"
#include "Enemyclassfunction.h"

#include "set_position.h"
#include "reset.h"
#include "Button_init.h"
#include "checkvision.h"
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
	EnemyTexture.free();
	gFPSTextTexture.free();
	object.free();
	HPTexture.free();
	FireEffectTexture.free();
	HPiconTexture.free();
	BULLETiconTexture.free();
	ENEMYiconTexture.free();
	MENUTexture.free();
    MENU_TEXTTexture.free();
    BUTTON_EFFECTTexture.free();
    VICTORYTexture.free();
    ENDGAME_TEXTTextute.free();
    DEFEATTexture.free();
    PAUSETexture.free();
    PAUSE_EFFECTTexture.free();
    PAUSE_BUTTONTexture.free();
    PAUSE_BUTTON1Texture.free();

	Mix_FreeChunk( fire_sound );
	fire_sound = NULL;
	Mix_FreeChunk( ouch_sound );
	ouch_sound = NULL;
	Mix_FreeChunk(click_sound);
	click_sound = NULL;
	Mix_FreeChunk( victory_sound );
	victory_sound = NULL;
	Mix_FreeChunk( defeat_sound);
	defeat_sound = NULL;

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
	Mix_Quit();
}

int main( int argc, char* args[] )
{
    addobject();
    posinit();
    enemyalive = TOTAL_ENEMY;
    srand(time(NULL));
    button_init();

    //memset( charvision, true, sizeof (charvision));
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

			LTimer fpsTimer;

			LTimer capTimer;

			std::stringstream timeText, HP;
			SDL_Color textColor = { 0, 0, 0, 0 };

			int countedFrames = 0;
			fpsTimer.start();

			//While application is running
			while( !quit )
			{
			    capTimer.start();

			    //Calculate and correct fps

			    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
                    SDL_RenderClear( gRenderer );

			    float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
				if( avgFPS > 2000000 )
				{
					avgFPS = 0;
				}
/*
				while( SDL_PollEvent( &e ) != 0 )
				{
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//Handle input for the dot
					//mainchar.acthandleEvent( e );
				}*/

				if(type == 0)
                {
                    //menu game
                    MENUTexture.renderMAP(0,0);

                    if( menu_play.check_BUTTON() )menu_play.renderBUTTON_Effect();
                    else if ( menu_tutorial.check_BUTTON() )menu_tutorial.renderBUTTON_Effect();
                    else if ( menu_exit.check_BUTTON() )menu_exit.renderBUTTON_Effect();

                    MENU_TEXTTexture.renderMAP(0,0);

                    while( SDL_PollEvent( &e ) != 0 )
                    {
                        if( e.type == SDL_QUIT )
					    {
                            quit = true;
					    }
                        if(e.type == SDL_MOUSEBUTTONDOWN)
                        {
                            if( menu_play.check_BUTTON() )type = menu_play.get_link(), Mix_PlayChannel(-1,click_sound,0);
                            else if ( menu_tutorial.check_BUTTON() )type = menu_tutorial.get_link(), Mix_PlayChannel(-1,click_sound,0);
                            else if ( menu_exit.check_BUTTON() )type = menu_exit.get_link(), Mix_PlayChannel(-1,click_sound,0);
                        }

                    }



                }
                else if(type == 2)
                {
                    //tutorial

                    TUTORIALTexture.renderMAP(0,0);

                    if( tutorial_back.check_BUTTON() )tutorial_back.renderBUTTON_Effect();

                    TUTORIAL_TEXTTexture.renderMAP(0,0);

                    while( SDL_PollEvent( &e ) != 0 )
                    {
                        if( e.type == SDL_QUIT )
					    {
                            quit = true;
					    }
                        if(e.type == SDL_MOUSEBUTTONDOWN)
                        {
                            if( tutorial_back.check_BUTTON() )type = tutorial_back.get_link(), Mix_PlayChannel(-1,click_sound,0);
                        }

                    }
                }
                else if(type == 3)
                {
                    //exit

                    quit = true;
                }
                else if(type == 4|| type == 1)
                {
                    //gameplay
                    if(type == 4){
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

                        check_vision();
                        //memset (charvision, 1, sizeof charvision);

                        for(int i = 0;i < TOTAL_ENEMY;i ++)
                        p[i].charmove();
                    }





                    //timeText.str( "" );
                    //timeText << "Average Frames Per Second (With Cap) " << avgFPS;

                    //Render text

                    /*if( !gFPSTextTexture.loadFromRenderedText( timeText.str().c_str(), textColor ) )
                    {
                            printf( "Unable to render FPS texture!\n" );
                    }*/

                    //Clear screen
                    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
                    SDL_RenderClear( gRenderer );

                    background.renderMAP(0, 0);

                    mainchar.aiming_line();
                    if(type == 4)listbl.move();//locate all bullet new pos

                    //Render objects
                    mainchar.charrender();

                    //cout << mainchar.get_hp()<< endl;

                    for(int i = 0;i < TOTAL_ENEMY;i ++)
                    if(charvision[i] && p[i].get_hp() > 0)
                    {
                        p[i].charrender();
                    }

                    object.renderMAP(0,0);

                    if(type == 4)
                    {
                        mainchar.charcountdown();
                        for(int i = 0;i < TOTAL_ENEMY;i ++)
                            p[i].charcountdown();

                        if(mainchar.get_hp() == 0)
                        {
                            type = 5;
                            reset();
                            SDL_Delay(70);
                            Mix_PlayChannel(-1, defeat_sound, 0);
                        }
                        else if(enemyalive == 0)
                        {
                            type = 6;
                            reset();
                            SDL_Delay(70);
                            Mix_PlayChannel(-1, victory_sound, 0);
                        }

                    }

                    HP.str("");
                    HP << mainchar.get_hp();

                    textColor = {255, 255, 255, 255};
                    if( !HPTexture.loadFromRenderedText( HP.str().c_str(), textColor ) )
                    {
                        printf( "Unable to render HP texture!\n" );
                    }

                    HPTexture.renderHP( 60, 20, HP.str().size() * TEXT_WIDTH, TEXT_HEIGHT + 5);

                    HPiconTexture.renderHPicon( -20, -10 , 100, 100);

                    //render bullet icon

                    textColor = {255, 255, 255, 255};
                    HP.str("");
                    if(mainchar.get_reloadstate() == 0)HP << mainchar.get_bullet() ;/*<< "          ";*/
                    else
                    {
                        HP << "RELOADING...";
                    }

                    if( mainchar.get_bullet() <= 5 || mainchar.get_reloadstate()) textColor = {255, 0, 0, 180};
                    if( !HPTexture.loadFromRenderedText( HP.str().c_str(), textColor ) )
                    {
                        printf( "Unable to render HP texture!\n" );
                    }

                    HPTexture.renderHP( 63, 80, HP.str().size() * TEXT_WIDTH + 5, TEXT_HEIGHT);

                    BULLETiconTexture.renderHPicon( -5, 70 , 70, 70);


                    HP.str("");
                    HP << enemyalive;

                    textColor = {255, 255, 255, 255};
                    if( !HPTexture.loadFromRenderedText( HP.str().c_str(), textColor ) )
                    {
                        printf( "Unable to render HP texture!\n" );
                    }

                    HPTexture.renderHP( 60, 130, HP.str().size() * TEXT_WIDTH, TEXT_HEIGHT + 10);

                    ENEMYiconTexture.renderHPicon( 0, 130 , 60, 60);


                    if(play_pause.check_BUTTON())
                        PAUSE_BUTTON1Texture.renderHPicon( 690, 5, 50, 50 );
                    else
                        PAUSE_BUTTONTexture.renderHPicon( 690, 5, 50, 50 );
                }
                else if(type == 5)
                {
                    //defeat

                    DEFEATTexture.renderMAP(0,0);

                    if( endgame_quit.check_BUTTON() )endgame_quit.renderBUTTON_Effect();
                    if( endgame_replay.check_BUTTON() ) endgame_replay.renderBUTTON_Effect();

                    ENDGAME_TEXTTextute.renderMAP(0,0);

                     while( SDL_PollEvent( &e ) != 0 )
                    {
                        if( e.type == SDL_QUIT )
					    {
                            quit = true;
					    }
                        if(e.type == SDL_MOUSEBUTTONDOWN)
                        {
                            if( endgame_quit.check_BUTTON() )type = endgame_quit.get_link(), Mix_PlayChannel(-1,click_sound,0);
                            if( endgame_replay.check_BUTTON() ) type = endgame_replay.get_link(), Mix_PlayChannel(-1,click_sound,0);
                        }

                    }
                }
                else if(type == 6)
                {
                    //victory

                    VICTORYTexture.renderMAP(0,0);

                    if( endgame_quit.check_BUTTON() )endgame_quit.renderBUTTON_Effect();
                    if( endgame_replay.check_BUTTON() ) endgame_replay.renderBUTTON_Effect();

                    ENDGAME_TEXTTextute.renderMAP(0,0);

                    while( SDL_PollEvent( &e ) != 0 )
                    {
                        if( e.type == SDL_QUIT )
					    {
                            quit = true;
					    }
                        if(e.type == SDL_MOUSEBUTTONDOWN)
                        {
                            if( endgame_quit.check_BUTTON() )type = endgame_quit.get_link(), Mix_PlayChannel(-1,click_sound,0);
                            if( endgame_replay.check_BUTTON() ) type = endgame_replay.get_link(), Mix_PlayChannel(-1,click_sound,0);
                        }

                    }
                }

                if(type == 1)
                {
                    //pause

                    PAUSETexture.renderMAP(0,0);
                    if( pause_quit.check_BUTTON() )pause_quit.renderPAUSE_EFFECT();
                    if( pause_resume.check_BUTTON() ) pause_resume.renderPAUSE_EFFECT();

                    while( SDL_PollEvent( &e ) != 0 )
                    {
                        if( e.type == SDL_QUIT )
					    {
                            quit = true;
					    }

                        if(e.type == SDL_MOUSEBUTTONDOWN)
                        {
                            if( pause_quit.check_BUTTON() )
                            {
                                Mix_PlayChannel(-1,click_sound,0);
                                type = pause_quit.get_link();
                                reset();
                            }
                            if( pause_resume.check_BUTTON() ) type = pause_resume.get_link(), Mix_PlayChannel(-1,click_sound,0);
                        }

                    }
                }



                    //gFPSTextTexture.renderfps( ( SCREEN_WIDTH - gFPSTextTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gFPSTextTexture.getHeight() ) / 2 );

/*


                //timeText.str( "" );
				//timeText << "Average Frames Per Second (With Cap) " << avgFPS;

				//Render text

				/*if( !gFPSTextTexture.loadFromRenderedText( timeText.str().c_str(), textColor ) )
				{
					printf( "Unable to render FPS texture!\n" );
				}
				//Clear screen

				*/

                SDL_RenderPresent( gRenderer );

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
