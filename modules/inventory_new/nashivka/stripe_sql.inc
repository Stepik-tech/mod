stock InventoryStripeSave(playerid, inventoryStripeId, inventoryStripeSlotId, inventoryUnicaltityCount, inventoryTypeId = 1)
    return f(global_str, sizeof(global_str), "SELECT * FROM `inventory_stripe` WHERE `stripe_account_id` = '%d' AND `stripe_slot` = '%d' AND `stripe_point` = '%d' AND `stripe_inventory_type` = '%d'", PI[playerid][pID], inventoryStripeSlotId, inventoryUnicaltityCount, inventoryTypeId), mysql_tquery(mysql, global_str, "@InventoryStripeSave", "iiiii", playerid, inventoryStripeId, inventoryStripeSlotId, inventoryUnicaltityCount, inventoryTypeId);

public: @InventoryStripeSave(playerid, inventoryStripeId, inventoryStripeSlotId, inventoryUnicaltityCount, inventoryTypeId)
{
    SCMF(playerid, -1, "InventoryStripeSave inventoryStripeId, %d inventoryStripeSlotId, %d inventoryUnicaltityCount, %d inventoryTypeId %d", inventoryStripeId, inventoryStripeSlotId, inventoryUnicaltityCount, inventoryTypeId);
    if(cache_num_rows())
    {
        f(global_str, sizeof(global_str), "DELETE FROM `inventory_stripe` WHERE `stripe_account_id` = '%d' AND `stripe_slot` = '%d' AND `stripe_point` = '%d' AND `stripe_inventory_type` = '%d'", PI[playerid][pID], inventoryStripeSlotId, inventoryUnicaltityCount, inventoryTypeId);
    }
    else f(global_str, sizeof(global_str), "INSERT INTO `inventory_stripe` (`stripe_account_id`, `stripe_inventory_type`, `stripe_type`, `stripe_slot`, `stripe_point`, `stripe_item_id`) VALUES ('%d', '%d', '%d', '%d', '%d', '%d');", PI[playerid][pID], inventoryTypeId, inventoryStripeId, inventoryStripeSlotId, inventoryUnicaltityCount, StripeData[inventoryStripeId][E_STRIPE_ITEMID]);
    
    return mysql_tquery(mysql, global_str), true;
}

public: InventoryStripeLoad(playerid)
{
    if(!cache_num_rows())
        return false;

    for(new i, tempData[5]; i < cache_num_rows(); i++)
    {
        cache_get_value_name_int(i, !"stripe_slot", tempData[0]);
        cache_get_value_name_int(i, !"stripe_point", tempData[1]);
        cache_get_value_name_int(i, !"stripe_type", tempData[2]);
        cache_get_value_name_int(i, !"stripe_item_id", tempData[3]);
        cache_get_value_name_int(i, !"stripe_inventory_type", tempData[4]);

        switch(tempData[4])
        {
            case 1:
            {
                PlayerInventoryStripeData[playerid][tempData[0]][tempData[1]][E_STRIPE_TYPE] = tempData[2];
                PlayerInventoryStripeData[playerid][tempData[0]][tempData[1]][E_STRIPE_TYPE_ITEMID] = tempData[3];
            }
            case 2:
            {
                PlayerAccessoryStripeData[playerid][tempData[0]][tempData[1]][E_STRIPE_TYPE] = tempData[2];
                PlayerAccessoryStripeData[playerid][tempData[0]][tempData[1]][E_STRIPE_TYPE_ITEMID] = tempData[3];
            }

            case 3:
            {
                PlayerSkinStripeData[playerid][tempData[0]][tempData[1]][E_STRIPE_TYPE] = tempData[2];
                PlayerSkinStripeData[playerid][tempData[0]][tempData[1]][E_STRIPE_TYPE_ITEMID] = tempData[3];
            }
        }
    }

    return true;
}