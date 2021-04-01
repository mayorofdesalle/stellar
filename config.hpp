const double PI {3.14159265358979323846};

// WINDOW DIMENSIONs
const int WINDOW_X{1024};
const int WINDOW_Y{768};

// AMOUNT OF STARS
const int STARMAP_SIZE {2000};

// COLOR PALETTE
const std::vector<sf::Color> PALETTE {
        sf::Color{33, 47, 69, 1}, sf::Color{20, 69, 82, 1},
        sf::Color{11, 82, 91, 1}, sf::Color{1, 1, 1, 1},
        sf::Color{77, 25, 77, 1}, sf::Color{0, 100, 102, 1},
        sf::Color{27, 58, 75, 1}, sf::Color{49, 34, 68, 1},
        sf::Color{39, 38, 64, 1}, sf::Color{6, 90, 96, 1},
        sf::Color{62, 31, 71, 1}, sf::Color{1, 1, 1, 1}
    };

// STAR RADIUS COEFFICIENT
const double RADII {5};
    
// VELOCITY, ACCELERATION AND THRUSTER (INPUT)
const double MIN_VELOCITY {0.05};
const double MAX_VELOCITY {100};
const double ACCELERATION {0.05};
const double THRUST {0.1};
double velocity {1};

// ROTATION, DIRECTION AND COEFFICIENTS
const double ROTATION {1};
const double MAX_ROTATION {100*ROTATION};
double rotation {0};
const double DIRECTION {0.01};
const double MAX_DIRECTION {100*DIRECTION};
double direction {0};

// TRAIL LENGTH COEFFICIENT
const double TRAIL_LENGTH {5};

// DISTANCE BETWEEN COLORS
double distance {2.5};