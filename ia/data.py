import inventory
import fov
import level
import alive
import freeSlot
import expulse
import message
import answer
import zappyParser

class Data:
    def __init__ (self):
        self.parser = zappyParser.ZappyParser()
        self.inventory = inventory.Inventory()
        self.fov = fov.Fov()
        self.level = level.Level()
        self.alive = alive.Alive()
        self.freeSlot = freeSlot.FreeSlot()
        self.expulse = expulse.Expulse()
        self.message = message.Message()
        self.answer = answer.Answer()

    def update (self, response):
        res = self.parser.parse(response)
        if res.isInventory():
            self.inventory = res.getInventory()
        elif res.isFov():
            self.fov = res.getFov()
        elif res.isLevel():
            self.level = res.getLevel()
        elif res.isAlive():
            self.alive = res.getAlive()
        elif res.isFreeSlot():
            self.freeSlot = res.getFreeSlot()
        elif res.isExpulse():
            self.expulse = res.getExpulse()
        elif res.isMessage():
            self.message = res.getMessage()
        elif res.isAnswer():
            self.answer = res.getAnswer()
