#include		"objects/ModelManager.hh"

namespace	Zappy
{
  ModelManager*	ModelManager::_instance = NULL;

  ModelManager::ModelManager()
  {
    _models[LINEMATE] = new gdl::Model();
    if (!_models[LINEMATE]->load("./assets/linemate.obj"))
      throw (std::runtime_error("Unable to load linemate.obj"));
    _models[DERAUMERE] = new gdl::Model();
    if (!_models[DERAUMERE]->load("./assets/deraumere.obj"))
      throw (std::runtime_error("Unable to load deraumere.obj"));
    _models[SIBUR] = new gdl::Model();
    if (!_models[SIBUR]->load("./assets/sibur.obj"))
      throw (std::runtime_error("Unable to load sibur.obj"));
    _models[MENDIANE] = new gdl::Model();
    if (!_models[MENDIANE]->load("./assets/mendiane.obj"))
      throw (std::runtime_error("Unable to load mendiane.obj"));
    _models[PHIRAS] = new gdl::Model();
    if (!_models[PHIRAS]->load("./assets/phiras.obj"))
      throw (std::runtime_error("Unable to load phiras.obj"));
    _models[THYSTAME] = new gdl::Model();
    if (!_models[THYSTAME]->load("./assets/thystame.obj"))
      throw (std::runtime_error("Unable to load thystame.obj"));
    _food = new gdl::Model();
    if (!_food->load("./assets/models/food/heart.obj"))
      throw (std::runtime_error("Unable to load heart.obj"));
    _world = new gdl::Model();
    if (!_world->load("./assets/models/world/kokiri_forest/world.fbx"))
      throw (std::runtime_error("Unable to load world.obj"));
  }

  gdl::Model*	ModelManager::getFood()
  {
    return (_food);
  }

  gdl::Model*	ModelManager::getWorld()
  {
    return (_world);
  }

  gdl::Model*	ModelManager::getStone(Type type)
  {
    return (_models[type]);
  }

  ModelManager*	ModelManager::getInstance()
  {
    if (!_instance)
      _instance = new ModelManager();
    return (_instance);
  }

  ModelManager::~ModelManager()
  {
  }
}
