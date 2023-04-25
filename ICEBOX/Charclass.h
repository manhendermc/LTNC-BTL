#ifndef Charclass_H_
#define Charclass_H_

class Character
{
    public:
        //The dimensions of the dot
		static const int CHAR_HITBOX_DIAMETER = 54;
		static const int CHAR_HITBOX_RADIUS = 27;
		static const int CHAR_HITBOX_DIS = 15;
		static const int CHAR_HITBOX_BULLET = 14;
		static const int CHAR_VEL = 4;
		static const int RELOAD_CNT = 5;
		static const int RELOAD_TOTAL = 25;
		static const int TOTAL_BULLET = 20;
		static const int RECOIL = 3;

        Character();

        void acthandleEvent ( SDL_Event& e );

        void charmove();

        void charrender();

        void charcountdown();

        bool check_collision();

        void reset();

        void aiming_line();

        SDL_Point get_mPos()
        {
            return Turning_point;
        }

        void sethp()
        {
            if(hp > 0)hp -= 20;
        }


        double get_degrees(){
            return degrees;
        }

        int get_hp(){
            return hp;
        }

        int get_bullet()
        {
            return bullet_remaining;
        }

        bool get_reloadstate()
        {
            return reloading;
        }



    private:
        int hp;
        int mPosX, mPosY;
        int mVelX, mVelY;

        double degrees;

        SDL_Point Turning_point, Turning_pos;

        int mouseX, mouseY;

        int countdown, bullet_remaining, reload_cnt, reload_countdown, recoil_countdown;

        bulletstate bullet;

        bool shooting, reloading;

        tilemap_POS nowpos;
};

#endif // Charclass_H_
