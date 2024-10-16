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
 cout<<"��������������"<<endl; Sleep(270);
 cout<<"������������ѡ���������ļ���ģʽ��"<<endl<<"����1---ģ�ⳡ��1"<<endl<<"����2---ģ�ⳡ��2"<<endl;  int select;  cin>>select; Sleep(270);
 
 if(select==1)
 {
 	cout << "ģʽһ���ã�"<<endl; 
 	fun_reader_16(select); //��ȡԭbmp�ļ������16����txt 
	fun_16_2(select);      //16������2����ת�� 
 	fun_noise(select);     //�ŵ����� 
 	fun_2_16(select);
 	fun_packaging(select);
 	fun_error_find(select);//ͳ�������ʣ��Ƚ϶����ǳɶԵ�16���������Ƚ�ʱÿ�ζ�ȡһ�����ֽ����ж�
 }
 
 if(select==2) 
 {
 	cout<< "ģʽ�����ã�"<<endl; 
 	fun_reader_16(select); //��ȡԭbmp�ļ������16����txt 
 	fun_16_2(select);      //16������2����ת�� 
 	fun_coding(select);    //��2�����ļ����� 
 	fun_noise(select);     //�ŵ����� 
 	fun_decoding(select);  //Ŀ���ļ�����һ�������Ķ������ļ��������ӦΪ�ȳ��������ļ��� 
 	fun_packaging(select);
 	fun_2_16(select);
 	fun_error_find(select);//ͳ�������ʣ��Ƚ϶����ǳɶԵ�16���������Ƚ�ʱÿ�ζ�ȡһ�����ֽ����ж�
 }
 
 //if(select==3) fun_2_16(select);
 return 0;
}
    	/*/---ʹ��˵����---///
------��Ҫ�ĳ�ʼ�ļ��У�ini.bmp �� head.txt
------ini.bmpΪԭbmpͼƬ���ļ��� 
------����ǰ׺wΪ������bmp�ļ��������ļ�������Ϊԭbmp�ļ��������ļ�
------ʹ��ǰ�������޸ĺ��Լ����ļ�����·�� 
------�ļ�����������2�����ı���ȫ����ʾbmp�ļ����ɵ�2�����ı� 16�����ı���ȫ����ʾbmp�ļ����ɵ�16�����ı� 
------����2�����ı���ȫ��Ϊ����������2�����ı�  
		*/
	
void fun_coding(int select)
{
	cout <<"2�����ļ����뺯�����ã�"<<endl; Sleep(170);
	FILE *fpins; //��ȡ������
	FILE *fpouts; //����������
	if(select==1){
	if ((fpins = fopen("D:\\Study Resourse\\�����\\�����о���ѧϰ\\��������ѧ\\�ı��ļ�\\2�����ı���ȫ��.txt", "rb")) == NULL) { cout << "the 16 file can not open!" << endl; exit(1); }
    if ((fpouts = fopen("D:\\Study Resourse\\�����\\�����о���ѧϰ\\��������ѧ\\�ı��ļ�\\����2�����ı���ȫ��.txt",  "wb")) == NULL) { cout << "the 2  file can not open!" << endl; exit(1); } }
    
    else if(select==2){
    if ((fpins = fopen("D:\\Study Resourse\\�����\\�����о���ѧϰ\\��������ѧ\\�ı��ļ�\\w2�����ı���ȫ��.txt", "rb")) == NULL) { cout << "the 16 file can not open!" << endl; exit(1); }
    if ((fpouts = fopen("D:\\Study Resourse\\�����\\�����о���ѧϰ\\��������ѧ\\�ı��ļ�\\w����2�����ı���ȫ��.txt",  "wb")) == NULL) { cout << "the 2  file can not open!" << endl; exit(1); } }
	
	int num,i,j,R[3] ;
	num = count(fpins) ;
	cout <<"�������ļ��а���"<<num<<"���ַ�"<<endl; Sleep(170);
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
    cout <<"2�����ļ����뺯�����ý�����"<<endl<<endl;
}

void fun_16_2(int select)
{	
	cout <<"16����to2���ƺ������ã�"<<endl; Sleep(270);
	FILE *fpin; //��ȡ������
	FILE *fpout; //����������
	
	if(select==1){
	if ((fpin = fopen("D:\\Study Resourse\\�����\\�����о���ѧϰ\\��������ѧ\\�ı��ļ�\\16�����ı���ȫ��.txt", "rb")) == NULL) { cout << "the 16 file can not open!" << endl; exit(1); }
    if ((fpout = fopen("D:\\Study Resourse\\�����\\�����о���ѧϰ\\��������ѧ\\�ı��ļ�\\2�����ı���ȫ��.txt",  "wb")) == NULL) { cout << "the 2  file can not open!" << endl; exit(1); } }
    
    else if(select==2){
    if ((fpin = fopen("D:\\Study Resourse\\�����\\�����о���ѧϰ\\��������ѧ\\�ı��ļ�\\w16�����ı���ȫ��.txt", "rb")) == NULL) { cout << "the 16 file can not open!" << endl; exit(1); }
    if ((fpout = fopen("D:\\Study Resourse\\�����\\�����о���ѧϰ\\��������ѧ\\�ı��ļ�\\w2�����ı���ȫ��.txt",  "wb")) == NULL) { cout << "the 2  file can not open!" << endl; exit(1); } }
    	
    int s,num;
    num = count(fpin);
    cout << "16�����ļ��а���" << num <<"���ַ�" << endl ; Sleep(170);
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
    cout <<"16����to2���ƺ������ý�����"<<endl<<endl;
}

void fun_reader_16(int select)
{
 cout << "��bmp�ļ���ȡ16�����ļ��������ã�" << endl ; Sleep(270); cout<<"���Ƿ�����˱�����������������1����������0" << endl;
 int s ; cin>>s;

 FILE *fpBmp,*head,*temp;
 BITMAPFILEHEADER bmpHeader;//�����ļ����͡���С�Ͳ��ֵ���Ϣ
 BITMAPINFOHEADER bmpInfHeader;//����λͼ�ĳߴ����ɫ��ʽ
 
    if(s==0){  
 		if ((head = fopen("D:\\Study Resourse\\�����\\�����о���ѧϰ\\��������ѧ\\�ı��ļ�\\head.txt", "rb")) == NULL){ cout << "the head file can not be open!"<< endl; exit(1);} //��head�ļ�
 		if ((temp = fopen("D:\\Study Resourse\\�����\\�����о���ѧϰ\\��������ѧ\\�ı��ļ�\\16�����ı���ȫ��.txt", "wb")) == NULL){cout << "the txt file can not be built!" << endl; exit(1);}//дTXT�ļ�
 		if ((fpBmp = fopen("D:\\Study Resourse\\�����\\�����о���ѧϰ\\��������ѧ\\ini.bmp", "rb")) == NULL){cout << "the bmp file can not be open!" << endl; exit(1);} }
 	
 	if(s==0&&select==2){
		if ((head = fopen("D:\\Study Resourse\\�����\\�����о���ѧϰ\\��������ѧ\\�ı��ļ�\\head.txt", "rb")) == NULL){ cout << "the head file can not be open!"<< endl; exit(1);} //��head�ļ�
 		if ((temp = fopen("D:\\Study Resourse\\�����\\�����о���ѧϰ\\��������ѧ\\�ı��ļ�\\w16�����ı���ȫ��.txt", "wb")) == NULL){cout << "the txt file can not be built!" << endl; exit(1);}//дTXT�ļ�
 		if ((fpBmp = fopen("D:\\Study Resourse\\�����\\�����о���ѧϰ\\��������ѧ\\ini.bmp", "rb")) == NULL){cout << "the bmp file can not be open!" << endl; exit(1);} }
 	
	if(s==1){ 
		if ((head = fopen("D:\\Study Resourse\\�����\\�����о���ѧϰ\\��������ѧ\\�ı��ļ�\\head.txt", "rb")) == NULL){ cout << "the head file can not be open!"<< endl; exit(1);} //��head�ļ�
 		if ((temp = fopen("D:\\Study Resourse\\�����\\�����о���ѧϰ\\��������ѧ\\�ı��ļ�\\���bmp16�����ı���ȫ��.txt", "wb")) == NULL){cout << "the txt file can not be built!" << endl; exit(1);}//дTXT�ļ�
 		if ((fpBmp = fopen("D:\\Study Resourse\\�����\\�����о���ѧϰ\\��������ѧ\\output_packaging.bmp", "rb")) == NULL){cout << "the bmp file can not be open!" << endl; exit(1);} }
 	
 	fread(&bmpHeader, sizeof(BITMAPFILEHEADER), 1, fpBmp);
 	fread(&bmpInfHeader, sizeof(BITMAPINFOHEADER), 1, fpBmp);

 	unsigned char *bmpData = new unsigned char[bmpInfHeader.biHeight*bmpInfHeader.biWidth];//�ڰ�ͼ��
 	fseek(fpBmp, bmpHeader.bfOffBits, SEEK_SET);
 	fread(bmpData,1,bmpInfHeader.biHeight*bmpInfHeader.biWidth,fpBmp);//�ڰ�ͼ��
	cout<<"bmp�ļ���С��"<<bmpInfHeader.biHeight<<"*"<<bmpInfHeader.biWidth<<endl; Sleep(170);
	
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
  	 		fprintf(temp,"%x",bmpData[i*bmpInfHeader.biWidth + j]);//�ڰ�ͼ��
 	 	}   }   
 	 	
 	fclose(fpBmp);  fclose(temp);  fclose(head);  
	cout <<"��bmp�ļ���ȡ16�����ļ��������ý�����"<<endl<<endl;
}

void noise1(int select)//noise0Ϊ��ģʽһ�µĶ������ı����뺯�� 
{
	cout <<"������һ�ż��뺯����"<<endl; Sleep(170);
	
	FILE *fpin; //��ȡ������
	FILE *fpout; //����������
	
	//��2�����ı���ȫ��.txt ����ȡ���С 
	if ((fpin = fopen("D:\\Study Resourse\\�����\\�����о���ѧϰ\\��������ѧ\\�ı��ļ�\\2�����ı���ȫ��.txt", "rb")) == NULL) { cout << "the target file can not open!" << endl; exit(1); }
    
	int size_ini = count(fpin); 
	int i,j,k,false_counter=0,right_counter=0;
	float rander;
	cout<<"ԭtxt�ļ���С��"<<size_ini<<endl;
	
	cout << "���������������ʣ�" ;
	cin >> rander ; 
	int num = int(float(size_ini)*rander) ;
	cout << "�������ݵ���ĿΪ��" << num << endl ; 
	
	int noise[size_ini]={0}; //�����������飬���Ϊ1��������� 
	
	int r,ave;
	ave=size_ini/num;
	for(int i=0;i<num;i++)
	{
		r=(rand()%(ave-1))+1;
	 // cout<<r<<endl;
		noise[i*ave+r]=1;
	}
	
	int data[size_ini]; //�����������飬���ڴ���ԭ�������ı���Ϣ	
		for(i=0;i<size_ini;i++)  {char ch = fgetc(fpin); data[i]=toint(ch);}  rewind(fpin);//¼�����������
		
		for(i=0;i<size_ini;i++) 
		{	if(noise[i]==1) 
			{
				data[i]=change(data[i]);
				false_counter++;
			}
			else right_counter++;
		}
	fclose(fpin); 

	//��ʾͳ�������� 
	double error =double(false_counter)/double(right_counter+false_counter) ;
	cout << "��ȷ��Ŀ��"<< right_counter<<endl<<"������Ŀ��"<<false_counter<<endl<<"ͳ�������ʣ�"<<error<<endl;
	
	//����Ϣ����д��txt�ļ�
	fpout=fopen("D:\\Study Resourse\\�����\\�����о���ѧϰ\\��������ѧ\\�ı��ļ�\\�ŵ�������2�����ı���ȫ��.txt","wb");
	for(i=0;i<size_ini;i++)
	{
		fprintf(fpout,"%d",data[i]);
	}
	
 	//�ر��ļ� 
	fclose(fpout);
}

void noise2(int select)
{
	cout <<"�����Ƕ��ż��뺯����"<<endl; Sleep(170);
	
	FILE *fpin; //��ȡ������
	FILE *fpout; //����������

	fpin=fopen("D:\\Study Resourse\\�����\\�����о���ѧϰ\\��������ѧ\\�ı��ļ�\\w����2�����ı���ȫ��.txt","rb"); //Ŀ���ļ��� 
	int size_ini = count(fpin); 
//	int size = size_ini/8;
	int i,j,k,false_counter=0,right_counter=0;
	float rander;
	cout<<"ԭtxt�ļ���С��"<<size_ini<<endl;
	
	cout << "���������������ʣ�" ;
	cin >> rander ; 
	int num = int(float(size_ini)*rander) ;
	cout << "�������ݵ���ĿΪ��" << num << endl ; 
	
	int noise[size_ini]={0}; //�����������飬���Ϊ1��������� 
	
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
	
	int data[size_ini]; //�����������飬���ڴ���ԭ�������ı���Ϣ	
		for(i=0;i<size_ini;i++)  {char ch = fgetc(fpin); data[i]=toint(ch);}  rewind(fpin);//¼�����������
		
		for(i=0;i<size_ini;i++) 
		{	if(noise[i]==1) 
			{
				data[i]=change(data[i]);
				false_counter++;
			}
			else right_counter++;
		}
	fclose(fpin); 

	//��ʾͳ�������� 
	double error =double(false_counter)/double(right_counter+false_counter) ;
	cout <<endl<<endl<< "��ȷ��Ŀ��"<< right_counter<<endl<<"������Ŀ��"<<false_counter<<endl<<"ͳ�������ʣ�"<<error<<endl;
	
	//����Ϣ����д��txt�ļ�
	fpout=fopen("D:\\Study Resourse\\�����\\�����о���ѧϰ\\��������ѧ\\�ı��ļ�\\w�ŵ������±���2�����ı���ȫ��.txt","wb");
	for(i=0;i<size_ini;i++)
	{
		if(i<size_ini-1) fprintf(fpout,"%d ",data[i]);
		else             fprintf(fpout,"%d",data[i]);
	}
	
 	//�ر��ļ� 
	fclose(fpout);
	
	//�Զ�����txt�ļ����д�� 
}

void fun_noise(int select)
{
	cout <<"���뺯�����ã�"<<endl; Sleep(270);
	if(select==1)          noise1(select);
	else if(select==2) 
	{
		noise2(select);			
	}
	
	cout <<"���뺯�����ý�����"<<endl<<endl; 
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
	cout << "���뺯�����ã�"<<endl; Sleep(170); 
	cout << "�ò�����matlab���ʵ�֣��뽫������ı��ļ�����Ϊ��"<<endl<<"����2�����ı���ȫ��.txt������������·��"<<endl;
	cout << "���ú���ǰ�������鲢�޸�Ŀ���ļ�·����������ļ�·�����м�飡"<<endl; 
	
	FILE *fpin,*fpout; //��ȡ������
	if ((fpin = fopen("D:\\Study Resourse\\�����\\�����о���ѧϰ\\��������ѧ\\�ı��ļ�\\����2�����ı���ȫ��.txt", "rb")) == NULL){ cout << "the target file can not be open!"<< endl; exit(1);} 
	else cout <<"�ļ�·����ȷ�����뺯�����ý�����"<<endl<<endl;
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
	
	fpout = fopen("D:\\Study Resourse\\�����\\�����о���ѧϰ\\��������ѧ\\�ı��ļ�\\����2�����ı���ȫ�޿ո�.txt", "wb");
	for(i=0;i<size;i++)  fprintf(fpout,"%x",str_int[i]);
	fclose(fpout);
}

int  fun_error_find(int select)
{
	cout<<"ͳ�������ʺ������ã�"<<endl; 
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
    cout<<"ͳ��������Ϊ��"<<e<<endl;
    cout<<"ͳ�������ʺ������ý�����"<<endl<<endl; 
}

void fun_2_16(int select)
{
	cout <<"2_16�������ã�����" <<endl; 
	FILE *fpin; //��ȡ������
	FILE *fpout; //����������

	if(select==1)	{fpin=fopen("D:\\Study Resourse\\�����\\�����о���ѧϰ\\��������ѧ\\�ı��ļ�\\�ŵ�������2�����ı���ȫ��.txt","rb"); //Ŀ���ļ��� 
					fpout=fopen("D:\\Study Resourse\\�����\\�����о���ѧϰ\\��������ѧ\\�ı��ļ�\\�ŵ�������16�����ı���ȫ��.txt","wb");}
	if(select==2)	{fpin=fopen("D:\\Study Resourse\\�����\\�����о���ѧϰ\\��������ѧ\\�ı��ļ�\\����2�����ı���ȫ�޿ո�.txt","rb"); //Ŀ���ļ��� 
					fpout=fopen("D:\\Study Resourse\\�����\\�����о���ѧϰ\\��������ѧ\\�ı��ļ�\\����16�����ı���ȫ��.txt","wb");}			
					
	int size = count(fpin)/4; rewind(fpin); //cout<<"�ļ���С"<< count(fpin)<<"size"<<size<<endl;
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
	cout <<"2_16�������ý���������" <<endl<<endl; 
}

void fun_packaging(int select)
{
	cout << "bmp��������{�ã�" <<endl;
	cout << "����������� Hex Editor �ֶ�ʵ��"<<endl;
	cout << "bmp��������{�ý�����" <<endl<<endl;
}
