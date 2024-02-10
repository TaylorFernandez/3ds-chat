#include "formatting.h"
#include "ui.h"

#include <citro3d.h>
#include <citro2d.h>

float getCenteredHorizontal(C2D_Text text){
    float textWidth = 0;
    float textHeight = 0;
    C2D_TextGetDimensions(&text, 0.5f, 0.5f, &textWidth, &textHeight);
    return SCREEN_WIDTH/2 - (textWidth/2);
}