import socket

class   ZappyNetwork:

    def __init__ (self, ip, port):
        try:
            self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.sock.connect((ip, port))
        except OSError as error:
            if error.errno == 104:
                print("\033[34mEnd of connection\033[00m")
            else:
                print("\033[31mNetwork Error " + str(error.errno) + ": \033[33m" + error.strerror + "\033[00m")
        except socket.error as error:
            if error[0] == 104:
                print("\033[34mEnd of connection\033[00m")
            else:
                print("\033[31mNetwork Error " + str(error[0]) + ": \033[33m" + error[1] + "\033[00m")
        except:
            raise

    def __del__ (self):
        self.sock.close()

    def send (self, msg):
        self.sock.send("{}\n".format(msg).encode("utf8"))

    def recv (self):
        return "{}\n".format(self.sock.recv(42420)).encode("utf8")
