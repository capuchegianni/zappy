/*
** EPITECH PROJECT, 2024
** BoxInfo.cpp
** File description:
** zappy_gui
*/

#include "BoxInfo.hpp"

zappy::BoxInfoDrawables::BoxInfoDrawables()
{
    background.setFillColor(sf::Color::Green);
    background.setOutlineColor(sf::Color::Black);
    background.setOutlineThickness(4);
}

zappy::BoxInfoDrawables::~BoxInfoDrawables() = default;

void zappy::BoxInfoDrawables::updateDisplay()
{
    renderTexture.clear(sf::Color::Transparent);

    renderTexture.draw(food);
    renderTexture.draw(linemate);
    renderTexture.draw(deraumere);
    renderTexture.draw(sibur);
    renderTexture.draw(mendiane);
    renderTexture.draw(phiras);
    renderTexture.draw(thystame);

    renderTexture.display();
    sprite.setTexture(renderTexture.getTexture(), true);
}

zappy::BoxInfo::BoxInfo(zappy::Assets &assets)
{
    _drawables.food.setTexture(*assets.foodTextures[0]);
    _drawables.linemate.setTexture(*assets.linemateTextures[0]);
    _drawables.deraumere.setTexture(*assets.deraumereTextures[0]);
    _drawables.sibur.setTexture(*assets.siburTextures[0]);
    _drawables.mendiane.setTexture(*assets.mendianeTextures[0]);
    _drawables.phiras.setTexture(*assets.phirasTextures[0]);
    _drawables.thystame.setTexture(*assets.thystameTextures[0]);

    _drawables.food.setOrigin(_drawables.food.getTexture()->getSize().x / 2, _drawables.food.getTexture()->getSize().y / 2);
    _drawables.linemate.setOrigin(_drawables.linemate.getTexture()->getSize().x / 2, _drawables.linemate.getTexture()->getSize().y / 2);
    _drawables.deraumere.setOrigin(_drawables.deraumere.getTexture()->getSize().x / 2, _drawables.deraumere.getTexture()->getSize().y / 2);
    _drawables.sibur.setOrigin(_drawables.sibur.getTexture()->getSize().x / 2, _drawables.sibur.getTexture()->getSize().y / 2);
    _drawables.mendiane.setOrigin(_drawables.mendiane.getTexture()->getSize().x / 2, _drawables.mendiane.getTexture()->getSize().y / 2);
    _drawables.phiras.setOrigin(_drawables.phiras.getTexture()->getSize().x / 2, _drawables.phiras.getTexture()->getSize().y / 2);
    _drawables.thystame.setOrigin(_drawables.thystame.getTexture()->getSize().x / 2, _drawables.thystame.getTexture()->getSize().y / 2);
}

zappy::BoxInfo::~BoxInfo() = default;

void zappy::BoxInfo::setDisplaySize(sf::Vector2f &size)
{
    _drawables.background.setSize(size);
    _drawables.renderTexture.create(size.x, size.y);
    _drawables.view = sf::View(sf::FloatRect(0, 0, size.x, size.y));

    _drawables.food.setPosition(size.x / 9, size.y / 9 + size.y / 14);
    _drawables.linemate.setPosition(size.x / 9, size.y / 9 * 2 + size.y / 14);
    _drawables.deraumere.setPosition(size.x / 9, size.y / 9 * 3 + size.y / 14);
    _drawables.sibur.setPosition(size.x / 9, size.y / 9 * 4 + size.y / 14);
    _drawables.mendiane.setPosition(size.x / 9, size.y / 9 * 5 + size.y / 14);
    _drawables.phiras.setPosition(size.x / 9, size.y / 9 * 6 + size.y / 14);
    _drawables.thystame.setPosition(size.x / 9, size.y / 9 * 7 + size.y / 14);

    float foodScale = size.y / 9 / _drawables.food.getTexture()->getSize().y;
    float linemateScale = size.y / 9 / _drawables.linemate.getTexture()->getSize().y;
    float deraumereScale = size.y / 9 / _drawables.deraumere.getTexture()->getSize().y;
    float siburScale = size.y / 9 / _drawables.sibur.getTexture()->getSize().y;
    float mendianeScale = size.y / 9 / _drawables.mendiane.getTexture()->getSize().y;
    float phirasScale = size.y / 9 / _drawables.phiras.getTexture()->getSize().y;
    float thystameScale = size.y / 9 / _drawables.thystame.getTexture()->getSize().y;

    _drawables.food.setScale(foodScale, foodScale);
    _drawables.linemate.setScale(linemateScale, linemateScale);
    _drawables.deraumere.setScale(deraumereScale, deraumereScale);
    _drawables.sibur.setScale(siburScale, siburScale);
    _drawables.mendiane.setScale(mendianeScale, mendianeScale);
    _drawables.phiras.setScale(phirasScale, phirasScale);
    _drawables.thystame.setScale(thystameScale, thystameScale);
}

void zappy::BoxInfo::setDisplayPosition(sf::Vector2f &position)
{
    _drawables.background.setPosition(position);
    _drawables.sprite.setPosition(position);
}

void zappy::BoxInfo::updateDisplay()
{
    _drawables.updateDisplay();
}

void zappy::BoxInfo::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(this->_drawables.background, states);
    target.draw(this->_drawables.sprite, states);
}
