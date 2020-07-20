    org     $0  ; important for other orgs to work
    incbin  bin\dune.bin
   
_g_unitArray:      equ $00FF1000 ; Unit[102] ; first 12 elements are air units, next 13 are shells and rockets, final 77 are ground units
_g_structureArray: equ $00FF4EB8 ; Structure[73]
_g_map:            equ $00FF7D9C ; Tile[64*64], $00FF7EA0 - packed tile number $41 (top left square on the map with side $3E), $00FF8DDC - packed tile number $410 (top left square on the map with side $20)
_g_dirtyUnitCount: equ $00FFC21C ; uint16
; $00FFC240, uint16, is the number of the packed tile the cursor is currently above
_g_playerHouseID:  equ $00FFC274 ; uint16
_g_unk_unit_updatemap: equ $00FFC610 ; tile32
_s_randomSeed:     equ $FFFFE016 ; uint8[4]
    
    org $00E42 ; [$00E42,$00E84)
    ;jmp _Tools_Random_256 ; bug: screen shake = brutal graphical bugs and broken rockets
    
    org $1152E ; [$1152E,$115C6)
    jmp _Tile_GetDirectionPacked
    
    org $11632 ; [$11632,$1168C)
    jmp _Tile_MoveByDirection
    
    org $11724 ; [$11724,$11762)
    jmp _Tile_GetYProjection
    org $11762 ; [$11762,$1179E)
    jmp _Tile_GetXProjection
    org $1179E ; [$1179E,$117B6)
    jmp _Tile_AddTileDiff
    
    org $12A90 ; [$12A90,$12AB0)
    jmp _Tile_GetPackedByDirection
    
    org $19B4C ; [$19B4C,$19D38)
    jmp _Unit_UpdateMap
    org $19E10
     _Map_UpdateAround:
    
    org $1A002
     _Tile_RemoveFogInRadius:
    org $1A8DC
     _Object_GetByPackedTile:
    
    org $1AFEA
     _Map_IsPositionUnveiled:
    org $23264
     _Unit_HouseUnitCount_Add:
    org $23450
     _Unit_HouseUnitCount_Remove:
    org $23724 ; [$23724,$2375E)
    jmp _House_AreAllied
    
    org $46084 ; [$46084,$468BA)
    ;jmp _Unit_Move
    
    org $4AA24 ; [$4AA24,$4AA26)
    dc.l _g_map
    
    org $49CDC ; [$49CDC,$49DB6)
    jmp _memset
    org $49DB8 ; [$49DB8,$49EE6)
    jmp _memcpy
    org $49EE8 ; [$49EE8,$49F3E)
    jmp _memmove
    
_g_table_unitInfo: equ $0006BC08 ; UnitInfo[UNIT_MAX]
_g_table_unitInfo_jump_table: equ $0006C5BC ; uint32[UNIT_MAX]
    
_g_functions:      equ $000714EE ; uint8[3][3]
    
    org     $100000
    include out\out.s
    