#pragma once

namespace Engine {
  /**
   * Timestep class, holds
   */
  class Timestep
  {
  public:

    /**
     * Default constructor
     * @param time: time unit in Seconds
     */
    Timestep(float time = 0.0f)
    :m_Time(time)
    { }

    /**
     * Cast to float
     * @return m_Time (Seconds)
     */
    operator float() const { return m_Time; };

    /**
     * Getter for Seconds
     * @return m_Time (in Seconds)
     */
    float GetSeconds() { return m_Time; };

    /**
     * Getter for Milliseconds
     * @returns m_Time in Milliseconds
     */
    float GetMilliseconds() { return m_Time * 1000.0f; };

  private:
    float m_Time; /*!<  time unit in Seconds */
  };
}
