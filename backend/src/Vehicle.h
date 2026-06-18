/**
 * Vehicle.h - 车辆信息结构体定义
 * 停车场管理系统
 */

#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <ctime>

using namespace std;

// 车辆信息结构体
struct Vehicle {
    string plateNumber;    // 车牌号
    string entryTime;      // 进场时间（字符串格式）
    time_t entryTimestamp; // 进场时间戳（用于计算时长）
    
    Vehicle() : entryTimestamp(0) {}
};

#endif // VEHICLE_H
