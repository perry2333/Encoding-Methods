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
	for (int i = 0; i <= latter_len; i++) {                                  //�����ƥ��
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
				cout << "I'm here!!\n";                                                                    //�������
			}
			cout << "λ�ã�" << distance << endl << "ƥ�䳤�ȣ�" << match_len << endl << "ʣ���ַ�" << left_letter << endl;
			cout << "I'm here!!!\n";                                                                       //�������
			break;
		}
		cout << "λ�ã�" << distance << endl << "ƥ�䳤�ȣ�" << match_len << endl << "ʣ���ַ�"<<left_letter<< endl;
	}
	FILE* compressed_file;
	while ((compressed_file = fopen("compressed_text.txt", "a")) == NULL) {//��׷����ʽ���ļ���������׷����ʽ�����±���ʱ����ˢ��txt���ݣ�
		cout<<"�ļ���ʧ��\n";
		exit(0);
	}
	if (match_len == 0) {
		if (left_letter >= '0' and left_letter <= '9') {      //�������ַ�����-15�����
			fprintf(compressed_file,"%c", left_letter - 15);
		}
		if (left_letter >= 'a' and left_letter <= 'f') {
			fprintf(compressed_file,"%c", left_letter + 24);  //������Сд��ĸ���ϰ���24�������������25��f���ܻᱻ��ɿո񣬲��ã��ʵ���Ϊ24��
			cout << "I'm here!\n";                            //�������
		}
	}
	else {
		fprintf(compressed_file, "%c%c%c", distance+43, match_len+43, left_letter);//ʮλ����һ���ַ����
	}
	return match_len;
}
int main() {
	int a;
	a = LZ77_compresser(dic_win, search_win);
	cout << "���س��ȣ�"<<a<<endl;
	return 0;
}
