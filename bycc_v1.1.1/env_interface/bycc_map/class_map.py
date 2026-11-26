from env_interface.data_types import (LabelInfo, ProtectUnit, GpsJammer, XKuJammer, Rcl670Jammer,
                                      WarningRadar, H9TtrRadar, H9Launcher, Aircraft, Rcz901Jammer,
                                      RadReconPara, RadReconDetectPara, RadarJammer, RadarPara)


CLASS_MAP = {
    "ProtectUnit": ProtectUnit,
    "GpsJammer": GpsJammer,
    "WarningRadar": WarningRadar,
    "H9TtrRadar": H9TtrRadar,
    "H9Launcher": H9Launcher,
    "Rcz901Jammer": Rcz901Jammer,
    "XKuJammer": XKuJammer,
    "Rcl670Jammer": Rcl670Jammer,
    "Aircraft": Aircraft,

    "ReconPara": RadReconPara,
    "RadarJamPara": RadarJammer,
    "RadReconDetectPara": RadReconDetectPara,
    "RadarPara": RadarPara,
    "LabelInfo": LabelInfo,

}

if __name__ == '__main__':
    print(CLASS_MAP)
