/*
** EPITECH PROJECT, 2024
** EventLogger.hpp
** File description:
** zappy_gui
*/

#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include <memory>

#include "Assets.hpp"

namespace zappy
{
    class EventLoggerDrawables
    {
        public:
            EventLoggerDrawables(sf::Font &font);
            ~EventLoggerDrawables();

            class EventLoggerDrawablesError : public std::exception
            {
                public:
                    EventLoggerDrawablesError(std::string const &message) : _message(message) {}
                    const char *what() const noexcept override { return _message.c_str(); }
                private:
                    std::string _message;
            };

            void log(std::string &log);

            sf::RectangleShape background;
            std::vector<std::unique_ptr<sf::Text>> logs;

            std::size_t max_logs = 10;
            float logHeight = 20;
            sf::Vector2f textOrigin = {0, 0};

        private:
            sf::Font _font;
    };

    class EventLogger : public sf::Drawable
    {
        public:
            EventLogger(std::size_t max_logs, Assets &assets);
            ~EventLogger() override;

            void log(std::string log);
            void clearLogs();

            void setDisplaySize(sf::Vector2f &size);
            void setDisplayPosition(sf::Vector2f &position);

        private:
            void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
            EventLoggerDrawables _drawables;
    };
}
