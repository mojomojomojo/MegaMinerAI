# -*- python -*-

from library import library

from ExistentialError import ExistentialError

class GameObject(object):
  def __init__(self, ptr):
    from BaseAI import BaseAI
    self.ptr = ptr
    self.iteration = BaseAI.iteration


##The base object for all mappable things
class Mappable(GameObject):
  def __init__(self, ptr):
    from BaseAI import BaseAI
    self.ptr = ptr
    self.iteration = BaseAI.iteration
    
    self.id = library.mappableGetId(ptr)

  ##Unique Identifier
  def getId(self):
    self.validify()
    return library.mappableGetId(self.ptr)

  ##The x coordinate
  def getX(self):
    self.validify()
    return library.mappableGetX(self.ptr)

  ##The y cooridnate
  def getY(self):
    self.validify()
    return library.mappableGetY(self.ptr)


  def __str__(self):
    self.validify()
    ret = ""
    ret += "id: %s\n" % self.getId()
    ret += "x: %s\n" % self.getX()
    ret += "y: %s\n" % self.getY()
    return ret

##The information on the base
class Base(Mappable):
  def __init__(self, ptr):
    from BaseAI import BaseAI
    self.ptr = ptr
    self.iteration = BaseAI.iteration
    
    self.id = library.baseGetId(ptr)

  def validify(self):
    from BaseAI import BaseAI
    #if this class is pointing to an object from before the current turn it's probably
    #somewhere else in memory now
    if self.iteration == BaseAI.iteration:
      return True
    for i in BaseAI.bases:
      if i.id == self.id:
        self.ptr = i.ptr
        self.iteration = BaseAI.iteration
        return True
    raise ExistentialError()
  ##Creates a Virus on the base with certain level.
  def spawn(self, Level):
    self.validify()
    return library.baseSpawn(self.ptr, Level)

  ##Unique Identifier
  def getId(self):
    self.validify()
    return library.baseGetId(self.ptr)

  ##The x coordinate
  def getX(self):
    self.validify()
    return library.baseGetX(self.ptr)

  ##The y cooridnate
  def getY(self):
    self.validify()
    return library.baseGetY(self.ptr)

  ##Whose base this is, all your base are belong to who
  def getOwner(self):
    self.validify()
    return library.baseGetOwner(self.ptr)

  ##The number of viruses this base can still spawn this turn
  def getSpawnsLeft(self):
    self.validify()
    return library.baseGetSpawnsLeft(self.ptr)


  def __str__(self):
    self.validify()
    ret = ""
    ret += "id: %s\n" % self.getId()
    ret += "x: %s\n" % self.getX()
    ret += "y: %s\n" % self.getY()
    ret += "owner: %s\n" % self.getOwner()
    ret += "spawnsLeft: %s\n" % self.getSpawnsLeft()
    return ret

##Stores information about a player in the game
class Player(GameObject):
  def __init__(self, ptr):
    from BaseAI import BaseAI
    self.ptr = ptr
    self.iteration = BaseAI.iteration
    
    self.id = library.playerGetId(ptr)

  def validify(self):
    from BaseAI import BaseAI
    #if this class is pointing to an object from before the current turn it's probably
    #somewhere else in memory now
    if self.iteration == BaseAI.iteration:
      return True
    for i in BaseAI.players:
      if i.id == self.id:
        self.ptr = i.ptr
        self.iteration = BaseAI.iteration
        return True
    raise ExistentialError()
  ##Allows a player to display a message to the screen.
  def talk(self, message):
    self.validify()
    return library.playerTalk(self.ptr, message)

  ##Unique Identifier
  def getId(self):
    self.validify()
    return library.playerGetId(self.ptr)

  ##Player's Name
  def getPlayerName(self):
    self.validify()
    return library.playerGetPlayerName(self.ptr)

  ##Player's points, one with more at end of game wins
  def getByteDollars(self):
    self.validify()
    return library.playerGetByteDollars(self.ptr)

  ##Player's machine cycles, used to create new Virus's
  def getCycles(self):
    self.validify()
    return library.playerGetCycles(self.ptr)

  ##The amount of time this player has before timing out
  def getTime(self):
    self.validify()
    return library.playerGetTime(self.ptr)


  def __str__(self):
    self.validify()
    ret = ""
    ret += "id: %s\n" % self.getId()
    ret += "playerName: %s\n" % self.getPlayerName()
    ret += "byteDollars: %s\n" % self.getByteDollars()
    ret += "cycles: %s\n" % self.getCycles()
    ret += "time: %s\n" % self.getTime()
    return ret

##Represents a single space on the map, can be owned by either player, neither player, or be a wall
class Tile(Mappable):
  def __init__(self, ptr):
    from BaseAI import BaseAI
    self.ptr = ptr
    self.iteration = BaseAI.iteration
    
    self.id = library.tileGetId(ptr)

  def validify(self):
    from BaseAI import BaseAI
    #if this class is pointing to an object from before the current turn it's probably
    #somewhere else in memory now
    if self.iteration == BaseAI.iteration:
      return True
    for i in BaseAI.tiles:
      if i.id == self.id:
        self.ptr = i.ptr
        self.iteration = BaseAI.iteration
        return True
    raise ExistentialError()
  ##Unique Identifier
  def getId(self):
    self.validify()
    return library.tileGetId(self.ptr)

  ##The x coordinate
  def getX(self):
    self.validify()
    return library.tileGetX(self.ptr)

  ##The y cooridnate
  def getY(self):
    self.validify()
    return library.tileGetY(self.ptr)

  ##who owns this tile: 0-First Player, 1-Second Player, 2-Not Owned, 3-Blocked
  def getOwner(self):
    self.validify()
    return library.tileGetOwner(self.ptr)


  def __str__(self):
    self.validify()
    ret = ""
    ret += "id: %s\n" % self.getId()
    ret += "x: %s\n" % self.getX()
    ret += "y: %s\n" % self.getY()
    ret += "owner: %s\n" % self.getOwner()
    return ret

##Stores the information about a virus
class Virus(Mappable):
  def __init__(self, ptr):
    from BaseAI import BaseAI
    self.ptr = ptr
    self.iteration = BaseAI.iteration
    
    self.id = library.virusGetId(ptr)

  def validify(self):
    from BaseAI import BaseAI
    #if this class is pointing to an object from before the current turn it's probably
    #somewhere else in memory now
    if self.iteration == BaseAI.iteration:
      return True
    for i in BaseAI.viruses:
      if i.id == self.id:
        self.ptr = i.ptr
        self.iteration = BaseAI.iteration
        return True
    raise ExistentialError()
  ##Moves a unit to the given (x,y) position
  def move(self, x, y):
    self.validify()
    return library.virusMove(self.ptr, x, y)

  ##Unique Identifier
  def getId(self):
    self.validify()
    return library.virusGetId(self.ptr)

  ##The x coordinate
  def getX(self):
    self.validify()
    return library.virusGetX(self.ptr)

  ##The y cooridnate
  def getY(self):
    self.validify()
    return library.virusGetY(self.ptr)

  ##The owner of this Virus
  def getOwner(self):
    self.validify()
    return library.virusGetOwner(self.ptr)

  ##The Virus's level
  def getLevel(self):
    self.validify()
    return library.virusGetLevel(self.ptr)

  ##The number of times this virus can still move this turn
  def getMovesLeft(self):
    self.validify()
    return library.virusGetMovesLeft(self.ptr)

  ##This virus is alive if the function returns a 1
  def getLiving(self):
    self.validify()
    return library.virusGetLiving(self.ptr)


  def __str__(self):
    self.validify()
    ret = ""
    ret += "id: %s\n" % self.getId()
    ret += "x: %s\n" % self.getX()
    ret += "y: %s\n" % self.getY()
    ret += "owner: %s\n" % self.getOwner()
    ret += "level: %s\n" % self.getLevel()
    ret += "movesLeft: %s\n" % self.getMovesLeft()
    ret += "living: %s\n" % self.getLiving()
    return ret
