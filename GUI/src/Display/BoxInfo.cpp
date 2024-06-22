/*
** EPITECH PROJECT, 2024
** BoxInfo.cpp
** File description:
** zappy_gui
*/

#include "BoxInfo.hpp"

zappy::BoxInfoDrawables::BoxInfoDrawables()
{
    background.setFillColor(sf::Color(32, 32, 32, 255));
    background.setOutlineColor(sf::Color::Black);
    background.setOutlineThickness(4);
}

zappy::BoxInfoDrawables::~BoxInfoDrawables() = default;

void zappy::BoxInfoDrawables::updateDisplay(std::shared_ptr<Box> &box)
{
    renderTexture.clear(sf::Color::Transparent);

    renderTexture.draw(food);
    renderTexture.draw(linemate);
    renderTexture.draw(deraumere);
    renderTexture.draw(sibur);
    renderTexture.draw(mendiane);
    renderTexture.draw(phiras);
    renderTexture.draw(thystame);

    if (box != nullptr)
    {
        foodText.setString("Food:" + std::to_string(box->food));
        linemateText.setString("Linemate:" + std::to_string(box->linemate));
        deraumereText.setString("Deraumere:" + std::to_string(box->deraumere));
        siburText.setString("Sibur:" + std::to_string(box->sibur));
        mendianeText.setString("Mendiane:" + std::to_string(box->mendiane));
        phirasText.setString("Phiras:" + std::to_string(box->phiras));
        thystameText.setString("Thystame:" + std::to_string(box->thystame));
    }

    renderTexture.draw(foodText);
    renderTexture.draw(linemateText);
    renderTexture.draw(deraumereText);
    renderTexture.draw(siburText);
    renderTexture.draw(mendianeText);
    renderTexture.draw(phirasText);
    renderTexture.draw(thystameText);

    renderTexture.draw(title);

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

    _drawables.foodText.setFont(assets.font);
    _drawables.linemateText.setFont(assets.font);
    _drawables.deraumereText.setFont(assets.font);
    _drawables.siburText.setFont(assets.font);
    _drawables.mendianeText.setFont(assets.font);
    _drawables.phirasText.setFont(assets.font);
    _drawables.thystameText.setFont(assets.font);

    _drawables.title.setFont(assets.font);
    _drawables.title.setString("Selected Box Info");
}

zappy::BoxInfo::~BoxInfo() = default;

void zappy::BoxInfo::setDisplaySize(sf::Vector2f &size)
{
    _drawables.background.setSize(size);
    _drawables.renderTexture.create(size.x, size.y);
    _drawables.view = sf::View(sf::FloatRect(0, 0, size.x, size.y));

    _drawables.food.setPosition(size.x / 4.5, size.y / 9 + size.y / 14);
    _drawables.linemate.setPosition(size.x / 4.5, size.y / 9 * 2 + size.y / 14);
    _drawables.deraumere.setPosition(size.x / 4.5, size.y / 9 * 3 + size.y / 14);
    _drawables.sibur.setPosition(size.x / 4.5, size.y / 9 * 4 + size.y / 14);
    _drawables.mendiane.setPosition(size.x / 4.5, size.y / 9 * 5 + size.y / 14);
    _drawables.phiras.setPosition(size.x / 4.5, size.y / 9 * 6 + size.y / 14);
    _drawables.thystame.setPosition(size.x / 4.5, size.y / 9 * 7 + size.y / 14);

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

    _drawables.foodText.setCharacterSize(size.y / 9 / 4);
    _drawables.linemateText.setCharacterSize(size.y / 9 / 4);
    _drawables.deraumereText.setCharacterSize(size.y / 9 / 4);
    _drawables.siburText.setCharacterSize(size.y / 9 / 4);
    _drawables.mendianeText.setCharacterSize(size.y / 9 / 4);
    _drawables.phirasText.setCharacterSize(size.y / 9 / 4);
    _drawables.thystameText.setCharacterSize(size.y / 9 / 4);

    _drawables.foodText.setPosition(size.x / 4.5 * 2, size.y / 9 + size.y / 14);
    _drawables.linemateText.setPosition(size.x / 4.5 * 2, size.y / 9 * 2 + size.y / 14);
    _drawables.deraumereText.setPosition(size.x / 4.5 * 2, size.y / 9 * 3 + size.y / 14);
    _drawables.siburText.setPosition(size.x / 4.5 * 2, size.y / 9 * 4 + size.y / 14);
    _drawables.mendianeText.setPosition(size.x / 4.5 * 2, size.y / 9 * 5 + size.y / 14);
    _drawables.phirasText.setPosition(size.x / 4.5 * 2, size.y / 9 * 6 + size.y / 14);
    _drawables.thystameText.setPosition(size.x / 4.5 * 2, size.y / 9 * 7 + size.y / 14);

    _drawables.title.setCharacterSize(size.x / 6 / 2);
    _drawables.title.setPosition(size.x / 2 - _drawables.title.getGlobalBounds().width / 2, 0);
}

void zappy::BoxInfo::setDisplayPosition(sf::Vector2f &position)
{
    _drawables.background.setPosition(position);
    _drawables.sprite.setPosition(position);
}

void zappy::BoxInfo::updateDisplay()
{
    _drawables.updateDisplay(_box);
}

void zappy::BoxInfo::setBox(std::shared_ptr<Box> box)
{
    _box = box;
}

void zappy::BoxInfo::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(this->_drawables.background, states);
    target.draw(this->_drawables.sprite, states);
}
