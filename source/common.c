#include "common.h"

#include <citro3d.h>
#include <citro2d.h>
#include <stdbool.h>
states applicationCurrentState;
MiiSelectorConf msConf;
MiiSelectorReturn msRet;
bool waitingOnNetwork;
bool setupComplete = false;
char miiName[36];