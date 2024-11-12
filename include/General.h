#ifndef GENERAL_H_INCLUDED
#define GENERAL_H_INCLUDED

//---------------------------------------------------------------------------
// get OS
//---------------------------------------------------------------------------

#ifdef __aarch64__
#if __has_include("rknn_api.h")
    #define ROCK5
#else
    #define JETSON
#endif // __has_include
#else
    #define PC
#endif // __aarch64__

//---------------------------------------------------------------------------
// includes
//---------------------------------------------------------------------------

#include <cstdint>
#include <cmath>
#include <deque>
#include <list>
#include <array>
#include <memory>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <istream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <chrono>
#include <vector>
#include <ctime>
#include <cctype>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <thread>
#include <atomic>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include "Tjson.h"
#include "Numbers.h"
//---------------------------------------------------------------------------
/**
    Global used parameters, structures and macros
*/
//---------------------------------------------------------------------------

#define VERSION "1.0.0.0"

//---------------------------------------------------------------------------
// LERP(a,b,c) = linear interpolation macro, is 'a' when c == 0.0 and 'b' when c == 1.0 */
#define MIN(a,b)  ((a) > (b) ? (b) : (a))               ///< Returns minimum value of a or b
#define MAX(a,b)  ((a) < (b) ? (b) : (a))               ///< Returns maximum value of a or b
#define LIM(a,b,c) (((a)>(c))?(c):((a)<(b))?(b):(a))    ///< Limits the value of a between b and c
#define LERP(a,b,c) (((b) - (a)) * (c) + (a))           ///< Linear interpolation returns 'a' when c == 0.0 and 'b' when c == 1.0
#define ROUND(a) (static_cast<int>((a)+0.5))            ///< Round a float to the nearest integer value
#define EUCLIDEAN(x1,y1,x2,y2) sqrt(((x1)-(x2))*((x1)-(x2))+((y1)-(y2))*((y1)-(y2)))    ///< Returns the Euclidean distance between two points.

//----------------------------------------------------------------------------------
struct bbox_t {
    unsigned int x, y, w, h;       ///< (x,y) - top-left corner, (w, h) - width & height of bounded box
    float prob;                    ///< confidence - probability that the object was found correctly
    unsigned int obj_id;           ///< class of object - from range [0, classes-1]
    unsigned int track_id;         ///< tracking id for video (0 - untracked, 1 - inf - tracked object)
};
//---------------------------------------------------------------------------
template<typename Tp> struct BBox
{
	Tp l; ///< left
	Tp r; ///< right
	Tp t; ///< top
	Tp b; ///< bottom
	Tp a; ///< anchor a.x=(l+r)/2  a.y=b
	Tp s; ///< size (a.r - a.l)*(a.b - a.t)

	BBox(): l(0),r(0),t(0),b(0),a(0),s(0) {}

	inline float IoU(const BBox &a){
        if (l > a.r || r < a.l || t > a.b || b < a.t) return 0.0;
        else
        {
            float dx    = std::min(r, a.r) - std::max(l, a.l);
            float dy    = std::min(b, a.b) - std::max(t, a.t);
            float inter = dx*dy;      // Intersection
            float uni   = s + a.s;    // Union
            float IoU   = inter / uni;
            return IoU;
        }
	}
};
//---------------------------------------------------------------------------
//do not add dynamic objects to the list!! like cv::mat or std::string
//---------------------------------------------------------------------------
struct TObject
{
    BBox<float>   Box;      ///< bounding box
    BBox<float>   Box_T0;   ///< firts BBox (t-1)
    float         Prob;     ///< confidence - probability that the object was found correctly
    unsigned int  Obj;      ///< class of object - from range [0, classes-1]
    unsigned int  Track;    ///< tracking id in video
    bool          Tdone;    ///< track has been set
    size_t        Tframe;   ///< actual frame count

	TObject(): Prob(0.0), Obj(-1), Track(0), Tdone {false}, Tframe {0} {}

	inline void load(const bbox_t& b, const slong64 _Cnt){
	    Box.l  = b.x;
	    Box.t  = b.y;
	    Box.r  = b.x+b.w;
	    Box.b  = b.y+b.h;
	    Box.s  = b.w*b.h;
	    Box.a  = (Box.l+Box.r)/2;
        Prob   = b.prob;
        Obj    = b.obj_id;
        Track  = b.track_id;
//        Tdone  = false;       //do not reset Tdone
        Tframe = _Cnt;
	}
};
//----------------------------------------------------------------------------------------
inline float GetTemp(void)
{
    std::ifstream myfile;
    float temp=0.0;
    std::string line;

    myfile.open("/sys/class/thermal/thermal_zone0/temp");
    if (myfile.is_open()) {
        getline(myfile,line);
        temp = stoi(line)/1000.0;
        myfile.close();
    }
    return temp;
}
//---------------------------------------------------------------------------
// to lower case
static inline void lcase(std::string &s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return std::tolower(c); });
}
//---------------------------------------------------------------------------
// to lower case (copying)
static inline std::string lcase_copy(std::string s) {
    lcase(s);
    return s;
}
//---------------------------------------------------------------------------
// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}
//---------------------------------------------------------------------------
// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}
//---------------------------------------------------------------------------
// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}
//---------------------------------------------------------------------------
// trim from start (copying)
static inline std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}
//---------------------------------------------------------------------------
// trim from end (copying)
static inline std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}
//---------------------------------------------------------------------------
// trim from both ends (copying)
static inline std::string trim_copy(std::string s) {
    trim(s);
    return s;
}
//---------------------------------------------------------------------------
#endif // GENERAL_H_INCLUDED
