#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <gtest/gtest.h>
#include "LimitedPID.h"


using namespace arc;


TEST(LimitedPID,Init){
  double target = 30.0;
  unsigned long t = 0;
  PID<double> pid(1.0,0.5,0.9);
  LimitedPID<double> rpid(pid,std::make_pair(0,100));
  double g = 9.8;
  double ac = 0;
  double ds = 0;
  int inc = 10;
  rpid.setTarget(target);
  for(int i=0;i<1000;i++){
    t += inc;
    rpid.setInput(ds,t);
    ac = rpid.getOutput(ac);
    ds += (ac - g) * ((double)inc / 1000.0);
    printf("ac=%f,ds=%f,t=%d\n",ac,ds,t);
  }
  EXPECT_EQ(round(ds),target);
}


int main(int argc,char ** argv){
  testing::InitGoogleTest(&argc,argv);
  return RUN_ALL_TESTS();
}
