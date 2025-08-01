//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_main.hpp"
#include "my_random.hpp"

//
// These are the first words in a seed name
//
static const char *dict1_names[] = {
    "alchemy",   "alpha",   "amulet",  "banshee", "bats",    "beast",    "berserk", "bleak",   "blood",   "bloody",
    "bogey",     "brazier", "castle",  "cave",    "centaur", "chalice",  "crow",    "crypt",   "crystal", "dank",
    "dark",      "death",   "demon",   "devil",   "dingy",   "dire",     "disco",   "djinn",   "donkey",  "doomed",
    "dragon",    "dwarf",   "eerie",   "elf",     "elve",    "entombed", "evil",    "fairy",   "fear",    "feral",
    "fiend",     "fiery",   "flesh",   "foot",    "foul",    "gargan",   "ghastly", "ghost",   "giant",   "gloop",
    "gnome",     "goblin",  "god",     "golem",   "grave",   "griffin",  "grim",    "grisly",  "grot",    "gryph",
    "haunt",     "heinous", "hell",    "hideo",   "hobbit",  "hollow",   "horror",  "howl",    "huge",    "imp",
    "impish",    "jabber",  "karma",   "king",    "kobold",  "kraken",   "legend",  "lore",    "lunar",   "lycanth",
    "macabre",   "maggot",  "maggots", "magic",   "magical", "maniac",   "maraud",  "mask",    "masked",  "medusa",
    "miasma",    "moan",    "moldy",   "monst",   "monster", "moon",     "mummy",   "muse",    "myth",    "necrotic",
    "nemesis",   "newt",    "oberon",  "occult",  "ogre",    "oracle",   "orc",     "owl",     "pale",    "pixie",
    "poison",    "potion",  "powder",  "power",   "prey",    "prince",   "prophet", "prowl",   "quail",   "quake",
    "queen",     "rage",    "raven",   "realm",   "rose",    "rouge",    "rune",    "sage",    "sandman", "scared",
    "scream",    "screech", "shaman",  "shriek",  "skele",   "skull",    "slate",   "slayer",  "slime",   "sorcer",
    "spell",     "spider",  "spirit",  "spook",   "stalk",   "stars",    "story",   "swarm",   "talis",   "tarant",
    "tarasque",  "terror",  "titan",   "toad",    "tomb",    "tragic",   "tremor",  "troll",   "ugly",    "unicorn",
    "unique",    "valiant", "valor",   "vampire", "vanish",  "vanqu",    "vice",    "vicious", "victim",  "villain",
    "vital",     "wail",    "wand",    "warlock", "weird",   "were",     "wicked",  "wild",    "wish",    "witch",
    "withering", "wizard",  "wolf",    "worry",   "worship", "xanadu",   "yeti",    "zar",     "dungeon"};

const char *os_rand_dict1_name(void)
{
  TRACE_NO_INDENT();
  return dict1_names[ os_random_range(0, ARRAY_SIZE(dict1_names)) ];
}
