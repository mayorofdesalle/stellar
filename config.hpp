// WINDOW DIMENSIONs
static const int WINDOW_X{1024};
static const int WINDOW_Y{768};

// AMOUNT OF STARS
static const int STARMAP_SIZE {2000};

// COLOR PALETTE
static const std::vector<sf::Color> PALETTE {
        sf::Color{33, 47, 69, 1}, sf::Color{20, 69, 82, 1},
        sf::Color{11, 82, 91, 1}, sf::Color{1, 1, 1, 1},
        sf::Color{77, 25, 77, 1}, sf::Color{0, 100, 102, 1},
        sf::Color{27, 58, 75, 1}, sf::Color{49, 34, 68, 1},
        sf::Color{39, 38, 64, 1}, sf::Color{6, 90, 96, 1},
        sf::Color{62, 31, 71, 1}, sf::Color{1, 1, 1, 1}
    };
    
// WARPING SPEED
static double warp_speed {1};

// THRUSTER (INPUT)
static double thrust {0.1};

// TRAIL LENGTH COEFFICIENT
static double trail_length {5};

// DISTANCE BETWEEN COLORS
static double distance {2.5};