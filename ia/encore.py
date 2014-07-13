import sys
import select
import queue
import re
import os
from random import randint

import zappyNetwork
import responseServer
import data
import managePlayer
    

class structFuncPtr:
    def __init__ (self, regex, funcPtr):
        self.regex = regex
        self.funcPtr = funcPtr

class Player:

    def __init__ (self, teamName):
        self.teamName = teamName
        self.wait = False
        self.leader = False
        self.eating = False
        self.staticGetlvl = 0
        self.staticForSeek = 0
        self.forking = False
        self.playerReadyOnMyCase = 0
        self.theQueue = queue.Queue()
        self.responseQueue = queue.Queue()
        self.data = data.Data()
        self.regStatusName = ["inventaire", "voir", "avance", "gauche", "droite", "prend", "pose", "incantation", "expulse", "getlvl", "mylvl", "come", "onMyWay", "connect_nbr", "fork"]
        self.regexStatus = {
            "inventaire" : structFuncPtr(re.compile("^inventaire$"), managePlayer.manageInventaire),
            "voir" : structFuncPtr(re.compile("^voir$"), managePlayer.manageVoir),
            "avance" : structFuncPtr(re.compile("^avance$"),managePlayer.manageAvance),
            "droite" : structFuncPtr(re.compile("^droite$"), managePlayer.manageDroite),
            "gauche" : structFuncPtr(re.compile("^gauche$"), managePlayer.manageGauche),
            "prend" : structFuncPtr(re.compile("^prend [a-z]+$"), managePlayer.managePrend),
            "pose" : structFuncPtr(re.compile("^pose [a-z]+$"), managePlayer.managePose),
            "incantation" : structFuncPtr(re.compile("^incantation$"), managePlayer.manageIncantation),
            "expulse" : structFuncPtr(re.compile("^expulse$"), managePlayer.manageExpulse),
            "getlvl" : structFuncPtr(re.compile("^broadcast getlvl ([a-zA-Z0-9]+)$"), managePlayer.manageGetlvl),
            "mylvl" : structFuncPtr(re.compile("^broadcast mylvl ([0-9]+) ([a-zA-Z0-9]+)$"), managePlayer.manageMylvl),
            "come" : structFuncPtr(re.compile("^broadcast come ([0-9]+) ([a-zA-Z0-9]+)$"), managePlayer.manageCome),
            "onMyWay" : structFuncPtr(re.compile("^broadcast onMyWay ([0-9]+) ([a-zA-Z0-9]+)$"), managePlayer.manageOnMyWay),
            "connect_nbr" : structFuncPtr(re.compile("^connect_nbr$"), managePlayer.manageConnectNbr),
            "fork" : structFuncPtr(re.compile("^fork$"), managePlayer.manageFork)
        }
        self.regexResponse = {
            "onMyWay" : re.compile("^onMyWay ([0-9]+) ([a-zA-Z0-9]+)$"),
            "come" : re.compile("^come ([0-9]+) ([a-zA-Z0-9]+)$"),
            "getlvl" : re.compile("^getlvl ([a-zA-Z0-9]+)$"),
            "mylvl" : re.compile("^mylvl ([0-9]+) ([a-zA-Z0-9]+)$")
        }
        self.stoneName = ["linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"]
        self.ressourcesByLevel = {
            1: {"player": 0, "linemate": 1, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0},
            2: {"player": 1, "linemate": 1, "deraumere": 1, "sibur": 1, "mendiane": 0, "phiras": 0, "thystame": 0},
            3: {"player": 1, "linemate": 2, "deraumere": 0, "sibur": 1, "mendiane": 0, "phiras": 2, "thystame": 0},
            4: {"player": 3, "linemate": 1, "deraumere": 1, "sibur": 2, "mendiane": 0, "phiras": 1, "thystame": 0},
            5: {"player": 3, "linemate": 1, "deraumere": 2, "sibur": 1, "mendiane": 3, "phiras": 0, "thystame": 0},
            6: {"player": 5, "linemate": 1, "deraumere": 2, "sibur": 3, "mendiane": 0, "phiras": 1, "thystame": 0},
            7: {"player": 5, "linemate": 2, "deraumere": 2, "sibur": 2, "mendiane": 2, "phiras": 2, "thystame": 1}
        }

        try:
            self.net = zappyNetwork.ZappyNetwork(sys.argv[1], int(sys.argv[2]))
        except:
            raise
        self.net.send(teamName)
        recv = self.net.recv()
        if recv == "ko":
            print("\033[33mYou can't reach the world yet\033[0m")
            raise GeneratorExit
        else:
            self.data.oldFreeSlot.freeSlot = int(recv)
        tmp = self.net.recv().split(" ")
        print("\033[32mYou have reach a world of size {} {} !!!\033[0m".format(tmp[0], tmp[1]))

    def transformNbrInDirection (self, nb):
        if nb == 1:
            self.theQueue.put("avance")
        elif nb == 2:
            self.theQueue.put("avance")
        elif nb == 3:
            self.theQueue.put("gauche")
            self.theQueue.put("avance")
        elif nb == 4:
            self.theQueue.put("gauche")
            self.theQueue.put("avance")
        elif nb == 5:
            self.theQueue.put("gauche")
            self.theQueue.put("gauche")
            self.theQueue.put("avance")
        elif nb == 6:
            self.theQueue.put("droite")
            self.theQueue.put("avance")
        elif nb == 7:
            self.theQueue.put("droite")
            self.theQueue.put("avance")
        elif nb == 8:
            self.theQueue.put("avance")

    def manageResponse (self, response):
        if response.isMessage() is True:
            exp = self.regexResponse["onMyWay"].search(response.getMessage().getMessage())
            if exp is not None\
               and self.leader is True\
               and self.eating is False\
               and int(exp.group(1)) == self.data.level.getActualLevel()\
               and exp.group(2) == self.teamName:
                if response.getMessage().getDirection() == 0:
                    self.playerReadyOnMyCase += 1
                self.theQueue.put("broadcast come "
                                  + str(self.data.level.getActualLevel())
                                  + " " + self.teamName)

            exp = self.regexResponse["come"].search(response.getMessage().getMessage())
            if exp is not None\
               and self.eating is False\
               and int(exp.group(1)) == self.data.level.getActualLevel()\
               and exp.group(2) == self.teamName:
                self.leader = False
                if response.getMessage().getDirection() == 0:
                    self.wait = True
                    self.theQueue.put("droite")
                    self.theQueue.put("droite")
                    self.theQueue.put("avance")
                else:
                    self.theQueue.put("broadcast onMyWay "
                                      + str(self.data.level.getActualLevel())
                                      + " " + self.teamName)
                    self.transformNbrInDirection(response.getMessage().getDirection())

            exp = self.regexResponse["getlvl"].search(response.getMessage().getMessage())
            if exp is not None\
               and exp.group(1) == self.teamName:
                print("->>>>>>>>>>>>>>>>>>> j'envoie un mylvl <<<<<<<<<<<<<<<<<<<<<<<-")
                self.theQueue.put("broadcast mylvl "
                                  + str(self.data.level.getActualLevel())
                                  + " " + self.teamName)

            exp = self.regexResponse["mylvl"].search(response.getMessage().getMessage())
            if exp is not None\
               and exp.group(2) == self.teamName:
                print("->>>>>>>>>>>>>>>>>>> je recoie un mylvl <<<<<<<<<<<<<<<<<<<<<<<-")
                self.data.addLevelToList(int(exp.group(1)))

        elif response.isFreeSlot() is True:
            print(str(self.data.newFreeSlot.getFreeSlot()) + " - " + str(self.data.oldFreeSlot.getFreeSlot()))
            if self.data.newFreeSlot.getFreeSlot() > \
               self.data.oldFreeSlot.getFreeSlot() and \
               self.forking == True:
                self.forking = False;
                self.doTheFork()
                self.staticGetlvl = 0
            if self.data.oldFreeSlot.getFreeSlot() != \
               self.data.newFreeSlot.getFreeSlot():
                self.data.oldFreeSlot.freeSlot = self.data.newFreeSlot.getFreeSlot()

    # gestion du fork
    def doTheFork (self):
        newPid = os.fork()
        if newPid == 0:
            os.system("python " + sys.argv[0] + " " + sys.argv[1] + " " + sys.argv[2] + " " + sys.argv[3])

    # gestion du serveur
    def recvFromServer (self):
        recv = self.net.recv()
        print("recv " + str(recv))
        response = self.data.update(recv)
        self.manageResponse(response)
        return response

    def sendToServer (self, msg):
        print("send " + str(msg))
        self.net.send(msg)

    # gestion des queues
    def getStatus (self, msg):
        if self.responseQueue.qsize() == 0:
            return False
        while self.responseQueue.qsize() > 0:
            response = self.responseQueue.get()
            for elem in self.regStatusName:
                exp = self.regexStatus[elem].regex.search(msg)
                if exp is not None:
                    print("regex <" + msg + "> = " + str(self.regexStatus[elem].funcPtr(self, response, exp)))
                    if self.regexStatus[elem].funcPtr(self, response, exp) is True:
                        self.responseQueue = queue.Queue()
                        return True
            return False

    def sendRequest (self):
        print("\n############")
        if self.theQueue.qsize() == 0:
            return
        msg = self.theQueue.get()
        print("------------["+ msg +"]--------------")
        self.sendToServer(msg)
        while (self.getStatus(msg) == False):
            self.sendToServer("inventaire")
            response = self.recvFromServer()
            if response.isAlive() is True:
                self.data.alive.killHim()
                return
            while (response.isInventory() is False):
                self.responseQueue.put(response)
                response = self.recvFromServer()
                if response.isAlive() is True:
                    self.data.alive.killHim()
                    return
                if self.data.inventory.getFood() <= 9 and self.eating == False:
                    print("manque de nouriture")
                    return

    # getion des recherches
    def chooseOtherView (self):
        tempo = queue.Queue()
        if self.staticForSeek < 3:
            self.staticForSeek += 1
            tempo.put("droite")
        else:
            self.staticForSeek = 0
            rand = randint(0, 2)
            if rand == 0:
                tempo.put("droite")
            elif rand == 1:
                tempo.put("gauche")
            for i in range(self.data.level.getActualLevel() * 2 + 1):
                tempo.put("avance")
        return tempo

    # gestion des pierres
    def getNeededStones (self):
        res = list()
        for elem in self.stoneName:
            tmp = self.ressourcesByLevel[self.data.level.getActualLevel()][elem] - self.data.inventory.getStoneCount(elem)
            if tmp > 0:
                res.append(elem)
        return res

    def seekStone (self):
        tempo = queue.Queue()
        if self.data.fov.getUsed() is True:
            tempo.put("voir")
        else:
            self.data.fov.setUsed(True)
            nearestDistance = 20
            nearest = queue.Queue()
            for elem in self.getNeededStones():
                print(elem)
                tmp = self.data.fov.getClosestStone(elem, self.data.level.getActualLevel())
                if tmp.qsize() > 0 and tmp.get()[5:] == "prend":
                    nearest = self.data.fov.getClosestStone(elem, self.data.level.getActualLevel())
                    break
                tmp = self.data.fov.getClosestStone(elem, self.data.level.getActualLevel())
                if tmp.qsize() > 0 and tmp.qsize() < nearestDistance:
                    nearest = tmp
            tempo = nearest
            if tempo.qsize() == 0:
                tempo = self.chooseOtherView()
            else:
                self.staticSeek = 0
        return tempo

    # gestion de la bouffe
    def seekFood (self):
        tempo = queue.Queue()
        if self.data.fov.getUsed() is True:
            tempo.put("voir")
            self.data.fov.setUsed(False)
        else:
            self.data.fov.setUsed(True)
            tempo = self.data.fov.getClosestFood(self.data.level.getActualLevel())
            if tempo.qsize() == 0:
                tempo = self.chooseOtherView()
            else:
                self.staticForSeek = 0
        return tempo


    # gestion evolution

    def dropAllStoneOnCase (self):
        for elem in self.stoneName:
            for i in range(self.data.fov.getStoneOnCase(0, elem)):
                self.theQueue.put("prend {}".format(elem))

    def putNeededStone (self):
        for elem in self.stoneName:
            for i in range(self.ressourcesByLevel[self.data.level.getActualLevel()][elem]):
                self.theQueue.put("pose {}".format(elem))

    def evolve (self):
        self.dropAllStoneOnCase()
        self.putNeededStone()
        self.theQueue.put("incantation")

    # principale
    def run (self):
        while self.data.alive.isAlive() is True:
            if self.theQueue.qsize() == 0:
                if self.data.inventory.getFood() <= 9 and self.eating is False:
                    self.eating = True
                    self.wait = False
                    self.leader = False
                    self.staticGetlvl = 0
                    self.playerReadyOnMyCase = 0
                    self.data.reinitializeListLevel()
                    self.theQueue = self.seekFood()
                elif self.eating is True:
                    if self.data.inventory.getFood() <= 20:
                        self.theQueue = self.seekFood()
                    else:
                        self.eating = False
                elif self.wait is False:
                    print("je n'attend pas")
                    if self.leader is True:
                        print("je suis leader")
                        if self.playerReadyOnMyCase >=\
                           self.ressourcesByLevel[self.data.level.getActualLevel()]["player"]:
                            print("il y a assez de joueur sur ma case")
                            self.evolve()
                    elif self.forking is False:
                        print("je ne fork pas")
                        if len(self.getNeededStones()) > 0:
                            print("je cherche des pierres")
                            self.theQueue = self.seekStone()
                        elif self.data.getNbrOfMyLevel() <\
                             self.ressourcesByLevel[self.data.level.getActualLevel()]["player"]:
                            print("il n'y pas assez de joueur sur la map")
                            if self.staticGetlvl == 0:
                                self.data.reinitializeListLevel()
                                self.theQueue.put("broadcast getlvl " + self.teamName)
                            elif self.staticGetlvl >= 10:
                                self.staticGetlvl = -1
                                self.data.reinitializeListLevel()
                                self.theQueue.put("fork")
                                self.forking = True
                                print("JE FORK")
                            self.staticGetlvl += 1
                        else:
                            print("le cas par defaut")
                            self.leader = True
                            if self.data.level.getActualLevel() > 1:
                                self.theQueue.put("broadcast come "
                                                  + str(self.data.level.getActualLevel())
                                                  + " " + self.teamName)
                self.theQueue.put("connect_nbr")
            self.sendRequest()

def main ():
    try:
        player = Player(sys.argv[3])
    except IndexError:
        print("\033[31mUsage : "
              + "\033[33mpython " + str(sys.argv[0]) + " ip port teamName\033[0m")
        raise
    player.run()

main ()
