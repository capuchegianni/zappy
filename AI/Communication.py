#!/usr/bin/env python3

import socket
from time import sleep
import threading
from AI.Color import Color


class Communication:
    def __init__(self, port, name, host):
        self.client_socket = self.openConnection(port, name, host)
        self.stop_listening = False
        self.listen_thread = threading.Thread(target=self.listenServer, daemon=True)
        self.listen_thread.start()


    def openConnection(self, port, name, host):
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        while True:
            try:
                client_socket.connect((host, port))
                break
            except socket.error:
                print(f"{Color.YELLOW}Failed to connect to server '{host}:{port}'. Retrying...{Color.RESET}")
                sleep(1)

        if (client_socket.recv(1024).decode() != "WELCOME\n"):
            exit("Server did not send welcome message")

        while True:
            client_socket.sendall(f"{name}\n".encode())
            data = client_socket.recv(1024).decode()
            if not data == "ko\n":
                break
            print(f"{Color.YELLOW}No slots available for team '{name}'{Color.RESET}")
            sleep(0.5)

        print(f"{Color.GREEN}Connected to server.{Color.RESET}")
        self.size_map = tuple(list(map(int, data.split()))[-2:])

        return client_socket


    def closeConnection(self, join=True):
        self.stop_listening = True
        if join:
            self.listen_thread.join(timeout=1)
        self.client_socket.close()


    def sendCommand(self, command):
        self.client_socket.sendall(command.encode())
        print(f"Sent command: {command}")


    def listenServer(self):
        while not self.stop_listening:
            data = self.client_socket.recv(1024).decode()
            if not data:
                print(f"{Color.BLUE}Connection closed by server.{Color.RESET}")
                self.closeConnection(join=False)
                break
            print(f"Received data: {data}")
            sleep(0.5)
