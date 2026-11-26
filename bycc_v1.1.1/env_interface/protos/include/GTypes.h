// 数据类型定义
#ifndef __GTYPES_H_091031__
#define __GTYPES_H_091031__

#include <vector>
#include <string.h>
#include <map>
//#include "qglobal.h"

#define Q_DECL_EXPORT __declspec(dllexport)


// 二维点结构
struct GPoint2
{
	union
	{
		double Lng;			// 经度		
		double dLng;
		double X;
	};
	union
	{
		double Lat;			// 纬度
		double dLat;
		double Y;
	};
	GPoint2()
	{
		X = Y = 0;
		Lng = Lat = 0;
	}
	
	GPoint2(double lng, double lat)
	{
		Lng = lng;
		Lat = lat;		
	}
};

typedef GPoint2		GPoint2D;

// 扩展三维和空间点结构
struct GPointEx3
{
	long x, y, z;						// 物理坐标
	bool bValid;
	double X, Y, Z;						// 逻辑坐标
	union								// 地理坐标	
	{
		double Lng;
		double dLng;
	};
	union
	{
		double Lat;
		double dLat;
	};
	union
	{
		double Altitude;
		double dAlt;
	};
	GPointEx3()
	{
		x = y = z = 0;
		X = Y = Z = 0.0;
		Lng = Lat = Altitude = 0;
		bValid = false;
	}	
};

typedef GPointEx3 GPointEx;


#define GPoint3		GVector3
#define GPoint3D	GVector3


struct D3DXVECTOR3
{
	// 空间坐标
	union
	{
		float x;
		float X;
		float fLng;
	};
	union
	{
		float y;
		float Y;
		float fLat;
	};
	union
	{
		float z;
		float Z;
		float fAlt;
	};
	D3DXVECTOR3() {x= 0; y = 0; z = 0; }

	D3DXVECTOR3(float fx, float fy, float fz)
	{
		x = fx;
		y = fy;
		z = fz;
	};
	D3DXVECTOR3 operator * ( double ) const
	{
		return *this;//待实现
	}
};


/** \brief 3D向量定义
 */
struct GVector3
{
	// 空间坐标
	union
	{
		double x;
		double X;
		double dLng;
	};
	union
	{
		double y;
		double Y;
		double dLat;
	};
	union
	{
		double z;
		double Z;
		double dAlt;
	};
	GVector3() {x= 0; y = 0; z = 0; }

	GVector3(double dx, double dy, double dz)
	{
		x = dx;
		y = dy;
		z = dz;
	}
};


// 二维顶点结构
struct GVector2
{
	double x;
	double y;
	GVector2()
	{
		x = 0;
		y = 0;
	}
	GVector2(double dx, double dy)
	{
		x = dx;
		y = dy;
	}
};

typedef struct _D3DVIEWPORT9 {
	int       X;
	int       Y;            /* Viewport Top left */
	int       Width;
	int       Height;       /* Viewport Dimensions */
	float       MinZ;         /* Min/max of clip Volume */
	float       MaxZ;
} D3DVIEWPORT9;

/** \brief 矩阵定义
 */
struct D3DXMATRIX
{
	union
	{
		struct 
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[4][4];	
	};

	D3DXMATRIX& operator *= ( const D3DXMATRIX& )
	{
		return *this;//待实现
	}
};

struct GMatrix
{
	union
	{
		struct 
		{
			double _11, _12, _13, _14;
			double _21, _22, _23, _24;
			double _31, _32, _33, _34;
			double _41, _42, _43, _44;
		};
		double m[4][4];	
	};
};


/** \brief 4D向量定义
 */
struct GVector4
{
	double x, y, z, w;
	GVector4(){x = 0; y = 0; z = 0; w = 0; }
	GVector4(double dx, double dy, double dz, double dw)
	{
		x = dx;
		y = dy;
		z = dz;
		w = dw;
	}
};


/** \brief 视区定义
 */
struct GViewport
{
	int X, Y; 
	int Width, Height;
	double MinZ, MaxZ;
};


/** \brief 平面
 */
struct GPlane
{
	double a, b, c, d;
	GPlane() {a = 0; b = 0; c = 0; d = 0;}
	GPlane(double da, double db, double dc, double dd)
	{
		a = da;
		b = db;
		c = dc;
		d = dd;
	}
};


/** \brief 向量
 */
struct GVector
{
	// 空间坐标
	double dLng;
	double dLat;
	double dAlt;
	double X, Y, Z;
	// 欧拉角
	union
	{
		double dYaw; 
		double dHeading;
	};
	union
	{
		double dPitch;
	};
	union
	{
		double dRoll;
		double dBank;
	};
	double T;					// 到达该点的时刻，秒
	int iIndex;
	double dV;                  //速度分量
	char Id[32];
	
	GVector()
	{
		Initialize();
	}

	void Initialize()
	{
		memset(this, 0, sizeof(GVector));
	}
};


//#define GDataID					qint64				// ID	（QT版）
#define GDataID						long				// ID	（标准C++版）20180901 wcr 更替

// 类型定义
typedef GDataID		GINDEX_T;
typedef short		GSEAT_T;


// 互斥锁
// class GAutoLock;
// class GLock
// {
// 	friend class GAutoLock;
// protected:
// 	CRITICAL_SECTION m_sec;
// 	QMutex m_mutex;
// private:
// 	GLock(const GLock &);
// 	GLock & operator=(const GLock &);
// 
// public:
// 	GLock()
// 	{
// 		::InitializeCriticalSectionAndSpinCount(&m_sec, 1000);
// 	}
// 	~GLock()
// 	{
// 		::DeleteCriticalSection(&m_sec);
// 	}
// 	void Lock()
// 	{
// 		::EnterCriticalSection(&m_sec);
// 	}
// 	void Unlock()
// 	{
// 		::LeaveCriticalSection(&m_sec);
// 	}
// };
// 
// 
// // 自动互斥锁
// class GAutoLock
// {
// 	LPCRITICAL_SECTION m_lpsec;
// 	GLock *m_pLock;
// private:
// 	GAutoLock(const GAutoLock &);
// 	GAutoLock & operator=(const GAutoLock &);
// 
// public:
// 	GAutoLock(GLock &Lock)
// 	{		
// 		m_pLock = &Lock;
// 		m_pLock->Lock();
// 		m_lpsec = NULL;
// 	}
// 	GAutoLock(LPCRITICAL_SECTION lpsec)
// 	{		
// 		m_lpsec = lpsec;
// 		::DeleteCriticalSection(m_lpsec);
// 		m_pLock = NULL;		
// 	}
// 	~GAutoLock()
// 	{
// 		if (m_pLock != NULL)
// 		{
// 			m_pLock->Unlock();
// 		}
// 		if (m_lpsec != NULL)
// 		{
// 			::LeaveCriticalSection(m_lpsec);
// 		}
// 	}
// };

struct GVectorEx
{
	// 空间坐标
	double dLng;
	double dLat;
	double dAlt;
	double T;					// 到达该点的时刻，秒
	float dV;                  //速度分量

	// 欧拉角
	union
	{
		float dYaw; 
		float dHeading;
	};
	union
	{
		float dPitch;
	};
	union
	{
		float dRoll;
		float dBank;
	};

	GVectorEx()
	{
		Initialize();
	}

	void Initialize()
	{
		//qMemSet(this, 0, sizeof(GVectorEx));
		memset(this, 0, sizeof(GVectorEx));
	}
};
#endif // __GTYPES_H_091031__