#include "combat.h"
#include "enemies/dark_necromancer.h"

AttackResult executeAttack(Player& player, Enemy& enemy, unsigned short& turn) {
    AttackResult result;

    result.damageDealt = player.calculateDamage(enemy);
    enemy.takeDamage(result.damageDealt);

    if (enemy.isAlive()) {
        result.damageTaken = enemy.calculateDamage(player);
        player.takeDamage(result.damageTaken);

        if (++turn % 3 == 0) {
            auto* necro = dynamic_cast<DarkNecromancer*>(&enemy);
            if (necro) {
                result.summonedEnemy = necro->summonSkeleton();
            }
        }
    }

    return result;
}
