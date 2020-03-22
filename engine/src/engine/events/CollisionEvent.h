//
// Created by philipp on 3/22/20.
//

#pragma once

#include "Event.h"
#include "engine/game/KineticBody.h"

namespace Engine {
  class CollisionEvent: public Event
  {
    KineticBody GetKineticBody() { return m_Body; }

    EVENT_CLASS_CATEGORY(EventCategoryCollision);

  private:
    KineticBody m_Body;
  };
  class BodyEnteredEvent: public CollisionEvent
  {
    EVENT_CLASS_TYPE(BodyEntered);
  };
  class BodyExitedEvent: public CollisionEvent
  {
    EVENT_CLASS_TYPE(BodyExited);
  };
}