#ifndef checkvision_H_
#define checkvision_H_

void check_vision()
{
    enemyalive = 0;
    for(int i = 0;i < TOTAL_ENEMY;i ++ )
    {
        if(p[i].get_hp() == 0)
        {
            charvision[i] = 0;enemyvision[i] = 0;
            continue;
        }

        enemyalive ++;
        double angle = get_angle( mainchar.get_mPos(), p[i].get_mPos() );

        SDL_Point newpos = line( double(mainchar.get_mPos().x), double(mainchar.get_mPos().y), angle);

        //cout << newpos.x << " "<< newpos.y << endl;


        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
        SDL_RenderDrawPoint( gRenderer, newpos.x, newpos.y );

        if( (p[i].get_mPos().x - mainchar.get_mPos().x)*(p[i].get_mPos().x - newpos.x) >= 0 &&
           (p[i].get_mPos().y - mainchar.get_mPos().y)*(p[i].get_mPos().y - newpos.y) >= 0  )
        {
            charvision[i] = 0;
            enemyvision[i] = 0;
        }
        else
        {
            if(min(abs(mainchar.get_degrees() - angle), 360 -  abs(mainchar.get_degrees() - angle))<= 200) charvision[i] = 1;
            else charvision[i] = 0;
            if(min(abs(p[i].get_degrees() - fix_degrees(angle + 180)), 360 - abs(p[i].get_degrees() - fix_degrees(angle + 180))) <= 200) enemyvision[i] = 1;
            else enemyvision[i] = 0;
        }
    }
}

#endif // checkvision_H_
