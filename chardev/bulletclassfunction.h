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

        if( bt.x - bullet_WIDTH <= SCREEN_WIDTH && bt.x >= 0 && bt.y - bullet_HEIGHT <= SCREEN_HEIGHT && bt.y >= 0)
        {
            //cout << cos(bt.angle / 180 * 3.1415) << " " << sin(bt.angle / 180 * 3.1415) << '\n';
            render(bt);
            //cout << -1 << '\n';
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
