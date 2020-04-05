#ifndef SensorManager_H
#define SensorManager_H

#include "GPS.cpp"
#include "Barometer.cpp"
#include <thread>

class SensorManager
{
  private:
    
    static bool isLooping = false;
    thread sensor_thread;

    static void thread_update_loop(double *status);

  public:

    void startThread(double *status);
    void stropThread();
    
};

#endif