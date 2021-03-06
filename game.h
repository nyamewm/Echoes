#define WWW sf::Keyboard::isKeyPressed(sf::Keyboard::W)
#define AAA sf::Keyboard::isKeyPressed(sf::Keyboard::A)
#define SSS sf::Keyboard::isKeyPressed(sf::Keyboard::S)
#define DDD sf::Keyboard::isKeyPressed(sf::Keyboard::D)
#define SPACE sf::Keyboard::isKeyPressed(sf::Keyboard::Space)

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
public:
    sf::RenderWindow* window;
    sf::RectangleShape rectangle;
    sf::Texture texture;
    const sf::Texture *pTexture = &texture;
    int x, y;
    int level;
    sf::Vector2f position;
    int angle;
    void update(float) {};
    //virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class Static: public Entity {
public:
    Static(sf::RenderWindow* window);
    /*void draw()
    {
        window->draw(rectangle);
    }*/
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class Dynamic: public Entity {
public:
    float v;
    float acceleration;
    float r;
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

float DotProduct(sf::Vector2f a, sf::Vector2f b)
{
    return (a.x*b.x + a.y*b.y);
}

/*void ResolveCollision(Dynamic A, Dynamic B)
{
    // Вычисляем относительную скорость
    sf::Vector2f rv = B.v - A.v;

    sf::Vector2f normal;
    normal.x = (B.position.x - A.position.x)/();

    // Вычисляем относительную скорость относительно направления нормали
    float velAlongNormal = DotProduct(rv, normal)

    // Не выполняем вычислений, если скорости разделены
    if(velAlongNormal > 0)
        return;

    // Вычисляем упругость
    float e = min( A.restitution, B.restitution)

    // Вычисляем скаляр импульса силы
    float j = -(1 + e) * velAlongNormal
    j /= 1 / A.mass + 1 / B.mass

    // Прикладываем импульс силы
    Vec2 impulse = j * normal
    A.velocity -= 1 / A.mass * impulse
    B.velocity += 1 / B.mass * impulse
}*/

class Player: public Dynamic {
    sf::Texture texture;
    const sf::Texture *pTexture = &texture;
public:
    Player(sf::RenderWindow* window);

    int level;
    sf::Vector2f pos;
    float vmax, vmin, vrot;
    /*void draw()
    {
        window->draw(rectangle);
    }*/
    void update(float time);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

Static::Static(sf::RenderWindow *window) {
    window = window;
    rectangle.setSize(sf::Vector2f(200,200));
    rectangle.setOrigin(25,25);
    rectangle.setPosition(300,300);
    rectangle.setRotation(0);
};
void Static::draw(sf::RenderTarget &target, sf::RenderStates states) const  {
    target.draw(rectangle, states);
};
void Dynamic::draw(sf::RenderTarget &target, sf::RenderStates states) const  {
    target.draw(rectangle, states);
};
Player::Player(sf::RenderWindow *window)
{
    texture.loadFromFile("images/a.png");
    acceleration = 100;
    r = 25;
    level = 0;
    v = 0;
    vmax = 0.3;
    vmin = -0.15;
    vrot = 15;
    window = window;
    rectangle.setSize(sf::Vector2f(50,50));
    rectangle.setOrigin(25,25);
    rectangle.setPosition(100, 100);
    rectangle.setRotation(0);
    rectangle.setTexture(pTexture);
};
void Player::update(float time) {
    if(WWW&DDD)
    {
        if(v < 0)
            v = v+3*acceleration*time;
        else if(v <= vmax-acceleration)
            v = v+acceleration*time;
        else
            v = vmax;
        rectangle.rotate(vrot*time);
    }
    else if(WWW&AAA)
    {
        if(v < 0)
            v = v+3*acceleration*time;
        else if(v <= vmax-acceleration)
            v = v+acceleration*time;
        else
            v = vmax;
        rectangle.rotate(-vrot*time);
    }
    else if(SSS&DDD)
    {
        if(v >= 3*acceleration)
            v = v-3*acceleration*time;
        else if(v > 0)
            v = 0;
        else if(v >= vmin+acceleration)
            v = v-acceleration*time;
        else
            v = vmin;
        rectangle.rotate(vrot*time);
    }
    else if(SSS&AAA)
    {
        if(v >= 3*acceleration)
            v = v-3*acceleration*time;
        else if(v > 0)
            v = 0;
        else if(v >= vmin+acceleration)
            v = v-acceleration*time;
        else
            v = vmin;
        rectangle.rotate(-vrot*time);
    }
    else if(WWW)
    {
        if(v < 0)
            v = v+3*acceleration*time;
        else if(v <= vmax-acceleration)
            v = v+acceleration*time;
        else
            v = vmax;
    }
    else 	if(SSS)
    {
        if(v >= 3*acceleration)
            v = v-3*acceleration*time;
        else if(v > 0)
            v = 0;
        else if(v >= vmin+acceleration)
            v = v-acceleration*time;
        else
            v = vmin;
    }
    else 	if(DDD) {
        if(v >= acceleration)
            v = v-acceleration;
        else if(v > 0)
            v = 0;
        else if(v >= -acceleration)
            v = 0;
        else
            v = v+acceleration;
        rectangle.rotate(vrot*time);
    }
    else 	if(AAA) {
        if(v >= acceleration)
            v = v-acceleration*time;
        else if(v > 0)
            v = 0;
        else if(v >= -acceleration)
            v = 0;
        else
            v = v+acceleration*time;
        rectangle.rotate(-vrot*time);
    }
    else 	if(SPACE) {
        if(v >= 3*acceleration)
            v = v-3*acceleration*time;
        else if(v > 0)
            v = 0;
        else if(v >= -3*acceleration)
            v = 0;
        else
            v = v+3*acceleration*time;
    }
    else
    {
        if(v >= acceleration)
            v = v-acceleration*time;
        else if(v > 0)
            v = 0;
        else if(v >= -acceleration)
            v = 0;
        else
            v = v+acceleration*time;
    }
    pos = rectangle.getPosition();
    pos.x += v*time*sin(rectangle.getRotation()*0.0175);
    pos.y += -v*time*cos(rectangle.getRotation()*0.0175);
    if(CollisionCircleRectangle(pos.x+25, pos.y+25, r, 500, 500, 200, 200, v))
    {
        v = 0;
    }
    rectangle.move(v*time*sin(rectangle.getRotation()*0.0175) ,-v*time*cos(rectangle.getRotation()*0.0175));
};
void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const  {
    target.draw(rectangle, states);
};