bool CollisionCircleRectangle(float x1, float y1, float r, float x2, float y2, float l,float w)
{
    if(((x1 > x2)&&(x1 < x2+l))
            &&
            ((y1 > y2)&&(y1 < y2+w)))
        return true;
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
class Entity {
protected:
    sf::RenderWindow* window;
    sf::RectangleShape rectangle;
    float x, y;
    int angle;
    virtual void update(float) {};
};
class Static: public Entity {
public:
    Static(sf::RenderWindow* window)
    {
        this->x = 500;
        this->y = 500;
        this->window = window;
        this->rectangle.setSize(sf::Vector2f(10,200));
        this->rectangle.setOrigin(25,25);
        this->rectangle.setPosition(this->x, this->y);
        this->rectangle.setRotation(0);
    }
    void draw()
    {
        this->window->draw(this->rectangle);
    }
    virtual void update(float) {}
};
class Dynamic: public Entity {
public:
    double v;
    float acceleration;
    float r;
    virtual void update(float) {}
};
class Player: public Dynamic {
    int level;
public:
    Player(sf::RenderWindow* window)
    {
        this->acceleration = 0.08;
        this->r = 25;
        this->level = 0;
        this->x = 100;
        this->y = 100;
        this->v = 0;
        this->window = window;
        this->rectangle.setSize(sf::Vector2f(50,50));
        this->rectangle.setOrigin(25,25);
        this->rectangle.setPosition(this->x, this->y);
        this->rectangle.setRotation(0);
    }
    void draw()
    {
        this->window->draw(this->rectangle);
    }
    void update(float time) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)&sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            if(v < 0)
                this->v = v+3*acceleration;
            else if(v <= 5.92)
                this->v = v+acceleration;
            else
                this->v = 6;
            this->rectangle.rotate(2);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)&sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            if(v < 0)
                this->v = v+3*acceleration;
            else if(v <= 5.92)
                this->v = v+acceleration;
            else
                this->v = 6;
            this->rectangle.rotate(-2);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)&sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            if(v >= 3*acceleration)
                this->v = v-3*acceleration;
            else if(v > 0)
                this->v = 0;
            else if(v >= -2.92)
                this->v = v-acceleration;
            else
                this->v = -3;
            this->rectangle.rotate(2);
        }

        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)&sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            if(v >= 3*acceleration)
                this->v = v-3*acceleration;
            else if(v > 0)
                this->v = 0;
            else if(v >= -2.92)
                this->v = v-acceleration;
            else
                this->v = -3;
            this->rectangle.rotate(-2);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            if(v < 0)
                this->v = v+3*acceleration;
            else if(v <= 5.92)
                this->v = v+acceleration;
            else
                this->v = 6;
        }

        else 	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            if(v >= 3*acceleration)
                this->v = v-3*acceleration;
            else if(v > 0)
                this->v = 0;
            else if(v >= -2.92)
                this->v = v-acceleration;
            else
                this->v = -3;
        }

        else 	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            if(v >= acceleration)
                this->v = v-acceleration;
            else if(v > 0)
                this->v = 0;
            else if(v >= -acceleration)
                this->v = 0;
            else
                this->v = v+acceleration;
            this->rectangle.rotate(2);
        }
        else 	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            if(v >= acceleration)
                this->v = v-acceleration;
            else if(v > 0)
                this->v = 0;
            else if(v >= -acceleration)
                this->v = 0;
            else
                this->v = v+acceleration;
            this->rectangle.rotate(-2);
        }
        else 	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            if(v >= 3*acceleration)
                this->v = v-3*acceleration;
            else if(v > 0)
                this->v = 0;
            else if(v >= -3*acceleration)
                this->v = 0;
            else
                this->v = v+3*acceleration;
        }
        else
        {
            if(v >= acceleration)
                this->v = v-acceleration;
            else if(v > 0)
                this->v = 0;
            else if(v >= -acceleration)
                this->v = 0;
            else
                this->v = v+acceleration;
            if(CollisionCircleRectangle(this->x+25, this->y+25, this->r, 500, 500, 10, 200))
            {
                v = 0;
            }
        }
        this->rectangle.move(v*sin(this->rectangle.getRotation()*0.0175) ,-v*cos(this->rectangle.getRotation()*0.0175));
    }
};