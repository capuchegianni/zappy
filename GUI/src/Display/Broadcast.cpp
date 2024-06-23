/*
** EPITECH PROJECT, 2024
** Broadcast.cpp
** File description:
** zappy_gui
*/

#include "Broadcast.hpp"

zappy::BroadcastDrawables::BroadcastDrawables() : duration(0) {}

zappy::BroadcastDrawables::~BroadcastDrawables() = default;

zappy::Broadcast::Broadcast(double duration, std::size_t x, std::size_t y, const std::string &message, Assets &assets) : x(x), y(y)
{
    _drawables.duration = duration;

    _drawables.message.setString(message);
    _drawables.message.setFont(assets.font);
    _drawables.message.setCharacterSize(20);
    _drawables.message.setFillColor(sf::Color::Black);

    _drawables.center.setTexture(assets.bubbleCenterTexture);
    _drawables.leftSide.setTexture(assets.bubbleLeftTexture);
    _drawables.rightSide.setTexture(assets.bubbleRightTexture);
    _drawables.fill1.setTexture(assets.bubbleFillTexture);
    _drawables.fill2.setTexture(assets.bubbleFillTexture);

    sf::FloatRect size = _drawables.message.getGlobalBounds();

    _drawables.message.setOrigin(size.width / 2, size.height / 2);
    _drawables.center.setOrigin(_drawables.center.getTexture()->getSize().x / 2, _drawables.center.getTexture()->getSize().y / 2);
    _drawables.leftSide.setOrigin(_drawables.leftSide.getTexture()->getSize().x, _drawables.leftSide.getTexture()->getSize().y / 2);
    _drawables.rightSide.setOrigin(0, _drawables.rightSide.getTexture()->getSize().y / 2);
    _drawables.fill1.setOrigin(_drawables.fill1.getTexture()->getSize().x / 2, _drawables.fill1.getTexture()->getSize().y / 2);
    _drawables.fill2.setOrigin(_drawables.fill2.getTexture()->getSize().x / 2, _drawables.fill2.getTexture()->getSize().y / 2);

    _drawables.message.setPosition(0, 0);
    _drawables.center.setPosition(0, 0);
    _drawables.leftSide.setPosition(-size.width / 2, 0);
    _drawables.rightSide.setPosition(size.width / 2, 0);

    _drawables.fill1.setPosition(-size.width / 2, 0);
    _drawables.fill2.setPosition(size.width / 2, 0);

    _drawables.fill1.setScale(size.width / _drawables.fill1.getTexture()->getSize().x, 1);
    _drawables.fill2.setScale(size.width / _drawables.fill2.getTexture()->getSize().x, 1);

    _drawables.view = sf::View(sf::FloatRect(-size.width / 2 - _drawables.leftSide.getTexture()->getSize().x, -_drawables.center.getTexture()->getSize().y / 2, size.width + _drawables.leftSide.getTexture()->getSize().x + _drawables.rightSide.getTexture()->getSize().x, _drawables.center.getTexture()->getSize().y));

    _drawables.renderTexture.setView(_drawables.view);
    _drawables.renderTexture.create(size.width + _drawables.leftSide.getTexture()->getSize().x + _drawables.rightSide.getTexture()->getSize().x, _drawables.center.getTexture()->getSize().y);

    _drawables.renderTexture.clear(sf::Color::Transparent);
    _drawables.renderTexture.draw(_drawables.leftSide);
    _drawables.renderTexture.draw(_drawables.rightSide);
    _drawables.renderTexture.draw(_drawables.fill1);
    _drawables.renderTexture.draw(_drawables.fill2);
    _drawables.renderTexture.draw(_drawables.center);
    _drawables.renderTexture.draw(_drawables.message);

    _drawables.renderTexture.display();

    _drawables.sprite.setTexture(_drawables.renderTexture.getTexture(), true);

    _drawables.clock.restart();
}

zappy::Broadcast::~Broadcast() = default;

void zappy::Broadcast::updateDisplay(zappy::render3d::Camera &camera)
{
    float scale = camera.unitaryPixelsSize / _drawables.sprite.getTexture()->getSize().y;

    _drawables.sprite.setScale(scale, scale);
}

double zappy::Broadcast::getElapsedTimeSeconds() const
{
    return _drawables.clock.getElapsedTime().asSeconds();
}

void zappy::Broadcast::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(_drawables.sprite, states);
}
