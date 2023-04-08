struct Position{
    size_t x, y;
    Position(size_t x, size_t y) : x{x}, y{y} {};
    Position(const Position& p) : x{p.x}, y{p.y} {};
    Position(Position&& p) : x{p.x}, y{p.y} {};
    Position &operator=(const Position& p) {
        x = p.x;
        y = p.y;
    }
    Position &operator=(Position && p) {
        x = p.x;
        y = p.y;
    }
    ~Position() {};

};
