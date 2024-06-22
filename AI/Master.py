#!/usr/bin/env python3

from AI.Bot import Bot
from AI.Enums import Element
import threading


class Master(Bot):
    def __init__(self, comm):
        super().__init__(comm)
        threading.Thread(target=self.sendNotMaster, daemon=True).start()
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


    def sendNotMaster(self):
        message = self.comm.getMessage()
        if message:
            if message[1] == "I'mMaster?-" + self.comm.team_name:
                self.broadcast("You'reNotMaster!-" + self.comm.team_name)
