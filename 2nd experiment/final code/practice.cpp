#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

double min_max_nor(double val,double min,double max,double newmin,double newmax)
{
    double res=((val-min)/(max-min))*(newmax-newmin)+newmin;
    return res;
}

double z_score(double val,double mean,double sd)
{
    double res=(val-mean)/sd;
    return res;
}

vector<double>decimal_sca(vector<double>data)
{
    double max=*max_element(data.begin(),data.end());
    int n=ceil(log10(max));

    vector<double>deci;
    for(double val:data)
    {
        val=val/pow(10,n);
        deci.push_back(val);
    }
    return deci;
}
int main()
{

    ifstream input("input1.csv");

    ofstream output("out_mm.csv");
    ofstream output1("out_zs.csv");
    ofstream output2("out_deci.csv");

    //min-max normalization
    vector<double> data;
    double val;

    while(input>>val)
    {
        data.push_back(val);
    }
    for(int i=0;i<data.size();i++)
    {
        cout<<data[i]<<endl;
    }
    double min_ele=INT16_MAX;
    double max_ele=INT16_MIN;

    for(int i=0;i<data.size();i++)
    {
        min_ele=min(min_ele,data[i]);
        max_ele=max(max_ele,data[i]);
    }
    cout<<min_ele<<max_ele<<endl;

    double new_min=0.0;
    double new_max=0.0;

    cout<<"enter new min and max value"<<endl;
    cin>>new_min>>new_max;

    for(const double &val:data)
    {
        double res=min_max_nor(val,min_ele,max_ele,new_min,new_max);
        cout<<res<<endl;
        output<<res<<endl;
    }

    //z-score normalization
    double sum=0.0;
    for(int i=0;i<data.size();i++)
    {
        sum=sum+data[i];
    }
    double mean=sum/data.size();
    cout<<sum<<mean<<endl;

    double diff_sum=0.0;
    for(const double &v:data)
    {
        diff_sum=diff_sum+pow((v-mean),2);
    }

    double sd=sqrt(diff_sum/data.size());
    cout<<sd<<endl;
    for(const double &v:data)
    {
        double res=z_score(v,mean,sd);
        cout<<res<<endl;
        output1<<res<<endl;
    }
    //decimal scaling normalization

    vector<double> res_decimal;
    res_decimal=decimal_sca(data);
    for(const double &v:res_decimal)
    {
        output2<<v<<endl;
    }

    input.close();
    output.close();
    return 0;



}