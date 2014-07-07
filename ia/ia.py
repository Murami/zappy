import zappyNetwork
import inventory
import sys

class   Player:
    """Ceci est la classe player, qui gère un joueur sur la map"""

    def __init__ (self, teamName):
        self.teamName = teamName

    # listes des commandes
    def connect (self):
        self.net = zappyNetwork.ZappyNetwork(sys.argv[1], sys.argv[2])
        self.net.connect(self.teamName)

    def forward (self):
        self.net.communicate("avance")

    def turnRight (self):
        self.net.communicate("droite")

    def turnLeft (self):
        self.net.communicate("gauche")

    def see (self):
        self.net.communicate("voir")

    def inventory (self):
        self.net.communicate("inventaire")

    def takeObject (self, objectName):
        self.net.communicate("prend {0}".format(objectName))

    def placeObject (self, objectName):
        res = self.net.communicate("pose {0}".format(objectName))
        print(res)

    def eject (self):
        self.net.communicate("expulse")

    def broadcast (self, msg):
        self.net.communicate("broadcast " + msg)

    def incantation (self):
        self.net.communicate("incantation")

    def fork(self):
        self.net.communicate("fork")

    def freeSlotNbr (self):
        self.net.communicate("connect_nbr")

################################################################## fin de la classe


def main():
    one = Player("Bichon")
    two = Player("Regnier")
    one.connect()

    # demander au serveur le contenu de l'inventaire coute du temps, mais une fois que c'est fait on replit notre classe inventaire côté client et on peut y accèder plein de fois

    one.inventory()
    one.placeObject("linemate")

main()
