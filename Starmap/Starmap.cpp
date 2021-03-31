#include "Starmap.hpp"

Starmap::Star::Star(double x, double y, double z, int p)
    // Star constructor
    : x{x}, y{y}, z{z}, body(1), trail(sf::Lines, 2)
    {   
        body.setFillColor(sf::Color::White);
        body.setOrigin(body.getRadius(), body.getRadius());
        body.setPosition(sf::Vector2f(x, y));
        body.setPointCount(p);
    }

Starmap::Starmap(const int sm_size, const int w_x, const int w_y, const std::vector<sf::Color> &palette)
    // Starmap Constructor
    :   stars{static_cast<size_t>(sm_size)}, 
        rd{std::random_device{}()},
        dist_x{static_cast<double>(-w_x/2), static_cast<double>(w_x/2)},
        dist_y{static_cast<double>(-w_y/2), static_cast<double>(w_y/2)},
        dist_z{0, static_cast<double>(w_x)}, 
        dist_p{3, 10}, // (min=triangle max=decagon)
        palette{palette}
    {   
        double x, y, z, p {};
        for (auto &s : stars) {
            x = dist_x(rd);
            y = dist_y(rd);
            z = dist_z(rd);
            p = dist_p(rd);
            s = Star {x, y, z, static_cast<int>(p)};
        }
    }

void Starmap::update(const sf::RenderWindow &window, const double &speed)
    // Update position, bodies and trails of the stars
    {
        size_t c;
        for (auto &s : stars) {
            // Warp
            s.z -= speed;

            if (s.z <= 0) {
                // Redraw star within boundaries
                s.x = dist_x(rd);
                s.y = dist_y(rd);
                s.z += window.getSize().x;

                // Color star white/random color
                c = static_cast<int>(dist_z(rd));
                if (c%2 == 0) {
                    c %= static_cast<int>(palette.size());
                    // Cannot move/copy sf::Color
                    s.body.setFillColor(sf::Color{palette.at(c).r, palette.at(c).g, palette.at(c).b, 255});
                }
                else
                    s.body.setFillColor(sf::Color::White);
            }
            
            // Handle next position
            double nx {(s.x * window.getSize().x / s.z) + window.getSize().x/2};
            double ny {(s.y * window.getSize().y / s.z) + window.getSize().y/2};
            s.body.setPosition(sf::Vector2f(nx, ny));
            // Adjust radius relative to z
            s.body.setRadius((window.getSize().x-s.z)/200);
            // Update origin
            s.body.setOrigin(s.body.getRadius(), s.body.getRadius());

            // Handle trail position
            double tx {(s.x * window.getSize().x / (s.z + speed * trail_length)) + window.getSize().x/2};
            double ty {(s.y * window.getSize().y / (s.z + speed * trail_length)) + window.getSize().y/2};
            s.trail[0] = sf::Vertex(sf::Vector2f(tx, ty));
            s.trail[1] = sf::Vertex(sf::Vector2f(nx, ny));
            // Color trail
            c = static_cast<int>(dist_z(rd)) % static_cast<int>((palette.size()));
            s.trail[0].color = sf::Color::White;
            s.trail[1].color = sf::Color{palette.at(c).r, palette.at(c).g, palette.at(c).b, 255};

        }
    }

void Starmap::render(sf::RenderWindow &window, const double &speed)
    // Render the stars
    {
        update(window, speed);
        for (auto &s : stars) {
            window.draw(s.body);
            window.draw(s.trail);
        }
    }