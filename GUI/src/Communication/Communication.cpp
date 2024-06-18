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
#include "../Map/Map.hpp"
#include "../Display/EventLogger.hpp"

zappy::Communication::Communication(int port, std::string host) : _port(port), _host(std::move(host)) {}

std::string zappy::Communication::getLine() {
    std::string line;
    while (line[line.size() - 1] != '\n') {
        char c;
        std::size_t received;
        if (this->_socket.receive(&c, 1, received) != sf::Socket::Done || received == 0) {
            throw std::runtime_error("Failed to receive data from the server");
        }
        line += c;
    }
    return line;
}

void zappy::Communication::sendCommand(std::string command) {
    command += "\n";
    if (this->_socket.send(command.c_str(), command.size()) != sf::Socket::Done) {
        throw std::runtime_error("Failed to send command to the server");
    }
}

zappy::Communication::~Communication() {
    if (this->_socket.getRemoteAddress() != sf::IpAddress::None)
        this->_socket.disconnect();
}

void zappy::Communication::connect() {
    if (this->_socket.getRemoteAddress() != sf::IpAddress::None) {
        throw std::runtime_error("Already connected to the server");
    }
    sf::Socket::Status status = this->_socket.connect(this->_host, this->_port);
    if (status != sf::Socket::Done) {
        throw std::runtime_error("Unable to connect to the server");
    }
    auto line = this->getLine();
    if (line != "WELCOME\n") {
        throw std::runtime_error("Failed to connect to the server");
    }
    if (this->_socket.send("GRAPHIC\n", 8) != sf::Socket::Done) {
        throw std::runtime_error("Authentication failed");
    }
}

void zappy::Communication::run() {
    if (this->_socket.getRemoteAddress() == sf::IpAddress::None) {
        this->connect();
    }
    std::vector<std::thread> threads;
    threads.emplace_back(&zappy::Communication::commandSender, this);
    threads.emplace_back(&zappy::Communication::commandReceiver, this);
    threads.emplace_back(&zappy::Communication::TODODELETE, this);
    for (auto &thread : threads) {
        thread.join();
    }
}

void zappy::Communication::TODODELETE() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Zappy", sf::Style::Close);
    zappy::EventLogger eventLogger(20, assets);

    sf::Vector2f loggerPos(1090, 10);
    sf::Vector2f loggerSize(820, 512);
    eventLogger.setDisplayPosition(loggerPos);
    eventLogger.setDisplaySize(loggerSize);

    window.setFramerateLimit(60);

    sf::Vector2f position(0, 0);
    sf::Vector2f size(1080, 1080);
    (*map).setDisplayPosition(position);
    (*map).setDisplaySize(size);
    while (true) {
        window.clear(sf::Color::Blue);
        (*map).updateDisplay();

        window.draw((*map));
        window.draw(eventLogger);
        window.display();
    }
}

void zappy::Communication::commandReceiver() {
    while (this->_run) {
        auto line = this->getLine();
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
            this->_commands[command](args);
        } else {
            std::cerr << "Unknown command: " << command << std::endl;
        }
    }
}

void zappy::Communication::commandSender() {
    while (this->_run) {
        for (auto &player : this->_playersToUpdate) {
            this->sendCommand("ppo " + std::to_string(player));
            this->sendCommand("pin " + std::to_string(player));
        }
        this->_playersToUpdate.clear();
        std::string command;
        std::getline(std::cin, command);
        this->sendCommand(command);
    }
}

void zappy::Communication::msz(std::vector<std::string> &args) {
    if (args.size() != 2) {
        throw std::runtime_error("Invalid number of arguments for msz command");
    }
    this->map = std::make_shared<zappy::Map>(std::stoi(args[0]), std::stoi(args[1]), this->assets);
}

void zappy::Communication::bct(std::vector<std::string> &args) {
    if (args.size() != 9)
        throw std::runtime_error("Invalid number of arguments for bct command");
    if (this->map == nullptr)
        return;
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
}

void zappy::Communication::tna(std::vector<std::string> &args) {
    if (args.size() != 1)
        throw std::runtime_error("Invalid number of arguments for tna command");
    if (this->map == nullptr)
        return;
    std::string team = args[0];
    (*this->map).addTeam(team);
}

void zappy::Communication::pnw(std::vector<std::string> &args) {
    if (args.size() != 6)
        throw std::runtime_error("Invalid number of arguments for pnw command");
    if (this->map == nullptr)
        return;
    int id = std::stoi(args[0]);
    int x = std::stoi(args[1]);
    int y = std::stoi(args[2]);
    short direction = std::stoi(args[3]);
    int level = std::stoi(args[4]);
    std::string team = args[5];
    zappy::Trantorien trantorien(id);
    trantorien.x = x;
    trantorien.y = y;
    trantorien.direction = direction;
    trantorien.level = level;
    (*this->map).getTeam(team).addPlayer(std::make_shared<zappy::Trantorien>(trantorien));
}

void zappy::Communication::pex(std::vector<std::string> &args) {
    if (args.size() != 1)
        throw std::runtime_error("Invalid number of arguments for pex command");
    if (this->map == nullptr)
        return;
    int id = std::stoi(args[0]);
    this->_playersToUpdate.push_back(id);
}