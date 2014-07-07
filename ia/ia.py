import zappyNetwork
import inventory
import sys

class   Player:
    def __init__ (self, teamName):
        self.teamName = teamName
        try:
            self.net = zappyNetwork.ZappyNetwork(sys.argv[1], int(sys.argv[2]))
        except IndexError:
            print("\033[31mError in connect : "
                  + "\033[33mmissing argument(s)\033[0m")
        except:
            raise
        self.net.send(teamName)

    def sendMessageToServer (self, msg):
        self.net.send(msg)






def main():
    try:
        player = Player(sys.argv[3])
    except IndexError:
        print("\033[31mError in connect : "
              + "\033[33mmissing argument(s)\033[0m")
        raise
    while 10:
        player.sendMessageToServer("avance")

try:
    main()
except BaseException as err:
    print("\033[34m" + str(err) + "\033[0m")
    print("\033[36mSo I quit...\033[0m")
    
