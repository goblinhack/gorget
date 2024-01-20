//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_FWD_HPP_
#define _MY_FWD_HPP_

#include <vector>

class Charmap;
class Font;
class Level;
class LevelPh2Room;
class LevelPh3Obstacles;
class LevelPh4Block;
class Tex;
class Tile;
class Tilemap;
class Tp;
class Wid;
class WidPopup;

struct LevelData_;
struct Dmap_;
struct SDL_Surface;

using Dmapp              = struct Dmap_ *;
using Fontp              = class Font *;
using LevelDatap         = struct LevelData_ *;
using Levelp             = class Level *;
using LevelPh2Roomp      = class LevelPh2Room *;
using LevelPh3Obstaclesp = class LevelPh3Obstacles *;
using LevelPh4Blockp     = class LevelPh4Block *;
using Lightp             = class Light *;
using Texp               = class Tex *;
using Tilemapp           = class Tilemap *;
using Tilep              = class Tile *;
using Tilevec            = std::vector< class Tile            *>;
using Id                 = unsigned int;
using TpId               = Id;
using ThingId            = Id;
using Tpp                = class Tp *;
using Widp               = class Wid *;

#endif
