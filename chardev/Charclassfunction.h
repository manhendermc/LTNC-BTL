#ifndef Charclassfunction_H_
#define Charclassfunction_H_

Character::Character()
{
    type = 0;

    mPosX = 0; mPosY = 0;
    mVelX = 0; mVelY = 0;

    degrees = 0;

    Turning_point = {0,0};
    Turning_pos = { 20, 27 };

    mouseX = 0; mouseY = 0;

    countdown = 0; shooting = 0;
}

void Character::acthandleEvent( SDL_Event &e )
{
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
       // std::cout << e.key.repeat << '\n';
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_w: mVelY -= CHAR_VEL; break;
            case SDLK_s: mVelY += CHAR_VEL; break;
            case SDLK_a: mVelX -= CHAR_VEL; break;
            case SDLK_d: mVelX += CHAR_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_w: mVelY += CHAR_VEL; break;
            case SDLK_s: mVelY -= CHAR_VEL; break;
            case SDLK_a: mVelX += CHAR_VEL; break;
            case SDLK_d: mVelX -= CHAR_VEL; break;
        }
    }

    else if(e.type == SDL_MOUSEBUTTONDOWN)
    {
        shooting = 1;
    }
    else if(e.type == SDL_MOUSEBUTTONUP)
    {
        shooting = 0;
    }
}

void Character::charcountdown()
{
    if( countdown > 0 ) countdown --;
}

void Character::charmove()
{
    mPosX += mVelX;

    //If the dot went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + CHAR_HITBOX_DIAMETER > SCREEN_WIDTH ) )
    {
        //Move back
        mPosX -= mVelX;
    }

    //Move the dot up or down
    mPosY += mVelY;

    //If the dot went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + CHAR_HITBOX_DIAMETER > SCREEN_HEIGHT ) )
    {
        //Move back
        mPosY -= mVelY;
    }

    SDL_GetMouseState( &mouseX, &mouseY );
    Turning_point = { mPosX + 27 , mPosY + 27 };
    bullet.stx = Turning_point.x ; bullet.sty = Turning_point.y;

    //cout << doubullete( y - Turning_point.y )/doubullete(x - Turning_point.x ) <<'\n';
    degrees = 1;
    if(mouseX - Turning_point.x == 0 && mouseY - Turning_point.y <= 0)  degrees = 90;
    else if (mouseX - Turning_point.x == 0 && mouseY - Turning_point.y > 0) degrees = -90;
    else degrees = atan( double( mouseY - Turning_point.y ) / double(mouseX - Turning_point.x )) * 180.0 / pi;
    if( mouseX - Turning_point.x < 0) degrees += 180;

    bullet.angle = degrees;

    if(shooting && countdown == 0 )
    {
        listbl.add ( bullet );
        countdown += FIRE_RATE;
    }
}

void Character::charrender()
{
    crt.renderCHAR( mPosX + 7, mPosY, degrees, Turning_pos);
}

void Character::gettype(bool tp)
{
    type = tp;
}

#endif // Charclassfunction_H_
