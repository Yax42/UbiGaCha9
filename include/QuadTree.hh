#ifndef		__QUADTREE_HH__
#define		__QUADTREE_HH__

#ifdef _MSC_VER
#include <basetsd.h>
typedef SSIZE_T ssize_t;
#endif

#include <cstdlib>
#include <vector>
#include "GameObject.hh"

class QuadTree
{
public:
  QuadTree(const sf::FloatRect &bounds = sf::FloatRect(), size_t depth = 0);
  ~QuadTree();
  void			setBounds(const sf::FloatRect &bounds) {_bounds = bounds;}
  void			insert(GameObject *entity);
  void			clear();
  bool			retrieve(GameObjectVector &returnEntities,
				 GameObject *entity) const;
private:
  void			split();
  ssize_t		getIndex(GameObject *entity) const;

  static const size_t	_maxEntities;
  static const size_t	_maxDepth;

  GameObjectVector	_entities;
  QuadTree		*_node[4];
  sf::FloatRect		_bounds;
  size_t		_depth;
};

#endif	//	__QUADTREE_HH__
