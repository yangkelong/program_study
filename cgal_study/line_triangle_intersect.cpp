#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/intersections.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_3 Point_3;
typedef K::Segment_3 Segment_3;
typedef K::Triangle_3 Triangle_3;

int main() {
    Point_3 p1(0, 0, 0);
    Point_3 p2(1, 0, 0);
    Point_3 p3(0, 1, 0);
    Point_3 start_point(0.15, 0.25, -1);
    Point_3 end_point(0.25, 0.15, 1);
    Segment_3 seg(start_point, end_point);
    Triangle_3 tri(p1, p2, p3);

    CGAL::cpp11::result_of<K::Intersect_3(Segment_3, Triangle_3)>::type result = CGAL::intersection(seg, tri);

    if (result) {
        if (const Point_3* p = boost::get<Point_3>(&*result)) {
            std::cout << "Intersection point: " << *p << std::endl;
        }
        else if (const Segment_3* s = boost::get<Segment_3>(&*result)) {
            std::cout << "Intersection segment: " << *s << std::endl;
        }
    }
    else {
        std::cout << "No intersection" << std::endl;
    }

    return 0;
}

