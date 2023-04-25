#ifndef colision_H_
#define colision_H_

void addobject()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("tile.inp" , "r" , stdin);

    for(int i = 0;i <= tilemap_HEIGHT + 1; i ++)
    {
        for(int j = 0;j <= tilemap_WIDTH + 1; j++)
        {
            cin >> tile[j][i];
        }
    }
}

tilemap_POS getlocate ( int x,int y )
{
    tilemap_POS r;

    r.x = ceil(double(x) / double( square_SIZE ) );
    r.y = ceil(double(y) / double( square_SIZE ) );

    return r;
}

double dis( int x, int y, int a, int b)
{
    a = a - x;
    b = b - y;
    return sqrt(a*a + b*b);
}

double fix_degrees( double degrees )
{
    while( degrees > 180 )degrees -= 360;
    while( degrees < -180 )degrees += 360;

    return degrees;
}

double get_angle(SDL_Point p1, SDL_Point p2)
{
    double degrees;

    if(p2.x - p1.x == 0 && p2.y - p1.y <= 0)  degrees = -90;
    else if ( p2.x - p1.x == 0 && p2.y - p1.y > 0) degrees = 90;
    else degrees = atan( double( p2.y - p1.y ) / double(p2.x - p1.x )) * 180.0 / pi;
    if( p2.x - p1.x < 0 && p2.y - p1.y >= 0)
        degrees += 180;
    else if( p2.x - p1.x < 0 && p2.y - p1.y < 0)
        degrees -= 180;

    degrees = fix_degrees(degrees);

    return degrees;
}

SDL_Point line( double x, double y, double angle)
{
    tilemap_POS nowpos = getlocate( int(x), int(y));

    if( angle >= 0 &&int(y) % square_SIZE == 0) nowpos.y ++;
    //if( angle >= 90 || angle <= -90)&& int(x) % square_SIZE == 0)

    if( tile[nowpos.x][nowpos.y] == 1 )return {int(x), int(y)};

    bool dir = (angle < 0);
    double nextline = square_SIZE * (nowpos.y - dir);
    double newx, newy;
    if( angle == 0 )newx = SCREEN_WIDTH + 1, newy = y;
    else if ( angle == 180 )newx = 0, newy = y;
    else if ( angle == 90 || angle == -90) newx = x, newy = nextline;
    else newx = (nextline - y) / tan( angle * pi / 180.0 ) + x, newy = nextline;

    tilemap_POS newpos = getlocate( newx, newy );

    int add;
    if( newpos.x>=nowpos.x ) add = 1;
    else add = -1;
    for(int i = nowpos.x;(i - newpos.x)*add <= 0;i += add)
    if(tile[i][nowpos.y]){
        double disx, disy;
        if( nowpos.x <= i )disx = (i - 1)*square_SIZE - x;
        else disx = i * square_SIZE - x;
        if ( angle == 180 || angle == 0)
            disy = 0;
        else disy = tan( angle * pi / 180.0 ) * disx;

        //cout << angle <<" "<< tan( angle * pi / 180.0 ) << endl;

        return {int(x + disx), int(y + disy)};
    }

    line( newx, newy, angle);

}

void draw_grid()
{
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
    for (int i = 1;i < SCREEN_WIDTH; i += square_SIZE)
        SDL_RenderDrawLine( gRenderer, i, 0, i, SCREEN_HEIGHT);
    for(int i = 1;i <SCREEN_HEIGHT;i += square_SIZE )
        SDL_RenderDrawLine( gRenderer, 0, i, SCREEN_WIDTH, i);
}

#endif // colision_H_
