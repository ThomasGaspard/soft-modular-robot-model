#include "set_sequence.hpp"

void set_sequence(std::vector<double>& start_times, std::vector<double>& time_table, unsigned long number_of_modules)
{
    std::string choice;
    std::string message;
    double actuation_time=0.0;
    time_table.clear();
    start_times.clear();
    for(int i=0;i<int(number_of_modules);++i)/* We cannot declare i as an unsigned int. Indeed, if there is an error when i=0, i will
                                              * be decremented, producing an undefined behaviour. Instead, we convert the unsigned int
                                              * of the vector.size() into an int.*/
    {
        try
        {
            std::cout<<"\nModule number "<<i+1<<" starts its actuation after (in seconds) : ";
            std::cin>>choice;
            actuation_time=std::stod(choice);
            if(actuation_time<0.0)
            {
                throw(std::invalid_argument("Actuation time cannot be negative."));
            }
            std::cout<<"\nModule "<<i+1<<" is actuated after "<<actuation_time<<"s. Y/n : ";
            std::cin>>choice;
            if(choice=="n")
            {
                --i;
            }
            else
            {
                start_times.push_back(actuation_time);
            }
        }
        catch(std::exception const& e)
        {
            std::cerr<<e.what();
            --i;
        }
    }
    for(int i=0;i<4;++i)
        /* We cannot declare i as an unsigned int. Indeed, if there is an error when i=0, i will
         * be decremented, producing an undefined behaviour. But this is not a problem here as we use a terrific magic value. Sorry.
         * 4 is a magic value, being the length of the time_table.time_table is a vector
         * containing the duration of the phases of the actuation, is second. It must be 4-element
         * long, and organized as follow : [Inflation, Break, Deflation, Break]. The elements are
         * the duration (and not a relative starting point) of said phases.*/
    {
        try
        {
            switch(i)
            {
                case 0:
                    message="inflation";
                    break;
                case 1:
                    message="first break";
                    break;
                case 2:
                    message="deflation";
                    break;
                case 3:
                    message="second break";
                    break;
            }
            std::cout<<"\nDuration of the "<<message<<" (in seconds) : ";
            std::cin>>choice;
            actuation_time=stod(choice);
            if(actuation_time<0.0)
            {
                throw(std::invalid_argument(std::string("The duration of the ")+message+std::string(" cannot be negative.")));
            }
            std::cout<<"\nThe "<<message<<" will last "<<actuation_time<<"s. Y/n :";
            std::cin>>choice;
            if(choice=="n")
            {
                --i;
            }
            else
            {
                time_table.push_back(actuation_time);
            }
        }
        catch(std::exception const& e)
        {
            std::cerr<<e.what();
            --i;
        }
    }
}

void set_sequence2(std::vector<double>& start_times, std::vector<double>& time_table, unsigned long number_of_modules)
{
    std::ifstream robot_file("C:/Users/Home/Documents/model/time.md",std::ios::in);
    std::string param;
    start_times.clear();
    time_table.clear();
    if(robot_file)
    {
        robot_file>>param;
        do
        {
            start_times.push_back(std::stod(param));
            robot_file>>param;
        }
        while(param!="EOST");
        if(number_of_modules!=start_times.size())
        {
            throw(std::logic_error("Time table given has not the same size that robot given."));
        }
        for(int i=0;i<4;++i)
        {
            robot_file>>param;
            time_table.push_back(std::stod(param));
        }
        robot_file.close();
        std::cout<<"---\nDuration for "<<time_table[0]<<"s, break for "<<time_table[1]<<"s, deflation for"<<time_table[2]<<"s and break for "<<time_table[3]<<"s.";
        std::cout<<"\nDuration of the actuation :"<<time_table[0]+time_table[1]+time_table[2]+time_table[3];
        for(unsigned long i=0;i<number_of_modules;++i)
        {
            std::cout<<"\nModule "<<i+1<<" starts after "<<start_times[i]<<"s.";
        }
    }

}
