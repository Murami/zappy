import socket
import sys
import encodings.idna
import unicodedata

class   ZappyNetwork:

    def __init__ (self, ip, port):
        try:
            self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.sock.connect((ip, port))
        except socket.error:
            print("Network Error: connecton failure\n");

    def __del__ (self):
        self.sock.close()

    def send (self, msg):
        self.sock.send(msg + "\n")

    def recv (self):
        return self.sock.recv(42420)
