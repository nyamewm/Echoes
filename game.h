class Player {
    sf::RenderWindow* window;
    sf::RectangleShape rectangle;
    sf::Texture texture;
    const sf::Texture *pTexture = &texture;
    int x, y;
    int level;
public:
    Player(sf::RenderWindow* window) {
        texture.loadFromFile("images/a.png");
        this->level = 0;
        this->x = 100;
        this->y = 100;
        this->window = window;
        this->rectangle.setSize(sf::Vector2f(200,200));
        this->rectangle.setOrigin(25,25);
        this->rectangle.setPosition(this->x, this->y);
        this->rectangle.setTexture(pTexture);

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