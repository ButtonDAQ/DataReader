#ifndef TIME_SLICE_H
#define TIME_SLICE_H

#include <vector>
#include <map>
#include <mutex>
#include <type_traits>

#include <cstddef>
#include <Hit.h>

using namespace ToolFramework;


enum class TriggerType {nhits, calib, zero_bias};

class TriggerInfo : SerialisableObject{

public:

  TriggerInfo(){;}
  TriggerInfo(TriggerType in_type, Time in_time){
    type = in_type;
    time = in_time;
  }
  TriggerType type;
  Time time;

  std::string GetType(TriggerType type){
    switch (type) {
      
    case TriggerType::nhits:
      return "nhits";
      
    case TriggerType::calib:
      return "calib";
      
    case TriggerType::zero_bias:
      return "zero_bias";
      
    default:
      return "";
    }
  }
  
  bool Print(){

    std::cout<<"Trigger "<<GetType(type)<<":"<<time.Print()<<std::endl;

    return true;
  }
  std::string GetVersion(){return "1.0";};
  bool Serialise(BinaryStream &bs){
    

    bs & type;
    bs & time; 
    
    return true;
  }
};

class TimeSlice : SerialisableObject {

public:
  
  Time time;
  std::vector<Hit> hits;
  std::mutex mutex;
  std::vector<TriggerInfo> triggers;

  bool Print(){


    std::cout<<std::endl<<"time="<<time.Print()<<std::endl;
    std::cout<<" hits size="<<hits.size()<<std::endl;

    for(size_t i=0; i<hits.size(); i++){
      std::cout<<"  hit "<<i<<":";
      hits.at(i).Print();
      std::cout<<std::endl;
    }

    std::cout<<std::endl<<" triggers size="<<triggers.size()<<std::endl;

    for(size_t i=0; i<triggers.size(); i++){
      std::cout<<"  trigger "<<i<<":";
      triggers.at(i).Print();
       std::cout<<std::endl;
    }
    std::cout<<std::endl;

    return true;
  }

  std::string GetVersion(){return "1.0";};
  bool Serialise(BinaryStream &bs){

    bs & time;
    bs & hits;
    bs & triggers;
    
    return true;
  }


  
};

#endif
