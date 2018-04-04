#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <gtest/gtest.h>
#include "PID.h"


using namespace arc;


TEST(PID,Init){
  double target = 30.0;
  unsigned long t = 0;
  PID<double> pid(1.0,0.5,0.9);
  pid.setInput(0, t);
  double g = 9.8;
  double ac = 0;
  double ds = 0;
  int inc = 10;
  pid.setTarget(target);
  for(int i=0;i<1000;i++){
    t += inc;
    pid.setInput(ds,t);
    double result = pid.getOutput();
    ac += result;
    ds += (ac - g) * ((double)inc / 1000.0);
  }
  EXPECT_EQ(round(ds),target);
}


int main(int argc,char ** argv){
  testing::InitGoogleTest(&argc,argv);
  return RUN_ALL_TESTS();
}