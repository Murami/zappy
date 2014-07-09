import re # for regular expression
import responseServer

class structFuncPtr:
    def __init__ (self, regex, funcPtr):
        self.regex = regex
        self.funcPtr = funcPtr

class ZappyParser:
    """ Classe qui parse les données envoyées par le serveur et qui renvoie un héritage """

    def __init__ (self):
        # nom des trucs a tester
        self.names = ["inventory", "fov", "message", "expulse", "answer", "freeSlot"]

        # liste de structures liant les regex et leur fonction de parsing
        self.tab = {}
        self.tab["inventory"] = structFuncPtr(re.compile("^{[ ]*nourriture[ ]+([0-9]+),[ ]*linemate[ ]+([0-9]+),[ ]*deraumere[ ]+([0-9]+),[ ]*sibur[ ]+([0-9]+),[ ]*mendiane[ ]+([0-9]+),[ ]*phiras[ ]+([0-9]+),[ ]*thystame[ ]+([0-9]+)}$"),
                                              self.__parseInventory)
        self.tab["fov"] = structFuncPtr(re.compile("^{([, ](joueur|nourriture|linemate|sibur|deraumere|mendiane|phiras|thystame)*)*}$"),
                                        self.__parseFov)
        self.tab["message"] = structFuncPtr(re.compile("^message [0-9]+,"),
                                               self.__parseMessage)
        self.tab["expulse"] = structFuncPtr(re.compile("^deplacement: [0-9]+$"),
                                            self.__parseExpulse)
        self.tab["answer"] = structFuncPtr(re.compile("^(ok|ko)$"),
                                           self.__parseAnswer)
        self.tab["freeSlot"] = structFuncPtr(re.compile("^[0-9]+$"),
                                             self.__parseFreeSlot)


    def parse (self, toParse):
        for elem in self.names:
            tmp = self.tab[elem].regex.search(toParse)
            if tmp is not None:
                return self.tab[elem].funcPtr(toParse)
        print("##########")
        print(toParse)
        print("##########")
        raise SyntaxError("\033[31mBAD COMMAND FROM THE SERVER (\033[33mthere might be a man in the middle\033[31m)\033[0m")

    def __parseMessage (self, toParse):
        res = responseServer.ResponseServerMessage()
        tmp = toParse.split(",")
        res.message.direction = tmp[0][8:]
        res.message.message = tmp[1]
        return res

    def __parseExpulse (self, toParse):
        res = responseServer.ResponseServerExpulse()
        res.expulse.direction = toParse.split(": ")[1]
        return res

    def __parseInventory (self, toParse):
        res = responseServer.ResponseServerInventory()
        tmp = re.findall("[a-z]+ [0-9]+", toParse)
        for elem in tmp:
            voz = elem.split(" ")
            res.inventory.stones[voz[0]] = voz[1]
        return res

    def __parseFov (self, toParse):
        res = responseServer.ResponseServerFov()
        tmp = toParse.split(",")
        i = 0
        for elem in tmp:
            res.fov.cases.append({})
            res.fov.cases[i]["joueur"] = elem.count("joueur")
            res.fov.cases[i]["nourriture"] = elem.count("nourriture")
            res.fov.cases[i]["linemate"] = elem.count("linemate")
            res.fov.cases[i]["deraumere"] = elem.count("deraumere")
            res.fov.cases[i]["sibur"] = elem.count("sibur")
            res.fov.cases[i]["phiras"] = elem.count("phiras")
            res.fov.cases[i]["thystame"] = elem.count("thystame")
            i += 1
        return res

    def __parseAnswer (self, toParse):
        res = responseServer.ResponseServerAnswer()
        if toParse == "ok":
            res.answer.isItOk = True
        return res

    def __parseFreeSlot (self, toParse):
        res = responseServer.ResponseServerFreeSlot()
        res.freeSlot.freeSlot = int(toParse)
        return res
