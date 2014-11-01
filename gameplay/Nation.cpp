#include "Nation.hpp"

Nation::Nation(NationId id)
  : mNation(id)
{
  for(int ii=First; ii<=Last; ++ii)
  {
    mRelations.insert(std::make_pair((NationId)ii, 0));
  }
}

Nation::NationId Nation::getId() const
{
  return mNation;
}

void Nation::setRelations (NationId nation, int relation)
{
  mRelations[nation] = relation;
}

int  Nation::getRelations (NationId nation) const
{
  int ret = 0;
  std::map<NationId, int>::const_iterator itr = mRelations.find(nation);
  if(itr != mRelations.end())
  {
    ret = itr->second;
  }
  
  return ret;
}

void Nation::modifyRelations (NationId nation, int change)
{
  mRelations[nation] += change;
}