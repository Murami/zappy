import inventory
import fov
import level
import alive
import freeSlot
import expulse
import message
import answer
import elevation
import zappyParser
import responseServer

class Data:
    def __init__ (self):
        self.parser = zappyParser.ZappyParser()
        self.inventory = inventory.Inventory()
        self.fov = fov.Fov()
        self.fov.setUsed(True)
        self.elevation = elevation.Elevation()
        self.level = level.Level()
        self.alive = alive.Alive()
        self.freeSlot = freeSlot.FreeSlot()
        self.expulse = expulse.Expulse()
        self.message = message.Message()
        self.answer = answer.Answer()
        self.listOtherLevel = [0, 0, 0, 0, 0, 0, 0, 0, 0]
        self.lvlNeeded = False
        self.direction = -1
        self.leader = 0

    def update (self, response):
        res = self.parser.parse(response)
        if res.isInventory():
            self.inventory = res.getInventory()
        elif res.isFov():
            self.fov = res.getFov()
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
        elif res.isElevation():
            self.elevation = res.getElevation()
        elif res.isLevel():
            self.level = res.getLevel()
            self.leader = 0
            self.elevation.isInElevation = False
        return res

    def reinitializeListLevel (self):
        self.listOtherLevel = [0, 0, 0, 0, 0, 0, 0, 0, 0]

    def getNbrOfLevel (self, level):
        return self.listOtherLevel[level]

    def getNbrofLowerLevel (self, level):
        res = 0
        for i in range(level):
            res += self.listOtherLevel[i]
        return res
