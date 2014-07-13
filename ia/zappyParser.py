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
        self.names = ["inventory", "fov", "message", "expulse", "answer", "freeSlot", "elevation", "level", "alive"]

        # liste de structures liant les regex et leur fonction de parsing
        self.tab = {
            "inventory" : structFuncPtr(re.compile("^{([ ]*(nourriture|linemate|sibur|deraumere|mendiane|phiras|thystame)[ ]+[0-9]+[,]*){7}}$"),
                                        self.__parseInventory),
            "fov" : structFuncPtr(re.compile("^{([,]?([ ](joueur|nourriture|linemate|sibur|deraumere|mendiane|phiras|thystame))?)*}"),
                                  self.__parseFov),
            "message" : structFuncPtr(re.compile("^message [0-9]+,"),
                                  self.__parseMessage),
            "expulse" : structFuncPtr(re.compile("^deplacement: [0-9]+$"),
                                      self.__parseExpulse),
            "answer" : structFuncPtr(re.compile("^(ok|ko)$"),
                                     self.__parseAnswer),
            "freeSlot" : structFuncPtr(re.compile("^[0-9]+$"),
                                       self.__parseFreeSlot),
            "elevation" : structFuncPtr(re.compile("elevation en cours"),
                                        self.__parseElevation),
            "level" : structFuncPtr(re.compile("niveau actuel : ([0-9]+)"),
                                    self.__parseLevel),
            "alive" : structFuncPtr(re.compile("mort"),
                                    self.__parseAlive)
        }
    def parse (self, toParse):
        for cmd in toParse.split("\n"):
            for elem in self.names:
                tmp = self.tab[elem].regex.search(cmd)
                if tmp is not None:
                    return self.tab[elem].funcPtr(cmd)
            print("##########")
            print(cmd)
            print("##########")
            raise SyntaxError("\033[31mBAD COMMAND FROM THE SERVER (\033[33mthere might be a man in the middle\033[31m)\033[0m")

    def __parseMessage (self, toParse):
        res = responseServer.ResponseServerMessage()
        tmp = toParse.split(",")
        res.message.direction = int(tmp[0][8:])
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
            if voz[0] == "nourriture":
                res.inventory.nourriture = int(voz[1])
            res.inventory.stones[voz[0]] = int(voz[1])
        return res

    def __parseFov (self, toParse):
        res = responseServer.ResponseServerFov()
        tmp = toParse.split(",")
        res.fov.nbrOfComma = toParse.count(",")
        i = 0
        for elem in tmp:
            res.fov.cases.append({})
            res.fov.cases[i]["joueur"] = elem.count("joueur")
            res.fov.cases[i]["nourriture"] = elem.count("nourriture")
            res.fov.cases[i]["linemate"] = elem.count("linemate")
            res.fov.cases[i]["deraumere"] = elem.count("deraumere")
            res.fov.cases[i]["sibur"] = elem.count("sibur")
            res.fov.cases[i]["mendiane"] = elem.count("mendiane")
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

    def __parseElevation (self, toParse):
        res = responseServer.ResponseServerElevation()
        res.isInElevation = True
        return res

    def __parseLevel (self, toParse):
        res = responseServer.ResponseServerLevel()
        res.level.actualLevel = int(self.tab["level"].regex.search(toParse).group(1))
        return res

    def __parseAlive (self, toParse):
        res = responseServer.ResponseServerAlive()
        return res
