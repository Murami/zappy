import socket

class   ZappyNetwork:

    def __init__ (self, ip, port):
        try:
            self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.sock.settimeout(1)
            self.sock.connect((ip, port))
        except OSError as error:
            print("\033[31mNetwork Error " + str(error.errno) + ": \033[33m" + error.strerror + "\033[00m")
        except socket.error as error:
            print("\033[31mNetwork Error " + str(error[0]) + ": \033[33m" + error[1] + "\033[00m")
        except ConnectionResetError:
            print("\033[34mEnd of connection\033[00m")
        except:
            raise
        self.recv()

    def __del__ (self):
        self.sock.close()

    def send (self, msg):
        self.sock.send("{}\n".format(msg).encode("utf8"))

    def recv (self):
        try:
            return str(self.sock.recv(42420)[:-1], "utf8")
        except:
            print("\033[32m\b\bPetit malin, t'as appuyé sur Ctrl+C\033[0m")
            raise
