#include <QCoreApplication>
#include <vector>
#include <tuple>
#include <fstream>
#include <iostream>

const string RESULT_PATH="result.csv";
const string ROBOT_PATH="robot.md";
const string TIME_PATH="time.md";

#include "set_robot.hpp"
#include "set_time.hpp"
#include "compute_actual_radii.hpp"
#include "set_sequence.hpp"
#include "find_contact_points.hpp"
#include "slipperiness.hpp"
#include "update_robot.hpp"




int main(int argc, char *argv[])
{
    //*
    QCoreApplication a(argc, argv);
    std::vector <double> centers_of_modules;
    std::vector <double> rest_radii;
    std::vector <double> max_radii;
    std::vector <double> actual_radii;
    std::vector <double> buffer_radii;
    std::vector <double> start_times;
    std::vector <double> time_table;

    double t=0.0;
    double deltaL=0.0;
    double duration;/*Duration of the simulation*/
    int numberOfIteration;/*Time scale*/
    double dt;
    unsigned long index_pivot1;
    unsigned long index_pivot2;
    double angle;
    std::tuple<long,long,double> result;
    std::pair<double,double> slip;

    set_robot2(centers_of_modules,rest_radii,max_radii);
    /*Now we have the initial state (centers_of_modules)and the default parameters of all of the modules.*/

    actual_radii=rest_radii;
    /*At its initial state, the robot is not deformed.*/

    set_time(numberOfIteration, duration, dt);
    /*Now, numberOfIteration, duration and dt are set and have acceptable values.*/

    set_sequence2(start_times,time_table,rest_radii.size());


    std::fstream result_file(RESULT_PATH, std::ios::out|std::ios::trunc);
    /*We run the simulation*/
    if(result_file)
    {
        result_file<<"Time;Left-side;Right-side;Center of gravity\n";
        for(int i=0;i<numberOfIteration;++i)
        {
            std::cout<<"\n"<<i<<"/"<<numberOfIteration;
            t+=dt;
            buffer_radii=actual_radii;
            compute_actual_radii(actual_radii,rest_radii,max_radii,t,start_times,time_table);
            //std::cout<<actual_radii[0];
            //std::cout<<"\nNew radii computed";
            result=find_contact_points(centers_of_modules,actual_radii);
           // std::cout<<"\nContact points found";
            index_pivot1=unsigned(std::get<0>(result));
            index_pivot2=unsigned(std::get<1>(result));
            angle=std::get<2>(result);
            slip=slipperiness(centers_of_modules[index_pivot1],centers_of_modules[index_pivot2],find_center_mass(centers_of_modules));
            //std::cout<<"\nSlipperiness determined";
            deltaL=actual_radii[index_pivot1]+actual_radii[index_pivot2]-buffer_radii[index_pivot1]-buffer_radii[index_pivot2];
            for(unsigned long j=index_pivot1+1;j<index_pivot2;++j)/* What cause the robot to move is the change in length bewteen the contact points */
            {
                deltaL+=2*actual_radii[j]-2*buffer_radii[j];
            }
            deltaL=deltaL*std::abs(std::cos(angle));
            if(slip.first!=0.0)
            {
                centers_of_modules[index_pivot1]+=slip.first*deltaL;
                update_robot(centers_of_modules,actual_radii,index_pivot1);
            }
            else
            {
                centers_of_modules[index_pivot2]+=slip.second*deltaL;
                update_robot(centers_of_modules,actual_radii,index_pivot2);
            }
            //std::cout<<"\n"<<t;
            //result_file<<t<<';'<<centers_of_modules[0]<<';'<<centers_of_modules[centers_of_modules.size()-1]<<';'<<f(t)<<'\n';
            //result_file<<t<<';'<<centers_of_modules[0]<<';'<<centers_of_modules[centers_of_modules.size()-1]<<';'<<g(2., 0.1, 0.45,t)+g(2., 0.55,0.9,t)<<'\n';

            result_file<<t<<';'<<centers_of_modules[0]<<';'<<centers_of_modules[centers_of_modules.size()-1]<<';'<<find_center_mass(centers_of_modules)<<'\n';

            //std::cout<<t<<';'<<centers_of_modules[0]<<';'<<centers_of_modules[centers_of_modules.size()-1]<<';'<<find_center_mass(centers_of_modules)<<'\n';
            /*
            result_file<<t;
            for(int i=0;i<15;++i)
            {
                result_file<<';'<<actual_radii[i];
            }
            result_file<<';'<<index_pivot1<<';'<<index_pivot2;
            result_file<<'\n';
            //*/
        }
    }
    else
    {
        std::cerr<<"\nResult file could not be opened.";
    }
    result_file.close();
    std::cout<<"Done !";
   /* Py_Initialize();
    PyObject *obj = Py_BuildValue("s", "graph.py");
    FILE *file = _Py_fopen_obj(obj, "r+");
    if(file != NULL)
    {
       PyRun_SimpleFile(file, "graph.py");
    }
    else
    {
       std::cout<<"Graph script could not be open.";
    }*/
    return a.exec();
    //*/
}
