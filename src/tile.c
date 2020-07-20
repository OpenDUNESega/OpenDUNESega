#include "tile.h"
#include "math.h"

uint16 Tile_GetDirectionPacked(uint16 packed_from, uint16 packed_to)
{
	static const uint16 returnValues[16] = {0x60, 0x40, 0x80, -1, 0xA0, 0xC0, 0x80, -1, 0x20, 0x40, 0x0, 01, 0xE0, 0xC0, 0x0, -1};

	int16 x1, y1, x2, y2;
	int16 dx, dy;
	uint16 index;

	x1 = Tile_GetPackedX(packed_from);
	y1 = Tile_GetPackedY(packed_from);
	x2 = Tile_GetPackedX(packed_to);
	y2 = Tile_GetPackedY(packed_to);

	index = 0;

	dy = y2 - y1;
	if (dy < 0) {
		index |= 0x8;
		dy = -dy;
	}

	dx = x2 - x1;
	if (dx < 0) {
		index |= 0x4;
		dx = -dx;
	}

	if (dy > dx*2) {
		index |= 0x2;
	} else if (dx > dy*2) {
		index |= 0x1;
	}

	return returnValues[index];
}

tile32 Tile_MoveByDirection(tile32 tile, int16 orientation, uint16 distance)
{
    int diffX, diffY;
    int roundingOffsetX, roundingOffsetY;

    distance = min(distance, 0xFF);

    if (distance == 0) return tile;

    diffX = Math_Cos[orientation & 0xFF];
    diffY = -Math_Sin[orientation & 0xFF];

    /* Always round away from zero */
    roundingOffsetX = diffX < 0 ? -64 : 64;
    roundingOffsetY = diffY < 0 ? -64 : 64;

    return Tile_MakeXY(
        Tile_GetX(tile) + ((diffX * distance + roundingOffsetX) / 128),
        Tile_GetY(tile) + ((diffY * distance + roundingOffsetY) / 128));
}

uint16 Tile_GetYProjection(tile32 tile, uint16 orientation, uint16 distance) /* tile unused */
{
    if (distance == 0)
        return 0;
    distance = min(distance, 0xff);
    return (-Math_Sin[orientation&0xff]*distance + 64) / 128;
}

uint16 Tile_GetXProjection(tile32 tile, uint16 orientation, uint16 distance) /* tile unused */
{
    if (distance == 0)
        return 0;
    distance = min(distance, 0xff);
    return (Math_Cos[orientation&0xff]*distance + 64) / 128;
}

tile32 Tile_AddTileDiff(tile32 from, int16 diffX, int16 diffY)
{
    return Tile_MakeXY(Tile_GetX(from) + diffX, Tile_GetY(from) + diffY);
}

uint16 Tile_GetPackedByDirection(uint16 packed_from, uint16 direction)
{
    int16 returnValues[] = {
        -0x40, -0x3F,  0x1,  0x41,
         0x40,  0x3F, -0x1, -0x41};
    return packed_from + returnValues[direction%8];
}