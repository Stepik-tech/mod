#define MIN_LOGO_VALUE 1
#define MAX_LOGO_VALUE 49 
#define CUSTOM_INTERFACE_TYPE 5
#define EVENT_ID 1

new ANIMIROVANNOEEBYCHEELOGO = MIN_LOGO_VALUE;

stock GetNextLogo(oldValue)
{
    new newValue = oldValue + 1;
    
    if(newValue > MAX_LOGO_VALUE)
        newValue = MIN_LOGO_VALUE;
    
    return newValue;
}

stock GetPreviousLogo(oldValue)
{
    new newValue = oldValue - 1;
    
    if(newValue < MIN_LOGO_VALUE)
        newValue = MAX_LOGO_VALUE;
    
    return newValue;
}

stock giflogo()
{
    new oldValue = ANIMIROVANNOEEBYCHEELOGO;
    ANIMIROVANNOEEBYCHEELOGO = GetNextLogo(oldValue);
    
    new onlineCount = Iter_Count(Player);
    new serverName[64];
    strcat(serverName, Setting_Server[7], sizeof(serverName));

    foreach(new i : Player)
    {
        if(PI[i][pCustomInterface][2] == CUSTOM_INTERFACE_TYPE) 
        {
            new jsonStr[128];
            format(jsonStr, sizeof(jsonStr), 
                "{\"id\":%d,\"title\":\"%s\",\"project\":\"Arizona\",\"type\":\"Role play\",\"onLine\":%d,\"flag\":33,\"logo\":%d,\"multiplier\":%d}",
                EVENT_ID, serverName, onlineCount, ANIMIROVANNOEEBYCHEELOGO, XDonate);
            
            new eventStr[200];
            format(eventStr, sizeof(eventStr), "window.executeEvent('event.arizonahud.serverInfo', '[%s]')", jsonStr);
            
            executeEvent(i, 0, eventStr);
        }
    }
    
    return 1;
}

stock PreviousLogo()
{
    ANIMIROVANNOEEBYCHEELOGO = GetPreviousLogo(ANIMIROVANNOEEBYCHEELOGO);
    UpdateAllPlayersWithLogo();
    return ANIMIROVANNOEEBYCHEELOGO;
}

stock NextLogo()
{
    ANIMIROVANNOEEBYCHEELOGO = GetNextLogo(ANIMIROVANNOEEBYCHEELOGO);
    UpdateAllPlayersWithLogo();
    return ANIMIROVANNOEEBYCHEELOGO;
}

stock SetLogoForced(newLogo)
{
    if(newLogo >= MIN_LOGO_VALUE && newLogo <= MAX_LOGO_VALUE)
    {
        ANIMIROVANNOEEBYCHEELOGO = newLogo;
        UpdateAllPlayersWithLogo();
        return 1;
    }
    return 0;
}

stock GetCurrentLogo()
{
    return ANIMIROVANNOEEBYCHEELOGO;
}

stock ResetLogo()
{
    ANIMIROVANNOEEBYCHEELOGO = MIN_LOGO_VALUE;
    UpdateAllPlayersWithLogo();
    return ANIMIROVANNOEEBYCHEELOGO;
}

stock UpdateLogoForPlayer(playerid)
{
    if(!IsPlayerConnected(playerid) || PI[playerid][pCustomInterface][2] != CUSTOM_INTERFACE_TYPE)
        return 0;
        
    new jsonStr[128];
    format(jsonStr, sizeof(jsonStr), 
        "{\"id\":%d,\"title\":\"%s\",\"project\":\"Arizona\",\"type\":\"Role play\",\"onLine\":%d,\"flag\":26,\"logo\":%d,\"multiplier\":%d}",
        EVENT_ID, Setting_Server[7], Iter_Count(Player), ANIMIROVANNOEEBYCHEELOGO, XDonate);
    
    new eventStr[200];
    format(eventStr, sizeof(eventStr), "window.executeEvent('event.arizonahud.serverInfo', '[%s]')", jsonStr);
    
    return executeEvent(playerid, 0, eventStr);
}

stock UpdateAllPlayersWithLogo(customLogo = -1)
{
    new logoToUse = (customLogo == -1) ? ANIMIROVANNOEEBYCHEELOGO : customLogo;
    new onlineCount = Iter_Count(Player);
    new serverName[64];
    strcat(serverName, Setting_Server[7], sizeof(serverName));
    
    foreach(new i : Player)
    {
        if(PI[i][pCustomInterface][2] == CUSTOM_INTERFACE_TYPE) 
        {
            new jsonStr[128];
            format(jsonStr, sizeof(jsonStr), 
                "{\"id\":%d,\"title\":\"%s\",\"project\":\"Arizona\",\"type\":\"Role play\",\"onLine\":%d,\"flag\":26,\"logo\":%d,\"multiplier\":%d}",
                EVENT_ID, serverName, onlineCount, logoToUse, XDonate);
            
            new eventStr[200];
            format(eventStr, sizeof(eventStr), "window.executeEvent('event.arizonahud.serverInfo', '[%s]')", jsonStr);
            
            executeEvent(i, 0, eventStr);
        }
    }
    
    return 1;
}

stock GetLogoInfo(playerid)
    return SCMF(playerid, -1, "щас %d, максимально %d", ANIMIROVANNOEEBYCHEELOGO, MAX_LOGO_VALUE);

cmd:getlogo(playerid)
{
	if(!IsOsnovatel(playerid))
		return false;

    return GetLogoInfo(playerid);
}
