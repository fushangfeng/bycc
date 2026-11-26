import math as mh


class CoordinationTransfer:
    def __init__(self):
        self.dEarthRadius = 6371000.0  # /*m*/
        self.BJ54_Aaxis = 6378245  # /*m*/
        self.BJ54_Baxis = 6356963  # /*m*/   //北京54坐标系
        self.XA80_Aaxis = 6378140  # //*m*/
        self.XA80_Baxis = 6356755  # //*m*/		//西安80坐标系
        self.WGS84_Aaxis = 6378137  # /*m*/
        self.WGS84_Baxis = 6356752.314  # /*m*/;//WGS84坐标系
        self.const_PI = mh.acos(-1.0)

    def WG84LBH2XYZ(self, Lon, Lat, Height, itype=3):
        Aaxis, Baxis = 0.0, 0.0
        if itype == 1:
            Aaxis = self.BJ54_Aaxis
            Baxis = self.BJ54_Baxis
        elif itype == 2:
            Aaxis = self.XA80_Aaxis
            Baxis = self.XA80_Baxis
        elif itype == 3:
            Aaxis = self.WGS84_Aaxis
            Baxis = self.WGS84_Baxis
        e2 = (Aaxis * Aaxis - Baxis * Baxis) / Aaxis / Aaxis
        N = Aaxis / mh.sqrt(1 - e2 * mh.sin(Lat / 180.0 * self.const_PI) * mh.sin(Lat / 180.0 * self.const_PI))
        X = (N + Height) * mh.cos(Lat / 180.0 * self.const_PI) * mh.cos(Lon / 180.0 * self.const_PI);
        Y = (N + Height) * mh.cos(Lat / 180.0 * self.const_PI) * mh.sin(Lon / 180.0 * self.const_PI);
        Z = (N * (1 - e2) + Height) * mh.sin(Lat / 180.0 * self.const_PI);
        return X, Y, Z

    def WG84XYZ2NEU(self, dX, dY, dZ, dLon0, dLat0, dH0):
        dx0, dy0, dz0 = self.WG84LBH2XYZ(dLon0, dLat0, dH0)
        dE = -(dX - dx0) * mh.sin(dLon0 / 180.0 * self.const_PI) + (dY - dy0) * mh.cos(dLon0 / 180.0 * self.const_PI)
        dN = -(dX - dx0) * mh.sin(dLat0 / 180.0 * self.const_PI) * mh.cos(dLon0 / 180.0 * self.const_PI) - (
                    dY - dy0) * mh.sin(dLat0 / 180.0 * self.const_PI) * mh.sin(dLon0 / 180.0 * self.const_PI) + (
                         dZ - dz0) * mh.cos(dLat0 / 180.0 * self.const_PI)
        dU = (dX - dx0) * mh.cos(dLat0 / 180.0 * self.const_PI) * mh.cos(dLon0 / 180.0 * self.const_PI) + (
                    dY - dy0) * mh.cos(dLat0 / 180.0 * self.const_PI) * mh.sin(dLon0 / 180.0 * self.const_PI) + (
                         dZ - dz0) * mh.sin(dLat0 / 180.0 * self.const_PI)
        return dN, dE, dU

    def TransforLBH2AzEl(self, dLon, dLat, dHeight, dLon1, dLat1, dHeight1):
        dx1, dy1, dz1 = self.WG84LBH2XYZ(dLon1, dLat1, dHeight1)
        dN, dE, dU = self.WG84XYZ2NEU(dx1, dy1, dz1, dLon, dLat, dHeight)
        dDetax = dN
        dDetay = dE
        dDetaz = dU
        dEl = mh.atan2(dU, mh.sqrt(dN * dN + dE * dE)) / self.const_PI * 180.0
        dAz = mh.atan2(dDetay, dDetax) / self.const_PI * 180.0
        dDis = mh.sqrt(dDetax * dDetax + dDetay * dDetay + dDetaz * dDetaz)
        return dAz, dEl, dDis