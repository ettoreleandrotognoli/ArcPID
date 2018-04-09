#ifndef __ARC_PID__
#define __ARC_PID__

#include <tuple>

#ifdef __linux__

#include "linux/Arduino.hpp"

#else

#include <Arduino.h>

#endif

namespace arc {

  template<typename V>
  class PID {
  public:
    PID(std::tuple<V,V,V> pid);
    PID(V kp,V ki, V kd);
    PID(const PID& pid);
    virtual ~PID();
    void setInput(const V& value);
    void setInput(const V& value, unsigned long t);
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


  };

  template<typename V>
  PID<V>::PID(std::tuple<V,V,V> pid){
    this->kp = std::get<0>(pid);
    this->ki = std::get<1>(pid);
    this->kd = std::get<2>(pid);
    this->lastTime = 0;
    this->error = 0;
  }

  template<typename V>
  PID<V>::PID(V kp,V ki,V kd){
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;
    this->lastTime = 0;
    this->error = 0;
  }

  template<typename V>
  PID<V>::PID(const PID<V>& pid){
    this->kp = pid.kp;
    this->ki = pid.ki;
    this->kd = pid.kd;
    this->lastTime = 0;
    this->error = 0;
  }

  template<typename V>
  PID<V>::~PID(){
  }

  template<typename V>
  inline void PID<V>::setInput(const V& value){
    unsigned long t = millis();
    this->setInput(value,t);
  }

  template<typename V>
  inline void PID<V>::setInput(const V& value,unsigned long t){
    this->update(value,t - this->lastTime); 
    this->lastTime = t;
  }

  template<typename V>
  inline bool PID<V>::errorMagnitudeChanged(V newError) const{
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