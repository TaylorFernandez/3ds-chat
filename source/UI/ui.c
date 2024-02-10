#include "ui.h"
#include "../Strings/TimeString.h"
#include "formatting.h"

#include <citro3d.h>
#include <citro2d.h>
#include <stdlib.h>

u32 clrWhite;
u32 clrGreen;
u32 clrRed;
u32 clrBlue;
u8 batteryLevel = 5;
u8 charging;
C3D_RenderTarget *top;
C3D_RenderTarget *bottom;

C2D_TextBuf timeBuf;
C2D_Text timeText;

int initColors(){
    clrWhite = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
    clrGreen = C2D_Color32(0x00, 0xFF, 0x00, 0xFF);
    clrRed   = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);
    clrBlue  = C2D_Color32(0x00, 0x00, 0xFF, 0xFF);
    return 0;
}

int initLibraries(){
    gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();

    return 0;
}

int initTop(){
    top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    initColors();

    timeBuf = C2D_TextBufNew(4096);
    C2D_TextParse(&timeText, timeBuf, getTime());
    C2D_TextOptimize(&timeText);


    return 0;

}

int updateTop(){
    //Clear the time buffer; update the text
    C2D_TextBufClear(timeBuf);
    C2D_TextParse(&timeText, timeBuf, getTime());
    C2D_TextOptimize(&timeText);

    // Render the scene
    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
    C2D_TargetClear(top, clrWhite);
    C2D_SceneBegin(top);

    //Get the size of the text element and draw it to the center of the screen
    C2D_DrawText(&timeText,0,getCenteredHorizontal(timeText), 8.0f, 0.5f, 0.5f, 0.5f);

    //Get the current battery level and draw to screen
    PMTU_GetBatteryLevel(&batteryLevel);
    PTMU_GetBatteryChargeState(charging);

    C3D_FrameEnd(0);
    
    return 0;
}

int initBottom(){

    return 0;
}

int updateBottom(){


    return 0;

}

int exitUI(){
    C2D_Fini();
	C3D_Fini();
	gfxExit();
    return 0;
}