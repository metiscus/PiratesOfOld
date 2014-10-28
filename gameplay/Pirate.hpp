#ifndef PIRATE_HPP_
#define PIRATE_HPP_

#include <string>

#include "Nations.hpp"

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
  
  void setCountry(Country cntry);
  Country getCountry() const;
  
  int getStandings(Country cntry) const;
  void setStandings(Country cntry, int standing);
  
private:
  std::string mFamilyName;
  int mAge;
  int mReputation;
  int mWealth;
  Country mCountry;
  int mStandings[Country_Count];
};

#endif // PIRATE_HPP_