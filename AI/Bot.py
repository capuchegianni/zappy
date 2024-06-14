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
        self.run()


    def run(self):
        while True:
            if not self.lookAround():
                break


    def lookAround(self):
        all_list = []
        vision = np.zeros((Levels[self.level]["VISION"], Levels[self.level]["VISION"]), dtype=Element)
        s = [self.level, self.level]

        for i in range(4):
            if self.comm.stop_listening:
                return False
            self.comm.sendCommand("Look")
            all_list.append(self.comm.data)
            if self.comm.stop_listening:
                return False
            self.comm.sendCommand("Right")

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


    def findNearest(self, element):
        min_distance = float('inf')
        nearest_coords = None

        for i in range(self.vision.shape[0]):
            for j in range(self.vision.shape[1]):
                if element in self.vision[i, j]:
                    distance = sqrt((self.level - i) ** 2 + (self.level - j) ** 2)
                    if distance < min_distance:
                        min_distance = distance
                        nearest_coords = (i, j)

        return nearest_coords
