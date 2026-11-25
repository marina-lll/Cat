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
