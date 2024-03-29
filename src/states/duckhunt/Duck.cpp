#include "../../../include/states/duckhunt/Duck.h"

const int DUCK_SCALE        =  2;  //How much the duck's sprites are scaled
const float ANGLE_RANGE     = 10;  //The range of angles the ducks can fly up
const VectorFloat GRAVITY   = VectorFloat(0, .5);
const float START_HEIGHT    = SCREEN.GetHeight()*.75;  //What row the ducks start
const float PROB_OF_QUACK   = .02;  //The probability of a duck quacking in any given frame

float Duck::buffer[4];
float Duck::probChangeVel = .0085;
float Duck::speed = 3;
std::unordered_map<DuckFrame, RectInt> Duck::frames;
std::unordered_map<DuckSound,   Sound> Duck::sounds;

Duck::Duck()
{
    frames[DuckFrame::UP_1   ] = RectInt(  0, 197,  29, 229);
    frames[DuckFrame::UP_2   ] = RectInt( 35, 197,  64, 229);
    frames[DuckFrame::UP_3   ] = RectInt( 67, 197,  96, 229);
    frames[DuckFrame::NORM_1 ] = RectInt( 98, 198, 132, 229);
    frames[DuckFrame::NORM_2 ] = RectInt(136, 199, 170, 230);
    frames[DuckFrame::NORM_3 ] = RectInt(173, 198, 206, 229);
    frames[DuckFrame::SHOT   ] = RectInt(212, 202, 243, 231);
    frames[DuckFrame::FALLING] = RectInt(245, 201, 263, 232);

    sounds[DuckSound::FLAP      ].Load("./sfx/duckhunt/flap.wav"     );
    sounds[DuckSound::QUACK     ].Load("./sfx/duckhunt/quack.wav"    );
    sounds[DuckSound::FALL      ].Load("./sfx/duckhunt/fall.wav"     );
    sounds[DuckSound::HIT_GROUND].Load("./sfx/duckhunt/hitground.wav");

    initSprite(sprite, sprites, frames[DuckFrame::NORM_1], DUCK_SCALE);
    setSpriteBuffer(sprite, buffer);
    sprite.SetPosition(Random::Random(buffer[LEFT], buffer[RIGHT]), START_HEIGHT);
    updateShotBox();

    velocity = VectorFloat(0, 0);
    state    = DuckState::IDLE;
}

Duck::~Duck()
{
    //dtor
}

void Duck::act()
{
    switch (state) {
        case DuckState::IDLE         : break;
        case DuckState::FLYING_IN    : flyIn();       break;
        case DuckState::FLYING_AROUND: flyAround();   break;
        case DuckState::SHOT         : die();         break;
        case DuckState::FALLING      : fall();        break;
        case DuckState::FLYING_OUT   : flyOut();      break;
        default: throw std::invalid_argument("Duck state #" + boost::lexical_cast<std::string, int>(int(state)) + " not recognized!");
    }

    updateShotBox();
    prevstate = state;
}

void Duck::flyIn()
{
    if (prevstate != DuckState::FLYING_IN) {
        sprite.SetPosition(Random::Random(buffer[LEFT], buffer[RIGHT]), START_HEIGHT);
        updateShotBox();
        float angle = Random::Random(-ANGLE_RANGE, ANGLE_RANGE);
        velocity = VectorFloat(speed*cos(angle), -fabs(speed*sin(angle)));
    }

    if (actiontimer.GetElapsedTime() < 1 && sprite.GetPosition().y > buffer[UP]) {
        sprite.Move(velocity);
        detectBoundaries();
    } else {
        setState(DuckState::FLYING_AROUND);
        setRandomDirection();
    }
}

void Duck::flyAround()
{
    if (Random::Random(0.0f, 1.0f) <= probChangeVel) setRandomDirection();

    if (Random::Random(0.0f, 1.0f) <= PROB_OF_QUACK && sounds[DuckSound::QUACK].getStatus() == sf::Sound::Stopped)
        sounds[DuckSound::QUACK].Play();

    detectBoundaries();
    sprite.Move(velocity);
}

void Duck::flyOut()
{
    if (prevstate == DuckState::FLYING_AROUND) {
        float angle = Random::Random(-ANGLE_RANGE, ANGLE_RANGE);
        velocity = VectorFloat(speed*cos(angle), -fabs(speed*sin(angle)));
    }
    sprite.Move(velocity);
}

void Duck::die()
{
    sprite.FlipX(false);
    sprite.SetSubRect(frames[DuckFrame::SHOT]);
    velocity = VectorFloat(0, 0);  //Stop moving

    if (actiontimer.GetElapsedTime() >= 1) setState(DuckState::FALLING);
}

void Duck::fall()
{
    if (sprite.GetSubRect().GetHeight() != frames[DuckFrame::FALLING].GetHeight()) {  //If we just started falling...
        sprite.SetSubRect(frames[DuckFrame::FALLING]);
        sounds[DuckSound::FALL].Play();
    }

    sprite.Move(velocity += GRAVITY);  //Fall down

    if (sprite.GetPosition().y >= SCREEN.GetHeight()*.7) {
        sprite.SetY(SCREEN.GetHeight()*2);  //Move off screen to satisfy a conditional in DuckHuntGameState
        sounds[DuckSound::FALL      ].Stop();
        sounds[DuckSound::HIT_GROUND].Play();
        setState(DuckState::IDLE);
    }
}

void Duck::initSki()
{
    frames[DuckFrame::UP_1   ] = RectInt(  0, 386,  27, 422);
    frames[DuckFrame::UP_2   ] = RectInt( 35, 386,  66, 422);
    frames[DuckFrame::UP_3   ] = RectInt( 68, 386,  93, 424);
    frames[DuckFrame::NORM_1 ] = RectInt( 98, 392, 130, 421);
    frames[DuckFrame::NORM_2 ] = RectInt(136, 395, 168, 422);
    frames[DuckFrame::NORM_3 ] = RectInt(173, 393, 205, 424);
    frames[DuckFrame::SHOT   ] = RectInt(212, 394, 243, 425);
    frames[DuckFrame::FALLING] = RectInt(245, 395, 263, 435);
}

void Duck::updateShotBox()
{
    shotbox.Left   = sprite.TransformToGlobal(VectorFloat(0, 0)).x;
    shotbox.Right  = sprite.GetPosition().x + sprite.GetSize().x/2;
    shotbox.Top    = sprite.TransformToGlobal(VectorFloat(0, 0)).y;
    shotbox.Bottom = sprite.GetPosition().y + sprite.GetSize().y/2;
}

void Duck::updateAnimation()
{
    sprite.FlipX(velocity.x < 0);  //If the duck is flying left, flip its sprite

    //If the duck is flying...
    if (state == DuckState::FLYING_AROUND || state == DuckState::FLYING_IN || state == DuckState::FLYING_OUT) {
        if (state == DuckState::FLYING_AROUND) {
            //This expression uses a sine wave to animate the duck
            sprite.SetSubRect(frames[DuckFrame(lround(sin(25*animationtimer.GetElapsedTime()-.5)+1))]);
        } else if (state == DuckState::FLYING_IN || state == DuckState::FLYING_OUT) {
            sprite.SetSubRect(frames[DuckFrame(lround(sin(25*animationtimer.GetElapsedTime()-.5)+1)+3)]);
        }

        if (sounds[DuckSound::FLAP].getStatus() == sf::Sound::Stopped && velocity != VectorFloat(0, 0) &&
            SCREEN.Contains(sprite.GetPosition().x, sprite.GetPosition().y))
                sounds[DuckSound::FLAP].Play();
    }
}

void Duck::detectBoundaries()
{
    //If we're outside the screen's x range...
    if (!IN_RANGE(sprite.GetPosition().x, buffer[LEFT], buffer[RIGHT])) {
        sprite.SetX(buffer[sprite.GetPosition().x < buffer[LEFT] ? LEFT : RIGHT]);
        velocity.x *= -1;
    }

    //If we're outside the screen's y range...
    if (state == DuckState::FLYING_AROUND) {  //The ducks ignore up and down boundaries if flying in or out
        float temp = SCREEN.GetHeight()*.6;
        if (!IN_RANGE(sprite.GetPosition().y, buffer[UP], temp)) {
            sprite.SetY(sprite.GetPosition().y < temp ? buffer[UP] : temp);
            velocity.y *= -1;
        }
    }
}

void Duck::setRandomDirection()
{
    float angle = Random::Random(0.0f, 360.0f);
    velocity = VectorFloat(speed * sin(angle), speed * cos(angle));
}
