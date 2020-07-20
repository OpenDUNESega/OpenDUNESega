#include "house.h"
#include "map.h"
#include "math.h"
#include "object.h"
#include "tile.h"
#include "unit.h"

uint32 g_unk_unit_updatemap;

/**
 * Update the map around the Unit depending on the type (entering tile, leaving, staying).
 * @param type The type of action on the map.
 * @param unit The Unit doing the action.
 */
void Unit_UpdateMap(uint16 type, Unit *unit)
{
	const UnitInfo *ui;
    tile32 position;
    uint16 packed;
	Tile *t;
	uint16 radius;

	if (unit == NULL || unit->o.flags.s.isNotOnMap || !unit->o.flags.s.used) return;

	ui = &g_table_unitInfo[unit->o.type];

	if (ui->movementType == MOVEMENT_WINGER) return;
    
    position = unit->o.position;
    if (g_unk_unit_updatemap) position = g_unk_unit_updatemap;
    packed = Tile_PackTile(position);
    t = &g_map[packed];
    
    if (t->isUnveiled || unit->o.houseID == g_playerHouseID) {
        Unit_HouseUnitCount_Add(unit, g_playerHouseID);
    }
    else {
        Unit_HouseUnitCount_Remove(unit);
    }

    if (type == 1) {
        if (House_AreAllied(unit->o.houseID, g_playerHouseID) && !Map_IsPositionUnveiled(packed) && unit->o.type != UNIT_SANDWORM) {
            Tile_RemoveFogInRadius(position, 1);
        }
        if (Object_GetByPackedTile(packed) == NULL) {
            t->index = unit->o.index + 1;
            t->hasUnit = true;
        }
    }
    
    if (type != 0) {
        unit->o.flags.s.isDirty = true;
		g_dirtyUnitCount++;
    }
    
    radius = ui->dimension + 3;
    if (radius > 0x20) radius = 0x20;
    
    Map_UpdateAround(radius, position, unit, *((((uint32*)g_functions)+type)));
    
    if (unit->o.type != UNIT_SANDWORM) {
        Map_UpdateAround(radius, unit->targetLast, unit, *((((uint32*)g_functions)+type)));
        Map_UpdateAround(radius, unit->targetPreLast, unit, *((((uint32*)g_functions)+type)));
    }
}
