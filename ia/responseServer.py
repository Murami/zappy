import inventory
import fov
import message
import expulse
import answer
import value

class ResponseServer:
    """ classe mere """

    def __init__ (self):
        self.isItInventory = False
        self.isItFov = False
        self.isItMessage = False
        self.isItExpulse = False
        self.isItAnswer = False
        self.isItValue = False

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

    def isValue (self):
        return self.isItValue

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
class ResponseServerValue(ResponseServer):

    def __init__ (self):
        ResponseServer.__init__(self)
        self.value = value.Value()
        self.isItValue = True

    def getValue (self):
        return self.value