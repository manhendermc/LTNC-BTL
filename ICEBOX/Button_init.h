#ifndef Button_init_H_
#define Button_init_H_

void button_init()
{
    menu_play.init_BUTTON( 35, 385, 420, 70, 4);
    menu_tutorial.init_BUTTON( 35, 455, 420, 70, 2);
    menu_exit.init_BUTTON( 35, 525, 420, 70, 3);
    tutorial_back.init_BUTTON( 1085, 595, 245, 70, 0);
    endgame_replay.init_BUTTON( 350, 420, 350, 70, 4);
    endgame_quit.init_BUTTON( 805, 420, 210, 70, 0);
    play_pause.init_BUTTON( 690, 5, 50, 50, 1);
    pause_quit.init_BUTTON( 525, 385, 350, 70, 0);
    pause_resume.init_BUTTON( 525, 280, 350, 70, 4);
}

#endif // Button_init_H_
