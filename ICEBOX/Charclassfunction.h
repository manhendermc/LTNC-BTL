#ifndef Charclassfunction_H_
#define Charclassfunction_H_

Character::Character()
{
    mPosX = 50; mPosY = 620;
    mVelX = 0; mVelY = 0;

    hp = 100;

    degrees = 0;

    Turning_point = {0,0};
    Turning_pos = { 20, 27 };

    mouseX = 0; mouseY = 0;

    reload_countdown = 0;
    recoil_countdown = 0;

    countdown = 0; shooting = 0; reloading = 0; bullet_remaining = TOTAL_BULLET; reload_cnt = 0;
}

void Character::reset()
{
     mPosX = 50; mPosY = 620;
    mVelX = 0; mVelY = 0;

    hp = 100;

    degrees = 0;

    Turning_point = {0,0};
    Turning_pos = { 20, 27 };

    mouseX = 0; mouseY = 0;

    reload_countdown = 0;
    recoil_countdown = 0;

    countdown = 0; shooting = 0; reloading = 0; bullet_remaining = TOTAL_BULLET; reload_cnt = 0;
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

    if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_r && reloading == 0)
    {
        reloading = 1;
    }

    if(e.type == SDL_MOUSEBUTTONDOWN && play_pause.check_BUTTON())
    {
        type = 1;
        Mix_PlayChannel(-1, click_sound, 0);
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

bool Character::check_collision()
{
    nowpos = getlocate( mPosX + CHAR_HITBOX_RADIUS, mPosY + CHAR_HITBOX_RADIUS);

    if( tile[nowpos.x][nowpos.y] ) return 1;

    int x1 = (nowpos.x - 1) * square_SIZE;
    int y1 = (nowpos.y - 1) * square_SIZE;
    int x2 = nowpos.x * square_SIZE;
    int y2 = nowpos.y * square_SIZE;

    if( mVelX > 0 && mVelY == 0 && !tile[nowpos.x+1][nowpos.y])
    {
        if(tile[nowpos.x + 1][nowpos.y - 1] && CHAR_HITBOX_DIS >= dis( x2, y1, mPosX + CHAR_HITBOX_RADIUS, mPosY + CHAR_HITBOX_RADIUS))
            mPosY = y1 + CHAR_HITBOX_DIS - CHAR_HITBOX_RADIUS;
        else if (tile[nowpos.x + 1][nowpos.y + 1] && CHAR_HITBOX_DIS >= dis( x2, y2, mPosX + CHAR_HITBOX_RADIUS, mPosY + CHAR_HITBOX_RADIUS))
            mPosY = y2 - CHAR_HITBOX_DIS - CHAR_HITBOX_RADIUS;
    }
    if( mVelX < 0 && mVelY == 0 && !tile[nowpos.x - 1][nowpos.y])
    {
        if(tile[nowpos.x - 1][nowpos.y - 1] && CHAR_HITBOX_DIS >= dis( x1, y1, mPosX + CHAR_HITBOX_RADIUS, mPosY + CHAR_HITBOX_RADIUS))
            mPosY = y1 + CHAR_HITBOX_DIS - CHAR_HITBOX_RADIUS;
        else if (tile[nowpos.x - 1][nowpos.y + 1] && CHAR_HITBOX_DIS >= dis( x1, y2, mPosX + CHAR_HITBOX_RADIUS, mPosY + CHAR_HITBOX_RADIUS))
            mPosY = y2 - CHAR_HITBOX_DIS - CHAR_HITBOX_RADIUS;
    }
    if( mVelY < 0 && mVelX == 0 && !tile[nowpos.x][nowpos.y-1] )
    {
        if(tile[nowpos.x - 1][nowpos.y - 1] && CHAR_HITBOX_DIS >= dis( x1, y1, mPosX + CHAR_HITBOX_RADIUS, mPosY + CHAR_HITBOX_RADIUS))
            mPosX = x1 + CHAR_HITBOX_DIS - CHAR_HITBOX_RADIUS;
        else if(tile[nowpos.x + 1][nowpos.y - 1] && CHAR_HITBOX_DIS >= dis( x2, y1, mPosX + CHAR_HITBOX_RADIUS, mPosY + CHAR_HITBOX_RADIUS))
            mPosX = x2 - CHAR_HITBOX_DIS - CHAR_HITBOX_RADIUS;
    }
    if( mVelY > 0 && mVelX == 0 && !tile[nowpos.x][nowpos.y + 1] )
    {
        if(tile[nowpos.x - 1][nowpos.y + 1] && CHAR_HITBOX_DIS >= dis( x1, y2, mPosX + CHAR_HITBOX_RADIUS, mPosY + CHAR_HITBOX_RADIUS))
            mPosX = x1 + CHAR_HITBOX_DIS - CHAR_HITBOX_RADIUS;
        else if(tile[nowpos.x + 1][nowpos.y + 1] && CHAR_HITBOX_DIS >= dis( x2, y2, mPosX + CHAR_HITBOX_RADIUS, mPosY + CHAR_HITBOX_RADIUS))
            mPosX = x2 - CHAR_HITBOX_DIS - CHAR_HITBOX_RADIUS;
    }

    bool ans = 0;
    ans |= (tile[nowpos.x - 1][nowpos.y - 1] && CHAR_HITBOX_DIS > dis( x1, y1, mPosX + CHAR_HITBOX_RADIUS, mPosY + CHAR_HITBOX_RADIUS));
    ans |= (tile[nowpos.x][nowpos.y - 1] && CHAR_HITBOX_DIS > dis( mPosX + CHAR_HITBOX_RADIUS, y1, mPosX + CHAR_HITBOX_RADIUS, mPosY + CHAR_HITBOX_RADIUS));
    ans |= (tile[nowpos.x + 1][nowpos.y - 1] && CHAR_HITBOX_DIS > dis( x2, y1, mPosX + CHAR_HITBOX_RADIUS, mPosY + CHAR_HITBOX_RADIUS));
    ans |= (tile[nowpos.x - 1][nowpos.y] && CHAR_HITBOX_DIS > dis( x1, mPosY + CHAR_HITBOX_RADIUS, mPosX + CHAR_HITBOX_RADIUS, mPosY + CHAR_HITBOX_RADIUS));
    ans |= (tile[nowpos.x + 1][nowpos.y] && CHAR_HITBOX_DIS > dis( x2, mPosY + CHAR_HITBOX_RADIUS, mPosX + CHAR_HITBOX_RADIUS, mPosY + CHAR_HITBOX_RADIUS));
    ans |= (tile[nowpos.x - 1][nowpos.y + 1] && CHAR_HITBOX_DIS > dis( x1, y2, mPosX + CHAR_HITBOX_RADIUS, mPosY + CHAR_HITBOX_RADIUS));
    ans |= (tile[nowpos.x][nowpos.y + 1] && CHAR_HITBOX_DIS > dis( mPosX + CHAR_HITBOX_RADIUS, y2, mPosX + CHAR_HITBOX_RADIUS, mPosY + CHAR_HITBOX_RADIUS));
    ans |= (tile[nowpos.x + 1][nowpos.y + 1] && CHAR_HITBOX_DIS > dis( x2, y2, mPosX + CHAR_HITBOX_RADIUS, mPosY + CHAR_HITBOX_RADIUS));

    return ans;
}

void Character::charcountdown()
{
    if( countdown > 0 ) countdown --;
    if( reload_countdown > 0)reload_countdown --;
    if( recoil_countdown > 0 && countdown == 0 )recoil_countdown --;
}

void Character::charmove()
{
    mPosX += mVelX;

    //If the dot went too far to the left or right
    if( check_collision() )
    {
        //Move back
        mPosX -= mVelX;
    }

    //Move the dot up or down
    mPosY += mVelY;

    //If the dot went too far up or down
    if( check_collision() )
    {
        //Move back
        mPosY -= mVelY;
    }

    SDL_GetMouseState( &mouseX, &mouseY );
    Turning_point = { mPosX + 27 , mPosY + 27 };
    bullet.x = Turning_point.x ; bullet.y = Turning_point.y;

    //cout << doubullete( y - Turning_point.y )/doubullete(x - Turning_point.x ) <<'\n';
    degrees = 1;
    if(mouseX - Turning_point.x == 0 && mouseY - Turning_point.y <= 0)  degrees = -90;
    else if ( mouseX - Turning_point.x == 0 && mouseY - Turning_point.y > 0) degrees = 90;
    else degrees = atan( double( mouseY - Turning_point.y ) / double(mouseX - Turning_point.x )) * 180.0 / pi;
    if( mouseX - Turning_point.x < 0 && mouseY - Turning_point.y >= 0)
        degrees += 180;
    else if( mouseX - Turning_point.x < 0 && mouseY - Turning_point.y < 0)
        degrees -= 180;


    if( mVelX == 0 && mVelY == 0 && recoil_countdown < 2*RECOIL )bullet.angle = degrees;
    else
    {
        //srand(time(NULL));
        bullet.angle = fix_degrees( degrees + (rand()%41 - 20));
    }
    bullet.stx = cos(bullet.angle / 180 * pi) * double(bullet_VEL);
    bullet.x += bullet.stx;
    bullet.sty = sin(bullet.angle / 180 * pi) * double(bullet_VEL);
    bullet.y += bullet.sty;

    if(shooting && bullet_remaining != 0 && countdown == 0 && !reloading)
    {
        listbl.add ( bullet );
        countdown += FIRE_RATE;
        recoil_countdown += RECOIL;
        bullet_remaining --;
        if(bullet_remaining == 0)reloading = 1;

        Mix_PlayChannel( -1, fire_sound, 0);
    }

    //cout << degrees <<endl;
}

void Character::charrender()
{
    if( reloading && reload_cnt == 0)Mix_PlayChannel( -1, reloading_sound, 0 );
    if( reloading == 1 && reload_countdown == 0)reload_cnt ++, reload_countdown = RELOAD_CNT;
    if( reload_cnt == RELOAD_TOTAL ){ reload_cnt = 0; reloading = 0; bullet_remaining = TOTAL_BULLET;}
    stringstream ss;
    ss << reload_cnt;

    string s = "reload - Copy/survivor-reload_rifle_" + ss.str() + ".png";

    if(!crt.loadFromFile(s))
    {
        printf( "Failed to load crt' texture image!\n" );
		exit(0);
    }
    crt.renderCHAR( mPosX + 7, mPosY, degrees, Turning_pos);

    if( shooting == 1 && countdown == FIRE_RATE) FireEffectTexture.renderFireEffect( mPosX + 7, mPosY, degrees, Turning_pos);
}

void Character::aiming_line()
{
    SDL_Point ed = line( Turning_point.x, Turning_point.y, degrees);

    SDL_SetRenderDrawBlendMode( gRenderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x44, 0x44, 0xFF);
    SDL_RenderDrawLine( gRenderer, Turning_point.x, Turning_point.y, ed.x, ed.y);

    ed = line( Turning_point.x, Turning_point.y, fix_degrees(degrees + 40));
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0xA5 );
    //SDL_RenderDrawLine( gRenderer, Turning_point.x, Turning_point.y, ed.x, ed.y);

    ed = line( Turning_point.x, Turning_point.y, fix_degrees(degrees - 40));
    //SDL_RenderDrawLine( gRenderer, Turning_point.x, Turning_point.y, ed.x, ed.y);
}

#endif // Charclassfunction_H_
