cmd:fammenu(playerid)
{
	if(!PI[playerid][pFamilyData][0]) 
        return SCM(playerid, COLOR_OLDRED, !"[Ошибка] {FFFFFF}Вы не состоите в одной из семей!");

	return ShowPlayerFamilyTextdraw(playerid);
}

cmd:fam(playerid, params[])
{
	new player_FamilyID = PI[playerid][pFamilyData][0];
	
	if(!player_FamilyID) 
        return SCM(playerid, COLOR_OLDRED, "[Ошибка] {FFFFFF}Вы не состоите в одной из семей!");

	else if(sscanf(params, "s[128]", global_str)) 
        return SCM(playerid, COLOR_OLDRED, "Используйте: /fam [text]");

	else if(Int_GetPlayerData(playerid, "nakaztimer") > Global_Time) return SCM(playerid, COLOR_RED, "[Ошибка]{FFFFFF} Не флуди!");

	Int_SetPlayerData(playerid, "nakaztimer", Global_Time + 5);
	SendFamilyMessageF(player_FamilyID, "{%06x}[Семья] %s %s[%d]:{B9C1B8} %s", ConvertColor(FamilyColorData[FamilyData[player_FamilyID][FamilyInformation][3]]), FamilyRankData[player_FamilyID][PI[playerid][pFamilyData][2]], PN(playerid), playerid, global_str);

	return true;
}

cmd:faminvite(playerid, params[])
{
	new player_FamilyID = PI[playerid][pFamilyData][0];

	if(!player_FamilyID) 
        return SCM(playerid, COLOR_OLDRED, "[Ошибка] {FFFFFF}Вы не состоите в одной из семей!");

	else if(!GetPlayerFamilyHead(playerid)) 
		return SCM(playerid, COLOR_OLDRED, !"[Ошибка] {FFFFFF}Эта команда доступна только лидеру и заместителю!");

	else if(sscanf(params, "u", params[0])) 
		return SCM(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Используйте: /faminvite [id]");

	else if(!IsPlayerOnline(params[0]))
		return false;

	else if(!ProxDetectorS(5.0, playerid, params[0]))
		return callcmd::fammenu(playerid), SCM(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Произошла ошибка, игрок слишком далеко от вас!");

	else if(PI[params[0]][pFamilyData][0])
		return callcmd::fammenu(playerid), SCM(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Произошла ошибка, игрок состоит в другой семьи!");

	else if(PI[params[0]][pLevel] < 2)
	    return callcmd::fammenu(playerid), SCM(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Произошла ошибка, игрок должен иметь уровень выше 2-го!");

	else if(Int_GetPlayerData(params[0], !"playerLastTickInvitedFamily") > Global_Time)
        return callcmd::fammenu(playerid), SCM(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Произошла ошибка, вы уже приглашали этого игрока!");

	SCMF(params[0], COLOR_ORANGE, "[Информация] {FFFFFF}Игрок %s[%d] приглашает вас в семью: {c8ec36}%s.", PN(playerid), playerid, FamilyData[player_FamilyID][FamilyName]);
	SCM(params[0], -1, !"Введите {c8ec36}/acceptfam{FFFFFF} для того чтобы принять предложение, или {ec4636}/cancelfam{FFFFFF}, чтобы отклонить.");
	SCMF(playerid, COLOR_ORANGE, "[Информация] {FFFFFF}Вы успешно предложили %s[%d] вступить в вашу семью!", PN(params[0]), params[0]);

	SetPVarInt(params[0], !"playerFamilyInviteID", playerid);
	return SetPVarInt(params[0], !"playerLastTickInvitedFamily", Global_Time + 120);
}

cmd:famuninvite(playerid, params[])
{
	new player_FamilyID = PI[playerid][pFamilyData][0];

	if(!player_FamilyID)
		return SCM(playerid, COLOR_OLDRED, !"[Ошибка] {FFFFFF}Вы не состоите в одной из семей!");

	else if(!GetPlayerFamilyHead(playerid)) 
		return SCM(playerid, COLOR_OLDRED, !"[Ошибка] {FFFFFF}Эта команда доступна только лидеру и заместителю!");

	else if(sscanf(params, "u", params[0])) 
		return SCM(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Используйте: /famuninvite [id]");

	else if(params[0] == INVALID_PLAYER_ID || GetPlayerFamilyHead(params[0]))
		return false;

	else if(!(PI[params[0]][pFamilyData][0] == player_FamilyID))
		return callcmd::fammenu(playerid), SCM(playerid, COLOR_OLDRED, !"[Ошибка] {FFFFFF}Произошла ошибка, игрок не состоит в вашей семье!");
		
	SendFamilyMessageF(player_FamilyID, "{%06x}[Семья (Новости)] %s[%d]: {B9C1B8}выгнал из семьи: %s[%d]!", ConvertColor(FamilyColorData[FamilyData[player_FamilyID][FamilyInformation][3]]), PN(playerid), playerid, PN(params[0]), params[0]);
	SPDF(params[0], 0, DIALOG_STYLE_MSGBOX, !"Информация", "{FFFFFF}%s[%d] выгнал вас из семьи: %s.", !"Принять", !"", PN(playerid), playerid, FamilyData[player_FamilyID][FamilyName]);
	UpdateFamilyData(player_FamilyID, "Members", FamilyData[playerid][FamilyMembers]--);
	
	return UpdatePlayerDataInt(params[0], "Family", PI[params[0]][pFamilyData][0] = 0);
}

cmd:acceptfam(playerid)
{
	if(Int_GetPlayerData(playerid, !"playerLastTickInvitedFamily") < Global_Time)
		return SCM(playerid, COLOR_OLDRED, !"[Ошибка] {FFFFFF}Вам никто не отправлял предложения вступить в семью!");

	new player_InviteID = Int_GetPlayerData(playerid, !"playerFamilyInviteID"), player_FamilyID = PI[player_InviteID][pFamilyData][0];
	
	if(!ProxDetectorS(5.0, playerid, player_InviteID))
		return SCM(player_InviteID, COLOR_RED, !"[Ошибка] {FFFFFF}Вы слишком далеко от игрока, которого пригласили в семью!"), SCM(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Вы слишком далеко от игрока, который пригласил вас в семью!"), DeletePVar(playerid, !"playerLastTickInvitedFamily");

	PI[player_InviteID][pFamilyData][0] = PI[playerid][pFamilyData][0];
    PI[player_InviteID][pFamilyData][1] = 0;
    PI[player_InviteID][pFamilyData][2] = 1;

    UpdateFamilyData(PI[playerid][pFamilyData][0], "Members", FamilyData[PI[playerid][pFamilyData][0]][FamilyMembers]++);

    SendFamilyMessageF(PI[playerid][pFamilyData][0], "{%06x}[Семья (Новости)] %s[%i]: {B9C1B8}пригласил в семью нового члена: %s[%i]!", ConvertColor(FamilyColorData[FamilyData[PI[playerid][pFamilyData][0]][FamilyInformation][3]]), PN(playerid), playerid, PN(player_InviteID), player_InviteID);
    
    SCMF(playerid, COLOR_ORANGE, "[Информация] {FFFFFF}%s[%i] принял ваше предложение вступить в семью!", PN(player_InviteID), player_InviteID);
	SCMF(player_InviteID, COLOR_ORANGE, "[Информация] {FFFFFF}Вы успешно приняли предложение вступить в семью: {e39f20}%s", FamilyData[PI[playerid][pFamilyData][0]][FamilyName]);
    SCM(player_InviteID, -1, !"Используйте команду /fammenu для подробной информации.");

	DeletePVar(playerid, !"playerFamilyInviteID"); 
	DeletePVar(playerid, !"playerLastTickInvitedFamily");

	return true;
}

cmd:cancelfam(playerid)
{
	if(Int_GetPlayerData(playerid, !"playerLastTickInvitedFamily") < Global_Time)
		return SCM(playerid, COLOR_OLDRED, !"[Ошибка] {FFFFFF}Вам никто не отправлял предложения вступить в семью!");
		
	SCMF(Int_GetPlayerData(playerid, !"playerFamilyInviteID"), COLOR_RED, "[Информация] {FFFFFF}Игрок %s[%d] отказался от вашего предложения на вступление в семью!", PN(playerid), playerid);
	SCM(playerid, COLOR_VALIK, !"[Информация] {FFFFFF}Вы успешно отказались от вступления в семью!");

	DeletePVar(playerid, !"playerLastTickInvitedFamily");
	return DeletePVar(playerid, !"playerFamilyInviteID");
}

cmd:buyfam(playerid)
{
	static player_Family; player_Family = PI[playerid][pFamilyData][0];
	
	if(!player_Family)
		return SCM(playerid, COLOR_OLDRED, !"[Ошибка] {FFFFFF}Вы не состоите в одной из семей!");
	
	else if(!GetPlayerFamilyHead(playerid)) 
		return SCM(playerid, COLOR_OLDRED, !"[Ошибка] {FFFFFF}Эта команда доступна только лидеру и заместителю!");
	
	else if(FamilyData[player_Family][FamilyKvID])
		return SCM(playerid, COLOR_OLDRED, !"[Ошибка] {FFFFFF}В вашей семье уже есть квартира или семейное поместье!");

	else if(pTemp[playerid][playerPosAreaId] == INVALID_DATA_ID || areasData[pTemp[playerid][playerPosAreaId]][areaType] != 43)
		return SCM(playerid, COLOR_OLDRED, !"[Ошибка] {FFFFFF}Вы должны находится возле семейной квартиры которую хотите купить.");

	else if(FamilyData[player_Family][FamilyInformation][0] < 10000)
		return SCM(playerid, COLOR_OLDRED, !"[Ошибка] {FFFFFF}На счету вашей семьи меньше 10000 очков репутации.");
	
	static player_FamilyKV; player_FamilyKV = areasData[pTemp[playerid][playerPosAreaId]][areaId];
	
	FamilyData[player_Family][FamilyInformation][0] -= 10000;

	SQL("UPDATE `family_apartament` SET `FamilyID` = '%d' WHERE ID = %d;", FamilyApartamentData[player_FamilyKV][FamilyApartamentFamilyID] = player_Family, player_FamilyKV);
	SQL("UPDATE `family` SET `KvID` = '%d' WHERE ID = %d;", FamilyData[player_Family][FamilyKvID] = player_FamilyKV, player_Family);
	UpdateFamilyData(player_Family, "Information", Int_PackMassive(0, FamilyData[player_Family][FamilyInformation]));

	SendFamilyMessageF(player_Family, "{%06x}[Семья (Новости)] %s[%d]: {FFFFFF}купил квартиру для семьи!", ConvertColor(FamilyColorData[FamilyData[player_Family][FamilyInformation][3]]), PN(playerid), playerid);
	UpdateFamilyApartament(player_FamilyKV);
	
	return SPD(playerid, 0, DIALOG_STYLE_MSGBOX, !"", !"\n \n{FFFFFF}Вы успешно купили квартиру для своей семьи.\n ", !"Закрыть", !"");
}

cmd:setplayerfamily(playerid, data[])
{
	if(sscanf(data, "dd", data[0], data[1]))
		return SCM(playerid, COLOR_OLDRED, "/setplayerfamily [ fam_id ] [ rang_id ]");

	if(Iter_Contains(Family, data[0]) <= 0)
		return SCM(playerid, COLOR_OLDRED, "fam not found");

	PI[playerid][pFamilyData][0] = data[0];
	PI[playerid][pFamilyData][1] = data[1];

	return SCMF(playerid, COLOR_VALIK, "Вы вступили в семью %s[%d] на %d ранг.", FamilyData[data[0]][FamilyName], data[0], data[1]);
}