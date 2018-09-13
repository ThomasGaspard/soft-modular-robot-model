#include "set_robot.hpp"

void set_robot(std::vector<double>& centers, std::vector<double>& default_radii, std::vector<double>& max_radii)
{
    bool loop=true;/*When loop is false, the simulation starts*/

    std::string choice="1";
    double dft_radius=0.0;
    double max_radius=0.0;
    while(loop)
    {
        std::cout<<"Currently, the robot is made of "<<centers.size()<<" robot.\n";
        std::cout<<"Run the simulation ? N/y : ";
        std::cin>>choice;
        if(choice=="y" or choice=="Y")
        {
            loop=false;
        }
        else/*The simulation does not start. Shall we add a module ?*/
        {
            std::cout<<"Add a module ? Y/n : ";
            std::cin>>choice;
            if(choice!="n")/*If default choice, we add a module.*/
            {
                std::cout<<"\nModule's base radii : ";
                std::cin>>choice;
                dft_radius=std::stod(choice);/*Convert entry to double*/
                std::cout<<"\nModule's max radii : ";
                std::cin>>choice;
                max_radius=std::stod(choice);
                std::cout<<"\nAdd a module with default radius : "<<dft_radius<<" and max size "<<max_radius<<" . Y/n :";
                std::cin>>choice;
                if(choice!="n")
                {
                    if(max_radius<=dft_radius or dft_radius==0.0)
                    {
                        throw(std::invalid_argument("Max radius must be greater than rest radius, and both must be nonzero values."));
                    }
                    /*We are sure the values are correct by now*/
                    if(centers.size()==0)
                    {
                        centers.push_back(0.0);
                    }
                    else
                    {
                        centers.push_back(centers[centers.size()-1]+default_radii[default_radii.size()-1]+dft_radius);
                    }
                    default_radii.push_back(dft_radius);
                    max_radii.push_back(max_radius);
                }

            }
        }

    }
}

void set_robot2(std::vector<double>& centers, std::vector<double>& default_radii, std::vector<double>& max_radii)
{
    /*The "robot" file should be organized as follow :
     * restSizeModule1 maxSizeModule1
     * restSizeModule2 maxSizeModule2
     * restSizeModule3 maxSizeModule3
     * ...
     * EOF
     * Everything after the "EOF" will not be used.
     * For exemple, a 3-module robot made of module with a size 15 at rest and 17 inflated should look as follows :
     *  15.0 17.0
     *  15.0 17.0
     *  15.0 17.0
     *  EOF
     * */
    std::ifstream robot_file("C:/Users/Home/Documents/model/robot.md",std::ios::in);
    std::string param;
    centers.clear();
    default_radii.clear();
    max_radii.clear();
    if(robot_file)
    {
        robot_file>>param;
        do
        {
            default_radii.push_back(std::stod(param));
            robot_file>>param;
            max_radii.push_back(std::stod(param));
            if(centers.size()==0)
            {
                centers.push_back(0.0);
            }
            else
            {
                centers.push_back(*--centers.end()+*(--(--default_radii.end()))+*(--default_radii.end()));
            }
            robot_file>>param;
        }
        while(param!="EOF");
        std::cout<<"\nRobot loaded :";
        for(unsigned long i=0;i<default_radii.size();++i)
        {
            std::cout<<"\nModule "<<i+1<<", rest size :"<<default_radii[i]<<", max size : "<<max_radii[i]<<".";
        }
        robot_file.close();
    }
    else
    {
        std::cerr<<"File not found";
    }

}
