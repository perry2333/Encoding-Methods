#include<stdio.h>
#include<string.h>
#include <fstream>

#include <iostream>
using namespace std;
int main()
{
	char sin[1000000]={},sout[1000000]={};
	int sum=0,i=0,j=0;
	
	ifstream in("datadata.txt", ios::in);
	if (!in.is_open())
	{
		cout << "open error!" << endl;
		exit(0);
	}
	//将数据文件数据存入数组
	while (!in.eof() && i < 999999)
	{
		in >> sin[i];
		i++;
	}
	
	//cin>>sin;
	cout<<"See the results in target_decompressed.txt"<<endl;
	for(i=0;i<999999;i++)
	{
		if(sin[i]>='0'-15&&sin[i]<='9'-15)
		{
			sout[sum]=sin[i]+15;
			sum++;
		}//解压孤立的字符数字
		else if(sin[i]>='a'+24&&sin[i]<='z'+24)
		{
			sout[sum]=sin[i]-24;
			sum++;
		}//解压孤立的字符小写字母
		else// if(sin[i]>='1'+43 &&sin[i]<='9'+43 )
		{
			for(j=0;j<sin[i+1]-43;j++)
			{
				sout[sum+j]=sout[sum-(sin[i]-43)+j];
			}
			sum+=j;
			
	/*	if(sin[i]=='C' && sin[i+1]=='C' && sin[i+2]=='f') 
			{
				sout[sum]='&';
				i+=2;
				sum++;
			}
			else
			{ */
				sout[sum]=sin[i+2];
				i+=2;
				sum++;
	//		}
		}
	}
	//	cout<<sout;
		ofstream fout("target_decompressed.txt");
		fout<<sout;


	return 0;
}