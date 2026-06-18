/**
 * ParkingLot_Search.cpp - 停车场查找算法实现
 * 停车场管理系统
 */

#include "ParkingLot.h"
#include <iostream>

using namespace std;

// 功能8：折半查找（递归算法）
void ParkingLot::binarySearchRecursive() {
    if (size == 0) {
        cout << "停车场为空，无法查找。" << endl;
        return;
    }

    // 提示需要先排序
    cout << "注意：折半查找需要先对车牌号进行排序。" << endl;
    cout << "是否先进行排序？(1-是, 0-否): ";
    int sortChoice;
    cin >> sortChoice;
    if (sortChoice == 1) {
        quickSortHelper(0, size - 1);
        cout << "排序完成！" << endl;
    }

    string target;
    cout << "请输入要查找的车牌号: ";
    cin >> target;

    // 调用递归查找
    int result = binarySearchRecursiveHelper(target, 0, size - 1);
    
    if (result != -1) {
        cout << "\n========== 查找成功（递归算法）==========" << endl;
        cout << "车位编号: " << (result + 1) << endl;
        cout << "车牌号: " << vehicles[result].plateNumber << endl;
        cout << "进场时间: " << vehicles[result].entryTime << endl;
        cout << "==========================================" << endl;
    } else {
        cout << "未找到车牌号为 " << target << " 的车辆。" << endl;
    }
}

// 折半查找递归辅助函数
int ParkingLot::binarySearchRecursiveHelper(const string& target, int low, int high) {
    // 递归终止条件
    if (low > high) {
        return -1;
    }

    int mid = (low + high) / 2;

    if (vehicles[mid].plateNumber == target) {
        return mid;  // 找到目标
    } else if (vehicles[mid].plateNumber > target) {
        return binarySearchRecursiveHelper(target, low, mid - 1);  // 在左半部分查找
    } else {
        return binarySearchRecursiveHelper(target, mid + 1, high);  // 在右半部分查找
    }
}

// 功能9：折半查找（非递归算法）
void ParkingLot::binarySearchIterative() {
    if (size == 0) {
        cout << "停车场为空，无法查找。" << endl;
        return;
    }

    // 提示需要先排序
    cout << "注意：折半查找需要先对车牌号进行排序。" << endl;
    cout << "是否先进行排序？(1-是, 0-否): ";
    int sortChoice;
    cin >> sortChoice;
    if (sortChoice == 1) {
        quickSortHelper(0, size - 1);
        cout << "排序完成！" << endl;
    }

    string target;
    cout << "请输入要查找的车牌号: ";
    cin >> target;

    // 非递归折半查找
    int low = 0, high = size - 1;
    int result = -1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (vehicles[mid].plateNumber == target) {
            result = mid;
            break;
        } else if (vehicles[mid].plateNumber > target) {
            high = mid - 1;  // 在左半部分查找
        } else {
            low = mid + 1;   // 在右半部分查找
        }
    }

    if (result != -1) {
        cout << "\n========== 查找成功（非递归算法）==========" << endl;
        cout << "车位编号: " << (result + 1) << endl;
        cout << "车牌号: " << vehicles[result].plateNumber << endl;
        cout << "进场时间: " << vehicles[result].entryTime << endl;
        cout << "============================================" << endl;
    } else {
        cout << "未找到车牌号为 " << target << " 的车辆。" << endl;
    }
}

// 添加测试数据
void ParkingLot::addTestData() {
    if (size + 5 > capacity) {
        cout << "容量不足，无法添加测试数据。" << endl;
        return;
    }

    // 添加5条测试数据，模拟不同时间入场
    string plates[] = {"京A12345", "沪B67890", "粤C11111", "苏D22222", "浙E33333"};
    // 模拟不同的入场时间（当前时间往前推）
    int minutesAgo[] = {120, 90, 60, 30, 10};  // 分别是2小时、1.5小时、1小时、30分钟、10分钟前

    time_t now = getCurrentTimestamp();
    
    for (int i = 0; i < 5; i++) {
        vehicles[size].plateNumber = plates[i];
        vehicles[size].entryTimestamp = now - (minutesAgo[i] * 60);  // 转换为秒
        
        // 生成对应的时间字符串（北京时间）
        time_t beijingTime = vehicles[size].entryTimestamp + (8 * 3600);
        tm* ltm = gmtime(&beijingTime);
        char buffer[20];
        sprintf(buffer, "%04d-%02d-%02d %02d:%02d",
                1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday,
                ltm->tm_hour, ltm->tm_min);
        vehicles[size].entryTime = string(buffer);
        
        size++;
    }

    cout << "已添加5条测试数据！" << endl;
    cout << "- 京A12345: 2小时前入场" << endl;
    cout << "- 沪B67890: 1.5小时前入场" << endl;
    cout << "- 粤C11111: 1小时前入场" << endl;
    cout << "- 苏D22222: 30分钟前入场" << endl;
    cout << "- 浙E33333: 10分钟前入场" << endl;
}
