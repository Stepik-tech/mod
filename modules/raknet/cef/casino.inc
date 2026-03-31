// Include create (05.07.2025)
// Roman Markov (t.me/kavemark && vk.com/rmmarkov)
// CEF Dice Game in Casino

enum diceGame
{
    bool:PlayerInGame,
    Float:dicePoint[3],

    diceHoster,
    diceBet,
    diceWin,
    diceSession,
    diceMove,

    Text3D:diceLabel,
	bool:diceStart
}
new const DiceTabelGame[][diceGame] =
{
    {true, {1912.3638, 1014.2815, 8.6484}, INVALID_PLAYER_ID},
    {true, {1984.3365, 1013.1868, 10.9999}, INVALID_PLAYER_ID}
};

enum playerDiceGame
{
    playerDiceTable,
    playerDiceID,
    playerDiceCube[2],
    playerDiceUnix[3],

    bool:playerDiceStatus
};
new PlayerDice[MAX_PLAYERS][playerDiceGame],
    IteratorArray:DiceTablePlayers[sizeof(DiceTabelGame)]<MAX_PLAYERS>;

public OnPlayerDisconnect(playerid, reason)
{
    if(PlayerDice[playerid][playerDiceTable] != INVALID_DATA_ID)
    {
        new id_table = PlayerDice[playerid][playerDiceTable];
        if(PlayerDice[playerid][playerDiceStatus] == true)
        {
            if(DiceTabelGame[id_table][diceMove] == playerid)
            {
                for(new id; id < 3; id ++)
                    KillTimer(PlayerDice[playerid][playerDiceUnix][id]);

                DiceTabelGame[id_table][diceMove] = INVALID_PLAYER_ID;
                SendNextDicePlayer(id_table, playerid);
            }
        }
        if(DiceTabelGame[id_table][diceHoster] == playerid)
        {
            new new_hoster_id = Iter_Last(DiceTablePlayers[id_table]);

            DiceTabelGame[id_table][diceHoster] = new_hoster_id;
            SendDiceEvent(id_table, (str_f("window.executeEvent('event.Dice.updatePlayer', `[{\"id\": %d, \"score\": %d}]`);", PlayerDice[new_hoster_id][playerDiceID])));
        }
        ClearPlayerDice(playerid, true);
    }

    #if defined Dice_OnPlayerDisconnect
        return Dice_OnPlayerDisconnect(playerid, reason);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect Dice_OnPlayerDisconnect
#if defined Dice_OnPlayerDisconnect
    forward Dice_OnPlayerDisconnect(playerid, reason);
#endif

public OnPlayerConnect(playerid)
{
    PlayerDice[playerid][playerDiceTable] = 
    PlayerDice[playerid][playerDiceID] = INVALID_DATA_ID;

    for(new id; id < 2; id++)
        PlayerDice[playerid][playerDiceCube][id] = 0;

    PlayerDice[playerid][playerDiceStatus] = false;

    #if defined Dice_OnPlayerConnect
        return Dice_OnPlayerConnect(playerid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect Dice_OnPlayerConnect
#if defined Dice_OnPlayerConnect
    forward Dice_OnPlayerConnect(playerid);
#endif

stock IsPlayerInDiceArea(playerid, bool:interface)
{
    for(new id; id < sizeof(DiceTabelGame); id++)
    {
        if(interface && DiceTabelGame[id][PlayerInGame] == false)
            continue;

        if(IsPlayerInRangeOfPoint(playerid, 2.5, DiceTabelGame[id][dicePoint][0], DiceTabelGame[id][dicePoint][1], DiceTabelGame[id][dicePoint][2]))
            return id;
    }
    return INVALID_DATA_ID;
}
stock OnPlayerRequestDiceInterface(playerid, id_table, bool:send_active_view = true)
{
    if(id_table == INVALID_DATA_ID)
        return SendErrorMessage(playerid);

    if(PlayerDice[playerid][playerDiceTable] != INVALID_DATA_ID)
        return false;

    if(send_active_view == false) 
        executeEvent(playerid, 0, "window.executeEvent('event.setActiveView', `[\"null\"]`);");    

    PlayerDice[playerid][playerDiceTable] = id_table;
    PlayerDice[playerid][playerDiceID] = Iter_Count(DiceTablePlayers[id_table]);

    Iter_Add(DiceTablePlayers[id_table], playerid);
    hidePlayerHud(playerid);
	TogglePlayerControllable(playerid, false);
    executeEvent(playerid, 0, "window.executeEvent('event.setActiveView', '[\"Dice\"]');");

    foreach(DiceTablePlayers[id_table], i)
    {
        if(PlayerDice[i][playerDiceTable] != id_table)
            continue;

        executeEvent(i, 0, (str_f("window.executeEvent('event.Dice.addPlayer', `\
            [{\"id\":%d,\"name\":\"%s\",\"status\":\"%d\",\"score\":0,\"isCurrent\":%d}]`);",\
            PlayerDice[playerid][playerDiceID], PN(playerid), DiceTabelGame[id_table][diceHoster] == INVALID_PLAYER_ID ? 2 : 1, playerid == i ? 1 : 0)));

        if(playerid != i)
        {
            executeEvent(playerid, 0, (str_f("window.executeEvent('event.Dice.addPlayer', `\
            [{\"id\":%d,\"name\":\"%s\",\"status\":\"%d\",\"score\":0,\"isCurrent\":0}]`);",\
                PlayerDice[i][playerDiceID], PN(i), DiceTabelGame[id_table][diceHoster] == i ? 2 : 1)));
        }

        if(playerid == i && DiceTabelGame[id_table][diceHoster] == INVALID_PLAYER_ID)
        {
            DiceTabelGame[id_table][diceHoster] = playerid;
            UpdateTableSession(id_table, 1);
        }

        if(DiceTabelGame[id_table][diceStart] == false)
        {
            if(DiceTabelGame[id_table][diceHoster] == playerid)
                executeEvent(i, 0, (str_f("window.executeEvent('event.Dice.addMessage', `[{\"name\":\"%s\",\"description\":\"присоединился к игре в качестве Хоста\"}]`);", PN(playerid))));                
        }
        else executeEvent(i, 0, (str_f("window.executeEvent('event.Dice.addMessage', `[{\"name\":\"%s\",\"description\":\"присоединился к игре в качестве Гостя\"}]`);", PN(playerid))));
    }

    if(DiceTabelGame[id_table][diceHoster] != playerid && DiceTabelGame[id_table][diceSession] == 2)
        executeEvent(playerid, 0, (str_f("window.executeEvent('event.Dice.updateSession', `[{\"status\":\"Ожидание игроков\", \"seconds\":null, \"buttonText\":\"Вступить в игру\", \"readyBets\":[], \"bet\":%d, \"sumBet\":%d, \"cubes\":null}]`);", DiceTabelGame[id_table][diceBet], DiceTabelGame[id_table][diceWin])));

    return cursorPlayer(playerid, 0, true);
}
stock EnterDiceGame(playerid, id_table)
{
    if(id_table == INVALID_DATA_ID)
        return false;

    if(PlayerDice[playerid][playerDiceStatus])
        return sendPlayerNotification(playerid, 2, "Кости", "Вы уже поставили ставку!", 3);
   
    if(GetCount(playerid, 530) < DiceTabelGame[id_table][diceBet])
        return sendPlayerNotification(playerid, 2, "Кости", "У вас недостаточно фишек!", 3);

    if(IsValidDynamic3DTextLabel(DiceTabelGame[id_table][diceLabel]))
        UpdateDynamic3DTextLabelText(DiceTabelGame[id_table][diceLabel], 0xF5BB1BFF, (str_f("/dice - для игры 1 на 1 с другими игроками\n\n[ Стол для игры в кости №%d ]\n\n{ffffff}Статус: {F5BB1B}Ожидание игроков\n{ffffff}Ставка: {F5BB1B}%d", id_table + 1, DiceTabelGame[id_table][diceBet])));    

    DiceTabelGame[id_table][diceWin] += DiceTabelGame[id_table][diceBet];
    PlayerDice[playerid][playerDiceStatus] = true;

    switch(DiceTabelGame[id_table][diceSession])
    {
        case 2:
        {
            executeEvent(playerid, 0, (str_f("window.executeEvent('event.Dice.updateSession', `[{\"status\":\"Ожидание игроков\", \"seconds\":null, \"buttonText\":\"Вступить в игру\", \"readyBets\":[], \"bet\":%d, \"sumBet\":null, \"cubes\":null}]`);", DiceTabelGame[id_table][diceBet])));
            SendDiceEvent(id_table, (str_f("window.executeEvent('event.Dice.updateSession', `[{\"sumBet\":%d}]`);", DiceTabelGame[id_table][diceWin])));
            SendDiceEvent(id_table, (str_f("window.executeEvent('event.Dice.updatePlayer', `[{\"id\":%d, \"status\":3}]`);", PlayerDice[playerid][playerDiceID])));
        }
    }
    return true;
}
stock StartDiceGame(playerid, id_table)
{
    if(PlayerDice[playerid][playerDiceStatus] != true)
        return SendNextDicePlayer(id_table, playerid);

    if(GetCount(playerid, 530) < DiceTabelGame[id_table][diceBet])
    {
        PlayerDice[playerid][playerDiceStatus] = false;
        SendDiceEvent(id_table, (str_f("window.executeEvent('event.Dice.addMessage', `[{\"name\":\"%s\", \"description\":\"исключен из-за нехватки фишек\"}]`);", PN(playerid))));
        SendDiceEvent(id_table, (str_f("window.executeEvent('event.Dice.deletePlayer', `[%d]`);", playerid)));
        sendPlayerNotification(playerid, 2, "Кости", "У вас недостаточно фишек", 3);
        return SendNextDicePlayer(id_table, playerid);
    }

    DiceTabelGame[id_table][diceMove] = playerid;
    DeleteItem(playerid, 530, DiceTabelGame[id_table][diceBet]);

    foreach(DiceTablePlayers[id_table], i)
    {
        if(i == playerid) executeEvent(playerid, 0, (str_f("window.executeEvent('event.Dice.updateSession', `[{\"status\":\"Ход игрока: %s\", \"seconds\":10, \"buttonText\":\"Бросить кубики\", \"cubes\":null}]`);", PN(playerid))));
        else executeEvent(i, 0, (str_f("window.executeEvent('event.Dice.updateSession', `[{\"status\":\"Ход игрока: %s\", \"seconds\":10, \"buttonText\":\"\", \"cubes\":null}]`);", PN(playerid))));
    }
    PlayerDice[playerid][playerDiceUnix][1] = 10;
    PlayerDice[playerid][playerDiceUnix][0] = CallTimeOutFunction("PlayerDiceTimer", 1000, true, "dd", playerid, id_table);

    return true;
}
public: PlayerDiceTimer(playerid, id_table)
{
    PlayerDice[playerid][playerDiceUnix][1] --;

    if(PlayerDice[playerid][playerDiceUnix][1] <= 0)
    {
        KillTimer(PlayerDice[playerid][playerDiceUnix][0]);
        OnPlayerRequestDiceResults(playerid, id_table);
    }
    else SendDiceEvent(id_table, (str_f("window.executeEvent('event.Dice.updateSession', `[{\"seconds\":%d}]`);", PlayerDice[playerid][playerDiceUnix][1])));

    return true;
}

stock SendNextDicePlayer(id_table, last_player)
{
    new starter_id = Iter_Next(DiceTablePlayers[id_table], last_player);

    if(starter_id == Iter_First(DiceTablePlayers[id_table]) or !IsPlayerConnected(starter_id))
    {
        new max_score = -1, last_score = -1, winner_id = INVALID_PLAYER_ID;
        
        foreach(DiceTablePlayers[id_table], i)
        {
            if(PlayerDice[i][playerDiceStatus] == false)
                continue;

            last_score = PlayerDice[i][playerDiceCube][0] + PlayerDice[i][playerDiceCube][1];

            if(last_score > max_score)
            {
                max_score = last_score;
                winner_id = i;
            }
        }
        UpdateDynamic3DTextLabelText(DiceTabelGame[id_table][diceLabel], 0xF5BB1BFF, (str_f("/dice - для игры 1 на 1 с другими игроками\n\n[ Стол для игры в кости №%d ]\n\n{ffffff}Статус: {F5BB1B}Игра окончена\n{ffffff}Ставка: {F5BB1B}%d", id_table + 1, DiceTabelGame[id_table][diceBet])));
        SendDiceEvent(id_table, (str_f("window.executeEvent('event.Dice.updateSession', `[{\"status\":\"Победил: %s\"}]`);", PN(winner_id))));
        AddItem(winner_id, 530, DiceTabelGame[id_table][diceWin]);
        sendPlayerNotification(winner_id, 1, "Кости", (str_f("Вы выиграли %d фишек", DiceTabelGame[id_table][diceWin])), 3);
        ClearDiceTable(id_table);

        foreach(Player, i)
        {
            if(PlayerDice[i][playerDiceTable] == -1)
                continue;

            ClearPlayerDice(i);
            PlayerDice[i][playerDiceUnix][2] = CallTimeOutFunction("ReEnterInDiceGame", 5000, false, "dd", i, id_table);
        }
    }
    else StartDiceGame(starter_id, id_table);
    return true;
}
public: ReEnterInDiceGame(playerid, id_table)
    return OnPlayerRequestDiceInterface(playerid, id_table, false);

stock ClearPlayerDice(playerid, bool:player_leave = false)
{
    if(playerid > MAX_PLAYERS - 1)
        return false;

    new id_table = PlayerDice[playerid][playerDiceTable];

    if(id_table != INVALID_DATA_ID)
    {
        if(Iter_Contains(DiceTablePlayers[id_table], playerid))
            Iter_Remove(DiceTablePlayers[id_table], playerid);

        if(player_leave)
        {
            SendDiceEvent(id_table, (str_f("window.executeEvent('event.Dice.addMessage', `[{\"name\":\"%s\", \"description\":\"отсоединился от игры\"}]`);", PN(playerid)))), 
            SendDiceEvent(id_table, (str_f("window.executeEvent('event.Dice.deletePlayer', `[%d]`);", playerid))), 
            TogglePlayerControllable(playerid, true);

            if(DiceTabelGame[id_table][diceHoster] == playerid) ClearDiceTable(id_table);
        }
    
        PlayerDice[playerid][playerDiceTable] = 
        PlayerDice[playerid][playerDiceID] = INVALID_DATA_ID;

        for(new id; id < 2; id ++)
            PlayerDice[playerid][playerDiceCube][id] = 0;

        PlayerDice[playerid][playerDiceStatus] = false;

        KillTimer(PlayerDice[playerid][playerDiceUnix][0]);
        KillTimer(PlayerDice[playerid][playerDiceUnix][2]);

        PlayerDice[playerid][playerDiceUnix][1] = 10;
        
    }

    return true;
}
stock GetCountOfReadePlayers(id_table)
{
    new count;

    foreach(DiceTablePlayers[id_table], i)
    {
        if(PlayerDice[i][playerDiceTable] != id_table or PlayerDice[i][playerDiceStatus] == false)
            continue;

        count ++;
    }
    return count;
}

stock ClearDiceTable(id_table)
{
    DiceTabelGame[id_table][diceSession] = 
    DiceTabelGame[id_table][diceBet] = 
    DiceTabelGame[id_table][diceWin] = 0;

    DiceTabelGame[id_table][diceMove] =
    DiceTabelGame[id_table][diceHoster] = INVALID_PLAYER_ID;

    DiceTabelGame[id_table][diceStart] = false;

    if(IsValidDynamic3DTextLabel(DiceTabelGame[id_table][diceLabel]))
        UpdateDynamic3DTextLabelText(DiceTabelGame[id_table][diceLabel], 0xF5BB1BFF, (str_f("/dice - для игры 1 на 1 с другими игроками\n\n[ Стол для игры в кости №%d ]\n\n{ffffff}Статус: {F5BB1B}Выбор ставки\n{ffffff}Ставка: {F5BB1B}Не установлена", id_table + 1)));

    return true;
}
stock OnPlayerRequestDiceResults(playerid, id_table)
{
    if(DiceTabelGame[id_table][diceMove] != playerid)
        return false;

    for(new id; id < 2; id ++)
        PlayerDice[playerid][playerDiceCube][id] = randomF(1, 6);

    if(DiceTabelGame[id_table][diceHoster] == playerid)
        SendDiceEvent(id_table, (str_f("window.executeEvent('event.Dice.updatePlayer', `[{\"id\":%d, \"status\":2}]`);", PlayerDice[DiceTabelGame[id_table][diceHoster]][playerDiceID])));

    else SendDiceEvent(id_table, (str_f("window.executeEvent('event.Dice.updatePlayer', `[{\"id\":%d, \"status\":0}]`);", PlayerDice[playerid][playerDiceID])));

    SendDiceEvent(id_table, (str_f("window.executeEvent('event.Dice.updateSession', `[{\"status\":\"Ход игрока: %s\", \"seconds\":null, \"buttonText\":\"\", \"cubes\":[%d, %d]}]`);", PN(playerid), PlayerDice[playerid][playerDiceCube][0], PlayerDice[playerid][playerDiceCube][1])));
    SendDiceEvent(id_table, (str_f("window.executeEvent('event.Dice.updatePlayer', `[{\"id\":%d, \"score\":%d}]`);", PlayerDice[playerid][playerDiceID], PlayerDice[playerid][playerDiceCube][0] + PlayerDice[playerid][playerDiceCube][1])));   

    DiceTabelGame[id_table][diceMove] = INVALID_PLAYER_ID;

    return CallTimeOutFunction("@SendNextDicePlayer", 1000, false, "dd", id_table, playerid);
}
public: @SendNextDicePlayer(id_table, playerid)
    return SendNextDicePlayer(id_table, playerid);

stock SendDiceEvent(id_table, event[], bool:send_to_hoster = true)
{
    if(id_table == INVALID_DATA_ID)
        return false;

    foreach(DiceTablePlayers[id_table], i)
    {
        if(PlayerDice[i][playerDiceTable] != id_table)
            continue;

        if(send_to_hoster == false && DiceTabelGame[id_table][diceHoster] == i)
            continue;

        executeEvent(i, 0, event);
    }
    return true;
}

stock UpdateTableSession(id_table, session_id)
{
    if(id_table == INVALID_DATA_ID)
        return false;

    new hoster_id = DiceTabelGame[id_table][diceHoster];

    if(hoster_id == INVALID_PLAYER_ID)
        return false;

    DiceTabelGame[id_table][diceSession] = session_id;

    switch(session_id)
    {
        case 1:
        {
            executeEvent(hoster_id, 0, "window.executeEvent('event.Dice.updateSession', `[{\"status\":\"Выбор ставки\", \"seconds\":null, \"buttonText\":\"Сделать ставку\", \"readyBets\":[20000,100000,200000,1000000], \"bet\":null, \"sumBet\":null, \"cubes\":null}]`);");
            EnterDiceGame(hoster_id, id_table);
        }
        case 2: executeEvent(hoster_id, 0, (str_f("window.executeEvent('event.Dice.updateSession', `[{\"status\":\"Ожидание игроков\", \"seconds\":null, \"buttonText\":\"Начать игру\", \"readyBets\":[], \"bet\":%d, \"sumBet\":null, \"cubes\":null}]`);", DiceTabelGame[id_table][diceBet])));
    }
    return true;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(!pTemp[playerid][tAuthorized]) return false;

    if(newkeys == PRESS_ALT && PlayerDice[playerid][playerDiceTable] == -1)
    {
        new id_table = IsPlayerInDiceArea(playerid, true);

        if(id_table != INVALID_DATA_ID)
            return OnPlayerRequestDiceInterface(playerid, id_table);
    }

    #if defined Dice_OnPlayerKeyStateChange
        return Dice_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerKeyStateChange
    #undef OnPlayerKeyStateChange
#else
    #define _ALS_OnPlayerKeyStateChange
#endif

#define OnPlayerKeyStateChange Dice_OnPlayerKeyStateChange
#if defined Dice_OnPlayerKeyStateChange
    forward Dice_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif

public OnGameModeInit()
{
    Iter_Init(DiceTablePlayers);

    for(new id, table_id; id < sizeof(DiceTabelGame); id ++)
    {
        DiceTabelGame[id][diceHoster] = 
        DiceTabelGame[id][diceMove] = INVALID_PLAYER_ID; 

        if(DiceTabelGame[id][PlayerInGame])
        {
            f(global_str, 200, "{F5BB1B}/dice - для игры 1 на 1 с другими игроками\n\n[ Стол для игры в кости №%d]\n\n{ffffff}Статус: {F5BB1B}Выбор ставки\n{ffffff}Ставка: {F5BB1B}Не установлена", table_id + 1);
            DiceTabelGame[id][diceLabel] = CreateDynamic3DTextLabel(global_str, 0xF5BB1BFF, DiceTabelGame[id][dicePoint][0], DiceTabelGame[id][dicePoint][1], DiceTabelGame[id][dicePoint][2], 10.0);
        }
    }

    #if defined Dice_OnGameModeInit
        return Dice_OnGameModeInit();
    #else
        return 1;
    #endif
}
#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif

#define OnGameModeInit Dice_OnGameModeInit
#if defined Dice_OnGameModeInit
    forward Dice_OnGameModeInit();
#endif
