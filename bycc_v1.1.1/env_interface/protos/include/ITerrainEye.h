#ifndef  _TERRAIN_EYE_H_
#define  _TERRAIN_EYE_H_

struct ZPoint3
{
	double dLng;
	double dLat;
	double dAlt;
	ZPoint3() {dLng= 0; dLat = 0; dAlt = 0; }

	ZPoint3(double dx, double dy, double dz)
	{
		dLng = dx;
		dLat = dy;
		dAlt = dz;
	}
};

bool MyGetVisibleDot(double Lng1, double Lat1, double Altitude, double Lng2, double Lat2, double Altitude2,
				   ZPoint3 * pVisibleDot = NULL);// 根据剖面，计算实际可视剖面 计算Lng1,Lat1到Lng2,Lat2的可视点




#endif
