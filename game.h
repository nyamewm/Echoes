#define WWW sf::Keyboard::isKeyPressed(sf::Keyboard::W)
#define AAA sf::Keyboard::isKeyPressed(sf::Keyboard::A)
#define SSS sf::Keyboard::isKeyPressed(sf::Keyboard::S)
#define DDD sf::Keyboard::isKeyPressed(sf::Keyboard::D)
#define SPACE sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
#include <SFML/Graphics.hpp>
#include<thread>



struct AABB
    /*Ограничивающий прямоугольник, выровненный по координатным осям (Axis Aligned Bounding Box, AABB)
     * — это прямоугольник, четыре оси которого выровнены относительно системы координат, в которой он
     * находится. Это значит, что прямоугольник не может вращаться и всегда находится под углом в 90
     * градусов (обычно выровнен относительно экрана). Обычно его называют «ограничивающим прямоугольником»,
     * потому что AABB используются для ограничения других, более сложных форм.*/
{
    sf::Vector2f min;
    sf::Vector2f max;
};

bool AABBvsAABB( AABB a, AABB b )
{
    // Выходим без пересечения, потому что найдена разделяющая ось
    if(a.max.x < b.min.x or a.min.x > b.max.x) return false;
    if(a.max.y < b.min.y or a.min.y > b.max.y) return false;

    // Разделяющая ось не найдена, поэтому существует по крайней мере одна пересекающая ось
    return true;
}

struct Circle
{
    float radius;
    sf::Vector2f position;
};



bool CircleVsCircle(Circle a, Circle b)
{
    float r = a.radius + b.radius;
    r *= r;
    return r < ((a.position.x + b.position.x)*(a.position.x + b.position.x) + (a.position.y + b.position.y)*(a.position.y + b.position.y));
}


class Entity : public sf::Drawable {
public:
    sf::RenderWindow* window;
    sf::RectangleShape rectangle;
    sf::Texture texture;
    const sf::Texture *pTexture = &texture;
    float CurrentFrame = 0;
    int level;
    sf::Vector2f position;
    int angle;
    void update(float) {};
    //virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class Static: public Entity {
public:
    Static(sf::RenderWindow* window);
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class Aid: public Static {
public:
    sf::SoundBuffer aidbuffer;
    sf::Sound aid;
    float hpregen;
    Aid(sf::RenderWindow* window);
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class Battery: public Static {
public:
    sf::SoundBuffer batterybuffer;
    sf::Sound battery;
    float energyregen;
    Battery(sf::RenderWindow* window);
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class Turret: public Static {
public:
    sf::Texture texture;
    const sf::Texture *pTexture = &texture;
    sf::SoundBuffer shootbuffer;
    sf::Sound shoot;
    Turret(sf::RenderWindow *window);
    float damage;
    float lastshot;
    float vrot;
    float reload;
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const{
        target.draw(rectangle, states);
    };
};

class Dynamic: public Entity {
public:
    sf::Vector2f pos;
    sf::Vector2f v;
    bool alive;
    float health;
    float healthmax;
    float energy;
    float energymax;
    //float v;
    float vmax, vmin, vrot;
    float acceleration;
    float r;
    sf::Texture textureExplosion;
    const sf::Texture *pTextureExplosion = &textureExplosion;
    sf::SoundBuffer explosionbuffer;
    sf::Sound explosion;
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class Bullet: public Dynamic {
public:
    sf::Texture texture;
    const sf::Texture *pTexture = &texture;
    float damage;
    float lifetime;
    float birthtime;
    Bullet(sf::RenderWindow* window, Turret turret, float timer);
    void update(float time, float timer);
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class Player: public Dynamic {
    sf::Texture texture;
    const sf::Texture *pTexture = &texture;
public:
    bool moving = false;
    Player(sf::RenderWindow* window);
    float headlightstimer;
    bool headlights;
    int level;
    /*void draw()
    {
        window->draw(rectangle);
    }*/
    void update(float time, float timer);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};



Static::Static(sf::RenderWindow *window) {
    rectangle.setSize(sf::Vector2f(200,200));
    rectangle.setOrigin(0,0);
    rectangle.setPosition(300,300);
    rectangle.setRotation(0);
    rectangle.setFillColor(sf::Color(100,100,100));
    rectangle.setOutlineColor(sf::Color(50,50,50));
    rectangle.setOutlineThickness(-15);
};

Aid::Aid(sf::RenderWindow *window) : Static(window) {
    texture.loadFromFile("images/repair_kit.png");
    rectangle.setTexture(pTexture);
    aidbuffer.loadFromFile("sounds/aid.ogg");
    aid.setBuffer(aidbuffer);
    hpregen = 50;
    rectangle.setSize(sf::Vector2f(30, 30));
    rectangle.setOrigin(15, 15);
    rectangle.setPosition(-200, -200);
    rectangle.setRotation(0);
    rectangle.setFillColor(sf::Color(255, 255, 255, 255));
    rectangle.setOutlineColor(sf::Color(0, 0, 0, 0));
};

Battery::Battery(sf::RenderWindow *window) : Static(window) {
    texture.loadFromFile("images/battery.png");
    rectangle.setTexture(pTexture);
    batterybuffer.loadFromFile("sounds/battery.wav");
    battery.setBuffer(batterybuffer);
    energyregen = 50;
    rectangle.setSize(sf::Vector2f(30, 30));
    rectangle.setOrigin(15, 15);
    rectangle.setPosition(-200, 0);
    rectangle.setRotation(0);
    rectangle.setFillColor(sf::Color(255, 255, 255, 255));
    rectangle.setOutlineColor(sf::Color(0, 0, 0, 0));
};

Turret::Turret(sf::RenderWindow *window) : Static(window) {
    vrot = 0.00015;
    texture.loadFromFile("images/turret.png");
    rectangle.setTexture(pTexture);
    shootbuffer.loadFromFile("sounds/gunshot.wav");
    shoot.setBuffer(shootbuffer);
    damage = 40;
    reload = 1;
    rectangle.setSize(sf::Vector2f(50,50));
    rectangle.setOrigin(25,25);
    rectangle.setPosition(200,-200);
    rectangle.setRotation(0);
    rectangle.setFillColor(sf::Color(255,255,255,255));
    rectangle.setOutlineColor(sf::Color(0,0,0,0));
};

Bullet::Bullet(sf::RenderWindow *window, Turret turret, float timer) {
    texture.loadFromFile("images/bullet.png");
    rectangle.setTexture(pTexture);
    r = 5;
    v.x = 0.0005;
    damage = turret.damage;
    birthtime = timer;
    lifetime = 3;
    rectangle.setSize(sf::Vector2f(20, 20));
    rectangle.setOrigin(10,10);
    rectangle.setPosition(turret.rectangle.getPosition());
    pos = rectangle.getPosition();
    rectangle.setRotation(turret.rectangle.getRotation()+90);
    v.y = rectangle.getRotation();
    rectangle.move(turret.rectangle.getSize().x*sin(rectangle.getRotation()*0.0175)/2 ,-turret.rectangle.getSize().x*cos(rectangle.getRotation()*0.0175)/2);
    rectangle.setFillColor(sf::Color(255,255,255,255));
    rectangle.setOutlineColor(sf::Color(0,0,0,0));
    rectangle.setOutlineThickness(0);
};

void Static::draw(sf::RenderTarget &target, sf::RenderStates states) const  {
    target.draw(rectangle, states);

};

void Dynamic::draw(sf::RenderTarget &target, sf::RenderStates states) const  {
    target.draw(rectangle, states);

};

Player::Player(sf::RenderWindow* window)
{
    headlights = false;
    alive = true;
    headlightstimer = 0;
    texture.loadFromFile("images/a.png");
    textureExplosion.loadFromFile("images/explosion.png");
    explosionbuffer.loadFromFile("sounds/explosion.ogg");
    explosion.setBuffer(explosionbuffer);
    acceleration = 0.0000000015;
    r = 25;
    level = 0;
    v.x = 0;
    vmax = 0.0009;
    vmin = -0.00045;
    vrot = 0.0003;
    rectangle.setSize(sf::Vector2f(50,50));
    rectangle.setOrigin(25,25);
    rectangle.setPosition(100, 100);
    rectangle.setRotation(0);
    rectangle.setTexture(pTexture);
};

void Bullet::update(float time, float timer) {
    rectangle.move(v.x*time*sin(v.y*0.0175) ,-v.x*time*cos(v.y*0.0175));
    pos.x += v.x*time*sin(v.y*0.0175);
    pos.y += -v.x*time*cos(v.y*0.0175);
}

void Player::update(float time, float timer) {
    if(alive)
    {
        if(moving)
            rectangle.move(v.x*time*sin(v.y*0.0175) ,-v.x*time*cos(v.y*0.0175));
        if(energy > 0)
        {
            moving = true;
            if(WWW&DDD)
            {
                if(v.x < 0)
                    v.x = v.x+3*acceleration*time;
                else if(v.x <= (0.5*vmax)-acceleration)
                    v.x = v.x+acceleration*time;
                else
                    v.x = v.x-acceleration*time;
                rectangle.rotate(vrot*time/2);
            }
            else if(WWW&AAA)
            {
                if(v.x < 0)
                    v.x = v.x+3*acceleration*time;
                else if(v.x <= (0.5*vmax)-acceleration)
                    v.x = v.x+acceleration*time;
                else
                    v.x = v.x-acceleration*time;
                rectangle.rotate(-vrot*time/2);
            }
            else if(SSS&DDD)
            {
                if(v.x >= 3*acceleration)
                    v.x = v.x-3*acceleration*time;
                else if(v.x > 0)
                    v.x = 0;
                else if(v.x >= vmin+acceleration)
                    v.x = v.x-acceleration*time;
                else
                    v.x = vmin;
                rectangle.rotate(vrot*time/2);
            }
            else if(SSS&AAA)
            {
                if(v.x >= 3*acceleration)
                    v.x = v.x-3*acceleration*time;
                else if(v.x > 0)
                    v.x = 0;
                else if(v.x >= vmin+acceleration)
                    v.x = v.x-acceleration*time;
                else
                    v.x = vmin;
                rectangle.rotate(-vrot*time/2);
            }
            else if(WWW)
            {
                if(v.x < 0)
                    v.x = v.x+3*acceleration*time;
                else if(v.x <= vmax-acceleration)
                    v.x = v.x+acceleration*time;
                else
                    v.x = vmax;
            }
            else 	if(SSS)
            {
                if(v.x >= 3*acceleration)
                    v.x = v.x-3*acceleration*time;
                else if(v.x > 0)
                    v.x = 0;
                else if(v.x >= vmin+acceleration)
                    v.x = v.x-acceleration*time;
                else
                    v.x = vmin;
            }
            else 	if(DDD) {
                if(v.x >= acceleration)
                    v.x = v.x-acceleration*time;
                else if(v.x > 0)
                    v.x = 0;
                else if(v.x >= -acceleration)
                    v.x = 0;
                else
                    v.x = v.x+acceleration*time;
                rectangle.rotate(vrot*time);
            }
            else 	if(AAA) {
                if(v.x >= acceleration)
                    v.x = v.x-acceleration*time;
                else if(v.x > 0)
                    v.x = 0;
                else if(v.x >= -acceleration)
                    v.x = 0;
                else
                    v.x = v.x+acceleration*time;
                rectangle.rotate(-vrot*time);
            }
            else 	if(SPACE && (timer-headlightstimer)>0.5 && energy > 10) {
                headlightstimer = timer;
                if (headlights)
                    headlights = false;
                else
                    headlights = true;
            }
            else
            {
                if(v.x >= 0.05*vmax)
                    v.x = v.x-acceleration*time;
                else if(v.x > 0) {
                    moving = false;
                    v.x = 0;
                }
                else if(v.x >= -0.05*vmax)
                {
                    moving = false;
                    v.x = 0;
                }
                else
                    v.x = v.x+acceleration*time;
            }
        }
        else {
            if (v.x >= acceleration)
                v.x = v.x - acceleration * time;
            else if (v.x > 0)
                v.x = 0;
            else if (v.x >= -acceleration)
                v.x = 0;
            else
                v.x = v.x + acceleration * time;
        }
        v.y = rectangle.getRotation();
        pos = rectangle.getPosition();
        pos.x += v.x*time*sin(v.y*0.0175);
        pos.y += -v.x*time*cos(v.y*0.0175);
        energy -= 3*time/1000000;
        if(headlights)
            energy -= 3*time/1000000;
        if(energy < 10) {
            headlightstimer = timer;
            headlights = false;
        }
        if(energy + time*((cos(timer*6.28/60)+1)/500000) < energymax)
            energy += time*((cos(timer*6.28/60)+1)/500000);
        else
            energy = energymax;
        if(energy < 0) {
            energy = 0;
        }
    }
    else if(CurrentFrame <= 48){
        CurrentFrame += 0.00004 * time;
        rectangle.setTextureRect(sf::IntRect((int(CurrentFrame)%8) * 240, int(CurrentFrame / 8) * 240, 240, 240));
    }
};

void Battery::draw(sf::RenderTarget &target, sf::RenderStates states) const  {
    target.draw(rectangle, states);
};

void Aid::draw(sf::RenderTarget &target, sf::RenderStates states) const  {
    target.draw(rectangle, states);
};

void Bullet::draw(sf::RenderTarget &target, sf::RenderStates states) const  {
    target.draw(rectangle, states);
};

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const  {
    target.draw(rectangle, states);
};