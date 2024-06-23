/*
** EPITECH PROJECT, 2024
** Map.hpp
** File description:
** zappy_gui
*/

#pragma once

#include <string>
#include <mutex>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include "Box.hpp"
#include "../Display/Assets.hpp"
#include "../Characters/Team.hpp"
#include "../Display/SceneData.hpp"
#include "../Characters/Team.hpp"
#include "../Display/Broadcast.hpp"

namespace zappy
{
    class MapDrawables
    {
        public:
            MapDrawables(Assets &assets, math::Vector3D mapSize);
            ~MapDrawables();

            void updateDisplay();

            SceneData sceneData;

            sf::RenderTexture renderTexture;
            sf::Texture texture;
            sf::Sprite sprite;
            sf::View view;
            sf::RectangleShape rect;
            sf::Sprite compass;
            sf::Sprite selection;
    };

    class Map : public sf::Drawable
    {
        public:
            Map(Assets &assets);
            Map(std::size_t width, std::size_t height, Assets &assets);
            ~Map() override;

            class MapError : public std::exception
            {
                public:
                    MapError(std::string const &message) : _message(message) {}
                    const char *what() const noexcept override { return _message.c_str(); }
                private:
                    std::string _message;
            };

            std::shared_ptr<Box> &operator()(std::size_t x, std::size_t y);
            std::shared_ptr<Trantorien> getPlayerById(std::size_t id);
            void addPlayer(const std::shared_ptr<Trantorien>& player, std::string &team);
            void removePlayerById(std::size_t id);
            void movePlayerById(std::size_t x, std::size_t y, std::size_t id);

            void updateEntities();
            void updateTiles();
            void updateDirectionUI();
            void updateDisplay();
            Team &getTeam(std::string &name);
            void addTeam(std::string &name);

            MapDrawables sceneDate;
            void addEgg(std::size_t x, std::size_t y, std::size_t id, std::string &team);
            void removeEggById(std::size_t id);

            void setDisplaySize(sf::Vector2f &size);
            void setDisplayPosition(sf::Vector2f &position);

            std::vector<std::pair<double, sf::Sprite>> getPlayersSprites(render3d::Camera &camera);

            void updateSelection();

            void setTimeUnit(int timeUnit);
            int getTimeUnit() const;

            void broadcast(std::size_t playerId, const std::string &message);

            std::vector<Team> &getTeams();

            math::Point3D selectedBox = {0, 0, 0};

            std::mutex mutex;
        private:
            std::vector<std::vector<std::shared_ptr<Box>>> _map;
            std::size_t _getPlayerIndexById(std::size_t id);

            std::vector<std::shared_ptr<Trantorien>> _players = {};

            std::vector<std::unique_ptr<Broadcast>> _broadcasts = {};

            Assets &_assets;
            void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

            std::vector<Team> _teams = {};
            int _timeUnit = 0;
    };
}
