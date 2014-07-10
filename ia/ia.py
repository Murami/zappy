import sys
import select
import queue
import zappyNetwork
import responseServer
import data
import re
from random import randint
from random import choice

static = 0
getlvl = 0

class   Player:
    def __init__ (self, teamName):
        self.mtdPtr = {
            "inventaire": responseServer.ResponseServer.isInventory,
            "avance": responseServer.ResponseServer.isAnswer,
            "gauche": responseServer.ResponseServer.isAnswer,
            "droite": responseServer.ResponseServer.isAnswer,
            "voir": responseServer.ResponseServer.isFov,
            "connect_nbr": responseServer.ResponseServer.isFreeSlot,
            "fork": responseServer.ResponseServer.isAnswer,
            "incantation": responseServer.ResponseServer.isLevel,
            "expulse": responseServer.ResponseServer.isExpulse,
            "prend": responseServer.ResponseServer.isAnswer,
            "pose": responseServer.ResponseServer.isAnswer,
            "broadcast": responseServer.ResponseServer.isAnswer
        }
        self.stoneName = ["linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"]
        self.ressourcesByLevel = {
            1: {"player": 0, "linemate": 1, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0},
            2: {"player": 1, "linemate": 1, "deraumere": 1, "sibur": 1, "mendiane": 0, "phiras": 0, "thystame": 0},
            3: {"player": 1, "linemate": 2, "deraumere": 0, "sibur": 1, "mendiane": 0, "phiras": 2, "thystame": 0},
            4: {"player": 3, "linemate": 1, "deraumere": 1, "sibur": 2, "mendiane": 0, "phiras": 1, "thystame": 0},
            5: {"player": 3, "linemate": 1, "deraumere": 2, "sibur": 1, "mendiane": 3, "phiras": 0, "thystame": 0},
            6: {"player": 5, "linemate": 1, "deraumere": 2, "sibur": 3, "mendiane": 0, "phiras": 1, "thystame": 0},
            7: {"player": 5, "linemate": 2, "deraumere": 2, "sibur": 2, "mendiane": 2, "phiras": 2, "thystame": 0}
        }
        self.regex = {
            "getlvl": re.compile("^getlvl$"),
            "mylvl": re.compile("^mylvl ([0-9]+)$"),
            "regroup": re.compile("^regroup ([0-9]+)$")
        }
        self.requests = queue.Queue()
        self.data = data.Data()
        self.teamName = teamName
        try:
            self.net = zappyNetwork.ZappyNetwork(sys.argv[1], int(sys.argv[2]))
        except IndexError:
            print("\033[31mError in connect : "
                  + "\033[33mmissing argument(s)\033[0m")
        except:
            raise
        self.net.send(teamName)
        if self.net.recv() == "ko":
            print("\033[33mYou can't reach the world yet\033[0m")
            raise GeneratorExit
        tmp = self.net.recv().split(" ")
        print("\033[32mYou have reach a world of size {} {} !!!\033[0m".format(tmp[0], tmp[1]))

    def addToQueue(self, request):
        self.requests.put(request)

    def responseIsTypeOf(self, response, type):
        ret = self.mtdPtr[type.split(" ")[0]](response)
        print("bool - " + type.split(" ")[0] + " = " + str(ret))
        return (self.mtdPtr[type.split(" ")[0]](response))

    def sendMessageToServer (self, msg):
        print("send = " + msg)
        self.net.send(msg)

    def manageMessage(self, message):
        if (self.regex["getlvl"].search(message) is not None):
            self.data.lvlNeeded = True;
        elif (self.regex["mylvl"].search(message) is not None):
            regex = self.regex["mylvl"].search(message)
            self.data.listOtherLevel[int(regex.group(1))] += 1
        elif (self.regex["regroup"].search(message) is not None):
            regex = self.regex["regroup"].search(message)
            if (int(regex.group(1)) == self.data.level.getActualLevel()):
                self.data.direction = self.data.message.getDirection()

    def recvFromServer (self):
        recv = self.net.recv()
        print("recv = " + recv)
        response = self.data.update(recv)
        if (response.isMessage() is True):
            self.manageMessage(self.data.message.getMessage())
        return (response)

    def sendRequests (self):
        while (self.requests.qsize() > 0):
            request = self.requests.get()
            self.sendMessageToServer(request)
            response = self.recvFromServer()
            while (self.responseIsTypeOf(response, request) == False and response.isAnswer() == False):
                response = self.recvFromServer()

    def searchFood (self):
        print("searchFood")
        global static
        if self.data.fov.getUsed() is True:
            self.addToQueue("voir")
        elif self.data.fov.getUsed() is False:
            self.data.fov.setUsed(True)
            self.requests = self.data.fov.getClosestFood(self.data.level.getActualLevel())
            if self.requests.qsize() == 0:
                if static < 3:
                    self.addToQueue("droite")
                    static += 1
                else:
                    static = 0
                    rand = randint(0,2)
                    if (rand == 0):
                        self.addToQueue("droite")
                    elif (rand == 1):
                        self.addToQueue("gauche")
                    for i in range(self.data.level.getActualLevel() * 2 + 1):
                        self.addToQueue("avance")
            else:
                static = 0
        self.sendRequests()

    def stoneNeeded (self):
        if (self.data.inventory.getStoneCount("linemate") <
            self.ressourcesByLevel[self.data.level.getActualLevel()]["linemate"]):
            return ("linemate")
        if (self.data.inventory.getStoneCount("deraumere") <
            self.ressourcesByLevel[self.data.level.getActualLevel()]["deraumere"]):
            return ("deraumere")
        if (self.data.inventory.getStoneCount("sibur") <
            self.ressourcesByLevel[self.data.level.getActualLevel()]["sibur"]):
            return ("sibur")
        if (self.data.inventory.getStoneCount("mendiane") <
            self.ressourcesByLevel[self.data.level.getActualLevel()]["mendiane"]):
            return ("mendiane")
        if (self.data.inventory.getStoneCount("phiras") <
            self.ressourcesByLevel[self.data.level.getActualLevel()]["phiras"]):
            return ("phiras")
        if (self.data.inventory.getStoneCount("thystame") <
            self.ressourcesByLevel[self.data.level.getActualLevel()]["thystame"]):
            return ("thystame")

    def searchStone (self, stone):
        print("searchStone")
        global static
        if self.data.fov.getUsed() is True:
            self.addToQueue("voir")
        elif self.data.fov.getUsed() is False:
            self.data.fov.setUsed(True)
            self.requests = self.data.fov.getClosestStone(stone, self.data.level.getActualLevel())
            if self.requests.qsize() == 0:
                if static < 3:
                    self.addToQueue("droite")
                    static += 1
                else:
                    static = 0
                    rand = randint(0,2)
                    if (rand == 0):
                        self.addToQueue("droite")
                    elif (rand == 1):
                        self.addToQueue("gauche")
                    for i in range(self.data.level.getActualLevel() * 2 + 1):
                        self.addToQueue("avance")
            else:
                static = 0
        self.sendRequests()

    def getInventory (self):
        print("inventory")
        self.addToQueue("inventaire")
        self.sendRequests()

    def gathering (self):
        print("gathering")
        self.addToQueue("broadcast regroup " + str(self.data.level.getActualLevel()))

    def dropAllStone (self):
        for elem in self.stoneName:
            for i in range(self.data.fov.getStoneOnCase(0, elem)):
                self.addToQueue("prend {}".format(elem))

    def putNeededStone (self):
        for elem in self.stoneName:
            for i in range(self.ressourcesByLevel[self.data.level.getActualLevel()][elem]):
                self.addToQueue("pose {}".format(elem))

    def evolutionProcess (self):
        print("evolution process")
        self.dropAllStone()
        self.putNeededStone()
        self.addToQueue("incantation")

    def fork (self):
        print("fork")
        self.addToQueue("fork")

    def evolution (self):
        print("evolution")
        global getlvl
        if (getlvl == -1):
            self.addToQueue("broadcast getlvl")
        if (getlvl > 20):
            self.data.reinitializeListLevel()
            getlvl = -1
        else:
            getlvl += 1
        print("nbrOfLevel " + str(self.data.level.getActualLevel()) + " = " + str(self.data.getNbrOfLevel(self.data.level.getActualLevel())))
        print("player needed = " + str(self.ressourcesByLevel[self.data.level.getActualLevel()]["player"]))
        if (self.data.level.getActualLevel() == 1):
            self.evolutionProcess()
        elif (self.data.getNbrOfLevel(self.data.level.getActualLevel()) >=
              self.ressourcesByLevel[self.data.level.getActualLevel()]["player"]):
            self.gathering()
        # elif (self.data.getNbrofLowerLevel(self.data.level.getActualLevel()) >=
        #       self.ressourcesByLevel[self.data.level.getActualLevel()]["player"]):
        #     self.fork()

    def transformNbrInDirection (self, nb):
        if nb == 1:
            self.addToQueue("avance")
        elif nb == 2:
            self.addToQueue("avance")
            self.addToQueue("gauche")
            self.addToQueue("avance")
        elif nb == 3:
            self.addToQueue("gauche")
            self.addToQueue("avance")
        elif nb == 4:
            self.addToQueue("gauche")
            self.addToQueue("avance")
            self.addToQueue("gauche")
            self.addToQueue("avance")
        elif nb == 5:
            self.addToQueue("gauche")
            self.addToQueue("gauche")
            self.addToQueue("avance")
        elif nb == 6:
            self.addToQueue("droite")
            self.addToQueue("avance")
            self.addToQueue("droite")
            self.addToQueue("avance")
        elif nb == 7:
            self.addToQueue("droite")
            self.addToQueue("avance")
        elif nb == 8:
            self.addToQueue("avance")
            self.addToQueue("droite")
            self.addToQueue("avance")

        

    def getDecision (self):
        stone = self.stoneNeeded()
        if self.data.inventory.getFood() < 11:
            while (self.data.inventory.getFood() < 20):
                self.searchFood()
                self.getInventory()
        elif (self.data.lvlNeeded == True):
            self.addToQueue("broadcast mylvl " + str(self.data.level.getActualLevel()))
            self.data.lvlNeeded = False
        elif (stone is not None):
            self.searchStone(stone)
        else:
            self.evolution()

    def run (self):
        while self.data.alive.isAlive():
            self.getInventory()
            self.getDecision()
        print("\033[32mOh no, you're dead !!!\033[0m")


def main():
    try:
        player = Player(sys.argv[3])
    except IndexError:
        print("\033[31mError in connect : "
              + "\033[33mmissing argument(s)\033[0m")
        raise
    player.run()


# try:
#     main()
# except BaseException as err:
#     print("\033[34m" + str(err) + "\033[0m")
#     print("\033[36mSo I quit...\033[0m")

main()
