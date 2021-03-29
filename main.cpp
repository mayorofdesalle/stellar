#include "Starmap/Starmap.hpp"

bool adjust_color(sf::Color &color, const sf::Color &target);

int main ()
{   
    sf::RenderWindow window {sf::VideoMode(WINDOW_X, WINDOW_Y), "ARP 87"};
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
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Handle input for speed manipulation
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            warp_speed += thrust;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            if (warp_speed > 3*thrust)
                warp_speed -= 2*thrust;
        }

        // Calculate distance traveled
        sf::Time time = clock.restart();
        distance -= time.asSeconds()*warp_speed;
        // Change galaxy color relative to the distance
        if (distance <= 0) {
            distance = 2.5;
            // Step 1 RGB towards next color
            if (adjust_color(galaxy_color, PALETTE.at(next_color)))
                next_color = (next_color + 1) % PALETTE.size();
        }

        // Render and display
        window.clear(galaxy_color);
        starmap.render(window, warp_speed);
        window.display();
    }

    return 0;
}

bool adjust_color(sf::Color &color, const sf::Color &target)
    // Transition seamlessly to the next color
    {   
        if (color.r != target.r)
            color.r += (color.r > target.r) ? -1 : 1;
        if (color.b != target.b)
            color.b += (color.b > target.b) ? -1 : 1;
        if (color.g != target.g)
            color.g += (color.g > target.g) ? -1 : 1;
        return (color == target) ? true : false;
    }