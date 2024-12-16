#include <CGAL/Timer.h>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Orthogonal_k_neighbor_search.h>
#include <CGAL/point_generators_3.h>
#include <CGAL/Search_traits_3.h>
typedef CGAL::Simple_cartesian<double>                Kernel;
typedef CGAL::Search_traits_3<Kernel>                 Traits_3;
typedef Kernel::Point_3                               Point_3;
typedef CGAL::Sliding_midpoint<Traits_3>              Sliding_midpoint;
typedef CGAL::Median_of_rectangle<Traits_3>           Median_of_rectangle;
typedef CGAL::Euclidean_distance<Traits_3>            Distance;
typedef CGAL::Orthogonal_k_neighbor_search<Traits_3, Distance, Sliding_midpoint>     Neighbor_search_sliding;
typedef CGAL::Orthogonal_k_neighbor_search<Traits_3, Distance, Median_of_rectangle>  Neighbor_search_median;
typedef Neighbor_search_sliding::Tree                 Tree_sliding;
typedef Neighbor_search_median::Tree                  Tree_median;
typedef CGAL::Fair<Traits_3> Fair;
using SplittingRule = Fair;
typedef CGAL::Kd_tree<Traits_3, SplittingRule, CGAL::Tag_true, CGAL::Tag_true> CacheTree;
typedef CGAL::Kd_tree<Traits_3, SplittingRule, CGAL::Tag_true, CGAL::Tag_false> Tree;
typedef CGAL::Orthogonal_k_neighbor_search<Traits_3, Distance, SplittingRule, CacheTree> CacheTree_Neighbor_search;
typedef CGAL::Orthogonal_k_neighbor_search<Traits_3, Distance, SplittingRule, Tree> Neighbor_search;
typedef CGAL::Random_points_in_cube_3<Point_3>              Random_points_iterator;


//int main()
int main_cache_test()
{   
    CGAL::Timer timer;
    const unsigned int K = 1;
    // generator for random data points in the cube ( (-1,-1,-1), (1,1,1) )
    Random_points_iterator rpit(50.0);
    std::vector<Point_3> wall_points;
    std::vector<int>     indices;
    const size_t wall_point_num = 1 << 20;
    std::cout << "wall_point_num =  " << wall_point_num << std::endl;
    for (size_t i = 0; i < wall_point_num; ++i) {
        wall_points.push_back(Point_3(*rpit++));
        indices.push_back(i);
    }
    const size_t query_point_num = 1 << 21; // 10M
    std::vector<Point_3> query_points(query_point_num);
    std::vector<double> query_dists(query_point_num);
    for (size_t i = 0; i < query_point_num; ++i) {
        query_points[i] = Point_3(*rpit++);
    }


   
    timer.start();
    // build tree
    CacheTree cache_tree(query_points.begin(), query_points.end());
    // search K nearest neighbors
    timer.stop();
    std::cout << "build tree spend time: " << timer.time() << std::endl;
    timer.reset();


    timer.start();
    // build tree
    Tree tree(query_points.begin(), query_points.end());
    // search K nearest neighbors
    timer.stop();
    std::cout << "build tree spend time: " << timer.time() << std::endl;
    timer.reset();


    Distance tr_dist;

    timer.start();
    for (size_t i = 0; i < query_point_num; ++i) {
        const auto& query = query_points[i];
        CacheTree_Neighbor_search search(cache_tree, query, K);
        CacheTree_Neighbor_search::iterator res_iter = search.begin();
        query_dists[i] = res_iter->second;
        //query_dists[i] = tr_dist.inverse_of_transformed_distance(res_iter->second);
    }
    timer.stop();
    std::cout << "cache tree nereast point query spend time: " << timer.time() << std::endl;
    timer.reset();

    timer.start();
    for (size_t i = 0; i < query_point_num; ++i) {
        const auto& query = query_points[i];
        Neighbor_search search(tree, query, K);
        Neighbor_search::iterator res_iter = search.begin();
        query_dists[i] = res_iter->second;
        //query_dists[i] = tr_dist.inverse_of_transformed_distance(res_iter->second);
    }
    timer.stop();
    std::cout << "nereast point query spend time: " << timer.time() << std::endl;
    timer.reset();



    return 0;
}