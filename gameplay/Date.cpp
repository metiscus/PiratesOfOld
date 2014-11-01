#include "Date.hpp"

Date::Date()
  : mDay(1)
  , mWeek(1)
  , mYear(1600)
{
  
}

Date::Date(int day, int week, int year)
{
  mDay  = day;
  mWeek = week;
  mYear = year;
}

void Date::setDay( int day )
{
  mDay = day;
}

void Date::setWeek( int week )
{
  mWeek = week;
}

void Date::setYear( int year )
{
  mYear = year;
}

int Date::getDay() const
{
  return mDay;
}

int Date::getWeek() const
{
  return mWeek;
}

int Date::getYear() const
{
  return mYear;
}

void Date::set(int day, int week, int year)
{
  mDay  = day;
  mWeek = week;
  mYear = year;
}