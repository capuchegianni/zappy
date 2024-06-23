/*
** EPITECH PROJECT, 2024
** TeamsInfo.cpp
** File description:
** zappy_gui
*/

#include "TeamsInfo.hpp"

zappy::TeamsInfoDrawables::TeamsInfoDrawables(sf::Font &font) : font(font)
{
    background.setFillColor(sf::Color(32, 32, 32, 255));
    background.setOutlineColor(sf::Color::Black);
    background.setOutlineThickness(4);
}

zappy::TeamsInfoDrawables::~TeamsInfoDrawables() = default;

void zappy::TeamsInfoDrawables::updateDisplay()
{
    renderTexture.clear(sf::Color::Transparent);

    for (std::size_t i = 0; i < teams.size(); i++)
    {
        renderTexture.draw(teamsbg[i]);
        renderTexture.draw(teams[i]);
        renderTexture.draw(teamsColor[i]);
    }

    for (std::size_t i = 0; i < players.size(); i++)
    {
        renderTexture.draw(playersbg[i]);
        renderTexture.draw(players[i]);
    }

    renderTexture.display();
    sprite.setTexture(renderTexture.getTexture(), true);
}

zappy::TeamsInfo::TeamsInfo(Assets &assets) : _drawables(assets.font) {}

zappy::TeamsInfo::~TeamsInfo() = default;

void zappy::TeamsInfo::setDisplaySize(sf::Vector2f &size)
{
    _drawables.background.setSize(size);
    _drawables.teamHeight = size.x / 10 ;
    _drawables.renderTexture.create(size.x, size.y);
}

void zappy::TeamsInfo::setDisplayPosition(sf::Vector2f &position)
{
    _drawables.background.setPosition(position);
    _drawables.sprite.setPosition(position);
}

void zappy::TeamsInfo::updateDisplay()
{
    _drawables.updateDisplay();
}

void zappy::TeamsInfo::updateTeams(std::vector<Team> &teams)
{
    _drawables.teams.clear();
    _drawables.teams.reserve(teams.size());

    for (auto &team : teams)
    {
        sf::Text text(team.name, _drawables.font, _drawables.teamHeight * 1 / 3);
        text.setFillColor(sf::Color::White);
        text.setOrigin(0, text.getGlobalBounds().height / 2);

        _drawables.teams.push_back(text);
    }

    if (_drawables.selectedTeam >= teams.size())
        _drawables.selectedTeam = 0;

    _drawables.teamsbg.clear();
    _drawables.teamsbg.reserve(teams.size());

    _drawables.teamsColor.clear();
    _drawables.teamsColor.reserve(teams.size());

    for (std::size_t i = 0; i < teams.size(); i++)
    {
        sf::RectangleShape rect(sf::Vector2f(_drawables.background.getSize().x / 2, _drawables.teamHeight));
        rect.setPosition(sf::Vector2f(0, i * _drawables.teamHeight));

        if (i == _drawables.selectedTeam)
            rect.setFillColor(sf::Color(128, 128, 128, 255));
        else
            rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineColor(sf::Color::Black);
        rect.setOutlineThickness(2);

        _drawables.teamsbg.push_back(rect);

        sf::CircleShape circle(_drawables.teamHeight / 4);
        circle.setOrigin(circle.getRadius(), circle.getRadius());
        circle.setPosition(sf::Vector2f(_drawables.teamHeight / 3.5, i * _drawables.teamHeight + _drawables.teamHeight / 2));
        circle.setFillColor(teams[i].color);
        circle.setOutlineColor(sf::Color::Black);
        circle.setOutlineThickness(3);

        _drawables.teamsColor.push_back(circle);

        _drawables.teams[i].setPosition(sf::Vector2f(_drawables.teamHeight / 3.5 * 2.5, i * _drawables.teamHeight + _drawables.teamHeight / 2));
    }

    _drawables.playersbg.clear();
    _drawables.players.clear();

    if (teams[_drawables.selectedTeam].players.size() > 0)
    {
        _drawables.playersbg.reserve(teams[_drawables.selectedTeam].players.size());
        _drawables.players.reserve(teams[_drawables.selectedTeam].players.size());

        for (std::size_t i = 0; i < teams[_drawables.selectedTeam].players.size(); i++)
        {
            sf::RectangleShape rect(sf::Vector2f(_drawables.background.getSize().x / 2, _drawables.teamHeight));
            rect.setPosition(sf::Vector2f(_drawables.background.getSize().x / 2, i * _drawables.teamHeight));

            if (i == _drawables.selectedPlayer)
                rect.setFillColor(sf::Color(128, 128, 128, 255));
            else
                rect.setFillColor(sf::Color::Transparent);
            rect.setOutlineColor(sf::Color::Black);
            rect.setOutlineThickness(2);

            _drawables.playersbg.push_back(rect);

            sf::Text text("<" + std::to_string(teams[_drawables.selectedTeam].players[i]->id) + ">", _drawables.font, _drawables.teamHeight * 1 / 3);
            text.setFillColor(sf::Color::White);
            text.setOrigin(0, text.getGlobalBounds().height / 2);
            text.setPosition(sf::Vector2f(_drawables.background.getSize().x / 2 + _drawables.teamHeight / 3.5 * 2.5, i * _drawables.teamHeight + _drawables.teamHeight / 2));

            _drawables.players.push_back(text);
        }
    }
}

void zappy::TeamsInfo::selectTeam(sf::Vector2f &mousePos)
{
    sf::Vector2f localPos = mousePos - _drawables.background.getPosition();

    for (std::size_t i = 0; i < _drawables.teams.size(); i++)
    {
        sf::FloatRect rect = _drawables.teamsbg[i].getGlobalBounds();

        if (rect.contains(localPos))
        {
            _drawables.selectedTeam = i;
            return;
        }
    }

    for (std::size_t i = 0; i < _drawables.players.size(); i++)
    {
        sf::FloatRect rect = _drawables.playersbg[i].getGlobalBounds();

        if (rect.contains(localPos))
        {
            _drawables.selectedPlayer = i;
            return;
        }
    }
}

void zappy::TeamsInfo::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(_drawables.background);
    target.draw(_drawables.sprite);
}
