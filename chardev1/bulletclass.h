#ifndef bulletclass_H_
#define bulletclass_H_

class bulletcontrol
{
    public:
        static const int bullet_VEL = 50;

        bulletcontrol();

        void add ( bulletstate x );

        void render( bulletstate bullet );

        void move();

        bool check_collision( bulletstate bt );

        void deletelist();

    private:

        queue< bulletstate > bullet_list;
        bool bstate;
};

#endif // bulletclass_H_
