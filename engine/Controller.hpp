#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <memory>

class Model;

class Controller
{
public:
  Controller() = default;
  virtual ~Controller() = default;
  
  void SetModel(std::shared_ptr<Model> model);
  std::shared_ptr<Model> GetModel();
  
private:
  Controller(const Controller&) = delete;
  const Controller& operator=(const Controller&) = delete;
  
  std::shared_ptr<Model> mModel;
};

#endif