#ifndef DATE_HPP_
#define DATE_HPP_

class Date
{
public:
    Date();
    Date(int day, int week, int year);

    void setDay( int day );
    void setWeek( int week );
    void setYear( int year );

    int getDay() const;
    int getWeek() const;
    int getYear() const;

    void set(int day, int week, int year);

private:
    int mDay;
    int mWeek;
    int mYear;
};

#endif 