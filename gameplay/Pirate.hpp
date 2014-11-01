#ifndef PIRATE_HPP_
#define PIRATE_HPP_

#include <string>

#include "Nation.hpp"

class Pirate
{
public:
  Pirate();
  void setFamilyName(std::string name);
  std::string getFamilyName() const;
  
  void setAge(int age);
  int getAge() const;
  
  int getReputation() const;
  void setReputation(int reputation);
  
  int getWealth() const;
  void setWealth(int wealth);
  
  void setCountry(Nation::NationId cntry);
  Nation::NationId getCountry() const;
  
  int getStandings(Nation::NationId cntry) const;
  void setStandings(Nation::NationId cntry, int standing);
  
private:
  std::string mFamilyName;
  int mAge;
  int mReputation;
  int mWealth;
  Nation::NationId mCountry;
  int mStandings[Nation::Count];
};

#endif // PIRATE_HPP_