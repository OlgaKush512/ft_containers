#include <iostream>
#include <string>
#include <iomanip>
// #include <map>
#include "map.hpp"
 
template<typename Map>
void print_map(Map& m)
{
   std::cout << '{';
   for(auto& p: m)
        std::cout << p.first << ':' << p.second << ' ';
   std::cout << "}\n";
}
 
struct Point { double x, y; };
struct PointCmp {
    bool operator()(const Point& lhs, const Point& rhs) const { 
        return lhs.x < rhs.x; // NB. intentionally ignores y
    }
};
 
int main()
{
	ft::map<int, int> map1;
	ft::pair<int, int> my_pair(10, 1);
	ft::pair<int, int> my_pair1(8, 2);
	ft::pair<int, int> my_pair2(15, 3);


	map1.insert(my_pair);
	map1.insert(my_pair1);
	map1.insert(my_pair2);

	map1.print_map();

}

//   map1["something"] = 69;
//   map1["anything"] = 199;
//   map1["that thing"] = 50;
//   std::cout << "map1 = "; print_map(map1);

//   std::map<std::string, int>::iterator  iter(map1.begin());
//   std::cout << "iter = " << iter->first << std::endl;
//   iter++;
//   std::cout << "iter = " << iter->first << std::endl;
//   iter++;
//   std::cout << "iter = " << iter->first << std::endl;
//    iter++;
//   std::cout << "iter = " << iter->first << std::endl;
 
//   // (2) Range constructor
//   std::map<std::string, int> iter(map1.find("anything"), map1.end());
//   std::cout << "\niter = "; print_map(iter);
//   std::cout << "map1 = "; print_map(map1);
 
//   // (3) Copy constructor
//   std::map<std::string, int> copied(map1);
//   std::cout << "\ncopied = "; print_map(copied);
//   std::cout << "map1 = "; print_map(map1);
 
//   // (4) Move constructor
//   std::map<std::string, int> moved(std::move(map1));
//   std::cout << "\nmoved = "; print_map(moved);
//   std::cout << "map1 = "; print_map(map1);
 
//   // (5) Initializer list constructor
//   const std::map<std::string, int> init {
//     {"this", 100},
//     {"can", 100},
//     {"be", 100},
//     {"const", 100},
//   };
//   std::cout << "\ninit = "; print_map(init);
 
 
//   // Custom Key class option 1:
//   // Use a comparison struct
//   std::map<Point, double, PointCmp> mag = {
//       { {5, -12}, 13 },
//       { {3, 4},   5 },
//       { {-8, -15}, 17 }
//   };
 
//   for(auto p : mag)
//       std::cout << "The magnitude of (" << p.first.x
//                 << ", " << p.first.y << ") is "
//                 << p.second << '\n';
 
//   // Custom Key class option 2:    
//   // Use a comparison lambda
//   // This lambda sorts points according to their magnitudes, where note that
//   //  these magnitudes are taken from the local variable mag
//   auto cmpLambda = [&mag](const Point &lhs, const Point &rhs) { return mag[lhs] < mag[rhs]; };
//   //You could also use a lambda that is not dependent on local variables, like this:
//   //auto cmpLambda = [](const Point &lhs, const Point &rhs) { return lhs.y < rhs.y; };
//   std::map<Point, double, decltype(cmpLambda)> magy(cmpLambda);
 
//   //Various ways of inserting elements:
//   magy.insert(std::pair<Point, double>({5, -12}, 13));
//   magy.insert({ {3, 4}, 5});
//   magy.insert({Point{-8.0, -15.0}, 17});
 
//   std::cout << '\n';
//   for(auto p : magy)
//       std::cout << "The magnitude of (" << p.first.x
//                 << ", " << p.first.y << ") is "
//                 << p.second << '\n';