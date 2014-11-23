#ifndef MODEL_HPP_
#define MODEL_HPP_

#include <memory>

class View;

class Model
{
public:
  Model() = default;
  virtual ~Model() = default;
  
  void SetView(std::shared_ptr<View> view);
  std::shared_ptr<View> GetModel();
  
private:
  Model(const Model&) = delete;
  const Model& operator=(const Model&) = delete;
  
  std::shared_ptr<View> mView;
};

#endif