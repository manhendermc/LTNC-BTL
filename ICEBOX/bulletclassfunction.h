#ifndef bulletclassfunction_H_
#define bulletclassfunction_H_

bulletcontrol::bulletcontrol()
{
    bstate = 0;
}

void bulletcontrol::add( bulletstate x )
{
    bullet_list.push( x );
}

void bulletcontrol::render( bulletstate bullet )
{
    //cout << -1 << '\n';
    SDL_Point turn = {bullet_WIDTH, bullet_HEIGHT / 2 };

    mbullet.renderBULLET(int(bullet.x) - bullet_WIDTH, int(bullet.y) - bullet_HEIGHT/2 , bullet.angle, turn);
}

bool bulletcontrol::check_collision(bulletstate bt)
{
    if(!bt.shooter)
    {
        bulletstate pre = bt;
        pre.x -= pre.stx;
        pre.y -= pre.sty;

        for(int i = 0;i < TOTAL_ENEMY;i ++)
        if(p[i].get_hp() > 0){
            if(dis( bt.x, bt.y, p[i].get_mPos().x, p[i].get_mPos().y) < p[i].CHAR_HITBOX_BULLET)
            {
                p[i].sethp();
                Mix_PlayChannel( -1, ouch_sound, 0 );
                return 1;
            }
            if((p[i].get_mPos().x - pre.x)*(p[i].get_mPos().x - bt.x) >= 0 && (p[i].get_mPos().y - pre.y)*(p[i].get_mPos().y - bt.y) >= 0)
            {
                continue;
            }
            else
            {
                SDL_Point tmp1{pre.x,pre.y};
                double angle = abs(get_angle(tmp1, p[i].get_mPos()) - pre.angle);

                angle = min( angle, 360 - angle );
                if( angle >= 90) continue;

                double h = dis( pre.x, pre.y, p[i].get_mPos().x, p[i].get_mPos().y) * sin(angle *pi / 180.0);
                if( abs(h) > p[i].CHAR_HITBOX_BULLET) continue;

                p[i].sethp();
                Mix_PlayChannel( -1, ouch_sound, 0 );
                return 1;
            }
        }
    }
    else
    {
        bulletstate pre = bt;
        pre.x -= pre.stx;
        pre.y -= pre.sty;

        if(mainchar.get_hp() > 0){
            if(dis( bt.x, bt.y, mainchar.get_mPos().x, mainchar.get_mPos().y) < mainchar.CHAR_HITBOX_BULLET)
            {
                mainchar.sethp();
                Mix_PlayChannel( -1, ouch_sound, 0 );
                return 1;
            }
            if((mainchar.get_mPos().x - pre.x)*(mainchar.get_mPos().x - bt.x) >= 0 && (mainchar.get_mPos().y - pre.y)*(mainchar.get_mPos().y - bt.y) >= 0)
            {

            }
            else
            {
                SDL_Point tmp1{pre.x,pre.y};
                double angle = abs(get_angle(tmp1, mainchar.get_mPos()) - pre.angle);

                angle = min( angle, 360 - angle );
                if( angle < 90)
                {
                    double h = dis( pre.x, pre.y, mainchar.get_mPos().x, mainchar.get_mPos().y) * sin(angle *pi / 180.0);
                    if( abs(h) <= mainchar.CHAR_HITBOX_BULLET)
                    {
                        mainchar.sethp();
                        Mix_PlayChannel( -1, ouch_sound, 0 );
                        return 1;
                    }
                }

            }
        }
    }

    tilemap_POS nowpos = getlocate( bt.x, bt.y );

    return tile[nowpos.x][nowpos.y];
}

void bulletcontrol::move()
{
    while( !bullet_list.empty() && bullet_list.front().state == bstate)
    {
        bulletstate bt = bullet_list.front();
        bullet_list.pop();

        //render(bt);

        bt.x += bt.stx/2;
        bt.y += bt.sty/2;
        //render(bt);
        bt.x += bt.stx/2;
        bt.y += bt.sty/2;
        bt.state = bstate^1;

        render(bt);

        if( !check_collision(bt) )
        {
            add(bt);
        }
    }

    bstate ^= 1;
}

void bulletcontrol::deletelist()
{
    while(!bullet_list.empty())
    {
        bullet_list.pop();
    }
}

#endif // bulletclassfunction_H_
