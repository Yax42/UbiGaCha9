#ifndef		__QUADTREE_HH__
#define		__QUADTREE_HH__

#ifdef _MSC_VER
#include <basetsd.h>
typedef SSIZE_T ssize_t;
#endif

#include <cstdlib>
#include <vector>
#include "Box.hh"
#include "GameObject.hh"

class QuadTree
{
public:
  QuadTree(const Box &bounds, size_t depth = 0);
  ~QuadTree();
  void			insert(AGameObject *entity);
  void			clear();
  bool			retrieve(AGameObjectVector &returnEntities,
				 AGameObject *entity) const;
private:
  void			split();
  ssize_t		getIndex(AGameObject *entity) const;

  static const size_t	_maxEntities;
  static const size_t	_maxDepth;

  AGameObjectVector	_entities;
  QuadTree		*_node[4];
  Box			_bounds;
  size_t		_depth;
};

#endif	//	__QUADTREE_HH__
