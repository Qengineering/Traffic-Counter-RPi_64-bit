#include "MJPGthread.h"
//----------------------------------------------------------------------------------
MJPGthread::MJPGthread()
{
    MJsend = NULL;
}
//----------------------------------------------------------------------------------
MJPGthread::~MJPGthread()
{
    if(MJsend!=NULL){
        delete MJsend;
    }
}
//----------------------------------------------------------------------------------
void MJPGthread::Init(int Port)
{
    MJsend = new MJPG_sender(Port, 500000, 70);
}
//----------------------------------------------------------------------------------
void MJPGthread::Send(cv::Mat& mat)
{
    try {
        std::lock_guard<std::mutex> lock(mtx_mjpeg);
        MJsend->write(mat);
    }
    catch (...) {
        std::cerr << " Error in send_mjpeg() function \n";
    }
}
//----------------------------------------------------------------------------------
