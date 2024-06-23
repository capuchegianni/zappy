#!/usr/bin/env python3

import socket
import queue
import select
import threading
from AI.Color import Color


class Communication:
    def __init__(self, port, name, host):
        self.team_name = name
        self.all_data = queue.Queue()
        self.data_queue = queue.Queue()
        self.message_queue = queue.Queue()
        self.client_socket = self.openConnection(port, name, host)
        self.stop_listening = False
        self.listen_thread = threading.Thread(target=self.listenServer, daemon=True)
        self.listen_thread.start()


    def openConnection(self, port, name, host):
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        try:
            client_socket.connect((host, port))
        except socket.error:
            print(f"{Color.RED}Failed to connect to server '{host}:{port}'.{Color.RESET}")
            exit(1)

        if (client_socket.recv(1024).decode() != "WELCOME\n"):
            exit("Server did not send welcome message")

        while True:
            client_socket.sendall(f"{name}\n".encode())
            ready = select.select([client_socket], [], [], 0.5)
            if ready[0]:
                data = client_socket.recv(1024).decode()
                if not data == "ko\n":
                    break
            else:
                print(f"{Color.YELLOW}No slots available for team '{name}'.{Color.RESET}")
                continue

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
            if self.stop_listening:
                return
            self.client_socket.sendall((command + "\n").encode())
            print(f"{Color.BLUE}Sent command: {command}{Color.RESET}")
        except socket.error as e:
            print(f"{Color.RED}Error sending data: {e}{Color.RESET}")
            return
        while self.data_queue.empty():
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
                data_items = filter(None, data_received.split('\n'))
                for data in data_items:
                    if data == "dead":
                        print(f"{Color.BLUE}You died.{Color.RESET}")
                        self.stop_listening = True
                        break
                    else:
                        self.all_data.put(data)
                        self.processQueue()
                if self.stop_listening:
                    break
            except socket.error as e:
                print(f"{Color.RED}Error receiving data: {e}{Color.RESET}")
                break
        self.closeConnection(join=False)


    def processQueue(self):
        while not self.all_data.empty():
            data_received = self.all_data.get()
            data_split = data_received.split(' ')
            if data_split[0] == "message":
                self.message_queue.put([int(data_split[1].strip(',')), ' '.join(data_split[2:])])
                print(f"{Color.YELLOW}Message queued: {[int(data_split[1].strip(',')), ' '.join(data_split[2:])]}{Color.RESET}")
            else:
                self.data_queue.put(data_received)
                print(f"{Color.PURPLE}Data queued: {data_received}{Color.RESET}")


    def getData(self):
        if not self.data_queue.empty():
            return self.data_queue.get()
        return None


    def getMessage(self):
        if not self.message_queue.empty():
            return self.message_queue.get()
        return None
