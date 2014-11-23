#include "Model.hpp"

void Model::SetView(std::shared_ptr<View> view)
{
  mView = view;
}

std::shared_ptr<View> Model::GetModel()
{
  return mView;
}