def __manageInventaire          (self, response, expr):
    return response.isInventory()

def __manageVoir                (self, response, expr):
    return response.isAnswer()

def __manageAvance              (self, response, expr):
    return response.isAnswer()

def __manageGauche              (self, response, expr):
    return response.isAnswer()

def __manageDroite              (self, response, expr):
    return response.isAnswer()

def __managePrend               (self, response, expr):
    return response.isAnswer()

def __managePose                (self, response, expr):
    return response.isAnswer()

def __manageIncantation         (self, response, expr):
    if response.isElevation() is True:
        return True
    if response.isLevel() is True:
        return True
    if response.isAnswer() is True:
        return True
    return False

def __manageExpulse             (self, response, expr):
    return response.isAnswer()

def __manageGetlvl              (self, response, expr):
    return False

def __manageMylvl               (self, response, expr):
    return False

def __manageCome                (self, response, expr):
    return False

def __manageOnMyWay             (self, response, expr):
    return False
