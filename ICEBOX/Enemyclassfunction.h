#ifndef Enemyclassfunction_H_
#define ENemyclassfunction_H_

Enemy::Enemy()
{
    hp = 100;
    mPosX = 700; mPosY = 100;
    ind = 0;

    default_degrees = 0;
    degrees = 0;


    Turning_point = {0, 0};
    Turning_pos = { CHAR_WIDTH / 3, CHAR_HEIGHT / 2 };

    flick_countdown = 0; bullet_cnt = 0;aware_countdown = 0;

    countdown = 0; shooting = 0;
}

void Enemy::reset()
{
    hp = 100;
    mPosX = 700; mPosY = 100;
    ind = 0;

    default_degrees = 0;
    degrees = 0;


    Turning_point = {0, 0};
    Turning_pos = { CHAR_WIDTH / 3, CHAR_HEIGHT / 2 };

    flick_countdown = 0; bullet_cnt = 0;aware_countdown = 0;

    countdown = 0; shooting = 0;
}

void Enemy::charmove()
{
    //cout << ind << " " << enemyvision[ind] << endl ;
    degrees = fix_degrees(degrees);
    SDL_Point pt{mPosX, mPosY};
    double angle = get_angle( pt, mainchar.get_mPos());
    double Dangle = abs(angle - degrees);
    Dangle = min(Dangle, 360 - Dangle);

    if(enemyvision[ind]) aware_countdown = AWARE_TIME;
    if(flick_countdown == 0 && bullet_cnt == 0 && enemyvision[ind])flick_countdown = REACT_TIME + min(15,int(Dangle)) / 5 * FLICK_TPD, bullet_cnt = 3;
    if( bullet_cnt == 3 && flick_countdown == REACT_TIME && enemyvision[ind])
    {
        degrees = angle;
    }

    if(bullet_cnt > 0 && flick_countdown == 0 && enemyvision[ind] && countdown == 0)
    {
        bullet.angle = degrees;
        bullet.x = mPosX; bullet.y = mPosY;
        bullet.stx = cos(bullet.angle / 180 * pi) * double(bullet_VEL);
        bullet.sty = sin(bullet.angle / 180 * pi) * double(bullet_VEL);
        bullet.shooter = 1;

        listbl.add ( bullet );
        countdown += FIRE_RATE;

        bullet_cnt --;

        Mix_PlayChannel( -1, fire_sound, 0);
    }

    if( !enemyvision[ind] && aware_countdown == AWARE_TIME - 1 ) degrees = angle;
    if( !enemyvision[ind] )bullet_cnt = 0;
    if( aware_countdown == 0 )degrees = default_degrees, bullet_cnt = 0;
}

void Enemy::charcountdown()
{
    if( countdown > 0)countdown --;
    if( aware_countdown > 0) aware_countdown --;
    if( flick_countdown > 0) flick_countdown --;
}

void Enemy::charrender()
{
    /*SDL_Point ed = line( mPosX, mPosY, degrees);

    SDL_SetRenderDrawBlendMode( gRenderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x82, 0xFF );
   // SDL_RenderDrawLine( gRenderer, mPosX, mPosY, ed.x, ed.y);*/

    EnemyTexture.renderCHAR( mPosX - CHAR_WIDTH / 3, mPosY - CHAR_HEIGHT / 2, degrees, Turning_pos );
    Turning_pos.y -= 3;
    if( countdown == FIRE_RATE ) FireEffectTexture.renderFireEffect(mPosX - CHAR_WIDTH / 3, mPosY - CHAR_HEIGHT / 2 + 3, degrees, Turning_pos);
    Turning_pos.y += 3;
}

void Enemy::setpos(int x, int y, double angle,int id)
{
    mPosX = x; mPosY = y; default_degrees = angle; ind = id;
    degrees = default_degrees;
}



#endif // Enemyclassfunction_H_
