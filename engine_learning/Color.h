class Color {
public:
    unsigned char r, g, b;
public:
    Color(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0);
    Color operator*(const float &intensity);
    Color operator+(const Color& other);
    Color operator/(float num);
};