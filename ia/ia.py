import sys
import select
import queue
import zappyNetwork
import responseServer
import data
from random import randint
from random import choice

static = 0

class   Player:
    def __init__ (self, teamName):
        self.mtdPtr = {
            "inventaire" : responseServer.ResponseServer.isInventory,
            "avance" : responseServer.ResponseServer.isAnswer,
            "gauche" : responseServer.ResponseServer.isAnswer,
            "droite" : responseServer.ResponseServer.isAnswer,
            "voir" : responseServer.ResponseServer.isFov,
            "connect_nbr" : responseServer.ResponseServer.isFreeSlot,
            "fork" : responseServer.ResponseServer.isAnswer,
            "incantation" : responseServer.ResponseServer.isAnswer,
            "expulse" : responseServer.ResponseServer.isExpulse,
            "prend" : responseServer.ResponseServer.isAnswer,
            "pose" : responseServer.ResponseServer.isAnswer,
            "broadcast" : responseServer.ResponseServer.isAnswer
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
        print("test5")
        return (self.mtdPtr[type](response))

    def sendMessageToServer (self, msg):
        print("send : " + msg)
        self.net.send(msg)

    def recvFromServer (self):
        res = self.net.recv()
        print("res = " + res)
        return (self.data.update(res))

    def sendRequests (self):
        while (self.requests.qsize() > 0):
            print("test1")
            request = self.requests.get()
            print("test2")
            self.sendMessageToServer(request)
            print("test3")
            response = self.recvFromServer()
            print("test4")
            while (self.responseIsTypeOf(response, request) == False):
                print("bool = " + str(self.responseIsTypeOf(response, request)))
                print("test6")
                response = self.recvFromServer()
                print("test7")

    def searchFood (self):
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

    def getInventory (self):
        self.addToQueue("inventaire")
        self.sendRequests()

    def getDecision(self):
        print("food = " + str(self.data.inventory.getFood()))
        if self.data.inventory.getFood() < 5:
            self.searchFood()
        else:
<<<<<<< HEAD
            if self.data.inventory.getFood() < 3:
                self.searchFood()
            else:
                print("je recherche des pierres")
            
    def updateData (self):
        self.data.update(self.net.recv())

    def getInventory (self):
        self.net.send("inventory")
        response = ResponseServer()
        while response.isInventory() is False:
            response = self.data.update(self.net.recv())
=======
            print("je recherche des pierres")
>>>>>>> 7376370a3524cba46c4e0a4cfdfc89eb67f8401c

    def run (self):
        while self.data.alive.isAlive():
            self.getInventory()
            print("test")
            self.getDecision()
            # var = self.decisions.get()
            # print("send = " + var)
            # self.net.send(var)
            # self.updateData()
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
