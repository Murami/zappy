import socket

class   ZappyNetwork:

    def __init__ (self, ip, port):
        try:
            self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.sock.connect((ip, port))
        except socket.error as error:
            print("\033[31mNetwork Error " + str(error[0]) + ": \033[33m" + error[1] + "\033[00m")

    def __del__ (self):
        self.sock.close()

    def send (self, msg):
        self.sock.send(msg + "\n")

    def recv (self):
        return self.sock.recv(42420)
