stock SetSkinCustomCharacteristic(playerid, type, bool:toggle)
{
	switch(type)
	{
		case 0, 1: 
			if(GetPlayerLauncher(playerid)) SendPlayerClientPacket(playerid, type ? 91 : 163, toggle ? 128 : 0);
	}

	return true;
}