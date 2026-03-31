#define MAX_ITEMS_FAMILY_SHOP   5

enum FamilyShopInfo 
{
    itemTitle[64],
    itemID,
    itemColorID,
    itemPrice
}

new FamilyShopData[MAX_ITEMS_FAMILY_SHOP][FamilyShopInfo] = {
    {"Антирадар", 8123, 255, 5000},
    {"Молот Лас Вегас", 7735, 255, 4000},
    {"Энергетический скейтборд", 7733, 255, 3000},
    {"Нимб стрит-флеш", 7741, 255, 6000},
    {"Слот машина", 7738, 255, 5000}
};

stock showMakeFamilyMenu(playerid)
{
    SendPlayerEvent(playerid, {0}, "window.executeEvent('event.setActiveView', `[\"Family\"]`);");
    SendPlayerEvent(playerid, {0}, "window.executeEvent('event.familyMenu.initializeCreateData', `[{ \"money\": 500001000, \"price\": 20000000 }]`);");

    return SendPlayerBrowserFocus(playerid, 0, true);
}

stock showFamilyMenu(playerid)
{
    new id = FP_Data[playerid][F_FAMILY_ID], count;
    
	f(mysql_string, 128, "SELECT * FROM family WHERE ID = %d", id);
	new Cache:result = mysql_query(mysql, mysql_string);
	
	static FamLeader[24], FamName[32], slogan[40], FamDiscord[64], FamZam[3][24], FamColor, FamType, FamRep, FamSpawnType, FamSpawnData,
 	FamLevel, FamExp, FamJackDaw, FamBrend, FamPercentDeposit, FamKV;

    cache_get_value_name(0, "name", FamName);
    cache_get_value_name(0, "slogan", slogan);
	cache_get_value_name(0, "ownername", FamLeader);
	cache_get_value_name(0, "discord", FamDiscord);
	cache_get_value_name(0, "zam_1", FamZam[0]);
	cache_get_value_name(0, "zam_2", FamZam[1]);
	cache_get_value_name(0, "zam_3", FamZam[2]);
	cache_get_value_name(0, "rank", SQL_STRING), sscanf(SQL_STRING, "p<,>a<s[128]>[10]", SQL_GET_ROW_STR);
	
    cache_get_value_name_int(0, "color", FamColor);
    cache_get_value_name_int(0, "type", FamType);
	cache_get_value_name_int(0, "reputation", FamRep);
	cache_get_value_name_int(0, "level", FamLevel);
	cache_get_value_name_int(0, "exp", FamExp);
	cache_get_value_name_int(0, "jackdaw", FamJackDaw);
	cache_get_value_name_int(0, "brend", FamBrend);
	cache_get_value_name_int(0, "percent_deposit", FamPercentDeposit);
	cache_get_value_name_int(0, "kv_id", FamKV);
	cache_get_value_name_int(0, "spawn_data", FamSpawnData);
	cache_get_value_name_int(0, "spawn_type", FamSpawnType);

    cache_delete(result);
		
    foreach(Player, i)
    {
        if(FP_Data[i][F_FAMILY_ID] == FP_Data[playerid][F_FAMILY_ID])
            format(mysql_string, 128, "(%d) %s[%d]\t%d\t%d\t0/3\n", count, PN(i), i, PI[i][pLevel], PlayerAFKTime[i]),
            strcat(global_str, mysql_string),
            count++;
    }

    SendPlayerEvent(playerid, {0}, !"window.executeEvent('event.setActiveView', `[\"Family\"]`);");
    
    SendPlayerEvent(playerid, {0}, !"window.executeEvent('event.familyMenu.initializeNavigation', `[[0,1,3,4]]`);");
    SendPlayerEventF(playerid, {0}, "window.executeEvent('event.familyMenu.initializeMainInfo', \
        `[\
            {\
                \"id\": %d, \
                \"management\": 1, \
                \"title\": \"%s\", \
                \"type\": \"%s\", \
                \"desc\": \"%s\", \
                \"message\": \"Нет объявлений\", \
                \"bg\": -1, \
                \"icon\": 0, \
                \"reputation\": %i, \
                \"evil\": 0, \
                \"money\": 0, \
                \"coins\": 0, \
                \"deposit\": %d, \
                \"payDay\": 0, \
                \"flag\": \"Нет\", \
                \"fraction\": \"Отсутствует\", \
                \"aliance\": \"Отсутствует\", \
                \"apart\": \"%s\", \
                \"verification\": %d, \
                \"brand\": %d, \
                \"discord\": \"%s\", \
                \"level\": %i, \
                \"currentExp\": %i, \
                \"online\": %d, \
                \"totalExp\": %i, \
                \"hasEstate\": 0,\
                \"leaders\": [\
                    {\
                        \"name\": \"%s\",\
                        \"online\": 1, \
                        \"role\": \"Лидер\" \
                    }\
                ]\
            }\
        ]`\
    );", id, FamName, FamilyType_EN[FamType], slogan, FamRep, FamPercentDeposit, !(FamSpawnData == -1) ? ( !FamSpawnType ? "Семейная квартира":(str_f("Дом №%d", FamSpawnData)) ):"Нет", \
    FamJackDaw, FamBrend,  isnull(FamDiscord) ? "" : FamDiscord, FamLevel, FamExp, count, FamLevel*10, FamLeader);
    
    SendPlayerEvent(playerid, {0}, !"window.executeEvent('event.familyMenu.initializeManagement', \
        `[\
            {\
                \"verificationPrice\": 50000000, \
                \"brandPrice\": 80000000, \
                \"hasAliance\": 0\
            }\
        ]`\
    );");

    return SendPlayerBrowserFocus(playerid, 0, true);
}

stock showDialogFamilyMenu(playerid, caseid)
{
    switch(caseid)
    {
        case 1:
        {
            SPD(playerid, 0, DIALOG_STYLE_MSGBOX, !"{cccccc}Пополнение зловещей репутации", !"\
            {FAAC58}-{ffffff} Для пополнения зловещей репутации в семье вам необходимо принимать участие\n\
            в мероприятии {FAAC58}'Зловещий дворец'{FFFFFF}. Данное мероприятие проводится каждый день\n\
            с {FAAC58}20:00{FFFFFF} до {FAAC58}20:15{FFFFFF} по серверному времени {FAAC58}(/GPS - Мероприятия - Зловещий дворец){FFFFFF}.\n\n\
            Принимать участие в мероприятии могут все игроки, которые состоят в семьях\n\
            и имеют {FAAC58}15+ игровой уровень{FFFFFF}.\n\n\
            В рамках мероприятия вам необходимо будет убивать страшных зомби и относить\n\
            их трофеи, ко входу во дворец. При смерти зомби вы гарантированно будете\n\
            получать {FAAC58}зловещую репутацию{FFFFFF}, а также с определенным шансом из него сможет\n\
            выпасть {FAAC58}зловещая монета{FFFFFF}. Данную монету вы сможете обменять на зловещую репутацию\n\
            или другие ценные предметы в специальном {FAAC58}магазине у Хагрида младшего{FFFFFF},\n\
            который находится возле входа на мероприятие.", !"Далее", !"Отмена");
        }
        case 2:
        {
            if(GetFamilyDataInt(FP_Data[playerid][F_FAMILY_ID], "kv_id") == -1)
                return SCM(playerid, COLOR_RED, !"[Ошибка] {ffffff}У вашей семьи нету семейной квартиры");
            
            SPD(playerid, 4777, DIALOG_STYLE_INPUT, !"{cccccc}Пополнение денег на складе семьи", !"\
            {FAAC58}|{ffffff} Введите количество {FAAC58}денег{FFFFFF}, которые хотите положить на склад семьи\n\n\
            Об вашем пополнении узнает вся семья\n\
            Деньги семьи можно будет потратить на различные {FAAC58}улучшения{FFFFFF}!", !"Далее", !"Отмена");
        }
        case 3:
        {
            SPD(playerid, 0, DIALOG_STYLE_TABLIST_HEADERS, !"{cccccc}Содержание в PayDay", "\
            {cccccc}Пункт\t{cccccc}Значение\n\
            {FAAC58}|{ffffff} Содержание улучшений	{cccccc}0 репутации в сутки\n\
            {FAAC58}|{ffffff} Содержание квартиры	{cccccc}0 репутации в PayDay\n\
            {FAAC58}|{ffffff} Содержание участников	{cccccc}0 репутации в PayDay\n\
            {FAAC58}|{ffffff} Содержание фургонов	{cccccc}0 репутации в PayDay за каждый фургон\n\
            {FAAC58}|{ffffff} Сумма	{cccccc}0 репутации", !"Закрыть", !"");
        }
        case 4:
        {
            SPD(playerid, 0, DIALOG_STYLE_MSGBOX, !"", !"\
            {FF6347}- Дополнительный респект\n\
            {FF6347}- Успех в работе\n\
            {FF6347}- Бизнесмены в долгy\n\
            {FF6347}- Неузнаваемый\n\
            {FF6347}- Медики в долгу\n\
            {FF6347}- Белый список\n\
            {FF6347}- Банковские махинации\n\
            {FF6347}- Мародёры\n\
            {FF6347}- Рыбный цех\n\
            {FF6347}- Третий заместитель\n\
            {FF6347}- Быстрые налоги\n\
            {FF6347}- Вместительные фургоны\n\n\n\
            {cccccc}ВАЖНО! Улучшения семьи неактивны, так как у Вас отсутствует семейная квартира или поместье!\n\
            {FAAC58}|{cccccc} - Фермер\n\
            {FAAC58}|{cccccc} - Грузчик\n\
            {FAAC58}|{cccccc} - Работник завода\n\
            {FAAC58}|{cccccc} - Развозчик пиццы\n\
            {FAAC58}|{cccccc} - Водитель автобуса\n\
            {FAAC58}|{cccccc} - Дальнобойщик\n\
            {FAAC58}|{cccccc} - Инкассатор\n\
            {FAAC58}|{cccccc} - Металлоломщик\n\
            {FAAC58}|{cccccc} - Мусорщик\n\
            {FAAC58}|{cccccc} - Налоговик\n\
            {FAAC58}|{cccccc} - Пилот\n\
            {FAAC58}|{cccccc} - Водитель поезда\n\
            {FAAC58}|{cccccc} - Водитель трамвая", !"Закрыть", !"");
        }
        case 5:
        {
            SPD(playerid, 0, DIALOG_STYLE_MSGBOX, !"{BFBBBA}Доступные привилегии и бонусы", !"\
            {FFFFFF}Привилегии и бонусы за галочку {FA8072}[ действуют ]{FFFFFF}:\n\
            {82CB43}   - Специальный знак, подтверждающий запатентованность семьи.\n\
            {82CB43}   - Возможность влияния на расформ. семьи, которая копировала название вашей.\n\
            {82CB43}   - Возможность терять в 2-а раза меньше репутации при наказании членов семьи.\n\
            {82CB43}   - Возможность взаимодействия с депозитом в кассах в любое время суток.\n\
            {FFFFFF}Привилегии и бонусы за бренд {FA8072}[ действуют ]{FFFFFF}:\n\
            {82CB43}   - Специальный знак, выделяющий вас от других семей.\n\
            {82CB43}   - Доступно 'Война за Территории' в Las Venturas (при наличии семейной квартиры и флага).\n\
            {82CB43}   - Возможность владеть одним домом больше!\n\n\
            {FFFFFF}Привилегии и бонусы за семейную квартиру {FA8072}[ Не действуют ]{FFFFFF}:\n\
            {82CB43}   - Доступно 'Война за Территории' в Las Venturas.\n\
            {82CB43}   - Заработок в размере {73B461}$180000 средств, и 8 семейных монет{82CB43} за каждую захваченную территорию.\n\
            {82CB43}   - Покупка до 6-и фургонов семьи за семейную репутацию.\n\n\
            {FFFFFF}Привилегии и бонусы за частную фракцию {FA8072}[ Не действуют ]{FFFFFF}:\n\
            {82CB43}   - Можно устроится во фракцию на специальном пикапе на 9 ранг, если Вы не состоите в другой фракции.\n\
            {82CB43}   - Возможность уволиться самостоятельно из частной фракции семьи.\n\
            {82CB43}   - Основной доход частной фракции поступает с оплаты услуг (лечение, покупка страховки, публикация объявлений).\n\n\
            {FFFFFF}Привилегии и бонусы за семейный флаг {FA8072}[ Не действуют ]{FFFFFF}:\n\
            {ff6666}   1) {ffffff}+12 процентов к заработку на водных нефтевышках;\n\
            {ff6666}   2) {ffffff}+15 процентов к заработку на кастомных фурах на работе дальнобойщика;\n\
            {ff6666}   3) {ffffff}+8 процентов к заработку на работе пилота;\n\
            {ff6666}   4) {ffffff}+7 процентов к зарплате в организации;\n\
            {ff6666}   5) {ffffff}+1 процент к улучшению PREMIUM VIP;\n\
            {ff6666}   6) {ffffff}+2 процента к шансу получения ларца водителя автобуса;\n\
            {ff6666}   7) {ffffff}+2 процента к шансу получения ларца инкассатора;\n\
            {ff6666}   8) {ffffff}+2 процента к шансу получения ларца пилота;\n\
            {ff6666}   9) {ffffff}+2 процента к шансу получения ларца дальнобойщика.\n\
            {ff6666}   10) {ffffff}Возможность иметь семейные предприятия.\n\
            {ff6666}   11) {ffffff}Возможность покупать и продавать семейные территории {C0C0C0}(/sellfamter).\n\n\
            {FFFFFF}Топ семьи {FA8072}[ Семья не в топе ]{FFFFFF}:\n\
            {FFA500}   [!] {FFFFFF}Как повысить уровень семьи:\n\
            {82CB43}      - Каждый участник семьи будет приносить по 1 ехр каждый payday.\n\
            {82CB43}      - При повышении уровня участника семьи, семьи будут прибавляться очки опыта.\n\
            {FFA500}   [!] {FFFFFF}Как повысить репутацию( влиятельность ) семьи:\n\
            {82CB43}      - Если в семье состоит 9 ранг или лидер, то каждый payday в семью будет прибавляться влиятельность.\n\
            {82CB43}      - Если участник семьи выиграл капт или стрелу за бизнес, то прибавится 2 очка репутации.\n\
            {82CB43}      - Если участник семьи пожертвовал деньги в центр благотворительности, то прибавится 1-2 очка репутации.\n\
            {FFA500}   [!] {FFFFFF}Как семья может потерять очки репутации:\n\
            {82CB43}      - Если члена семьи забанят/дадут варн.\n\
            {82CB43}      - Если член семьи проиграет капт или стрелу.\n\
            {82CB43}      - И еще много факторов.\n\
            {C0C0C0}Если в вашей семьи есть квартира, то за неё с вас будут брать 8 очков репутации каждый payday.\n\
            В случае если у вас будет меньше 8-ти очков репутации, квартира будет продана.", !"Закрыть", !"");
        }
        case 6:
        {
            SPD(playerid, 0, DIALOG_STYLE_MSGBOX, !"{cccccc}Помощь и примечания", !"\
            {FFFFFF}Список доступных семейных команд:\n\
            {FAAC58}1. {CCCCCC}/fammenu{FFFFFF} - Панель семьи;\n\
            {FAAC58}2. {CCCCCC}/fam{FFFFFF} - Чат семьи(рация);\n\
            {FAAC58}3. {CCCCCC}/famoffkick{FFFFFF} - Выгнать из семьи(оффлайн);\n\
            {FAAC58}4. {CCCCCC}/fammute{FFFFFF} - Выдать бан семейного чата;\n\
            {FAAC58}5. {CCCCCC}/famunmute{FFFFFF} - Снять бан семейного чата;\n\
            {FAAC58}6. {CCCCCC}/faminvite{FFFFFF} - Быстрый инвайт в семью;\n\
            {FAAC58}7. {CCCCCC}/famuninvite{FFFFFF} - Быстрое увольнение;\n\
            {FAAC58}8. {CCCCCC}/fmembers{FFFFFF} - Члены семьи онлайн;\n\
            {FAAC58}9. {CCCCCC}/setfrank{FFFFFF} - Изменить ранг члену семьи;\n\
            {FAAC58}10. {CCCCCC}/al{FFFFFF} - Чат альянса;\n\
            {FAAC58}11. {CCCCCC}/famdisband{FFFFFF} - Расформировать семью (для лидера);\n\
            {FAAC58}12. {CCCCCC}/fpremium{FFFFFF} - Выдача одноразовых премий;\n\
            {FAAC58}13. {CCCCCC}/famspawn{FFFFFF} - Спавн незанятого семейного т/с;\n\
            {FAAC58}14. {CCCCCC}/fcarrank{FFFFFF} - Изменить ранг доступа к семейному авто;\n\
            {FAAC58}15. {CCCCCC}/famtag{FFFFFF} - Изменить тэг игрока в чате;\n\
            {FAAC58}16. {CCCCCC}/unfamtag{FFFFFF} - Убрать тэг игрока в чате;\n\
            {FAAC58}17. {CCCCCC}/famwarn{FFFFFF} - Выдать выговор игроку в семье;\n\
            {FAAC58}18. {CCCCCC}/unfamwarn{FFFFFF} - Снять выговор игроку в семье;\n\
            {FAAC58}19. {CCCCCC}/famblacklist{FFFFFF} - Добавить игрока в ЧС;\n\
            {FAAC58}20. {CCCCCC}/famunblacklist{FFFFFF} - Удалить игрока из ЧС;\n\
            {FAAC58}21. {CCCCCC}/famunblacklistoff{FFFFFF} - Удалить игрока из ЧС в оффлайне;\n\
            {FAAC58}22. {CCCCCC}/sellfamflag{FFFFFF} - Продать семейный флаг другой семье;\n\
            {FAAC58}23. {CCCCCC}/sellfamter{FFFFFF} - Продать территорию другой семье.\n\n\
            {FAAC58}Примечания:{FFFFFF}\n\
            - Семейные улучшения действуют только при наличии семейной квартиры;\n\
            - Следите за семейной репутацией и налогами - слёт квартиры очистит семейный флаг и семейные улучшения!\n\
            - Семейные улучшения и флаг сохраняются при: продаже квартиры государству, другой семье или при переводе в поместье.\n\
            - Частная фракция остается при потери семейной квартиры/поместья;\n\
            - Семейный автопарк не очищается при потери квартиры/поместья и будет доступен при повторном приобритении семейной недвижимости.", !"Закрыть", !"");
        }
    }
    return true;
}

stock showFamilyShop(playerid)
{
    CefInterfaceActionHide(playerid, 1);

    SendPlayerEvent(playerid, {0}, "window.executeEvent('event.setActiveView', `[\"MountainTestDrive\"]`);");
    SendPlayerEvent(playerid, {0}, "window.executeEvent('event.mountain.testDrive.initializeText', `[{\"title\":\"Магазин\",\"desc\":\"Список доступных предметов\"}]`);");

    global_str = "";

    for(new i, string[256]; i < sizeof(FamilyShopData); i++)
    {
        format(string, sizeof(string), "\
            {\
                \"id\":%d,\
                \"title\":\"%s\",\
                \"img\":\"%i\",\
                \"color\":%i,\
                \"price\":%i\
            }%s\
        ", i, FamilyShopData[i][itemTitle], FamilyShopData[i][itemID], FamilyShopData[i][itemColorID], FamilyShopData[i][itemPrice], i == (sizeof(FamilyShopData) -1 ) ? "" : "," );

        strcat(global_str, string);

        string = "";
    }
    SendPlayerEventF(playerid, {0}, "window.executeEvent('event.mountain.testDrive.addVehicles', `[[%s]]`);", global_str);

    return SendPlayerBrowserFocus(playerid, 0, true);
}