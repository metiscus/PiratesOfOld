#include "Ship.hpp"

Ship::Ship()
{
  ;
}
    
const Ship::HullInfo& Ship::getHullInfo() const
{
    return mHull;
}

void Ship::setHull(HullInfo info)
{
    mHull = info;
}

Ship::Role Ship::getRole() const
{
  return mRole;
}

void Ship::setRole(Role role)
{
  mRole = role;
}