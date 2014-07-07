import zappyNetwork
import inventory
import sys
import queue
import zappyParser

class   Player:
    def __init__ (self, teamName):
        self.responses = queue.Queue()
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

    def IaReceive (self):
        p = zappyParser.ZappyParser()
        self.responses.put(p.parse(self.net.recv()))

    def sendMessageToServer (self, msg):
        self.net.send(msg)

    def getResponseFromServer (self):
        if not self.responses.empty():
            return self.responses.get()
        else:
            return None


def main():
    try:
        player = Player(sys.argv[3])
    except IndexError:
        print("\033[31mError in connect : "
              + "\033[33mmissing argument(s)\033[0m")
        raise

    player.sendMessageToServer("avance")
    player.IaReceive()
    tmp = player.getResponseFromServer()
    if tmp.isAnswer():
        print(tmp.getAnswer.isOk())
        
        
    




try:
    main()
except BaseException as err:
    print("\033[34m" + str(err) + "\033[0m")
    print("\033[36mSo I quit...\033[0m")
    
