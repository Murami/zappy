import inventory
import fov
import message
import expulse
import answer
import freeSlot
import alive
import level
import elevation

class ResponseServer:
    """ classe mere """

    def __init__ (self):
        self.isItInventory = False
        self.isItFov = False
        self.isItMessage = False
        self.isItExpulse = False
        self.isItAnswer = False
        self.isItFreeSlot = False
        self.isItAlive = False
        self.isItElevation = False
        self.isItLevel = False

    def isInventory (self):
        return self.isItInventory

    def isFov (self):
        return self.isItFov

    def isMessage (self):
        return self.isItMessage

    def isExpulse (self):
        return self.isItExpulse

    def isAnswer (self):
        return self.isItAnswer

    def isFreeSlot (self):
        return self.isItFreeSlot

    def isAlive (self):
        return self.isItAlive

    def isElevation (self):
        return self.isItElevation

    def isLevel (self):
        return self.isItLevel

# class reponse de type inventaire
class ResponseServerInventory(ResponseServer):

    def __init__ (self):
        ResponseServer.__init__(self)
        self.inventory = inventory.Inventory()
        self.isItInventory = True

    def getInventory (self):
        return self.inventory

# class reponse de type field of view
class ResponseServerFov(ResponseServer):
    
    def __init__ (self):
        ResponseServer.__init__(self)
        self.fov = fov.Fov()
        self.isItFov = True

    def getFov (self):
        return self.fov

# class reponse de type message
class ResponseServerMessage(ResponseServer):

    def __init__ (self):
        ResponseServer.__init__(self)
        self.message = message.Message()
        self.isItMessage = True

    def getMessage (self):
        return self.message

# class reponse de type message
class ResponseServerExpulse(ResponseServer):

    def __init__ (self):
        ResponseServer.__init__(self)
        self.expulse = expulse.Expulse()
        self.isItExpulse = True

    def getExpulse (self):
        return self.expulse

# class reponse de type reponse
class ResponseServerAnswer(ResponseServer):

    def __init__ (self):
        ResponseServer.__init__(self)
        self.answer = answer.Answer()
        self.isItAnswer = True

    def getAnswer (self):
        return self.answer

# class reponse de type valeur
class ResponseServerFreeSlot(ResponseServer):

    def __init__ (self):
        ResponseServer.__init__(self)
        self.freeSlot = freeSlot.FreeSlot()
        self.isItFreeSlot = True

    def getFreeSlot (self):
        return self.freeSlot

# class reponse de type alive
class ResponseServerAlive(ResponseServer):

    def __init__ (self):
        ResponseServer.__init__(self)
        self.alive = alive.Alive()
        self.isItAlive = True

    def getAlive (self):
        return self.alive

# class reponse de type elevation
class ResponseServerElevation(ResponseServer):

    def __init__ (self):
        ResponseServer.__init__(self)
        self.elevation = elevation.Elevation()
        self.isItElevation = True

    def getElevation (self):
        return self.elevation

# class reponse de type level
class ResponseServerLevel(ResponseServer):

    def __init__ (self):
        ResponseServer.__init__(self)
        self.level = level.Level()
        self.isItLevel = True

    def getLevel (self):
        return self.level
