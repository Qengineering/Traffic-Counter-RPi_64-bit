#ifndef MJPG_SENDER_H
#define MJPG_SENDER_H
#include <sys/types.h>
#include <sys/socket.h>
#include <opencv2/opencv.hpp>
//----------------------------------------------------------------------------------------
#define PORT         unsigned short
#define SOCKET       int
#define HOSTENT      struct hostent
#define SOCKADDR     struct sockaddr
#define SOCKADDR_IN  struct sockaddr_in
#define ADDRPOINTER  unsigned int*
//----------------------------------------------------------------------------------------
void send_json_custom(char const* send_buf, int port, int timeout);
//----------------------------------------------------------------------------------------
class MJPG_sender
{
protected:
    SOCKET sock;
    SOCKET maxfd;
    fd_set master;
    int timeout;                // master sock timeout, shutdown after timeout usec.
    int quality;                // jpeg compression [1..100]
    int close_all_sockets;
    int _write(int sock, char const*const s, int len)
    {
        if (len < 1) { len = strlen(s); }
        return ::send(sock, s, len, 0);
    }
public:
    MJPG_sender(int port = 0, int _timeout = 400000, int _quality = 30);
    ~MJPG_sender(void);
    bool release(void);
    void close_all(void);
    bool open(int port);
    bool isOpened(void);
    bool write(const cv::Mat & frame);
};
//----------------------------------------------------------------------------------------
#endif // MJPG_SENDER_H
