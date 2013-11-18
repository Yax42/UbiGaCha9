#include "QuadTree.hh"

const size_t	QuadTree::_maxEntities = 4;
const size_t	QuadTree::_maxDepth = 8;

QuadTree::QuadTree(const Box &bounds, size_t depth)
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

void QuadTree::insert(AGameObject *entity)
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
      AGameObjectVector::iterator it = _entities.begin();
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

bool QuadTree::retrieve(AGameObjectVector &returnEntities,
			AGameObject *entity) const
{
  ssize_t	i = getIndex(entity);

  if (i != -1)
    _node[i]->retrieve(returnEntities, entity);
  for (AGameObjectVector::const_iterator it = _entities.begin();
       it != _entities.end(); ++it)
    if (*it != entity)
      returnEntities.push_back(*it);
  return (!returnEntities.empty());
}

void QuadTree::split()
{
  sf::Vector2f		subDim(_bounds.getHalfDimension().x / 2,
			       _bounds.getHalfDimension().y / 2);
  float		x = _bounds.getCenter().x;
  float         y = _bounds.getCenter().y;
  size_t	depth = _depth + 1;

  _node[0] = new QuadTree(Box(sf::Vector2f(x - subDim.x, y + subDim.y), subDim), depth);
  _node[1] = new QuadTree(Box(sf::Vector2f(x + subDim.x, y + subDim.y), subDim), depth);
  _node[2] = new QuadTree(Box(sf::Vector2f(x - subDim.x, y - subDim.y), subDim), depth);
  _node[3] = new QuadTree(Box(sf::Vector2f(x + subDim.x, y - subDim.y), subDim), depth);
}

ssize_t QuadTree::getIndex(AGameObject *entity) const
{
  if (_node[0] == NULL)
    return (-1);
  for (size_t i = 0; i < 4; ++i)
    if (_node[i]->_bounds.contains(entity->getBox()))
      return (i);
  return (-1);
}
