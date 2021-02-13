class Player {
    sf::RenderWindow* window;
    sf::RectangleShape rectangle;
    int x, y;
    int level;
public:
    Player(sf::RenderWindow* window) {
        this->level = 0;
        this->x = 100;
        this->y = 100;
        this->window = window;
        this->rectangle.setSize(sf::Vector2f(50,50));
        this->rectangle.setOrigin(25,25);
        this->rectangle.setPosition(this->x, this->y);


    }
    void draw() {
        this->window->draw(this->rectangle);

    }
    void update(float time) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {

            this->rectangle.move(0 ,-2);

        }
        else 	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            this->rectangle.move(0 ,2);
        }

        else 	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            this->rectangle.move(2 ,0);
        }
        else 	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            this->rectangle.move(-2 ,0);
        }


    }
};