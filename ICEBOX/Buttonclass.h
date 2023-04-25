#ifndef Buttonclass_H_
#define Buttonclass_H_

class Buttonclass
{
    public:

        Buttonclass();

        void renderBUTTON_Effect();

        bool check_BUTTON();

        int get_link()
        {
            return link;
        }

        void init_BUTTON(int _x,int _y,int _w,int _h,int _link);

        void renderPAUSE_EFFECT();
    private:

        int x, y, w, h;
        int link;
};

#endif // Buttonclass_H_
