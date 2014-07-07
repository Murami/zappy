import zappyNetwork
import inventory
import sys

class   Player:
    def __init__ (self, teamName):
        self.teamName = teamName
        try:
            self.net = zappyNetwork.ZappyNetwork(sys.argv[1], sys.argv[2])
        except IndexError:
            print("\033[31mError in connect : "
                  + "\033[33mmissing argument(s)\033[0m")
        self.net.send(teamName)

    def sendMessageToServer (self, msg):
        self.net.send(msg)

def main():
    try:
        player = Player(sys.argv[3])
    except IndexError:
        print("\033[31mError in connect : "
              + "\033[33mmissing argument(s)\033[0m")


try:
    main()
except:
    print("\033[32mSo I quit...\033[0m")
