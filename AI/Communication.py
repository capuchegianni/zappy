#!/usr/bin/env python3

import socket
import queue
from time import sleep
import threading
from AI.Color import Color


class Communication:
    def __init__(self, port, name, host):
        self.team_name = name
        self.data_queue = queue.Queue()
        self.client_socket = self.openConnection(port, name, host)
        self.stop_listening = False
        self.listen_thread = threading.Thread(target=self.listenServer, daemon=True)
        self.listen_thread.start()
        self.data = None
        self.message = None


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
        self.size_map = client_socket.recv(1024).decode()

        return client_socket


    def closeConnection(self, join=True):
        self.stop_listening = True
        self.client_socket.close()
        if join:
            self.listen_thread.join(timeout=1)


    def sendCommand(self, command):
        try:
            self.client_socket.sendall((command + "\n").encode())
            print(f"{Color.BLUE}Sent command: {command}{Color.RESET}")
        except socket.error as e:
            print(f"{Color.RED}Error sending data: {e}{Color.RESET}")
            return
        while self.data is None:
            if self.stop_listening:
                return
            continue


    def listenServer(self):
        while not self.stop_listening:
            try:
                data_received = self.client_socket.recv(1024).decode()
                if not data_received:
                    print(f"{Color.BLUE}Connection closed by server.{Color.RESET}")
                    break
                if data_received == "dead\n":
                    print(f"{Color.BLUE}You died.{Color.RESET}")
                    self.stop_listening = True
                    break
            except socket.error as e:
                print(f"{Color.RED}Error receiving data: {e}{Color.RESET}")
                break
            self.data_queue.put(data_received)
            self.processQueue()
        self.closeConnection(join=False)


    def processQueue(self):
        if self.data_queue.empty():
            return False
        data_received = self.data_queue.get()
        data_split = data_received.split(' ')
        if data_split[0] == "message":
            self.message = [int(data_split[1].strip(',')), data_split[2].strip('\n')]
            print(f"{Color.YELLOW}Message received: {self.message}{Color.RESET}")
        else:
            self.data = data_received
            print(f"{Color.PURPLE}Data received: {self.data}{Color.RESET}")
        return True


    def getData(self):
        data = self.data
        self.data = None
        return data


    def getMessage(self):
        message = self.message
        self.message = None
        return message
