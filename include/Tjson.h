#ifndef TJSON_H
#define TJSON_H

#include "General.h"
#include <nlohmann/json.hpp>

using json = nlohmann::ordered_json; // Use ordered_json to preserve original key order

//----------------------------------------------------------------------------------------
class Tjson
{
friend class ThreadCam;
friend class TProcessPipe;
friend class TMapper;
friend class TPortal;
public:
    Tjson();
    ~Tjson();
    bool LoadFromFile(const std::string FileName);
    void Save(void);
    bool GetSettings(void);
    //  ------------------------------------------------------
    //  your config.json settings
    //  ------------------------------------------------------
    //   input
    std::string Stream;         ///< used input stream
    //   border
    int  X1;                    ///< location of counting border
    int  Y1;                    ///< location of counting border
    int  X2;                    ///< location of counting border
    int  Y2;                    ///< location of counting border
    //   output
    bool MQTT_On;               ///< output json though MQTT
    bool Annotate;              ///< draw DNN output on screen
    std::string MQTT_Server;    ///< MQTT server
    std::string MQTT_Client;    ///< MQTT client
    std::string TopicName;      ///< MQTT topic string
    std::string DeviceName;     ///< Name of the device (or location)
    int  JSON_Port;             ///< output stream json (0 = no stream, usually 8070)
    int  MJPEG_Port;            ///< output stream mjpeg (0 = no stream, usually 8090)
    int  MJPEG_Width;           ///< output image width 8090 stream
    int  MJPEG_Height;          ///< output image height 8090 stream
    int  MesSec;                ///< send every MesSec a (MQTT) message into the world
    //   administration
    std::string  Version;       ///< Version string
    //   DNN models
    std::string  Pstr;          ///< Param ncnn model file name
    std::string  Bstr;          ///< Bin ncnn model file name
    //  ------------------------------------------------------
public: //private:
    json j;
private:
    std::string JsonFile;
    bool Jvalid;
    //using root
    bool GetSetting(const std::string Key, int& Value);
    bool GetSetting(const std::string Key, bool& Value);
    bool GetSetting(const std::string Key, double& Value);
    bool GetSetting(const std::string Key, std::string& Value);
    //using entry s
    bool GetSetting(const json& s, const std::string Key, int& Value);
    bool GetSetting(const json& s, const std::string Key, bool& Value);
    bool GetSetting(const json& s, const std::string Key, double& Value);
    bool GetSetting(const json& s, const std::string Key, std::string& Value);
};
///<  ----------------------------------------------------------------------------------------

#endif ///<   TJSON_H
