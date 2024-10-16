#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <string.h>  
#include <stdio.h> 
using namespace std;
int LZ77_compresser(char* dic_win, char* search_win, FILE *compressed_file, int latter_len, int front_len);
int Min(int i, int j);
int Max(int i, int j);
//打开文件为utf8-16.txt
//压缩后输出文件为target.txt 

int main()
{
	//------------------------------------------------------------------------------------------------//	
	//---------------------------以下代码已通过调试，请勿进行修改-------------------------------------//	
	//------------------------------------------------------------------------------------------------//
	FILE *temp1, *temp2; // temp1指向要进行压缩的文件 ,temp2指向压缩后的目标文件  
	const char *fbitname = "C:\\Users\\LENOVO\\Desktop\\utf8-16.txt";//要进行压缩的文件 
	const char *fbit_changedname = "C:\\Users\\LENOVO\\Desktop\\pressed.txt";//压缩后的目标文件 

	if ((temp1 = fopen(fbitname, "rb")) == NULL) { cout << "the bmp file can not open!" << endl; exit(1); }
	//打开要进行压缩的文件

	fseek(temp1, 0, SEEK_END); int fileSize = ftell(temp1); printf("压缩前文件大小为%d\n", fileSize); Sleep(1000);
	//获取并打印要压缩的文件大小

	rewind(temp1);
	//将temp1重置到要压缩的文件头部 

	if ((temp2 = fopen(fbit_changedname, "wb")) == NULL) { cout << "the file can not be built!" << endl; exit(1); }
	//打开压缩后的目标文件 


	int match, longest, i, j, k;
	const unsigned char *buffer;
	int *offset;
	unsigned char *next;
	char ch1, ch2;
	int LZ77_WINDOW_SIZE; //窗口总大小
	int LZ77_BUFFER1_SIZE; //查找缓冲区大小
	int LZ77_BUFFER2_SIZE; //先行缓冲区大小
	//参量声明 

	int e; cout << "请输入您的模式：" << endl; Sleep(500); cout << "输入“1”采用默认窗口大小" << endl << "输入“2”自定义窗口大小" << endl; Sleep(1000);
	cin >> e;
	if (e == 1) {
		LZ77_WINDOW_SIZE = 48; LZ77_BUFFER1_SIZE = 24; LZ77_BUFFER2_SIZE = 24;
		cout << "窗口总大小：" << LZ77_WINDOW_SIZE << endl; Sleep(500); cout << "查找窗大小：" << LZ77_BUFFER1_SIZE << endl; Sleep(500); cout << "先行窗大小：" << LZ77_BUFFER2_SIZE << endl;
	}//默认窗口大小 
	else {
		if (e == 2) {
			cout << "请输入窗口总大小：" << endl; cin >> LZ77_WINDOW_SIZE;  cout << "窗口总大小：" << LZ77_WINDOW_SIZE << endl; Sleep(500);
			cout << "请输入查找窗大小：" << endl; cin >> LZ77_BUFFER1_SIZE; cout << "查找窗大小：" << LZ77_BUFFER1_SIZE << endl; Sleep(500);
			LZ77_BUFFER2_SIZE = LZ77_WINDOW_SIZE - LZ77_BUFFER1_SIZE;     cout << "先行窗大小：" << LZ77_BUFFER2_SIZE << endl; Sleep(500);
		}//自定义窗口大小
		else { cout << "输入有误，退出程序\n"; }
	}//输入有误，请重新运行程序 

	char *buffer1, *window, *buffer2;//buffer1为查找缓冲区 
	window = new char[LZ77_WINDOW_SIZE + 1];
	buffer1 = new char[LZ77_BUFFER1_SIZE + 1];
	buffer2 = new char[LZ77_BUFFER2_SIZE + 1];
	for (i = 0; i < LZ77_WINDOW_SIZE + 1; i++) { window[i] = 'f'; } for (i = 0; i < LZ77_BUFFER1_SIZE + 1; i++) { buffer1[i] = 'f'; } for (i = 0; i < LZ77_BUFFER2_SIZE + 1; i++) { buffer2[i] = 'f'; }
	//对目标范围内的元素置为字符0 实际数组长度可能大于要求数组长度 演示如下 
	//int len ;len = strlen(window);	printf("%d\n",len);printf("%c\n",window[26]);
//  cout <<"置零后window："<<endl;  puts(window) ; Sleep(200);
//	cout <<"置零后buffer1："<<endl; puts(buffer1); Sleep(200);
//	cout <<"置零后buffer2："<<endl; puts(buffer2); Sleep(200);
//------------------------------------------------------------------------------------------------//	
//---------------------------以上代码已通过调试，请勿进行修改-------------------------------------//	
//------------------------------------------------------------------------------------------------//	
	i = 0;
	while (i <= fileSize - LZ77_BUFFER1_SIZE) //变量i用来遍历filesize，i=0时，buffer1与buffer2的中间指针指向文件开头第一个字符的前面 
	{
		//    	printf("i = %d \n",i);
		if (i <= LZ77_BUFFER2_SIZE-1) {
			ch1 = fgetc(temp1);

			if (ch1 >= '0' and ch1 <= '9') {
			//	fprintf(temp2, "%c", ch1 );
				fprintf(temp2, "%c", ch1 - 15);
			}
			if (ch1 >= 'a' and ch1 <= 'f') {
			//	fprintf(temp2, "%c", ch1 );
				fprintf(temp2, "%c", ch1 + 24);
			}
			//		cout << "ch = "<< ch1<<endl;	
			i++;
		}//如果小于等于3，查找窗buffer1中最多三个元素，无需编码，直接写入目标文件 

		else//开始编码 
		{

			//变量j用于输入先行窗buffer1、查找窗buffer2与总窗window
		//	cout << "i="<<i<<endl;
		//	cout<<"buffer2:"<<endl ;
			for (j = 0; j < LZ77_BUFFER2_SIZE; j++)
			{
				ch1 = fgetc(temp1); buffer2[j] = ch1;//printf("%c",buffer2[j]);
			} //cout<<endl; //先输入先行窗buffer2并打印
			fseek(temp1, max(i - LZ77_BUFFER1_SIZE, 0), 0);	// temp1回到输入buffer1位置，准备输入buffer1 

		//	cout<<"buffer1:"<<endl ;
			for (j = 0; j < min(LZ77_BUFFER1_SIZE, i); j++)
			{
				ch1 = fgetc(temp1); buffer1[j] = ch1;//printf("%c",buffer1[j]);
			} //cout<<endl; //输入查找窗buffer1并打印 	
			fseek(temp1, max(i - LZ77_BUFFER1_SIZE, 0), 0);	//temp1回到输入buffer1位置，准备输入window 


		//	cout<<"window:"<<endl ;
			for (j = 0; j < LZ77_BUFFER2_SIZE + min(LZ77_BUFFER1_SIZE, i); j++)
			{
				ch1 = fgetc(temp1); window[j] = ch1;//printf("%c",window[j]);
			} //cout<<endl; 

			int longest = LZ77_compresser(buffer1, buffer2, temp2, LZ77_BUFFER2_SIZE, LZ77_BUFFER1_SIZE); //定义最长匹配字符长度longest，默认为1 


			i = i + longest + 1; fseek(temp1, i, 0);	//temp1默认指向下一位，即窗口整体后移1 
		}//else结束 
	}

	fclose(temp1);//关闭要进行压缩的文件
	fclose(temp2);//关闭压缩后的目标文件

	FILE *temp3;
	if ((temp3 = fopen(fbit_changedname, "r")) == NULL) { cout << "the target file can not open!" << endl; exit(1); }
	fseek(temp1, 0, SEEK_END); int fileSize_changed = ftell(temp3); printf("压缩后文件大小为%d\n", fileSize_changed); Sleep(1000);
	double rr = double(fileSize) / double(fileSize_changed);

	cout << "在查找缓冲区大小为" << LZ77_BUFFER1_SIZE
		<< ",先行缓冲区大小为" << LZ77_BUFFER1_SIZE << "时，"
		<< "文件压缩比为" << rr << endl;

	return 0;
} //主函数结束 


//下面是所用函数区，请勿改动    
int Min(int i, int j)
{
	if (i <= j) { return i; }
	else { return j; }
}

int Max(int i, int j)
{
	if (i >= j) { return i; }
	else { return j; }
}

int LZ77_compresser(char* dic_win, char* search_win, FILE *compressed_file, int latter_len, int front_len) {
	//cout << "dic_win:" << dic_win << "\nsearch_win:" << search_win << endl;
	int distance = 0; int match_len = 0; char left_letter; int flag = 0;
	string match_m, bematched_m;
	for (int i = 0; i <= latter_len; i++) {                                  //进行最长匹配
		match_m = match_m + search_win[i];
		for (int j = match_len; j < front_len; j++) {
			for (int q = 0; q <= match_len; q++) {
				bematched_m = bematched_m + dic_win[front_len - j + q - 1];
			}
			//			cout << match_m << "\t" << bematched_m << endl<<"j="<<j<<endl;
			if (bematched_m == match_m) {
				match_len++;
				distance = j + 1;
				left_letter = search_win[match_len];
				flag = 1;
				bematched_m = "";
				break;
			}
			else {
				flag = 0;
			}
			bematched_m = "";
		}

		if (flag == 0) {
			if (match_len == 0) {
				left_letter = search_win[0];
				//				cout << "I'm here!!\n";                                                                    //调试语句
			}
			//			cout << "位置：" << distance << endl << "匹配长度：" << match_len << endl << "剩余字符" << left_letter << endl;
			//			cout << "I'm here!!!\n";                                                                       //调试语句
			break;
		}
			//	cout << "位置：" << distance << endl << "匹配长度：" << match_len << endl << "剩余字符"<<left_letter<< endl;
	}

	//	FILE* compressed_file;
	//	while ((compressed_file = fopen("compressed_text.txt", "a")) == NULL) {//以追加形式打开文件（由于是追加形式，重新编译时不会刷新txt内容）
	//		cout<<"文件打开失败\n";
	//		exit(0);
	//	}
	if (match_len == 0) {
		if (left_letter >= '0' and left_letter <= '9') {      //孤立的字符数字-15后输出
		
		//	fprintf(compressed_file, "%c", left_letter );
			fprintf(compressed_file, "%c", left_letter - 15);
		}
		if (left_letter >= 'a' and left_letter <= 'f') {
			
		//	fprintf(compressed_file, "%c", left_letter );
			fprintf(compressed_file, "%c", left_letter + 24);  //孤立的小写字母向上搬运24后输出（若搬运25，f可能会被变成空格，不好，故调整为24）
//			cout << "I'm here!\n";                            //调试语句
		}
	}
	else {
	//	fprintf(compressed_file, "%c%c%c", distance , match_len , left_letter);//十位数归一成字符输出
		fprintf(compressed_file, "%c%c%c", distance + 43, match_len + 43, left_letter);//十位数归一成字符输出
		
	}
	return match_len;
}
