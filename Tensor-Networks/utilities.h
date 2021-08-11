#pragma once 
#include<unordered_map>
#include<string> 
#include<vector> 

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

    private:

    };

};