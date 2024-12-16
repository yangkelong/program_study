#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Search_traits_3.h>
#include <CGAL/Search_traits_adapter.h>
#include <CGAL/point_generators_3.h>
#include <CGAL/Orthogonal_k_neighbor_search.h>
#include <CGAL/property_map.h>
#include <boost/iterator/zip_iterator.hpp>
#include <utility>
#include <CGAL/Timer.h>
typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::Point_3                                     Point_3;
typedef boost::tuple<Point_3, int>                           Point_and_int;
typedef CGAL::Random_points_in_cube_3<Point_3>              Random_points_iterator;
typedef CGAL::Search_traits_3<Kernel>                       Traits_base;
typedef CGAL::Search_traits_adapter<Point_and_int,
    CGAL::Nth_of_tuple_property_map<0, Point_and_int>,
    Traits_base>                                              Traits;
typedef CGAL::Orthogonal_k_neighbor_search<Traits>          K_neighbor_search;
typedef K_neighbor_search::Tree                             Tree;
typedef K_neighbor_search::Distance                         Distance;
//int main()
int main_tree_test()
{   
    CGAL::Timer timer;
    const unsigned int K = 1;
    // generator for random data points in the cube ( (-1,-1,-1), (1,1,1) )
    Random_points_iterator rpit(1.0);
    std::vector<Point_3> wall_points;
    std::vector<int>     indices;
    const size_t wall_point_num = 1 << 20;
    std::cout << "wall_point_num =  " << wall_point_num << std::endl;
    for (size_t i = 0; i < wall_point_num; ++i) {
        wall_points.push_back(Point_3(*rpit++));
        indices.push_back(i);
    }
    const size_t query_point_num = 1 << 21; // 2M
    std::vector<Point_3> query_points(query_point_num);
    std::vector<double> query_dists(query_point_num);
    for (size_t i = 0; i < query_point_num; ++i) {
        query_points[i] = Point_3(*rpit++);
    }
    
    timer.start();
    // build tree
    Tree tree(boost::make_zip_iterator(boost::make_tuple(wall_points.begin(), indices.begin())),
        boost::make_zip_iterator(boost::make_tuple(wall_points.end(), indices.end())));
    // search K nearest neighbors
    timer.stop();
    std::cout << "build tree spend time: " << timer.time() << std::endl;
    timer.reset();
    
    timer.start();
    Distance tr_dist;
    for (size_t i = 0; i < query_point_num; ++i) {
        const auto& query = query_points[i];
        K_neighbor_search search(tree, query, K);
        K_neighbor_search::iterator res_iter = search.begin();
        query_dists[i] = res_iter->second;
        //query_dists[i] = tr_dist.inverse_of_transformed_distance(res_iter->second);
    }
    timer.stop();
    std::cout << "nereast point query spend time: " << timer.time() << std::endl;
    timer.reset();
    return 0;
}