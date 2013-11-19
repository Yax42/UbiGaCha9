#include "QuadTree.hh"

const size_t	QuadTree::_maxEntities = 4;
const size_t	QuadTree::_maxDepth = 8;

QuadTree::QuadTree(const sf::FloatRect &bounds, size_t depth)
  : _bounds(bounds),
    _depth(depth)
{
  _node[0] = NULL;
  _node[1] = NULL;
  _node[2] = NULL;
  _node[3] = NULL;
}

QuadTree::~QuadTree()
{
  clear();
}

void QuadTree::insert(GameObject *entity)
{
  if (_node[0] != NULL)
    {
      ssize_t i = getIndex(entity);
      if (i != -1)
	{
	  _node[i]->insert(entity);
	  return;
	}
    }
  _entities.push_back(entity);
  if (_entities.size() > _maxEntities && _depth < _maxDepth)
    {
      if (_node[0] == NULL)
	split();
      GameObjectVector::iterator it = _entities.begin();
      while (it != _entities.end())
	{
	  ssize_t i = getIndex(*it);
	  if (i != -1)
	    {
	      _node[i]->insert(*it);
	      it = _entities.erase(it);
	    }
	  else
	    ++it;
	}
    }
}

void QuadTree::clear()
{
  _entities.clear();
  for (size_t i = 0; i < 4; ++i)
    if (_node[i] != NULL)
      {
	delete _node[i];
	_node[i] = NULL;
      }
}

bool QuadTree::retrieve(GameObjectVector &returnEntities,
			GameObject *entity) const
{
  ssize_t	i = getIndex(entity);

  if (i != -1)
    _node[i]->retrieve(returnEntities, entity);
  for (GameObjectVector::const_iterator it = _entities.begin();
       it != _entities.end(); ++it)
    if (*it != entity)
      returnEntities.push_back(*it);
  return (!returnEntities.empty());
}

void QuadTree::split()
{
  sf::Vector2f		subDim(_bounds.width / 2.f,
			       _bounds.height / 2.f);
  size_t		depth = _depth + 1;

  _node[0] = new QuadTree(sf::FloatRect(sf::Vector2f(_bounds.left, _bounds.top), subDim), depth);
  _node[1] = new QuadTree(sf::FloatRect(sf::Vector2f(_bounds.left + subDim.x, _bounds.top), subDim), depth);
  _node[2] = new QuadTree(sf::FloatRect(sf::Vector2f(_bounds.left, _bounds.top - subDim.y), subDim), depth);
  _node[3] = new QuadTree(sf::FloatRect(sf::Vector2f(_bounds.left + subDim.x, _bounds.top - subDim.y), subDim), depth);
}

ssize_t QuadTree::getIndex(GameObject *entity) const
{
  if (_node[0] == NULL)
    return (-1);
  for (size_t i = 0; i < 4; ++i)
    {
      sf::FloatRect	res;
      if (_node[i]->_bounds.intersects(entity->getBox(), res) && entity->getBox() == res)
	return (i);
    }
  return (-1);
}
