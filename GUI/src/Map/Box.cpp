/*
** EPITECH PROJECT, 2024
** Box.cpp
** File description:
** zappy_gui
*/

#include "Box.hpp"

zappy::BoxDrawables::BoxDrawables(zappy::render3d::DisplayTile &displayTile, zappy::render3d::Camera &camera, std::size_t x, std::size_t y) : _tile(displayTile), _camera(camera), _x(x), _y(y)
{
    foodPosition = getRandomPosInBox() + sf::Vector3f(x, y, 0);
    linematePosition = getRandomPosInBox() + sf::Vector3f(x, y, 0);
    deraumerePosition = getRandomPosInBox() + sf::Vector3f(x, y, 0);
    siburPosition = getRandomPosInBox() + sf::Vector3f(x, y, 0);
    mendianePosition = getRandomPosInBox() + sf::Vector3f(x, y, 0);
    phirasPosition = getRandomPosInBox() + sf::Vector3f(x, y, 0);
    thystamePosition = getRandomPosInBox() + sf::Vector3f(x, y, 0);
}

void zappy::BoxDrawables::updateSprite()
{
    float crystalScale = 0.1;

    sprite = sf::Sprite(_tile.getTexture());
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
    sprite.setPosition(_camera.displayUnitaryX.x * _x + _camera.displayUnitaryY.x * _y + _camera.centerX * _camera.displayUnitaryX.x + _camera.displayUnitaryY.x * _camera.centerY + _camera.displayUnitaryZ.x * _camera.centerZ,
                        _camera.displayUnitaryX.y * _x + _camera.displayUnitaryY.y * _y + _camera.centerX * _camera.displayUnitaryX.y + _camera.displayUnitaryY.y * _camera.centerY + _camera.displayUnitaryZ.y * _camera.centerZ);
    food.setRadius(_camera.unitaryPixelsSize * crystalScale);
    food.setOrigin(food.getGlobalBounds().width / 2, food.getGlobalBounds().height / 2);
    food.setFillColor(sf::Color::Green);
    food.setPosition(_camera.displayUnitaryX.x * foodPosition.x + _camera.displayUnitaryY.x * foodPosition.y + _camera.centerX * _camera.displayUnitaryX.x + _camera.displayUnitaryY.x * _camera.centerY + _camera.displayUnitaryZ.x * _camera.centerZ,
                     _camera.displayUnitaryX.y * foodPosition.x + _camera.displayUnitaryY.y * foodPosition.y + _camera.centerX * _camera.displayUnitaryX.y + _camera.displayUnitaryY.y * _camera.centerY + _camera.displayUnitaryZ.y * _camera.centerZ);

    linemate.setRadius(_camera.unitaryPixelsSize  * crystalScale);
    linemate.setOrigin(linemate.getGlobalBounds().width / 2, linemate.getGlobalBounds().height / 2);
    linemate.setFillColor(sf::Color::Blue);
    linemate.setPosition(_camera.displayUnitaryX.x * linematePosition.x + _camera.displayUnitaryY.x * linematePosition.y + _camera.centerX * _camera.displayUnitaryX.x + _camera.displayUnitaryY.x * _camera.centerY + _camera.displayUnitaryZ.x * _camera.centerZ,
                        _camera.displayUnitaryX.y * linematePosition.x + _camera.displayUnitaryY.y * linematePosition.y + _camera.centerX * _camera.displayUnitaryX.y + _camera.displayUnitaryY.y * _camera.centerY + _camera.displayUnitaryZ.y * _camera.centerZ);

    deraumere.setRadius(_camera.unitaryPixelsSize  * crystalScale);
    deraumere.setOrigin(deraumere.getGlobalBounds().width / 2, deraumere.getGlobalBounds().height / 2);
    deraumere.setFillColor(sf::Color::Red);
    deraumere.setPosition(_camera.displayUnitaryX.x * deraumerePosition.x + _camera.displayUnitaryY.x * deraumerePosition.y + _camera.centerX * _camera.displayUnitaryX.x + _camera.displayUnitaryY.x * _camera.centerY + _camera.displayUnitaryZ.x * _camera.centerZ,
                        _camera.displayUnitaryX.y * deraumerePosition.x + _camera.displayUnitaryY.y * deraumerePosition.y + _camera.centerX * _camera.displayUnitaryX.y + _camera.displayUnitaryY.y * _camera.centerY + _camera.displayUnitaryZ.y * _camera.centerZ);

    sibur.setRadius(_camera.unitaryPixelsSize  * crystalScale);
    sibur.setOrigin(sibur.getGlobalBounds().width / 2, sibur.getGlobalBounds().height / 2);
    sibur.setFillColor(sf::Color::Yellow);
    sibur.setPosition(_camera.displayUnitaryX.x * siburPosition.x + _camera.displayUnitaryY.x * siburPosition.y + _camera.centerX * _camera.displayUnitaryX.x + _camera.displayUnitaryY.x * _camera.centerY + _camera.displayUnitaryZ.x * _camera.centerZ,
                        _camera.displayUnitaryX.y * siburPosition.x + _camera.displayUnitaryY.y * siburPosition.y + _camera.centerX * _camera.displayUnitaryX.y + _camera.displayUnitaryY.y * _camera.centerY + _camera.displayUnitaryZ.y * _camera.centerZ);

    mendiane.setRadius(_camera.unitaryPixelsSize  * crystalScale);
    mendiane.setOrigin(mendiane.getGlobalBounds().width / 2, mendiane.getGlobalBounds().height / 2);
    mendiane.setFillColor(sf::Color::Magenta);
    mendiane.setPosition(_camera.displayUnitaryX.x * mendianePosition.x + _camera.displayUnitaryY.x * mendianePosition.y + _camera.centerX * _camera.displayUnitaryX.x + _camera.displayUnitaryY.x * _camera.centerY + _camera.displayUnitaryZ.x * _camera.centerZ,
                        _camera.displayUnitaryX.y * mendianePosition.x + _camera.displayUnitaryY.y * mendianePosition.y + _camera.centerX * _camera.displayUnitaryX.y + _camera.displayUnitaryY.y * _camera.centerY + _camera.displayUnitaryZ.y * _camera.centerZ);

    phiras.setRadius(_camera.unitaryPixelsSize  * crystalScale);
    phiras.setOrigin(phiras.getGlobalBounds().width / 2, phiras.getGlobalBounds().height / 2);
    phiras.setFillColor(sf::Color::Cyan);
    phiras.setPosition(_camera.displayUnitaryX.x * phirasPosition.x + _camera.displayUnitaryY.x * phirasPosition.y + _camera.centerX * _camera.displayUnitaryX.x + _camera.displayUnitaryY.x * _camera.centerY + _camera.displayUnitaryZ.x * _camera.centerZ,
                        _camera.displayUnitaryX.y * phirasPosition.x + _camera.displayUnitaryY.y * phirasPosition.y + _camera.centerX * _camera.displayUnitaryX.y + _camera.displayUnitaryY.y * _camera.centerY + _camera.displayUnitaryZ.y * _camera.centerZ);

    thystame.setRadius(_camera.unitaryPixelsSize  * crystalScale);
    thystame.setOrigin(thystame.getGlobalBounds().width / 2, thystame.getGlobalBounds().height / 2);
    thystame.setFillColor(sf::Color::White);
    thystame.setPosition(_camera.displayUnitaryX.x * thystamePosition.x + _camera.displayUnitaryY.x * thystamePosition.y + _camera.centerX * _camera.displayUnitaryX.x + _camera.displayUnitaryY.x * _camera.centerY + _camera.displayUnitaryZ.x * _camera.centerZ,
                        _camera.displayUnitaryX.y * thystamePosition.x + _camera.displayUnitaryY.y * thystamePosition.y + _camera.centerX * _camera.displayUnitaryX.y + _camera.displayUnitaryY.y * _camera.centerY + _camera.displayUnitaryZ.y * _camera.centerZ);
}

sf::Vector3f zappy::BoxDrawables::getRandomPosInBox()
{
    std::seed_seq seed{std::random_device{}()};
    std::mt19937 gen(seed);
    std::uniform_real_distribution<float> dis(-0.5, 0.5);

    return sf::Vector3f(dis(gen), dis(gen), 0);
}

zappy::BoxDrawables::~BoxDrawables() = default;

zappy::Box::Box(std::size_t x, std::size_t y, zappy::SceneData &data) : x(x), y(y), _drawables(*data.getRandomTile(), data.camera, x, y)
{
    food = 0;
    linemate = 0;
    deraumere = 0;
    sibur = 0;
    mendiane = 0;
    phiras = 0;
    thystame = 0;
}

zappy::Box::~Box() = default;

void zappy::Box::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(_drawables.sprite, states);
    target.draw(_drawables.food, states);
    target.draw(_drawables.linemate, states);
    target.draw(_drawables.deraumere, states);
    target.draw(_drawables.sibur, states);
}

void zappy::Box::updateSprite()
{
    _drawables.updateSprite();
}
