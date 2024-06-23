#!/usr/bin/env python3

from AI.Bot import Bot
from AI.Enums import Element
import time


class Master(Bot):
    def __init__(self, comm):
        super().__init__(comm)
        notMaster_time = time.time()
        requestInventory_time = time.time()
        self.number_of_servants = 0
        self.all_inventories = {}

        while True:
            if self.comm.stop_listening:
                break
            if time.time() - notMaster_time > 0.2:
                self.broadcast("You'reNotMaster!-" + self.comm.team_name)
                notMaster_time = time.time()
            # if self.canLevelUp():
            #     self.incantation()
            if not self.lookAround():
                break
            if not self.updateInventory():
                break
            if not self.refillFood():
                break
            if not self.getObject([Element.LINEMATE, Element.DERAUMERE, Element.SIBUR, Element.MENDIANE, Element.PHIRAS, Element.THYSTAME]):
                break
            if time.time() - requestInventory_time > 5:
                self.requestInventories()
                self.createEgg()
                requestInventory_time = time.time()


    def requestInventories(self):
        self.all_inventories = self.inventory.copy()
        self.number_of_servants = 0
        start_time = time.time()
        self.broadcast("RequestInventory-" + self.comm.team_name + "|")

        while True:
            if time.time() - start_time > 3:
                break

            message = self.comm.getMessage()
            if not message:
                continue
            message_split = message[1].split("|")
            if message_split[0] == "Inventory-" + self.comm.team_name:
                self.number_of_servants += 1
                for item in message_split[1].strip("_").split("_"):
                    name, quantity = item.split(":")
                    element_key = Element[name]
                    self.all_inventories[element_key] = self.all_inventories.get(element_key, 0) + int(quantity)


    def createEgg(self):
        if self.number_of_servants < 5:
            self.comm.sendCommand("Fork")
            if self.comm.getData() == "ko\n":
                return False
        return True


    def canLevelUp(self):
        next_level_requirements = self.levels_dict[self.level]["ELEVATION"]

        for element, required_quantity in next_level_requirements:
            if element not in self.all_inventories or self.all_inventories[element] < required_quantity:
                return False

        if self.number_of_servants < 5:
            return False

        return True


    def incantation(self):
        print("Start Incantation!")
        print(self.vision[self.level, self.level])
        while sum(1 for item in self.vision[self.level, self.level] if item == Element.PLAYER) != 6:
            self.broadcast("Incantation-" + self.comm.team_name)

        print("Incantation!")
        time.sleep(5)
