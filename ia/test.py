import zappyParser

p = zappyParser.ZappyParser()

# response = p.parse("{nourriture 10,linemate 0,sibur 0,deraumere 0,mendiane 0,phiras 0,thystame 0}")

# response = p.parse("message 8,réussi")

response = p.parse("{ joueur nourriture nourriture, linemate, nourriture,}")

if response.isFov() is True:
    fov = response.getFov()
    print("OK")

elif response.isInventory() is True:
    inventory = response.getInventory()
    print("INVENTORY")

elif response.isExpulse() is True:
    expulse = response.getExpulse()

elif response.isAnswer() is True:
    answer = response.getAnswer()

elif response.isMessage() is True:
    message = response.getMessage()

elif response.isFreeSlot() is True:
    freeSlot = response.getFreeSlot()

# tmp = fov.getClosestFood()
# while not tmp.empty():
#     print(tmp.get())
