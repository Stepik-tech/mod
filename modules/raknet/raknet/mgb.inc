cmd:mgb(playerid)
{
	if(!IsOsnovatel(playerid)) 
		return SCM(playerid, COLOR_RED, !"[Ошибка]{FFFFFF} Неизвестная команда! Введите /help для просмотра доступных функций.");

	return SPDF(playerid, 4460, DIALOG_STYLE_LIST, (str_f("{FFFFFF}Автоматический онлайн: %s", (IsStartBot) ? ("{6495ED}Запущен") : ("{CCCCCC}Остановлен"))), "Настройка\nСтатистика\n%s", "Выбрать", "Закрыть", (IsStartBot) ? ("{6495ED}Запущены") : ("{6495ED}Остановлены"));
}

stock SetCount_bot(playerid)
{
	global_str[0] = EOS;

	for(new i; i < 24; i++) 
	{
		if(AtHourBot[i] != -1) 
			f(global_str, sizeof(global_str), "%s{FFFFFF}Максимальное количество ботов на {6495ED}%i:00 {ffffff}равно %i/%i\n", global_str, i, AtHourBot[i], MAX_PLAYERS-1);

		else f(global_str, sizeof(global_str), "%s{FFFFFF}Боты на {6495ED}%i:00 {ffffff}варьируются от реального онлайна\n", global_str, i);
	}

	SPD(playerid, 4461, DIALOG_STYLE_LIST, !"{FFFFFF}Настройка", global_str, !"Выбрать", !"Назад");
	return 1;
}

stock SetCount_botList(playerid, listitem)
{
	if(listitem < 0 || listitem > 24) 
		return SetCount_bot(playerid);

	global_str[0] = EOS, f(global_str, sizeof(global_str), "{FFFFFF}Введите количество ботов на время %i:00\n{CCCCCC}- Для включения вариация от онлайна, пропишите >- \'-1\'", listitem);
	return spdList(playerid, 0, listitem), SPD(playerid, 4462, DIALOG_STYLE_INPUT, !"Настройки", global_str, !"Принять", !"Назад");
}

stock DeleteBot()
{
	new id = Iter_Random(IsPlayerBot);
	if(Iter_Contains(Player, id) == 1) Kick(id);
}

stock AddBot()
{
	static const InfoNameBot[][] = {
		{"Sergio"},{"Sergey"},{"Dmitriy"},{"Dmitry"},{"Johny"},{"Djon"},{"Jordan"},{"Maxim"},{"Max"},{"Bogdan"},{"Diego"},{"Baby"},{"Danya"},{"Great"},{"Danil"},{"Daniel"},{"Yamato"},{"Santo"},{"Matteo"},{"Slayd"},
		{"Rayn"},{"Cosmo"},{"Alexey"},{"Alex"},{"Morty"},{"Hatory"},{"Kolya"},{"Nikolay"},{"Cursed"},{"Lucifer"},{"Takashi"},{"Tawer"},{"Jack"},{"Benzo"},{"Noro"},{"Thrill"},{"Vova"},{"Vovan"},{"Dapo"},{"Vlad"},
		{"Felix"},{"Roma"},{"Mishka"},{"Daddy"},{"Zero"},{"Maloy"},{"Sam"}
	},
		InfoFamilyBot[][] = {
		{"Revazz"},{"NeOleg"},{"Capone"},{"Ghetto"},{"Pizza"},{"Blitz"},{"Meison"},{"Mason"},{"Long"},{"McDick"},{"Reez"},{"White"},{"Black"},{"Zero"},{"Wizard"},{"Vovk"},{"Killer"},{"Monopoly"},{"Lovlya"},{"XsDick"},
		{"Winston"},{"Toretto"},{"Carter"},{"Lincoln"},{"Castle"},{"Allison"},{"Pimp"},{"Life"},{"Filatov"},{"Side"},{"Didas"},{"xCock"},{"Yosida"},{"Nambovan"},{"Deys"},{"KiberSport"},{"Plaza"},{"Capone"},{"Lowlight"},
		{"High"},{"Cybersport"},{"Bandit"},{"BlackBerry"}
	};
	global_str[0] = EOS, f(global_str, sizeof(global_str), "%s", InfoNameBot[random(sizeof(InfoNameBot))]);
	strcat(global_str, "_");
	f(global_str, sizeof(global_str), "%s%s", global_str, InfoFamilyBot[random(sizeof(InfoFamilyBot))]);
	SetString(botCheckName, global_str);
	PB_RegisterBot(botCheckName);
	ConnectNPC(botCheckName, "pawnbots");
	return botConnect_Timer = 5;
}

stock OnPlayerRegisterSuccess(playerid)
{
	new Cache:result = mysql_query(mysql, (str_f("INSERT INTO `accounts` (`NickName`, `Password`, `Level`, `Sex`, `Race`, `Skin`, `ReferalID`, `Money`, `VirMoney`) VALUES ('%s', '%s', 5, %d, %d, %d, %d, 200000000, 1000000)", PlayerName[playerid], MD5_Hash(PI[playerid][pRegistrationPass]), PI[playerid][pSex], PI[playerid][pRace], PI[playerid][pSkin][0], PI[playerid][pReferalID])));

	if(Iter_Contains(IsPlayerBot, playerid) == 1)
		pTemp[playerid][tSkinSelectedId] = 0;

	PI[playerid][pID] = cache_insert_id();
	cache_delete(result);
	SCM(playerid, COLOR_VALIK, !"[Подсказка] {FFFFFF}Благодарим вас за регистрацию на нашем сервере");
	SCM(playerid, COLOR_VALIK, !"[Подсказка] {FFFFFF}Сейчас вам желательно добраться до мэрии и получить паспорт");

 	foreach(Player, i) {
		if(PI[i][pAdmin] && ADuty{i} && !AdminInfo[i][admInfoNewPlayer]) 
			SCMF(i, -1, "Приветствуем нового игрока нашего сервера: {FF9900}%s {FFFFFF}(ID: %i) {cccccc}IP: %s",PlayerName[playerid], playerid, AdminInfo[i][admIP] ? "Скрыто":PlayerIp[playerid]);
	}

	SetFullness(playerid, 100);
	UpdatePlayerHealth(playerid, 100);

	if(GetPlayerLauncher(playerid) == 2 || pTemp[playerid][cefAuth])
		HideActor(playerid, pTemp[playerid][cefAuthActor]);

	OnPlayerLogin(playerid); 
	return true;
}

new playerRakNet[2];

ORPC:155(playerid, BitStream:bs)
{
	new bytes, otherid, score, ping, BitStream:stream = BS_New();
	BS_GetNumberOfBytesUsed(bs, bytes);
	for(new i = (bytes / 10) - 1; i >= 0; i--)
	{
		BS_ReadValue(bs, PR_UINT16, otherid, PR_INT32, score, PR_UINT32, ping);
		if(!IsPlayerConnected(otherid)) continue;
		playerRakNet[0] = score;
		playerRakNet[1] = ping;
	}
	foreach(Player, i)
	{
		if(Iter_Contains(IsPlayerBot, i) == 1) 
			BS_WriteValue(stream, PR_UINT16, i, PR_INT32, playerRakNet[0], PR_UINT32, playerRakNet[1]);

		else 
			BS_WriteValue(stream, PR_UINT16, i, PR_INT32, 1, PR_UINT32, (playerRakNet[1] + random(10)));
	}

	PR_SendRPC(stream, playerid, 155, PR_LOW_PRIORITY, PR_RELIABLE_ORDERED);
	BS_Delete(stream);
	return 0;
}