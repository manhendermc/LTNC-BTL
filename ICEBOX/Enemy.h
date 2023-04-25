#ifndef Enemy_H_
#define Enemy_H_

class Enemy
{
     public:
        //The dimensions of the dot
		static const int CHAR_HITBOX_DIAMETER = 54;
		static const int CHAR_HITBOX_RADIUS = 27;
		static const int CHAR_HITBOX_DIS = 15;
		static const int CHAR_HITBOX_BULLET = 20;
		static const int REACT_TIME = 13;
		static const int FLICK_TPD = 9;
		static const int AWARE_TIME = 240;

        Enemy();

        void charrender();

        void charcountdown();
        void setpos(int x, int y, double angle, int id);
        void react();

        void reset();

        void sethp()
        {
            if(hp > 0)hp -= 25;
        }

        SDL_Point get_mPos(){
            return {mPosX, mPosY};
        }


        double get_degrees()
        {
            return degrees;
        }


        int get_hp(){
            return hp;
        }

        void charmove();
    private:
        int ind;
        int hp;
        int mPosX, mPosY;

        double degrees;
        double default_degrees;

        SDL_Point Turning_point, Turning_pos;

        int countdown, flick_countdown, bullet_cnt, aware_countdown;

        bulletstate bullet;

        bool shooting;
};
#endif // Enemy_H_
