#define WWW sf::Keyboard::isKeyPressed(sf::Keyboard::W)
#define AAA sf::Keyboard::isKeyPressed(sf::Keyboard::A)
#define SSS sf::Keyboard::isKeyPressed(sf::Keyboard::S)
#define DDD sf::Keyboard::isKeyPressed(sf::Keyboard::D)
#define SPACE sf::Keyboard::isKeyPressed(sf::Keyboard::Space)

bool CollisionCircleRectangle(float x1, float y1, float r, float x2, float y2, float l, float w, double v)
{
    float b = -2*y1;
    float c = pow(y1, 2) + pow((x2-x1), 2) - pow(r, 2);
    double D = pow(b, 2) - 4*c;
            if(D >= 0) {
                float y3 = (-b + sqrt(D)) / 2;
                float y4 = (-b - sqrt(D)) / 2;
                if(((y3 > y2)&&(y3 < y2 + w))||((y4 > y2)&&(y4 < y2 + w)))
                    return true;
            }
    b = -2*y1;
    c = pow(y1, 2) + pow((x2+l-x1), 2) - pow(r, 2);
    D = pow(b, 2) - 4*c;
    if(D >= 0) {
        float y3 = (-b + sqrt(D)) / 2;
        float y4 = (-b - sqrt(D)) / 2;
        if(((y3 > y2)&&(y3 < y2 + w))||((y4 > y2)&&(y4 < y2 + w)))
            return true;
    }
    b = -2*x1;
    c = pow(x1, 2) + pow((y2-y1), 2) - pow(r, 2);
    D = pow(b, 2) - 4*c;
    if(D >= 0) {
        float x3 = (-b + sqrt(D)) / 2;
        float x4 = (-b - sqrt(D)) / 2;
        if(((x3 > y2)&&(x3 < x2 + l))||((x4 > x2)&&(x4 < x2 + l)))
            return true;
    }
    b = -2*x1;
    c = pow(x1, 2) + pow((y2+w-y1), 2) - pow(r, 2);
    D = pow(b, 2) - 4*c;
    if(D >= 0) {
        float x3 = (-b + sqrt(D)) / 2;
        float x4 = (-b - sqrt(D)) / 2;
        if(((x3 > y2)&&(x3 < x2 + l))||((x4 > x2)&&(x4 < x2 + l)))
            return true;
    }
    return false;
}
class Entity : public sf::Drawable {
protected:
    sf::RenderWindow* window;
    sf::RectangleShape rectangle;
    float x, y;
    int angle;
public:
    void update(float) {};
    //virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class Static: public Entity {
public:
    Static(sf::RenderWindow* window);
    /*void draw()
    {
        this->window->draw(this->rectangle);
    }*/
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class Dynamic: public Entity {
public:
    double v = 0;
    float acceleration = 0;
    float r = 0;
};

class Player: public Dynamic {
public:
    int level;
    sf::Vector2f pos;
    float vmax, vmin, vrot;
    Player(sf::RenderWindow* window);
    /*void draw()
    {
        this->window->draw(this->rectangle);
    }*/
    void update(float time);
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

Static::Static(sf::RenderWindow *window) {
    this->x = 500;
    this->y = 500;
    this->window = window;
    this->rectangle.setSize(sf::Vector2f(200,200));
    this->rectangle.setOrigin(25,25);
    this->rectangle.setPosition(this->x, this->y);
    this->rectangle.setRotation(0);
};
void Static::draw(sf::RenderTarget &target, sf::RenderStates states) const  {
    target.draw(rectangle, states);
};
Player::Player(sf::RenderWindow *window)
{
    this->acceleration = 0.001;
    this->r = 25;
    this->level = 0;
    this->x = 100;
    this->y = 100;
    this->v = 0;
    this->vmax = 0.3;
    this->vmin = -0.15;
    this->vrot = 0.15;
    this->window = window;
    this->rectangle.setSize(sf::Vector2f(50,50));
    this->rectangle.setOrigin(25,25);
    this->rectangle.setPosition(this->x, this->y);
    this->rectangle.setRotation(0);
};
void Player::update(float time) {
    if(WWW&DDD)
    {
        if(v < 0)
            this->v = v+3*acceleration*time;
        else if(v <= vmax-acceleration)
            this->v = v+acceleration*time;
        else
            this->v = vmax;
        this->rectangle.rotate(vrot*time);
    }
    else if(WWW&AAA)
    {
        if(v < 0)
            this->v = v+3*acceleration*time;
        else if(v <= vmax-acceleration)
            this->v = v+acceleration*time;
        else
            this->v = vmax;
        this->rectangle.rotate(-vrot*time);
    }
    else if(SSS&DDD)
    {
        if(v >= 3*acceleration)
            this->v = v-3*acceleration*time;
        else if(v > 0)
            this->v = 0;
        else if(v >= vmin+acceleration)
            this->v = v-acceleration*time;
        else
            this->v = vmin;
        this->rectangle.rotate(vrot*time);
    }
    else if(SSS&AAA)
    {
        if(v >= 3*acceleration)
            this->v = v-3*acceleration*time;
        else if(v > 0)
            this->v = 0;
        else if(v >= vmin+acceleration)
            this->v = v-acceleration*time;
        else
            this->v = vmin;
        this->rectangle.rotate(-vrot*time);
    }
    else if(WWW)
    {
        if(v < 0)
            this->v = v+3*acceleration*time;
        else if(v <= vmax-acceleration)
            this->v = v+acceleration*time;
        else
            this->v = vmax;
    }
    else 	if(SSS)
    {
        if(v >= 3*acceleration)
            this->v = v-3*acceleration*time;
        else if(v > 0)
            this->v = 0;
        else if(v >= vmin+acceleration)
            this->v = v-acceleration*time;
        else
            this->v = vmin;
    }
    else 	if(DDD) {
        if(v >= acceleration)
            this->v = v-acceleration;
        else if(v > 0)
            this->v = 0;
        else if(v >= -acceleration)
            this->v = 0;
        else
            this->v = v+acceleration;
        this->rectangle.rotate(vrot*time);
    }
    else 	if(AAA) {
        if(v >= acceleration)
            this->v = v-acceleration*time;
        else if(v > 0)
            this->v = 0;
        else if(v >= -acceleration)
            this->v = 0;
        else
            this->v = v+acceleration*time;
        this->rectangle.rotate(-vrot*time);
    }
    else 	if(SPACE) {
        if(v >= 3*acceleration)
            this->v = v-3*acceleration*time;
        else if(v > 0)
            this->v = 0;
        else if(v >= -3*acceleration)
            this->v = 0;
        else
            this->v = v+3*acceleration*time;
    }
    else
    {
        if(v >= acceleration)
            this->v = v-acceleration*time;
        else if(v > 0)
            this->v = 0;
        else if(v >= -acceleration)
            this->v = 0;
        else
            this->v = v+acceleration*time;
    }
    pos = rectangle.getPosition();
    pos.x += v*time*sin(this->rectangle.getRotation()*0.0175);
    pos.y += -v*time*cos(this->rectangle.getRotation()*0.0175);
    if(CollisionCircleRectangle(pos.x+25, pos.y+25, this->r, 500, 500, 200, 200, v))
    {
        v = 0;
    }
    this->rectangle.move(v*time*sin(this->rectangle.getRotation()*0.0175) ,-v*time*cos(this->rectangle.getRotation()*0.0175));
};
void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const  {
    target.draw(rectangle, states);
};