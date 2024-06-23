/*
** EPITECH PROJECT, 2024
** TeamsInfo.hpp
** File description:
** zappy_gui
*/

#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "../Characters/Team.hpp"

namespace zappy
{
    class TeamsInfoDrawables
    {
        public:
            TeamsInfoDrawables(sf::Font &font);
            ~TeamsInfoDrawables();

            void updateDisplay();

            sf::RectangleShape background;
            std::vector<sf::RectangleShape> teamsbg;
            std::vector<sf::CircleShape> teamsColor;
            std::vector<sf::Text> teams;

            std::vector<sf::RectangleShape> playersbg;
            std::vector<sf::Text> players;

            sf::RenderTexture renderTexture;
            sf::Sprite sprite;

            float scrollPos = 0;
            float teamHeight = 0;

            std::size_t selectedTeam = 0;
            std::size_t selectedPlayer = 0;

            std::size_t selectedPlayerID = 0;

            sf::Font &font;
    };

    class TeamsInfo : public sf::Drawable
    {
        public:
            TeamsInfo(Assets &assets);
            ~TeamsInfo();

            void setDisplaySize(sf::Vector2f &size);
            void setDisplayPosition(sf::Vector2f &position);
            void updateDisplay();

            void updateTeams(std::vector<Team> &teams);
            void selectTeam(sf::Vector2f &mousePos);

            std::size_t getSelectedPlayer() const;

        private:
            void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

            TeamsInfoDrawables _drawables;
    };
}
