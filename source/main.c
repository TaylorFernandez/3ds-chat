#include <citro2d.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "UI/ui.h"
#include "common.h"

states currentApplicationState; 

//---------------------------------------------------------------------------------
int main(int argc, char* argv[]) {
//------------------\---------------------------------------------------------------
	romfsInit();
	initLibraries();
	initTop();
	initBottom();

	currentApplicationState = APPLICATION_INIT;
	bool miiSelected = false;

	// Main loop
	while (aptMainLoop())
	{
		hidScanInput();

		// Respond to user input
		u32 kDown = hidKeysDown();

		if(kDown & KEY_A && miiSelected == false){
			currentApplicationState = APPLICATION_SELECT_MII;
			miiSelected = true;
			//Temporary; used to break infinite mii select loop
			currentApplicationState = APPLICATION_INIT;
		}
		if (kDown & KEY_START)
			break; // break in order to return to hbmenu

		updateTop(currentApplicationState);
		updateBottom(currentApplicationState);
	
		
	}

	// Deinit libs
	exitUI();
	return 0;
}
