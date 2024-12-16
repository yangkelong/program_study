#include <boost/next_prior.hpp>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Fuzzy_sphere.h>
#include <CGAL/Kd_tree.h>
#include <CGAL/Orthogonal_k_neighbor_search.h>
#include <CGAL/Random.h>
#include <CGAL/Search_traits_2.h>
#include <CGAL/Search_traits_adapter.h>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/algorithm.h>
#include <CGAL/point_generators_2.h>
#include <deque>

using Kernel = CGAL::Exact_predicates_inexact_constructions_kernel;
using Point = Kernel::Point_2;

struct Element {
    Point p;
    int   id;

    struct GetPoint { // property map to access the point
        using key_type = Element;
        using value_type = Point;
        using reference = value_type const&;
        using category = boost::lvalue_property_map_tag;

        value_type const& operator[](Element const& p) const { return p.p; }

        friend reference get(GetPoint const&, Element const& p) { return p.p; }
        friend void put(GetPoint const&, Element& p, value_type v) { p.p = std::move(v); }
    };
};

using Random_points_iterator = CGAL::Random_points_in_square_2<Point>;
using Traits_base = CGAL::Search_traits_2<Kernel>;
using Traits = CGAL::Search_traits_adapter<Element, Element::GetPoint, Traits_base>;
using K_neighbor_search = CGAL::Orthogonal_k_neighbor_search<Traits>;
using Fuzzy_circle = CGAL::Fuzzy_sphere<Traits>;
using Tree = K_neighbor_search::Tree;



int main1111() {
    int const    no_points = 2000; // arbitrary
    int const    size = 1000;

    std::vector<Element> elements;
    generate_n(back_inserter(elements), no_points,
        [gen = Random_points_iterator(size), id = 0]() mutable {
            return Element{ *gen++, id++ };
        });

    // Add this to a K-D tree
    Tree tree(elements.begin(), elements.end());

    // Find a random point to search
    CGAL::Random rand;
    Point search_point = Point(rand.get_double(0, size), rand.get_double(0, size));

    auto radius = 40;
    Fuzzy_circle search_circle(search_point, radius, 0.1);

    // boost::optional<Tree::Point_d> search_area = tree.search_any_point(search_circle);

    // Doing a range search on the tree KD tree space
    std::deque<Element> search_result;
    tree.search(back_inserter(search_result), search_circle);

    std::cout << "Points in within " << radius << " of " << search_point << ":\n";

    for (auto& [p, id] : search_result)
        std::cout << " - " << p << "(#" << id << ")\n";
}