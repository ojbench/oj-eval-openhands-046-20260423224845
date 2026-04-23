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
            // Fighter deals double damage to Caster
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

}
#endif //ROLE_HPP
