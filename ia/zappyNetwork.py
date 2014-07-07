import socket
import sys
import encodings.idna
import unicodedata

### ceci est la classe que doit me fournir pinon, en mieux bien sûr ;)

class   ZappyNetwork:
    """Classe qui sera appelé par les joueurs lors de l'envoie de données"""

    def __init__ (self, ip, port):
        self.ip = ip
        self.port = port
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def __del__ (self):
        self.sock.close()

    def connect(self, teamName):
        self.sock.connect((self.ip, int(self.port)))
        self.sock.send(bytes(teamName + "\n", "utf-8"))
        receive = str(self.sock.recv(1024), "utf-8")
        print("HERE : ", receive)
        if receive  == "ko\n":
            print("Error")

    def communicate (self, msg):
        self.sock.send(bytes(msg + "\n", "utf-8"))
        return str(self.sock.recv(1024), "utf-8")
