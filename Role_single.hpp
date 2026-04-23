
#include<string>
#include<iostream>
#ifndef ROLE_HPP
#define ROLE_HPP
namespace final{
    
    class Fighter;
    class Protector;
    class Caster;

    //uncompleted, you should add code into this class
    class Base{
        friend class Fighter;
        friend class Protector;
        friend class Caster;
    private:
        //WARNING: NO OTHER MEMBER VARIABLE IS ALLOWED TO BE ADDED HERE.
        std::string name;
        int health,attack;
        bool alive,defensive;
        //you only need to define aliveNumber here.
        static int aliveNumber;
    public:
        //WARNING: NO OTHER PUBLIC FUNCTION IS ALLOWED TO BE ADDED.
        //WARNING: THIS CLASS(Base) CAN NOT BE INSTANTIATED（实例化）.
        //WARNING: THE FUNCTION PROVIDED NEED NO MODIFICATION
        //the function you need to implement or define is as follows.
        //(1) getAliveNumber
        //(2) Constructor
        //(3) launch_attack
        //(4) defend
        bool isAlive(){
            return alive;
        }

        bool isDefensive(){
            return defensive;
        }
        
        static int getAliveNumber() {
            return aliveNumber;
        }
        
        virtual void defend(bool flag) = 0;
        virtual void launch_attack(Base* target) = 0;
        
    public:
        virtual ~Base() {
            if (alive) {
                aliveNumber--;
            }
        }
        
    protected:
        Base(const std::string& name, const int health, const int attack) 
            : name(name), health(health), attack(attack), alive(true), defensive(false) {
            aliveNumber++;
        }
        
        void setHealth(int newHealth) {
            health = newHealth;
            if (health <= 0 && alive) {
                alive = false;
                aliveNumber--;
            }
        }
        
        void setAttack(int newAttack) {
            attack = newAttack;
        }
        
        void setDefensive(bool flag) {
            defensive = flag;
        }
        
        int getHealth() const {
            return health;
        }
        
        int getAttack() const {
            return attack;
        }
        
        const std::string& getName() const {
            return name;
        }
        
        virtual const char* getRoleName() const = 0;
        
        virtual double getDamageMultiplier(const Base* target) const = 0;
        virtual bool isCaster() const = 0;
    };

    class Fighter:public Base{
    public:
        //WARNING: NO OTHER PUBLIC FUNCTION IS ALLOWED TO BE ADDED.
        //WARNING: THE FUNCTION PROVIDED NEED NO MODIFICATION
        Fighter (const std::string& name, const int health,const int attack):Base(name,health,attack){}

        void launch_attack(Base* target);

        void defend(bool flag){
            if (flag) {
                setDefensive(true);
                setHealth(getHealth() + 3);
                setAttack(getAttack() + 2);
            } else {
                setDefensive(false);
            }
        }
        
    protected:
        const char* getRoleName() const override {
            return "Fighter";
        }
        
        double getDamageMultiplier(const Base* target) const override {
            return 2.0;  // Simplified - will check target type in implementation
        }
        
        bool isCaster() const override {
            return false;
        }
    };

    class Protector:public Base{
    public:
        //WARNING: NO OTHER PUBLIC FUNCTION IS ALLOWED TO BE ADDED.
        //WARNING: THE FUNCTION PROVIDED NEED NO MODIFICATION
        Protector (const std::string& name, const int health,const int attack):Base(name,health,attack){}

        void launch_attack(Base* target);

        void defend(bool flag){
            if (flag) {
                setDefensive(true);
                setHealth(getHealth() + 7);
                setAttack(getAttack() + 1);
            } else {
                setDefensive(false);
            }
        }
        
    protected:
        const char* getRoleName() const override {
            return "Protector";
        }
        
        double getDamageMultiplier(const Base* target) const override {
            return 1.0;  // Simplified - will check target type in implementation
        }
        
        bool isCaster() const override {
            return false;
        }
    };

    class Caster:public Base{
    public:
        //WARNING: NO OTHER PUBLIC FUNCTION IS ALLOWED TO BE ADDED.
        //WARNING: THE FUNCTION PROVIDED NEED NO MODIFICATION
        Caster (const std::string& name, const int health,const int attack):Base(name,health,attack){}

        void launch_attack(Base* target);

        void defend(bool flag){
            if (flag) {
                setDefensive(true);
                setHealth(getHealth() + 5);
            } else {
                setDefensive(false);
            }
        }
        
    protected:
        const char* getRoleName() const override {
            return "Caster";
        }
        
        double getDamageMultiplier(const Base* target) const override {
            return 1.0;  // Simplified - will check target type in implementation
        }
        
        bool isCaster() const override {
            return true;
        }
    };

    // Static member definition
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
#endif //ROLE_HPP

