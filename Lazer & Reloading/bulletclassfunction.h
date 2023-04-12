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

    mbullet.renderBULLET(bullet.x - bullet_WIDTH, bullet.y - bullet_HEIGHT/2 , bullet.angle, turn);
}

bool bulletcontrol::check_collision(bulletstate bt)
{
    tilemap_POS nowpos = getlocate( bt.x, bt.y );

    return tile[nowpos.x][nowpos.y];
}

void bulletcontrol::move()
{
    while( !bullet_list.empty() && bullet_list.front().state == bstate)
    {
        bulletstate bt = bullet_list.front();
        bullet_list.pop();

        bt.dis += bullet_VEL;

        bt.x = bt.stx + cos(bt.angle / 180 * pi) * double(bt.dis);
        bt.y = bt.sty + sin(bt.angle / 180 * pi) * double(bt.dis);
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
