#ifndef		__ITEMOBJECT_HH__
#define		__ITEMOBJECT_HH__

#include <vector>
#include "GameObject.hh"

class ItemObject : public GameObject
{
public:
  ItemObject(const sf::Vector2f &pos, int id);
  virtual ~ItemObject() {}

  virtual void	update(float dt, size_t frameCount) {}
  virtual bool	collides(GameObject &obj);

  static void	initAsset();

private:
  static AssetDescriptor	s_assetDesc[4];
  int	_id;
};

#endif	//	__ITEMOBJECT_HH__
