#ifndef loadmedia_H_
#define loadmedia_H_

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load Foo' texture
	if( !crt.loadFromFile( "rifle.png" ) )
	{
		printf( "Failed to load crt' texture image!\n" );
		success = false;
	}

	if( !FireEffectTexture.loadFromFile( "fire_effect.png" ) )
	{
		printf( "Failed to load crt' texture image!\n" );
		success = false;
	}

    if( !mbullet.loadFromFile( "bullet2.png" ) )
	{
		printf( "Failed to load bullet' texture image!\n" );
		success = false;
	}

	if( !EnemyTexture.loadFromFile( "Enemy.png" ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}

	gFont = TTF_OpenFont( "TrueTypeFont/Vector Sigma Italic.ttf", 50 );
	if( gFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	//Load background texture
	if( !background.loadFromFile( "map.png" ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}

	if( !object.loadFromFile( "object_remake.png" ) )
    {
        printf( "Failed to load background texture image!\n" );
		success = false;
    }

    if( !BULLETiconTexture.loadFromFile( "bulleticon.png" ) )
    {
        printf( "Failed to load background texture image!\n" );
		success = false;
    }

    if( !ENEMYiconTexture.loadFromFile( "enemyicon.png" ) )
    {
        printf( "Failed to load enemyicon texture image!\n" );
		success = false;
    }

    if( !MENUTexture.loadFromFile( "menu.png" ) )
    {
        printf( "Failed to load menu texture image!\n" );
		success = false;
    }

    if( !MENU_TEXTTexture.loadFromFile( "menu_text.png" ) )
    {
        printf( "Failed to load menu text texture image!\n" );
		success = false;
    }

    if( !BUTTON_EFFECTTexture.loadFromFile( "button_effect.png" ) )
    {
        printf( "Failed to load button_effect texture image!\n" );
		success = false;
    }

    if( !TUTORIALTexture.loadFromFile( "tutorial.png" ) )
    {
        printf( "Failed to load tutorial texture image!\n" );
		success = false;
    }

    if( !TUTORIAL_TEXTTexture.loadFromFile( "tutorial_text.png" ) )
    {
        printf( "Failed to load button_effect texture image!\n" );
		success = false;
    }

    if( !VICTORYTexture.loadFromFile( "victory.png" ) )
    {
        printf( "Failed to load button_effect texture image!\n" );
		success = false;
    }

    if( !DEFEATTexture.loadFromFile( "defeat.png" ) )
    {
        printf( "Failed to load button_effect texture image!\n" );
		success = false;
    }

    if( !ENDGAME_TEXTTextute.loadFromFile( "endgame_text.png" ) )
    {
        printf( "Failed to load button_effect texture image!\n" );
		success = false;
    }

    if( !PAUSETexture.loadFromFile( "PAUSE.png" ) )
    {
        printf( "Failed to load button_effect texture image!\n" );
		success = false;
    }

    if( !PAUSE_EFFECTTexture.loadFromFile( "PAUSE_EFFECT.png" ) )
    {
        printf( "Failed to load button_effect texture image!\n" );
		success = false;
    }

    if( !PAUSE_BUTTONTexture.loadFromFile( "PAUSE_BUTTON.png" ) )
    {
        printf( "Failed to load button_effect texture image!\n" );
		success = false;
    }

    if( !PAUSE_BUTTON1Texture.loadFromFile( "PAUSE_BUTTON1.png" ) )
    {
        printf( "Failed to load button_effect texture image!\n" );
		success = false;
    }

    fire_sound = Mix_LoadWAV( "firesound.wav" );
	if( fire_sound == NULL )
	{
		printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	ouch_sound = Mix_LoadWAV( "ouch.wav" );
	if( ouch_sound == NULL )
	{
		printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

    reloading_sound = Mix_LoadWAV( "reloading_sound.wav" );
	if( reloading_sound == NULL )
	{
		printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	click_sound = Mix_LoadWAV( "click_sound.mp3" );
	if( click_sound == NULL )
	{
		printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	victory_sound = Mix_LoadWAV( "victory_sound.mp3" );
	if( victory_sound == NULL )
	{
		printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

    defeat_sound = Mix_LoadWAV( "fail_sound.wav" );
	if( defeat_sound == NULL )
	{
		printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	if( !HPiconTexture.loadFromFile( "hp.png" ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}

	return success;
}

#endif // loadmedia_H_
