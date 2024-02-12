#include "uiStateManager.h"
#include "../common.h"
#include "ui.h"

#include <citro3d.h>
#include <citro2d.h>
#include <stdbool.h>

u32 clrWhite;
u32 clrGreen;
u32 clrRed;
u32 clrBlue;

C2D_Text text1;
C2D_TextBuf text1Buffer; 

char verifyString[120];
bool startedMiiSelector = false;

static const char welcomeString[] = "Welcome to 3ds Chat!\n"
                                    "3ds Chat is a simple chatting application.\n"
                                    "To begin setup, please select a Mii.\n"
                                    "This will be used to setup your account.\n\n\n\n\n\n\n"
                                    "Press A to continue...";

int renderApplicationWelcome(){
    startedMiiSelector = false;
    //Clear the buffer before writing text
    C2D_TextBufClear(text1Buffer);
    
    //Draws the frame for the welcome screen
    C2D_DrawRectangle(25.0f, 30.0f, 0.0f, SCREEN_WIDTH-50, SCREEN_HEIGHT-60,clrWhite,clrWhite,clrWhite,clrWhite);

    //Draws the welcome text to the screen
    C2D_TextParse(&text1, text1Buffer, welcomeString);
    C2D_TextOptimize(&text1);
    C2D_DrawText(&text1, 0, 30.0f, 45.0f, 0.0f, 0.5f, 0.5f);

    return 0;
}

int renderInfoVerification(){
    C2D_TextBufClear(text1Buffer);
    
    //Draws the frame for the welcome screen
    C2D_DrawRectangle(25.0f, 30.0f, 0.0f, SCREEN_WIDTH-50, SCREEN_HEIGHT-60,clrWhite,clrWhite,clrWhite,clrWhite);

    //Get the Mii's info from the return value
    miiSelectorReturnGetName(&msRet, miiName, sizeof(miiName));

    //Format the Mii's Info in a string
    sprintf(verifyString, "Mii Selected: %s\nBirthday: %d/%d\n\n\n\n\n\n\nPress A to continue\nPress B to pick another Mii", miiName, msRet.mii.mii_details.bday_day, msRet.mii.mii_details.bday_month);
    C2D_TextParse(&text1, text1Buffer, verifyString);
    C2D_TextOptimize(&text1);
    C2D_DrawText(&text1, 0, 30.0f, 45.0f, 0.0f, 0.5f, 0.5f);

    return 0;
}


int renderSelectMii(){
    //Draws the frame for the welcome screen
    C2D_DrawRectangle(25.0f, 30.0f, 0.0f, SCREEN_WIDTH-50, SCREEN_HEIGHT-60,clrWhite,clrWhite,clrWhite,clrWhite);


    miiSelectorInit(&msConf);
    miiSelectorSetTitle(&msConf, "Select a Mii");
    miiSelectorSetOptions(&msConf, 0);
    if(!startedMiiSelector){
        startedMiiSelector = true;
        miiSelectorLaunch(&msConf, &msRet);
    }

    applicationCurrentState = APPLICATION_VERIFY_INFO;

    return 0;
}

int renderRegisterWaiting(){
    C2D_TextBufClear(text1Buffer);

    C2D_DrawRectangle(25.0f, 30.0f, 0.0f, SCREEN_WIDTH-50, SCREEN_HEIGHT-60,clrWhite,clrWhite,clrWhite,clrWhite);

    C2D_TextParse(&text1, text1Buffer, "Registering with 3ds chat servers.\nPlease wait...");
    C2D_TextOptimize(&text1);
    C2D_DrawText(&text1, 0, 30.0f, 45.0f, 0.0f, 0.5f, 0.5f);

    //This is just to get to the next stage. Eventually, this will be moved to system handling communications with API 
    applicationCurrentState = APPLICATION_REGISTER_COMPLETE;
    return 0;
}

int renderRegisterComplete(){
    C2D_TextBufClear(text1Buffer);

    C2D_DrawRectangle(25.0f, 30.0f, 0.0f, SCREEN_WIDTH-50, SCREEN_HEIGHT-60,clrWhite,clrWhite,clrWhite,clrWhite);

    C2D_TextParse(&text1, text1Buffer, "Registration complete! Welcome to 3ds Chat.\n\n\n\n\n\n\n\nPress A to continue...");
    C2D_TextOptimize(&text1);
    C2D_DrawText(&text1, 0, 30.0f, 45.0f, 0.0f, 0.5f, 0.5f);
    return 0;
}

int renderMainMenu(){
    setupComplete = true;

    C2D_TextBufClear(text1Buffer);

    C2D_DrawRectangle(25.0f, 30.0f, 0.0f, SCREEN_WIDTH-50, SCREEN_HEIGHT-60,clrWhite,clrWhite,clrWhite,clrWhite);

    C2D_TextParse(&text1, text1Buffer, "Placeholder text");
    C2D_TextOptimize(&text1);
    C2D_DrawText(&text1, 0, 30.0f, 45.0f, 0.0f, 0.5f, 0.5f);
    return 0;
}

int retryMii(){
    startedMiiSelector = false;
    applicationCurrentState = APPLICATION_SELECT_MII;
    return 0;
}

int stateManagerInit(){
    //Create the colors used for UI elements
    clrWhite = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
    clrGreen = C2D_Color32(0x00, 0xFF, 0x00, 0xFF);
    clrRed   = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);
    clrBlue  = C2D_Color32(0x00, 0x00, 0xFF, 0xFF);

    //Create Text buffers
    text1Buffer = C2D_TextBufNew(4096);

    return 0;
}
int updateApplicationTop(states currentApplicationStates){
    switch(applicationCurrentState){
        case APPLICATION_INIT: renderApplicationWelcome(); break; 
        case APPLICATION_SELECT_MII: renderSelectMii(); break;
        case APPLICATION_VERIFY_INFO: renderInfoVerification(); break;
        case APPLICATION_RETRY_MII: retryMii(); break;
        case APPLICATION_REGISTER_WAITING: renderRegisterWaiting(); break;
        case APPLICATION_REGISTER_COMPLETE: renderRegisterComplete(); break;
        case APPLICATION_MAIN_MENU: renderMainMenu(); break;
    }

    return 0;
}

int exitStateManager(){
    C2D_TextBufDelete(text1Buffer);
    return 0;
}
