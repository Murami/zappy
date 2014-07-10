
class Inventory:
    """ Classe inventaire qui sera actualiser a chaque fois qu'on envoi "inventaire" au serveur """

    def __init__ (self):
        self.nourriture = 10
        self.stones = {
            "linemate":0,
            "deraumere":0,
            "sibur":0,
            "mendiane":0,
            "phiras":0,
            "thystame":0
        }

    def getFood (self):
        return self.nourriture
        
    def getStoneCount(self, stoneName):
        print("getStoneCount")
        try:
            return self.stones[stoneName]
        except KeyError:
            print("\033[31mError in getStoneCount : "
                  + "\033[33munknown key ['" + stoneName + "']\033[0m")
        except NameError:
            print("\033[31mError in getStoneCount : "
                  + "\033[33mbad name\033[0m")
        return 0
