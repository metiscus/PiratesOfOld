#ifndef VIEW_HPP_
#define VIEW_HPP_

class View
{
public:
  View() = default
  virtual ~View() = default;
    
private:
  View(const View&) = delete;
  const View& operator=(const View&) = delete;
};

#endif