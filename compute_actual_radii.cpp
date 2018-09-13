#include "compute_actual_radii.hpp"

void compute_actual_radii(std::vector<double>& radii, const std::vector<double>& initial_radii, const std::vector<double>& max_radii,
                          double t, const std::vector<double> start_times, const std::vector<double> time_table)
/* Radii is a reference toward the vector that will be modified representing the state at time t
 *
 * initial_radii is a vector giving the initial radii of all of the modules
 *
 * t is the time at which one wants to determine the state of the robot
 *
 * start_time is a vector the size of the robot containing the starting time of actuation for each module. The lenght of the actuation is
 *      thus max(start_times)+sum(time_table). If t>actuation_length, we assume the actuation periodic and starts at t mod(actuation_length
 *      instead.
 *
 * time_table is a vector containing the duration of the phases of the actuation, is second. It must be 4-element long, and organized
 *      as follow : [Inflation, Break, Deflation, Break]. The elements are the duration (and not a relative starting point) of said
 *      phases.
*/
{
    double actuation_duration=0.0;
    double period_duration=0.0;

    if(time_table.size()!=4)/*C.F. preliminary comment for the magic value.*/
    {
        throw(std::invalid_argument("Time table does not have a valid size."));
    }
    /*Processing the actuation duration, that is the duration of actuation of one module. It is the sum of the
     * values given in the time_table*/

    for(unsigned int i=0;i<time_table.size();++i)
    {
        period_duration+=time_table[i];
        if(time_table[i]<0.0)
        {
            throw(std::invalid_argument("The description of the actuation cannot contain negative elements."));
        }
    }
    //std::cout<<"\n"<<actuation_duration<<"\n";
    /*We will now check the validity of the start_time. As said in the description comment, it must be the same size
     * as radii or initial_radii. Furthemore, it must not contain negative elements.*/
    if(start_times.size()!=initial_radii.size())
    {
        throw(std::invalid_argument("Start time does not have the right length."));
    }
   if(*(std::min_element(std::begin(start_times), std::end(start_times)))<0.0)
   {
       throw(std::invalid_argument("No module can starts its actuation at negative times."));
   }
   actuation_duration=*(std::max_element(std::begin(start_times), std::end(start_times)))+period_duration;
   while(t>actuation_duration)
   {
       t-=actuation_duration;
   }

   /*Now we need to determine the state of the modules that are actuated*/
   for(unsigned int i=0;i<radii.size(); ++i)
   {
        if(t>start_times[i] and t<(start_times[i]+actuation_duration))
        {
            /*Module i is actuated. Time to determine in what kind of phase it is in !*/
            if(t<(time_table[0]+start_times[i]))
            {
               // std::cout<<"\n"<<i<<" : inflation";
                /*We consider the increase of radius linear in time*/
                radii[i]=initial_radii[i]+(max_radii[i]-initial_radii[i])*(t-start_times[i])/time_table[0];
                //std::cout<<radii[i];
                //radii[i]=std::max(0.0,R(t));
            }
            else if (t<(start_times[i]+time_table[1]+time_table[0]))
            {
               // std::cout<<"\n"<<i<<" : b1";
                radii[i]=max_radii[i];
            }
            else if(t<(start_times[i]+time_table[2]+time_table[1]+time_table[0]))
            {
                //std::cout<<"\n"<<i<<" : deflation";
                radii[i]=max_radii[i]+(initial_radii[i]-max_radii[i])*(t-start_times[i]-time_table[0]-time_table[1])/
                        (time_table[2]);
                //std::cout<<radii[i];
                //radii[i]=std::max(0.0,R(t));
            }
            else
            {
                //std::cout<<"\n"<<i<<" : b2";
                radii[i]=initial_radii[i];
            }
      }
   }
}

double R(double t)
{
    double r=1000.0*42.0/(3.0*45.0)-0.163*t+0.103*t*t;
    if(t-0.147>0.0)
    {
        r+=0.00217*t;
    }
    if(0.644-t>1)
    {
        r+=(0.17*t-0.0654-0.106*t*t);
    }
    else
    {
        r-=(0.17*t-0.0654-0.106*t*t);
    }
    return r;
}
