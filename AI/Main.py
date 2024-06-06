#!/usr/bin/env python3

import argparse
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
    communication = Communication(*parse_args())
    print(f"Size of the map: {communication.size_map}")
    return communication


if __name__ == "__main__":
    communication = None
    try:
        communication = main()
        while True:
            if not communication.listen_thread.is_alive():
                break
            pass
    except KeyboardInterrupt:
        print(f"\r\r{Color.BLUE}Interrupted by user. Closing...{Color.RESET}")
        if communication is not None:
            communication.closeConnection()
