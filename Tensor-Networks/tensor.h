#ifndef TENSORS_H
#define TENSORS_H 
#include<iostream>
#include<vector>
#include<algorithm> 
#include<cassert> 
#include "utilities.h"

template<typename T> 
class Tensors
{
public:

/** 
 * Constructor for all zero initialization 
*/ 
    Tensors(const size_t& ndim,const std::vector<size_t>& dims,const int seed)
        : ndims(ndim) , dimensions(dims) 
        {
            const int num_elements = Utilities::cumulative_product(dimensions); 
            tensor.resize(num_elements); 
        } 

/** 
 * Constructor for random number initialization of the tensor 
 */ 
    Tensors(const size_t& ndim,const std::vector<size_t>& dims)
        : ndims(ndim) , dimensions(dims) 
        {
            const int num_elements = Utilities::cumulative_product(dimensions);
            tensor.resize(num_elements); 
            std::generate(tensor.begin(),tensor.end(),[](){return rand()%10;});
        }

// No copying allowed
    Tensors(const Tensors&) = delete; 

// No copying allowed 
    Tensors& operator=(const Tensors&) =delete; 

// Move constructor is allowed 
    Tensors(const Tensors&& other) 
    {
        // Steal data 
        ndims = other.ndims; 
        dimensions = other.dimensions; 
        tensor = other.tensor;

        // Due diligence 
        other.ndims = 0;
        dimensions = NULL; 
        tensor = NULL;  
    }

// Move assignment operation is allowed 
    Tensor& operator=(const Tensor&& other)
    {
        if(&other != this)
        {
            ndims = other.ndims; 
            dimensions = other.dimensions; 
            tensor = other.tensor; 

            other.ndims = 0; 
            other.dimensions = NULL; 
            other.tensor = NULL; 
        }
        return *this; 
    }
// Default constructor : Prevents improper declaration of the type. 
    Tensors() = default; 

// Default destructor 
    ~Tensors() = default; 


/** 
 * Permute the tensor to a new dimension set : Brute force implementation 
 * 
 * Returns a new tensor : Not ideal. 
 * We require an inplace implementation of this version as well. 
 * 
 * @param[in] perm :: vector of new link order 
 * @param[out] tensor_1 : permuted value of the tensor 
 */ 

    Tensor<T> permute_links(const std::vector<size_t>& perm_index)
    {
        int param1 = Utilities::cumulative_product(perm_index); 
        int param2 = Utilities::cumulative_product(dimensions);
        assert(param1 - param2 == 0); 
        Tensor<T> permuted(ndims,perm_index,0);
        // Logic to permute the elements in the vector 
        // Stick with a vector
        // C style arrays require memory mamagement and clean up 
        // Despite overhead the vector type can be efficient
        // If the speedup in the computation is insufficient, we shall try to use a C style array. 
    }

    /// TODO: Other implementations from the base paper. 

private: 
    size_t ndims; 
    std::vector<size_t> dimensions;
    std::vector<T> tensor;
};  
#endif 