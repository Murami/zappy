import zappyNetwork
import inventory
import sys

class   Player:
    """Ceci est la classe player, qui gère un joueur sur la map"""

    def __init__ (self, teamName):
        self.teamName = teamName
        self.net = zappyNetwork.ZappyNetwork(sys.argv[1], sys.argv[2])
        self.net.send(teamName)

    def sendMessageToServer (self, msg):
        self.net.send(msg)

################################################################## fin de la classe


def main():
    try:
        player = Player(sys.argv[3])
    except IndexError:
        print("\033[31mError in connect : "
              + "\033[33mmissing argument(s)\033[0m")


    # demander au serveur le contenu de l'inventaire coute du temps, mais une fois que c'est fait on replit notre classe inventaire côté client et on peut y accèder plein de fois



main()
