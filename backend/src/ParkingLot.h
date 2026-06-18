/**
 * ParkingLot.h - 停车场顺序表类定义
 * 停车场管理系统
 */

#ifndef PARKINGLOT_H
#define PARKINGLOT_H

#include "Vehicle.h"
#include <string>
#include <ctime>

using namespace std;

// 停车场顺序表类
class ParkingLot {
private:
    Vehicle* vehicles;     // 车辆数组
    int capacity;          // 最大容量
    int size;              // 当前车辆数
    double feePerHour;     // 每小时收费标准

    // 私有辅助函数
    void quickSortHelper(int low, int high);
    int partition(int low, int high);
    int binarySearchRecursiveHelper(const string& target, int low, int high);

public:
    // 构造函数和析构函数
    ParkingLot(int cap = 100, double fee = 5.0);
    ~ParkingLot();

    // 工具函数
    string getCurrentTime();           // 获取当前时间字符串
    time_t getCurrentTimestamp();      // 获取当前时间戳
    int getParkingDuration(time_t entryTime);  // 计算停车时长（分钟）
    double calculateFee(int duration); // 计算费用

    // 功能1：批量输入车辆信息
    void inputVehicles();

    // 功能2：显示所有车辆信息
    void displayAll();

    // 功能3：在指定位置插入车辆
    void insertAt();

    // 功能4：删除指定位置的车辆
    void deleteAt();

    // 功能5：统计车辆数量
    void countVehicles();

    // 功能6：插入排序（直接/折半）
    void insertionSort();

    // 功能7：快速排序
    void quickSort();

    // 功能8：折半查找（递归）
    void binarySearchRecursive();

    // 功能9：折半查找（非递归）
    void binarySearchIterative();

    // 添加测试数据
    void addTestData();
};

#endif // PARKINGLOT_H
