#ifndef reset_H_
#define reset_H_

void reset()
{
    mainchar.reset();
    for(int i = 0;i < TOTAL_ENEMY;i ++)
        p[i].reset();

    posinit();
    listbl.deletelist();
}

#endif // reset_H_
