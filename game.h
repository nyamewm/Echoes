class Player {
    sf::RenderWindow* window;
    sf::RectangleShape rectangle;
    sf::Texture texture;
    const sf::Texture *pTexture = &texture;
    int x, y;
    int level;
    float v;
public:
    Player(sf::RenderWindow* window) {
        texture.loadFromFile("images/a.png");
        this->level = 0;
        this->x = 100;
        this->y = 100;
        this->v = 0;
        this->window = window;
        this->rectangle.setSize(sf::Vector2f(200,200));
        this->rectangle.setOrigin(25,25);
        this->rectangle.setPosition(this->x, this->y);
        this->rectangle.setTexture(pTexture);
        this->rectangle.setRotation(0);


    }
    void draw() {
        this->window->draw(this->rectangle);

    }
    void update(float time) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)&sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {

            if(v < 0)
                this->v = v+0.12;
            else if(v <= 5.96)
                this->v = v+0.04;
            else
                this->v = 6;
            this->rectangle.rotate(2);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)&sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {

            if(v < 0)
                this->v = v+0.12;
            else if(v <= 5.96)
                this->v = v+0.04;
            else
                this->v = 6;
            this->rectangle.rotate(-2);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)&sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {

            if(v >= 0.012)
                this->v = v-0.12;
            else if(v > 0)
                this->v = 0;
            else if(v >= -2.96)
                this->v = v-0.04;
            else
                this->v = -3;
            this->rectangle.rotate(2);

        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)&sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {

            if(v >= 0.012)
                this->v = v-0.12;
            else if(v > 0)
                this->v = 0;
            else if(v >= -2.96)
                this->v = v-0.04;
            else
                this->v = -3;
            this->rectangle.rotate(-2);

        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {

            if(v < 0)
                this->v = v+0.12;
            else if(v <= 5.96)
                this->v = v+0.04;
            else
                this->v = 6;

        }
        else 	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {

            if(v >= 0.012)
                this->v = v-0.12;
            else if(v > 0)
                this->v = 0;
            else if(v >= -2.96)
                this->v = v-0.04;
            else
                this->v = -3;

        }

        else 	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            this->rectangle.rotate(2);
        }
        else 	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            this->rectangle.rotate(-2);
        }
        else 	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            if(v >= 0.012)
                this->v = v-0.12;
            else if(v > 0)
                this->v = 0;
            else if(v >= -0.12)
                this->v = 0;
            else
                this->v = v+0.12;
        }
        this->rectangle.move(v*sin(this->rectangle.getRotation()*0.0175) ,-v*cos(this->rectangle.getRotation()*0.0175));


    }
};