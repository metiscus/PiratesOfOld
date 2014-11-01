#include "Territory.hpp"

Territory::Territory()
{
  
}

int Territory::getId() const
{
  return mId;
}

void Territory::setId(int id)
{
  mId = id;
}

Territory::Type Territory::getType() const
{
  return mType;
}

void Territory::setType(Type type)
{
  mType = type;
}

void Territory::setName(std::string name)
{
  mName = name;
}

std::string Territory::getName() const
{
  return mName;
}

void Territory::setOwningPower(Nation::NationId owner)
{
  mOwningPower = owner;
}

Nation::NationId Territory::getOwningPower() const
{
  return mOwningPower;
}

int Territory::getGarrison() const
{
  return mGarrison;
}

void Territory::setGarrison(int garrison)
{
  mGarrison = garrison;
}

bool Territory::getHasShipyard() const
{
  return mHasShipyard;
}

bool Territory::getHasFort() const
{
  return mHasFort;
}

bool Territory::getHasGovernor() const
{
  return mHasGovernor;
}

void Territory::setHasShipyard(bool hasShip)
{
  mHasShipyard = hasShip;
}

void Territory::setHasFort(bool hasFort)
{
  mHasFort = hasFort;
}

void Territory::setHasGovernor(bool hasGov)
{
  mHasGovernor = hasGov;
}