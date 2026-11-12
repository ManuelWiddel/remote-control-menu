#include "menu.h"
#include "parameters.h"
#include <stddef.h>

/* =====================================================
   MENU STATE
   ===================================================== */

static MenuState_t menuState;

static bool parameterChanged = false;

static uint16_t changedParameterID;

static float changedParameterValue;


/* =====================================================
   ACTIONS
   ===================================================== */

static void Action_Save(void)
{
    /* Save parameters to flash */
}

static void Action_Reset(void)
{
    /* Reset parameters */
}


/* =====================================================
   LEVEL 3: ANGLE
   ===================================================== */

static MenuItem_t *angleChildren[4];

static MenuItem_t angleMenu =
{
    .name = "Angle",
    .type = MENU_FOLDER,
    .children = angleChildren,
    .childCount = 4,
    .parent = NULL
};

/* =====================================================
   LEVEL 3: ANGLE VEL
   ===================================================== */

static MenuItem_t *angleVelChildren[4];

static MenuItem_t angleVelMenu =
{
    .name = "Angle Vel",
    .type = MENU_FOLDER,
    .children = angleVelChildren,
    .childCount = 4,
    .parent = NULL
};

/* =====================================================
   LEVEL 3: SPEED
   ===================================================== */

static MenuItem_t *speedChildren[2];

static MenuItem_t speedMenu =
{
    .name = "Speed",
    .type = MENU_FOLDER,
    .children = speedChildren,
    .childCount = 2,
    .parent = NULL
};

/* =====================================================
   LEVEL 3: POSITION
   ===================================================== */

static MenuItem_t *positionChildren[2];

static MenuItem_t positionMenu =
{
    .name = "Position",
    .type = MENU_FOLDER,
    .children = positionChildren,
    .childCount = 2,
    .parent = NULL
};

/* =====================================================
   LEVEL 2: CONTROLLERS
   ===================================================== */

static MenuItem_t *controllersChildren[4];

static MenuItem_t controllersMenu =
{
    .name = "Controllers",
    .type = MENU_FOLDER,
    .children = controllersChildren,
    .childCount = 4,
    .parent = NULL
};

/* =====================================================
   LEVEL 2: OBSERVER
   ===================================================== */

static MenuItem_t *observerChildren[3];

static MenuItem_t observerMenu =
{
    .name = "Observer",
    .type = MENU_FOLDER,
    .children = observerChildren,
    .childCount = 3,
    .parent = NULL
};

/* =====================================================
   LEVEL 2: BNO055
   ===================================================== */

static MenuItem_t *bnoChildren[3];

static MenuItem_t bnoMenu =
{
    .name = "BNO055",
    .type = MENU_FOLDER,
    .children = bnoChildren,
    .childCount = 3,
    .parent = NULL
};

/* =====================================================
   LEVEL 1: MAIN
   ===================================================== */

static MenuItem_t *mainChildren[3];

static MenuItem_t mainMenu =
{
    .name = "MAIN",
    .type = MENU_FOLDER,
    .children = mainChildren,
    .childCount = 3,
    .parent = NULL
};

/* =====================================================
   INITIALIZATION
   ===================================================== */

void Menu_Init(void)
{

	parameterChanged = false;

    /* -----------------------------------------------
       Angle parameters
       ----------------------------------------------- */

    static MenuItem_t angleKpItem =
    {
        .type = MENU_PARAMETER,
        .parameterID = PARAM_ANGLE_KP
    };

    static MenuItem_t angleKiItem =
    {
		.type = MENU_PARAMETER,
		.parameterID = PARAM_ANGLE_KI
    };

    static MenuItem_t angleKdItem =
    {
		.type = MENU_PARAMETER,
		.parameterID = PARAM_ANGLE_KD
    };
    static MenuItem_t angleSetpointItem =
	{
		.type = MENU_PARAMETER,
		.parameterID = PARAM_ANGLE_SETPOINT
	};


    angleChildren[0] = &angleKpItem;
    angleChildren[1] = &angleKiItem;
    angleChildren[2] = &angleKdItem;
    angleChildren[3] = &angleSetpointItem;

    /* -----------------------------------------------
       Angle velocity parameters
       ----------------------------------------------- */

    static MenuItem_t angleVelKpItem =
    {
        .type = MENU_PARAMETER,
        .parameterID = PARAM_ANGLE_VEL_KP
    };

    static MenuItem_t angleVelKiItem =
    {
		.type = MENU_PARAMETER,
		.parameterID = PARAM_ANGLE_VEL_KI
    };

    static MenuItem_t angleVelKdItem =
    {
		.type = MENU_PARAMETER,
		.parameterID = PARAM_ANGLE_VEL_KD
    };
    static MenuItem_t angleVelSetpointItem =
	{
		.type = MENU_PARAMETER,
		.parameterID = PARAM_ANGLE_VEL_SETPOINT
	};


    angleVelChildren[0] = &angleVelKpItem;
    angleVelChildren[1] = &angleVelKiItem;
    angleVelChildren[2] = &angleVelKdItem;
    angleVelChildren[3] = &angleVelSetpointItem;


    /* -----------------------------------------------
       Speed parameters
       ----------------------------------------------- */

    static MenuItem_t speedKpItem =
    {
        .type = MENU_PARAMETER,
        .parameterID = PARAM_SPEED_KP
    };

    static MenuItem_t speedSetpointItem =
	{
		.type = MENU_PARAMETER,
		.parameterID = PARAM_SPEED_SETPOINT
	};


    speedChildren[0] = &speedKpItem;
    speedChildren[1] = &speedSetpointItem;

    /* -----------------------------------------------
       Position parameters
       ----------------------------------------------- */

    static MenuItem_t positionKpItem =
    {
        .type = MENU_PARAMETER,
        .parameterID = PARAM_POSITION_KP
    };

    static MenuItem_t positionSetpointItem =
	{
		.type = MENU_PARAMETER,
		.parameterID = PARAM_POSITION_SETPOINT
	};


    positionChildren[0] = &positionKpItem;
    positionChildren[1] = &positionSetpointItem;

    /* -----------------------------------------------
       Controllers menu
       ----------------------------------------------- */

    controllersChildren[0] = &angleMenu;
    controllersChildren[1] = &angleVelMenu;
    controllersChildren[2] = &speedMenu;
	controllersChildren[3] = &positionMenu;

    /* -----------------------------------------------
       Observer parameters
       ----------------------------------------------- */

    static MenuItem_t observerL1Item =
    {
        .type = MENU_PARAMETER,
        .parameterID = PARAM_OBSERVER_L1
    };

    static MenuItem_t observerL2Item =
    {
		.type = MENU_PARAMETER,
		.parameterID = PARAM_OBSERVER_L2
    };

    static MenuItem_t observerL3Item =
    {
		.type = MENU_PARAMETER,
		.parameterID = PARAM_OBSERVER_L3
    };

    observerChildren[0] = &observerL1Item;
    observerChildren[1] = &observerL2Item;
    observerChildren[2] = &observerL3Item;

    /* -----------------------------------------------
       BNO055 parameters
       ----------------------------------------------- */

    static MenuItem_t complimentaryTauItem =
    {
        .type = MENU_PARAMETER,
        .parameterID = PARAM_COMPLIMENTARY_TAU
    };

    static MenuItem_t accBWItem =
    {
		.type = MENU_PARAMETER,
		.parameterID = PARAM_ACC_BW
    };

    static MenuItem_t gyroBWItem =
    {
		.type = MENU_PARAMETER,
		.parameterID = PARAM_GYRO_BW
    };

    bnoChildren[0] = &complimentaryTauItem;
    bnoChildren[1] = &accBWItem;
    bnoChildren[2] = &gyroBWItem;

    /* -----------------------------------------------
       Main menu
       ----------------------------------------------- */

    mainChildren[0] = &controllersMenu;
    mainChildren[1] = &observerMenu;
    mainChildren[2] = &bnoMenu;

    /* -----------------------------------------------
       Parent relationships
       ----------------------------------------------- */

    controllersMenu.parent = &mainMenu;
    observerMenu.parent = &mainMenu;
    bnoMenu.parent = &mainMenu;

    angleMenu.parent = &controllersMenu;
    angleVelMenu.parent = &controllersMenu;
    speedMenu.parent = &controllersMenu;
    positionMenu.parent = &controllersMenu;

    /* Parameter and action parents */
    angleKpItem.parent = &angleMenu;
    angleKiItem.parent = &angleMenu;
    angleKdItem.parent = &angleMenu;
    angleSetpointItem.parent = &angleMenu;

    angleVelKpItem.parent = &angleVelMenu;
    angleVelKiItem.parent = &angleVelMenu;
    angleVelKdItem.parent = &angleVelMenu;
    angleVelSetpointItem.parent = &angleVelMenu;

    speedKpItem.parent = &speedMenu;
    speedSetpointItem.parent = &speedMenu;

    positionKpItem.parent = &positionMenu;
    positionSetpointItem.parent = &positionMenu;

    observerL1Item.parent = &observerMenu;
    observerL2Item.parent = &observerMenu;
    observerL3Item.parent = &observerMenu;

    complimentaryTauItem.parent = &bnoMenu;
    accBWItem.parent = &bnoMenu;
    gyroBWItem.parent = &bnoMenu;

    /* -----------------------------------------------
       Initial menu state
       ----------------------------------------------- */

    menuState.currentMenu = &mainMenu;
    menuState.selectedIndex = 0;
    menuState.editing = false;
}


void Menu_Process(MenuEvent_t event)
{
    if (menuState.currentMenu == NULL ||
        event == EVENT_NONE)
    {
        return;
    }

    MenuItem_t *currentMenu = menuState.currentMenu;

    /* =============================================
       PARAMETER EDITING
       ============================================= */

    if (menuState.editing)
    {
        if (currentMenu->children == NULL ||
            menuState.selectedIndex >= currentMenu->childCount)
        {
            menuState.editing = false;
            return;
        }

        MenuItem_t *item =
            currentMenu->children[menuState.selectedIndex];

        if (item == NULL || item->type != MENU_PARAMETER)
        {
            menuState.editing = false;
            return;
        }

        // Retrieve parameter using its ID
        Parameter_t *parameter =
            Parameter_GetByID(item->parameterID);

        if (parameter == NULL || parameter->value == NULL)
        {
            menuState.editing = false;
            return;
        }

        switch (event)
        {
            case EVENT_DOWN:

                if (*parameter->value + parameter->stepSize
                    <= parameter->maxValue)
                {
                    *parameter->value += parameter->stepSize;

                    parameterChanged = true;
                    changedParameterID = parameter->id;
                    changedParameterValue = *parameter->value;
                }

                break;

            case EVENT_UP:

                if (*parameter->value - parameter->stepSize
                    >= parameter->minValue)
                {
                    *parameter->value -= parameter->stepSize;

                    parameterChanged = true;
                    changedParameterID = parameter->id;
                    changedParameterValue = *parameter->value;
                }

                break;

            case EVENT_ENTER:
            case EVENT_BACK:

                menuState.editing = false;
                break;

            default:
                break;
        }

        return;
    }

    /* =============================================
       NORMAL NAVIGATION
       ============================================= */

    switch (event)
    {
        case EVENT_UP:

            if (menuState.selectedIndex > 0)
                menuState.selectedIndex--;

            break;

        case EVENT_DOWN:

            if (menuState.selectedIndex + 1 <
                currentMenu->childCount)
            {
                menuState.selectedIndex++;
            }

            break;

        case EVENT_ENTER:
        {
            if (currentMenu->children == NULL ||
                menuState.selectedIndex >= currentMenu->childCount)
            {
                break;
            }

            MenuItem_t *item =
                currentMenu->children[menuState.selectedIndex];

            if (item == NULL)
                break;

            if (item->type == MENU_FOLDER)
            {
                if (item->children != NULL &&
                    item->childCount > 0)
                {
                    menuState.currentMenu = item;
                    menuState.selectedIndex = 0;
                }
            }
            else if (item->type == MENU_PARAMETER)
            {
                Parameter_t *parameter =
                    Parameter_GetByID(item->parameterID);

                if (parameter != NULL &&
                    parameter->value != NULL)
                {
                    menuState.editing = true;
                }
            }
            else if (item->type == MENU_ACTION &&
                     item->action != NULL)
            {
                item->action();
            }

            break;
        }

        case EVENT_BACK:

            if (currentMenu->parent != NULL)
            {
                menuState.currentMenu = currentMenu->parent;
                menuState.selectedIndex = 0;
            }

            break;

        default:
            break;
    }
}

/* =============================================
   GET MENU STATE
   ============================================= */

MenuState_t *Menu_GetState(void)
{
    return &menuState;
}

bool Menu_GetChangedParameter(uint16_t *id, float *value)
{
    if (!parameterChanged)
        return false;

    if (id == NULL || value == NULL)
        return false;

    *id = changedParameterID;
    *value = changedParameterValue;

    parameterChanged = false;

    return true;
}

