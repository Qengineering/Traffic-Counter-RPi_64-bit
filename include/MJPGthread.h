#ifndef MJPGTHREAD_H
#define MJPGTHREAD_H
#include "MJPG_sender.h"
#include <opencv2/opencv.hpp>
//----------------------------------------------------------------------------------
class MJPGthread
{
public:
    MJPGthread();
    virtual ~MJPGthread();

    void Init(int Port);
    void Send(cv::Mat& mat);
protected:

private:
    MJPG_sender* MJsend;
    std::mutex mtx_mjpeg;
};
//----------------------------------------------------------------------------------
#endif // MJPGTHREAD_H
