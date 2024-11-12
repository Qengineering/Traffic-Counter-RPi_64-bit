//----------------------------------------------------------------------------------------
//
// Created by Q-engineering 2023/1/2
//
//----------------------------------------------------------------------------------------
#include "Tjson.h"
//----------------------------------------------------------------------------------------
Tjson::Tjson(): MJPEG_Port(0)
{
    Jvalid=false;
}
//----------------------------------------------------------------------------------------
Tjson::~Tjson()
{
    //dtor
}
//----------------------------------------------------------------------------------------
bool Tjson::LoadFromFile(const std::string FileName)
{
    if(std::filesystem::exists(FileName)){
        try{
            std::ifstream f(FileName);
            j = json::parse(f);
            Jvalid=true;
            JsonFile = FileName;
        }
        catch ( ... ){
            std::cout << "parse error in file " << FileName << std::endl;
        }
    }
    else{
        Jvalid=false;
        std::cout << FileName << " file not found!" << std::endl;
    }

    return Jvalid;
}
//----------------------------------------------------------------------------------------
void Tjson::Save(void)
{
    if(Jvalid){
        // Save the changes back to the json file
        std::ofstream outFile(JsonFile);
        outFile << std::setw(4) << j << std::endl;
    }
}
//----------------------------------------------------------------------------------------
bool Tjson::GetSettings(void)
{
    std::string Jstr, Sstr;
    bool Success=false;

    if(Jvalid){
        //   input
        if(!GetSetting("STREAM",Stream))                          return Success;
        //   border
        if(!GetSetting("BORDER_X1",X1))                           return Success;
        if(!GetSetting("BORDER_Y1",Y1))                           return Success;
        if(!GetSetting("BORDER_X2",X2))                           return Success;
        if(!GetSetting("BORDER_Y2",Y2))                           return Success;
        //   output
        if(!GetSetting("MQTT_ON",MQTT_On))                        return Success;
        if(!GetSetting("MQTT_SERVER",MQTT_Server))                return Success;
        if(!GetSetting("MQTT_CLIENT_ID",MQTT_Client))             return Success;
        if(!GetSetting("MQTT_TOPIC",TopicName))                   return Success;
        if(!GetSetting("DEVICE_NAME",DeviceName))                 return Success;
        if(!GetSetting("MESSAGE_TIME",MesSec))                    return Success;
        if(!GetSetting("JSON_PORT",JSON_Port))                    return Success;
        if(!GetSetting("MJPEG_PORT",MJPEG_Port))                  return Success;
        if(!GetSetting("MJPEG_WIDTH",MJPEG_Width))                return Success;
        if(!GetSetting("MJPEG_HEIGHT",MJPEG_Height))              return Success;
        if(!GetSetting("ANNOTATE",Annotate))                      return Success;
        //   administration
        if(!GetSetting("VERSION",Version))                        return Success;
        //   DNN models
        if(!GetSetting("PARAM_MODEL",Pstr))                       return Success;
        if(!GetSetting("BIN_MODEL",Bstr))                         return Success;

        //so far, so good
        Success=true;
    }

    return Success;
}
//----------------------------------------------------------------------------------------
bool Tjson::GetSetting(const std::string Key,std::string& Value)
{
    bool Success=false;

    if(Jvalid){
        //read the key
        Value = j.at(Key);
        if(Value.empty()){
            std::cout << "Error reading value of "<< Key <<" in json file!" << std::endl;
        }
        else Success=true;
    }

    return Success;
}
//----------------------------------------------------------------------------------------
bool Tjson::GetSetting(const std::string Key,bool& Value)
{
    bool Success=false;

    if(Jvalid){
        //read the key
        try{
            Value = j.at(Key);
            Success=true;
        }
        catch( ... ){
            std::cout << "Error reading value of "<< Key <<" in json file!" << std::endl;
        }
    }

    return Success;
}
//----------------------------------------------------------------------------------------
bool Tjson::GetSetting(const std::string Key,int& Value)
{
    bool Success=false;

    if(Jvalid){
        try{
            Value = j.at(Key);
            Success=true;
        }
        catch( ... ){
            std::cout << "Error reading value of "<< Key <<" in json file!" << std::endl;
        }
    }

    return Success;
}
//----------------------------------------------------------------------------------------
bool Tjson::GetSetting(const std::string Key,double& Value)
{
    bool Success=false;

    if(Jvalid){
        try{
            Value = j.at(Key);
            Success=true;
        }
        catch( ... ){
            std::cout << "Error reading value of "<< Key <<" in json file!" << std::endl;
        }
    }

    return Success;
}
//----------------------------------------------------------------------------------------
bool Tjson::GetSetting(const json& s,const std::string Key,std::string& Value)
{
    bool Success=false;

    if(Jvalid){
        //read the key
        Value = s.at(Key);
        if(Value.empty()){
            std::cout << "Error reading value of "<< Key <<" in json file!" << std::endl;
        }
        else Success=true;
    }

    return Success;
}
//----------------------------------------------------------------------------------------
bool Tjson::GetSetting(const json& s, const std::string Key,bool& Value)
{
    bool Success=false;

    if(Jvalid){
        //read the key
        try{
            Value = s.at(Key);
            Success=true;
        }
        catch( ... ){
            std::cout << "Error reading value of "<< Key <<" in json file!" << std::endl;
        }
    }

    return Success;
}
//----------------------------------------------------------------------------------------
bool Tjson::GetSetting(const json& s, const std::string Key,int& Value)
{
    bool Success=false;

    if(Jvalid){
        try{
            Value = s.at(Key);
            Success=true;
        }
        catch( ... ){
            std::cout << "Error reading value of "<< Key <<" in json file!" << std::endl;
        }
    }

    return Success;
}
//----------------------------------------------------------------------------------------
bool Tjson::GetSetting(const json& s, const std::string Key,double& Value)
{
    bool Success=false;

    if(Jvalid){
        try{
            Value = s.at(Key);
            Success=true;
        }
        catch( ... ){
            std::cout << "Error reading value of "<< Key <<" in json file!" << std::endl;
        }
    }

    return Success;
}
//----------------------------------------------------------------------------------------

