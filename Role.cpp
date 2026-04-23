
#include "Role.hpp"

namespace final {
    int Base::aliveNumber = 0;

    void Fighter::launch_attack(Base *target) {
        if (!target || !target->isAlive()) return;
        
        // Calculate damage multiplier
        double multiplier = 1.0;
        const Caster* casterTarget = dynamic_cast<const Caster*>(target);
        if (casterTarget) {
            multiplier = 2.0;  // Fighter deals double damage to Caster
        }
        
        int damage = getAttack() * multiplier;
        
        if (target->isDefensive()) {
            // Target is defending
            int actualDamage = damage - target->getAttack();
            if (actualDamage > 0) {
                target->setHealth(target->getHealth() - actualDamage);
            }
            
            // Attacker takes counter damage (unless attacker is Caster)
            if (!isCaster()) {
                int counterDamage = target->getAttack();
                setHealth(getHealth() - counterDamage);
            }
        } else {
            // Target is not defending
            target->setHealth(target->getHealth() - damage);
        }
        
        // Check if target died
        if (!target->isAlive()) {
            std::cout << target->getRoleName() << " " << target->getName() << " is killed\n";
        }
        
        // Check if attacker died (output target death first if both died)
        if (!isAlive()) {
            std::cout << getRoleName() << " " << getName() << " is killed\n";
        }
    }

    void Protector::launch_attack(Base *target) {
        if (!target || !target->isAlive()) return;
        
        // Calculate damage multiplier
        double multiplier = 1.0;
        const Fighter* fighterTarget = dynamic_cast<const Fighter*>(target);
        if (fighterTarget) {
            multiplier = 2.0;  // Protector deals double damage to Fighter
        }
        
        int damage = getAttack() * multiplier;
        
        if (target->isDefensive()) {
            // Target is defending
            int actualDamage = damage - target->getAttack();
            if (actualDamage > 0) {
                target->setHealth(target->getHealth() - actualDamage);
            }
            
            // Attacker takes counter damage (unless attacker is Caster)
            if (!isCaster()) {
                int counterDamage = target->getAttack();
                setHealth(getHealth() - counterDamage);
            }
        } else {
            // Target is not defending
            target->setHealth(target->getHealth() - damage);
        }
        
        // Check if target died
        if (!target->isAlive()) {
            std::cout << target->getRoleName() << " " << target->getName() << " is killed\n";
        }
        
        // Check if attacker died (output target death first if both died)
        if (!isAlive()) {
            std::cout << getRoleName() << " " << getName() << " is killed\n";
        }
    }

    void Caster::launch_attack(Base *target) {
        if (!target || !target->isAlive()) return;
        
        // Calculate damage multiplier
        double multiplier = 1.0;
        const Protector* protectorTarget = dynamic_cast<const Protector*>(target);
        if (protectorTarget) {
            multiplier = 2.0;  // Caster deals double damage to Protector
        }
        
        int damage = getAttack() * multiplier;
        
        if (target->isDefensive()) {
            // Target is defending
            int actualDamage = damage - target->getAttack();
            if (actualDamage > 0) {
                target->setHealth(target->getHealth() - actualDamage);
            }
            
            // Attacker takes counter damage (unless attacker is Caster)
            // Caster doesn't take counter damage
        } else {
            // Target is not defending
            target->setHealth(target->getHealth() - damage);
        }
        
        // Check if target died
        if (!target->isAlive()) {
            std::cout << target->getRoleName() << " " << target->getName() << " is killed\n";
        }
        
        // Check if attacker died (output target death first if both died)
        if (!isAlive()) {
            std::cout << getRoleName() << " " << getName() << " is killed\n";
        }
    }
}
