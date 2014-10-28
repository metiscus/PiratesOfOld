#include "Pirate.hpp"

Pirate::Pirate()
{
    mFamilyName;
    mAge = 21;
    mReputation = 1;
    mWealth = 0;
    mCountry = Country_Holland;
  
    for(int ii=0; ii<Country_Count; ++ii)
        mStandings[ii] = 0;
}

void Pirate::setFamilyName(std::string name)
{
    mFamilyName = name;
}

std::string Pirate::getFamilyName() const
{
    return mFamilyName;
}

void Pirate::setAge(int age)
{
    mAge = age;
}

int Pirate::getAge() const
{
    return mAge;
}

int Pirate::getReputation() const
{
    return mReputation;
}

void Pirate::setReputation(int reputation)
{
    mReputation = reputation;
}

int Pirate::getWealth() const
{
    return mWealth;
}

void Pirate::setWealth(int wealth)
{
    mWealth = wealth;
}

void Pirate::setCountry(Country cntry)
{
    mCountry = cntry;
}

Country Pirate::getCountry() const
{
    return mCountry;
}

int Pirate::getStandings(Country cntry) const
{
    return mStandings[cntry];
}

void Pirate::setStandings(Country cntry, int standing)
{
    mStandings[cntry] = standing;
}