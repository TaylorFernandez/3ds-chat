#include <citro2d.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "UI/ui.h"
#include "common.h"

//---------------------------------------------------------------------------------
int main(int argc, char* argv[]) {
//------------------\---------------------------------------------------------------
	romfsInit();
	initLibraries();
	initTop();
	initBottom();

	applicationCurrentState = APPLICATION_INIT;
	bool miiSelected = false;

	// Main loop
	while (aptMainLoop())
	{
		hidScanInput();

		// Respond to user input
		u32 kDown = hidKeysDown();

		if(kDown & KEY_A) {
			if(applicationCurrentState == APPLICATION_INIT && miiSelected == false){
				applicationCurrentState = APPLICATION_SELECT_MII;
				miiSelected = true;			
			}else if(applicationCurrentState == APPLICATION_VERIFY_INFO){
				applicationCurrentState = APPLICATION_REGISTER_WAITING;
			}else if(applicationCurrentState == APPLICATION_REGISTER_COMPLETE){
				applicationCurrentState = APPLICATION_MAIN_MENU;
			}
		}
		if(kDown & KEY_B){
			if(applicationCurrentState == APPLICATION_VERIFY_INFO){
				applicationCurrentState = APPLICATION_RETRY_MII;
			}
		}
		if (kDown & KEY_START)
			break; // break in order to return to hbmenu

		updateTop(applicationCurrentState);
		updateBottom(applicationCurrentState);
	
		
	}

	// Deinit libs
	exitUI();
	return 0;
}
