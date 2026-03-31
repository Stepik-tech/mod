#define Action: Load

stock GetPlayerInstalledStripe(playerid, stripeItemId)
{
    for(new i; i < sizeof(PlayerAccessoryStripeData[]); i++)
    {
        for(new j; j < sizeof(PlayerAccessoryStripeData[][]); j++)
            if(PlayerAccessoryStripeData[playerid][i][j][E_STRIPE_TYPE_ITEMID] == stripeItemId)
                return true;
    }

    for(new j; j < sizeof(PlayerSkinStripeData[][]); j++)
        if(PlayerSkinStripeData[playerid][0][j][E_STRIPE_TYPE_ITEMID] == stripeItemId)
            return true;

    return false;
}

stock Action:InventorySkinCharacter(playerid, bool:characterEnable)
{
    for(new i; i < sizeof(PlayerSkinStripeData[][]); i++)
    {        
        if(PlayerSkinStripeData[playerid][0][i][E_STRIPE_TYPE_ITEMID] == 7345 || PlayerSkinStripeData[playerid][0][i][E_STRIPE_TYPE_ITEMID] == 7346)
            SetInventorySkinCharacter(playerid, PlayerSkinStripeData[playerid][0][i][E_STRIPE_TYPE_ITEMID], characterEnable);
    }
}

stock SetInventorySkinCharacter(playerid, characterItemId, bool:characterEnable)
    return SendPlayerClientPacket(playerid, characterItemId == 7346 ? 91 : 163, characterEnable == false ? 0 : 128);


stock SetPlayerOnFire(playerid)
{
	new Float:playerPos[4];
	GetPlayerPos(playerid, playerPos[0], playerPos[1], playerPos[2]);
	GetPlayerFacingAngle(playerid, playerPos[3]);
	
    pTemp[playerid][tFireObject] = CreateObject(18688, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    AttachObjectToPlayer(pTemp[playerid][tFireObject], playerid, 0.0, 0.0, -2.0, 0.0, 0.0, 0.0);

	return SetTimerEx("DisPlayerOnFire", 5000, false, "i", playerid);
}

public: DisPlayerOnFire(playerid)
{
	DestroyObject(pTemp[playerid][tFireObject]);
	pTemp[playerid][tFireObject] = INVALID_DATA_ID;
}

stock Action:UpdatePlayerFire(playerid)
{
    if(pTemp[playerid][tFireObject] != INVALID_DATA_ID)
    {
        PI[playerid][pHealth] = PI[playerid][pHealth] - 1.0;
        UpdatePlayerHealth(playerid, PI[playerid][pHealth]);
        SetPlayerChatBubble(playerid, "-1 υο", COLOR_OLDRED, 10.0, 500);
    }
}


stock Action:ReflectionMode(playerid)
{
    HealthReflection[playerid]++;

    new healthString[16];
    format(healthString, sizeof(healthString), "-%d_υο", HealthReflection[playerid]);

    if(pTemp[playerid][tReflectionTime] != 0)
    {
        DisableReflectionMode(playerid, false);

        PlayerTextDrawSetString(playerid, reflection[playerid][5], IntToStr(pTemp[playerid][tReflectionTime] = 60));
        PlayerTextDrawSetString(playerid, reflection[playerid][4], healthString);
    }
    else
        ShowTextDrawReflectionMode(playerid, healthString, pTemp[playerid][tReflectionTime] = 60);

    TimerReflection[playerid][0] = SetTimerEx("DisableReflectionMode", 60000, false, "dd", playerid, true);
    TimerReflection[playerid][1] = SetTimerEx("UpdateReflectionMode", 1000, true, "d", playerid);

    return true;
}

public: UpdateReflectionMode(playerid)
{
    PlayerTextDrawSetString(playerid, reflection[playerid][5], IntToStr(--pTemp[playerid][tReflectionTime]));

    if(pTemp[playerid][tReflectionTime] <= 0)
        DisableReflectionMode(playerid, true);
}

public: DisableReflectionMode(playerid, bool:destroyTd)
{
	pTemp[playerid][tReflectionShot] =
    pTemp[playerid][tReflectionTime] = 0;

    KillTimer(TimerReflection[playerid][0]);
    KillTimer(TimerReflection[playerid][1]);

    if(destroyTd)
        for(new i; i < 6; i++)
            DestroyPlayerTD(playerid, reflection[playerid][i]);
}

stock UpdatePlayerTakeDamage(playerid, weaponid, Float:amount)
{
	if(PI[playerid][pArmour] > 0)
	{
	    if(weaponid > 46) UpdatePlayerHealth(playerid, PI[playerid][pHealth] - amount);
	    else UpdatePlayerArmour(playerid, PI[playerid][pArmour] - amount);
	}
	else UpdatePlayerHealth(playerid, PI[playerid][pHealth] - amount);
}

#include "modules/inventory/itemAttributes/stripe_actiontd.inc"