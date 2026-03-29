#include <gtest/gtest.h>
#include "classes/warrior.h"
#include "classes/mage.h"
#include "classes/rogue.h"
#include "enemies/goblin.h"
#include "enemies/skeleton.h"
#include "enemies/troll.h"
#include "enemies/goblin_chief.h"
#include "enemies/stone_golem.h"
#include "enemies/dark_necromancer.h"
#include "game_constants.h"

// ─── Character base behaviour ────────────────────────────────────────────────

TEST(CharacterTest, TakeDamageReducesHp) {
    Warrior w("T");
    w.takeDamage(10);
    EXPECT_EQ(w.getHp(), WARRIOR_HP - 10);
}

TEST(CharacterTest, HpDoesNotGoBelowZero) {
    Warrior w("T");
    w.takeDamage(9999);
    EXPECT_EQ(w.getHp(), 0);
}

TEST(CharacterTest, HealDoesNotExceedMaxHp) {
    Warrior w("T");
    w.takeDamage(20);
    w.heal(9999);
    EXPECT_EQ(w.getHp(), w.getMaxHp());
}

TEST(CharacterTest, IsAliveAfterPartialDamage) {
    Warrior w("T");
    w.takeDamage(10);
    EXPECT_TRUE(w.isAlive());
}

TEST(CharacterTest, IsDeadAfterFatalDamage) {
    Warrior w("T");
    w.takeDamage(9999);
    EXPECT_FALSE(w.isAlive());
}

// ─── Player classes ──────────────────────────────────────────────────────────

TEST(WarriorTest, InitialStats) {
    Warrior w("Hero");
    EXPECT_EQ(w.getHp(),      WARRIOR_HP);
    EXPECT_EQ(w.getMaxHp(),   WARRIOR_HP);
    EXPECT_EQ(w.getAttack(),  WARRIOR_ATTACK);
    EXPECT_EQ(w.getDefense(), WARRIOR_DEFENSE);
    EXPECT_EQ(w.getLevel(),   1);
}

TEST(MageTest, InitialStats) {
    Mage m("Hero");
    EXPECT_EQ(m.getHp(),      MAGE_HP);
    EXPECT_EQ(m.getMaxHp(),   MAGE_HP);
    EXPECT_EQ(m.getAttack(),  MAGE_ATTACK);
    EXPECT_EQ(m.getDefense(), MAGE_DEFENSE);
    EXPECT_EQ(m.getLevel(),   1);
}

TEST(RogueTest, InitialStats) {
    Rogue r("Hero");
    EXPECT_EQ(r.getHp(),      ROGUE_HP);
    EXPECT_EQ(r.getMaxHp(),   ROGUE_HP);
    EXPECT_EQ(r.getAttack(),  ROGUE_ATTACK);
    EXPECT_EQ(r.getDefense(), ROGUE_DEFENSE);
    EXPECT_EQ(r.getLevel(),   1);
}

TEST(PlayerTest, StartsWithZeroXpAndGold) {
    Warrior w("Hero");
    EXPECT_EQ(w.getExperience(), 0);
    EXPECT_EQ(w.getGold(),       0u);
}

TEST(PlayerTest, AddExperienceAccumulates) {
    Warrior w("Hero");
    w.addExperience(50);
    w.addExperience(30);
    EXPECT_EQ(w.getExperience(), 80);
}

TEST(PlayerTest, AddGoldAccumulates) {
    Warrior w("Hero");
    w.addGold(10);
    w.addGold(5);
    EXPECT_EQ(w.getGold(), 15u);
}

TEST(PlayerTest, LevelUpOnXpThreshold) {
    Warrior w("Hero");
    w.addExperience(100);   // threshold for level 1 -> 2 is 100 * 1
    EXPECT_EQ(w.getLevel(), 2);
}

TEST(PlayerTest, LevelUpIncreasesMaxHp) {
    Warrior w("Hero");
    int hpBefore = w.getMaxHp();
    w.addExperience(100);
    EXPECT_GT(w.getMaxHp(), hpBefore);
}

// ─── Enemies ─────────────────────────────────────────────────────────────────

TEST(GoblinTest, InitialStats) {
    Goblin g("Fallen");
    EXPECT_EQ(g.getHp(),         GOBLIN_HP);
    EXPECT_EQ(g.getAttack(),     GOBLIN_ATTACK);
    EXPECT_EQ(g.getDefense(),    GOBLIN_DEFENSE);
    EXPECT_EQ(g.getExpReward(),  GOBLIN_EXP_REWARD);
    EXPECT_EQ(g.getGoldReward(), GOBLIN_GOLD_REWARD);
}

TEST(SkeletonTest, InitialStats) {
    Skeleton s("Bones");
    EXPECT_EQ(s.getHp(),         SKELETON_HP);
    EXPECT_EQ(s.getAttack(),     SKELETON_ATTACK);
    EXPECT_EQ(s.getDefense(),    SKELETON_DEFENSE);
    EXPECT_EQ(s.getExpReward(),  SKELETON_EXP_REWARD);
    EXPECT_EQ(s.getGoldReward(), SKELETON_GOLD_REWARD);
}

TEST(TrollTest, InitialStats) {
    Troll t("Mauler");
    EXPECT_EQ(t.getHp(),         TROLL_HP);
    EXPECT_EQ(t.getAttack(),     TROLL_ATTACK);
    EXPECT_EQ(t.getDefense(),    TROLL_DEFENSE);
    EXPECT_EQ(t.getExpReward(),  TROLL_EXP_REWARD);
    EXPECT_EQ(t.getGoldReward(), TROLL_GOLD_REWARD);
}

TEST(GoblinChiefTest, InitialStats) {
    GoblinChief gc("Shaman");
    EXPECT_EQ(gc.getHp(),         GOBLIN_CHIEF_HP);
    EXPECT_EQ(gc.getAttack(),     GOBLIN_CHIEF_ATTACK);
    EXPECT_EQ(gc.getDefense(),    GOBLIN_CHIEF_DEFENSE);
    EXPECT_EQ(gc.getExpReward(),  GOBLIN_CHIEF_EXP_REWARD);
    EXPECT_EQ(gc.getGoldReward(), GOBLIN_CHIEF_GOLD_REWARD);
}

TEST(StoneGolemTest, InitialStats) {
    StoneGolem sg("Golem");
    EXPECT_EQ(sg.getHp(),         STONE_GOLEM_HP);
    EXPECT_EQ(sg.getAttack(),     STONE_GOLEM_ATTACK);
    EXPECT_EQ(sg.getDefense(),    STONE_GOLEM_DEFENSE);
    EXPECT_EQ(sg.getExpReward(),  STONE_GOLEM_EXP_REWARD);
    EXPECT_EQ(sg.getGoldReward(), STONE_GOLEM_GOLD_REWARD);
}

TEST(DarkNecromancerTest, InitialStats) {
    DarkNecromancer dn("Malachar");
    EXPECT_EQ(dn.getHp(),         DARK_NECROMANCER_HP);
    EXPECT_EQ(dn.getAttack(),     DARK_NECROMANCER_ATTACK);
    EXPECT_EQ(dn.getDefense(),    DARK_NECROMANCER_DEFENSE);
    EXPECT_EQ(dn.getExpReward(),  DARK_NECROMANCER_EXP_REWARD);
    EXPECT_EQ(dn.getGoldReward(), DARK_NECROMANCER_GOLD_REWARD);
}

TEST(DarkNecromancerTest, SummonSkeletonIsAlive) {
    DarkNecromancer dn("Malachar");
    auto skeleton = dn.summonSkeleton();
    EXPECT_TRUE(skeleton->isAlive());
    EXPECT_EQ(skeleton->getHp(), SKELETON_HP);
}

// ─── Combat damage range ─────────────────────────────────────────────────────

TEST(CombatTest, WarriorDamageVsGoblinIsInRange) {
    Warrior attacker("T");
    Goblin target("T");
    int dmg = attacker.calculateDamage(target);
    EXPECT_GE(dmg, WARRIOR_ATTACK - GOBLIN_DEFENSE / 2 - 3);
    EXPECT_LE(dmg, WARRIOR_ATTACK - GOBLIN_DEFENSE / 2 + 3);
}

TEST(CombatTest, MageDamageVsGoblinIsInRange) {
    Mage attacker("T");
    Goblin target("T");
    int dmg = attacker.calculateDamage(target);
    EXPECT_GE(dmg, MAGE_ATTACK - GOBLIN_DEFENSE / 2 - 3);
    EXPECT_LE(dmg, MAGE_ATTACK - GOBLIN_DEFENSE / 2 + 3);
}

TEST(CombatTest, RogueDamageVsGoblinIsNeverNegative) {
    Rogue attacker("T");
    Goblin target("T");
    // run multiple times to account for crit randomness
    for (int i = 0; i < 100; i++) {
        EXPECT_GE(attacker.calculateDamage(target), 0);
    }
}

TEST(CombatTest, RogueCritDamageNeverExceedsDoubleMax) {
    Rogue attacker("T");
    Goblin target("T");
    int maxNormal = ROGUE_ATTACK - GOBLIN_DEFENSE / 2 + 3;
    for (int i = 0; i < 100; i++) {
        EXPECT_LE(attacker.calculateDamage(target), maxNormal * 2);
    }
}

// ─── Level up stat increases per class ───────────────────────────────────────

TEST(WarriorTest, LevelUpStats) {
    Warrior w("T");
    int atkBefore = w.getAttack();
    int defBefore = w.getDefense();
    w.addExperience(100);
    EXPECT_EQ(w.getAttack(),  atkBefore + 2);
    EXPECT_EQ(w.getDefense(), defBefore + 2);
    EXPECT_EQ(w.getMaxHp(),   WARRIOR_HP + 10);
}

TEST(MageTest, LevelUpStats) {
    Mage m("T");
    int atkBefore = m.getAttack();
    int defBefore = m.getDefense();
    m.addExperience(100);
    EXPECT_EQ(m.getAttack(),  atkBefore + 4);
    EXPECT_EQ(m.getDefense(), defBefore + 1);
    EXPECT_EQ(m.getMaxHp(),   MAGE_HP + 7);
}

TEST(RogueTest, LevelUpStats) {
    Rogue r("T");
    int atkBefore = r.getAttack();
    int defBefore = r.getDefense();
    r.addExperience(100);
    EXPECT_EQ(r.getAttack(),  atkBefore + 3);
    EXPECT_EQ(r.getDefense(), defBefore + 1);
    EXPECT_EQ(r.getMaxHp(),   ROGUE_HP + 8);
}

TEST(PlayerTest, LevelUpHealsToFullHp) {
    Warrior w("T");
    w.takeDamage(50);
    w.addExperience(100);
    EXPECT_EQ(w.getHp(), w.getMaxHp());
}
