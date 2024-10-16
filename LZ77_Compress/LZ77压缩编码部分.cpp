#include<stdio.h>
#include<iostream>
#include<string>
#define front_len 4
#define latter_len 24
using namespace std;
char dic_win[front_len+1] = "37e7";
char search_win[latter_len + 1] = "67ee0012800032f804109b52";
int LZ77_compresser(char* dic_win,char* search_win) {
	int distance=0; int match_len = 0; char left_letter; int flag = 0;
	string match_m,bematched_m;
	for (int i = 0; i <= latter_len; i++) {                                  //进行最长匹配
		match_m = match_m + search_win[i];
		for (int j = match_len; j < front_len; j++) {
			for (int q = 0; q <= match_len; q++) {
				bematched_m = bematched_m + dic_win[front_len - j + q-1];
			}
			cout << match_m << "\t" << bematched_m << endl<<"j="<<j<<endl;
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
				cout << "I'm here!!\n";                                                                    //调试语句
			}
			cout << "位置：" << distance << endl << "匹配长度：" << match_len << endl << "剩余字符" << left_letter << endl;
			cout << "I'm here!!!\n";                                                                       //调试语句
			break;
		}
		cout << "位置：" << distance << endl << "匹配长度：" << match_len << endl << "剩余字符"<<left_letter<< endl;
	}
	FILE* compressed_file;
	while ((compressed_file = fopen("compressed_text.txt", "a")) == NULL) {//以追加形式打开文件（由于是追加形式，重新编译时不会刷新txt内容）
		cout<<"文件打开失败\n";
		exit(0);
	}
	if (match_len == 0) {
		if (left_letter >= '0' and left_letter <= '9') {      //孤立的字符数字-15后输出
			fprintf(compressed_file,"%c", left_letter - 15);
		}
		if (left_letter >= 'a' and left_letter <= 'f') {
			fprintf(compressed_file,"%c", left_letter + 24);  //孤立的小写字母向上搬运24后输出（若搬运25，f可能会被变成空格，不好，故调整为24）
			cout << "I'm here!\n";                            //调试语句
		}
	}
	else {
		fprintf(compressed_file, "%c%c%c", distance+43, match_len+43, left_letter);//十位数归一成字符输出
	}
	return match_len;
}
int main() {
	int a;
	a = LZ77_compresser(dic_win, search_win);
	cout << "返回长度："<<a<<endl;
	return 0;
}
