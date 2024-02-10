// Simple citro2d untextured shape example
#include <citro2d.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "UI/ui.h"


//---------------------------------------------------------------------------------
int main(int argc, char* argv[]) {
//------------------\---------------------------------------------------------------

	initLibraries();
	initTop();
	initBottom();

	// Main loop
	while (aptMainLoop())
	{
		hidScanInput();

		// Respond to user input
		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; // break in order to return to hbmenu

		updateTop();
		updateBottom();
	
		
	}

	// Deinit libs
	exitUI();
	return 0;
}
