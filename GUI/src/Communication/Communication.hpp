/*
** EPITECH PROJECT, 2024
** GUI/src/Communication/Communication.hpp
** File description:
** B-YEP-400-LIL-4-1-zappy-nicolas.pechart
*/

#pragma once

#include <string>
#include <utility>
#include <SFML/Network.hpp>
#include <iostream>
#include <unordered_map>
#include <functional>
#include <thread>
#include "../Map/Map.hpp"

namespace zappy {
    class Communication {
    private:
        bool _run {true};
        int _port {};
        std::string _host {};
        sf::TcpSocket _socket {};
        zappy::Assets assets {};
        std::shared_ptr<zappy::Map> map {nullptr};
        std::vector<int> _playersToUpdate {};
        std::string getLine();
        void sendCommand(std::string command);
        void commandSender();
        void commandReceiver();
        void TODODELETE();
    public:
        Communication(int port, std::string host);
        ~Communication();

        void connect();

        void run();

        class CommunicationError : public std::exception {
        public:
            explicit CommunicationError(std::string message) : _message(std::move(message)) {}
            const char *what() const noexcept override { return _message.c_str(); }
        private:
            std::string _message;
        };
        class CommandError : public std::exception {
        public:
            explicit CommandError(std::string message) : _message(std::move(message)) {}
            const char *what() const noexcept override { return _message.c_str(); }
        private:
            std::string _message;
        };
    private:
        // Commands
        std::unordered_map<std::string, std::function<void(std::vector<std::string> &args)>> _commands {
            {"msz", [this](std::vector<std::string> &args) { zappy::Communication::msz(args); }},
            {"bct", [this](std::vector<std::string> &args) { zappy::Communication::bct(args); }},
            {"tna", [this](std::vector<std::string> &args) { zappy::Communication::tna(args); }},
            {"pnw", [this](std::vector<std::string> &args) { zappy::Communication::pnw(args); }},
            {"ppo", [this](std::vector<std::string> &args) { zappy::Communication::ppo(args); }},
            {"plv", [this](std::vector<std::string> &args) { zappy::Communication::plv(args); }},
            {"pin", [this](std::vector<std::string> &args) { zappy::Communication::pin(args); }},
            {"pex", [this](std::vector<std::string> &args) { zappy::Communication::pex(args); }},
            //{"pbc", [this](std::vector<std::string> &args) { zappy::Communication::pbc(args); }},
            //{"pic", [this](std::vector<std::string> &args) { zappy::Communication::pic(args); }},
            //{"pie", [this](std::vector<std::string> &args) { zappy::Communication::pie(args); }},
            //{"pfk", [this](std::vector<std::string> &args) { zappy::Communication::pfk(args); }},
            //{"pdr", [this](std::vector<std::string> &args) { zappy::Communication::pdr(args); }},
            //{"pgt", [this](std::vector<std::string> &args) { zappy::Communication::pgt(args); }},
            //{"pdi", [this](std::vector<std::string> &args) { zappy::Communication::pdi(args); }},
            //{"enw", [this](std::vector<std::string> &args) { zappy::Communication::enw(args); }},
            //{"ebo", [this](std::vector<std::string> &args) { zappy::Communication::ebo(args); }},
            //{"edi", [this](std::vector<std::string> &args) { zappy::Communication::edi(args); }},
            //{"sgt", [this](std::vector<std::string> &args) { zappy::Communication::sgt(args); }},
            //{"sst", [this](std::vector<std::string> &args) { zappy::Communication::sst(args); }},
            //{"seg", [this](std::vector<std::string> &args) { zappy::Communication::seg(args); }},
            //{"smg", [this](std::vector<std::string> &args) { zappy::Communication::smg(args); }},
            //{"suc", [this](std::vector<std::string> &args) { zappy::Communication::suc(args); }},
            //{"sbp", [this](std::vector<std::string> &args) { zappy::Communication::sbp(args); }}
        };
        void msz(std::vector<std::string> &args);
        void bct(std::vector<std::string> &args);
        void tna(std::vector<std::string> &args);
        void pnw(std::vector<std::string> &args);
        void ppo(std::vector<std::string> &args);
        void plv(std::vector<std::string> &args);
        void pin(std::vector<std::string> &args);
        void pex(std::vector<std::string> &args);
        //void pbc(std::vector<std::string> &args);
        //void pic(std::vector<std::string> &args);
        //void pie(std::vector<std::string> &args);
        //void pfk(std::vector<std::string> &args);
        //void pdr(std::vector<std::string> &args);
        //void pgt(std::vector<std::string> &args);
        //void pdi(std::vector<std::string> &args);
        //void enw(std::vector<std::string> &args);
        //void ebo(std::vector<std::string> &args);
        //void edi(std::vector<std::string> &args);
        //void sgt(std::vector<std::string> &args);
        //void sst(std::vector<std::string> &args);
        //void seg(std::vector<std::string> &args);
        //void smg(std::vector<std::string> &args);
        //void suc(std::vector<std::string> &args);
        //void sbp(std::vector<std::string> &args);
    };
};
