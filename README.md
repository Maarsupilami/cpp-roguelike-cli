# Dungeon RPG (CLI)

A text-based dungeon crawler built in C++23 as a hands-on OOP learning project.

> **Status: complete.** This repository is the finished CLI version.
> The project continues as a 2D graphical game using SFML: [cpp-roguelike-2d](https://github.com/Maarsupilami/cpp-roguelike-2d).

## C++ concepts covered

- Inheritance: `Character` → `Player` / `Enemy` → subclasses
- Abstract classes and pure virtual methods (`Item::use()`)
- Smart pointers: `std::unique_ptr` for polymorphic ownership
- `dynamic_cast` for safe downcasting (Necromancer summon, equip system)
- `std::vector<std::unique_ptr<Item>>` as abstract inventory
- Forward declarations to break circular dependencies
- `enum class` with `COUNT` trick for range-safe random selection
- `std::mt19937` + `std::uniform_int_distribution` for RNG
- `std::function` + lambdas as factory pattern (LootTable)
- Separation of I/O and logic for unit testability (`executeAttack`)
- Google Test via FetchContent (no install required)

## Features

- Three playable classes: Warrior, Mage, Rogue (with stat differences and crit)
- Six enemy types across three dungeon levels
- Turn-based combat with damage feedback
- Weighted loot table per enemy (`LootTable` with `std::function` factories)
- Stacking inventory: consumables merge into one slot with quantity
- Item use in combat and between fights
- `MagicScroll`: deals direct damage to enemy (`Enemy*` param on `use()`)
- Equip system: MainHand / OffHand slots, swap returns old weapon to inventory
- XP-based leveling with per-class stat growth
- Necromancer summon mechanic

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
├── game/
│   ├── game.h
│   ├── game.cpp
│   ├── combat.h        ← extracted for testability
│   └── combat.cpp
└── core/
    ├── character.h
    ├── player.h
    ├── enemy.h
    ├── item.h
    ├── loot_table.h    ← weighted drop system
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
        ├── magic_scroll.h
        └── weapon_types/sword/
            ├── sword.h
            └── iron_sword.h
tests/
└── main_test.cpp       ← 45 unit tests
```

## Dungeon layout

| Level | Encounters       | Boss             |
|-------|------------------|------------------|
| 1     | 2 random enemies | Goblin Chief     |
| 2     | 3 random enemies | Stone Golem      |
| 3     | —                | Dark Necromancer |
