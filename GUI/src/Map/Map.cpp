/*
** EPITECH PROJECT, 2024
** Map.cpp
** File description:
** zappy_gui
*/

#include "Map.hpp"

zappy::MapDrawables::MapDrawables(zappy::Assets &assets, math::Vector3D mapSize) : sceneData(assets)
{
    sceneData.camera.rotate(math::Vector3D(-45, 0, -45));
    sceneData.camera.centerX = -mapSize.x / 2;
    sceneData.camera.centerY = -mapSize.y / 2;
    sceneData.camera.centerZ = mapSize.z / 2;

    view = sf::View(sf::FloatRect(-250, -250, 500, 500));
    renderTexture.create(500, 500);
    renderTexture.setView(view);
}

void zappy::MapDrawables::updateDisplay()
{
    for (auto &tile : sceneData.tiles) {
        tile->computeTileImage(sceneData.camera);
    }

    render3d::Camera compassCamera = sceneData.camera;
    compassCamera.unitaryPixelsSize = 130;

    sceneData.compassTile.computeTileImage(compassCamera);
    sceneData.selectionTile.computeTileImage(sceneData.camera);
}

zappy::MapDrawables::~MapDrawables() = default;

zappy::Map::Map(Assets &assets) : Map(10, 10, assets) {}

zappy::Map::Map(std::size_t width, std::size_t height, Assets &assets) : sceneDate(assets, math::Vector3D(width, height, 0)), _assets(assets)
{
    _map.reserve(width);

    for (std::size_t i = 0; i < width; i++)
    {
        _map.push_back({});
        _map[i].reserve(height);

        for (std::size_t j = 0; j < height; j++)
        {
            _map[i].push_back(Box(i, j, sceneDate.sceneData, _assets));
        }
    }

    sceneDate.rect.setFillColor(sf::Color(64, 64, 255, 255));
    sceneDate.rect.setOutlineColor(sf::Color::Black);
    sceneDate.rect.setOutlineThickness(4);
}

zappy::Map::~Map() = default;

zappy::Box &zappy::Map::operator()(std::size_t x, std::size_t y)
{
    if (x >= _map.size() || y >= _map[0].size())
        throw Map::MapError("Out of bounds");

    return _map[x][y];
}

std::shared_ptr<zappy::Trantorien> zappy::Map::getPlayerById(std::size_t id)
{
    for (auto &team : _teams) {
        try {
            return team.getPlayerById(id);
        } catch (Team::TeamError &e) {
            continue;
        }
    }

    throw Map::MapError("Player " + std::to_string(id) + " not found");
}

void zappy::Map::addPlayer(const std::shared_ptr<Trantorien>& player, std::string &team)
{
    Team &storedTeam = getTeam(team);
    player->team = team;

    player->color = storedTeam.color;
    _players.push_back(player);
    storedTeam.addPlayer(player);
}

void zappy::Map::removePlayerById(std::size_t id)
{
    std::shared_ptr<Trantorien> player = getPlayerById(id);
    zappy::Team &team = getTeam(player->team);

    team.removePlayerById(id);
    for (std::size_t i = 0; i < _players.size(); i++) {
        if (_players[i]->id == id) {
            _players.erase(_players.begin() + i);
            return;
        }
    }
}

std::size_t zappy::Map::_getPlayerIndexById(std::size_t id)
{
    std::shared_ptr<zappy::Trantorien> player = getPlayerById(id);
    zappy::Team &team = getTeam(getPlayerById(id)->team);

    return team.getPlayerIndexById(id);
}

void zappy::Map::movePlayerById(std::size_t x, std::size_t y, std::size_t id)
{
    std::shared_ptr<Trantorien> player = getPlayerById(id);

    if (player == nullptr)
        throw Map::MapError("Player not found");

    player->x = x;
    player->y = y;
}

void zappy::Map::updateEntities()
{
    std::vector<std::pair<double, sf::Sprite>> allSprites = getPlayersSprites(sceneDate.sceneData.camera);

    for (auto &tile : _map) {
        for (auto &box : tile) {
            std::vector<std::pair<double, sf::Sprite>> tileSprites = box.getObjectsSprites(sceneDate.sceneData.camera);
            allSprites.insert(allSprites.end(), tileSprites.begin(), tileSprites.end());
        }
    }

    std::sort(allSprites.begin(), allSprites.end(), [](const std::pair<double, sf::Sprite> &a, const std::pair<double, sf::Sprite> &b) {
        return a.first < b.first;
    });

    for (auto &player : _players) {
        sceneDate.renderTexture.draw(*player);
    }

    for (auto &team : _teams) {
        for (auto &egg : team.eggs) {
            egg->updateDisplay(sceneDate.sceneData.camera);
            sceneDate.renderTexture.draw(*egg);
        }
    }

    for (auto &sprite : allSprites) {
        sceneDate.renderTexture.draw(sprite.second);
    }
}

void zappy::Map::updateTiles()
{
    for (auto &row : _map) {
        for (auto &box : row) {
            box.updateSprite();
            sceneDate.sceneData.camera.directionBackup = sceneDate.sceneData.camera.direction;
            sceneDate.sceneData.camera.unitaryPixelsSizeBackup = sceneDate.sceneData.camera.unitaryPixelsSize;
            sceneDate.renderTexture.draw(box);
        }
    }
}

void zappy::Map::updateDirectionUI()
{
    sceneDate.selection.setTexture(sceneDate.sceneData.selectionTile.getTexture(), true);
    sceneDate.selection.setOrigin(sceneDate.selection.getTexture()->getSize().x / 2, sceneDate.selection.getTexture()->getSize().y / 2);
    sceneDate.selection.setPosition(sceneDate.sceneData.camera.displayUnitaryX.x * _selected.x + sceneDate.sceneData.camera.displayUnitaryY.x * _selected.y + sceneDate.sceneData.camera.centerX * sceneDate.sceneData.camera.displayUnitaryX.x + sceneDate.sceneData.camera.displayUnitaryY.x * sceneDate.sceneData.camera.centerY + sceneDate.sceneData.camera.displayUnitaryZ.x * sceneDate.sceneData.camera.centerZ,
                       sceneDate.sceneData.camera.displayUnitaryX.y * _selected.x + sceneDate.sceneData.camera.displayUnitaryY.y * _selected.y + sceneDate.sceneData.camera.centerX * sceneDate.sceneData.camera.displayUnitaryX.y + sceneDate.sceneData.camera.displayUnitaryY.y * sceneDate.sceneData.camera.centerY + sceneDate.sceneData.camera.displayUnitaryZ.y * sceneDate.sceneData.camera.centerZ);
    sceneDate.renderTexture.draw(sceneDate.selection);
    
    sceneDate.compass.setTexture(sceneDate.sceneData.compassTile.getTexture(), true);
    sceneDate.compass.setOrigin(sceneDate.compass.getTexture()->getSize().x / 2, sceneDate.compass.getTexture()->getSize().y / 2);
    sceneDate.compass.setPosition(80-sceneDate.rect.getSize().x / 2, 80-sceneDate.rect.getSize().y / 2);
    sceneDate.renderTexture.draw(sceneDate.compass);
}

void zappy::Map::updateDisplay()
{
    sceneDate.updateDisplay();
    sceneDate.renderTexture.clear(sf::Color::Transparent);

    updateTiles();
    updateEntities();
    updateDirectionUI();

    sceneDate.renderTexture.display();
    sceneDate.texture = sceneDate.renderTexture.getTexture();
    sceneDate.sprite.setTexture(sceneDate.texture, true);
}

zappy::Team &zappy::Map::getTeam(std::string &name)
{
    for (auto &team : _teams) {
        if (team.name == name)
            return team;
    }

    throw Map::MapError("Team " + name + " not found");
}

void zappy::Map::addTeam(std::string &name)
{
    _teams.emplace_back(name, _assets);
}

void zappy::Map::addEgg(std::size_t x, std::size_t y, std::size_t id, std::string &team)
{
    Team &storedTeam = getTeam(team);
    storedTeam.addEgg(std::make_shared<Egg>(x, y, id, team));
}

void zappy::Map::removeEggById(std::size_t id)
{
    for (auto &team : _teams) {
        try {
            team.removeEggById(id);
            return;
        } catch (Team::TeamError &e) {
            continue;
        }
    }

    throw Map::MapError("Egg " + std::to_string(id) + " not found");
}

void zappy::Map::setDisplaySize(sf::Vector2f &size)
{
    sceneDate.view = sf::View(sf::FloatRect(-(static_cast<float>(size.x) / 2), -(static_cast<float>(size.y) / 2),
                                            static_cast<float>(size.x), static_cast<float>(size.y)));
    sceneDate.renderTexture.create(size.x, size.y);
    sceneDate.renderTexture.setView(sceneDate.view);
    sceneDate.rect.setSize(size);
}

void zappy::Map::setDisplayPosition(sf::Vector2f &position)
{
    sceneDate.sprite.setPosition(position);
    sceneDate.rect.setPosition(position);
}

std::vector<std::pair<double, sf::Sprite>> zappy::Map::getPlayersSprites(zappy::render3d::Camera &camera)
{
    math::Point3D cameraPosition = math::Vector3D(camera.centerX - camera.direction.x * 10000, camera.centerY - camera.direction.y * 10000,
                                                  camera.centerZ - camera.direction.z * 10000);

    std::vector<std::pair<double, sf::Sprite>> playersSprites;

    for (auto &player : _players)
    {
        double distance = math::Point3D::distance(cameraPosition, math::Point3D(player->x, player->y, 0));
        player->updateDisplay(sceneDate.sceneData.camera);
        playersSprites.push_back({distance, player->getSprite()});
    }

    for (auto &team : _teams)
    {
        for (auto &egg : team.eggs)
        {
            egg->updateDisplay(camera);
            playersSprites.push_back(egg->getSprite(camera));
        }
    }

    return playersSprites;
}

void zappy::Map::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sceneDate.rect, states);
    target.draw(sceneDate.sprite, states);
}
