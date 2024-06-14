#!/usr/bin/env python3

import argparse
from AI.Bot import Bot
from AI.Communication import Communication
from AI.Color import Color


def check_port(value):
    ivalue = int(value)
    if ivalue < 1024 or ivalue > 65535:
        raise argparse.ArgumentTypeError("Port must be between 1024 and 65535")
    return ivalue


def parse_args():
    parser = argparse.ArgumentParser(description='Zappy AI', add_help=False)
    parser.add_argument('-p', '--port', type=check_port, required=True, help='Port number (1024-65535)')
    parser.add_argument('-n', '--name', required=True, help='Name')
    parser.add_argument('-h', '--host', required=True, help='Host')
    parser.add_argument('-help', action='help', default=argparse.SUPPRESS, help='Show this help message')
    args = parser.parse_args()

    return args.port, args.name, args.host


def main():
    bot = Bot(Communication(*parse_args()))
    bot.run()
    return bot


if __name__ == "__main__":
    bot = None
    try:
        bot = main()
        while bot and bot.comm and bot.comm.listen_thread.is_alive():
            pass
    except KeyboardInterrupt:
        print(f"\r{Color.BLUE}Interrupted by user. Closing...{Color.RESET}")
    finally:
        if bot and bot.comm is not None:
            bot.comm.closeConnection()
