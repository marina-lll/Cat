void drawLadder(sf::RenderWindow& w, sf::Vector2f a, sf::Vector2f b)
{
    sf::Vector2f d = b - a;
    float len = std::hypot(d.x, d.y);
    if (len < 2.0f) return;
    sf::Vector2f u = d / len, perp(-u.y, u.x);
    const float rail = 7.0f;
    sf::Vector2f a1 = a + perp * rail, b1 = b + perp * rail;
    sf::Vector2f a2 = a - perp * rail, b2 = b - perp * rail;

    sf::Vector2f sh(2, 3);
    drawThickLine(w, a1 + sh, b1 + sh, 13, sf::Color(0, 0, 0, 40));
    drawThickLine(w, a2 + sh, b2 + sh, 13, sf::Color(0, 0, 0, 40));

    for (const auto& p : { std::make_pair(a1, b1), std::make_pair(a2, b2) })
    {
        drawThickLine(w, p.first, p.second, 11, WOOD_DARK);
        drawThickLine(w, p.first, p.second, 7, WOOD);
    }

    int rungs = std::max(3, int(len / 24));
    for (int i = 1; i < rungs; ++i)
    {
        float s = float(i) / rungs;
        sf::Vector2f p = a + u * (len * s);
        drawThickLine(w, p + perp * (rail + 2), p - perp * (rail + 2), 8, WOOD_DARK);
        drawThickLine(w, p + perp * rail, p - perp * rail, 5, WOOD);
    }
}
void drawSnake(sf::RenderWindow& w, sf::Vector2f head, sf::Vector2f tail)
{
    sf::Vector2f d = tail - head;
    float len = std::hypot(d.x, d.y);
    if (len < 2.0f) return;
    sf::Vector2f u = d / len, perp(-u.y, u.x);

    const int   SEG   = 46;
    const float waves = 2.6f, amp = 7.0f;
    std::vector<sf::Vector2f> pts(SEG + 1);
    for (int i = 0; i <= SEG; ++i)
    {
        float s = float(i) / SEG;
        pts[i] = head + u * (len * s)
               + perp * (std::sin(s * waves * 2 * PI) * amp);
    }

    sf::Vector2f sh(3, 4);
    for (int i = SEG; i >= 0; --i)
    {
        float s = float(i) / SEG;
        float r = (11.f - 4.f * s) + 3.f;
        sf::CircleShape c(r);
        c.setOrigin(r, r);
        c.setPosition(pts[i] + sh);
        c.setFillColor(sf::Color(0, 0, 0, 40));
        w.draw(c);
    }
    for (int i = SEG; i >= 0; --i)
    {
        float s = float(i) / SEG;
        float r = 11.f - 4.f * s;
        sf::CircleShape c(r);
        c.setOrigin(r, r);
        c.setPosition(pts[i]);
        c.setFillColor(SNAKE_DARK);
        w.draw(c);
    }
    for (int i = SEG; i >= 0; --i)
    {
        float s = float(i) / SEG;
        float r = 7.5f - 3.f * s;
        sf::CircleShape c(r);
        c.setOrigin(r, r);
        c.setPosition(pts[i]);
        c.setFillColor(SNAKE_BODY);
        w.draw(c);
    }
 // Голова
    sf::CircleShape headShape(15.f);
    headShape.setOrigin(15.f, 15.f);
    headShape.setPosition(pts[0]);
    headShape.setFillColor(SNAKE_DARK);
    w.draw(headShape);
    headShape.setRadius(12.f);
    headShape.setOrigin(12.f, 12.f);
    headShape.setPosition(pts[0] + u * 2.f);
    headShape.setFillColor(SNAKE_BODY);
    w.draw(headShape);

    // Глаз
    sf::CircleShape eye(4.5f);
    eye.setOrigin(4.5f, 4.5f);
    eye.setPosition(pts[0] + u * 9.f + perp * 4.f);
    eye.setFillColor(sf::Color::White);
    w.draw(eye);
    sf::CircleShape pupil(2.2f);
    pupil.setOrigin(2.2f, 2.2f);
    pupil.setPosition(pts[0] + u * 10.f + perp * 4.5f);
    pupil.setFillColor(sf::Color(30, 30, 30));
    w.draw(pupil);

    // Язычок
    drawThickLine(w, pts[0] + u * 18.f, pts[0] + u * 34.f, 2.5f, sf::Color(255, 60, 60));
}

