def Get_EquipID(info_manager):
    ReconID = JammerID = -1
    for i1 in range(len(info_manager.raw_obs.extra_info_dict['obs']['data']['reconGetPara'])):
        if info_manager.raw_obs.extra_info_dict['obs']['data']['reconGetPara'][i1]['EquipmentType'] == 'X_KU_JAMMER':
            ReconID = info_manager.raw_obs.extra_info_dict['obs']['data']['reconGetPara'][i1]['ReconID']
            break

    for i1 in range(len(info_manager.raw_obs.extra_info_dict['obs']['data']['jamGetPara'])):
        if info_manager.raw_obs.extra_info_dict['obs']['data']['jamGetPara'][i1]['EquipmentType'] == 'X_KU_JAMMER':
            JammerID = info_manager.raw_obs.extra_info_dict['obs']['data']['jamGetPara'][i1]['JammerID']
            break

    return JammerID if JammerID else ReconID
