def manageConnectNbr          (self, response, expr):
    return response.isFreeSlot()

def manageFork                (self, response, expr):
    return response.isAnswer()

def manageInventaire          (self, response, expr):
    return response.isInventory()

def manageVoir                (self, response, expr):
    print("ici je sui dans le voir")
    return response.isFov()

def manageAvance              (self, response, expr):
    print("ici je suis dans avance")
    return response.isAnswer()

def manageGauche              (self, response, expr):
    print("ici je suis dans le gauche")
    return response.isAnswer()

def manageDroite              (self, response, expr):
    print("ici je suis dans le droite")
    return response.isAnswer()

def managePrend               (self, response, expr):
    print("ici je suis dans le prend")
    return response.isAnswer()

def managePose                (self, response, expr):
    print("ici je suis dans le pose")
    return response.isAnswer()

def manageIncantation         (self, response, expr):
    if response.isElevation() is True:
        return True
    if response.isLevel() is True:
        return True
    if response.isAnswer() is True:
        return True
    return False

def manageExpulse             (self, response, expr):
    return response.isAnswer()

def manageGetlvl              (self, response, expr):
    return response.isAnswer()

def manageMylvl               (self, response, expr):
    return response.isAnswer()

def manageCome                (self, response, expr):
    return response.isAnswer()

def manageOnMyWay             (self, response, expr):
    return response.isAnswer()
