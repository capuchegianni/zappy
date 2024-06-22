/*
** EPITECH PROJECT, 2024
** GUI/src/Communication/Communication.cpp
** File description:
** B-YEP-400-LIL-4-1-zappy-nicolas.pechart
*/

#include "Communication.hpp"

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
    while (line[line.size() - 1] != '\n') {
        char c;
        std::size_t received;
        if (this->_socket.receive(&c, 1, received) != sf::Socket::Done || received == 0) {
            throw CommunicationError("Failed to receive data from the server");
        }
        line += c;
    }
    return line;
}

void zappy::Communication::sendCommand(std::string command) {
    command += "\n";
    if (this->_socket.send(command.c_str(), command.size()) != sf::Socket::Done) {
        throw CommunicationError("Failed to send command to the server");
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
    if (this->_socket.send("GRAPHIC\n", 8) != sf::Socket::Done) {
        throw CommunicationError("Authentication failed");
    }
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

    double mapWindowWidth = 0.5;

    sf::RenderWindow window(sf::VideoMode(winwidth, winheight), "Zappy");

    sf::Vector2f loggerPos(1090, 20);
    sf::Vector2f loggerSize(820, 512);

    eventLogger.setDisplayPosition(loggerPos);
    eventLogger.setDisplaySize(loggerSize);

    window.setFramerateLimit(60);

    sf::Vector2f position(0, 0);
    sf::Vector2f size(1080, 1080);
    window.setFramerateLimit(60);

    sf::Event event;
    sf::Clock frameClock;
    int lastFrameTime = 0;

    frameClock.restart();

    sf::View view(sf::FloatRect(0, 0, static_cast<float>(winwidth), static_cast<float>(winheight)));

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
                map->sceneDate.sceneData.camera.centerX += movForward.x * lastFrameTime * 0.1;
                map->sceneDate.sceneData.camera.centerY += movForward.y * lastFrameTime * 0.1;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                map->sceneDate.sceneData.camera.centerX -= movForward.x * lastFrameTime * 0.1;
                map->sceneDate.sceneData.camera.centerY -= movForward.y * lastFrameTime * 0.1;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            {
                map->sceneDate.sceneData.camera.centerX += movRight.x * lastFrameTime * 0.1;
                map->sceneDate.sceneData.camera.centerY += movRight.y * lastFrameTime * 0.1;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                map->sceneDate.sceneData.camera.centerX -= movRight.x * lastFrameTime * 0.1;
                map->sceneDate.sceneData.camera.centerY -= movRight.y * lastFrameTime * 0.1;
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

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::Resized)
            {
                size = sf::Vector2f(event.size.width / 2, event.size.height);
                view = sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height));
                (*map).setDisplaySize(size);
                window.setView(view);
            }
        }

        map->updateDisplay();
        window.clear(sf::Color::Blue);
        window.draw(*map);
        window.draw(eventLogger);
        window.display();
        lastFrameTime = frameClock.getElapsedTime().asMilliseconds();
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
                std::cerr << command << ": " << e.what() << std::endl;
            }
        } else {
            std::cerr << command << ": Unknown command" << std::endl;
        }
    }
    std::cout << "Command Receiver Stopped\n";
}

void zappy::Communication::automaticCommandSender() {
    std::cout << "Starting Automatic Sender\n";
    this->sendCommand("msz");
    this->sendCommand("tna");
    this->sendCommand("mct");
    while (this->_running) {
        this->sendCommand("mct");
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "Automatic Sender Stopped\n";
}

void zappy::Communication::msz(std::vector<std::string> &args) {
    if (args.size() != 2) {
        throw CommandError("Invalid number of arguments");
    }
    if (this->map == nullptr) {
        this->map = std::make_shared<zappy::Map>(std::stoi(args[0]), std::stoi(args[1]), this->assets);
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
        (*this->map)(x, y).food = food;
        (*this->map)(x, y).linemate = linemate;
        (*this->map)(x, y).deraumere = deraumere;
        (*this->map)(x, y).sibur = sibur;
        (*this->map)(x, y).mendiane = mendiane;
        (*this->map)(x, y).phiras = phiras;
        (*this->map)(x, y).thystame = thystame;
    } catch (std::invalid_argument &e) {
        throw CommandError("Invalid arguments");
    } catch (Map::MapError &e) {
        throw CommandError("Out of bounds");
    } catch (std::exception &e) {
        throw CommandError("Unknown error");
    }
}

void zappy::Communication::tna(std::vector<std::string> &args) {
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
        this->sendCommand("pin " + std::to_string(id));
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
    } catch (std::exception &e) {
        throw CommandError("Invalid arguments");
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
    } catch (std::exception &e) {
        throw CommandError("Invalid arguments");
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
        this->updateTimeUnit(timeUnit);
    } catch (std::invalid_argument &e) {
        throw CommandError("Invalid arguments");
    } catch (std::exception &e) {
        throw CommandError("Unknown error");
    }
}
