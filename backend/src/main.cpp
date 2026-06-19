/**
 * main.cpp - 停车场管理系统主程序
 * 基于顺序表实现的车辆信息管理
 * 支持 Windows / Linux / macOS 跨平台编译
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include "ParkingLot.h"

using namespace std;

// 从环境变量读取整型配置，缺省或非法值时返回默认值
static int getEnvInt(const char* name, int defaultValue) {
    const char* value = std::getenv(name);
    if (value == nullptr || *value == '\0') {
        return defaultValue;
    }
    try {
        int parsed = std::stoi(value);
        if (parsed <= 0) return defaultValue;
        return parsed;
    } catch (...) {
        return defaultValue;
    }
}

// 从环境变量读取浮点型配置，缺省或非法值时返回默认值
static double getEnvDouble(const char* name, double defaultValue) {
    const char* value = std::getenv(name);
    if (value == nullptr || *value == '\0') {
        return defaultValue;
    }
    try {
        double parsed = std::stod(value);
        if (parsed < 0.0) return defaultValue;
        return parsed;
    } catch (...) {
        return defaultValue;
    }
}

// 跨平台清屏
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// 跨平台暂停
void pauseScreen() {
    cout << "\n按回车键继续...";
    cin.ignore();
    cin.get();
}

// 显示菜单
void showMenu() {
    cout << "\n============================================" << endl;
    cout << "          停 车 场 管 理 系 统              " << endl;
    cout << "============================================" << endl;
    cout << "  1. 批量输入车辆信息" << endl;
    cout << "  2. 显示所有车辆信息" << endl;
    cout << "  3. 在指定位置插入车辆" << endl;
    cout << "  4. 删除指定位置的车辆" << endl;
    cout << "  5. 统计车辆数量" << endl;
    cout << "  6. 插入排序（直接/折半）" << endl;
    cout << "  7. 快速排序" << endl;
    cout << "  8. 折半查找（递归）" << endl;
    cout << "  9. 折半查找（非递归）" << endl;
    cout << "  0. 添加测试数据" << endl;
    cout << "  q. 退出系统" << endl;
    cout << "============================================" << endl;
    cout << "请选择操作: ";
}

int main() {
    // 业务参数支持通过环境变量覆盖，便于在容器/CI 中无需改代码即可调整
    int capacity = getEnvInt("PARKING_CAPACITY", 100);
    double feePerHour = getEnvDouble("PARKING_FEE_PER_HOUR", 5.0);

    ParkingLot parkingLot(capacity, feePerHour);
    char choice;

    while (true) {
        showMenu();
        cin >> choice;

        switch (choice) {
            case '1':
                parkingLot.inputVehicles();
                break;
            case '2':
                parkingLot.displayAll();
                break;
            case '3':
                parkingLot.insertAt();
                break;
            case '4':
                parkingLot.deleteAt();
                break;
            case '5':
                parkingLot.countVehicles();
                break;
            case '6':
                parkingLot.insertionSort();
                break;
            case '7':
                parkingLot.quickSort();
                break;
            case '8':
                parkingLot.binarySearchRecursive();
                break;
            case '9':
                parkingLot.binarySearchIterative();
                break;
            case '0':
                parkingLot.addTestData();
                break;
            case 'q':
            case 'Q':
                cout << "感谢使用停车场管理系统，再见！" << endl;
                return 0;
            default:
                cout << "无效选择，请重新输入！" << endl;
        }

        pauseScreen();
        clearScreen();
    }

    return 0;
}
