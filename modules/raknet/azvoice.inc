const MAX_AZVOICE_ZONE = 20000;

enum AZVoice_data
{
    voiceZoneType,
    voiceZoneAttach,
    voiceZoneAudioTime,
    voiceZoneAudioTimeSave,
    voiceZoneAudioTimeStart,
    bool:voiceZoneAudioPlay,
    voiceZoneAudioPlayId,
    voiceZoneUpdateTimer
}

enum 
{
    AZVoiceRadioZone,
    AZVoiceSoundZone,
    AZVoiceLocalZone
}

new 
    Iterator:AZVoiceZone<MAX_AZVOICE_ZONE>,
    Iterator:AZVoice[MAX_PLAYERS]<MAX_PLAYERS>,
    AZVoiceData[MAX_AZVOICE_ZONE][AZVoice_data];

stock CreateAZVoiceZone(zoneTypeId, attachedId, const attachText[] = "", textColor = 0xffffffff, forplayerid = INVALID_PLAYER_ID, Float:Position[] = {0.0, 0.0, 0.0})
{
    new zoneId = Iter_Free(AZVoiceZone);
    Iter_Add(AZVoiceZone, zoneId);

    AZVoiceData[zoneId][voiceZoneType] = zoneTypeId;
    AZVoiceData[zoneId][voiceZoneAttach] = attachedId;

    return send_CreateAZVoiceZone(zoneId, zoneTypeId, attachedId, attachText, textColor, forplayerid, Position), zoneId;
}

stock send_CreateAZVoiceZone(zoneId, zoneTypeId, attachedId, const attachText[] = "", textColor = 0xffffffff, forplayerid = INVALID_PLAYER_ID, Float:Position[] = {0.0, 0.0, 0.0})
{
    if(zoneId == -1)
        return false;

    new BitStream:bs = BS_New();

	BS_WriteValue(bs,
		PR_UINT8, 10,
		PR_UINT16, zoneId + 1,
		PR_UINT16, strlen(attachText),
		PR_STRING, attachText,
		PR_UINT32, textColor,
		PR_UINT8, zoneTypeId,
		zoneTypeId == 4 ? PR_FLOAT : PR_UINT16, zoneTypeId == 4 ? 50 : attachedId);

    if(zoneTypeId == 1)
        BS_WriteValue(bs, PR_UINT8, 1, PR_UINT8, 0, PR_UINT8, 2);

    else
    {
        if(zoneTypeId == 4)
        {
            BS_WriteValue(bs,
                PR_VECTOR, Position,
                PR_VECTOR, Position,
                PR_UINT32, 0);
        }
        BS_WriteValue(bs,
            PR_UINT32, 0);
    }

    if(forplayerid == INVALID_PLAYER_ID)
        SendVoicePacket(bs, attachedId, zoneTypeId == 3 ? 1 : zoneTypeId == 4 ? 3 : 2, 252, zoneTypeId == 2 ? attachedId : INVALID_PLAYER_ID, PR_HIGH_PRIORITY, PR_RELIABLE_ORDERED, 5);

    else
        SendVoicePacket(bs, forplayerid, 2, 252, forplayerid, PR_HIGH_PRIORITY, PR_RELIABLE_ORDERED, 5);

	return BS_Delete(bs);
}

stock AudioPlayZoneAZVoice(zoneId, const audioLink[], Float:audioVolume, audioPlayTime = 0, forplayerid = INVALID_PLAYER_ID)
{
    if(zoneId == -1)
        return false;

	new BitStream:bs = BS_New();

	BS_WriteValue(bs,
		PR_UINT8, 17,
		PR_UINT16, zoneId + 1,
		PR_BOOL, true,
		PR_UINT16, strlen(audioLink),
		PR_STRING, audioLink,
		PR_FLOAT, 0.0,
		PR_FLOAT, audioVolume);

	if(audioPlayTime)
		BS_WriteValue(bs,
			PR_BOOL, true,
			PR_UINT32, audioPlayTime);

    if(forplayerid == INVALID_PLAYER_ID)
    {
        if(AZVoiceData[zoneId][voiceZoneType] == 3)
            SendVoicePacket(bs, AZVoiceData[zoneId][voiceZoneAttach], 1, 252, INVALID_PLAYER_ID, PR_HIGH_PRIORITY, PR_RELIABLE_ORDERED, 5);

        else
            SendVoicePacket(bs, AZVoiceData[zoneId][voiceZoneAttach], 2, 252, AZVoiceData[zoneId][voiceZoneAttach], PR_HIGH_PRIORITY, PR_RELIABLE_ORDERED, 5);
    }

    else
        SendVoicePacket(bs, forplayerid, 2, 252, forplayerid, PR_HIGH_PRIORITY, PR_RELIABLE_ORDERED, 5);

    if(0 <= audioPlayTime <= 1)
        f(global_str, 256, "api.beluy.ru/samp/audio_duration.php?%s", audioLink),
        HTTP(zoneId, HTTP_GET, global_str, "", "AudioSetMaxTimeAZVoice");
	
	return BS_Delete(bs);
}

stock AudioStopZoneAZVoice(zoneId, forplayerid = INVALID_PLAYER_ID)
{
    if(zoneId == -1)
        return false;

    new BitStream:bs = BS_New();

    BS_WriteValue(bs, 
		PR_UINT8, 13, 
		PR_UINT16, zoneId + 1);

    if(forplayerid == INVALID_PLAYER_ID && AZVoiceData[zoneId][voiceZoneType] == 3)
        SendVoicePacket(bs, AZVoiceData[zoneId][voiceZoneAttach], 1, 252, INVALID_PLAYER_ID, PR_HIGH_PRIORITY, PR_RELIABLE_ORDERED, 5);

    else
        SendVoicePacket(bs, forplayerid, 2, 252, forplayerid, PR_HIGH_PRIORITY, PR_RELIABLE_ORDERED, 5);

    ServerStopAZVoice(zoneId);

    return BS_Delete(bs);
}

stock DestroyAZVoiceZone(zoneId, forplayerid = INVALID_PLAYER_ID)
{
    if(zoneId == -1)
        return false;

    send_DestroyZoneAZVoice(zoneId, AZVoiceData[zoneId][voiceZoneType], forplayerid);
    return Iter_Remove(AZVoiceZone, zoneId);
}

stock send_DestroyZoneAZVoice(zoneId, zoneType, forplayerid = INVALID_PLAYER_ID)
{
    if(zoneId == -1)
        return false;

	new BitStream:bs = BS_New();

	BS_WriteValue(bs, 
		PR_UINT8, 11, 
		PR_UINT16, zoneId + 1);

    SendVoicePacket(bs, forplayerid, 2, 252, forplayerid, PR_HIGH_PRIORITY, PR_RELIABLE_ORDERED, 5);

    return BS_Delete(bs);
}

stock SearchAZVoiceZoneID(zoneId, zoneAttachId, zoneTypeId)
{
    static zoneSearchedCount; zoneSearchedCount = 0;

    for(new i; i < Iter_Count(AZVoiceZone); i++)
        if(AZVoiceData[i][voiceZoneAttach] == zoneAttachId && AZVoiceData[i][voiceZoneType] == zoneTypeId)
        {
            if(zoneSearchedCount == zoneId)
                return i;

            zoneSearchedCount++;
        }

    return INVALID_DATA_ID;
}

stock SendVoicePacket(BitStream:bs, sendId, typeId, rpcId = INVALID_DATA_ID, forplayerid = INVALID_PLAYER_ID, PR_PacketPriority:priority = PR_HIGH_PRIORITY, PR_PacketReliability:reliability = PR_RELIABLE_ORDERED, orderingchannel = 0)
{
    if(sendId == INVALID_PLAYER_ID)
        return false;

    foreach(new i: Player)
    {
        static target; target = forplayerid != INVALID_PLAYER_ID ? forplayerid : i;

        if(rpcId == INVALID_DATA_ID)
        {
            PR_SendPacket(bs, target, priority, reliability, orderingchannel);
            if(typeId == 3) PR_SendPacket(bs, sendId, priority, reliability, orderingchannel);
        }
        else
        {
            PR_SendRPC(bs, target, rpcId, priority, reliability, orderingchannel);
            if(typeId == 3) PR_SendRPC(bs, sendId, rpcId, priority, reliability, orderingchannel);
        }

        if(forplayerid != INVALID_PLAYER_ID)
            break;
    }
    return true;
}

public: AudioSetMaxTimeAZVoice(index, response_code, data[]) 
{
	//if(response_code != 200)
      // return printf("(AudioSetMaxTimeAZVoice:214) request get audio_duration a error (response_code %d | index %d | data %s)", response_code, response_code, data), false;

    AZVoiceData[index][voiceZoneAudioPlay] = true;
    AZVoiceData[index][voiceZoneAudioTime] = gettime() + strval(data);
    AZVoiceData[index][voiceZoneAudioTimeSave] = strval(data);
    AZVoiceData[index][voiceZoneAudioTimeStart] = gettime();
    AZVoiceData[index][voiceZoneUpdateTimer] = CallTimeOutFunction("AudioUpdateAZVoice", 1000, true, "d", index);

	return true;	
}

public: AudioUpdateAZVoice(zoneId)
{
    if(!Iter_Contains(AZVoiceZone, zoneId) || !AZVoiceData[zoneId][voiceZoneAudioPlay])
		return KillTimer(AZVoiceData[zoneId][voiceZoneUpdateTimer]), AZVoiceData[zoneId][voiceZoneUpdateTimer] = INVALID_DATA_ID;

    if(AZVoiceData[zoneId][voiceZoneAudioTime] < gettime())
        ServerStopAZVoice(zoneId);

    return true;
}

stock ServerStopAZVoice(zoneId)
{
    AZVoiceData[zoneId][voiceZoneAudioTime] = 
    AZVoiceData[zoneId][voiceZoneAudioTimeSave] = 
    AZVoiceData[zoneId][voiceZoneAudioTimeStart] = 
    AZVoiceData[zoneId][voiceZoneAudioPlay] = false;
    KillTimer(AZVoiceData[zoneId][voiceZoneUpdateTimer]), AZVoiceData[zoneId][voiceZoneUpdateTimer] = INVALID_DATA_ID;
}

stock SendPlayerVoiceKey(playerid, keyid, const name[])
{
	new BitStream:bs = BS_New();

    BS_WriteValue(bs, 
        PR_UINT8, 6,
        PR_UINT8, keyid,
        PR_UINT16, strlen(name),
        PR_STRING, name);

    SendVoicePacket(bs, playerid, 2, 252, playerid, PR_HIGH_PRIORITY, PR_RELIABLE_ORDERED, 5);
    return BS_Delete(bs);
}

stock ToggleVoiceState(playerid, bool:status = false)
{
    if(!pTemp[playerid][pVoiceInitied])
        return false;

    new BitStream:bs = BS_New();

    BS_WriteValue(bs,
        PR_UINT8, 19,
        PR_UINT16, 0,
        PR_BOOL, status);

    return SendVoicePacket(bs, playerid, 2, 252, playerid, PR_HIGH_PRIORITY, PR_RELIABLE_ORDERED, 5), BS_Delete(bs);
}

IPacket:252(playerid, BitStream:bs)
{
    if(!GetPlayerLauncher(playerid) || !pTemp[playerid][pVoiceKeyPressed])
        return false;

    if(PI[playerid][pMuteTime])
        return SendMuteMessage(playerid);
    
    static packet_voice_channel[2], packet_voice_length_byte, packet_voice_press_button_id, packet_voice_zone_data[2];
    new BitStream:send_bitstream = BS_New();

    BS_ReadValue(bs, 
        PR_IGNORE_BITS, 8, 
        PR_UINT8, packet_voice_channel[0], 
        PR_UINT8, packet_voice_channel[1], 
        PR_UINT8, packet_voice_press_button_id);

    if(packet_voice_press_button_id == PI[playerid][pHotKeyInfo][0])
        packet_voice_zone_data[0] = OrgInfo[PI[playerid][pMember][0]][oAZVoiceZone], packet_voice_zone_data[1] = 4;

    else packet_voice_zone_data[0] = SearchAZVoiceZoneID(AZVoiceLocalZone, playerid, 2), packet_voice_zone_data[1] = 2;

    BS_WriteValue(send_bitstream, 
        PR_UINT8, 252, 
        PR_UINT16, playerid, 
        PR_UINT8, packet_voice_channel[0], 
        PR_UINT8, packet_voice_channel[1], 
        PR_UINT16, 1, 
        PR_UINT16, packet_voice_zone_data[0] + 1);

    BS_GetNumberOfBytesUsed(bs, packet_voice_length_byte);

    for(new i = 4, id; i < packet_voice_length_byte; i++)
        BS_ReadUint8(bs, id), BS_WriteUint8(send_bitstream, id);

    SendVoicePacket(send_bitstream, playerid, packet_voice_zone_data[1], INVALID_DATA_ID, INVALID_PLAYER_ID, PR_HIGH_PRIORITY, PR_UNRELIABLE_SEQUENCED, 5); 
    BS_Delete(send_bitstream);

    return true;
}

ICustomRPC:252(playerid, BitStream:bs)
{
    if(!GetPlayerLauncher(playerid))
        return false;

    static customid;
    BS_ReadUint8(bs, customid);

    //printf("ICustomRPC(252): %d", customid);

    if(customid == 3 && !pTemp[playerid][pVoiceInitied])
        pTemp[playerid][pVoiceInitied] = true;

    else if(customid == 5)
    {
        static bool:status;
        BS_ReadValue(bs, PR_IGNORE_BITS, 8, PR_BOOL, status);
        pTemp[playerid][pVoiceKeyPressed] = status;
        //SendPlayerDebugF(playerid, "VOICE_RECORD_STATUS = %s", status ? "true" : "false");
    }

    return true;
}