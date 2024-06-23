#!/usr/bin/env python3

from AI.Bot import Bot
from AI.Enums import Element, Direction, Action


class Servant(Bot):
    def __init__(self, comm):
        super().__init__(comm)
        self.action = Action.NONE

        while True:
            if self.comm.stop_listening:
                break
            self.handleMasterMessage()
            if self.action == Action.NONE:
                if not self.lookAround():
                    break
                if not self.updateInventory():
                    break
                if not self.refillFood():
                    break
                if not self.getObject([Element.LINEMATE, Element.DERAUMERE, Element.SIBUR, Element.MENDIANE, Element.PHIRAS, Element.THYSTAME]):
                    break


    def handleMasterMessage(self):
        message = self.comm.getMessage()
        if not message:
            return

        message_split = message[1].split("|")
        if message_split[0] == "RequestInventory-" + self.comm.team_name:
            self.sendInventory()
        elif message_split[0] == "Incantation-" + self.comm.team_name and int(message_split[1]) == self.level and self.action != Action.WAIT_ELEVATION:
            self.joinMaster(message[0])
        elif message_split[0] == "IncantationFailed-" + self.comm.team_name:
            self.action = Action.NONE
        elif message_split[0] == "IncantationDone-" + self.comm.team_name:
            self.comm.getData()
            self.comm.getData()
            self.level += 1
            self.action = Action.NONE


    def sendInventory(self):
        inventory = ""
        for key, value in self.inventory.items():
            inventory += key.name + ":" + str(value) + "_"
        self.broadcast("Inventory-" + self.comm.team_name + "|" + inventory)


    def joinMaster(self, direction):
        self.action = Action.JOIN_MASTER

        if direction == 0:
            self.broadcast("JoinedMaster-" + self.comm.team_name)
            self.dropObjects()
            self.action = Action.WAIT_ELEVATION
        elif direction == 1:
            self.forward()
        elif direction == 2:
            self.forward()
            self.setDirection(Direction.WEST)
            self.forward()
        elif direction == 3:
            self.setDirection(Direction.WEST)
            self.forward()
        elif direction == 4:
            self.setDirection(Direction.SOUTH)
            self.forward()
            self.setDirection(Direction.EAST)
            self.forward()
        elif direction == 5:
            self.setDirection(Direction.SOUTH)
            self.forward()
        elif direction == 6:
            self.setDirection(Direction.SOUTH)
            self.forward()
            self.setDirection(Direction.WEST)
            self.forward()
        elif direction == 7:
            self.setDirection(Direction.EAST)
            self.forward()
        elif direction == 8:
            self.forward()
            self.setDirection(Direction.EAST)
            self.forward()
