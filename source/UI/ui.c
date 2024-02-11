#include "ui.h"
#include "../Strings/TimeString.h"
#include "formatting.h"
#include "../common.h"
#include "uiStateManager.h"

#include <citro3d.h>
#include <citro2d.h>
#include <stdlib.h>

u32 clrAqua;

u8 batteryLevel = 5;
u8 charging;
u8 wifiStatus;
C3D_RenderTarget *top;
C3D_RenderTarget *bottom;

C2D_TextBuf timeBuf;
C2D_Text timeText;

C2D_SpriteSheet spriteSheet;

C2D_Sprite batteryState;
C2D_Sprite wifiState;


int getCurrentBatterySprite(){
    //Get the current battery level and draw to screen
    PTMU_GetBatteryLevel(&batteryLevel);
    PTMU_GetBatteryChargeState(&charging);

    if(charging == 1){
        C2D_SpriteFromSheet(&batteryState, spriteSheet, 5);
    }else{
        C2D_SpriteFromSheet(&batteryState, spriteSheet, batteryLevel-1);

    }

    C2D_SpriteSetCenter(&batteryState, 0.5f, 0.5f);
    C2D_SpriteSetPos(&batteryState, SCREEN_WIDTH-15, 0+10);
    
    return 0;
}

int getCurrentWifiSprite(){
    wifiStatus = osGetWifiStrength();

    if(wifiStatus == 0){
        C2D_SpriteFromSheet(&wifiState, spriteSheet, 10);
    }else{
        C2D_SpriteFromSheet(&wifiState, spriteSheet, 6 + wifiStatus);
    }
    C2D_SpriteSetCenter(&wifiState, 0.5f, 0.5f);
    C2D_SpriteSetPos(&wifiState, 0 + 15, 0 + 10);

    return 0;
}


int initColors(){
    //Creates the colors used in ui
    clrAqua  = C2D_Color32(0x00, 0xFF, 0xFF, 0xFF);
    return 0;
}

int initLibraries(){
    //Initialize libraries
    gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
    stateManagerInit();

    //load the sprites
    spriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x");
	if (!spriteSheet) svcBreak(USERBREAK_PANIC);

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

int updateTop(states applicationCurrentState){
    //Clear the time buffer; update the text
    C2D_TextBufClear(timeBuf);
    C2D_TextParse(&timeText, timeBuf, getTime());
    C2D_TextOptimize(&timeText);

    // Render the scene
    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
    C2D_TargetClear(top, clrAqua);
    C2D_SceneBegin(top);

    //Get the size of the text element and draw it to the center of the screen
    C2D_DrawText(&timeText,0,getCenteredHorizontal(timeText), 8.0f, 0.5f, 0.5f, 0.5f);

    //Get the current battery level and draw to screen
    getCurrentBatterySprite();
    C2D_DrawSprite(&batteryState);

    //Get the current wifi state and draw to screen
    getCurrentWifiSprite();
    C2D_DrawSprite(&wifiState);

    //Updates the content of the application
    updateApplicationTop(applicationCurrentState);

    C3D_FrameEnd(0);
    
    return 0;
}

int initBottom(){
    consoleInit(GFX_BOTTOM, NULL);
    return 0;
}

int updateBottom(states applicationCurrentState){

    int numSprites = C2D_SpriteSheetCount(spriteSheet);
    printf("\x1b[8;1HCurrent Application State: %d", applicationCurrentState);
    return 0;

}

int exitUI(){
    C2D_Fini();
	C3D_Fini();
	gfxExit();
    return 0;
}