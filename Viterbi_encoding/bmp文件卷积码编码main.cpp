#define _CRT_SECURE_NO_WARNINGS

#include <cstdlib>
#include <string.h>  
#include <fstream> 
#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <algorithm>
#include <time.h>
#include <ctime>

using namespace std;

void fun_16_2(int select);
void fun_reader_16(int select);
void fun_coding(int select);
void fun_decoding(int select);
void fun_noise(int select);
void fun_2_16(int select);
void fun_packaging(int select);
void fun_reader_16(int select);
void noise1(int select);
void noise2(int select);
int  fun_error_find(int select);
int  fun_getc_to_int(char ch);
int  g1(int a0,int a1,int a2);
int  g2(int a0,int a1,int a2);
int  count(FILE *fpin);
int  toint(char ch);
int  change(int k);

int main()
{
 cout<<"这里是主函数！"<<endl; Sleep(270);
 cout<<"请输入数字来选择您处理文件的模式："<<endl<<"输入1---模拟场景1"<<endl<<"输入2---模拟场景2"<<endl;  int select;  cin>>select; Sleep(270);
 
 if(select==1)
 {
 	cout << "模式一启用！"<<endl; 
 	fun_reader_16(select); //读取原bmp文件并输出16进制txt 
	fun_16_2(select);      //16进制向2进制转化 
 	fun_noise(select);     //信道噪声 
 	fun_2_16(select);
 	fun_packaging(select);
 	fun_error_find(select);//统计误码率，比较对象是成对的16进制数，比较时每次读取一对数字进行判断
 }
 
 if(select==2) 
 {
 	cout<< "模式二启用！"<<endl; 
 	fun_reader_16(select); //读取原bmp文件并输出16进制txt 
 	fun_16_2(select);      //16进制向2进制转化 
 	fun_coding(select);    //对2进制文件编码 
 	fun_noise(select);     //信道噪声 
 	fun_decoding(select);  //目标文件是上一步编码后的二进制文件，译码后应为等长二进制文件。 
 	fun_packaging(select);
 	fun_2_16(select);
 	fun_error_find(select);//统计误码率，比较对象是成对的16进制数，比较时每次读取一对数字进行判断
 }
 
 //if(select==3) fun_2_16(select);
 return 0;
}
    	/*/---使用说明：---///
------需要的初始文件有：ini.bmp 、 head.txt
------ini.bmp为原bmp图片的文件名 
------带有前缀w为加噪后的bmp文件衍生的文件，否则为原bmp文件衍生的文件
------使用前请认真修改好自己的文件保存路径 
------文件名命名规则：2进制文本（全）表示bmp文件生成的2进制文本 16进制文本（全）表示bmp文件生成的16进制文本 
------编码2进制文本（全）为卷积码编码后的2进制文本  
		*/
	
void fun_coding(int select)
{
	cout <<"2进制文件编码函数调用！"<<endl; Sleep(170);
	FILE *fpins; //读取操作流
	FILE *fpouts; //读出操作流
	if(select==1){
	if ((fpins = fopen("D:\\Study Resourse\\大二下\\信论研究型学习\\第四章研学\\文本文件\\2进制文本（全）.txt", "rb")) == NULL) { cout << "the 16 file can not open!" << endl; exit(1); }
    if ((fpouts = fopen("D:\\Study Resourse\\大二下\\信论研究型学习\\第四章研学\\文本文件\\编码2进制文本（全）.txt",  "wb")) == NULL) { cout << "the 2  file can not open!" << endl; exit(1); } }
    
    else if(select==2){
    if ((fpins = fopen("D:\\Study Resourse\\大二下\\信论研究型学习\\第四章研学\\文本文件\\w2进制文本（全）.txt", "rb")) == NULL) { cout << "the 16 file can not open!" << endl; exit(1); }
    if ((fpouts = fopen("D:\\Study Resourse\\大二下\\信论研究型学习\\第四章研学\\文本文件\\w编码2进制文本（全）.txt",  "wb")) == NULL) { cout << "the 2  file can not open!" << endl; exit(1); } }
	
	int num,i,j,R[3] ;
	num = count(fpins) ;
	cout <<"二进制文件中包含"<<num<<"个字符"<<endl; Sleep(170);
	rewind(fpins);
	for(i=0;i<3;i++) R[i]=0;
	
	for(i=0;i<num;i++)
	{
		int x1,x2;
		R[2]=R[1];
		R[1]=R[0];
		char R0 = fgetc(fpins);
		R[0]= fun_getc_to_int(R0);
		
		x1 = g1(R[0],R[1],R[2]);
		x2 = g2(R[0],R[1],R[2]);
		
		fprintf(fpouts,"%d",x1);
		fprintf(fpouts,"%d",x2);
	}
	
	fclose(fpins);
    fclose(fpouts);
    cout <<"2进制文件编码函数调用结束！"<<endl<<endl;
}

void fun_16_2(int select)
{	
	cout <<"16进制to2进制函数调用！"<<endl; Sleep(270);
	FILE *fpin; //读取操作流
	FILE *fpout; //读出操作流
	
	if(select==1){
	if ((fpin = fopen("D:\\Study Resourse\\大二下\\信论研究型学习\\第四章研学\\文本文件\\16进制文本（全）.txt", "rb")) == NULL) { cout << "the 16 file can not open!" << endl; exit(1); }
    if ((fpout = fopen("D:\\Study Resourse\\大二下\\信论研究型学习\\第四章研学\\文本文件\\2进制文本（全）.txt",  "wb")) == NULL) { cout << "the 2  file can not open!" << endl; exit(1); } }
    
    else if(select==2){
    if ((fpin = fopen("D:\\Study Resourse\\大二下\\信论研究型学习\\第四章研学\\文本文件\\w16进制文本（全）.txt", "rb")) == NULL) { cout << "the 16 file can not open!" << endl; exit(1); }
    if ((fpout = fopen("D:\\Study Resourse\\大二下\\信论研究型学习\\第四章研学\\文本文件\\w2进制文本（全）.txt",  "wb")) == NULL) { cout << "the 2  file can not open!" << endl; exit(1); } }
    	
    int s,num;
    num = count(fpin);
    cout << "16进制文件中包含" << num <<"个字符" << endl ; Sleep(170);
    rewind(fpin); 
    
    for(s=0;s<num;s++)
        {
		 char ch;
		 ch = fgetc(fpin); 
		 int x = toint(ch);
         
         int a,b,c,d,i,j; 
    	 a = x / 8; fprintf(fpout,"%d",a); i = x % 8 ;
   		 b = i / 4; fprintf(fpout,"%d",b); i = x % 4 ;
    	 c = i / 2; fprintf(fpout,"%d",c); i = x % 2 ;
    	 d = i; fprintf(fpout,"%d",d);
		}
    
	fclose(fpin);
    fclose(fpout);
    cout <<"16进制to2进制函数调用结束！"<<endl<<endl;
}

void fun_reader_16(int select)
{
 cout << "由bmp文件读取16进制文件函数调用！" << endl ; Sleep(270); cout<<"您是否完成了编译码任务？是请输入1，否请输入0" << endl;
 int s ; cin>>s;

 FILE *fpBmp,*head,*temp;
 BITMAPFILEHEADER bmpHeader;//包含文件类型、大小和布局的信息
 BITMAPINFOHEADER bmpInfHeader;//包含位图的尺寸和颜色格式
 
    if(s==0){  
 		if ((head = fopen("D:\\Study Resourse\\大二下\\信论研究型学习\\第四章研学\\文本文件\\head.txt", "rb")) == NULL){ cout << "the head file can not be open!"<< endl; exit(1);} //读head文件
 		if ((temp = fopen("D:\\Study Resourse\\大二下\\信论研究型学习\\第四章研学\\文本文件\\16进制文本（全）.txt", "wb")) == NULL){cout << "the txt file can not be built!" << endl; exit(1);}//写TXT文件
 		if ((fpBmp = fopen("D:\\Study Resourse\\大二下\\信论研究型学习\\第四章研学\\ini.bmp", "rb")) == NULL){cout << "the bmp file can not be open!" << endl; exit(1);} }
 	
 	if(s==0&&select==2){
		if ((head = fopen("D:\\Study Resourse\\大二下\\信论研究型学习\\第四章研学\\文本文件\\head.txt", "rb")) == NULL){ cout << "the head file can not be open!"<< endl; exit(1);} //读head文件
 		if ((temp = fopen("D:\\Study Resourse\\大二下\\信论研究型学习\\第四章研学\\文本文件\\w16进制文本（全）.txt", "wb")) == NULL){cout << "the txt file can not be built!" << endl; exit(1);}//写TXT文件
 		if ((fpBmp = fopen("D:\\Study Resourse\\大二下\\信论研究型学习\\第四章研学\\ini.bmp", "rb")) == NULL){cout << "the bmp file can not be open!" << endl; exit(1);} }
 	
	if(s==1){ 
		if ((head = fopen("D:\\Study Resourse\\大二下\\信论研究型学习\\第四章研学\\文本文件\\head.txt", "rb")) == NULL){ cout << "the head file can not be open!"<< endl; exit(1);} //读head文件
 		if ((temp = fopen("D:\\Study Resourse\\大二下\\信论研究型学习\\第四章研学\\文本文件\\打包bmp16进制文本（全）.txt", "wb")) == NULL){cout << "the txt file can not be built!" << endl; exit(1);}//写TXT文件
 		if ((fpBmp = fopen("D:\\Study Resourse\\大二下\\信论研究型学习\\第四章研学\\output_packaging.bmp", "rb")) == NULL){cout << "the bmp file can not be open!" << endl; exit(1);} }
 	
 	fread(&bmpHeader, sizeof(BITMAPFILEHEADER), 1, fpBmp);
 	fread(&bmpInfHeader, sizeof(BITMAPINFOHEADER), 1, fpBmp);

 	unsigned char *bmpData = new unsigned char[bmpInfHeader.biHeight*bmpInfHeader.biWidth];//黑白图像
 	fseek(fpBmp, bmpHeader.bfOffBits, SEEK_SET);
 	fread(bmpData,1,bmpInfHeader.biHeight*bmpInfHeader.biWidth,fpBmp);//黑白图像
	cout<<"bmp文件大小："<<bmpInfHeader.biHeight<<"*"<<bmpInfHeader.biWidth<<endl; Sleep(170);
	
 	bmpInfHeader.biHeight = bmpInfHeader.biHeight / 4 ;
 	bmpInfHeader.biWidth = bmpInfHeader.biWidth / 2 ;
    
	int num = count(head); 
	rewind(head);
 	int i,j;
 	for(i=0;i<num;i++)
 	{
 		char ch;
	 	ch = fgetc(head); //cout <<ch;
	 	fprintf(temp,"%c",ch);
 	}
 
 	for (i = 0; i < bmpInfHeader.biHeight; i++)
 	{	for (j = 0; j < bmpInfHeader.biWidth; j++)
 		{
  	 		if(bmpData[i*bmpInfHeader.biWidth + j]<=15) {int r = 0 ; fprintf(temp,"%d",r);}
  	 		fprintf(temp,"%x",bmpData[i*bmpInfHeader.biWidth + j]);//黑白图像
 	 	}   }   
 	 	
 	fclose(fpBmp);  fclose(temp);  fclose(head);  
	cout <<"由bmp文件读取16进制文件函数调用结束！"<<endl<<endl;
}

void noise1(int select)//noise0为对模式一下的二进制文本加噪函数 
{
	cout <<"这里是一号加噪函数！"<<endl; Sleep(170);
	
	FILE *fpin; //读取操作流
	FILE *fpout; //读出操作流
	
	//打开2进制文本（全）.txt 并读取其大小 
	if ((fpin = fopen("D:\\Study Resourse\\大二下\\信论研究型学习\\第四章研学\\文本文件\\2进制文本（全）.txt", "rb")) == NULL) { cout << "the target file can not open!" << endl; exit(1); }
    
	int size_ini = count(fpin); 
	int i,j,k,false_counter=0,right_counter=0;
	float rander;
	cout<<"原txt文件大小："<<size_ini<<endl;
	
	cout << "请输入噪声误码率：" ;
	cin >> rander ; 
	int num = int(float(size_ini)*rander) ;
	cout << "错误数据点数目为：" << num << endl ; 
	
	int noise[size_ini]={0}; //生成噪声数组，标记为1则异或运算 
	
	int r,ave;
	ave=size_ini/num;
	for(int i=0;i<num;i++)
	{
		r=(rand()%(ave-1))+1;
	 // cout<<r<<endl;
		noise[i*ave+r]=1;
	}
	
	int data[size_ini]; //生成数据数组，用于储存原二进制文本信息	
		for(i=0;i<size_ini;i++)  {char ch = fgetc(fpin); data[i]=toint(ch);}  rewind(fpin);//录入二进制序列
		
		for(i=0;i<size_ini;i++) 
		{	if(noise[i]==1) 
			{
				data[i]=change(data[i]);
				false_counter++;
			}
			else right_counter++;
		}
	fclose(fpin); 

	//显示统计误码率 
	double error =double(false_counter)/double(right_counter+false_counter) ;
	cout << "正确数目："<< right_counter<<endl<<"错误数目："<<false_counter<<endl<<"统计误码率："<<error<<endl;
	
	//将信息重新写入txt文件
	fpout=fopen("D:\\Study Resourse\\大二下\\信论研究型学习\\第四章研学\\文本文件\\信道噪声下2进制文本（全）.txt","wb");
	for(i=0;i<size_ini;i++)
	{
		fprintf(fpout,"%d",data[i]);
	}
	
 	//关闭文件 
	fclose(fpout);
}

void noise2(int select)
{
	cout <<"这里是二号加噪函数！"<<endl; Sleep(170);
	
	FILE *fpin; //读取操作流
	FILE *fpout; //读出操作流

	fpin=fopen("D:\\Study Resourse\\大二下\\信论研究型学习\\第四章研学\\文本文件\\w编码2进制文本（全）.txt","rb"); //目标文件名 
	int size_ini = count(fpin); 
//	int size = size_ini/8;
	int i,j,k,false_counter=0,right_counter=0;
	float rander;
	cout<<"原txt文件大小："<<size_ini<<endl;
	
	cout << "请输入噪声误码率：" ;
	cin >> rander ; 
	int num = int(float(size_ini)*rander) ;
	cout << "错误数据点数目为：" << num << endl ; 
	
	int noise[size_ini]={0}; //生成噪声数组，标记为1则异或运算 
	
	int r,ave;
	ave=size_ini/num;
	for(int i=0;i<num;i++)
	{
		r=(rand()%(ave-1))+1;
	 // cout<<r<<endl;
		noise[i*ave+r]=1;
	}
	
//	for(i=0;i<size_ini;i++) {cout << noise[i];}
		
	rewind(fpin);
	
	int data[size_ini]; //生成数据数组，用于储存原二进制文本信息	
		for(i=0;i<size_ini;i++)  {char ch = fgetc(fpin); data[i]=toint(ch);}  rewind(fpin);//录入二进制序列
		
		for(i=0;i<size_ini;i++) 
		{	if(noise[i]==1) 
			{
				data[i]=change(data[i]);
				false_counter++;
			}
			else right_counter++;
		}
	fclose(fpin); 

	//显示统计误码率 
	double error =double(false_counter)/double(right_counter+false_counter) ;
	cout <<endl<<endl<< "正确数目："<< right_counter<<endl<<"错误数目："<<false_counter<<endl<<"统计误码率："<<error<<endl;
	
	//将信息重新写入txt文件
	fpout=fopen("D:\\Study Resourse\\大二下\\信论研究型学习\\第四章研学\\文本文件\\w信道噪声下编码2进制文本（全）.txt","wb");
	for(i=0;i<size_ini;i++)
	{
		if(i<size_ini-1) fprintf(fpout,"%d ",data[i]);
		else             fprintf(fpout,"%d",data[i]);
	}
	
 	//关闭文件 
	fclose(fpout);
	
	//对二进制txt文件进行打包 
}

void fun_noise(int select)
{
	cout <<"加噪函数调用！"<<endl; Sleep(270);
	if(select==1)          noise1(select);
	else if(select==2) 
	{
		noise2(select);			
	}
	
	cout <<"加噪函数调用结束！"<<endl<<endl; 
}

int count(FILE *fpin)
{
	int i = 0 ;
	while(fgetc(fpin)!=EOF)
	{
		i++	;
	}
	return i ;
}

int toint(char ch)
{
	if(ch=='a'||ch=='b'||ch=='c'||ch=='d'||ch=='e'||ch=='f') return int(ch)-87;
	else return int(ch)-48;
}
int g1(int a0,int a1,int a2)
{
	if(a0+a2==1) return 1;
	else         return 0;	
}

int g2(int a0,int a1,int a2)
{
	if(a0+a1+a2==1||a0+a1+a2==3)  return 1;
	else                          return 0;	
}

int fun_getc_to_int(char ch)
{	
	int x = int(ch);
	return x-48 ;
}

int change(int k)
{
	if(k==0) return 1;
	else if(k==1) return 0;
	else {
		cout <<"noise_fun error!"<<endl; exit(0); return 0; 
	}
}

void fun_decoding(int select)
{
	cout << "译码函数调用！"<<endl; Sleep(170); 
	cout << "该部分由matlab软件实现，请将输出的文本文件命名为："<<endl<<"译码2进制文本（全）.txt并保存至合理路径"<<endl;
	cout << "调用函数前请认真检查并修改目标文件路径！下面对文件路径进行检查！"<<endl; 
	
	FILE *fpin,*fpout; //读取操作流
	if ((fpin = fopen("D:\\Study Resourse\\大二下\\信论研究型学习\\第四章研学\\文本文件\\译码2进制文本（全）.txt", "rb")) == NULL){ cout << "the target file can not be open!"<< endl; exit(1);} 
	else cout <<"文件路径正确！译码函数调用结束！"<<endl<<endl;
	int size = count(fpin);
	size = (size+1)/2 ; cout <<"size="<<size<<endl; rewind(fpin);
	int i,str_int[size];
	for(i=0;i<size;i++)
	{
		char ch = fgetc(fpin);
		int s =toint(ch);//cout<<s;
		ch = fgetc(fpin);
		str_int[i]=s;
	}
	rewind(fpin);
	fclose(fpin);
	
	fpout = fopen("D:\\Study Resourse\\大二下\\信论研究型学习\\第四章研学\\文本文件\\译码2进制文本（全无空格）.txt", "wb");
	for(i=0;i<size;i++)  fprintf(fpout,"%x",str_int[i]);
	fclose(fpout);
}

int  fun_error_find(int select)
{
	cout<<"统计误码率函数调用！"<<endl; 
    char s1[1000000]={},s2[1000000]={};
    string filename;
    int i=0,i1=0,i2=0,sum=0;
    float e=0;

    cout<<"Please input the name of your original file"<<endl;
    cin>>filename;

    ifstream fin1(filename.c_str());
    while(fin1.fail())
    {
        cout<<"Failed to open! Please input again!"<<endl;
        cin>>filename;
        fin1.open(filename.c_str());
    }
    while(!fin1.eof())
    {
        fin1>>s1[i1];
        i1++;
    }

    cout<<"Please input the name of your file you want to comapare with the oringinal"<<endl;
    cin>>filename;
    ifstream fin2(filename.c_str());
    while(fin2.fail())
    {
        cout<<"Failed to open! Please input again!"<<endl;
        cin>>filename;
        fin2.open(filename.c_str());
    }
    while(!fin2.eof())  
    {
        fin2>>s2[i2];
        i2++;
    }

    for(i=0;i<i1;i++)
    {
        if(s1[i]!=s2[i]) sum++;
    }
    e=(float)sum/(float)i1;
    cout<<"统计误码率为："<<e<<endl;
    cout<<"统计误码率函数调用结束！"<<endl<<endl; 
}

void fun_2_16(int select)
{
	cout <<"2_16函数调用！！！" <<endl; 
	FILE *fpin; //读取操作流
	FILE *fpout; //读出操作流

	if(select==1)	{fpin=fopen("D:\\Study Resourse\\大二下\\信论研究型学习\\第四章研学\\文本文件\\信道噪声下2进制文本（全）.txt","rb"); //目标文件名 
					fpout=fopen("D:\\Study Resourse\\大二下\\信论研究型学习\\第四章研学\\文本文件\\信道噪声下16进制文本（全）.txt","wb");}
	if(select==2)	{fpin=fopen("D:\\Study Resourse\\大二下\\信论研究型学习\\第四章研学\\文本文件\\译码2进制文本（全无空格）.txt","rb"); //目标文件名 
					fpout=fopen("D:\\Study Resourse\\大二下\\信论研究型学习\\第四章研学\\文本文件\\译码16进制文本（全）.txt","wb");}			
					
	int size = count(fpin)/4; rewind(fpin); //cout<<"文件大小"<< count(fpin)<<"size"<<size<<endl;
	int a,b,c,d,i;
	int str_int[size];
	int sum=0;
	for(i=0;i<size;i++)
	{
		char ch;
		ch = fgetc(fpin); a = toint(ch);
		ch = fgetc(fpin); b = toint(ch);
		ch = fgetc(fpin); c = toint(ch);
		ch = fgetc(fpin); d = toint(ch);
		
		int s = 8*a+4*b+2*c+d;
		str_int[i]=s;
		sum++;
	}
	fclose(fpin);

	for(i=0;i<size;i++)
	{
		fprintf(fpout,"%x",str_int[i]);
	}
	fclose(fpout);
	cout <<"2_16函数调用结束！！！" <<endl<<endl; 
}

void fun_packaging(int select)
{
	cout << "bmp打包函數調用！" <<endl;
	cout << "本函数由软件 Hex Editor 手动实现"<<endl;
	cout << "bmp打包函數調用结束！" <<endl<<endl;
}
