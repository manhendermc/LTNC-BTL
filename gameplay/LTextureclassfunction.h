#ifndef LTextureclassfunction_H_
#define LTextureclassfunction_H_

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF , 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::renderMAP( int x, int y)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_RenderCopy( gRenderer, mTexture, NULL, &renderQuad );
}

void LTexture::renderBULLET( int x, int y, double angle, SDL_Point tpt)
{
    SDL_Rect renderQuad = { x, y, bullet_WIDTH, bullet_HEIGHT};
    SDL_RenderCopyEx( gRenderer, mTexture, NULL, &renderQuad, angle, &tpt, SDL_FLIP_NONE);
}

void LTexture::renderCHAR( int x, int y, double angle, SDL_Point tpt)
{
    SDL_Rect renderQuad = { x, y, CHAR_WIDTH, CHAR_HEIGHT};
    SDL_RenderCopyEx( gRenderer, mTexture, NULL, &renderQuad, angle, &tpt, SDL_FLIP_NONE);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

void LTexture::renderfps( int x, int y)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set c
		renderQuad.w = 500;
		renderQuad.h = 30;

	//Render to screen
	SDL_RenderCopy( gRenderer, mTexture, NULL, &renderQuad);
}

void LTexture::renderHP(int x,int y,int w,int h)
{
    SDL_Rect renderQuad = { x, y, w, h};

    SDL_RenderCopy( gRenderer, mTexture, NULL, &renderQuad);
}

void LTexture::renderFireEffect( int x, int y, double angle, SDL_Point tpt)
{
    SDL_Rect renderQuad = { x, y, CHAR_WIDTH * 2 , CHAR_HEIGHT};
    SDL_RenderCopyEx( gRenderer, mTexture, NULL, &renderQuad, angle, &tpt, SDL_FLIP_NONE);
}

#endif // LTextureclassfunction_H_
