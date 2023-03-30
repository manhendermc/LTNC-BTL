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

    if( !mbullet.loadFromFile( "bullet2.png" ) )
	{
		printf( "Failed to load bullet' texture image!\n" );
		success = false;
	}

	gFont = TTF_OpenFont( "lazy.ttf", 28 );
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

	return success;
}

#endif // loadmedia_H_
