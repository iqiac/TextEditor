#pragma once

#include "IObserver.hpp"
#include "IScreen.hpp"
#include "IScreenRenderer.hpp"
#include "ISubject.hpp"

class ScreenRenderer : public IScreenRenderer, public IObserver<std::vector<Line>>, public IObserver<Position> {
public:
  explicit ScreenRenderer(IScreen& screen) : _screenAdapter(screen) {}

  void Update(const ISubject<std::vector<Line>>& subject) override;
  void Update(const ISubject<Position>& subject) override;
  void Start() override;
  void Stop() override;

private:
  IScreen& _screenAdapter;
};
