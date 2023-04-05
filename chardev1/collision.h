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


#endif // colision_H_
