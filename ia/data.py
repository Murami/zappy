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
        self.fov.setUsed(True)
        self.level = level.Level()
        self.alive = alive.Alive()
        self.freeSlot = freeSlot.FreeSlot()
        self.expulse = expulse.Expulse()
        self.message = message.Message()
        self.answer = answer.Answer()

    def update (self, response):
        res = self.parser.parse(response)
        print("test")
        if res.isInventory():
            print("test1")
            self.inventory = res.getInventory()
        elif res.isFov():
            print("test2")
            self.fov = res.getFov()
        elif res.isLevel():
            print("test3")
            self.level = res.getLevel()
        elif res.isAlive():
            print("test4")
            self.alive = res.getAlive()
        elif res.isFreeSlot():
            print("test5")
            self.freeSlot = res.getFreeSlot()
        elif res.isExpulse():
            print("test6")
            self.expulse = res.getExpulse()
        elif res.isMessage():
            print("test7")
            self.message = res.getMessage()
        elif res.isAnswer():
            print("test8")
            self.answer = res.getAnswer()
        print("end")
