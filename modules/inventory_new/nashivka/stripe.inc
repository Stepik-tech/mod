#define Stripe: stripe_

enum
{
    E_STRIPE_FOR_ACCESSORY,
    E_STRIPE_FOR_SKIN,
    E_STRIPE_FOR_ARMOR,
    E_STRIPE_FOR_BAG
}

enum
{
    E_STRIPE_INFO,
    E_STRIPE_CONFIRM
}

enum e_inventory_stripe_info
{
    E_STRIPE_TYPE,
    E_STRIPE_TYPE_ITEMID
}
new PlayerInventoryStripeData[MAX_PLAYERS][inv_MaxInventorySlot][2][e_inventory_stripe_info],
    PlayerAccessoryStripeData[MAX_PLAYERS][8][1][e_inventory_stripe_info],
    PlayerSkinStripeData[MAX_PLAYERS][1][2][e_inventory_stripe_info];

enum e_stripe_info
{
    E_STRIPE_ITEMID,
    E_STRIPE_FOR,
    E_STRIPE_TITLE[48]
}
new const StripeData[][e_stripe_info] = 
{
    {2183, E_STRIPE_FOR_ACCESSORY, "Нашивка на аксессуар(защита)"},
    {2184, E_STRIPE_FOR_ACCESSORY, "Нашивка на аксессуар(регенерация)"},
    {2185, E_STRIPE_FOR_ACCESSORY, "Нашивка на аксессуар(урон)"},
    {2186, E_STRIPE_FOR_ACCESSORY, "Нашивка на аксессуар(удача)"},
    {3621, E_STRIPE_FOR_ACCESSORY, "Нашивка на аксессуар(макс. хп)"},
    {7345, E_STRIPE_FOR_SKIN, "Бег Си Джея"},
    {7346, E_STRIPE_FOR_SKIN, "Бесконечный бег"},
    {7347, E_STRIPE_FOR_SKIN, "Защитная пластина"},
    {7348, E_STRIPE_FOR_SKIN, "Огненные пули"},
    {7349, E_STRIPE_FOR_SKIN, "Опыт Battle Pass"},
    {7415, E_STRIPE_FOR_SKIN, "Мастер рыболовли"},
    {7419, E_STRIPE_FOR_BAG, "Снижение урона противника"},
    {7420, E_STRIPE_FOR_ARMOR, "Защита от оглушения"},
    {8097, E_STRIPE_FOR_ACCESSORY, "Отражение урона"},
    {8816, E_STRIPE_FOR_ACCESSORY, "Тьма"},
    {8817, E_STRIPE_FOR_ACCESSORY, "Монстр"},
    {8818, E_STRIPE_FOR_ACCESSORY, "Энергия"}
};

stock GetStripeID(inventoryItemId)
{
    for(new i; i < sizeof(StripeData); i++)
        if(StripeData[i][E_STRIPE_ITEMID] == inventoryItemId)
            return i;

    return INVALID_DATA_ID;
}

stock IsStripeInstalled(playerid, inventorySlotId, inventoryStripeItemId)
{
    for(new j; j < sizeof(PlayerInventoryStripeData[][]); j++)
        if(PlayerInventoryStripeData[playerid][inventorySlotId][j][E_STRIPE_TYPE_ITEMID] == inventoryStripeItemId)
            return true;

    return false;
}

stock ShowPlayerStripeInstallDialog(playerid, inventoryStripeSlot, inventoryStripeInSlot = 0)
{    
    new typeSubjectStripe[12], inventoryStripeId = GetStripeID(PlayerInventorySlotData[playerid][InventoryItemID][inventoryStripeSlot]);

    if(inventoryStripeId == INVALID_DATA_ID)
        return SCM(playerid, COLOR_OLDRED, !"[Ошибка] {ffffff}Произошла ошибка, сообщите разработчику код ошибки: [#10]");

    typeSubjectStripe = StripeData[inventoryStripeId][E_STRIPE_FOR] == E_STRIPE_FOR_ACCESSORY ? "аксессуар" : StripeData[inventoryStripeId][E_STRIPE_FOR] == E_STRIPE_FOR_SKIN ? "скин" : StripeData[inventoryStripeId][E_STRIPE_FOR] == E_STRIPE_FOR_BAG ? "чемодан" : "бронежилет";

    switch(pTemp[playerid][tInstallStripeStage])
    {
        case E_STRIPE_INFO:
        {
            pTemp[playerid][tStripeInstallSlot] = inventoryStripeSlot;
            pTemp[playerid][tInstallStripeStage] = E_STRIPE_CONFIRM;

            return SPDF(playerid, 0, DIALOG_STYLE_MSGBOX, !"{cccccc}Подсказка", "\
			{ffffff}Сейчас вам нужно выбрать %s, на который вы хотите пришить нашивку\n\n\
			{cccccc}Обратите внимание, что пришив нашивку вы больше никогда не сможете снять её %s.\n\
			Что бы отменить установку нашивки, нажмите на предмет нашивки еще раз или закройте инвентарь.\
		    ", !"Закрыть", !"", typeSubjectStripe, StripeData[inventoryStripeId][E_STRIPE_FOR] == E_STRIPE_FOR_ACCESSORY ? "с аксессуара" : StripeData[inventoryStripeId][E_STRIPE_FOR] == E_STRIPE_FOR_SKIN ? "со скина" : StripeData[inventoryStripeId][E_STRIPE_FOR] == E_STRIPE_FOR_BAG ? "с чемодана" : "с бронежилета");
        }

        case E_STRIPE_CONFIRM:
        {
            spdList(playerid, 0, inventoryStripeSlot), spdList(playerid, 1, inventoryStripeInSlot);

            return SPDF(playerid, 25691, DIALOG_STYLE_MSGBOX, !"{cccccc}Подтверждение", "\
			{ffffff}Вы действительно хотите пришить нашивку {cccccc}%s {ffffff}на %s {ffff00}%s{ffffff}?\
            ", !"Принять", !"Отмена", StripeData[inventoryStripeId][E_STRIPE_TITLE], typeSubjectStripe, ItemsInfo[PlayerInventorySlotData[playerid][InventoryItemID][inventoryStripeInSlot]][itemName]);
        }
    }

    return false;
}

stock Stripe:ClearPlayerData(playerid)
{
	if(pTemp[playerid][tFireObject] != INVALID_DATA_ID)
		DestroyObject(pTemp[playerid][tFireObject]);

	pTemp[playerid][tFireObject] =
	pTemp[playerid][playerCurrentSelectId] = INVALID_DATA_ID;

    DisableReflectionMode(playerid, true);

    HealthReflection[playerid] = 0;

    pTemp[playerid][tInstallStripeStage] =
	pTemp[playerid][tStripeInstallSlot] = 0;

    return true;
}

stock IsItemValidInstallStripe(playerid, inventoryItemId)
{
    switch(StripeData[GetStripeID(PlayerInventorySlotData[playerid][InventoryItemID][pTemp[playerid][tStripeInstallSlot]])][E_STRIPE_FOR])
    {
        case E_STRIPE_FOR_ACCESSORY:
        {
            if(!IsItemAccessory(inventoryItemId))
                return SCM(playerid, COLOR_OLDRED, !"[Ошибка] {ffffff}Произошла ошибка, данную нашивку можно пришить только к аксессуарам!"), false;
        }
        case E_STRIPE_FOR_SKIN:
        {
            if(!IsItemSkin(inventoryItemId))
                return SCM(playerid, COLOR_OLDRED, !"[Ошибка] {ffffff}Произошла ошибка, данную нашивку можно пришить только к скинам!"), false;
        }
        case E_STRIPE_FOR_ARMOR, E_STRIPE_FOR_BAG:
        {
            if(ItemsInfo[inventoryItemId][itemType] != 6)
                return SCM(playerid, COLOR_OLDRED, !"[Ошибка] {ffffff}Произошла ошибка, данную нашивку нельзя пришить на данный предмет"), false;
        }
    }

    return true;
}

stock Stripe:OnDialogResponse(playerid, response)
{
    if(!response)
        return false;

    new inventoryStripeSlot = gpdList(playerid, 0), inventoryStripeInSlot = gpdList(playerid, 1), inventoryUnicaltityCount = PlayerInventorySlotData[playerid][InventoryUnicalityID][inventoryStripeInSlot];
    new inventoryStripeItemId = _:PlayerInventorySlotData[playerid][InventoryItemID][inventoryStripeSlot];
    new inventoryStripeId = GetStripeID(inventoryStripeItemId);

    if(IsStripeInstalled(playerid, inventoryStripeInSlot, inventoryStripeItemId))
        return SCM(playerid, COLOR_OLDRED, !"[Ошибка] {ffffff}Данная нашивка уже установлена на этот предмет");

    else if(inventoryUnicaltityCount >= (IsItemSkin(PlayerInventorySlotData[playerid][InventoryItemID][inventoryStripeInSlot]) ? 2 : 1))
        return SCMF(playerid, COLOR_OLDRED, "[Ошибка] {ffffff}Данный предмет уже имеет %s", IsItemSkin(PlayerInventorySlotData[playerid][InventoryItemID][inventoryStripeInSlot]) ? "две нашивки" : "одну нашивку");

    PlayerInventoryStripeData[playerid][inventoryStripeInSlot][inventoryUnicaltityCount][E_STRIPE_TYPE] = inventoryStripeId;
    PlayerInventoryStripeData[playerid][inventoryStripeInSlot][inventoryUnicaltityCount][E_STRIPE_TYPE_ITEMID] = inventoryStripeItemId;
    PlayerInventorySlotData[playerid][InventoryUnicalityID][inventoryStripeInSlot]++;

    InventoryStripeSave(playerid, inventoryStripeId, inventoryStripeInSlot, inventoryUnicaltityCount);
    clearInventorySlot(playerid, inventoryStripeSlot);

    global_str = "";
    f(global_str, 144, "%s[%i] занимается модификацией своей одежды", PN(playerid), playerid);
    ProxDetector(25, playerid, global_str, COLOR_ME);
        
    SCMF(playerid, COLOR_VALIK, "Вы вставили нашивку в %s", StripeData[inventoryStripeId][E_STRIPE_FOR] == E_STRIPE_FOR_ACCESSORY ? "аксессуар" : StripeData[inventoryStripeId][E_STRIPE_FOR] == E_STRIPE_FOR_SKIN ? "скин" : StripeData[inventoryStripeId][E_STRIPE_FOR] == E_STRIPE_FOR_BAG ? "чемодан" : "бронежилет");
    ApplyAnimationEx(playerid, "SHOP", "ROB_shifty", 4.1, 0, 1, 1, 0, 0);

    return Stripe:ClearPlayerData(playerid);
}

stock MoveStripeData(playerid, inventorySlotId, arraySlotId, inventoryTypeId, stripePointMax, inventoryMaxInfo, srcArray[][][][e_inventory_stripe_info])
{
    for(new stripePointId; stripePointId < stripePointMax; stripePointId++)
    {
        InventoryStripeSave(playerid, GetStripeID(srcArray[playerid][arraySlotId][stripePointId][E_STRIPE_TYPE_ITEMID]), arraySlotId, stripePointId, inventoryTypeId);

        for(new e_inventory_stripe_info:inventoryInfoId; _:inventoryInfoId < inventoryMaxInfo; _:inventoryInfoId++)
        {
            PlayerInventoryStripeData[playerid][inventorySlotId][stripePointId][inventoryInfoId] = srcArray[playerid][arraySlotId][stripePointId][inventoryInfoId];
            srcArray[playerid][arraySlotId][stripePointId][inventoryInfoId] = 0;
        }

        InventoryStripeSave(playerid, GetStripeID(PlayerInventoryStripeData[playerid][inventorySlotId][stripePointId][E_STRIPE_TYPE_ITEMID]), inventorySlotId, stripePointId);
    }
}

stock GetStripeInventoryInfo(playerid, inventoryTypeId, inventoryBlockSlotId, inventoryStripePoint, e_inventory_stripe_info:inventoryNeedData)
{
    switch(inventoryTypeId)
    {
        case 1:
            return PlayerInventoryStripeData[playerid][inventoryBlockSlotId][inventoryStripePoint][inventoryNeedData];

        case 2, 17:
            return PlayerAccessoryStripeData[playerid][inventoryBlockSlotId][inventoryStripePoint][inventoryNeedData];

        case 22:
            return PlayerSkinStripeData[playerid][0][inventoryStripePoint][inventoryNeedData];
    }

    return SCM(playerid, COLOR_OLDRED, !"[Ошибка] {ffffff}Произошла ошибка, сообщите разработчику код ошибки: [#11]");
}

stock Stripe:GetItemInfo(playerid, inventoryBlockSlotTypeId, inventoryBlockSlotId, inventoryStripePoint)
    return format(global_str, sizeof(global_str), "%s\n{ffffff}- Встроена нашивка: {BD8686}%s", global_str, StripeData[GetStripeID(GetStripeInventoryInfo(playerid, inventoryBlockSlotTypeId, inventoryBlockSlotTypeId == 17 ? (_:!inventoryBlockSlotId + 6) : inventoryBlockSlotId, inventoryStripePoint, E_STRIPE_TYPE_ITEMID))][E_STRIPE_TITLE]), true;

#include "modules/inventory/itemAttributes/stripe_action.inc"
#include "modules/inventory/itemAttributes/stripe_sql.inc"