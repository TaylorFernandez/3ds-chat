#ifndef COMMON_H
#define COMMON_H

#include <citro3d.h>
#include <citro2d.h>

typedef enum{
    APPLICATION_INIT,
    APPLICATION_SELECT_MII,
    APPLICATION_VERIFY_INFO,
    APPLICATION_RETRY_MII,
    APPLICATION_REGISTER_WAITING,
    APPLICATION_REGISTER_COMPLETE,
    APPLICATION_MAIN_MENU
} states;

extern states applicationCurrentState;
extern MiiSelectorConf msConf;
extern MiiSelectorReturn msRet;
extern bool setupComplete;
extern char miiName[36];
#endif