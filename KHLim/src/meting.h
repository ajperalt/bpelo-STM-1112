#include <stdio.h>
#include <timeToFrequency.h>
#include <frequencyToForce.h>

class Meting
{
private:
   unsigned float meting;
   int timeToFrequency;
   int frequency;
   int frequencyToForce;
   int force;
   
public:
   Meting(int timeToFrequency, int frequencyToForce);
   ~Meting();
   
   unsigned float meting();
   int timeToFrequency();
   int frequency();
   int frequencyToForce();
   int force();
   
   bool meting(unsigned float meting);
   bool timeToFrequency(int timeToFrequency);
   bool frequency(int frequency);
   bool frequencyToForce(int frequencyToForce);
   // force setter is er niet!
};