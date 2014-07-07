import sys
import select
import queue
import zappyNetwork
import data

class   Player:
    def __init__ (self, teamName):
        self.decisions = queue.Queue()
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

    def getDecision(self):
        if not self.decisions.empty():
            return;
        elif self.decisions.empty() && fov.getUsed() == True:
            self.decisions.put("voir")
        elif self.decisions.empty() && fov.getUsed() == False:
            self.decisions = self.fov.getClosestFood()

    def updateData(self):
        data.update(self.net.recv());

    def run (self):
        while self.data.alive.isAlive():
            rlist, wlist, elist = select.select([self.net.sock], [self.net.sock], [])
            if (len(rlist) > 0):
                updateData()
            if (len(wlist) > 0):
                getDecision()
            self.net.send(self.decisions.pop())



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
