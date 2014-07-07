import socket

class   ZappyNetwork:

    def __init__ (self, ip, port):
        try:
            self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.sock.connect((ip, port))
        except socket.error as serr:
            print(serr);

    def __del__ (self):
        self.sock.close()

    def send (self, msg):
        self.sock.send(msg + "\n")

    def recv (self):
        return self.sock.recv(42420)
