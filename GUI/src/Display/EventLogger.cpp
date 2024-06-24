/*
** EPITECH PROJECT, 2024
** EventLogger.cpp
** File description:
** zappy_gui
*/

#include "EventLogger.hpp"

zappy::EventLoggerDrawables::EventLoggerDrawables(sf::Font &font) : _font(font)
{
    background.setFillColor(sf::Color(32, 32, 32, 255));
    background.setOutlineColor(sf::Color::Black);
    background.setOutlineThickness(4);
}

zappy::EventLoggerDrawables::~EventLoggerDrawables() = default;

void zappy::EventLoggerDrawables::log(std::string &log)
{
    mutex.lock();
    if (logs.size() >= max_logs)
        logs.erase(logs.begin());

    auto text = std::make_unique<sf::Text>(log, _font, logHeight);
    text->setFillColor(sf::Color::White);
    text->setPosition(textOrigin);

    for (auto &log : logs) {
        log->move(0, logHeight);
    }

    logs.push_back(std::move(text));

    if (logs.size() > max_logs) {
        logs.erase(logs.begin());
    }
    mutex.unlock();
}

zappy::EventLogger::EventLogger(std::size_t max_logs, Assets &assets) : _drawables(assets.font)
{
    _drawables.max_logs = max_logs;
}

zappy::EventLogger::~EventLogger() = default;

void zappy::EventLogger::log(std::string log)
{
    _drawables.log(log);
}

void zappy::EventLogger::clearLogs()
{
    _drawables.logs.clear();
}

void zappy::EventLogger::setDisplaySize(sf::Vector2f &size)
{
    _drawables.background.setSize(size);

    _drawables.logHeight = size.x / 25;

    std::size_t i = 0;
    for (auto &log : _drawables.logs) {
        log->setPosition(_drawables.textOrigin + sf::Vector2f(0, _drawables.logHeight * i));
        log->setCharacterSize(_drawables.logHeight);
        i++;
    }
}

void zappy::EventLogger::setDisplayPosition(sf::Vector2f &position)
{
    _drawables.background.setPosition(position);
    _drawables.textOrigin = position;

    std::size_t i = 0;
    for (auto &log : _drawables.logs) {
        log->setPosition(_drawables.textOrigin + sf::Vector2f(0, _drawables.logHeight * i));
        log->setCharacterSize(_drawables.logHeight);
        i++;
    }
}

void zappy::EventLogger::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(_drawables.background, states);

    for (const auto &log : _drawables.logs) {
        target.draw(*log, states);
    }
}

void zappy::EventLogger::lock()
{
    _drawables.mutex.lock();
}

void zappy::EventLogger::unlock()
{
    _drawables.mutex.unlock();
}
