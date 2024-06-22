#!/usr/bin/env python3

from AI.Bot import Bot
from AI.Enums import Element


class Servant(Bot):
    def __init__(self, comm):
        super().__init__(comm)
        while True:
            if self.comm.stop_listening:
                break
            if not self.lookAround():
                break
            if not self.updateInventory():
                break
            if not self.refillFood():
                break
            if not self.getObject([Element.LINEMATE, Element.DERAUMERE, Element.SIBUR, Element.MENDIANE, Element.PHIRAS, Element.THYSTAME]):
                break
