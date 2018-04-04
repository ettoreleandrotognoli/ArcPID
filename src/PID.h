#ifndef __ARC_PID__
#define __ARC_PID__

#ifdef __linux__

#include "linux/Arduino.hpp"

#else

#include <Arduino.h>

#endif

namespace arc {

  template<typename V>
  class PID {
  protected:
    unsigned long lastTime;
    V integral;
    V error;
    V ouput;
    V target;

    V kp;
    V ki;
    V kd;

    bool errorMagnitudeChanged(V newError) const;

  public:

    PID(V kp,V ki, V kd);
    void setInput(V value);
    void setInput(V value, unsigned long t);
    V update(V feedback, unsigned long interval);
    V getOutput() const;
    PID<V>& setKp(V kp);
    PID<V>& setKi(V ki);
    PID<V>& setKd(V kd);
    const V getKp() const;
    const V getKi() const;
    const V getKd() const;
    PID<V>& setTarget(V target);
    const V getTarget() const;

  };

  template<typename V>
  PID<V>::PID(V kp,V ki,V kd){
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;
    this->lastTime = 0;
    this->error = 0;
  }

  template<typename V>
  void PID<V>::setInput(V value){
    unsigned long t = millis();
    this->setInput(value,t);
  }

  template<typename V>
  void PID<V>::setInput(V value,unsigned long t){
    this->update(value,t - this->lastTime); 
    this->lastTime = t;
  }

  template<typename V>
  bool PID<V>::errorMagnitudeChanged(V newError) const{
    if(newError > 0 && this->error < 0){
      return true;
    }
    if(newError < 0 && this->error > 0){
      return true;
    }
    return false;
  }

  template<typename V>
  V PID<V>::update(V feedback, unsigned long interval){
    V p,i,d;
    V error = this->target - feedback;
    V dt = ((double)interval)/1000.0;

    if(this->errorMagnitudeChanged(error)){
      this->integral = 0;
    }

    this->integral += error * dt;

    p = this->kp * error;
    i = this->ki * this->integral;
    if(interval > 0){
      d = this->kd * (error - this->error)/ dt;
    }
    else{
      d = 0;
    }
    this->error = error;
    this->ouput = p + i + d;
    return this->ouput;
  }

  template<typename V>
  inline V PID<V>::getOutput() const {
    return this->ouput;
  }

  template<typename V>
  inline PID<V>& PID<V>::setKp(V kp){
    this->kp = kp;
    return *this;
  }

  template<typename V>
  inline const V PID<V>::getKp() const{
    return this->kp;
  }

  template<typename V>
  inline PID<V>& PID<V>::setKi(V ki){
    this->ki = ki;
    return *this;
  }

  template<typename V>
  inline const V PID<V>::getKi() const{
    return this->ki;
  }

  template<typename V>
  inline PID<V>& PID<V>::setKd(V kd){
    this->kd = kd;
    return *this;
  }

  template<typename V>
  inline const V PID<V>::getKd() const{
    return this->kd;
  }

  template<typename V>
  inline PID<V>& PID<V>::setTarget(V target){
    this->target = target;
    return *this;
  }

  template<typename V>
  inline const V PID<V>::getTarget() const{
    return this->target;
  }

}

#endif