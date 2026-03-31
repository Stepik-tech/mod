enum E_ITEM_BUFF
{
	bItemId,
	bItemDefault[11],
	bItemYellow[11],
	bItemWeapon[10],
}

new ItemBuffData[][E_ITEM_BUFF] =
{
	{2157, {0}, {1, 0, 0, 0, 5}},
	{3998, {2}},
	{4001, {0, 0, 4}},
	{4003, {0, 0, 4}},
	{4009, {2}},
	{5650, {1, 2, 0, 2}},
	{5670, {1, 2, 0, 2}},
	{5671, {1, 2, 0, 2}},
	{5674, {2, 0, 0, 1}},
	{5780, {1, 1, 0, 10, 0, 25, 0, 0}},
	{5781, {1, 1, 0, 10, 0, 25, 0, 0}},
	{5782, {1, 1, 0, 10, 0, 25, 0, 0}},
	{5783, {1, 1, 0, 10, 0, 25, 0, 0}},
	{5784, {1, 1, 0, 10, 0, 25, 0, 0}},
	{5785, {1, 1, 0, 10, 0, 25, 0, 0}},
	{5786, {1, 1, 0, 10, 0, 25, 0, 0}},
	{5871, {2, 0, 0, 0, 0, 0, 0, 0, 0}},
	{5925, {1, 0, 0, 25, 0, 0, 0, 0}},
	{5928, {0, 0, 0, 10}},
	{5931, {2, 0, 0, 0, 0, 0, 0, 0}},
	{6264, {0, 0, 0, 3, 0, 0, 0, 0}},
	{6266, {0, 0, 0, 0, 0, 0, 6, 0}},
	{6267, {0, 0, 0, 0, 0, 0, 6, 0}},
	{6268, {0, 0, 0, 0, 0, 0, 6, 0}},
	{6269, {0, 0, 0, 0, 0, 0, 6, 0}},
	{6270, {0, 0, 0, 0, 0, 0, 6, 0}},
	{6271, {0, 0, 0, 0, 0, 0, 6, 0}},
	{6313, {1, 1, 0, 10, 0, 25, 0, 0}},
	{6324, {1, 2, 0, 2, 0, 0, 0, 0}},
	{6330, {0, 0, 0, 2, 0, 0, 0, 0}},
	{6331, {0, 0, 0, 2, 0, 0, 0, 0}},
	{6332, {0, 0, 0, 2, 0, 0, 0, 0}},
	{6333, {0, 0, 0, 2, 0, 0, 0, 0}},
	{6334, {0, 0, 0, 2, 0, 0, 0, 0}},
	{6335, {0, 0, 0, 2, 0, 0, 0, 0}},
	{6520, {1, 1, 0, 10, 0, 25, 0, 0}},
	{6526, {1, 1, 0, 10, 0, 25, 0, 0}},
	{6532, {2, 0, 0, 0, 0, 0, 0, 0}},
	{6543, {2, 0, 0, 0, 0, 0, 0, 0}},
	{6551, {2, 0, 0, 0, 0, 0, 0, 0}},	
	{6556, {1, 0, 0, 1, 0, 0, 0, 0}},
	{6557, {1, 0, 0, 1, 0, 0, 0, 0}},
	{6558, {1, 0, 0, 1, 0, 0, 0, 0}},
	{6559, {1, 0, 0, 1, 0, 0, 0, 0}},
	{6560, {1, 0, 0, 1, 0, 0, 0, 0}},
	{6561, {1, 0, 0, 1, 0, 0, 0, 0}},
	{6562, {1, 0, 0, 1, 0, 0, 0, 0}},
	{6563, {1, 0, 0, 1, 0, 0, 0, 0}},
	{6564, {1, 0, 0, 1, 0, 0, 0, 0}},
	{6565, {1, 0, 0, 1, 0, 0, 0, 0}},
	{6566, {1, 0, 0, 1, 0, 0, 0, 0}},
	{6567, {1, 0, 0, 1, 0, 0, 0, 0}},
	{6568, {1, 0, 0, 1, 0, 0, 0, 0}},
	{6578, {0, 0, 0, 2, 0, 0, 0, 0}},
	{6585, {0, 0, 0, 2, 0, 0, 0, 0}},
	{6605, {0, 4, 0, 0, 0, 0, 0, 0}},
	{6644, {2, 0, 0, 0, 0, 0, 0, 0}},
	{6926, {0, 0, 0, 10, 0, 20, 4, 0}},
	{6931, {0, 0, 0, 10, 0, 20, 4, 0}},
	{7237, {0, 0, 0, 2, 0, 0, 0, 0}},
	{7253, {2, 0, 0, 0, 10, 0, 0, 0, 2}},
	{7258, {2, 0, 0, 0, 0, 0, 0, 0}},
	{7361, {1, 2, 0, 2, 0, 0, 0, 0}},
	{7406, {0, 3, 0, 0, 0, 0, 13, 4}},
	{7409, {0, 0, 0, 10}, {0, 0, 0, 1, 5}},
	{7410, {2, 4, 0, 24, 5, 27, 0, 10}},
	{7726, {0, 0, 0, 2}},
	{7727, {1, 0, 0, 1}},
	{7728, {0, 1, 0, 10, 0, 0, 1}},
	{7705, {0}, {1, 1}},
	{7835, {0}, {0, 2, 0, 0, 0, 10}},
	{7846, {1, 2, 0, 1, 0, 35}},
	{7847, {0}, {2, 0, 0, 0, 0, 10}},
	{7848, {0}, {0, 0, 0, 2, 0, 10}},
	{7849, {0, 0, 0, 10, 0, 20, 4}, {0, 0, 0, 1, 0, 10}},
	{7852, {2, 2, 0, 12, 0, 25}, {0, 2, 0, 0, 5}},
	{7924, {0, 0, 0, 0, 0, 0, 6}},
	{7979, {0, 0, 0, 1, 5, 5}},
	{7981, {1, 0, 0, 25}},
	{7989, {0}, {0, 2}},
	{7996, {0, 0, 0, 1}},
	{8002, {0, 1, 0, 10, 0, 0, 1}},
	{8003, {0}, {0, 0, 0, 0, 5, 5}},
	{8004, {0}, {0, 0, 0, 2, 5, 5}},
	{8008, {1, 1}},
	{8009, {0, 0, 0, 0, 0, 0, 0, 0, 0, 2}},
	{8017, {0}, {1, 1, 0, 5, 5}},
	{8080, {1, 1, 0, 10, 0, 25}},
	{8005, {0}, {2, 2, 0, 5, 5, 0, 0, 0, 6}},
	{8082, {1, 1, 0, 10, 0, 25}},
	{8083, {1, 1, 0, 10, 0, 25}},
	{8130, {0}, {2, 2}},
	{8148, {0}, {0, 2, 0, 4, 0, 0, 3, 0, 1}},
	{8150, {0}, {0, 2, 0, 0, 8, 0, 0, 0, 0, 9}},
	{8151, {0}, {5, 0, 0, 5, 5}},
	{8153, {0}, {0, 0, 0, 3, 0, 4, 0, 0, 1}},
	{8165, {0, 4}},
	{8167, {0}, {0, 2, 0, 0, 10, 7, 0, 0, 1}},
	{8179, {0}, {0, 0, 0, 2, 0, 0, 8, 0, 2}},
	{8183, {0}, {2, 1, 0, 1, 10}},
	{8184, {1, 1, 0, 1}},
	{8185, {0, 4}, {1, 1, 0, 0, 6, 5}},
	{8186, {0}, {2, 1, 0, 1, 10}},
	{8197, {2, 0, 0, 0, 0, 10, 5}},
	{8202, {0, 0, 0, 2, 0, 0, 10, 0, 0, 0, 20}},
	{8206, {0, 2, 0, 0, 5, 0, 10}}
};

/*
	0 — Защита
	1 — Урон
	2 — HP в мин.
	3 — Удача: шанс крит.урона
	4 — Макс. ХП
	5 — Макс. Брони
	6 — Шанс оглушения
	7 — Шанс избежать оглушения
	8 — Шанс опьянения
	9 - Шанс отражения урона
	10 - Шанс воскрешения
*/

stock GetItemBuff(itemId, buffId, buffType = 0)
{
	for(new i; i < sizeof(ItemBuffData); i++)
	{
		if(ItemBuffData[i][bItemId] != itemId)
			continue;

		if(buffType == 0)
			return ItemBuffData[i][bItemDefault][buffId];

		else if(buffType == 1)
			return ItemBuffData[i][bItemYellow][buffId];

		else if(buffType == 2)
			return ItemBuffData[i][bItemWeapon][buffId];
	}

	return INVALID_DATA_ID;
}

stock InventoryAccessoryPlayerUseable(playerid, inventoryAccessorySlotId)
{
	if(!playerAccessoriesCreated[playerid][inventoryAccessorySlotId])
		return false;

	switch(GetInventoryBlockSlotData(playerid, inventoryAccessorySlotId, 2, InventoryItemID))
	{
		case 168:
		{
			if(!GetPlayerLauncher(playerid))
				return SCM(playerid, COLOR_OLDRED, !"[Ошибка]{FFFFFF} Скейт доступен только с лаунчера!");
				
			if(!addskate[playerid])
			{
				RemovePlayerAttachedObject(playerid, 5);
				SetPlayerAttachedObject(playerid, 6, 19878, 6, -0.055999, 0.013000, 0.000000, -84.099983, 0.000000, -106.099998, 1.000000, 1.000000, 1.000000);
				SCM(playerid, COLOR_GREEN, !"Вы взяли скейт в руку, чтобы его использовать зажмите 'КЛАВИШУ ДЛЯ БЕГА'");
				addskate[playerid] = 1;
			}
			else
			{
				RemovePlayerAttachedObject(playerid, 6);
				SetPlayerAccessory(playerid, AksSlot[playerid][0][5], 5);
				addskate[playerid] = 0;
			}
		}
		
		case 2181:
		{
			if(CountVehicles() >= MAX_VEHICLES - 1 or AnimPlayed{playerid} or !(GetPlayerState(playerid) == 1)) return SendErrorMessage(playerid);

			new Float:X, Float:Y, Float:Z, Float:A;
			GetPlayerPos(playerid, X, Y, Z), GetPlayerFacingAngle(playerid, A);

			PLVEH_destroy(playerid);
			
			PI[playerid][plveh] = J_AddStaticVehicleEx(GetPlayerLauncher(playerid) ? 14916 : 510, X, Y, Z, A, 1, 1), PutPlayerInVehicle(playerid, PI[playerid][plveh], 0);

			SetVehicleEngineToggle(PI[playerid][plveh], true);
			RemovePlayerAttachedObject(playerid, 5);
		}
		case 2182:
		{
			if(CountVehicles() >= MAX_VEHICLES - 1 or AnimPlayed{playerid} or !(GetPlayerState(playerid) == 1)) return SendErrorMessage(playerid);
			else if(!GetPlayerLauncher(playerid)) return SCM(playerid, COLOR_OLDRED, "[Ошибка]{FFFFFF} Дельтаплан доступен только с лаунчера!");

			new Float:X, Float:Y, Float:Z, Float:A;
			GetPlayerPos(playerid, X, Y, Z), GetPlayerFacingAngle(playerid, A);

			PLVEH_destroy(playerid);

			PI[playerid][plveh] = J_AddStaticVehicleEx(4800, X, Y, Z, A, 1, 1), PutPlayerInVehicle(playerid, PI[playerid][plveh], 0);

			SetVehicleEngineToggle(PI[playerid][plveh], true);
			RemovePlayerAttachedObject(playerid, 5);
		}
		
		case 181: callcmd::boom(playerid);
		case 182: _GiveGun(playerid, 2, 1);
		case 183: _GiveGun(playerid, 5, 1);
		case 184: _GiveGun(playerid, 6, 1);
		case 185: _GiveGun(playerid, 7, 1);
		case 186: _GiveGun(playerid, 8, 1);
		case 187: _GiveGun(playerid, 15, 1);
		case 188..190: onboard(playerid);
		case 743..747: callcmd::rcveh(playerid);

		case 1134..1140, 5780..5786, 7410:
		{
			if(SharInfo[playerid][sharStatus])
				return SCM(playerid, COLOR_RED, !"[Ошибка]{FFFFFF} Вы уже используете воздушный шар.");

			else if(GetPlayerGZ(playerid))
				return SCM(playerid, COLOR_RED, !"[Ошибка]{FFFFFF} В зеленой зоне нельзя развернуть воздушный шар.");

			else if(CountVehicles() >= 1999)
				return SendErrorMessage(playerid);

			SharInfo[playerid][sharStatus] = true;
			CreateSharik(playerid, ItemsInfo[ AksSlot[playerid][0][slot] ][itemModel]);
		}

		case 1159: callcmd::remkey(playerid);
		case 1164: _GiveGun(playerid, 43, 20);

		case 7361:
		{
			if(!GetPlayerLauncher(playerid)) 
				return SCM(playerid, COLOR_OLDRED, "[Ошибка]{FFFFFF} Джетпак доступен только с лаунчера!");

			if(GlobalMassive[playerid][30])
				return GlobalMassive[playerid][30] = false, SetPlayerSpecialAction(playerid, 0);

			GlobalMassive[playerid][29] = true;
			PlayerHudActionHide(playerid),
			SystemTextDrawHide(playerid), CancelSelectTextDraw(playerid),
			SendPlayerInterfaceToggle(playerid, false), 

			//SendPlayerChangeBrowserPicture(playerid, 1, "file:///frontend/effects/jetpack/index.html"), 
			sendPlayerActionBar(playerid, "Развертывание джетпака", 7);
			//playZoneAZVoice(GetRadioZone(playerid, 2), "http://arizona.gtasounds.com/sound_effect/sound_jetpack_effect.mp3", 0, playerid);
		}
	}

	return SendPlayerDebug(playerid, "(InventoryAccessoryPlayerUseable) функция выполнена успешно");
}

stock GetStripeInfo(stripe_id, type)
{
	new stripe_return;

	switch stripe_id do
	{
		//acs stripe
		case 1..3: stripe_return = (type > 0 ? 0 : stripe_id);
		case 4..6: stripe_return = (type == 1 ? 1 : type == 2 ? 2 : stripe_id - 3);
		case 7..9: stripe_return = (type == 1 ? 2 : type == 2 ? 1 : stripe_id - 6);
		case 10..12: stripe_return = (type == 1 ? 3 : type == 2 ? 3 : stripe_id - 9);
		case 13..15: stripe_return = (type == 1 ? 4 : type == 2 ? 4 : stripe_id - 12);
		//skin stripe
		case 16: stripe_return = (type == 1 ? 5 : type == 2 ? 0 : stripe_id);
		case 17: stripe_return = (type == 1 ? 6 : type == 2 ? 11 : stripe_id);
		case 18: stripe_return = (type == 1 ? 7 : type == 2 ? 12 : stripe_id);
		case 19: stripe_return = (type == 1 ? 8 : type == 2 ? 13 : stripe_id);
		case 20: stripe_return = (type == 1 ? 9 : type == 2 ? 14 : stripe_id);
		case 21: stripe_return = (type == 1 ? 10 : type == 2 ? 15 : stripe_id);
		//other stripe
		case 22: stripe_return = (type == 1 ? 11 : type == 2 ? 16 : stripe_id);
		case 23: stripe_return = (type == 1 ? 12 : type == 2 ? 7 : 20);
	}

	return stripe_return;
}

stock GetAccessoryUpgradeBuff(itemid)
{
	switch(itemid)
	{
		case 7253: return 0;
		default:
		{
			if(ItemsInfo[itemid][itemType] == 6 && !ItemsInfo[itemid][itemAccessorySlot])
				return 4;

			else
			{
				if(ItemsInfo[itemid][itemAccessorySlot] == 1 or ItemsInfo[itemid][itemAccessorySlot] == 4) return 0;
				else if(ItemsInfo[itemid][itemAccessorySlot] == 2 or ItemsInfo[itemid][itemAccessorySlot] == 3) return 2;
				else if(ItemsInfo[itemid][itemAccessorySlot] == 0 or ItemsInfo[itemid][itemAccessorySlot] == 5) return 3;
			}
		}
	}

	return 4;
}

stock GetBuffColor(itemId, buffid)
{
	static string[8]; string[0] = EOS;
	format(string, sizeof(string), "%s", GetItemBuff(itemId, buffid) > 0 ? "73B461" : "B83434");
    return string;
}

stock GetAccessoryPlayerBuff(playerid, type)
{
	new amount_buff = 0;
	static max_buff_amount[] = {90, 0, 66, 82, 0, 160, 0, 0, 0};

	if(ItemsInfo[GetInventoryBlockSlotData(playerid, 0, 22, InventoryItemID)][itemModel] > 311)
		amount_buff += FindAccessoryBuffUsed(playerid, 0, 22, GetInventoryBlockSlotData(playerid, 0, 22, InventoryItemID), type, GetInventoryBlockSlotData(playerid, 0, 22, InventoryEnchanted), true);

	for(new i; i < 8; i++)
	{
		if(GetInventoryBlockSlotData(playerid, i, 2, InventoryMending) <= 10)
			continue;

		amount_buff += FindAccessoryBuffUsed(playerid, i, 2, GetInventoryBlockSlotData(playerid, i, 2, InventoryItemID), type, GetInventoryBlockSlotData(playerid, i, 2, InventoryEnchanted), true);

		if(GetInventoryBlockSlotData(playerid, i, 2, InventoryUnicalityID) > 0 && type == GetStripeInfo(GetInventoryBlockSlotData(playerid, i, 2, InventoryUnicalityID), 2))
			amount_buff += GetStripeInfo(GetInventoryBlockSlotData(playerid, i, 2, InventoryUnicalityID), 0);

		if(type == 0)
			amount_buff += 3;

		if(PlayerAccessoriesData[playerid][3][i] == 13)
			amount_buff += (type == 4 ? 4 : type == 5 ? 9 : 0);

		if(max_buff_amount[type] != 0 && amount_buff > max_buff_amount[type])
			amount_buff = max_buff_amount[type];
	}

	return amount_buff;
}

stock FindAccessoryBuffUsed(playerid, slot, blockid, item, type, enchant, bool:playerUsed = false)
{
	new buff[9];

	if(ItemsInfo[item][itemModel] > 311 && IsItemSkin(item))
	{	
		buff[4] += buff[5] += enchant;

		if(enchant == 3 or enchant == 5 or enchant == 8 or enchant >= 10)
			buff[0] += floatround(0.66666666666 * enchant, floatround_ceil), buff[1] += buff[2] += buff[3] += floatround(0.33333333333 * enchant, floatround_ceil);

		if(enchant >= 10 && buff[0] != 8)
			buff[0] = 8, buff[1] = buff[2] = buff[3] = 4;
	}

	for(new i; i < 2; i++)
	{
		if(i && !playerUsed)
			continue;
			
		if(GetInventoryBlockSlotData(playerid, slot, blockid, InventoryDisassemble) > 0)
			item = GetInventoryBlockSlotData(playerid, slot, blockid, InventoryDisassemble);

		if(GetItemBuff(item, type, i) > 0) 
		{
			buff[type] += GetItemBuff(item, type, i);

			if(type == 0)
				buff[0] += 1;
		}
	}

	if(type == 5 && ItemsInfo[item][itemType] == 6 && !ItemsInfo[item][itemAccessorySlot])
		buff[5] += 5 * enchant;

	if(enchant >= 4)
	{
		if(GetAccessoryUpgradeBuff(item) == type)
		{
			switch type do
			{
				case 0: 
					buff[0] += floatround(2.222222 * (enchant - 4));

				case 2, 3: 
					buff[type] += 1 + (enchant - 4);
			}
		}
	}

	return buff[type];
}