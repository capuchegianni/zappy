#!/usr/bin/env python3

from AI.Enums import Direction
from AI.Enums import Element
import numpy as np
from math import sqrt


Levels = {}
Levels[1] = {"VISION" : 3, "ELEVATION" : [(Element.LINEMATE, 1), (Element.DERAUMERE, 0), (Element.SIBUR, 0), (Element.MENDIANE, 0), (Element.PHIRAS, 0), (Element.THYSTAME, 0)]}
Levels[2] = {"VISION" : 5, "ELEVATION" : [(Element.LINEMATE, 1), (Element.DERAUMERE, 1), (Element.SIBUR, 1), (Element.MENDIANE, 0), (Element.PHIRAS, 0), (Element.THYSTAME, 0)]}
Levels[3] = {"VISION" : 7, "ELEVATION" : [(Element.LINEMATE, 2), (Element.DERAUMERE, 0), (Element.SIBUR, 1), (Element.MENDIANE, 0), (Element.PHIRAS, 2), (Element.THYSTAME, 0)]}
Levels[4] = {"VISION" : 9, "ELEVATION" : [(Element.LINEMATE, 1), (Element.DERAUMERE, 1), (Element.SIBUR, 2), (Element.MENDIANE, 0), (Element.PHIRAS, 1), (Element.THYSTAME, 0)]}
Levels[5] = {"VISION" : 11, "ELEVATION" : [(Element.LINEMATE, 1), (Element.DERAUMERE, 2), (Element.SIBUR, 1), (Element.MENDIANE, 3), (Element.PHIRAS, 0), (Element.THYSTAME, 0)]}
Levels[6] = {"VISION" : 13, "ELEVATION" : [(Element.LINEMATE, 1), (Element.DERAUMERE, 2), (Element.SIBUR, 3), (Element.MENDIANE, 0), (Element.PHIRAS, 1), (Element.THYSTAME, 0)]}
Levels[7] = {"VISION" : 15, "ELEVATION" : [(Element.LINEMATE, 2), (Element.DERAUMERE, 2), (Element.SIBUR, 2), (Element.MENDIANE, 2), (Element.PHIRAS, 2), (Element.THYSTAME, 1)]}
Levels[8] = {"VISION" : 17, "ELEVATION" : [()]}


class Bot:
    def __init__(self, comm):
        self.comm = comm
        self.direction = Direction.NORTH
        self.level = 1
        self.master = False


    def forward(self, steps=1):
        for i in range(steps):
            self.comm.sendCommand("Forward")


    def right(self):
        self.comm.sendCommand("Right")
        if self.direction == Direction.NORTH:
            self.direction = Direction.EAST
        elif self.direction == Direction.EAST:
            self.direction = Direction.SOUTH
        elif self.direction == Direction.SOUTH:
            self.direction = Direction.WEST
        elif self.direction == Direction.WEST:
            self.direction = Direction.NORTH


    def left(self):
        self.comm.sendCommand("Left")
        if self.direction == Direction.NORTH:
            self.direction = Direction.WEST
        elif self.direction == Direction.WEST:
            self.direction = Direction.SOUTH
        elif self.direction == Direction.SOUTH:
            self.direction = Direction.EAST
        elif self.direction == Direction.EAST:
            self.direction = Direction.NORTH


    def setDirection(self, direction):
        while self.direction != direction:
            self.right()


    def takeObject(self, object):
        self.comm.sendCommand("Take " + object.name.lower())


    def setObject(self, object):
        self.comm.sendCommand("Set " + object.name.lower())


    def broadcast(self, text):
        self.comm.sendCommand("Broadcast " + text)


    def startIncantation(self):
        self.comm.sendCommand("Incantation")


    def run(self):
        while True:
            if not self.lookAround():
                break
            if not self.updateInventory():
                break
            if not self.refillFood():
                break
            if not self.getObject([Element.LINEMATE, Element.DERAUMERE, Element.SIBUR, Element.MENDIANE, Element.PHIRAS, Element.THYSTAME]):
                break


    def lookAround(self):
        all_list = []
        vision = np.zeros((Levels[self.level]["VISION"], Levels[self.level]["VISION"]), dtype=Element)
        s = [self.level, self.level]

        for i in range(4):
            if i == 0:
                self.setDirection(Direction.NORTH)
            elif i == 1:
                self.setDirection(Direction.EAST)
            elif i == 2:
                self.setDirection(Direction.SOUTH)
            elif i == 3:
                self.setDirection(Direction.WEST)
            if self.comm.stop_listening:
                return False
            self.comm.sendCommand("Look")
            all_list.append(self.comm.data)

        for i, list in enumerate(all_list):
            elements = list.strip()[1:-1].strip().split(',')
            clean_elements = [element.strip() for element in elements]
            all_list[i] = [[Element[sub_item.upper()] for sub_item in item.split()] for item in clean_elements]

        for list in all_list:
            x = 1
            while list:
                for i in range(x):
                    if not list:
                        break
                    vision[s[0], s[1]] = list.pop(0)
                    s[1] += 1
                s[0] -= 1
                x += 2
                s[1] -= x - 1
            s[0] = self.level
            s[1] = self.level
            vision = np.rot90(vision, k=1)

        self.vision = vision
        return True


    def findNearest(self, elements):
        min_distance = float('inf')
        nearest_coords = None
        nearest_element = None

        for i in range(self.vision.shape[0]):
            for j in range(self.vision.shape[1]):
                for element in elements:
                    if element in self.vision[i, j]:
                        distance = sqrt((self.level - i) ** 2 + (self.level - j) ** 2)
                        if distance < min_distance:
                            min_distance = distance
                            nearest_coords = (i, j)
                            nearest_element = element
                            break

        return nearest_coords, nearest_element


    def goTo(self, y, x):
        if y < 0:
            self.setDirection(Direction.NORTH)
            self.forward(abs(y))
        elif y > 0:
            self.setDirection(Direction.SOUTH)
            self.forward(y)

        if x < 0:
            self.setDirection(Direction.WEST)
            self.forward(abs(x))
        elif x > 0:
            self.setDirection(Direction.EAST)
            self.forward(x)

        return True


    def updateInventory(self):
        if self.comm.stop_listening:
            return False
        self.comm.sendCommand("Inventory")
        self.inventory = {}

        if self.comm.data == "dead\n":
            return False
        for item in self.comm.data.strip()[1:-1].split(','):
            key, value = item.strip().split(' ')
            self.inventory[Element[key.upper()]] = int(value)

        return True


    def getObject(self, object):
        nearest, nearest_type = self.findNearest(object)
        if nearest is None:
            if self.comm.stop_listening:
                return False
            self.forward()
            return True

        if not self.goTo(nearest[0] - self.level, nearest[1] - self.level):
            return False

        self.takeObject(nearest_type)

        return True


    def refillFood(self):
        if self.inventory[Element.FOOD] < 10:
            while self.inventory[Element.FOOD] < 20:
                if not self.getObject([Element.FOOD]):
                    break
                if not self.lookAround():
                    break
                if not self.updateInventory():
                    break

        return True
