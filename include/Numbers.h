//---------------------------------------------------------------------------
// Q-engineering 1997 - 2023
//---------------------------------------------------------------------------
#ifndef NumbersH
#define NumbersH
#include "math.h"
#include "float.h"
#include <vector>
#include <opencv2/opencv.hpp>
//---------------------------------------------------------------------------
typedef signed long long int slong64;       ///< largest possible integer.<br> At least 64 bits
//----------------------------------------------------------------------------------
enum ObjectType {
    NONE = -1,
    PERSON,
    BIKE,
    CAR
};
//----------------------------------------------------------------------------------
enum FlowType {
    PHANTOM = -1,
    IN,
    OUT,
    UNKNOWN
};
//----------------------------------------------------------------------------------
enum DirectionType { N, NE, E , SE, S, SW, W, NW };
//---------------------------------------------------------------------------
template<typename Tp> struct Point2
{
	Tp X, Y;

	Point2(): X(0),Y(0) {}
	Point2(const Tp& a): X(a),Y(a) {}
	Point2(const Tp& x,const Tp& y): X(x),Y(y) {}

	inline void   operator  =(const Point2 &a) { X=a.X; Y=a.Y; }
	inline Point2 operator  -(const Point2 &a) { Point2 D; D.X=X-a.X; D.Y=Y-a.Y; return D; }
	inline Point2 operator  *(const double &a) { Point2 D; D.X=a*X; D.Y=a*Y; return D; }
	inline void   operator -=(const Point2 &a) { X-=a.X; Y-=a.Y; }
	inline void   operator /=(const double &a) { X/=a; Y/=a; }
	inline void   operator /=(const Point2 &a) { X/=a.X; Y/=a.Y; }
	inline double Length(const Point2 &a){ return sqrt((X-a.X)*(X-a.X)+(Y-a.Y)*(Y-a.Y)); }
};
//---------------------------------------------------------------------------
template<typename Tp> struct Point3
{
	Tp X, Y, A;             //most of the time: x=X, y=Y, angle=A

	Point3(): X(0),Y(0),A(0) {}
	Point3(const Tp& t): X(t),Y(t),A(t) {}
	Point3(const Tp& x,const Tp& y,const Tp& t): X(x),Y(y),A(t) {}

	inline void   operator  =(const Point3 &t) { X=t.X; Y=t.Y; A=t.A; }
	inline Point3 operator  -(const Point3 &t) { Point3 D; D.X=X-t.X; D.Y=Y-t.Y; D.A=A-t.A; return D; }
	inline Point3 operator  *(const Point3 &t) { Point3 D; D.X=X*t.X; D.Y=Y*t.Y; D.A=A*t.A; return D; }
	inline Point3 operator  *(const double &t) { Point3 D; D.X=X*t;   D.Y=Y*t;   D.A=A*t;   return D; }
	inline Point3 operator  /(const double &t) { Point3 D; D.X=X/t;   D.Y=Y/t;   D.A=A/t;   return D; }
	inline void   operator *=(const double &t) { X*=t; Y*=t; A*=t; }
	inline void   operator -=(const Point3 &t) { X-=t.X; Y-=t.Y; A-=t.A; }
	inline void   operator +=(const Point3 &t) { X+=t.X; Y+=t.Y; A+=t.A; }
	inline void   operator /=(const double &t) { X/=t; Y/=t; A/=t; }
	inline void   operator /=(const Point3 &t) { X/=t.X; Y/=t.Y; A/=t.A;}
	inline double Length(const Point3 &t){ return sqrt((X-t.X)*(X-t.X)+(Y-t.Y)*(Y-t.Y)+(A-t.A)*(A-t.A)); }
};
//---------------------------------------------------------------------------
template<typename Tp> struct Point4
{
	Tp X, Y, A, V;          //most of the time: x=X, y=Y, angle=A, velocity=V

	Point4(): X(0),Y(0),A(0),V(0) {}
	Point4(const Tp& t): X(t),Y(t),A(t),V(t) {}
	Point4(const Tp& x,const Tp& y,const Tp& t,const Tp& v): X(x),Y(y),A(t),V(v) {}

	inline void   operator  =(const Point4 &t) { X=t.X; Y=t.Y; A=t.A; V=t.V; }
	inline Point4 operator  -(const Point4 &t) { Point4 D; D.X=X-t.X; D.Y=Y-t.Y; D.A=A-t.A; D.V=V-t.V; return D; }
	inline Point4 operator  *(const double &t) { Point4 D; D.X=t*X; D.Y=t*Y; D.A=t*A; D.V=t*V; return D; }
	inline void   operator -=(const Point4 &t) { X-=t.X; Y-=t.Y; A-=t.A; V-=t.V; }
	inline void   operator /=(const double &t) { X/=t; Y/=t; A/=t; V/=t; }
	inline void   operator /=(const Point4 &t) { X/=t.X; Y/=t.Y; A/=t.A; V/=t.V; }
	inline double Length(const Point4 &t){ return sqrt((X-t.X)*(X-t.X)+(Y-t.Y)*(Y-t.Y)+(A-t.A)*(A-t.A)+(V-t.V)*(V-t.V)); }
};
//---------------------------------------------------------------------------
template<typename Tp> struct Point5
{
	Tp X, Y, A, V, S;          //most of the time: x=X, y=Y, angle=A, velocity=V, size=S

	Point5(): X(0),Y(0),A(0),V(0),S(0) {}
	Point5(const Tp& t): X(t),Y(t),A(t),V(t),S(t) {}
	Point5(const Tp& x,const Tp& y,const Tp& t,const Tp& v,const Tp& s): X(x),Y(y),A(t),V(v),S(s) {}

	inline void   operator  =(const Point5 &t) { X=t.X; Y=t.Y; A=t.A; V=t.V; S=t.S;}
	inline Point5 operator  -(const Point5 &t) { Point5 D; D.X=X-t.X; D.Y=Y-t.Y; D.A=A-t.A; D.V=V-t.V; D.S=S-t.S; return D; }
	inline Point5 operator  *(const double &t) { Point5 D; D.X=t*X; D.Y=t*Y; D.A=t*A; D.V=t*V; D.S=t*S; return D; }
	inline void   operator -=(const Point5 &t) { X-=t.X; Y-=t.Y; A-=t.A; V-=t.V; S-=t.S; }
	inline void   operator /=(const double &t) { X/=t; Y/=t; A/=t; V/=t; S/=t; }
	inline void   operator /=(const Point5 &t) { X/=t.X; Y/=t.Y; A/=t.A; V/=t.V; S/=t.S; }
};
//---------------------------------------------------------------------------
struct PoI                          ///< Place of Interest
{
    double        Speed;
    FlowType      Flow;
    DirectionType Direction;
    std::vector<cv::Point> Poly;

	inline void   operator  =(const PoI &t) {
	    Poly=t.Poly; Direction=t.Direction;
	    Flow=t.Flow; Speed=t.Speed;
    }
};
//---------------------------------------------------------------------------
typedef Point2<int>    IPoint;
typedef Point2<float>  FPoint;
typedef Point2<double> DPoint;
//---------------------------------------------------------------------------
struct TParaLine
{
//  Y=aX+b -> TParaLine 'A' stands for 'a' and 'B' for 'b'.
//  It is NOT a line from point 'A' to point 'B'
	DPoint A;
	DPoint B;

	inline void operator =(const TParaLine &a) { A=a.A; B=a.B; }

	inline void Get(const int t,int &X,int &Y){ X=int(A.X*t+B.X+0.5); Y=int(A.Y*t+B.Y+0.5);}

	inline void Get(const double t,double &X,double &Y){ X=A.X*t+B.X; Y=A.Y*t+B.Y;}

	inline void Get(const double t,DPoint &Pnt){ Pnt.X=A.X*t+B.X; Pnt.Y=A.Y*t+B.Y;}

	inline double GetT(const double X)
	{
		double t;

		if(A.X!=0.0) t=(X-B.X)/A.X;
        else         t=DBL_MAX;

		return t;
	}

	inline double GetY(const double X)
	{
		double Y,t;

		if(A.X!=0.0){ t=(X-B.X)/A.X; Y=A.Y*t+B.Y;	}
		else Y=DBL_MAX;

		return Y;
	}

	inline double GetX(const double Y)
	{
		double X,t;

		if(A.Y!=0.0){ t=(Y-B.Y)/A.Y; X=A.X*t+B.X;	}
		else X=DBL_MAX;

		return X;
	}

	inline void MakeLine(const DPoint &P1,const DPoint &P2){ B=P1; A=P1; A-=P2; }

	inline void Orthogonal(void)
	{
		double D;

		D=A.X; A.X=A.Y; A.Y=D;

		if(A.X!=0.0) A.X*=-1.0;
		else 		 A.Y*=-1.0;
	}

	inline void Normalize(void)
	{
		double D;

		D=sqrt(A.X*A.X+A.Y*A.Y);
		if(D>0.0){ A.X/=D; A.Y/=D; }
	}

	inline void Intersection(const TParaLine &a,DPoint &Pnt)  //Pnt is crossing of the paraline with a
	{
		double cx=B.X-a.B.X;
		double cy=B.Y-a.B.Y;
		double pr=(A.Y*a.A.X-A.X*a.A.Y);

		if(pr!=0.0){
			double t=(cx*a.A.Y-cy*a.A.X)/pr;
			Pnt.X=t*A.X+B.X; Pnt.Y=t*A.Y+B.Y;
		}
		else{ Pnt.X=DBL_MAX; Pnt.Y=DBL_MAX; }//lines are parallel
	}

	inline void Rotate(const double Angle) //+ clockwise angle in °
	{
      double An;

      if(A.X==0.0) An=90.0;
      else         An=180.0*atan(A.Y/A.X)/M_PI;

      An+=Angle;

      if(An==90.0){ A.X=0.0; A.Y=1.0; }
      else{ A.Y=tan(M_PI*(An/180.0)); A.X=1.0; }

      Normalize();
	}
};
//---------------------------------------------------------------------------
struct TLine
{
	double A;
	double B;

	inline TLine(void){ A=B=0.0; }
	inline TLine(const TLine &a) {  operator =(a); }

	inline void operator =(const double &a){A=a;   B=a;   }
	inline void operator =(const TLine &a) {A=a.A; B=a.B; }
	inline double GetY(const double &x){ return A*x+B; }
	inline double GetX(const double &y){ return (y-B)/A; }

	inline void MakeLine(const DPoint &P1,const DPoint &P2)
   {
      double dx=P1.X-P2.X;

      if(dx!=0.0){ A=(P1.Y-P2.Y)/dx; B=P1.Y-A*P1.X; }
      else{ A=DBL_MAX; B=DBL_MAX; }
   }

	inline void Orthogonal(const DPoint &P)      //perpendicular in P
	{
		if(A!=0.0){ A=-1.0/A; B=P.Y-A*P.X; }
		else{ A=DBL_MAX; B=DBL_MAX; }
	}

   inline void MakeParaLine(double X,TParaLine &Pl)
   {
      Pl.A.X=1.0; Pl.A.Y=A;
      Pl.B.X=X;   Pl.B.Y=A*X+B;
      Pl.Normalize();
   }

   inline void MakeOrthoParaLine(double X,TParaLine &Pl)
   {
      Pl.A.Y=-1.0; Pl.A.X=A;
      Pl.B.X=X;   Pl.B.Y=A*X+B;
      Pl.Normalize();
   }
};
//---------------------------------------------------------------------------
struct TQuadratic
{
	double A;
	double B;
	double C;

	inline TQuadratic(void){ A=B=C=0.0; }
	inline TQuadratic(const TQuadratic &a) {  operator =(a); }

	inline void operator =(const double &a)     {A=a;   B=a;   C=a;   }
	inline void operator =(const TQuadratic &a) {A=a.A; B=a.B; C=a.C; }
	inline double GetY(const double &x){ return x*(A*x+B)+C; }

	inline void MakeLine(const DPoint &P1,const DPoint &P2,const DPoint &P3)
   {
      double x1x=P1.X*P1.X;
      double x2x=P2.X*P2.X;
      double x3x=P3.X*P3.X;
      double dx1=P1.X-P2.X;
      double dy1=P1.Y-P2.Y;
      double dx3=P1.X-P3.X;
      double dy3=P1.Y-P3.Y;
      double d2x1=x1x-x2x;
      double d2x3=x1x-x3x;
      double dyd= dy1*dx3- dy3*dx1;
      double dxd=d2x1*dx3-d2x3*dx1;

      if(dxd!=0.0 && dx1!=0.0){ A=dyd/dxd; B=(dy1-A*d2x1)/dx1; C=P1.Y-x1x*A-P1.X*B; }
      else{ A=DBL_MAX; B=DBL_MAX; C=DBL_MAX; }
   }

   inline void MakeParaLine(double X,TParaLine &Pl)
   {
      Pl.B.X=X;    Pl.B.Y=GetY(X);
      Pl.A.X=-0.1; Pl.A.Y=Pl.B.Y-GetY(X+0.1);
      Pl.Normalize();
   }

   inline void MakeOrthoParaLine(double X,TParaLine &Pl)
   {
      Pl.B.X=X;    Pl.B.Y=GetY(X);
      Pl.A.Y=-0.1; Pl.A.X=GetY(X+0.1)-Pl.B.Y;
      Pl.Normalize();
   }
};
//---------------------------------------------------------------------------
struct TCubic
{
    double A;
    double B;
    double C;
    double D;

    inline TCubic(void){ A=B=C=D=0.0; }
    inline TCubic(const TCubic &a) {  operator =(a); }

    inline void operator =(const double &a) {A=a;   B=a;   C=a;   D=a;   }
    inline void operator =(const TCubic &a) {A=a.A; B=a.B; C=a.C; D=a.D; }
   inline void operator /=(const double &a) {A/=a; B/=a;  C/=a;  D/=a;  }
   inline TCubic operator +(const TCubic &a) const
   {
      TCubic Q;
      Q.A=A+a.A;
      Q.B=B+a.B;
      Q.C=C+a.C;
      Q.D=D+a.D;
      return Q;
   }
   inline TCubic operator -(const TCubic &a) const
   {
      TCubic Q;
      Q.A=A-a.A;
      Q.B=B-a.B;
      Q.C=C-a.C;
      Q.D=D-a.D;
      return Q;
   }

   inline double GetY(const double &x){ return x*(x*(A*x+B)+C)+D; }
   double Secant(const double Seed1,const double Seed2,const double e=1E-6)
   {
      int i=0;
      double y1,y2,x1;
      double x2=Seed1;
      double x3=Seed2;

      i=0; x1=x2; x2=x3;
      y1=x1*(x1*(x1*A+B)+C)+D;
      y2=x2*(x2*(x2*A+B)+C)+D;
      x3=x2-((x2-x1)/(y2-y1))*y2;

      while(fabs(x3-x2)>=e && x3!=0.0 && i<50){
         i++; x1=x2; x2=x3; y1=y2;
         y2=x2*(x2*(x2*A+B)+C)+D;
         x3=x2-((x2-x1)/(y2-y1))*y2;
      };

      return x3;
   };


   inline void MakeParaLine(double X,TParaLine &Pl)
   {
      Pl.B.X=X;    Pl.B.Y=GetY(X);
      Pl.A.X=-0.1; Pl.A.Y=Pl.B.Y-GetY(X+0.1);
      Pl.Normalize();
   }

   inline void MakeOrthoParaLine(double X,TParaLine &Pl)
   {
      Pl.B.X=X;    Pl.B.Y=GetY(X);
      Pl.A.Y=-0.1; Pl.A.X=GetY(X+0.1)-Pl.B.Y;
      Pl.Normalize();
   }

   inline void Intersection(TParaLine &a,DPoint &Pnt,const double Tolerance=1E-6)
   {
      TCubic Cb;
      TLine Ln;

      if(a.A.X==0.0){
         Pnt.X=a.B.X;
         Pnt.Y=GetY(Pnt.X);
      }
      else{
         Ln.A=a.A.Y/a.A.X;
         Ln.B=a.B.Y-Ln.A*a.B.X;
         Cb.A=A;
         Cb.B=B;
         Cb.C=C-Ln.A;
         Cb.D=D-Ln.B;
         Pnt.X=Cb.Secant(a.B.X-20.0,a.B.X+20.0);
         Pnt.Y=a.GetY(Pnt.X);
      }
   }
};
//---------------------------------------------------------------------------
#define AVERAGE 8           //depth of array
//---------------------------------------------------------------------------
template<class Tp> struct TMoveAverFixed
{
    Tp Ar[AVERAGE];
    int Pnt, Len, Fixed;

    TMoveAverFixed() {Pnt=Len=0; Fixed=30;}

    void Store(const Tp Value,const int Fx,const int Le)
    {
        Fixed=Fx; Len=Le;
        for(int i=0;i<AVERAGE;i++) Ar[i]=Value;
    }

    inline Tp Aver(void)
    {
        if(Len>0){
            Tp Sum=0.0;
            if(Len>AVERAGE){
                for(int i=0;i<AVERAGE;i++) Sum+=Ar[i];
                return Sum/((double)AVERAGE);
            }
            else{
                for(int i=0;i<Len;i++) Sum+=Ar[i];
                return Sum/((double)Len);
            }
        }
        else{
            Tp Zero=0.0;
            return Zero;
        }
    }

    inline void Add(const Tp &a)
    {
        if(Fixed==0){
            if(Len<AVERAGE){
                Ar[Pnt] = a;
                Pnt++; Pnt%=AVERAGE; Len++;
            }
            else{
                Ar[Pnt] = a;
                Pnt++; Pnt%=AVERAGE;
            }
        }
        else{
            if(Len<16){
                Ar[Pnt] = a;
                Pnt++; Pnt%=AVERAGE; Len++;
            }
            else{
                if(Len<Fixed){
                    double Fz=1.0-((double(Len-16))/(Fixed-16));
                    if(Fz>0.0 && Fz<=1.0){
                        Ar[Pnt]=a; Ar[Pnt]*=Fz;
                        Ar[Pnt]+=(Aver()*(1.0-Fz));
                        Pnt++; Pnt%=AVERAGE; Len++;
                    }
                }
                else{
                    if(Len<Fixed+4) Len++;      //additional increments for save() check
                }
            }
        }
    }
};
//---------------------------------------------------------------------------
template<class Tp> struct TLast4Aver
{
    Tp Ar[4];
    int Len, Pnt;

    TLast4Aver() {Len=0; Pnt=0;}

    inline void operator =(const TLast4Aver &a)
    {
        Len=a.Len; Pnt=a.Pnt;
        for(int i=0;i<Len;i++) Ar[i]=a.Ar[i];
    }

    inline void Add(const Tp &a)
    {
        if(Len<4) Ar[Len++]=a;
        else{
            Ar[Pnt++]=a;
            Pnt &= 0x03;        //MODULO 4
        }
    }

    inline Tp Aver(void)
    {
        if(Len>0){
            Tp Sum=0.0;
            for(int i=0;i<Len;i++) Sum+=Ar[i];
            return Sum/((double)Len);
        }
        else{
            Tp Zero=0.0;
            return Zero;
        }
    }
};
//---------------------------------------------------------------------------
template<class Tp> struct TAver
{
    Tp Aver;
    int Cnt;

    TAver() {Aver=0.0; Cnt=0;}

    inline void operator =(const TAver &a)
    {
        Aver=a.Aver; Cnt=a.Cnt;
    }

    inline void Add(const Tp &a)
    {
        Cnt++;
        double d=static_cast<double>(Cnt);
        Aver = (Aver*(d-1.0)+a)/d;
    }
};
//---------------------------------------------------------------------------
#endif
