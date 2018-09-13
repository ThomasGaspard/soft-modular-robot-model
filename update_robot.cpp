#include "update_robot.hpp"

void update_robot(std::vector<double>& centers, std::vector<double>& radii, unsigned long index_fix_point)
{
    for(long i=long(index_fix_point)-1;i>=0;--i)
    {
        centers[unsigned(i)]=centers[unsigned(i+1)]-radii[unsigned(i)]-radii[unsigned(i+1)];
    }
    for(unsigned long i=index_fix_point+1;i<centers.size();++i)
    {
        centers[i]=centers[i-1]+radii[i]+radii[i+1];
    }
}
