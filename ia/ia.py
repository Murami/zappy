import sys
import select
import queue

import zappyNetwork
import zappyParser
import inventory


class   Player:
    def __init__ (self, teamName):
        self.decisions = queue.Queue()
        self.teamName = teamName
        self.parser = zappyParser.ZappyParser()
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

    def run (self):
        while True:
            rlist, wlist, elist = select.select([self.net.sock], [self.net.sock], [])



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
