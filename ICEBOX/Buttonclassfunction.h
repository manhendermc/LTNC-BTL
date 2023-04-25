#ifndef Buttonclassfunction_H_
#define Buttonclassfunction_H_

Buttonclass::Buttonclass()
{
    x = 0; y = 0; w = 0; h = 0;
    link = 0;
}

void Buttonclass::init_BUTTON(int _x,int _y,int _w,int _h,int _link)
{
    x = _x;
    y = _y;
    h = _h;
    w = _w;
    link = _link;
}

bool Buttonclass::check_BUTTON()
{
    int mouseX, mouseY;
    SDL_GetMouseState( &mouseX, &mouseY );

    if( mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h)
    {
        return true;
    }

    return false;
}

void Buttonclass::renderBUTTON_Effect()
{
    BUTTON_EFFECTTexture.renderBUTTONEFFECT( x, y, w, h );
}

void Buttonclass::renderPAUSE_EFFECT()
{
    PAUSE_EFFECTTexture.renderBUTTONEFFECT( x, y, w, h);
}
#endif // Buttonclassfunction_H_
