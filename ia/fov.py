import queue

class Fov:

    def __init__ (self):
        self.cases = []
        self.use = False

    # savoir si les donnees de voir on deja ete exploitee
    def getUsed (self):
        return self.use

    def setUsed (self, use):
        self.use = use

    def getFoodOnCase (self, case):
        try:
            return self.cases[case]["nourriture"]
        except IndexError:
            print("\033[31mError in getFoodOnCase : "
                  + "\033[33mbad index [" + str(case) + "]\033[0m")
        return 0

    def getPlayerOnCase (self, case):
        try:
            return self.cases[case]["joueur"]
        except:
            print("\033[31mError in getPlayerOnCase : "
                  + "\033[33mbad index [" + str(case) + "]\033[0m")
        return 0

    def getStoneOnCase (self, case, stoneName):
        try:
            return self.cases[int(case)][stoneName]
        except IndexError:
            print("\033[31mError in getStoneOnCase : "
                  + "\033[33mbad index [" + str(case) + "]\033[0m")
        except KeyError:
            print("\033[31mError in getStoneOnCase : "
                  + "\033[33munknown key [" + stoneName + "]\033[0m")
        return 0

    def getClosestFood (self, actualLevel):
        temp = queue.Queue()
        for elem in distance:
            for sub in elem:
                if sub < len(self.cases):
                    if self.cases[sub]["nourriture"] > 0:
                        if sub == 0:
                            temp.put("prend nourriture")
                            return temp
                        else:
                            print("j'ai trouve un chemin")
                            temp = self.getPath(sub, actualLevel)
                            return temp
        return temp

    def getClosestStone (self, stoneName, actualLevel):
        temp = queue.Queue()
        for elem in distance:
            for sub in elem:
                if sub < len(self.cases):
                    try:
                        if self.cases[sub][stoneName] > 0:
                            if sub == 0:
                                temp.put("prend " + stoneName)
                                return temp
                            else:
                                return self.getPath(sub, actualLevel)
                    except KeyError:
                        print("\033[31mError in getClosestStone : "            
                              + "\033[33munknown key [" + stoneName + "]\033[0m")
                        return temp
        return temp


    def getPath (self, caseIndex, actualLevel):
        maxPerLevel = (0, 2, 6, 12, 20, 30, 42, 56, 72)
        res = queue.Queue()
        for i in range(actualLevel):
            res.put("avance")
        if  caseIndex < maxPerLevel[actualLevel]:
            res.put("gauche")
        elif caseIndex > maxPerLevel[actualLevel]:
            res.put("droite")
        for i in range(abs(maxPerLevel[actualLevel] - caseIndex)):
            res.put("avance")
        return res

distance = list()
distance.append([0])
distance.append([2])
distance.append([6])
distance.append([1, 3, 12])
distance.append([5, 7, 20])
distance.append([4, 8, 11, 13, 30])
distance.append([10, 14, 19, 21, 42])
distance.append([9, 15, 18, 22, 29, 31, 56])
distance.append([17, 23, 28, 32, 41, 43, 72])
distance.append([16, 24, 27, 33, 40, 44, 55, 57])
distance.append([26, 34, 39, 45, 54, 58, 71, 73])
distance.append([25, 35, 38, 46, 53, 59, 70, 74])
distance.append([37, 47, 52, 60, 69, 75])
distance.append([36, 48, 51, 61, 68, 76])
distance.append([50, 62, 67, 77])
distance.append([49, 63, 66, 78])
distance.append([65, 79])
distance.append([64, 80])
