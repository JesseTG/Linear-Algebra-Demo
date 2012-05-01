#ifndef DUCK_H
#define DUCK_H

#include "../../Declarations.h"

#include <unordered_map>

enum class DuckFrame : char {
    UP_1, UP_2, UP_3,
    DOWN_1, DOWN_2, DOWN_3,
    SHOT, FALLING
};

namespace std {
    template<> struct hash<DuckFrame> {
        std::size_t operator()(const DuckFrame df) const
        { return hash<char>()(static_cast<char>(df)); }
    };
}

class Duck
{
    public:
        Duck();
        virtual ~Duck();

        void fly();
        void flyAway();
        void die();

        void updateAnimation();

        RectFloat getShotBox() const { return shotbox; }

        Sprite& getSprite() { return sprite; }

    protected:
        //The frames that the ducks can use
        static std::unordered_map<DuckFrame, RectInt> frames;

        //Updates the position of the box we can shoot at
        void updateShotBox();

        //Sets the direction of the duck to be random
        void setRandomDirection();

        //Times the duck's animation
        Timer animationtimer;

        //The current frame this duck has
        uint8_t frame;

        //SPEED, not velocity
        static float speed;

        RectFloat shotbox;

        float buffer[4];
        Sprite sprite;
        bool is_ski;
        bool is_shot;
        bool is_hit_ground;

        //The odds of the duck changing velocity (thus direction) each frame
        float probChangeVel;

        //How fast this duck is going on both dimensions
        VectorFloat velocity;

};

#endif // DUCK_H
