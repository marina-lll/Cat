sf::Vector2f cellTopLeft(int cell)
{
    int row = cell / GRID_SIZE;
    int col = cell % GRID_SIZE;
    if (row % 2 == 1)
        col = GRID_SIZE - 1 - col;
    return { MARGIN + col * CELL_PX,
             MARGIN + (GRID_SIZE - 1 - row) * CELL_PX };
}

sf::Vector2f cellCenter(int cell)
{
    sf::Vector2f tl = cellTopLeft(cell);
    return { tl.x + CELL_PX / 2.0f, tl.y + CELL_PX / 2.0f };
}

float clamp01(float t) { return std::clamp(t, 0.0f, 1.0f); }

float easeInOut(float t)
{
    t = clamp01(t);
    return t * t * (3.0f - 2.0f * t);
}

float easeOutBack(float t)
{
    t = clamp01(t);
    const float c1 = 1.70158f, c3 = c1 + 1.0f;
    return 1.0f + c3 * std::pow(t - 1.0f, 3) + c1 * std::pow(t - 1.0f, 2);
}

// кириллицу конвертируем в Unicode
sf::String toSfString(const std::string& s)
{
    return sf::String::fromUtf8(s.begin(), s.end());
}
// Описание поля
struct Transition
{
    int  from;
    int  to;
    bool up;
};

struct EventCell
{
    int         cell;
    std::string desc;
    bool        extra;   // true = «Ещё ход», false = «Пропуск хода»
};

const std::vector<Transition> g_transitions = {
    {  3, 22, true },
    {  8, 30, true },
    { 28, 84, true },
    { 58, 77, true },
    { 95, 75, false },
    { 88, 24, false },
    { 62, 18, false },
    { 49, 11, false },
    { 36,  6, false },
    { 21,  9, false },
};

const std::vector<EventCell> g_events = {
    { 12, "Пропуск хода", false },
    { 47, "Ещё ход",      true  },
    { 71, "Пропуск хода", false },
    { 90, "Ещё ход",      true  },
};
// Скруглённый прямоугольник из ConvexShape (выпуклая фигура — подходит).
sf::ConvexShape roundedRect(sf::Vector2f size, float radius, unsigned per = 8)
{
    sf::ConvexShape shape;
    shape.setPointCount(per * 4);
    float w = size.x, h = size.y;
    radius = std::min(radius, std::min(w, h) * 0.49f);
    const sf::Vector2f centers[4] = {
        { radius, radius }, { w - radius, radius },
        { w - radius, h - radius }, { radius, h - radius }
    };
    const float startAngle[4] = { 180.f, 270.f, 0.f, 90.f };
    unsigned idx = 0;
    for (int c = 0; c < 4; ++c)
        for (unsigned k = 0; k < per; ++k)
        {
            float a = (startAngle[c] + 90.f * float(k) / per) * PI / 180.f;
            shape.setPoint(idx++, { centers[c].x + radius * std::cos(a),
                                    centers[c].y + radius * std::sin(a) });
        }
    return shape;
}

void drawThickLine(sf::RenderWindow& w, sf::Vector2f a, sf::Vector2f b,
                   float thickness, sf::Color col)
{
    sf::Vector2f d = b - a;
    float len = std::hypot(d.x, d.y);
    if (len < 0.001f) return;
    float ang = std::atan2(d.y, d.x) * 180.f / PI;
    sf::RectangleShape r(sf::Vector2f(len, thickness));
    r.setOrigin(0, thickness / 2.f);
    r.setPosition(a);
    r.setRotation(ang);
    r.setFillColor(col);
    w.draw(r);
}

void drawBackground(sf::RenderWindow& w)
{
    sf::VertexArray va(sf::PrimitiveType::TrianglesStrip, 4);
    va[0] = sf::Vertex({ 0, 0 }, BG_TOP);
    va[1] = sf::Vertex({ 0, WINDOW_H }, BG_BOTTOM);
    va[2] = sf::Vertex({ WINDOW_W, 0 }, BG_TOP);
    va[3] = sf::Vertex({ WINDOW_W, WINDOW_H }, BG_BOTTOM);
    w.draw(va);
}
