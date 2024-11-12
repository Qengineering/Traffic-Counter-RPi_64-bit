#ifndef TCHANNEL_H
#define TCHANNEL_H

#include "General.h"
//---------------------------------------------------------------------------
class TChannel
{
private:
    Point2<float> p1;
    Point2<float> p2;
private:
    bool isAboveAndBelow(const BBox<float> &Loc3, const BBox<float> &Loc4);
    bool FindObject(const bbox_t& bo,size_t& j);
    void CountObjects(TObject &Ob);
    void CleanList(void);
protected:
protected:
    void MapDynamic(void);
    void MQTTevent(void);        //also calling JSONevent
    bool SendJsonHTTP(std::string send_json, int port = 8070, int timeout = 400000);
    std::ostringstream GetJSONstring(void);
public:
    TChannel();
    virtual ~TChannel();
    int CntAr[80];
    std::vector<TObject> MapList;    ///< Objects currently in the scene

    void Init(void);
    void ResetCntAr(void);
    void SendMessage(void);
    void Execute(std::vector<bbox_t> objs);
};
//----------------------------------------------------------------------------------------
#endif // TCHANNEL_H
