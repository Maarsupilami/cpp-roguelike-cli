# Dungeon RPG

A text-based dungeon crawler built in C++17 as a hands-on OOP learning project.

## Features (in progress)

- Class hierarchy: `Character` → `Player` / `Enemy` → subclasses
- Three playable classes: Warrior, Mage, Rogue
- Six enemy types across three dungeon levels
- Turn-based combat with critical hits
- Inventory system with usable and equippable items
- XP-based leveling with stat growth

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
└── entities/
    ├── character.h
    ├── player.h
    ├── enemy.h
    ├── game_constants.h
    └── classes/
        ├── warrior.h
        ├── mage.h
        └── rogue.h
```

## Dungeon layout

| Level | Encounters               | Boss            |
|-------|--------------------------|-----------------|
| 1     | 2 random enemies         | Goblin Chief    |
| 2     | 3 random enemies         | Stone Golem     |
| 3     | —                        | Dark Necromancer|
