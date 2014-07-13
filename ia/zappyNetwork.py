import socket

class   ZappyNetwork:

    def __init__ (self, ip, port):
        try:
            self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.sock.connect((ip, port))
        except OSError as error:
            print("\033[31mNetwork Error " + str(error.errno) + ": \033[33m" + error.strerror + "\033[00m")
        except socket.error as error:
            print("\033[31mNetwork Error " + str(error[0]) + ": \033[33m" + error[1] + "\033[00m")
        except ConnectionResetError:
            print("\033[34mEnd of connection\033[00m")
        except:
            raise
        self.data = ""
        recv = self.recv()

    def __del__ (self):
        self.sock.close()

    def send (self, msg):
        self.sock.send("{}\n".format(msg).encode("utf8"))

    def recv (self):
        print("!dfjkwljkldjfjksmlkjdlskjmldkj")
        try:
            while (self.data.find("\n") == -1):
                self.data = self.data + str(self.sock.recv(4096), "utf8")
            tmp = self.data.find("\n")
            recv = self.data[0:tmp]
            self.data = self.data[tmp + 1:len(self.data)]
            return recv

        except KeyboardInterrupt:
            print("\033[32m\b\bPetit malin, t'as appuyé sur Ctrl+C\033[0m")
            raise
        except:
            raise
