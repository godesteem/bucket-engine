//
// Created by philipp on 3/22/20.
//

#pragma once

#include "Event.h"
#include "engine/game/KineticBody.h"

namespace Engine {
  class CollisionEvent: public Event
  {
  public:
    explicit CollisionEvent(KineticBody body): m_Body(body){}
    KineticBody GetKineticBody() { return m_Body; }

    EVENT_CLASS_CATEGORY(EventCategoryCollision);

  private:
    KineticBody m_Body;
  };
  class BodyEnteredEvent: public CollisionEvent
  {
  public:
    explicit BodyEnteredEvent(KineticBody body): CollisionEvent(body){};
    EVENT_CLASS_TYPE(BodyEntered);
  };
  class BodyExitedEvent: public CollisionEvent
  {
  public:
    explicit BodyExitedEvent(KineticBody body): CollisionEvent(body){};
    EVENT_CLASS_TYPE(BodyExited);
  };
}