#include "Starmap/Starmap.hpp"

bool adjust_color(sf::Color &color, const sf::Color &target);
void update_velocity(double &velocity);
void update_rotation(double &rotation);
void update_direction(double &direction);

int main ()
{   
    sf::RenderWindow window {sf::VideoMode(WINDOW_X, WINDOW_Y), "ARP 87"};
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(60);

    sf::Image icon;
    icon.loadFromFile("res/icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    size_t next_color {1}; // palette index
    sf::Color galaxy_color = PALETTE[0]; // current color
    Starmap starmap {STARMAP_SIZE, WINDOW_X, WINDOW_Y, PALETTE};

    sf::Clock clock;

    while (window.isOpen())
    {   
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                window.close();
        }

        // Handle input
        update_direction(direction);
        update_velocity(velocity);
        update_rotation(rotation);
        
        // Calculate distance traveled
        sf::Time time = clock.restart();
        distance -= time.asSeconds()*velocity;

        // Change galaxy color relative to the distance
        if (distance <= 0) {
            distance = 2.5;
            // Step 1 RGB towards next color
            if (adjust_color(galaxy_color, PALETTE.at(next_color)))
                next_color = (next_color + 1) % PALETTE.size();
        }

        // Render and display
        window.clear(galaxy_color);
        starmap.render(window, velocity, rotation, direction);
        window.display();
    }
}

bool adjust_color(sf::Color &color, const sf::Color &next_color)
    // Transition seamlessly to the next color
    {   
        if (color.r != next_color.r)
            color.r += (color.r > next_color.r) ? -1 : 1;
        if (color.b != next_color.b)
            color.b += (color.b > next_color.b) ? -1 : 1;
        if (color.g != next_color.g)
            color.g += (color.g > next_color.g) ? -1 : 1;
        return (color == next_color) ? true : false;
    }

void update_velocity(double &velocity) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && velocity <= MAX_VELOCITY) {
            velocity += THRUST + ACCELERATION;
        }
        else if (velocity > MIN_VELOCITY) {
            velocity -= (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) ? THRUST + ACCELERATION : 2 * THRUST;
        }
        else
            velocity = MIN_VELOCITY;
}

void update_rotation(double &rotation) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && std::fabs(rotation) <= MAX_ROTATION)
        rotation += ROTATION;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && std::fabs(rotation) <= MAX_ROTATION)
        rotation -= ROTATION;
    else {
        if (rotation > ROTATION)
            rotation -= ROTATION;
        else if (rotation < -ROTATION)
            rotation += ROTATION;
        else
            rotation = 0;
    }
}

void update_direction(double &direction) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && std::fabs(direction) <= MAX_DIRECTION)
            direction += DIRECTION + ACCELERATION;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && std::fabs(direction) <= MAX_DIRECTION) 
            direction -= DIRECTION + ACCELERATION;
        else {
            if (direction > ACCELERATION)
                direction -= ACCELERATION;
            else if (direction < -ACCELERATION)
                direction += ACCELERATION;
            else
                direction = 0;
        }
}