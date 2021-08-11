#pragma once 
#include<unordered_map>
#include<string> 
#include<vector> 
#include<chrono> 
#include<numeric>
+

static std::unordered_map<std::string,double> statistics; 

namespace Utilities
{
/**
 * 
 * Cumulative  product 
 * 
 * @param[in] vec : vector of dimensions in each direction 
 * @param[out] product : cumulative product of vec  
 * 
 */
template<typename T>
T cumulative_product(const std::vector<T>& vec)
{
    const int size = vec.size(); 
    T product = 1;
    for(const i=0;i<size;++i){
        product *= vec[i]; 
    } 
    return product; 
} 

/** 
 * 
 * Scope Timer 
 * 
 * Type for active time measurement : 
 * 
 * Simply declare a object in the scope and the time taken for the operation is included in a list. 
 * 
 */
    class ScopeTimer
    {
    public: 
        ScopeTimer(std::string name)
        {
            function_name = name; 
            start = std::chrono::high_resolution_clock::now(); 
        }

        ~ScopeTimer()
        {
            end = std::chrono::high_resolution_clock::now(); 
            auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds> (end - start);
            statistics[function_name].push_back(elapsed_time.count()); 
        }
    private:
        std::string function_name; 
        std::chrono::time_point start; 
        std::chrono::time_point end; 
        static std::unordered_map<std::string ,std::vector<double>> statistics; 
    };


 // Print the total time spent in all of the functions 
// We could either be satisfied with such an approximation or take up a more challenging setup and try to compute the better Statistics 
    void print_statistics()
    {
        std::cerr <<  "Time spent in each of the subroutines " << std::endl; 
        for(std::pair<std::string , std::vector<double>> stat : statistics) {
            std::cerr << stat.first << " : " << std::accumulate(stat.begin(),stat.end(),0) << "\n"; 
        }
    }
};