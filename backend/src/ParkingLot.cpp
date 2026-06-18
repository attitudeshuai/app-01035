/**
 * ParkingLot.cpp - 停车场顺序表类实现
 * 停车场管理系统
 */

#include "ParkingLot.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <cstring>

using namespace std;

// 北京时区偏移（UTC+8 = 8小时 = 28800秒）
const int BEIJING_OFFSET = 8 * 3600;

// 构造函数
ParkingLot::ParkingLot(int cap, double fee) {
    capacity = cap;
    size = 0;
    feePerHour = fee;
    vehicles = new Vehicle[capacity];
}

// 析构函数
ParkingLot::~ParkingLot() {
    delete[] vehicles;
}

// 获取当前时间戳
time_t ParkingLot::getCurrentTimestamp() {
    return time(0);
}

// 获取当前时间字符串（北京时间）
string ParkingLot::getCurrentTime() {
    time_t now = time(0);
    // 转换为北京时间
    time_t beijingTime = now + BEIJING_OFFSET;
    tm* ltm = gmtime(&beijingTime);
    
    char buffer[20];
    sprintf(buffer, "%04d-%02d-%02d %02d:%02d",
            1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday,
            ltm->tm_hour, ltm->tm_min);
    return string(buffer);
}

// 计算停车时长（分钟）- 动态计算
int ParkingLot::getParkingDuration(time_t entryTime) {
    time_t now = getCurrentTimestamp();
    int duration = (int)difftime(now, entryTime) / 60;  // 转换为分钟
    return duration < 0 ? 0 : duration;
}

// 计算费用
double ParkingLot::calculateFee(int duration) {
    return (duration / 60.0) * feePerHour;
}

// 功能1：指定车辆数，逐个输入车辆信息
void ParkingLot::inputVehicles() {
    int n;
    cout << "请输入要添加的车辆数量: ";
    cin >> n;

    if (size + n > capacity) {
        cout << "错误：停车场容量不足！当前剩余车位: " << (capacity - size) << endl;
        return;
    }

    for (int i = 0; i < n; i++) {
        cout << "\n--- 输入第 " << (i + 1) << " 辆车的信息 ---" << endl;
        
        cout << "车牌号: ";
        cin >> vehicles[size].plateNumber;
        
        // 记录进场时间
        vehicles[size].entryTimestamp = getCurrentTimestamp();
        vehicles[size].entryTime = getCurrentTime();
        
        cout << "进场时间已自动记录: " << vehicles[size].entryTime << " (北京时间)" << endl;
        
        size++;
        cout << "车辆添加成功！当前停车位编号: " << size << endl;
    }
}

// 功能2：显示所有车辆信息（动态计算时长和费用）
void ParkingLot::displayAll() {
    if (size == 0) {
        cout << "停车场为空，没有车辆信息。" << endl;
        return;
    }

    cout << "\n======================= 停车场车辆信息表 =======================" << endl;
    cout << "当前时间: " << getCurrentTime() << " (北京时间)" << endl;
    cout << "----------------------------------------------------------------" << endl;
    cout << left << setw(6) << "车位" 
         << setw(12) << "车牌号" 
         << setw(18) << "进场时间" 
         << setw(12) << "停车时长" 
         << setw(12) << "应缴费用" << endl;
    cout << "----------------------------------------------------------------" << endl;

    for (int i = 0; i < size; i++) {
        // 动态计算停车时长和费用
        int duration = getParkingDuration(vehicles[i].entryTimestamp);
        double fee = calculateFee(duration);
        
        cout << left << setw(6) << (i + 1)
             << setw(12) << vehicles[i].plateNumber
             << setw(18) << vehicles[i].entryTime
             << setw(12) << (to_string(duration) + "分钟")
             << fixed << setprecision(2) << fee << "元" << endl;
    }
    cout << "================================================================" << endl;
    cout << "共计 " << size << " 辆车" << endl;
}

// 功能3：在指定位置插入车辆
void ParkingLot::insertAt() {
    if (size >= capacity) {
        cout << "错误：停车场已满！" << endl;
        return;
    }

    int pos;
    cout << "请输入要插入的位置 (1-" << (size + 1) << "): ";
    cin >> pos;

    if (pos < 1 || pos > size + 1) {
        cout << "错误：位置无效！" << endl;
        return;
    }

    Vehicle newVehicle;
    cout << "车牌号: ";
    cin >> newVehicle.plateNumber;
    
    // 记录进场时间
    newVehicle.entryTimestamp = getCurrentTimestamp();
    newVehicle.entryTime = getCurrentTime();
    
    cout << "进场时间已自动记录: " << newVehicle.entryTime << " (北京时间)" << endl;

    // 后移元素
    for (int i = size; i >= pos; i--) {
        vehicles[i] = vehicles[i - 1];
    }
    vehicles[pos - 1] = newVehicle;
    size++;

    cout << "车辆插入成功！" << endl;
}

// 功能4：删除指定位置的车辆（显示动态计算的时长和费用）
void ParkingLot::deleteAt() {
    if (size == 0) {
        cout << "停车场为空，无法删除。" << endl;
        return;
    }

    int pos;
    cout << "请输入要删除的车位编号 (1-" << size << "): ";
    cin >> pos;

    if (pos < 1 || pos > size) {
        cout << "错误：位置无效！" << endl;
        return;
    }

    Vehicle deleted = vehicles[pos - 1];
    
    // 动态计算停车时长和费用
    int duration = getParkingDuration(deleted.entryTimestamp);
    double fee = calculateFee(duration);
    
    // 前移元素
    for (int i = pos - 1; i < size - 1; i++) {
        vehicles[i] = vehicles[i + 1];
    }
    size--;

    cout << "\n========== 删除车辆信息 ==========" << endl;
    cout << "车牌号: " << deleted.plateNumber << endl;
    cout << "进场时间: " << deleted.entryTime << endl;
    cout << "离场时间: " << getCurrentTime() << " (北京时间)" << endl;
    cout << "停车时长: " << duration << " 分钟" << endl;
    cout << "应缴费用: " << fixed << setprecision(2) << fee << " 元" << endl;
    cout << "==================================" << endl;
}

// 功能5：统计车辆数
void ParkingLot::countVehicles() {
    cout << "当前停车场共有 " << size << " 辆车" << endl;
    cout << "剩余车位: " << (capacity - size) << " 个" << endl;
}
