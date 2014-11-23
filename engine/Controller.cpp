#include "Controller.hpp"

void Controller::SetModel(std::shared_ptr<Model> model)
{
  mModel = model;
}

std::shared_ptr<Model> Controller::GetModel()
{
  return mModel;
}