#ifndef NATIONS_HPP_
#define NATIONS_HPP_

#include <string>

enum Country
{
  Country_Holland,
  Country_Spain,
  Country_England,
  Country_France,
  Country_Count,
};

enum Era
{
  Era_GoldenAge = 1650,
  Era_Sunset    = 1730
};

enum Relations
{
    Relation_War     = -100,
    Relation_Neutral = 0,
    Relation_Allies  = 100,
};

class Nations
{
public:
    Nations();
    void loadData(std::string filename);
    void writeData(std::string filename) const;
    
private:
    std::string mNames[Country_Count];
    int mRelations[Country_Count][Country_Count];
};


#endif // NATIONS_HPP_