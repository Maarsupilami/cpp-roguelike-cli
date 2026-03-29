# Dungeon RPG

A text-based dungeon crawler built in C++23 as a hands-on OOP learning project.

## Features

- Class hierarchy: `Character` → `Player` / `Enemy` → subclasses
- Three playable classes: Warrior, Mage, Rogue (with class selection)
- Six enemy types across three dungeon levels
- Turn-based combat with critical hits (Rogue)
- Inventory system with usable and equippable items (in progress)
- XP-based leveling with per-class stat growth
- Necromancer summon mechanic
- Google Test unit tests (FetchContent, no install required)

## Build

```bash
./build.sh
./build/dungeon
```

Requires CMake 3.28+ and a C++23-capable compiler (GCC 15+).

## Project structure

```
src/
├── main.cpp
└── core/
    ├── character.h
    ├── player.h
    ├── enemy.h
    ├── item.h
    ├── game_constants.h
    ├── classes/
    │   ├── warrior.h
    │   ├── mage.h
    │   └── rogue.h
    ├── enemies/
    │   ├── goblin.h
    │   ├── skeleton.h
    │   ├── troll.h
    │   ├── goblin_chief.h
    │   ├── stone_golem.h
    │   └── dark_necromancer.h
    └── items/
        ├── potion.h
        ├── weapon.h
        └── magic_scroll.h
tests/
└── main_test.cpp
```

## Dungeon layout

| Level | Encounters               | Boss            |
|-------|--------------------------|-----------------|
| 1     | 2 random enemies         | Goblin Chief    |
| 2     | 3 random enemies         | Stone Golem     |
| 3     | —                        | Dark Necromancer|
