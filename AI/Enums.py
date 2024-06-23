#!/usr/bin/env python3

from enum import Enum


class Direction(Enum):
    NORTH = 0
    EAST = 1
    SOUTH = 2
    WEST = 3


class Element(Enum):
    FOOD = 0
    LINEMATE = 1
    DERAUMERE = 2
    SIBUR = 3
    MENDIANE = 4
    PHIRAS = 5
    THYSTAME = 6
    PLAYER = 7
    EGG = 8


class Action(Enum):
    NONE = 0
    JOIN_MASTER = 1
    WAIT_ELEVATION = 2
