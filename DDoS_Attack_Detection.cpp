#include<bits/stdc++.h>
#include<fstream>
#include<sstream>
#include<cmath>
using namespace std;
int main(int argc, char *argv[])
{
	string line,key;
	int t=0;
	double value,mean,sum,variance,stdDeviation,H,B=300;
	map<string,int> premapper;
	ifstream myfile (argv[1]);
	cout<<"The alogrithm is run for ever 500 records in the data set."<<endl;
	cout<<"If a DDoS attack is detected the output is specified as follows"<<endl;
	cout<<"output: (Portocol, Source IP,Destination IP, Source Port, Destination Port)"<<endl;
	if (myfile.is_open())
	{
		while(getline(myfile,line) && (t<500))
		{
			stringstream lineStream(line);
			string cell;
			vector<string> result;
			while(getline(lineStream,cell,','))
				result.push_back(cell);
			if (!lineStream && cell.empty())
				result.push_back("");
			key = result[10]+","+result[11]+","+result[12]+","+result[13]+","+result[14];
			if(premapper.find(key)==premapper.end())
				premapper.insert(make_pair(key,1));
			else
				premapper[key]+=1;
			t++;
		}
		int check;
		cout << "Number of Iterations:";
		cin >> check;
		int count=0;
		while(check>0)
		{
			cout << "Iteration "<<++count<<" :"<< endl;
			t=0;
			map<string,int> mapper;
			while(getline(myfile,line) && (t<500))
			{
				stringstream lineStream(line);
				string cell;
				vector<string> result;
				while(getline(lineStream,cell,','))
					result.push_back(cell);
				if (!lineStream && cell.empty())
					result.push_back("");
				key = result[10]+","+result[11]+","+result[12]+","+result[13]+","+result[14];
				if(mapper.find(key)==mapper.end())
					mapper.insert(make_pair(key,1));
				else
					mapper[key]+=1;
				t++;
			}
			sum = 0;
			for(auto x : mapper)
				sum+=x.second;
			mean=sum/mapper.size();
			for(auto x : mapper)
				variance+=pow(x.second-mean,2);
			variance=variance/mapper.size();
			stdDeviation=sqrt(variance);
			for(auto x : mapper)
			{
				double temp;
				if(premapper.find(x.first)!=premapper.end())
				{
					temp = premapper[x.first];
					if(x.second > temp)
						H = log(temp/x.second)-log(x.second/sum);
					else
						H = log(x.second/temp)-log(x.second/sum);
					if (H> 1.5*mean)
						B++;
					if (H< 0.5*mean)
						B--;
					if(fabs(mean-H) > B*stdDeviation)
						cout << x.first<<endl;
				}
			}
			premapper = mapper;
			check--;
		}
		myfile.close();
	}
	else
		cout<<"Unable to open file";
	return 0;
}
