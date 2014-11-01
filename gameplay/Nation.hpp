#ifndef NATION_HPP_
#define NATION_HPP_

#include <string>
#include <map>

class Nation
{
public:
  enum NationId
  {
    Invalid = 0,
    First,
    France = First,
    England,
    Spain,
    Holland,
    Last = Holland,
    Count,
  };
  
  Nation(NationId id = Invalid);
  
  NationId getId() const;
  
  void setRelations (NationId nation, int relation);
  int  getRelations (NationId nation) const;
  void modifyRelations (NationId nation, int change);
  
private:
  NationId mNation;
  std::map<NationId, int> mRelations;
};


#endif // NATIONS_HPP_