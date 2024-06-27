/*
** EPITECH PROJECT, 2024
** GUI/src/Communication/Communication.cpp
** File description:
** B-YEP-400-LIL-4-1-zappy-nicolas.pechart
*/

#include "Communication.hpp"
#include "../Display/BoxInfo.hpp"
#include "../Display/PlayerInfo.hpp"
#include "../Display/TeamsInfo.hpp"

#include <iostream>
#include <unordered_map>
#include <functional>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

zappy::Communication::Communication(int port, std::string host) : _port(port), _host(std::move(host)) {}

void zappy::Communication::updateTimeUnit(int timeUnit) {
    if (timeUnit < 0) {
        throw CommandError("Invalid time unit");
    }
    this->sendCommand("sst " + std::to_string(timeUnit));
}

std::string zappy::Communication::getLine() {
    std::string line;
    char c;
    std::size_t received;
    sf::Socket::Status status;
    while (this->_running) {
        status = this->_socket.receive(&c, 1, received);
        if (status == sf::Socket::Done && received > 0) {
            line += c;
            if (c == '\n') {
                break;
            }
        } else if (status == sf::Socket::NotReady) {
            continue;
        } else {
            throw CommunicationError("Failed to receive data from the server");
        }
    }
    if (!this->_running) {
        throw CommunicationError("Connection closed");
    }
    return line;
}

void zappy::Communication::sendCommand(std::string command) {
    if (this->_socket.getRemoteAddress() == sf::IpAddress::None) {
        throw CommunicationError("Not connected to the server");
    }
    command += "\n";
    std::size_t totalSent = 0;
    while (totalSent < command.size()) {
        std::size_t sent;
        sf::Socket::Status status = this->_socket.send(command.c_str() + totalSent, command.size() - totalSent, sent);
        if (status != sf::Socket::Done) {
            throw CommunicationError("Failed to send command to the server");
        }
        totalSent += sent;
    }
}

zappy::Communication::~Communication() {
    if (this->_socket.getRemoteAddress() != sf::IpAddress::None)
        this->_socket.disconnect();
}

void zappy::Communication::connect() {
    if (this->_socket.getRemoteAddress() != sf::IpAddress::None) {
        throw CommunicationError("Already connected to the server");
    }
    sf::Socket::Status status = this->_socket.connect(this->_host, this->_port);
    this->_socket.setBlocking(false);
    if (status != sf::Socket::Done) {
        throw CommunicationError("Unable to connect to the server");
    }
    std::string line;
    try {
        line = this->getLine();
    } catch (CommunicationError &e) {
        throw CommunicationError("Failed to connect to the server");
    }
    if (line != "WELCOME\n") {
        throw CommunicationError("Failed to connect to the server");
    }
    this->sendCommand("GRAPHIC");
}

void zappy::Communication::run() {
    if (this->_socket.getRemoteAddress() == sf::IpAddress::None) {
        this->connect();
    }
    std::vector<std::thread> threads;
    threads.emplace_back(&zappy::Communication::commandReceiver, this);
    threads.emplace_back(&zappy::Communication::automaticCommandSender, this);
    threads.emplace_back(&zappy::Communication::graphicalUserInterface, this);
    for (auto &thread : threads) {
        thread.join();
    }
}

void zappy::Communication::graphicalUserInterface() {
    int winwidth = 1920;
    int winheight = 1080;
    bool map_created = false;

    sf::RenderWindow window(sf::VideoMode(winwidth, winheight), "Zappy");

    int displayedFrameRate = 0;
    int frames = 0;
    sf::Clock frameRateClock;

    window.setFramerateLimit(60);

    sf::Event event;
    sf::Clock frameClock;
    int lastFrameTime = 0;

    frameClock.restart();

    sf::View view(sf::FloatRect(0, 0, static_cast<float>(winwidth), static_cast<float>(winheight)));

    zappy::BoxInfo boxInfo(assets);
    zappy::PlayerInfo playerInfo(assets);
    zappy::TeamsInfo teamsInfo(assets);

    // init window properly
    sf::Vector2f size = sf::Vector2f(winwidth / 2, winheight);
    sf::Vector2f position = sf::Vector2f(0, 0);
    view = sf::View(sf::FloatRect(0, 0, winwidth, winheight));

    sf::Vector2f boxPos(winwidth / 2 + 5, winheight / 2);
    sf::Vector2f boxSize(winwidth / 8 - 5, winheight / 2);

    sf::Vector2f loggerPos(winwidth / 2 + 5 + winheight / 4, 0);
    sf::Vector2f loggerSize(winwidth / 4 - 5, winheight);

    sf::Vector2f playerInfoPos(winwidth / 2 + event.size.width / 8 + 5, winheight / 2);
    sf::Vector2f playerInfoSize(winwidth / 8 - 5, winheight / 2);

    sf::Vector2f teamsInfoPos(winwidth / 2 + 5, 0);
    sf::Vector2f teamsInfoSize(winwidth / 4 - 5, winheight / 2);

    boxInfo.setDisplaySize(boxSize);
    boxInfo.setDisplayPosition(boxPos);
    playerInfo.setDisplaySize(playerInfoSize);
    playerInfo.setDisplayPosition(playerInfoPos);
    teamsInfo.setDisplaySize(teamsInfoSize);
    teamsInfo.setDisplayPosition(teamsInfoPos);
    eventLogger.setDisplayPosition(loggerPos);
    eventLogger.setDisplaySize(loggerSize);
    window.setView(view);

    std::size_t lastPlayerSelected = 0;

    while (window.isOpen())
    {
        if (frameClock.getElapsedTime().asMilliseconds() <= 1000 / 60) {
            continue;
        }
        if (map == nullptr) {
            continue;
        } else if (!map_created) {
            map->setDisplaySize(size);
            map->setDisplayPosition(position);
            map_created = true;
        }

        math::Vector3D movForward = map->sceneDate.sceneData.camera.direction * 0.01 * lastFrameTime;
        math::Vector3D movRight = map->sceneDate.sceneData.camera.right * 0.01 * lastFrameTime;

        if (window.hasFocus())
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            {
                map->sceneDate.sceneData.camera.centerX += movForward.x * lastFrameTime * 0.05;
                map->sceneDate.sceneData.camera.centerY += movForward.y * lastFrameTime * 0.05;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                map->sceneDate.sceneData.camera.centerX -= movForward.x * lastFrameTime * 0.05;
                map->sceneDate.sceneData.camera.centerY -= movForward.y * lastFrameTime * 0.05;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            {
                map->sceneDate.sceneData.camera.centerX += movRight.x * lastFrameTime * 0.05;
                map->sceneDate.sceneData.camera.centerY += movRight.y * lastFrameTime * 0.05;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                map->sceneDate.sceneData.camera.centerX -= movRight.x * lastFrameTime * 0.05;
                map->sceneDate.sceneData.camera.centerY -= movRight.y * lastFrameTime * 0.05;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && map->sceneDate.sceneData.camera.unitaryPixelsSize < 200)
            {
                map->sceneDate.sceneData.camera.unitaryPixelsSize += 1;
                map->sceneDate.sceneData.camera.rotate(math::Vector3D(0, 0, 0));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
                map->sceneDate.sceneData.camera.unitaryPixelsSize > 10)
            {
                map->sceneDate.sceneData.camera.unitaryPixelsSize -= 1;
                map->sceneDate.sceneData.camera.rotate(math::Vector3D(0, 0, 0));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                map->sceneDate.sceneData.camera.rotate(math::Vector3D(0, 0, 1 * lastFrameTime) * 0.1);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                map->sceneDate.sceneData.camera.rotate(math::Vector3D(0, 0, -1 * lastFrameTime * 0.1));
            }
        }

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                teamsInfo.selectTeam(mousePos);
                if (teamsInfo.getSelectedPlayer() != lastPlayerSelected)
                {
                    lastPlayerSelected = teamsInfo.getSelectedPlayer();
                    try
                    {
                        this->sendCommand("plv " + std::to_string(teamsInfo.getSelectedPlayer()));
                        this->sendCommand("pin " + std::to_string(teamsInfo.getSelectedPlayer()));
                    }
                    catch (std::exception &e)
                    {
                        eventLogger.log(e.what());
                    }
                }
            }

            if (event.type == sf::Event::Resized)
            {
                size = sf::Vector2f(event.size.width / 2, event.size.height);
                view = sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height));

                boxPos = sf::Vector2f(event.size.width / 2 + 5, event.size.height / 2);
                boxSize = sf::Vector2f(event.size.width / 8 - 5, event.size.height / 2);

                loggerPos = sf::Vector2f(event.size.width / 2 + 5 + event.size.width / 4, 0);
                loggerSize = sf::Vector2f(event.size.width / 4 - 5, event.size.height);

                playerInfoPos = sf::Vector2f(event.size.width / 2 + event.size.width / 8 + 5, event.size.height / 2);
                playerInfoSize = sf::Vector2f(event.size.width / 8 - 5, event.size.height / 2);

                teamsInfoPos = sf::Vector2f(event.size.width / 2 + 5, 0);
                teamsInfoSize = sf::Vector2f(event.size.width / 4 - 5, event.size.height / 2);

                boxInfo.setDisplaySize(boxSize);
                boxInfo.setDisplayPosition(boxPos);
                playerInfo.setDisplaySize(playerInfoSize);
                playerInfo.setDisplayPosition(playerInfoPos);
                teamsInfo.setDisplaySize(teamsInfoSize);
                teamsInfo.setDisplayPosition(teamsInfoPos);
                eventLogger.setDisplayPosition(loggerPos);
                eventLogger.setDisplaySize(loggerSize);
                (*map).setDisplaySize(size);
                window.setView(view);
            }

            if (event.type == sf::Event::KeyPressed)
            {
                bool sendTimeUnit = false;

                switch (event.key.code)
                {
                    case sf::Keyboard::Add:
                    case sf::Keyboard::F:
                        map->setTimeUnit(map->getTimeUnit() + 1);
                        sendTimeUnit = true;
                        break;
                    case sf::Keyboard::Subtract:
                    case sf::Keyboard::G:
                        if (map->getTimeUnit() >= 1)
                        {
                            map->setTimeUnit(map->getTimeUnit() - 1);
                            sendTimeUnit = true;
                        }
                        break;
                    default:
                        break;
                }

                if (sendTimeUnit)
                {
                    try
                    {
                        updateTimeUnit(map->getTimeUnit());
                    }
                    catch (std::exception &e)
                    {
                        eventLogger.log(e.what());
                    }
                }
            }
        }

        teamsInfo.updateTeams(map->getTeams());
        boxInfo.setBox((*map)(map->selectedBox.x, map->selectedBox.y));

        try
        {
            std::shared_ptr<zappy::Trantorien> selectedPlayer = map->getPlayerById(teamsInfo.getSelectedPlayer());
            _displayPlayerID = selectedPlayer->id;
            playerInfo.setPlayer(selectedPlayer);
        }
        catch (std::exception &e)
        {
            std::shared_ptr<zappy::Trantorien> selectedPlayer = nullptr;
            _displayPlayerID = 0;
            playerInfo.setPlayer(selectedPlayer);
        }

        teamsInfo.updateDisplay();
        map->updateSelection();
        map->updateDisplay();
        boxInfo.updateDisplay();
        playerInfo.updateDisplay();

        window.clear(sf::Color::Blue);
        window.draw(*map);

        eventLogger.lock();
        window.draw(eventLogger);
        eventLogger.unlock();

        window.draw(boxInfo);
        window.draw(playerInfo);
        window.draw(teamsInfo);
        window.display();
        lastFrameTime = frameClock.getElapsedTime().asMilliseconds();

        if (frameRateClock.getElapsedTime().asSeconds() >= 1)
        {
            displayedFrameRate = frames;
            frames = 0;
            frameRateClock.restart();
        }
        else
        {
            frames++;
        }

        window.setTitle("Zappy - FPS: " + std::to_string(displayedFrameRate) + " - Tickrate: " + std::to_string(map->getTimeUnit()));
        frameClock.restart();
    }
    this->_running = false;
}

void zappy::Communication::commandReceiver() {
    std::cout << "Starting Command Receiver\n";
    while (this->_running) {
        std::string line;
        try {
            line = this->getLine();
        } catch (CommunicationError &e) {
            std::cerr << e.what() << std::endl;
            this->_running = false;
            break;
        }
        std::string command = line.substr(0, line.find(' '));
        if (this->_commands.find(command) != this->_commands.end()) {
            std::vector<std::string> args;
            for (std::size_t i = line.find(' ') + 1; i < line.size(); i++) {
                std::string arg;
                while (line[i] != ' ' && line[i] != '\n') {
                    arg += line[i];
                    i++;
                }
                args.push_back(arg);
            }
            try {
                this->_commands[command](args);
            } catch (std::exception &e) {
                std::string commandCopy = line;
                commandCopy.erase(std::remove(commandCopy.begin(), commandCopy.end(), '\n'), commandCopy.end());
                std::cerr << command << ": " << e.what() << " (" << commandCopy << ")" << std::endl;
            }
        } else {
            std::cerr << command << ": Unknown command" << std::endl;
        }
    }
    std::cout << "Command Receiver Stopped\n";
}

void zappy::Communication::automaticCommandSender() {
    std::cout << "Starting Automatic Sender\n";
    try {
        this->sendCommand("msz");
        while (this->_running) {
            this->sendCommand("mct");
            try {
                if (this->map != nullptr) {
                    auto player = (*this->map).getPlayerById(this->_displayPlayerID);
                    if (player != nullptr) {
                        this->sendCommand("ppo " + std::to_string(this->_displayPlayerID));
                        this->sendCommand("pin " + std::to_string(this->_displayPlayerID));
                        this->sendCommand("plv " + std::to_string(this->_displayPlayerID));
                    }
                }
            } catch (Map::MapError &e) {}
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } catch (CommunicationError &e) {
        std::cerr << e.what() << std::endl;
        this->_running = false;
    }
    eventLogger.log("Disconnected from server");
    std::cout << "Automatic Sender Stopped\n";
}

void zappy::Communication::msz(std::vector<std::string> &args) {
    if (args.size() != 2) {
        throw CommandError("Invalid number of arguments");
    }
    if (this->map == nullptr) {
        this->map = std::make_shared<zappy::Map>(std::stoi(args[0]), std::stoi(args[1]), this->assets);
        try {
            this->sendCommand("tna");
            this->sendCommand("mct");
        } catch (CommunicationError &e) {
            std::cerr << e.what() << std::endl;
            this->_running = false;
        }
    }
}

void zappy::Communication::bct(std::vector<std::string> &args) {
    if (args.size() != 9)
        throw CommandError("Invalid number of arguments");
    if (this->map == nullptr)
        throw MapUninitialized();
    try {
        int x = std::stoi(args[0]);
        int y = std::stoi(args[1]);
        int food = std::stoi(args[2]);
        int linemate = std::stoi(args[3]);
        int deraumere = std::stoi(args[4]);
        int sibur = std::stoi(args[5]);
        int mendiane = std::stoi(args[6]);
        int phiras = std::stoi(args[7]);
        int thystame = std::stoi(args[8]);
        (*this->map)(x, y)->food = food;
        (*this->map)(x, y)->linemate = linemate;
        (*this->map)(x, y)->deraumere = deraumere;
        (*this->map)(x, y)->sibur = sibur;
        (*this->map)(x, y)->mendiane = mendiane;
        (*this->map)(x, y)->phiras = phiras;
        (*this->map)(x, y)->thystame = thystame;
    } catch (std::invalid_argument &e) {
        throw CommandError("Invalid arguments");
    } catch (Map::MapError &e) {
        throw CommandError("Out of bounds");
    } catch (std::exception &e) {
        throw CommandError("Unknown error");
    }
}

void zappy::Communication::tna(std::vector<std::string> &args) {
    std::cout << "Team " << args[0] << " added\n";
    if (args.size() != 1)
        throw CommandError("Invalid number of arguments");
    if (this->map == nullptr)
        throw MapUninitialized();
    std::string team = args[0];
    (*this->map).addTeam(team);
}

void zappy::Communication::pnw(std::vector<std::string> &args) {
    if (args.size() != 6)
        throw CommandError("Invalid number of arguments");
    if (this->map == nullptr)
        throw MapUninitialized();
    try {
        int id = std::stoi(args[0]);
        int x = std::stoi(args[1]);
        int y = std::stoi(args[2]);
        int direction = std::stoi(args[3]);
        int level = std::stoi(args[4]);
        std::string team = args[5];
        zappy::Trantorien trantorien(id);
        trantorien.x = x;
        trantorien.y = y;
        trantorien.direction = direction;
        trantorien.level = level;
        (*this->map).addPlayer(std::make_shared<zappy::Trantorien>(trantorien), team);
        this->eventLogger.log("Player " + std::to_string(id) + " joined team " + team);
    } catch (std::invalid_argument &e) {
        throw CommandError("Invalid arguments");
    } catch (Map::MapError &e) {
        throw CommandError("Team not found");
    } catch (std::exception &e) {
        throw CommandError("Unknown error");
    }
}

void zappy::Communication::ppo(std::vector<std::string> &args) {
    if (args.size() != 4)
        throw CommandError("Invalid number of arguments");
    if (this->map == nullptr)
        throw MapUninitialized();
    try {
        int id = std::stoi(args[0]);
        int x = std::stoi(args[1]);
        int y = std::stoi(args[2]);
        int direction = std::stoi(args[3]);
        (*this->map).getPlayerById(id)->direction = direction;
        (*this->map).movePlayerById(x, y, id);
    } catch (std::invalid_argument &e) {
        throw CommandError("Invalid arguments");
    } catch (Map::MapError &e) {
        throw CommandError("Player not found");
    } catch (std::exception &e) {
        throw CommandError("Unknown error");
    }
}

void zappy::Communication::plv(std::vector<std::string> &args) {
    if (args.size() != 2)
        throw CommandError("Invalid number of arguments");
    if (this->map == nullptr)
        throw MapUninitialized();
    try {
        int id = std::stoi(args[0]);
        int level = std::stoi(args[1]);
        (*this->map).getPlayerById(id)->level = level;
    } catch (std::invalid_argument &e) {
        throw CommandError("Invalid arguments");
    } catch (Map::MapError &e) {
        throw CommandError("Player not found");
    } catch (std::exception &e) {
        throw CommandError("Unknown error");
    }
}

void zappy::Communication::pin(std::vector<std::string> &args) {
    if (args.size() != 10)
        throw CommandError("Invalid number of arguments");
    if (this->map == nullptr)
        throw MapUninitialized();
    try {
        int id = std::stoi(args[0]);
        int x = std::stoi(args[1]);
        int y = std::stoi(args[2]);
        int food = std::stoi(args[3]);
        int linemate = std::stoi(args[4]);
        int deraumere = std::stoi(args[5]);
        int sibur = std::stoi(args[6]);
        int mendiane = std::stoi(args[7]);
        int phiras = std::stoi(args[8]);
        int thystame = std::stoi(args[9]);
        std::shared_ptr<zappy::Trantorien> player = (*this->map).getPlayerById(id);
        player->x = x;
        player->y = y;
        player->food = food;
        player->linemate = linemate;
        player->deraumere = deraumere;
        player->sibur = sibur;
        player->mendiane = mendiane;
        player->phiras = phiras;
        player->thystame = thystame;
    } catch (std::invalid_argument &e) {
        throw CommandError("Invalid arguments");
    } catch (Map::MapError &e) {
        throw CommandError("Player not found");
    } catch (std::exception &e) {
        throw CommandError("Unknown error");
    }
}

void zappy::Communication::pex(std::vector<std::string> &args) {
    if (args.size() != 1)
        throw CommandError("Invalid number of arguments");
    if (this->map == nullptr)
        throw MapUninitialized();
    try {
        int id = std::stoi(args[0]);
        this->sendCommand("ppo " + std::to_string(id));
        this->eventLogger.log("Player " + std::to_string(id) + " has been expelled");
    } catch (CommunicationError &e) {
        throw CommandError("Lost connection to the server");
    } catch (std::exception &e) {
        throw CommandError("Invalid arguments");
    }
}

void zappy::Communication::pbc(std::vector<std::string> &args) {
    if (args.size() < 2)
        throw CommandError("Invalid number of arguments");
    if (this->map == nullptr)
        throw MapUninitialized();
    try {
        int id = std::stoi(args[0]);
        std::string message;
        for (std::size_t i = 1; i < args.size(); i++) {
            message += args[i];
            if (i + 1 < args.size()) {
                message += " ";
            }
        }
        this->eventLogger.log("Player " + std::to_string(id) + " broadcasted: " + message);
        map->mutex.lock();
        (*this->map).broadcast(id, message);
        map->mutex.unlock();
    } catch (std::invalid_argument &e) {
        throw CommandError("Invalid arguments");
    } catch (std::exception &e) {
        throw CommandError("Unknown error");
    }
}

void zappy::Communication::pic(std::vector<std::string> &args) {
    if (args.size() < 4)
        throw CommandError("Invalid number of arguments");
    if (this->map == nullptr)
        throw MapUninitialized();
    try {
        int x = std::stoi(args[0]);
        int y = std::stoi(args[1]);
        int id = std::stoi(args[2]);
        std::vector<unsigned long> players;
        for (std::size_t i = 3; i < args.size(); i++) {
            try {
                auto player = (*this->map).getPlayerById(std::stoi(args[i]));
                if (player != nullptr) {
                    players.push_back(player->id);
                }
            } catch (std::invalid_argument &e) {
                throw CommandError("Invalid arguments");
            } catch (Map::MapError &e) {
                throw CommandError("Player not found");
            }
        }
        this->eventLogger.log("Incantation at " + std::to_string(x) + " " + std::to_string(y) + " started by player " + std::to_string(id));
        for (auto &player : players) {
            this->eventLogger.log("Player " + std::to_string(player) + " is participating in the incantation");
        }
    } catch (std::invalid_argument &e) {
        throw CommandError("Invalid arguments");
    } catch (Map::MapError &e) {
        throw CommandError("Player not found");
    } catch (std::exception &e) {
        throw CommandError("Unknown error");
    }
}

void zappy::Communication::pie(std::vector<std::string> &args) {
    if (args.size() != 3)
        throw CommandError("Invalid number of arguments");
    if (this->map == nullptr)
        throw MapUninitialized();
    try {
        int x = std::stoi(args[0]);
        int y = std::stoi(args[1]);
        int result = std::stoi(args[2]);
        if (result == 1) {
            this->eventLogger.log("Incantation at " + std::to_string(x) + " " + std::to_string(y) + " succeeded");
        } else {
            this->eventLogger.log("Incantation at " + std::to_string(x) + " " + std::to_string(y) + " failed");
        }
    } catch (std::invalid_argument &e) {
        throw CommandError("Invalid arguments");
    } catch (Map::MapError &e) {
        throw CommandError("Player not found");
    } catch (std::exception &e) {
        throw CommandError("Unknown error");
    }
}

void zappy::Communication::pdr(std::vector<std::string> &args) {
    if (args.size() != 2)
        throw CommandError("Invalid number of arguments");
    if (this->map == nullptr)
        throw MapUninitialized();
    try {
        int id = std::stoi(args[0]);
        auto player = (*this->map).getPlayerById(id);
        if (player == nullptr)
            return;
        this->sendCommand("pin " + std::to_string(id));
        this->sendCommand("bct " + std::to_string(player->x) + " " + std::to_string(player->y));
    } catch (CommunicationError &e) {
        throw CommandError("Lost connection to the server");
    } catch (std::invalid_argument &e) {
        throw CommandError("Invalid arguments");
    } catch (Map::MapError &e) {
        throw CommandError("Player not found");
    } catch (std::exception &e) {
        throw CommandError("Unknown error");
    }
}

void zappy::Communication::pgt(std::vector<std::string> &args) {
    if (args.size() != 2)
        throw CommandError("Invalid number of arguments");
    if (this->map == nullptr)
        throw MapUninitialized();
    try {
        int id = std::stoi(args[0]);
        auto player = (*this->map).getPlayerById(id);
        if (player == nullptr)
            return;
        this->sendCommand("pin " + std::to_string(id));
        this->sendCommand("bct " + std::to_string(player->x) + " " + std::to_string(player->y));
    } catch (CommunicationError &e) {
        throw CommandError("Lost connection to the server");
    } catch (std::invalid_argument &e) {
        throw CommandError("Invalid arguments");
    } catch (Map::MapError &e) {
        throw CommandError("Player not found");
    } catch (std::exception &e) {
        throw CommandError("Unknown error");
    }
}

void zappy::Communication::pdi(std::vector<std::string> &args) {
    if (args.size() != 1)
        throw CommandError("Invalid number of arguments");
    if (this->map == nullptr)
        throw MapUninitialized();
    try {
        int id = std::stoi(args[0]);
        (*this->map).removePlayerById(id);
        this->eventLogger.log("Player " + std::to_string(id) + " died");
    } catch (Team::TeamError &e) {
        throw CommandError("Player not found");
    } catch (Map::MapError &e) {
        throw CommandError("Player not found");
    } catch (std::exception &e) {
        throw CommandError("Unknown error");
    }
}

void zappy::Communication::enw(std::vector<std::string> &args) {
    if (args.size() != 4)
        throw CommandError("Invalid number of arguments");
    if (this->map == nullptr)
        throw MapUninitialized();
    try {
        int id = std::stoi(args[0]);
        int player_id = std::stoi(args[1]);
        int x = std::stoi(args[2]);
        int y = std::stoi(args[3]);
        std::string team = (*this->map).getPlayerById(player_id)->team;
        (*this->map).addEgg(x, y, id, team);
        this->eventLogger.log("Egg " + std::to_string(id) + " has been laid by player " + std::to_string(player_id));
    } catch (std::invalid_argument &e) {
        throw CommandError("Invalid arguments");
    } catch (Map::MapError &e) {
        throw CommandError("Player not found");
    } catch (std::exception &e) {
        throw CommandError("Unknown error");
    }
}

void zappy::Communication::ebo(std::vector<std::string> &args) {
    if (args.size() != 1)
        throw CommandError("Invalid number of arguments");
    if (this->map == nullptr)
        throw MapUninitialized();
    try {
        int id = std::stoi(args[0]);
        (*this->map).removeEggById(id);
    } catch (std::invalid_argument &e) {
        throw CommandError("Invalid arguments");
    } catch (Map::MapError &e) {
        throw CommandError("Egg not found");
    } catch (std::exception &e) {
        throw CommandError("Unknown error");
    }
}

void zappy::Communication::edi(std::vector<std::string> &args) {
    if (args.size() != 1)
        throw CommandError("Invalid number of arguments");
    if (this->map == nullptr)
        throw MapUninitialized();
    try {
        int id = std::stoi(args[0]);
        (*this->map).removeEggById(id);
    } catch (std::invalid_argument &e) {
        throw CommandError("Invalid arguments");
    } catch (Map::MapError &e) {
        throw CommandError("Egg not found");
    } catch (std::exception &e) {
        throw CommandError("Unknown error");
    }
}

void zappy::Communication::sgt(std::vector<std::string> &args) {
    if (args.size() != 1)
        throw CommandError("Invalid number of arguments");
    if (this->map == nullptr)
        throw MapUninitialized();
    try {
        int timeUnit = std::stoi(args[0]);
        (*this->map).setTimeUnit(timeUnit);
    } catch (std::invalid_argument &e) {
        throw CommandError("Invalid arguments");
    } catch (std::exception &e) {
        throw CommandError("Unknown error");
    }
}

void zappy::Communication::sst(std::vector<std::string> &args) {
    if (args.size() != 1)
        throw CommandError("Invalid number of arguments");
    if (this->map == nullptr)
        throw MapUninitialized();
    try {
        int timeUnit = std::stoi(args[0]);
        (*this->map).setTimeUnit(timeUnit);
    } catch (std::invalid_argument &e) {
        throw CommandError("Invalid arguments");
    } catch (std::exception &e) {
        throw CommandError("Unknown error");
    }
}

void zappy::Communication::seg(std::vector<std::string> &args) {
    if (args.size() != 1)
        throw CommandError("Invalid number of arguments");
    if (this->map == nullptr)
        throw MapUninitialized();
    try {
        std::string team = args[0];
        this->eventLogger.log("Team " + team + " has won");
        this->_running = false;
    } catch (std::exception &e) {
        throw CommandError("Invalid arguments");
    }
}

void zappy::Communication::smg(std::vector<std::string> &args) {
    if (args.size() != 1)
        throw CommandError("Invalid number of arguments");
    if (this->map == nullptr)
        throw MapUninitialized();
    try {
        std::string message = args[0];
        this->eventLogger.log(message);
    } catch (std::exception &e) {
        throw CommandError("Invalid arguments");
    }
}

void zappy::Communication::suc(std::vector<std::string> &args) {
    if (!args.empty())
        throw CommandError("Invalid number of arguments");
    if (this->map == nullptr)
        throw MapUninitialized();
    this->eventLogger.log("Command failed");
}

void zappy::Communication::sbp(std::vector<std::string> &args) {
    if (!args.empty())
        throw CommandError("Invalid number of arguments");
    if (this->map == nullptr)
        throw MapUninitialized();
    this->eventLogger.log("Command failed");
}

void zappy::Communication::pfk(std::vector<std::string> &args)
{
    if (args.size() != 1)
        throw CommandError("Invalid number of arguments");
    if (this->map == nullptr)
        throw MapUninitialized();
    try
    {
        int id = std::stoi(args[0]);
        this->eventLogger.log("Player " + std::to_string(id) + " is laying an egg");
        std::size_t x = (*this->map).getPlayerById(id)->x;
        std::size_t y = (*this->map).getPlayerById(id)->y;
        (*this->map).addEgg(x, y, id, (*this->map).getPlayerById(id)->team);
    }
    catch (std::invalid_argument &e)
    {
        throw CommandError("Invalid arguments");
    }
    catch (Map::MapError &e)
    {
        throw CommandError("Player not found");
    }
    catch (std::exception &e)
    {
        throw CommandError("Unknown error");
    }
}
