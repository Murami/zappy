import sys
import select
import queue
import zappyNetwork
import data
from random import randint
from random import choice

static = 0

class   Player:
    def __init__ (self, teamName):
        self.decisions = queue.Queue()
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
        self.net.recv()
        self.net.recv()

    def sendMessageToServer (self, msg):
        self.net.send(msg)

    def getResponseFromServer (self):
        return self.parser.parse(self.net.recv())

    def searchFood (self):
        global static
        if static < 3:
            self.decisions.put("droite")
            static += 1
        else:
            static = 0
            rand = randint(0,2)
            if (rand == 0):
                self.decisions.put("droite")
            elif (rand == 1):
                self.decisions.put("gauche")
            for i in range(self.data.level.getActualLevel() * 2 + 1):
                self.decisions.put("avance")

    def getDecision(self):
        global static
        if not self.decisions.empty():
            return;
        elif self.decisions.empty() and self.data.fov.getUsed() is True:
            self.decisions.put("voir")
        elif self.decisions.empty() and self.data.fov.getUsed() is False:
            self.data.fov.setUsed(True)
            self.decisions = self.data.fov.getClosestFood()
            print("##################")
            while not self.decisions.empty():
                print(self.decisions.get())
            print("#############")
            exit(-1)
            if self.decisions.empty():
                self.searchFood()
            else:
                static = 0

    def updateData (self):
        print("update")
        msg = self.net.recv()
        print(msg)
        self.data.update(msg);

    def run (self):
        while self.data.alive.isAlive():
            # rlist, wlist, elist = select.select([self.net.sock], [self.net.sock], [])
            self.getDecision()
            var = self.decisions.get()
            print(var)
            self.net.send(var)
            self.updateData()
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
