/*
** EPITECH PROJECT, 2024
** Box.cpp
** File description:
** zappy_gui
*/

#include "Box.hpp"

zappy::BoxDrawables::BoxDrawables(zappy::render3d::DisplayTile &displayTile, Assets &assets, zappy::render3d::Camera &camera, std::size_t x, std::size_t y) : _assets(assets), _tile(displayTile), _camera(camera), _x(x), _y(y)
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
    float crystalScale = 0.4;
    float scale;

    sprite = sf::Sprite(_tile.getTexture());
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
    sprite.setPosition(_camera.displayUnitaryX.x * _x + _camera.displayUnitaryY.x * _y + _camera.centerX * _camera.displayUnitaryX.x + _camera.displayUnitaryY.x * _camera.centerY + _camera.displayUnitaryZ.x * _camera.centerZ,
                        _camera.displayUnitaryX.y * _x + _camera.displayUnitaryY.y * _y + _camera.centerX * _camera.displayUnitaryX.y + _camera.displayUnitaryY.y * _camera.centerY + _camera.displayUnitaryZ.y * _camera.centerZ);

    food.setTexture(*_assets.foodTextures[0]);
    scale = food.getTexture()->getSize().x / (_camera.unitaryPixelsSize * crystalScale);
    food.setScale(1/scale, 1/scale);
    food.setOrigin(food.getTexture()->getSize().x / 2, food.getTexture()->getSize().y);
    food.setPosition(_camera.displayUnitaryX.x * foodPosition.x + _camera.displayUnitaryY.x * foodPosition.y + _camera.centerX * _camera.displayUnitaryX.x + _camera.displayUnitaryY.x * _camera.centerY + _camera.displayUnitaryZ.x * _camera.centerZ,
                     _camera.displayUnitaryX.y * foodPosition.x + _camera.displayUnitaryY.y * foodPosition.y + _camera.centerX * _camera.displayUnitaryX.y + _camera.displayUnitaryY.y * _camera.centerY + _camera.displayUnitaryZ.y * _camera.centerZ);

    linemate.setTexture(*_assets.linemateTextures[0]);
    scale = linemate.getTexture()->getSize().x / (_camera.unitaryPixelsSize * crystalScale);
    linemate.setScale(1/scale, 1/scale);
    linemate.setOrigin(linemate.getTexture()->getSize().x / 2, linemate.getTexture()->getSize().y);
    linemate.setPosition(_camera.displayUnitaryX.x * linematePosition.x + _camera.displayUnitaryY.x * linematePosition.y + _camera.centerX * _camera.displayUnitaryX.x + _camera.displayUnitaryY.x * _camera.centerY + _camera.displayUnitaryZ.x * _camera.centerZ,
                        _camera.displayUnitaryX.y * linematePosition.x + _camera.displayUnitaryY.y * linematePosition.y + _camera.centerX * _camera.displayUnitaryX.y + _camera.displayUnitaryY.y * _camera.centerY + _camera.displayUnitaryZ.y * _camera.centerZ);

    deraumere.setTexture(*_assets.deraumereTextures[0]);
    scale = deraumere.getTexture()->getSize().x / (_camera.unitaryPixelsSize * crystalScale);
    deraumere.setScale(1/scale, 1/scale);
    deraumere.setOrigin(deraumere.getTexture()->getSize().x / 2, deraumere.getTexture()->getSize().y);
    deraumere.setPosition(_camera.displayUnitaryX.x * deraumerePosition.x + _camera.displayUnitaryY.x * deraumerePosition.y + _camera.centerX * _camera.displayUnitaryX.x + _camera.displayUnitaryY.x * _camera.centerY + _camera.displayUnitaryZ.x * _camera.centerZ,
                        _camera.displayUnitaryX.y * deraumerePosition.x + _camera.displayUnitaryY.y * deraumerePosition.y + _camera.centerX * _camera.displayUnitaryX.y + _camera.displayUnitaryY.y * _camera.centerY + _camera.displayUnitaryZ.y * _camera.centerZ);

    sibur.setTexture(*_assets.siburTextures[0]);
    scale = sibur.getTexture()->getSize().x / (_camera.unitaryPixelsSize * crystalScale);
    sibur.setScale(1/scale, 1/scale);
    sibur.setOrigin(sibur.getTexture()->getSize().x / 2, sibur.getTexture()->getSize().y);
    sibur.setPosition(_camera.displayUnitaryX.x * siburPosition.x + _camera.displayUnitaryY.x * siburPosition.y + _camera.centerX * _camera.displayUnitaryX.x + _camera.displayUnitaryY.x * _camera.centerY + _camera.displayUnitaryZ.x * _camera.centerZ,
                        _camera.displayUnitaryX.y * siburPosition.x + _camera.displayUnitaryY.y * siburPosition.y + _camera.centerX * _camera.displayUnitaryX.y + _camera.displayUnitaryY.y * _camera.centerY + _camera.displayUnitaryZ.y * _camera.centerZ);

    mendiane.setTexture(*_assets.mendianeTextures[0]);
    scale = mendiane.getTexture()->getSize().x / (_camera.unitaryPixelsSize * crystalScale);
    mendiane.setScale(1/scale, 1/scale);
    mendiane.setOrigin(mendiane.getTexture()->getSize().x / 2, mendiane.getTexture()->getSize().y);
    mendiane.setPosition(_camera.displayUnitaryX.x * mendianePosition.x + _camera.displayUnitaryY.x * mendianePosition.y + _camera.centerX * _camera.displayUnitaryX.x + _camera.displayUnitaryY.x * _camera.centerY + _camera.displayUnitaryZ.x * _camera.centerZ,
                        _camera.displayUnitaryX.y * mendianePosition.x + _camera.displayUnitaryY.y * mendianePosition.y + _camera.centerX * _camera.displayUnitaryX.y + _camera.displayUnitaryY.y * _camera.centerY + _camera.displayUnitaryZ.y * _camera.centerZ);

    phiras.setTexture(*_assets.phirasTextures[0]);
    scale = phiras.getTexture()->getSize().x / (_camera.unitaryPixelsSize * crystalScale);
    phiras.setScale(1/scale, 1/scale);
    phiras.setOrigin(phiras.getTexture()->getSize().x / 2, phiras.getTexture()->getSize().y);
    phiras.setPosition(_camera.displayUnitaryX.x * phirasPosition.x + _camera.displayUnitaryY.x * phirasPosition.y + _camera.centerX * _camera.displayUnitaryX.x + _camera.displayUnitaryY.x * _camera.centerY + _camera.displayUnitaryZ.x * _camera.centerZ,
                        _camera.displayUnitaryX.y * phirasPosition.x + _camera.displayUnitaryY.y * phirasPosition.y + _camera.centerX * _camera.displayUnitaryX.y + _camera.displayUnitaryY.y * _camera.centerY + _camera.displayUnitaryZ.y * _camera.centerZ);

    thystame.setTexture(*_assets.thystameTextures[0]);
    scale = thystame.getTexture()->getSize().x / (_camera.unitaryPixelsSize * crystalScale);
    thystame.setScale(1/scale, 1/scale);
    thystame.setOrigin(thystame.getTexture()->getSize().x / 2, thystame.getTexture()->getSize().y);
    thystame.setPosition(_camera.displayUnitaryX.x * thystamePosition.x + _camera.displayUnitaryY.x * thystamePosition.y + _camera.centerX * _camera.displayUnitaryX.x + _camera.displayUnitaryY.x * _camera.centerY + _camera.displayUnitaryZ.x * _camera.centerZ,
                        _camera.displayUnitaryX.y * thystamePosition.x + _camera.displayUnitaryY.y * thystamePosition.y + _camera.centerX * _camera.displayUnitaryX.y + _camera.displayUnitaryY.y * _camera.centerY + _camera.displayUnitaryZ.y * _camera.centerZ);
}

sf::Vector3f zappy::BoxDrawables::getRandomPosInBox()
{
    std::seed_seq seed{std::random_device{}()};
    std::mt19937 gen(seed);
    std::uniform_real_distribution<float> dis(-0.35, 0.35);

    return sf::Vector3f(dis(gen), dis(gen), 0);
}

zappy::BoxDrawables::~BoxDrawables() = default;

zappy::Box::Box(std::size_t x, std::size_t y, zappy::SceneData &data, Assets &assets) : x(x), y(y), _drawables(*data.getRandomTile(), assets, data.camera, x, y)
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

    if (food > 0)
        target.draw(_drawables.food, states);

    if (linemate > 0)
        target.draw(_drawables.linemate, states);

    if (deraumere > 0)
        target.draw(_drawables.deraumere, states);

    if (sibur > 0)
        target.draw(_drawables.sibur, states);

    if (mendiane > 0)
        target.draw(_drawables.mendiane, states);

    if (phiras > 0)
        target.draw(_drawables.phiras, states);

    if (thystame > 0)
        target.draw(_drawables.thystame, states);
}

void zappy::Box::updateSprite()
{
    _drawables.updateSprite();
}
