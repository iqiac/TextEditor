#pragma once

#include "CommonTypes.hpp"

class IInputHandler {
public:
  virtual ~IInputHandler() = default;

  virtual void Start() = 0;
  virtual void Stop()  = 0;

private:
  virtual void HandleInput() = 0;
};
