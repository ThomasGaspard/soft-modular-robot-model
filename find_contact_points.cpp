#include "find_contact_points.hpp"

std::tuple<long,long,double> find_contact_points(std::vector<double>& position_of_the_centers, std::vector<double>& radii)
{
    double xg=find_center_mass(position_of_the_centers);

    std::vector<double>::iterator radius_pivot1;
    std::vector<double>::iterator radius_pivot2;
    std::vector<double>::iterator moving_radius;

    std::vector<double>::iterator position_pivot1;
    std::vector<double>::iterator position_pivot2;
    std::vector<double>::iterator moving_position;

    long index_pivot1;
    long index_pivot2;

    double minimal_slope=std::numeric_limits<double>::infinity();
    double slope;
    double angle;

    radius_pivot1=radii.begin();
    radius_pivot2=radii.begin();
    position_pivot1=position_of_the_centers.begin();
    position_pivot2=position_of_the_centers.begin();

    while(radius_pivot1!=std::max_element(std::begin(radii),std::end(radii)))
    {
        ++radius_pivot1;
        ++radius_pivot2;
        ++position_pivot1;
        ++position_pivot2;
    }/*Now the iterators are toward the module that is the most inflated*/

    while((std::min(*position_pivot1,*position_pivot2)>xg) or (std::max(*position_pivot1,*position_pivot2)<xg))
        /* While both of the pivot are on the same side of the center of gravity, the contact is not stable */
    {

        if(*position_pivot1<=xg)/*If the pivots are on the left side of the center of gravity */
        {
            moving_position=position_pivot1;
            moving_radius=radius_pivot1;
            while(moving_radius<--(--std::end(radii))) /*We look for the module at the right of the pivot1 which provide the lowest slope */
            {
                ++moving_radius;
                ++moving_position;
                slope=(*radius_pivot1-*moving_radius)/(*moving_position-*position_pivot1);
                if(slope<=minimal_slope)
                {
                    minimal_slope=slope;
                    position_pivot2=moving_position;
                    radius_pivot2=moving_radius;
                    angle=-1.0;
                }
            }
        }
        else /* Else if the pivot are on the right side of the center of mass */
        {
            moving_position=position_pivot1;
            moving_radius=radius_pivot1;
            while(moving_radius>std::begin(radii)) /* We look for the module at the left of pivot1 which provide the lowest slope */
            {
                --moving_radius;
                --moving_position;
                slope=(*moving_radius-*radius_pivot1)/(*moving_position-*position_pivot1);
                if(minimal_slope>=slope)
                {
                    minimal_slope=slope;
                    position_pivot2=moving_position;
                    radius_pivot2=moving_radius;
                    angle=1.0;
                }
            }
        }
        /*If, after that, the two modules are still on the same side of the robot ; pivot1 turns into pivot2 and we start again */
        if((std::min(*position_pivot1,*position_pivot2)>xg) or (std::max(*position_pivot1,*position_pivot2)<xg))
        {
            radius_pivot1=radius_pivot2;
            position_pivot1=position_pivot2;

            minimal_slope=std::numeric_limits<double>::infinity();
        }
        //std::cout<<"\np1 : "<<*position_pivot1<<"\np2 ."<<*position_pivot2<<"\nxg : "<<xg;
        //std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    angle=angle*std::atan(minimal_slope);
    index_pivot1=std::distance(radii.begin(),radius_pivot1);
    index_pivot2=std::distance(radii.begin(),radius_pivot2);
    if(index_pivot1<index_pivot2)
    {
        return(std::make_tuple(index_pivot1,index_pivot2,angle));
    }
    else
    {
        return(std::make_tuple(index_pivot2,index_pivot1,angle));
    }

}


double find_center_mass(const std::vector<double>& centers)
{
    /* Each module weight the same, and must be seen as a ponctual mass of weight m placed at centers[i].
     * Hence, the center of mass is the average of the centers ponderated by the mass of each modules. As the mass are the same,
     * the center of mass lays at the average of the centers' position. */
    unsigned long number_of_modules=centers.size();
    double xg=0.0;
    for(unsigned long i=0;i<number_of_modules;++i)
    {
        xg+=centers[i];
    }
    xg/=double(number_of_modules);
    //std::cout<<"\nxg : "<<xg;
    return (xg);
}
