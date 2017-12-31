#include <iostream>
#include <vector>

int main(int argc, char *argv[])
{
    std::vector<double> dist_between_citys;
    dist_between_citys.clear();
    double distance = 0.0;
    std::cout << "Please enter distances between citys!\n";
    while (std::cin >> distance) {
        if (distance <= 0.0) {
            std::cout << "Please enter legal distance between citys!\n";
            continue;
        }
        dist_between_citys.push_back(distance);
    }
    
    if (dist_between_citys.empty()) {
        std::cout << "No legal input!\n";    
    }
    
    double max_distance = dist_between_citys[0];
    double min_distance = max_distance;
    double total_dists = 0.0;
    
    for (auto& item : dist_between_citys) {
        total_dists += item;
        
        if (item > max_distance) {
            max_distance = item;    
        }
        
        if (item < min_distance) {
            min_distance = item;    
        }
    }
    
    int city_nums = dist_between_citys.size();
    double average_dist = total_dists / city_nums;
    
    std::cout << "Total distances: " << total_dists << std::endl;
    std::cout << "Min distance: " << min_distance << std::endl;
    std::cout << "Max distance: " << max_distance << std::endl;
    std::cout << "Average distance: " << average_dist << std::endl;
    
    return 0;
}

