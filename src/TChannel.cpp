#include "TChannel.h"
#include "Tjson.h"
#include "General.h"
#include "MQTT.h"
#include "MJPG_sender.h"
//----------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------
extern Tjson   Js;
extern slong64 FrameCnt;
extern float   FPS;
extern const char* class_names[];
//----------------------------------------------------------------------------------
// Publish MQTT message with a JSON payload
//----------------------------------------------------------------------------------
void publishMQTTMessage(const string& topic, const string payload)
{
    mqtt_publish(topic, payload);
}
//----------------------------------------------------------------------------------
// TChannel class
//----------------------------------------------------------------------------------------
TChannel::TChannel()
{
    ResetCntAr();
}
//----------------------------------------------------------------------------------------
TChannel::~TChannel()
{
}
//----------------------------------------------------------------------------------------
void TChannel::Init(void)
{
    p1.X=static_cast<float>(Js.X1);
    p1.Y=static_cast<float>(Js.Y1);
    p2.X=static_cast<float>(Js.X2);
    p2.Y=static_cast<float>(Js.Y2);
}
//----------------------------------------------------------------------------------------
void TChannel::ResetCntAr(void)
{
    for(int i=0;i<80;i++) CntAr[i]=0;
}
//----------------------------------------------------------------------------------------
void TChannel::Execute(std::vector<bbox_t> objs)
{
    //loop through the objects
    for(size_t b=0;b<objs.size();b++){
        size_t n;
        //search for the object in the list
        if(FindObject(objs[b],n)){
            //object already in the scene, so update
            MapList[n].load(objs[b],FrameCnt);
            CountObjects(MapList[n]);
        }
        else{
            //new object
            TObject Mo;
            Mo.load(objs[b],FrameCnt);
            Mo.Box_T0 = Mo.Box;
            MapList.push_back(Mo);
        }
    }
    //remove old, unused objects
    CleanList();
}
//----------------------------------------------------------------------------------------
void TChannel::SendMessage(void)
{
    MQTTevent();
}
//----------------------------------------------------------------------------------------
// Some local subroutines
//----------------------------------------------------------------------------------------
// Function to check if p3 is above and p4 is below the line defined by p1 and p2
bool TChannel::isAboveAndBelow(const BBox<float> &Loc3, const BBox<float> &Loc4)
{
    double a1 = p2.Y - p1.Y;
    double b1 = p1.X - p2.X;
    double c1 = a1 * p1.X + b1 * p1.Y;

    double a2 = Loc4.b - Loc3.b;
    double b2 = Loc3.a - Loc4.a;
    double c2 = a2 * Loc3.a + b2 * Loc3.b;

    double determinant = a1 * b2 - a2 * b1;

    if (determinant == 0) return false; // Lines are parallel (or coincident)
    else {
        double x = (b2 * c1 - b1 * c2) / determinant;
        double y = (a1 * c2 - a2 * c1) / determinant;

        // Calculate the signed distances of p3 and p4 from the line (p1, p2)
        float positionP3 = (p2.X - p1.X) * (Loc3.b - p1.Y) - (p2.Y - p1.Y) * (Loc3.a - p1.X);
        float positionP4 = (p2.X - p1.X) * (Loc4.b - p1.Y) - (p2.Y - p1.Y) * (Loc4.a - p1.X);

        // Check if p3 is above (positive signed distance) and p4 is below (negative signed distance) or vice versa
        if ((positionP3 > 0.0 && positionP4 < 0.0) || (positionP3 < 0.0 && positionP4 > 0.0)){
            // check if a point is within a line segment
            return std::min(p1.X, p2.X) <= x && x <= std::max(p1.X, p2.X) &&
                   std::min(p1.Y, p2.Y) <= y && y <= std::max(p1.Y, p2.Y);
        }
        else return false; //both p3 and p4 are above or below the (p1,p2) line
    }
}
//----------------------------------------------------------------------------------------
void TChannel::CountObjects(TObject &Ob)
{
    if(Ob.Tdone) return;

    if( isAboveAndBelow(Ob.Box_T0, Ob.Box) ){
        if(Ob.Obj<80){
            if(Ob.Obj == 6) CntAr[7]++;  //repair train -> truck
            else            CntAr[Ob.Obj]++;
        }
        Ob.Tdone=true;
    }

}
//----------------------------------------------------------------------------------------
void TChannel::CleanList(void)
{
    size_t lim = 2*FPS;
    // Remove objects not updated in the last 3*FPS seconds
    MapList.erase(
        std::remove_if(MapList.begin(), MapList.end(),
                       [this, lim](const TObject& obj) {
                            return (FrameCnt - obj.Tframe) > lim; }),
        MapList.end());
}
//----------------------------------------------------------------------------------------
bool TChannel::FindObject(const bbox_t& bo, size_t& j)
{
    auto it = std::find_if(MapList.begin(), MapList.end(),
                           [&bo](const TObject& obj) {
                               return obj.Obj == bo.obj_id && obj.Track == bo.track_id;
                           });

    if (it != MapList.end()) {
        j = std::distance(MapList.begin(), it); // Set the index of the found object
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
std::ostringstream TChannel::GetJSONstring(void)
{
    std::ostringstream oj;

    //compose the string
    oj << "{\n\"name\": \"" << Js.DeviceName << "\",";
    oj<< "\n\""<< class_names[1] << "\": "<< CntAr[0] << ",";   //person
    oj<< "\n\""<< class_names[2] << "\": "<< CntAr[1] << ",";   //bicycle
    oj<< "\n\""<< class_names[3] << "\": "<< CntAr[2] << ",";   //car
    oj<< "\n\""<< class_names[4] << "\": "<< CntAr[3] << ",";   //motorbike
    oj<< "\n\""<< class_names[6] << "\": "<< CntAr[5] << ",";   //bus
    oj<< "\n\""<< class_names[8] << "\": "<< CntAr[7] << "\n}"; //truck

    return oj;
}
//---------------------------------------------------------------------------
void TChannel::MQTTevent(void) //also calling JSONevent
{
    std::ostringstream oj=GetJSONstring();

    if(Js.MQTT_On){
        publishMQTTMessage(Js.TopicName,oj.str());     //send mqtt into the world
    }

    //send json into the world (port 8070)
    if(Js.JSON_Port>0){
        SendJsonHTTP(oj.str(), Js.JSON_Port);          //send json to port 8070
    }
}
//----------------------------------------------------------------------------------------
bool TChannel::SendJsonHTTP(std::string send_json, int port, int timeout)
{
    send_json_custom(send_json.c_str(), port, timeout);

    return true;
}
//----------------------------------------------------------------------------------------
