#include "set_time.hpp"

void set_time(int& nbr_iterations, double& duration, double& dt)
{
    std::string value;

    std::cout<<"\nWhat shall the duration of the simulation be ? (in s) : ";
    std::cin>>value;
    duration=std::stod(value);
    if(duration<=0.0)
    {
        throw(std::invalid_argument("Duration must be positive and nonzero."));
    }

    std::cout<<"\nIn how many steps the duration should be discretized into ? : ";
    std::cin>>value;
    nbr_iterations=std::stoi(value);
    if(nbr_iterations==0)
    {
        throw(std::invalid_argument("Number of intervalls cannot be 0."));
    }

    dt=duration/double(nbr_iterations);/*It is a valid value as duration and nbr_iterations have been checked beforehand.*/

    std::cout<<"\n";
}
