#include <set>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> source_arr;
    for(int i=0; i<10; ++i)
        source_arr.push_back(i);
    std::set<int> blocks_set(source_arr.begin(), source_arr.end());
    //std::copy(, blocks_set.end());
    double angle_in_radians = 1.0;  // 以弧度为单位的角度
    constexpr const double PI = 3.14159265358979323846;
    double sine_value = sin(PI /2);  // 计算正弦值
    std::cout << "The sine of " << angle_in_radians << " radians is " << sine_value << std::endl;
    int step = 10;
    double sum_d = 0.;
    for (int cur_step = 0; cur_step < step; ++cur_step) {
        // set deform_grid, 设置子步的形变量
        //double scale_factor = 1.0 / step;  // 均匀变化
        constexpr const double PI = 3.14159265358979323846;
        const double x_interval = PI / 2 / step;
        double scale_factor = sin(x_interval * (cur_step + 1)) - sin(x_interval * cur_step);
        std::cout << "x_interval: " << x_interval << std::endl;
        sum_d += scale_factor;
        std::cout << "scale_factor: " << scale_factor <<", sum_d: "<< sum_d << std::endl;

    }
}