#include <algorithm>
#include "ioManager.h"
#include "collisionStrategy.h"
using std::cout; using std::endl;

void RectangularCollisionStrategy::draw() const {
 // IOManager::getInstance().printMessageAt("Rectangular Collision Strategy", 320, 10);
}

bool RectangularCollisionStrategy::execute(
  const Sprite& obj1, const Sprite& obj2) const {
  float left1 = obj1.X();
  float left2 = obj2.X();
  float right1 = left1+obj1.getFrame()->getWidth();
  float right2 = left2+obj2.getFrame()->getWidth();
  float top1 = obj1.Y()-obj1.getFrame()->getHeight();
  float top2 = obj2.Y()-obj2.getFrame()->getHeight();
  float bottom1 = top1+obj1.getFrame()->getHeight();
  float bottom2 = top2+obj2.getFrame()->getHeight();
  if ( right1 < left2 ) return false;
  if ( left1 > right2 ) return false;
  if ( bottom1 < top2 ) return false;
  if ( bottom2 < top1 ) return false;
  return true;
}


float MidPointCollisionStrategy::
distance(float x1, float y1, float x2, float y2) const {
  float x = x1-x2, y = y1-y2;
  return hypot(x, y);
}

void MidPointCollisionStrategy::draw() const {
  //IOManager::getInstance().printMessageAt("Distance from Middle Strategy", 320, 10);
}

bool MidPointCollisionStrategy::execute(
      const Sprite& obj1, const Sprite& obj2) const {
  int COLLISION_DISTANCE = 
    obj1.getFrame()->getWidth()/2 + obj2.getFrame()->getWidth()/2;
  float xobj1 = obj1.X()+obj1.getFrame()->getWidth()/2;
  float yobj1 = obj1.Y()+obj1.getFrame()->getHeight()/2;
  float xobj2 = obj2.X() + obj2.getFrame()->getWidth()/2;
  float yobj2 = obj2.Y() + obj2.getFrame()->getHeight()/2;
  return distance(xobj1, yobj1, xobj2, yobj2) < COLLISION_DISTANCE;
}

void PerPixelCollisionStrategy::draw() const {
  //IOManager::getInstance().printMessageAt("Per-Pixel Collision Strategy", 320, 10);
}

bool PerPixelCollisionStrategy::execute(
      const Sprite& obj1, const Sprite& obj2) const {

  RectangularCollisionStrategy strategy;
  if ( not strategy.execute(obj1, obj2) ) return false;
  // If we got this far, we know that the sprite rectangles intersect!

  Vector2f p1 = obj1.getPosition();
  Vector2f p2 = obj2.getPosition();
  const Frame * const frame1 = obj1.getFrame();
  const Frame * const frame2 = obj2.getFrame();

  int o1Left = p1[0]; 
  int o1Right = o1Left+frame1->getWidth();

  int o2Left = p2[0]; 
  int o2Right = o2Left+frame2->getWidth();
  std::vector<int> x;
  x.reserve(4);
  x.push_back( o1Left );
  x.push_back( o1Right );
  x.push_back( o2Left );
  x.push_back( o2Right );
  std::sort( x.begin(), x.end() );

  int o1Up = p1[1];
  int o1Down = o1Up+frame1->getHeight();
  int o2Up = p2[1];
  int o2Down = o2Up+frame2->getHeight();
  std::vector<int> y;
  y.reserve(4);
  y.push_back( o1Up );
  y.push_back( o1Down );
  y.push_back( o2Up );
  y.push_back( o2Down );
  std::sort( y.begin(), y.end() );
  SDL_Surface* surface1 = frame1->getSurface();
  SDL_Surface* surface2 = frame2->getSurface();

  SDL_LockSurface(surface1);
  SDL_LockSurface(surface2);
  unsigned pixels1;
  unsigned pixels2;
  for (int i = x[1]; i < x[2]; ++i) {
    for (int j = y[1]; j < y[2]; ++j) {
      // check pixels in obj1 and obj2!
      pixels1 = obj1.getPixel(i, j);
      pixels2 = obj2.getPixel(i, j);
      if ( pixels1 != 0xff00ff && pixels2 != 0xff00ff) {
        SDL_UnlockSurface(surface1);
        SDL_UnlockSurface(surface2);
        return true;
      }
    }
  }
  SDL_UnlockSurface(surface1);
  SDL_UnlockSurface(surface2);

  return false;
}

