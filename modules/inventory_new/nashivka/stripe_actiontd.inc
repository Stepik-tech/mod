stock ShowTextDrawReflectionMode(playerid, healthString[], time)
{
    reflection[playerid][0] = CreatePlayerTextDraw(playerid, 247.616501, 381.755707, "");
    PlayerTextDrawLetterSize(playerid, reflection[playerid][0], 0.480000, 1.120000);
    PlayerTextDrawTextSize(playerid, reflection[playerid][0], 16.000000, 67.000000);
    PlayerTextDrawAlignment(playerid, reflection[playerid][0], 1);
    PlayerTextDrawColor(playerid, reflection[playerid][0], 0xFFFFFFFFFFFFFFFF);
    PlayerTextDrawUseBox(playerid, reflection[playerid][0], 0);
    PlayerTextDrawBoxColor(playerid, reflection[playerid][0], 0xFFFFFFFF80808080);
    PlayerTextDrawSetShadow(playerid, reflection[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, reflection[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, reflection[playerid][0], 0x00000000);
    PlayerTextDrawFont(playerid, reflection[playerid][0], 5);
    PlayerTextDrawSetProportional(playerid, reflection[playerid][0], 0);
    PlayerTextDrawSetSelectable(playerid, reflection[playerid][0], 0);
    PlayerTextDrawSetPreviewModel(playerid, reflection[playerid][0], 1318);
    PlayerTextDrawSetPreviewRot(playerid, reflection[playerid][0], 94.000000, 0.000000, 90.000000, 0.495400);

    reflection[playerid][1] = CreatePlayerTextDraw(playerid, 243.333206, 400.777802, "LD_BEAT:chit");
    PlayerTextDrawLetterSize(playerid, reflection[playerid][1], 0.480000, 1.120000);
    PlayerTextDrawTextSize(playerid, reflection[playerid][1], 25.000000, 31.000000);
    PlayerTextDrawAlignment(playerid, reflection[playerid][1], 1);
    PlayerTextDrawColor(playerid, reflection[playerid][1], 0xFFFFFFFFFFFFFFFF);
    PlayerTextDrawUseBox(playerid, reflection[playerid][1], 0);
    PlayerTextDrawBoxColor(playerid, reflection[playerid][1], 0xFFFFFFFF80808080);
    PlayerTextDrawSetShadow(playerid, reflection[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, reflection[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, reflection[playerid][1], 0x000000FF);
    PlayerTextDrawFont(playerid, reflection[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, reflection[playerid][1], 0);
    PlayerTextDrawSetSelectable(playerid, reflection[playerid][1], 0);

    reflection[playerid][2] = CreatePlayerTextDraw(playerid, 249.383301, 390.570709, "");
    PlayerTextDrawLetterSize(playerid, reflection[playerid][2], 0.480000, 1.120000);
    PlayerTextDrawTextSize(playerid, reflection[playerid][2], 13.000000, 50.000000);
    PlayerTextDrawAlignment(playerid, reflection[playerid][2], 1);
    PlayerTextDrawColor(playerid, reflection[playerid][2], 0xFFFFFFFF800000FF);
    PlayerTextDrawUseBox(playerid, reflection[playerid][2], 0);
    PlayerTextDrawBoxColor(playerid, reflection[playerid][2], 0xFFFFFFFF80808080);
    PlayerTextDrawSetShadow(playerid, reflection[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, reflection[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, reflection[playerid][2], 0x00000000);
    PlayerTextDrawFont(playerid, reflection[playerid][2], 5);
    PlayerTextDrawSetProportional(playerid, reflection[playerid][2], 0);
    PlayerTextDrawSetSelectable(playerid, reflection[playerid][2], 0);
    PlayerTextDrawSetPreviewModel(playerid, reflection[playerid][2], 1318);
    PlayerTextDrawSetPreviewRot(playerid, reflection[playerid][2], 94.000000, 0.000000, 90.000000, 0.495400);

    reflection[playerid][3] = CreatePlayerTextDraw(playerid, 246.399902, 403.789001, "LD_BEAT:chit");
    PlayerTextDrawLetterSize(playerid, reflection[playerid][3], 0.480000, 1.120000);
    PlayerTextDrawTextSize(playerid, reflection[playerid][3], 19.000000, 24.000000);
    PlayerTextDrawAlignment(playerid, reflection[playerid][3], 1);
    PlayerTextDrawColor(playerid, reflection[playerid][3], 0xFFFFFFFF800000FF);
    PlayerTextDrawUseBox(playerid, reflection[playerid][3], 0);
    PlayerTextDrawBoxColor(playerid, reflection[playerid][3], 0xFFFFFFFF80808080);
    PlayerTextDrawSetShadow(playerid, reflection[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, reflection[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, reflection[playerid][3], 0x000000FF);
    PlayerTextDrawFont(playerid, reflection[playerid][3], 4);
    PlayerTextDrawSetProportional(playerid, reflection[playerid][3], 0);
    PlayerTextDrawSetSelectable(playerid, reflection[playerid][3], 0);

    reflection[playerid][4] = CreatePlayerTextDraw(playerid, 261.666504, 397.688904, healthString);
    PlayerTextDrawLetterSize(playerid, reflection[playerid][4], 0.272700, 1.631100);
    PlayerTextDrawTextSize(playerid, reflection[playerid][4], 1280.000000, 1280.000000);
    PlayerTextDrawAlignment(playerid, reflection[playerid][4], 2);
    PlayerTextDrawColor(playerid, reflection[playerid][4], 0xFFFFFFFF800000FF);
    PlayerTextDrawUseBox(playerid, reflection[playerid][4], 0);
    PlayerTextDrawBoxColor(playerid, reflection[playerid][4], 0xFFFFFFFF80808080);
    PlayerTextDrawSetShadow(playerid, reflection[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, reflection[playerid][4], 255);
    PlayerTextDrawBackgroundColor(playerid, reflection[playerid][4], 0xFFFFFFFFFFFFFFFF);
    PlayerTextDrawFont(playerid, reflection[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, reflection[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, reflection[playerid][4], 0);

    reflection[playerid][5] = CreatePlayerTextDraw(playerid, 255.949905, 416.829407, IntToStr(time));
    PlayerTextDrawLetterSize(playerid, reflection[playerid][5], 0.362800, 1.838500);
    PlayerTextDrawTextSize(playerid, reflection[playerid][5], 1280.000000, 1280.000000);
    PlayerTextDrawAlignment(playerid, reflection[playerid][5], 2);
    PlayerTextDrawColor(playerid, reflection[playerid][5], 0xFFFFFFFFA52A2AFF);
    PlayerTextDrawUseBox(playerid, reflection[playerid][5], 0);
    PlayerTextDrawBoxColor(playerid, reflection[playerid][5], 0xFFFFFFFF80808080);
    PlayerTextDrawSetShadow(playerid, reflection[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, reflection[playerid][5], 255);
    PlayerTextDrawBackgroundColor(playerid, reflection[playerid][5], 0xFFFFFFFFFFFFFFFF);
    PlayerTextDrawFont(playerid, reflection[playerid][5], 1);
    PlayerTextDrawSetProportional(playerid, reflection[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, reflection[playerid][5], 0);

    for(new i; i < 6; i++)
        PlayerTextDrawShow(playerid, reflection[playerid][i]);

    return true;
}