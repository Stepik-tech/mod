#define MIN_FLAG_VALUE 1
#define MAX_FLAG_VALUE 49
#define DEFAULT_FLAG 33

new CurrentServerFlag = DEFAULT_FLAG;

stock SetServerFlag(flag)
{
    if(flag >= MIN_FLAG_VALUE && flag <= MAX_FLAG_VALUE)
    {
        CurrentServerFlag = flag;
        UpdateAllPlayersFlag();
        return 1;
    }
    return 0;
}


stock ResetServerFlag()
{
    CurrentServerFlag = DEFAULT_FLAG;
    UpdateAllPlayersFlag();
    return CurrentServerFlag;
}

stock PreviousFlag()
{
    CurrentServerFlag--;
    if(CurrentServerFlag < MIN_FLAG_VALUE)
        CurrentServerFlag = MAX_FLAG_VALUE;
    
    UpdateAllPlayersFlag();
    return CurrentServerFlag;
}

stock UpdateAllPlayersFlag()
{
    new onlineCount = Iter_Count(Player);
    new serverName[64];
    strcat(serverName, Setting_Server[7], sizeof(serverName));
    
    foreach(new i : Player)
    {
        if(PI[i][pCustomInterface][2] == 5) 
        {
            new eventStr1[128], eventStr2[256];
            
            format(eventStr1, sizeof(eventStr1), "window.executeEvent('event.hudSA.updateSanAndreasHudVisible', '[%s]');", 
                PI[i][pCustomInterface][2] == 5 ? "true" : "false");
            executeEvent(i, 0, eventStr1);
            
            format(eventStr2, sizeof(eventStr2), "window.executeEvent('event.arizonahud.serverInfo', '[{\"id\":1,\"title\":\"%s\",\"project\":\"Arizona\",\"type\":\"Role play\",\"onLine\":%d,\"flag\":%d,\"logo\":9,\"multiplier\":%d}]');", 
                serverName, onlineCount, CurrentServerFlag, XDonate);
            executeEvent(i, 0, eventStr2);
        }
    }
    
    return 1;
}

stock UpdatePlayerFlag(playerid)
{
    if(!IsPlayerConnected(playerid) || PI[playerid][pCustomInterface][2] != 5)
        return 0;
    
    new eventStr1[128], eventStr2[256];
    
    format(eventStr1, sizeof(eventStr1), "window.executeEvent('event.hudSA.updateSanAndreasHudVisible', '[%s]');", 
        PI[playerid][pCustomInterface][2] == 5 ? "true" : "false");
    executeEvent(playerid, 0, eventStr1);

    format(eventStr2, sizeof(eventStr2), "window.executeEvent('event.arizonahud.serverInfo', '[{\"id\":1,\"title\":\"%s\",\"project\":\"Arizona\",\"type\":\"Role play\",\"onLine\":%d,\"flag\":%d,\"logo\":9,\"multiplier\":%d}]');", 
        Setting_Server[7], Iter_Count(Player), CurrentServerFlag, XDonate);
    executeEvent(playerid, 0, eventStr2);
    
    return 1;
}

stock GetFlagInfo(playerid)
{
    new info[128];
    format(info, sizeof(info), "Текущий флаг: {FFFFFF}%d {00FF00}(диапазон: {FFFFFF}%d-%d{00FF00}, стандартный: {FFFFFF}%d{00FF00})", 
        CurrentServerFlag, MIN_FLAG_VALUE, MAX_FLAG_VALUE, DEFAULT_FLAG);
    SCM(playerid, -1, info);
    return 1;
}


CMD:set_flag(playerid, params[])
{    
	if(!IsOsnovatel(playerid))
		return false;

    new flag;
    
    if(sscanf(params, "i", flag))
    {
        GetFlagInfo(playerid);
        SCM(playerid, -1, "Использование: /test_flag [1-49] - установить флаг");
        return 1;
    }
    
    return 1;
}