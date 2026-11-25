#include <SFML/Graphics.hpp>

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>
#include <string>
#include <vector>

// Параметры игры и окна
constexpr int   GRID_SIZE   = 10;
constexpr int   CELLS_TOTAL = GRID_SIZE * GRID_SIZE;
constexpr float CELL_PX     = 62.0f;
constexpr float FIELD_PX    = CELL_PX * GRID_SIZE;
constexpr float MARGIN      = 24.0f;
constexpr int   NUM_PLAYERS = 2;
constexpr int   DICE_FACES  = 6;
constexpr float PANEL_W     = 320.0f;
constexpr float PANEL_GAP   = 26.0f;

constexpr float WINDOW_W = MARGIN * 2 + FIELD_PX + PANEL_GAP + PANEL_W;
constexpr float WINDOW_H = MARGIN * 2 + FIELD_PX;
constexpr float PANEL_X  = MARGIN * 2 + FIELD_PX + PANEL_GAP;

constexpr float PI = 3.14159265358979f;

// Палитра оформления
const sf::Color BG_TOP(162, 213, 255);
const sf::Color BG_BOTTOM(255, 250, 233);
const sf::Color PANEL_BG(255, 255, 255);
const sf::Color PANEL_BORDER(206, 214, 228);
const sf::Color CELL_A(255, 255, 255);
const sf::Color CELL_B(231, 242, 255);
const sf::Color CELL_BORDER(158, 180, 205);
const sf::Color EVENT_TINT(214, 178, 255, 110);
const sf::Color NUMBER_COL(128, 140, 156);
const sf::Color TEXT_DARK(52, 62, 78);
const sf::Color TEXT_MID(110, 122, 140);
const sf::Color WOOD(196, 138, 66);
const sf::Color WOOD_DARK(122, 78, 30);
const sf::Color SNAKE_BODY(255, 96, 92);
const sf::Color SNAKE_DARK(178, 44, 42);
const sf::Color GOLD(255, 200, 60);

const sf::Color PLAYER_COLORS[NUM_PLAYERS] = {
    sf::Color(255, 108, 82),
    sf::Color(74, 144, 255),
};
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
