const MAX_FAMILY = 50,
    MAX_APARTAMENT = 150;

enum 
{
    FamilyDialogInformationSelect,
    FamilyDialogInformation,
    FamilyDialogColorSelect,
    FamilyDialogTypeSelect,
    FamilyDialogRankSelect
}

enum familyData
{
    FamilyID,
    FamilyLeaderID,
    FamilyZamsID[3],
    FamilyName[32],
    FamilySlogan[40],
    FamilyDiscord[64],
    FamilyInformation[9], /* reputation (0) & level (1) & exp (2) & color (3) & type (4) & jackdaw (5) & brend (6) & zlovesh reputation (7) & fraction (8) */
    FamilyPercentDeposit,
    FamilyKvID,
    FamilySpawnData[2], /* type (0) & id (1) */
    FamilyAllianceID[2], /* alliance Owner Family (0) & alliance */
    FamilyFlagID,
    FamilyImprovement[10], /* deputy 3 (0) */
    FamilyMembers,
    FamilyAZVoiceZone
}

enum familyApartamentsData
{
    FamilyApartamentID,
    FamilyApartamentFamilyID,
    FamilyApartamentLocked,
    Float:FamilyApartamentPosition[3],
    STREAMER_TAG_3D_TEXT_LABEL:FamilyApartament3DText,
    STREAMER_TAG_PICKUP:FamilyApartamentPickup
}

enum familyApartamentsMainData
{
    Float:FamilyApartamentsEnterPosition[3],
    Float:FamilyApartamentsExitPosition[3],
    Float:FamilyApartamentsInfoPosition[3],
    Float:FamilyApartamentsAutoPosition[3],
    Float:FamilyApartamentsPositions[8],
    STREAMER_TAG_3D_TEXT_LABEL:FamilyApartaments3DText[4],
    STREAMER_TAG_PICKUP:FamilyApartamentsPickup[4]
}

new FamilyData[MAX_FAMILY][familyData],
    FamilyApartamentData[MAX_APARTAMENT][familyApartamentsData],
    FamilyApartamentMainData[][familyApartamentsMainData] = 
    {
        {{1803.0518, 410.1965, 20.2294}, {2790.6895, 739.5587, 1500.1187}, {2786.4941, 739.5807, 1500.6187}, {1794.3065, 413.8255, 20.2294}, {2788.6782, 738.2451, 1500.1187, 138.3252, 1802.9182, 407.6309, 20.2294, 175.2988}},
        {{2461.4653, 2245.1494, 10.8203}, {1574.8331, 1332.4812, 10.8588}, {1564.3380, 1334.6041, 11.3665}, {2504.7102, 2242.5874, 10.820}, {1572.3121, 1332.4218, 10.8606, 90.0000, 2461.3877, 2242.3989, 10.8203, 176.6225}},
        {{-2050.9075, 450.4305, 35.1719}, {1898.8167, 740.3824, 1500.1459}, {1891.0282, 740.3294, 1500.6460}, {-2017.0059, 445.0810, 35.1723}, {1895.8622, 740.1544, 1500.1459, 90.1548, -2049.5986, 453.7315, 35.1719, 336.0418}}
    },
    FamilyRankData[MAX_FAMILY][10][30],
    FamilyTypeName[][][] = 
    {
        {"Family", "Семья", 1}, 
		{"Corporation", "Корпорация", 10}, 
		{"Crew", "Команда", 20}, 
		{"Squad", "Отряд", 30}, 
		{"Brotherhood", "Братство", 40}, 
		{"Dynasty", "Dynasty", 75}, 
		{"Empire", "Empire", 100},
		{"Club", "Club", 150},
		{"Gang", "Gang", 200},
		{"Mafia", "Mafia", 250},
		{"Syndicate", "Syndicate", 300},
		{"Union", "Union", 350},
		{"Guys", "Guys", 400},
		{"Boys", "Boys", 450}
    },
    FamilyColorData[] =
	{
		0xFF5E5EFF, 0xFFFFFFFF, 0xE65075FF, 0xEFA4B7FF, 0x905B69FF, 0xD052CEFF, 0xFF00FCFF, 0x5D395DFF, 0x8E38EAFF, 0x6B21BBFF, 0x2F00FFFF, 0x7456F8FF, 0x5287F1FF, 0x1DBAF2FF, 
        0x308EB0FF, 0x30B061FF, 0x20F271FF, 0x107135FF, 0x47EB2AFF, 0x9EE991FF, 0xC2D95EFF, 0xD1FF00FF, 0x7B9022FF, 0xFFC900FF, 0xE8CA60FF, 0x6B5B1FFF, 0xFF8400FF, 0xC04312FF, 
        0x5C4C45FF, 0x373534FF, 0x351204FF
    },
    PlayerText:FamilyTextdraw[MAX_PLAYERS][99],
    bool:FamilyPlayerTextdrawOpen[MAX_PLAYERS char],
    bool:FamilyPlayerManagementOpen[MAX_PLAYERS char],
    Iterator:Family<MAX_FAMILY>;

public: @LoadFamily()
{
    if(!cache_num_rows())
        return false;

    global_str = "";

    for(new i, id; i < cache_num_rows(); i++)
    {
        cache_get_value_name_int(i, "ID", id), FamilyData[id][FamilyID] = id;
        cache_get_value_name_int(i, "LeaderID", FamilyData[id][FamilyLeaderID]);
        cache_get_value_name(i, "ZamsID", global_str), sscanf(global_str, "P<,>a<i>[3]", FamilyData[id][FamilyZamsID]);
        cache_get_value_name(i, "Name", FamilyData[id][FamilyName]);
        cache_get_value_name(i, "Slogan", FamilyData[id][FamilySlogan]);
        cache_get_value_name(i, "Discord", FamilyData[id][FamilyDiscord]);
        cache_get_value_name(i, "Information", global_str), sscanf(global_str, "P<,>a<i>[9]", FamilyData[id][FamilyInformation]);
        cache_get_value_name_int(i, "PercentDeposit", FamilyData[id][FamilyPercentDeposit]);
        cache_get_value_name_int(i, "KvID", FamilyData[id][FamilyKvID]);
        cache_get_value_name(i, "SpawnData", global_str), sscanf(global_str, "P<,>a<i>[2]", FamilyData[id][FamilySpawnData]);
        cache_get_value_name(i, "Rank", global_str), sscanf(global_str, "P<,>s[30]s[30]s[30]s[30]s[30]s[30]s[30]s[30]s[30]s[30]", FamilyRankData[id][0], FamilyRankData[id][1], FamilyRankData[id][2], FamilyRankData[id][3], FamilyRankData[id][4], FamilyRankData[id][5], FamilyRankData[id][6], FamilyRankData[id][7], FamilyRankData[id][8], FamilyRankData[id][9]);
        cache_get_value_name_int(i, "Members", FamilyData[id][FamilyMembers]);

        FamilyData[id][FamilyAZVoiceZone] = CreateAZVoiceZone(1, 0, "Семейный", FamilyColorData[FamilyData[id][FamilyInformation][3]]);
        Iter_Add(Family, id);
    }

    return true;
}

public: @LoadFamilyApartament()
{
    if(!cache_num_rows())
        return false;

    global_str = "";

    for(new i, id; i < cache_num_rows(); i++)
    {
        cache_get_value_name_int(i, "ID", id), FamilyApartamentData[id][FamilyApartamentID] = id;
        cache_get_value_name_int(i, "FamilyID", FamilyApartamentData[id][FamilyApartamentFamilyID]);
        cache_get_value_name(i, "Position", global_str), sscanf(global_str, "P<,>a<f>[3]", FamilyApartamentData[id][FamilyApartamentPosition]);
        cache_get_value_name_int(i, "Lock", FamilyApartamentData[id][FamilyApartamentLocked]);
        UpdateFamilyApartament(id);
    }

    return true;
}

stock ShowPlayerFamilyTextdraw(playerid, bool:management = false)
{
    if(FamilyPlayerTextdrawOpen{playerid})
        HidePlayerFamilyTextdraw(playerid, false);

    new player_FamilyID = PI[playerid][pFamilyData][0];

    #include modules/family/textdraw

    for(new i; i < (management ? 83 : sizeof(FamilyTextdraw[])); i++)
        ShowPlayerTD(playerid, FamilyTextdraw[playerid][i]);

    FamilyPlayerTextdrawOpen{playerid} = true;
    FamilyPlayerManagementOpen{playerid} = management;

    SelectTextDraw(playerid, 0x994545FF);

    return SendPlayerDebug(playerid, "(ShowPlayerFamilyTextdraw) завершен.");
}

stock HidePlayerFamilyTextdraw(playerid, bool:call_CancelSelectTextdraw = true)
{
    for(new i; i < sizeof(FamilyTextdraw[]); i++)
        DestroyPlayerTD(playerid, FamilyTextdraw[playerid][i]);

    FamilyPlayerTextdrawOpen{playerid} =
    FamilyPlayerManagementOpen{playerid} = false;

    if(call_CancelSelectTextdraw)
        CancelSelectTextDraw(playerid);

    return SendPlayerDebug(playerid, "(HidePlayerFamilyTextdraw) завершен.");
}

stock fam_OnPlayerClickPlayerTextdraw(playerid, PlayerText:playertextid)
{
    new player_FamilyID = PI[playerid][pFamilyData][0];

    if(!player_FamilyID)
        return false;

    for(new i; i < sizeof(FamilyTextdraw[]); i++)
    {
        if(playertextid == FamilyTextdraw[playerid][i])
        {
            switch(i)
            {
                case 4:
                {
                    if(!FamilyPlayerManagementOpen{playerid})
                        return ShowPlayerFamilyTextdraw(playerid, true);
                }

                case 6:
                {
                    if(!FamilyPlayerManagementOpen{playerid})
                       FamilyDialogData(playerid, FamilyDialogInformationSelect);
                }

                case 8:
                {
                    if(FamilyPlayerManagementOpen{playerid})
                        FamilyDialogData(playerid, FamilyDialogColorSelect);
                }

                case 10:
                {
                    if(FamilyPlayerManagementOpen{playerid})
                        FamilyDialogData(playerid, FamilyDialogTypeSelect);
                }

                case 14:
                {
                    if(!FamilyPlayerManagementOpen{playerid})
                    {
                        if(PI[playerid][pID] == FamilyData[player_FamilyID][FamilyLeaderID])
                            return SCM(playerid, COLOR_OLDRED, !"[Ошибка] {FFFFFF}Лидер не может покинуть семью!");
                    }
                }

                case 16:
                {
                    if(FamilyPlayerManagementOpen{playerid})
                        FamilyDialogData(playerid, FamilyDialogRankSelect);
                }
            }

            HidePlayerFamilyTextdraw(playerid, true);
            SendPlayerDebugF(playerid, "(family_OnPlayerClickPlayerTextdraw) clickId: %i", i);
        }
    }

    return true;
}

stock FamilyDialogData(playerid, dialog_type)
{
    new player_FamilyID = PI[playerid][pFamilyData][0];

    if(!player_FamilyID)
        return false;

    global_str = "";

    switch(dialog_type)
    {
        case FamilyDialogInformationSelect:
            SPD(playerid, 27086, DIALOG_STYLE_LIST, !"Информация", "{C0C0C0}[1] {FFFFFF}Посмотреть общую информацию\n{C0C0C0}[2] {FFFFFF}Бонусы и улучшения семьи\n{C0C0C0}[3] {FFFFFF}Информация об альянсе {FA8072}[ Нет ]\n{C0C0C0}[4] {FFFFFF}Семейные территории и предприятия {FA8072}[ Нет ]", !"Выбрать", !"Закрыть");
    
        case FamilyDialogInformation:
        {
            static familyColor; familyColor = ConvertColor(FamilyColorData[FamilyData[player_FamilyID][FamilyInformation][3]]);

            f(global_str, sizeof(global_str), "\
                {FFFFFF}\n\n\
                Название семьи: {%06x}%s [fam id: %i]{FFFFFF}\n\
                Тип семьи: {%06x}%s{FFFFFF}\n\
                Репутация семьи: {%06x}%i очк.{FFFFFF}\n\
                Зловещая репутация семьи: {%06x}%i очк.{FFFFFF}\n\
                Уровень семьи: {%06x}%i [%i/%i]{FFFFFF}\n\
                Членов в семье: {%06x}%d человек{FFFFFF} из {%06x}510 человек\n\
                Идёт в казну с депозитов членов семьи: {%06x}%i%{FFFFFF}\n\
                Местоположение спавна: {%06x}Нет{FFFFFF}\n\
                Денег в бюджете семьи: {%06x}$-1{FFFFFF}\n\
                Семейных монет на складе: {%06x}-1 шт.{FFFFFF}\n\
                Discord: {%06x}[ %s ]{FFFFFF}\n\n",
            familyColor, FamilyData[player_FamilyID][FamilyName], FamilyData[player_FamilyID][FamilyID],
            familyColor, FamilyTypeName[FamilyData[player_FamilyID][FamilyInformation][4]][0],
            familyColor, FamilyData[player_FamilyID][FamilyInformation][0],
            familyColor, FamilyData[player_FamilyID][FamilyInformation][7],
            familyColor, FamilyData[player_FamilyID][FamilyInformation][1], FamilyData[player_FamilyID][FamilyInformation][2], FamilyData[player_FamilyID][FamilyInformation][1] * 10,
            familyColor, FamilyData[player_FamilyID][FamilyMembers], familyColor,
            familyColor, FamilyData[player_FamilyID][FamilyPercentDeposit],
            familyColor,
            familyColor, 
            familyColor,
            familyColor, FamilyData[player_FamilyID][FamilyDiscord]);

            static const ownerName[][] = {"Лидер семьи", "Заместитель", "Заместитель 2", "Заместитель 3"};
            for(new i; i < 4; i++)
                f(global_str, sizeof(global_str), "%s%s: {%06x}%s{FFFFFF}\n", global_str, ownerName[i], familyColor, !i ? (OnPlayerFindNameByAccountID(FamilyData[player_FamilyID][FamilyLeaderID], SQL_GET_ROW_STR[0]), SQL_GET_ROW_STR[0]) : FamilyData[player_FamilyID][FamilyZamsID][i - 1] != -1 ? (OnPlayerFindNameByAccountID(FamilyData[player_FamilyID][FamilyZamsID][i - 1], SQL_GET_ROW_STR[0]), SQL_GET_ROW_STR[0]) : "{FFFFFF}[{FF8859}Нет{FFFFFF}]");

            f(global_str, sizeof(global_str), "%s\
                \nСлоган: {%06x}%s{FFFFFF}\n\
                Содержание улучшений: {%06x}0 репутации в сутки{FFFFFF}\n\
                Содержание квартиры: {%06x}0 репутации в PayDay{FFFFFF}\n\
                Содержание участников: {%06x}0 репутации в PayDay{FFFFFF}\n\
                Содержание фургонов: {%06x}3 репутации в PayDay за каждый фургон\n\n\n\
                \
                {ffffff}Семейный флаг: {ffffff}Нет\n\n\
                \
                {FFFFFF}Семейная частная фракция: {%06x}Нет{FFFFFF}\n\
                {FFFFFF}Обьявление: \n\n\
                \
                {D4D4D4}1\n\
                {D4D4D4}2\n\
                {D4D4D4}3\n\
                {D4D4D4}4\n\
                {D4D4D4}5\n\
                {D4D4D4}6\n\n\n\n\n\n\
                \
                {ffffff}Информация об ограничениях за текущий час (для заместителей):\n\
	                - Уволено игроков: 0/5\n\
	                - Потрачено семейной репутации{CCCCCC}(закупка аптечек/бронежилетов){ffffff}: 0/5000\n\n\
                \
                {ff6666}Примечания:{cccccc}\n\
                - Семейные улучшения действуют только при наличии семейной квартиры.\n\
                - Если квартира будет отобрана по налогам или по недостатку репутации, то улучшения будут очищены. Продажа между семьями сохраняет улучшения.\n\
                - Флаг семьи будет очищен, если семейная квартира будет продана любым способом.\n\
                - Семейная частная фракция остается при утере семейной квартиры.\n\
                - Семейный автопарк не очищается при утере квартиры и будет доступен при повторном приобретении семейной недвижимости.", 
            global_str, familyColor, FamilyData[player_FamilyID][FamilySlogan],
            familyColor, 
            familyColor, 
            familyColor, 
            familyColor, 
            familyColor);

            SPD(playerid, 27085, 0, !"Информация о семье", global_str, !"Назад", !"Закрыть");
        }

        case FamilyDialogColorSelect:
        {
            global_str = "{FFFFFF}\n\n\
                \
                - Цвет семьи, функция которая даст вам возможность сделать небольшое отличие от других семей!\n\
                Цвет семьи используется:\n\n\
                \
                {F58558}- В рации семьи.\n\
                - В статистике семьи.\n\
                - В названии семьи, над головой персонажа.\n\
                - Система будет дополнятся в процессе обновлений.{FFFFFF}\n\n\
                \
                Введите в окошко цифру, цвет которой вам нравится больше всего:\n\
                {FF5E5E}0, {FFFFFF}1, {E65075}2, {EFA4B7}3, {905B69}4, {D052CE}5, {FF00FC}6, {5D395D}7, {8E38EA}8, {6B21BB}9,{2F00FF}10, {7456F8}11, {5287F1}12, {1DBAF2}13, {308EB0}14, {30B061}15, {20F271}16, {107135}17, {47EB2A}18, {9EE991}19, {C2D95E}20, {D1FF00}21, {7B9022}22, {FFC900}23, {E8CA60}24, {6B5B1F}25, {FF8400}26, {C04312}27, {5C4C45}28, {373534}29, {351204}30.\n\n";

            SPD(playerid, 2922, DIALOG_STYLE_INPUT, !"", global_str, !"Принять", !"Назад");
        }

        case FamilyDialogTypeSelect:
        {
            for(new i; i < sizeof(FamilyTypeName); i++)
                f(global_str, sizeof(global_str), "%s{D4D4D4}[{%s}%s{D4D4D4}] %s\n", global_str, FamilyData[player_FamilyID][FamilyInformation][1] >= FamilyTypeName[i][2][0] ? "8DFD4C" : "FD4C4C", FamilyData[player_FamilyID][FamilyInformation][1] >= FamilyTypeName[i][2][0] ? "+" : "-", FamilyTypeName[i][0]);

            SPD(playerid, 7521, DIALOG_STYLE_LIST, !"", global_str, !"Принять", !"Отмена");
        }

        case FamilyDialogRankSelect:
        {
            for(new i; i < 10; i++)
                f(global_str, sizeof(global_str), "%s[%i] %s\n", global_str, i + 1, FamilyRankData[player_FamilyID][i]);

            SPD(playerid, 15022, DIALOG_STYLE_LIST, !"Ранги семьи", global_str, !"Выбрать", !"Назад");
        }
    }

    return true;
}

stock GetPlayerFamilyHead(playerid)
    return (FamilyData[PI[playerid][pFamilyData][0]][FamilyLeaderID] == PI[playerid][pID] || IsAFamilyZam(playerid));

stock IsAFamilyZam(playerid)
{
    for(new i; i < 3; i++)
        if(FamilyData[PI[playerid][pFamilyData][0]][FamilyZamsID][i] == PI[playerid][pID])
            return true;

    return false;
}

stock SendFamilyMessage(family_id, const message[])
{
    foreach(Player, playerid)
    {
        if(!IsPlayerOnline(playerid) || (family_id != INVALID_DATA_ID && PI[playerid][pFamilyData][0] != family_id))
            continue;

        SCM(playerid, 0xB9C1B8FF, message);
    }

    return true;
}
/*
    [09:54:35.573152] (script)	packet_hooker (2).lua: 27086, 2, {BFBBBA}Информация, Выбрать, Закрыть, {C0C0C0}[1] {FFFFFF}Посмотреть общую информацию
{C0C0C0}[2] {FFFFFF}Бонусы и улучшения семьи
{C0C0C0}[3] {FFFFFF}Информация об альянсе {FA8072}[ Нет ]
{C0C0C0}[4] {FFFFFF}Семейные территории и предприятия {FA8072}[ Нет ]
[09:54:36.711340] (script)	packet_hooker (2).lua: [RakLuaEvents.INCOMING_PACKET(220)] browserId -> 0 & eventTextLen -> 60 & eventText -> window.executeEvent('event.setActiveView', `["NpcDialog"]`);
[09:54:36.712333] (script)	packet_hooker (2).lua: [RakLuaEvents.INCOMING_PACKET(220)] browserId -> 0 & eventTextLen -> 66 & eventText -> window.executeEvent('event.arizonahud.hotkeysVisible', `[false]`);
[09:54:36.712333] (script)	packet_hooker (2).lua: [RakLuaEvents.INCOMING_PACKET(220)] browserId -> 0 & eventTextLen -> 73 & eventText -> window.executeEvent('event.hudSA.updateSanAndreasHudVisible', `[false]`);
[09:54:36.712333] (script)	packet_hooker (2).lua: [RakLuaEvents.INCOMING_PACKET(220)] browserId -> 0 & eventTextLen -> 70 & eventText -> window.executeEvent('event.arizonahud.activeQuestVisible', `[false]`);
[09:54:36.713318] (script)	packet_hooker (2).lua: [RakLuaEvents.INCOMING_PACKET(220)] browserId -> 0 & eventTextLen -> 66 & eventText -> window.executeEvent('event.arizonahud.hotkeysVisible', `[false]`);
[09:54:36.713318] (script)	packet_hooker (2).lua: [RakLuaEvents.INCOMING_PACKET(220)] browserId -> 0 & eventTextLen -> 73 & eventText -> window.executeEvent('event.hudSA.updateSanAndreasHudVisible', `[false]`);
[09:54:36.713318] (script)	packet_hooker (2).lua: [RakLuaEvents.INCOMING_PACKET(220)] browserId -> 0 & eventTextLen -> 65 & eventText -> window.executeEvent('event.npcDialog.initializeRewards', `[[]]`);
[09:54:36.713318] (script)	packet_hooker (2).lua: [RakLuaEvents.INCOMING_PACKET(220)] browserId -> 0 & eventTextLen -> 404 & eventText -> window.executeEvent('event.npcDialog.initializeDialog', `[{"id":0,"title":"","text":"Привет, ты куда-то пропал, ничего не случилось?
Готов вернуться к выполнению моего задания?

Я отправил тебе место, куда нужно съездить, давай только шустрее!","backgroundColor":"rgba(19, 21, 22, 0.65)","hoverColor":"rgba(19, 21, 22, 0.55)","keyboard": [[ {"id":1,"icon":"&#128526;","text":"Окей, выдвигаюсь!"} ]] }]`);
[09:54:39.962973] (script)	packet_hooker (2).lua: 27085, 0, {BFBBBA}Информация о семье, Назад, Закрыть, {FFFFFF}

Название семьи: {47EB2A}Fujiwara [fam id: 361]{FFFFFF}
Тип семьи: {47EB2A}Corporation{FFFFFF}
Репутация семьи: {47EB2A}10183 очк.{FFFFFF}
Зловещая репутация семьи: {47EB2A}40 очк.{FFFFFF}
Уровень семьи: {47EB2A}18 [13/180]{FFFFFF}
Членов в семье: {47EB2A}3 человек{FFFFFF} из {47EB2A}510 человек
Идёт в казну с депозитов членов семьи: {47EB2A}5%{FFFFFF}
Местоположение спавна: {47EB2A}Нет{FFFFFF}
Денег в бюджете семьи: {47EB2A}$10270{FFFFFF}
Семейных монет на складе: {47EB2A}0 шт.{FFFFFF}
Discord: {47EB2A}[ Нет ]{FFFFFF}

Лидер семьи: {47EB2A}Daniil_Snezhkov{FFFFFF}
Заместитель: {47EB2A}Tommy_Mur{FFFFFF}
Заместитель 2: {47EB2A}{FFFFFF}[{FF8859}Нет{FFFFFF}]{FFFFFF}
Заместитель 3: {47EB2A}{FFFFFF}[{FF8859}Нет{FFFFFF}]{FFFFFF}

Слоган: {47EB2A}фармилы не ходите в казино{FFFFFF}
Содержание улучшений: {47EB2A}0 репутации в сутки{FFFFFF}
Содержание квартиры: {47EB2A}0 репутации в PayDay{FFFFFF}
Содержание участников: {47EB2A}0 репутации в PayDay{FFFFFF}
Содержание фургонов: {47EB2A}3 репутации в PayDay за каждый фургон


{ffffff}Семейный флаг: {ffffff}Нет

{FFFFFF}Семейная частная фракция: {47EB2A}Нет{FFFFFF}
{FFFFFF}Обьявление: 

{D4D4D4}Лучший промокод #majorik
{D4D4D4}Семья создана 9.11.23
{D4D4D4}Всем удачи, любим
{D4D4D4} 
{D4D4D4}И главное не играйте в казино
{D4D4D4}И будут у вас вирты!


 
 
 

{ffffff}Информация об ограничениях за текущий час (для заместителей):
	- Уволено игроков: 0/5
	- Потрачено семейной репутации{CCCCCC}(закупка аптечек/бронежилетов){ffffff}: 0/5000
 
{ff6666}Примечания:{cccccc}
- Семейные улучшения действуют только при наличии семейной квартиры.
- Если квартира будет отобрана по налогам или по недостатку репутации, то улучшения будут очищены. Продажа между семьями сохраняет улучшения.
- Флаг семьи будет очищен, если семейная квартира будет продана любым способом.
- Семейная частная фракция остается при утере семейной квартиры.
- Семейный автопарк не очищается при утере квартиры и будет доступен при повторном приобретении семейной недвижимости.
[09:54:44.706426] (script)	packet_hooker (2).lua: [RakLuaEvents.INCOMING_RPC(252)] zoneId -> 7717 & eventTextLen -> 0 & eventText ->  & zoneColor -> 0x0 & zoneType -> 2 & zoneAttachID -> 542 & sasal52 ->
[09:54:44.706426] (script)	packet_hooker (2).lua: 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
[09:54:44.890083] (script)	packet_hooker (2).lua: 27086, 2, {BFBBBA}Информация, Выбрать, Закрыть, {C0C0C0}[1] {FFFFFF}Посмотреть общую информацию
{C0C0C0}[2] {FFFFFF}Бонусы и улучшения семьи
{C0C0C0}[3] {FFFFFF}Информация об альянсе {FA8072}[ Нет ]
{C0C0C0}[4] {FFFFFF}Семейные территории и предприятия {FA8072}[ Нет ]


oldred -> [Ошибка] {FFFFFF}Лидер не может покинуть семью!
red -> [Ошибка] {FFFFFF}У вас уже есть галочка!
red -> [Ошибка] {FFFFFF}У вас уже есть бренд!
red -> [Ошибка] {FFFFFF}У вашей семьи нет улучшения: 'Третий заместитель'
oldred -> [Ошибка] {FFFFFF}Чтобы установить этот тип семьи, уровень семьи должен быть выше 20-го!

{FFFFFF}[Семья (Новости)] Daniil_Snezhkov[581]:{B9C1B8} Изменил цвет чата/статуса семьи!

2922, 1, {BFBBBA}, Принять, Назад, {FFFFFF}

- Цвет семьи, функция которая даст вам возможность сделать небольшое отличие от других семей!
Цвет семьи используется:

{F58558}- В рации семьи.
- В статистике семьи.
- В названии семьи, над головой персонажа.
- Система будет дополнятся в процессе обновлений.{FFFFFF}

Введите в окошко цифру, цвет которой вам нравится больше всего:
{FF5E5E}0, {FFFFFF}1, {E65075}2, {EFA4B7}3, {905B69}4, {D052CE}5, {FF00FC}6, {5D395D}7, {8E38EA}8, {6B21BB}9,{2F00FF}10, {7456F8}11, {5287F1}12, {1DBAF2}13, {308EB0}14, {30B061}15, {20F271}16, {107135}17, {47EB2A}18, {9EE991}19, {C2D95E}20, {D1FF00}21, {7B9022}22, {FFC900}23, {E8CA60}24, {6B5B1F}25, {FF8400}26, {C04312}27, {5C4C45}28, {373534}29, {351204}30.


valik - [Информация] {ffffff}Вы установили новое название для ранга №1 (было: '/mm - 11 пункт - #ma', стало: '123')

*/

stock GetFamilyApartamentUID(apartament_id)
{
    if(1 <= apartament_id <= 28)
        return 0;

    else if(29 <= apartament_id <= 61)
        return 2;

    else if(62 <= apartament_id <= 79)
        return 1;

    return INVALID_DATA_ID;
}

stock UpdateFamilyApartament(apartament_id, bool:create = false)
{
    static apartament_uid; apartament_uid = GetFamilyApartamentUID(apartament_id);

    if(apartament_uid == INVALID_DATA_ID)
        return false;

    if(IsValidDynamicPickup(FamilyApartamentData[apartament_id][FamilyApartamentPickup]) && create)
        DestroyDynamicPickup(FamilyApartamentData[apartament_id][FamilyApartamentPickup]);

    if(IsValidDynamic3DTextLabel(FamilyApartamentData[apartament_id][FamilyApartament3DText]))
        DestroyDynamic3DTextLabel(FamilyApartamentData[apartament_id][FamilyApartament3DText]);
    
    if(create)
    {
        FamilyApartamentData[apartament_id][FamilyApartamentPickup] = CreateDynamicPickup(19132, 1, FamilyApartamentData[apartament_id][FamilyApartamentPosition][0], FamilyApartamentData[apartament_id][FamilyApartamentPosition][1], FamilyApartamentData[apartament_id][FamilyApartamentPosition][2], 23, 206 + apartament_uid);
        createDynamicArea(43, 9, apartament_id, 1024, CreateDynamicSphere(FamilyApartamentData[apartament_id][FamilyApartamentPosition][0], FamilyApartamentData[apartament_id][FamilyApartamentPosition][1], FamilyApartamentData[apartament_id][FamilyApartamentPosition][2], 2.0, 23, 206 + apartament_uid));
    }

    f(global_str, sizeof(global_str), "Семейная квартира №%d\n%s: {%06x}%s{FFFFFF}\nСтатус: {%06x}[%s]{FFFFFF}\n", apartament_id, FamilyApartamentData[apartament_id][FamilyApartamentFamilyID] ? "Владелец" : "Стоимость", FamilyApartamentData[apartament_id][FamilyApartamentFamilyID] ? 0x57A552 : 0x87EB7F, !FamilyApartamentData[apartament_id][FamilyApartamentFamilyID] ? ("10000 репутации") : (str_f("%s", FamilyData[FamilyApartamentData[apartament_id][FamilyApartamentFamilyID]][FamilyName])), FamilyApartamentData[apartament_id][FamilyApartamentLocked] ? 0xF56183 : 0x87EB7F, FamilyApartamentData[apartament_id][FamilyApartamentLocked] ? "Закрыта" : "Открыта");
    FamilyApartamentData[apartament_id][FamilyApartament3DText] = CreateDynamic3DTextLabel(global_str, 0xFFFFFFFFFFFFFFFF, FamilyApartamentData[apartament_id][FamilyApartamentPosition][0], FamilyApartamentData[apartament_id][FamilyApartamentPosition][1], FamilyApartamentData[apartament_id][FamilyApartamentPosition][2], 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 23, 206 + apartament_uid);

    return true;
}