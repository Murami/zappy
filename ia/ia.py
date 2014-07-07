import sys
import select
import queue
import zappyNetwork
import data

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

    def getDecision(self):
        if not self.decisions.empty():
            return;
        elif self.decisions.empty() and self.data.fov.getUsed() is True:
            self.decisions.put("voir")
        elif self.decisions.empty() and self.data.fov.getUsed() is False:
            self.decisions = self.data.fov.getClosestFood()

    def updateData (self):
        var = self.net.recv()
        print(var)
        print("@@@@@@@@@@@@@@@@@")
        self.data.update(var);
        
    def run (self):
        while self.data.alive.isAlive():
            rlist, wlist, elist = select.select([self.net.sock], [self.net.sock], [])
            if len(wlist) > 0:
                self.net.send(self.decisions.get())
            self.getDecision()
            if len(rlist) > 0:
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
