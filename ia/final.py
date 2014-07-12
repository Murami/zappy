import sys
import select
import queue
import re
from random import randint

import zappyNetwork
import responseServer
import data

class structFuncPtr:
    def __init__ (self, regex, funcPtr):
        self.regex = regex
        self.funcPtr = funcPtr

class   Player:

    def __init__ (self, teamName):
        self.mtdPtr = {
            "inventaire":responseServer.ResponseServer.isInventory,
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
        self.stoneName = ["linemate", "deraumere", "sibur", "mendiane", "phiras", "t\
hystame"]
        self.ressourcesByLevel = {
            1: {"player": 0, "linemate": 1, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0},
            2: {"player": 1, "linemate": 1, "deraumere": 1, "sibur": 1, "mendiane": 0, "phiras": 0, "thystame": 0},
            3: {"player": 1, "linemate": 2, "deraumere": 0, "sibur": 1, "mendiane": 0, "phiras": 2, "thystame": 0},
            4: {"player": 3, "linemate": 1, "deraumere": 1, "sibur": 2, "mendiane": 0, "phiras": 1, "thystame": 0},
            5: {"player": 3, "linemate": 1, "deraumere": 2, "sibur": 1, "mendiane": 3, "phiras": 0, "thystame": 0},
            6: {"player": 5, "linemate": 1, "deraumere": 2, "sibur": 3, "mendiane": 0, "phiras": 1, "thystame": 0},
            7: {"player": 5, "linemate": 2, "deraumere": 2, "sibur": 2, "mendiane": 2, "phiras": 2, "thystame": 0}
        }
        self.taskList = list()
        self.regName= ["come", "getlvl", "mylvl", "here", "way"]
        self.regex = {
            "come": structFuncPtr(re.compile("^come ([0-9]+)$"), self.__come),
            "getlvl": structFuncPtr(re.compile("^getlvl$"), self.__getlvl),
            "mylvl": structFuncPtr(re.compile("^mylvl ([0-9]+)$"), self.__mylvl),
            "here": structFuncPtr(re.compile("^here$"), self.__here),
            "way" : structFuncPtr(re.compile("^on my way$"), self.__way),
            "wait": structFuncPtr(re.compile("^wait ([0-9]+)$"), self.__wait)
        }
        self.isGetLevel = False
        self.isCome = False
        self.staticSeek = 0
        self.staticEvolve = 0
        self.requests = queue.Queue()
        self.data = data.Data()
        self.playerReadyOnMyCase = 0
        self.possibleLeader = True
        self.needToStay = False
        self.isFirstCome = True
        self.iMustWait = False
        try:
            self.net = zappyNetwork.ZappyNetwork(sys.argv[1], int(sys.argv[2]))
        except:
            raise
        self.net.send(teamName)
        if self.net.recv() == "ko":
            print("\033[33mYou can't reach the world yet\033[0m")
            raise GeneratorExit
        tmp = self.net.recv().split(" ")
        print("\033[32mYou have reach a world of size {} {} !!!\033[0m".format(tmp[0\
], tmp[1]))

    def addToQueue (self, request):
        self.requests.put(request)

    def sendToServer (self, msg):
        if msg[:5] == "broad":
            print("\033[32m" + msg + "\033[0m")
        self.net.send(msg)

    def recvFromServer (self):
        recv = self.net.recv()
        if recv[:7] == "message":
            print("\033[31m" + str(recv) + "\033[0m")
        return self.data.update(recv)

    def sendRequests (self):
        response = responseServer.ResponseServer()
        while self.requests.qsize() > 0:
            request = self.requests.get()
            self.sendToServer(request)
            while True:
                response = self.recvFromServer()
                if response.isMessage() is True or\
                   response.isExpulse() is True:
                    self.taskList.insert(0, response)
                elif response.isAlive() is True:
                    print("\033[32mOh no, you're dead !!!\033[0m")
                    exit (0)
                else:
                    break

    def getNeededStones (self):
        res = list()
        for elem in self.stoneName:
            tmp = self.ressourcesByLevel[self.data.level.getActualLevel()][elem]\
                  - self.data.inventory.getStoneCount(elem)
            if tmp < 0:
                tmp = 0
            for i in range(0, tmp):
                res.append(elem)
        return res

    def chooseOtherView (self):
        if self.staticSeek < 3:
            self.addToQueue("droite")
            self.staticSeek += 1
        else:
            self.staticSeek = 0
            rand = randint(0, 2)
            if rand == 0:
                self.addToQueue("droite")
            elif rand == 1:
                self.addToQueue("gauche")
            for i in range(self.data.level.getActualLevel() * 2 + 1):
                self.addToQueue("avance")

    def seekFood (self):
        print("SEEK FOOD")
        if self.data.fov.getUsed() is True:
            self.addToQueue("voir")
        else:
            self.data.fov.setUsed(True)
            self.requests = self.data.fov.getClosestFood(self.data.level.getActualLevel())
            if self.requests.qsize() == 0:
                self.chooseOtherView()
            else:
                self.staticSeek = 0
        self.sendRequests()

    def seekStone (self):
        print("SEEK STONE")
        if self.data.fov.getUsed() is True:
            self.addToQueue("voir")
        else:
            self.data.fov.setUsed(True)
            nearestDistance = 20
            nearest = queue.Queue()
            for elem in self.getNeededStones():
                tmp = self.data.fov.getClosestStone(elem, self.data.level.getActualLevel())
                if tmp.get()[5:] == "prend":
                    nearest = self.data.fov.getClosestStone(elem, self.data.level.getActualLevel())
                    break
                tmp = self.data.fov.getClosestStone(elem, self.data.level.getActualLevel())
                if tmp.qsize() < nearestDistance:
                    nearest = tmp
            self.requests = nearest
            if self.requests.qsize() == 0:
                self.chooseOtherView()
            else:
                self.staticSeek = 0
        self.sendRequests()

    def dropAllStoneOnCase (self):
        for elem in self.stoneName:
            for i in range(self.data.fov.getStoneOnCase(0, elem)):
                self.addToQueue("prend {}".format(elem))

    def putNeededStone (self):
        for elem in self.stoneName:
            for i in range(self.ressourcesByLevel[self.data.level.getActualLevel()][elem]):
                self.addToQueue("pose {}".format(elem))

    def fork (self):
        print("\033[36mFORK\033[0m")

    def evolve (self):
        self.isFirstCome = True
        self.dropAllStoneOnCase()
        self.putNeededStone()
        self.addToQueue("incantation")

    def tryToEvolve (self):
        print("TRY EVOLVE")
        if self.data.getNbrOfMyLevel() >=\
           self.ressourcesByLevel[self.data.level.getActualLevel()]["player"]:
            print("EVOLVE COND 1 : il y a assez de joueur")
            print(self.playerReadyOnMyCase)
            if self.playerReadyOnMyCase >=\
               self.ressourcesByLevel[self.data.level.getActualLevel()]["player"]:
                print("EVOLVE COND 1'1 : c'est le evolve")
                self.evolve()
            elif self.isFirstCome == True:
                print("EVOLVE COND 1''2; cc'est le broadcast come")
                self.isFirstCome = False
                self.addToQueue("broadcast come " + str(self.data.level.getActualLevel()))
        else:
            print("EVOLVE COND 2 : il y a pas assez de joueur")
            if self.staticEvolve == 0:
                print("EVOLVE COND 2'1 :  je demande les niveaux")
                self.addToQueue("broadcast getlvl")
                self.data.reinitializeListLevel()
            else:
                print("EVOLVE COND 2''2")
                self.staticEvolve += 1
                if self.staticEvolve >= 5:
                    print("EVOLVE COND 221")
                    if self.data.getNbrOfLowerLevel() >=\
                       self.ressourcesByLevel[self.data.level.getActualLevel()]["player"]:
                        self.fork()
                    self.playerReadyOnMyCase = 0
                    self.staticEvolve = 0
        self.sendRequests()

    def transformNbrInDirection (self, nb):
        if nb == 0:
            self.addToQueue("broadcast here")
            self.needToStay = True
        elif nb == 1:
            self.addToQueue("avance")
        elif nb == 2:
            self.addToQueue("avance")
        elif nb == 3:
            self.addToQueue("gauche")
            self.addToQueue("avance")
        elif nb == 4:
            self.addToQueue("gauche")
            self.addToQueue("avance")
        elif nb == 5:
            self.addToQueue("gauche")
            self.addToQueue("gauche")
            self.addToQueue("avance")
        elif nb == 6:
            self.addToQueue("droite")
            self.addToQueue("avance")
        elif nb == 7:
            self.addToQueue("droite")
            self.addToQueue("avance")
        elif nb == 8:
            self.addToQueue("avance")

    def __come (self, exp, message):
        if self.isCome == True:
            return
        if self.data.level.getActualLevel() == int(exp.group(1)):
            if self.needToStay is False:
                self.transformNbrInDirection(message.getDirection())
                self.addToQueue("broadcast on my way")
            self.possibleLeader = False
            self.isCome = True

    def __getlvl (self, exp, message):
        if self.isGetLevel == True:
            return
        self.addToQueue("broadcast mylvl " + str(self.data.level.getActualLevel()))
        self.isGetLevel = True

    def __mylvl (self, exp, message):
        self.data.addLevelToList(int(exp.group(1)))

    def __here (self, exp, message):
        print("##############################################################")
        self.playerReadyOnMyCase += 1

    def __way (self, exp, message):
        if self.isWay == True:
            return
        if message.getDirection() == 0:
            self.addToQueue("wait " + str(self.data.level.getActualLevel()))
        self.addToQueue("broadcast come " + str(self.data.level.getActualLevel()))
        self.isWay = True

    def __wait (self, exp, message):
        if exp.group(1) == self.data.level.getActualLevel()\
           and message.getDirection() == 0:
            self.iMustWait = True

    def manageMessage (self, message):
        for elem in self.regName:
            res = self.regex[elem].regex.search(message.getMessage())
            if res is not None:
                self.regex[elem].funcPtr(res, message)

    def manageTaskList (self):
        if len(self.taskList) == 0:
            return
        self.isCome = False
        self.isGetLevel = False
        self.isWay = False
        for elem in self.taskList:
            if elem.isMessage() is True:
                self.manageMessage(elem.getMessage())
        self.sendRequests()
        self.taskList = list()

    def getInventory(self):
        self.addToQueue("inventaire")
        self.sendRequests()

    def getDecision (self):
        print("\nDECISION")
        self.possibleLeader = True
        self.manageTaskList()
        if self.data.inventory.getFood() <= 3:
            self.playerReadyOnMyCase = 0
            self.needToStay = False
            self.isFirstCome = True
            while self.data.inventory.getFood() < 10:
                self.seekFood()
                self.getInventory()
        elif self.iMustWait == False and self.possibleLeader is True and len(self.getNeededStones()) > 0:
            self.playerReadyOnMyCase = 0
            self.needToStay = False
            self.isFirstCome = True
            self.seekStone()
        elif self.iMustWait == False and self.possibleLeader == True:
            self.tryToEvolve()

    def run (self):
        while self.data.alive.isAlive() is True:
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



main()






