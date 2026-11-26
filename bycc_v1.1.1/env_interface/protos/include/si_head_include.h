#ifndef __SI_HEAD_INCLUDE_H__
#define __SI_HEAD_INCLUDE_H__

#include<math.h>
#include<time.h>
//#include<winsock.h>
#ifdef _WIN32
#include <WINSOCK2.H>
#else
#include <arpa/inet.h>
#endif

#include<iostream>

#pragma comment(lib,"radar_simulation_e2d.lib")


#include "si_out.h"
#include "si_main.h"
#include <string.h>


#endif