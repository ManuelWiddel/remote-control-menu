#ifndef MENU_H
#define MENU_H

#include <stdint.h>
#include <stdbool.h>
#include "parameters.h"

typedef enum
{
    MENU_FOLDER,
    MENU_PARAMETER,
    MENU_ACTION
} MenuItemType_t;

typedef struct MenuItem MenuItem_t;

typedef void (*MenuAction_t)(void);

struct MenuItem
{
    const char *name;

    MenuItemType_t type;

    /* Array of pointers to child menu items */
    MenuItem_t **children;
    uint8_t childCount;

    /* Pointer to parent folder */
    MenuItem_t *parent;

    /* Parameter information */
    uint16_t parameterID;


    MenuAction_t action;
};

typedef enum
{
    EVENT_NONE,
    EVENT_UP,
    EVENT_DOWN,
    EVENT_ENTER,
    EVENT_BACK
} MenuEvent_t;

typedef struct
{
    MenuItem_t *currentMenu;

    uint8_t selectedIndex;

    bool editing;

} MenuState_t;

void Menu_Init(void);
void Menu_Process(MenuEvent_t event);

MenuState_t* Menu_GetState(void);

bool Menu_GetChangedParameter(uint16_t *id, float *value);

#endif

/*

#ifndef MENU_H
#define MENU_H

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    MENU_FOLDER,
    MENU_PARAMETER,
    MENU_ACTION
} MenuItemType_t;

typedef struct MenuItem MenuItem_t;

typedef void (*MenuAction_t)(void);

struct MenuItem
{
    const char *name;

    MenuItemType_t type;

    MenuItem_t *parent;

    MenuItem_t *children;
    uint8_t childCount;

    int32_t *value;
    int32_t minValue;
    int32_t maxValue;

    MenuAction_t action;
};

typedef enum
{
    EVENT_NONE,
    EVENT_UP,
    EVENT_DOWN,
    EVENT_ENTER,
    EVENT_BACK
} MenuEvent_t;

typedef struct
{
    MenuItem_t *currentMenu;

    uint8_t selectedIndex;

    bool editing;

} MenuState_t;

void Menu_Init(void);
void Menu_Process(MenuEvent_t event);

MenuState_t* Menu_GetState(void);

#endif

 * */
