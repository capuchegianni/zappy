/*
** EPITECH PROJECT, 2024
** Arguments.hpp
** File description:
** zappy_gui
*/

#pragma once

#include <iostream>
#include <vector>

namespace zappy
{
    class Arguments
    {
        public:
            Arguments(std::vector<std::string> args);
            ~Arguments();

            class ArgumentsError : public std::exception
            {
                public:
                    ArgumentsError(std::string const &message) : _message(message) {}
                    const char *what() const noexcept override { return _message.c_str(); }
                private:
                    std::string _message;
            };

            int port = -1;
            std::string ip = " ";
    };
}
