#include "slipperiness.hpp"

std::pair<double,double> slipperiness(double x1, double x2, double xg)
{
    double epsilon=1.09;
    double d1=std::abs(x1-xg);/* Distance from the first pivot to the center of mass */
    double d2=std::abs(x2-xg);/* Distance from the second pivot to the center of mass */
    if(d1/d2>epsilon)
    {
        std::cout<<"\n"<<-1<<":"<<0;
        return(std::make_pair(-1.0,0.0));      
    }
    else if(d2/d1>epsilon)
    {
        std::cout<<"\n"<<0<<":"<<1;
        return(std::make_pair(0.0,1.0));
    }
    std::cout<<"\n"<<-0.5<<":"<<0.5;
    return(std::make_pair(-0.5,0.5));   
}
std::pair<double,double> slipperiness2(double x1, double x2, double xg)
{
    double C=0.1;
    double s=0;
    s = std::min(x1,x2);
    s=xg-s;
    s=s/std::abs(x2-x1);
    s=s-0.5;
    s=M_PI*s;
    s=std::tan(s);
    s=-C*s;
    s=std::exp(s);
    s=s+1;
    s=1/s;
    std::cout<<"\n"<<-s<<":"<<1-s;
    return(std::make_pair(-s,1-s));
}

std::pair<double,double> slipperiness3(double x1, double x2, double xg)
{
    double x=std::min(x1,x2);
    x=(xg-x)/(std::max(x1,x2)-x);
    std::cout<<"\n"<<-f(x)<<":"<<1-f(x);
    return(std::make_pair(-f(x),1-f(x)));
}

std::pair<double,double> slipperiness4(double x1, double x2, double xg)
{
    double alpha=0.3;
    double beta = 0.5;
    double gamma = 0.5;
    double delta = 0.8;
    double C1=3.;
    double C2=C1;
    double x=std::min(x1,x2);
    x=(xg-x)/(std::max(x1,x2)-x);
    //std::cout<<"\n"<<-f(x)<<":"<<1-f(x);
    return(std::make_pair(-g(C1, alpha, beta,x)-g(C1, gamma, delta,x),1-g(C1, alpha, beta,x)-g(C2, gamma, delta,x)));
}

double f(double x)
{
    double beta=0.12;
    double C=5;
    if(x<=beta)
    {
        return(0.0);
    }
    else if(x>=1-beta)
    {
        return(1.0);
    }
    x-=1./2.;
    x*=(M_PI)/(1-2*beta);
    x=-C*std::tan(x);
    x=1+std::exp(x);
    return(1/x);
}

double g(double C,double alpha, double beta, double x)
{
    if(x<=alpha)
    {
        return(0.0);
    }
    else if(x>=beta)
    {
        return(0.5);
    }
    x-=alpha;
    x/=(beta-alpha);
    x-=1./2.;
    x*=M_PI;
    x=std::tan(x);
    x*=-C;
    x=1+std::exp(x);
    x=1/(2*x);
    return(x);
}
