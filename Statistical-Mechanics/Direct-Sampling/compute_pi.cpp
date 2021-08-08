#include<iostream> 
#include<random> 
#include<cmath> 
#include<vector> 
#include<array> 
#include<numeric>

//==============================================================================================================================
/** 
 * Scale the uniform random number distribution to the required limits 
 * @param val_max : double
 * @param val_min : double 
 * @param rand_num : double uniform random numbers in the range (0,1) 
 * 
 * @result shifted_val
 **/ 

double shift_range(const double &val_max,const double &val_min,double rand_num)
{   
    double shift = val_max - val_min;
    return val_min + shift * rand_num;    
}

//==============================================================================================================================

/** 
 * Returns the distance between any to points
 * @param point1 std::array<double,2>
 * @param point2 std::array<double,2> 
 * 
 * @result distance double 
 * 
 **/ 

double distance_l2(const std::array<double,2> &point1,const std::array<double,2> &point2)
{
    return sqrt((point1[0] - point2[0])*(point1[0] - point2[0]) + (point1[1] - point2[1])*(point1[1] - point2[1])); 
}
//==============================================================================================================================

/** 
 * Returns the distance between one point and the origin
 * @param point1 std::array<double,2>
 * 
 * @result distance double 
 * 
 **/ 
double distance_to_origin(const std::array<double,2> &point1)
{
    return sqrt((point1[0])*(point1[0]) + (point1[1])*(point1[1])); 
}

//==============================================================================================================================

/** 
 * Prints vector of values for pi in a list like fashion 
 * 
 * @param list : std::vector<template> 
 **/ 
template<typename T> 
void print_vector(const std::vector<T>& list) 
{
    for(const auto &elem : list){
        std::cout << elem << "\n"; 
    }
}

//==============================================================================================================================

/**
 * To compute the magnitude of pi from direct sampling 
 **/ 
int main(int argc,char** argv) 
{
    int seed = 0; 
    double xmax = 1; 
    double xmin = -1; 
    double ymax = 1; 
    double ymin = -1;
    double radius = 1.0; 
    double x_candidate,y_candidate;  
    std::default_random_engine generator(seed); 
    std::uniform_real_distribution<double> distribution(0,1);
    size_t num_trails = 1e6; 
    size_t num_runs = 1e2; 
    size_t current_run = 0; 
    std::vector<double> success_history; 
    int num_of_hits; 

    while(current_run < num_runs) {
        num_of_hits = 0; 
        for(size_t trail=0;trail<num_trails;++trail){
            x_candidate = shift_range(xmax,xmin,distribution(generator)); 
            y_candidate = shift_range(ymax,ymin,distribution(generator)); 
            if(distance_to_origin(std::array<double,2>{x_candidate,y_candidate}) <= radius) {
               num_of_hits ++;  
            } 
        }
        success_history.push_back((double)num_of_hits/num_trails);
        current_run++; 
    }
    print_vector(success_history); 
    std::cout << "Average value of pi is " << 4.0*(std::accumulate(success_history.begin(),success_history.end(),0.0))/(double)num_runs << std::endl; 
    return 0;
}