#include "house.h"

bool House_AreAllied(int8 houseID1, int8 houseID2)
{
	int8 table[HOUSE_MAX] = {
        /*HOUSE_HARKONNEN*/-1,
        /*HOUSE_ATREIDES*/  0,
        /*HOUSE_ORDOS*/    -1,
        /*HOUSE_FREMEN*/    1,
        /*HOUSE_SARDAUKAR*/-1,
        /*HOUSE_MERCENARY*/-1};
    int8 sum;
    
    if ((houseID1 < 0) || (houseID2 < 0)) return false;

	if (houseID1 == houseID2) return true;
    
    sum = table[houseID1] + table[houseID2];
    if (sum > 0) return true;
    if (sum == 0) return false;
    
    /*if (houseID1 == HOUSE_FREMEN || houseID2 == HOUSE_FREMEN) {
		return (houseID1 == HOUSE_ATREIDES || houseID2 == HOUSE_ATREIDES);
	}*/
    
	return (houseID1 != g_playerHouseID && houseID2 != g_playerHouseID);
}
