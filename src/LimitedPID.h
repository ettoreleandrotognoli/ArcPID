#ifndef __ARC_RELATIVE_PID__
#define __ARC_RELATIVE_PID__

#include <utility> 
#include <tuple>
#include <algorithm>
#include "PID.h"




namespace arc{

  template<typename V>
  class LimitedPID {
  private:
  protected:
    PID<V>& pid;
    std::pair<V,V> outputLimits;
  public:
    LimitedPID(PID<V> pid,std::pair<V,V> outputLimits);
    void setInput(const V& value);
    void setInput(const V& value,unsigned long t);
    V getOutput(const V& last) const;
    void setTarget(V target);
  };


  template<typename V>
  LimitedPID<V>::LimitedPID(PID<V> pid, std::pair<V,V> outputLimits) : pid(pid){
    this->outputLimits = outputLimits;
  }

  template<typename V>
  void LimitedPID<V>::setInput(const V& value){
    this->pid.setInput(value);
  }

  template<typename V>
  void LimitedPID<V>::setInput(const V& value,const unsigned long t){
    this->pid.setInput(value,t);
  }

  template<typename V>
  void LimitedPID<V>::setTarget(V value){
    this->pid.setTarget(value);
  }

  template<typename V>
  V LimitedPID<V>::getOutput(const V& last) const{
    return std::max(std::min(last + this->pid.getOutput(),outputLimits.second),outputLimits.first);
  }


};



#endif