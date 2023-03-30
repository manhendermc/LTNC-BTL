#ifndef bulletclass_H_
#define bulletclass_H_

class bulletcontrol
{
    public:
        static const int bullet_VEL = 60;

        bulletcontrol();

        void add ( bulletstate x );

        void render( bulletstate bullet );

        void move();

        void deletelist();

    private:

        queue< bulletstate > bullet_list;
        bool bstate;
};

#endif // bulletclass_H_
