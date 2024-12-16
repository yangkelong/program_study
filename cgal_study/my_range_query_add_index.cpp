#include <CGAL/Epick_d.h>
#include <CGAL/point_generators_d.h>
#include <CGAL/Kd_tree.h>
#include <CGAL/Fuzzy_sphere.h>
#include <CGAL/Search_traits_d.h>
#include <CGAL/Orthogonal_k_neighbor_search.h>
#include <boost/iterator/zip_iterator.hpp>
#include <CGAL/Search_traits_adapter.h>

const int D = 3;
typedef CGAL::Epick_d<CGAL::Dimension_tag<D> > K;
typedef K::Point_d Point_d;

typedef CGAL::Search_traits_d<K, CGAL::Dimension_tag<D> >  Traits_base;
typedef CGAL::Random_points_in_cube_d<Point_d>       Random_points_iterator;
using index = boost::tuple<int, int>;
typedef boost::tuple<Point_d, index>                           Point_and_int;
//typedef boost::tuple<Point_d, int>                           Point_and_int;
typedef CGAL::Search_traits_adapter<Point_and_int, 
    CGAL::Nth_of_tuple_property_map<0, Point_and_int>, Traits_base> Traits;
typedef CGAL::Kd_tree<Traits> Tree;
typedef CGAL::Fuzzy_sphere<Traits> Fuzzy_sphere;

typedef CGAL::Orthogonal_k_neighbor_search<Traits>          K_neighbor_search;
typedef K_neighbor_search::Tree                             Tree1;


int my_fuzzy_range_query1()
//int main()
{
    const int N = 100;
    Random_points_iterator rpit(D, 1.0);
    double  pcoord[D] = { 0.3, 0.3, 0.3 };
    Point_d p(pcoord + 0, pcoord + D);
    Fuzzy_sphere fs(p, 0.7, 0.1);
    std::vector<Point_d> wall_points;
    std::vector<index>     indices;
    const size_t wall_point_num = N;
    //const size_t wall_point_num = 1 << 20;
    for (size_t i = 0; i < wall_point_num; ++i) {
        wall_points.push_back(Point_d(*rpit++));
        indices.emplace_back(N, i + 1);
        //indices.push_back(index(i, i+1));
    }
    Tree tree(boost::make_zip_iterator(boost::make_tuple(wall_points.begin(), indices.begin())),
        boost::make_zip_iterator(boost::make_tuple(wall_points.end(), indices.end())));
    std::vector<Point_and_int> result;
    tree.search(back_inserter(result), fs);
    for (Point_and_int& item : result) {
        const index& idx = boost::get<1>(item);
        std::cout << boost::get<0>(idx)<< ", " << boost::get<1>(idx) << "\n"; // boost::get<0>(item) <<
    }
    //tree.search(std::ostream_iterator<Point_and_int>(std::cout, "\n"), fs);
    return 0;
}