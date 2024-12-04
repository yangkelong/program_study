#include <iostream>
#include "mylib.h"
#include <array>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <string>

template<typename T> class Blob {
public:
    T var;
    Blob(T) {

    }

};




void print(const std::string file_name, bool clear, bool tag = false) {
    std::cout << file_name << std::endl;
}

void print(const std::string file_path, const std::string file_name, bool tag = false) {
    std::cout << file_path+file_name << std::endl;
}


//void print(const std::string file_path, const std::string file_name, bool clear, bool tag = false) {
//    std::cout << "????????????" << std::endl;
//    if (!file_path.empty()) {
//        print(file_path + file_name, false);
//    }
//}


struct Point {
    int vertex_idx;
    int block_idx;
    Point(int a, int b) : vertex_idx(a), block_idx(b) {};
    bool operator<(const Point& rf) const{
        if (block_idx < rf.block_idx)
            return true;
        else if(block_idx > rf.block_idx)
            return false;
        return vertex_idx < rf.vertex_idx;
    }

    friend std::ostream& operator<< (std::ostream& cout, const Point &p);
 
};

std::ostream& operator<<(std::ostream& cout, const Point &p) {
    std::cout << "(" << p.block_idx << ", " << p.vertex_idx << ")" << std::endl;
    return cout;
}

size_t pointHasher(const Point& point) {
    return std::hash<int>()(point.block_idx) ^
        std::hash<int>()(point.vertex_idx);
}
bool pointEqOp(const Point& lf, const Point& rf) {
    if (lf.block_idx == rf.block_idx && lf.vertex_idx == rf.vertex_idx)
        return true;
    return false;
}

bool cmpPoint(const Point& lf, const Point& rf) {
    if (lf.block_idx < rf.block_idx)
        return true;
    else if (lf.block_idx > rf.block_idx)
        return false;
    return lf.vertex_idx < rf.vertex_idx;
}
#define TAB_SPACE 90
using PointUnorderedSet = std::unordered_set<Point, decltype(pointHasher)*, decltype(pointEqOp)*>;
PointUnorderedSet pointUnorderedSet(10, pointHasher, pointEqOp);

using PointSet = std::set<Point>;
using PointSet1 = std::set<Point, decltype(cmpPoint)*>;
PointSet pointSet;
PointSet1 pointSet1(cmpPoint);
PointSet pointSet2;

int main(){
    std::string file_path = "/";
    print(file_path, std::string("h.txt"), false);

    std::cout<<"hello world!"<<"\n";
	foo();
    std::array<int, 3> arr = {0,0,0};
    std::vector<std::array<int, 3>> dd;
    for (int i = 0; i < 9; ++i) {
        dd.push_back({ 0, i, 0 });
    }
    std::vector<std::array<int, 3>> ddd(dd.size());
    std::copy(dd.begin(), dd.end(), ddd.begin());
    for (int i = 0; i < 9; ++i) {
        std::cout << ddd[i][1] << std::endl;
    }

    std::unordered_set<int> set1;
    std::set<int> set2;
    int n = 9;
    for (int i = 0; i < n; ++i) {
        set2.insert(n-i);
        set1.insert(n - i);
    }
    std::cout << "Max value in the vector is " << *std::max_element(set1.begin(), set1.end()) << std::endl;
    for (const auto &iter: set1) {
        std::cout << iter << std::endl;
    }
    for (const auto& iter : set2) {
        std::cout << iter << std::endl;
    }
    pointSet.insert(Point(10, 10));
    pointSet.insert(Point(10, 9));
    pointSet.insert(Point(10, 11));
    pointSet.insert(Point(9, 10));
    pointSet.insert(Point(11, 10));
    pointSet.insert(Point(10, 10));
    pointSet.emplace(100, 100);

    for (const Point& p : pointSet) {
        std::cout << p;
    }
    Point p(1,1);
    Point &p_ref = p;
    pointSet.insert(p_ref);
    p.vertex_idx = 100;
    p.block_idx = 100;
    std::cout << *pointSet.begin();
    pointSet1.insert(Point(10, 10));
    pointSet2.insert(Point(999, 999));
    std::cout << "after swap" << std::endl;
    pointSet.swap(pointSet2);
    //pointSet.swap(pointSet1);
    for (auto& p : pointSet) {
        std::cout << p;
    }

    const Point point1(10, 10);
    std::vector<const Point*> points_ptr;
    points_ptr.push_back(&point1);
    int a{ 2 }, b{ 3 }, c{5};
    c -= a + b;
    std::cout << c << std::endl;

    std::vector<Point> points1;
    points1.push_back(Point(11, 10));
    points1.push_back(Point(11, 10));
    points1.push_back(Point(11, 10));
    Point* arrrrr[2] = { &(points1[0]),  &(points1[1]) };

    using arr3r = std::array<double, 3>;
    std::vector<arr3r> vec3r;
    //vec3r.push_back(arr3r(1., 1., 1.));
    vec3r.push_back({1., 1., 1.});
    int aa = 5;
    const int* a_ptr = &a;
    const double* db_ptr = reinterpret_cast<const double*>(a_ptr);

    int a_val{5}, b_val{2};
    std::cout << a_val/b_val << std::endl;

    int offset2[2];
    int face_orient = 1;
    for (int i = 0, m = 0; i < 3; ++i) {
        if (i == face_orient) continue;
        offset2[m++] = i;
        //offset2[++m] = i;
        //m += 1;
    }
    for (int i = 0; i < 2; ++i) {
        std::cout << offset2[i] << std::endl;
    }
    const int width = TAB_SPACE + 10;

    char title_centered[4 * width + 1];
    std::map<double, int> layer2cluster_map;
    layer2cluster_map[0.1] = 5;
    layer2cluster_map[3] = 5;
    layer2cluster_map[2.5] = 5;
    layer2cluster_map[1.4] = 5;
    layer2cluster_map[3.2] = 5;
    //for (auto& pair : layer2cluster_map) {
    //    std::cout << pair.first << std::endl;
    //}
    std::cout << ">>>>>>>>>>" << std::endl;
    for (auto iter = layer2cluster_map.begin(); iter!= layer2cluster_map.end(); ++iter) {
        auto next_iter = std::next(iter);
        if(next_iter!= layer2cluster_map.end())
            std::cout << iter->first << std::endl;
    }


    system("pause");
    return 0;
}








