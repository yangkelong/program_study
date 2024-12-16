#include <CGAL/Epick_d.h>
#include <CGAL/point_generators_d.h>
#include <CGAL/Kd_tree.h>
#include <CGAL/Fuzzy_sphere.h>
#include <CGAL/Fuzzy_iso_box.h>
#include <CGAL/Search_traits_d.h>
const int D = 3;
typedef CGAL::Epick_d<CGAL::Dimension_tag<D> > K;
typedef K::Point_d Point_d;

typedef CGAL::Search_traits_d<K, CGAL::Dimension_tag<D> >  Traits;
typedef CGAL::Random_points_in_cube_d<Point_d>       Random_points_iterator;
typedef CGAL::Counting_iterator<Random_points_iterator> N_Random_points_iterator;
typedef CGAL::Kd_tree<Traits> Tree;
typedef CGAL::Fuzzy_sphere<Traits> Fuzzy_sphere;
typedef CGAL::Fuzzy_iso_box<Traits> Fuzzy_iso_box;

int my_fuzzy_range_query()
//int main()
{
    const int N = 100;
    // generator for random data points in the square ( (-1, -1, -1), (1, 1, 1) )
    Random_points_iterator rpit(D, 1.0);
    // Insert N points in the tree
    Tree tree(N_Random_points_iterator(rpit, 0), N_Random_points_iterator(rpit, N));
    // define range query objects
    double  pcoord[D] = {0.3, 0.3, 0.3};
    Point_d p(pcoord + 0, pcoord + D);
    std::cout << p << std::endl;
    Fuzzy_sphere fs(p, 0.7, 0.1); // r = 0.7, ϵ = 0.1
    std::cout << "points approximately in fuzzy spherical range query" << std::endl;
    std::cout << "with center (300, 300, 300)" << std::endl;
    std::cout << "and fuzzy radius [600, 800] are:" << std::endl;
    tree.search(std::ostream_iterator<Point_d>(std::cout, "\n"), fs);


    //double  qcoord[D] = { 900.0, 900.0, 900.0 };
    //Point_d q(D, qcoord + 0, qcoord + D);
    //Fuzzy_iso_box fib(p, q, 100.0);
    //std::cout << "points approximately in fuzzy rectangular range query ";
    //std::cout << "[[200, 400], [800,1000]]^4 are:" << std::endl;
    //tree.search(std::ostream_iterator<Point_d>(std::cout, "\n"), fib);
    return 0;
}