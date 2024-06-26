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
            _map[i].push_back(std::make_shared<Box>(i, j, sceneDate.sceneData, _assets));
        }
    }

    sceneDate.rect.setFillColor(sf::Color(64, 64, 255, 255));
    sceneDate.rect.setOutlineColor(sf::Color::Black);
    sceneDate.rect.setOutlineThickness(4);
}

zappy::Map::~Map() = default;

std::shared_ptr<zappy::Box> &zappy::Map::operator()(std::size_t x, std::size_t y)
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
    for (auto it = _players.begin(); it != _players.end(); it++) {
        if ((*it)->id == id) {
            _players.erase(it);
            std::cout << "Player " << id << " removed from list" << std::endl;
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
            std::vector<std::pair<double, sf::Sprite>> tileSprites = box->getObjectsSprites(sceneDate.sceneData.camera);
            allSprites.insert(allSprites.end(), tileSprites.begin(), tileSprites.end());
        }
    }

    std::sort(allSprites.begin(), allSprites.end(), [](const std::pair<double, sf::Sprite> &a, const std::pair<double, sf::Sprite> &b) {
        return a.first < b.first;
    });

    for (auto &player : _players) {
        sceneDate.renderTexture.draw(*player);
    }

    mutex.lock();
    for (auto &team : _teams) {
        for (auto &egg : team.eggs) {
            egg->updateDisplay(sceneDate.sceneData.camera);
            sceneDate.renderTexture.draw(*egg);
        }
    }
    mutex.unlock();

    for (auto &sprite : allSprites) {
        sceneDate.renderTexture.draw(sprite.second);
    }

    mutex.lock();
    for (auto it = _broadcasts.begin(); it != _broadcasts.end();)
    {
        if ((*it)->getElapsedTimeSeconds() > (*it)->duration)
        {
            it = _broadcasts.erase(it);
        }
        else
        {
            it++;
        }
    }

    for (auto &broadcast : _broadcasts) {
        broadcast->updateDisplay(sceneDate.sceneData.camera);
        sceneDate.renderTexture.draw(*broadcast);
    }
    mutex.unlock();
}

void zappy::Map::updateTiles()
{
    for (auto &row : _map) {
        for (auto &box : row) {
            box->updateSprite();
            sceneDate.sceneData.camera.directionBackup = sceneDate.sceneData.camera.direction;
            sceneDate.sceneData.camera.unitaryPixelsSizeBackup = sceneDate.sceneData.camera.unitaryPixelsSize;
            sceneDate.renderTexture.draw(*box);
        }
    }

    sceneDate.selection.setTexture(sceneDate.sceneData.selectionTile.getTexture(), true);
    sceneDate.selection.setOrigin(sceneDate.selection.getTexture()->getSize().x / 2, sceneDate.selection.getTexture()->getSize().y / 2);
    sceneDate.selection.setPosition(sceneDate.sceneData.camera.displayUnitaryX.x * selectedBox.x + sceneDate.sceneData.camera.displayUnitaryY.x * selectedBox.y + sceneDate.sceneData.camera.centerX * sceneDate.sceneData.camera.displayUnitaryX.x + sceneDate.sceneData.camera.displayUnitaryY.x * sceneDate.sceneData.camera.centerY + sceneDate.sceneData.camera.displayUnitaryZ.x * sceneDate.sceneData.camera.centerZ,
                                    sceneDate.sceneData.camera.displayUnitaryX.y * selectedBox.x + sceneDate.sceneData.camera.displayUnitaryY.y * selectedBox.y + sceneDate.sceneData.camera.centerX * sceneDate.sceneData.camera.displayUnitaryX.y + sceneDate.sceneData.camera.displayUnitaryY.y * sceneDate.sceneData.camera.centerY + sceneDate.sceneData.camera.displayUnitaryZ.y * sceneDate.sceneData.camera.centerZ);
    sceneDate.renderTexture.draw(sceneDate.selection);
}

void zappy::Map::updateDirectionUI()
{
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
    try {
        getTeam(name);
    } catch (Map::MapError &e) {
        _teams.emplace_back(name, _assets);
    }
}

void zappy::Map::addEgg(std::size_t x, std::size_t y, std::size_t id, std::string &team)
{
    mutex.lock();
    Team &storedTeam = getTeam(team);
    storedTeam.addEgg(std::make_shared<Egg>(x, y, id, team));
    mutex.unlock();
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

void zappy::Map::updateSelection()
{
    // round camera position to nearest integer
    math::Point3D cameraPosition = math::Point3D(-sceneDate.sceneData.camera.centerX, -sceneDate.sceneData.camera.centerY, 0);
    math::Point3D roundedCameraPosition = math::Point3D(round(cameraPosition.x), round(cameraPosition.y), 0);

    if (roundedCameraPosition.x < 0 || roundedCameraPosition.y < 0 || roundedCameraPosition.x >= _map.size() || roundedCameraPosition.y >= _map[0].size())
        return;

    selectedBox.x = roundedCameraPosition.x;
    selectedBox.y = roundedCameraPosition.y;
}

void zappy::Map::setTimeUnit(int timeUnit) {
    if (timeUnit < 0)
        throw Map::MapError("Time unit must be positive");
    this->_timeUnit = timeUnit;
}

int zappy::Map::getTimeUnit() const {
    return this->_timeUnit;
}

void zappy::Map::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sceneDate.rect, states);
    target.draw(sceneDate.sprite, states);
}

std::vector<zappy::Team> &zappy::Map::getTeams()
{
    return _teams;
}

void zappy::Map::broadcast(std::size_t playerId, const std::string &message)
{
    std::shared_ptr<Trantorien> player = getPlayerById(playerId);

    double duration = 1;

    double x = player->x;
    double y = player->y;
    double z = player->getSprite().getGlobalBounds().height;

    if (_broadcasts.size() > 50)
    {
        _broadcasts.erase(_broadcasts.begin());
    }
    _broadcasts.push_back(std::make_unique<Broadcast>(duration, x, y, z, player->color, message, _assets));
}
