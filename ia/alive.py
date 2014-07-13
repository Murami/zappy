
class Alive:

    def __init__ (self):
        self.isItAlive = True

    def isAlive (self):
        return self.isItAlive

    def killHim (self):
        self.isItAlive = False
