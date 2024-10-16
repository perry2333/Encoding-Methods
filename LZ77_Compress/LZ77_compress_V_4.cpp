#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <string.h>  
#include <stdio.h> 
using namespace std;
int LZ77_compresser(char* dic_win, char* search_win, FILE *compressed_file, int latter_len, int front_len);
int Min(int i, int j);
int Max(int i, int j);
//���ļ�Ϊutf8-16.txt
//ѹ��������ļ�Ϊtarget.txt 

int main()
{
	//------------------------------------------------------------------------------------------------//	
	//---------------------------���´�����ͨ�����ԣ���������޸�-------------------------------------//	
	//------------------------------------------------------------------------------------------------//
	FILE *temp1, *temp2; // temp1ָ��Ҫ����ѹ�����ļ� ,temp2ָ��ѹ�����Ŀ���ļ�  
	const char *fbitname = "C:\\Users\\LENOVO\\Desktop\\utf8-16.txt";//Ҫ����ѹ�����ļ� 
	const char *fbit_changedname = "C:\\Users\\LENOVO\\Desktop\\pressed.txt";//ѹ�����Ŀ���ļ� 

	if ((temp1 = fopen(fbitname, "rb")) == NULL) { cout << "the bmp file can not open!" << endl; exit(1); }
	//��Ҫ����ѹ�����ļ�

	fseek(temp1, 0, SEEK_END); int fileSize = ftell(temp1); printf("ѹ��ǰ�ļ���СΪ%d\n", fileSize); Sleep(1000);
	//��ȡ����ӡҪѹ�����ļ���С

	rewind(temp1);
	//��temp1���õ�Ҫѹ�����ļ�ͷ�� 

	if ((temp2 = fopen(fbit_changedname, "wb")) == NULL) { cout << "the file can not be built!" << endl; exit(1); }
	//��ѹ�����Ŀ���ļ� 


	int match, longest, i, j, k;
	const unsigned char *buffer;
	int *offset;
	unsigned char *next;
	char ch1, ch2;
	int LZ77_WINDOW_SIZE; //�����ܴ�С
	int LZ77_BUFFER1_SIZE; //���һ�������С
	int LZ77_BUFFER2_SIZE; //���л�������С
	//�������� 

	int e; cout << "����������ģʽ��" << endl; Sleep(500); cout << "���롰1������Ĭ�ϴ��ڴ�С" << endl << "���롰2���Զ��崰�ڴ�С" << endl; Sleep(1000);
	cin >> e;
	if (e == 1) {
		LZ77_WINDOW_SIZE = 48; LZ77_BUFFER1_SIZE = 24; LZ77_BUFFER2_SIZE = 24;
		cout << "�����ܴ�С��" << LZ77_WINDOW_SIZE << endl; Sleep(500); cout << "���Ҵ���С��" << LZ77_BUFFER1_SIZE << endl; Sleep(500); cout << "���д���С��" << LZ77_BUFFER2_SIZE << endl;
	}//Ĭ�ϴ��ڴ�С 
	else {
		if (e == 2) {
			cout << "�����봰���ܴ�С��" << endl; cin >> LZ77_WINDOW_SIZE;  cout << "�����ܴ�С��" << LZ77_WINDOW_SIZE << endl; Sleep(500);
			cout << "��������Ҵ���С��" << endl; cin >> LZ77_BUFFER1_SIZE; cout << "���Ҵ���С��" << LZ77_BUFFER1_SIZE << endl; Sleep(500);
			LZ77_BUFFER2_SIZE = LZ77_WINDOW_SIZE - LZ77_BUFFER1_SIZE;     cout << "���д���С��" << LZ77_BUFFER2_SIZE << endl; Sleep(500);
		}//�Զ��崰�ڴ�С
		else { cout << "���������˳�����\n"; }
	}//�����������������г��� 

	char *buffer1, *window, *buffer2;//buffer1Ϊ���һ����� 
	window = new char[LZ77_WINDOW_SIZE + 1];
	buffer1 = new char[LZ77_BUFFER1_SIZE + 1];
	buffer2 = new char[LZ77_BUFFER2_SIZE + 1];
	for (i = 0; i < LZ77_WINDOW_SIZE + 1; i++) { window[i] = 'f'; } for (i = 0; i < LZ77_BUFFER1_SIZE + 1; i++) { buffer1[i] = 'f'; } for (i = 0; i < LZ77_BUFFER2_SIZE + 1; i++) { buffer2[i] = 'f'; }
	//��Ŀ�귶Χ�ڵ�Ԫ����Ϊ�ַ�0 ʵ�����鳤�ȿ��ܴ���Ҫ�����鳤�� ��ʾ���� 
	//int len ;len = strlen(window);	printf("%d\n",len);printf("%c\n",window[26]);
//  cout <<"�����window��"<<endl;  puts(window) ; Sleep(200);
//	cout <<"�����buffer1��"<<endl; puts(buffer1); Sleep(200);
//	cout <<"�����buffer2��"<<endl; puts(buffer2); Sleep(200);
//------------------------------------------------------------------------------------------------//	
//---------------------------���ϴ�����ͨ�����ԣ���������޸�-------------------------------------//	
//------------------------------------------------------------------------------------------------//	
	i = 0;
	while (i <= fileSize - LZ77_BUFFER1_SIZE) //����i��������filesize��i=0ʱ��buffer1��buffer2���м�ָ��ָ���ļ���ͷ��һ���ַ���ǰ�� 
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
		}//���С�ڵ���3�����Ҵ�buffer1���������Ԫ�أ�������룬ֱ��д��Ŀ���ļ� 

		else//��ʼ���� 
		{

			//����j�����������д�buffer1�����Ҵ�buffer2���ܴ�window
		//	cout << "i="<<i<<endl;
		//	cout<<"buffer2:"<<endl ;
			for (j = 0; j < LZ77_BUFFER2_SIZE; j++)
			{
				ch1 = fgetc(temp1); buffer2[j] = ch1;//printf("%c",buffer2[j]);
			} //cout<<endl; //���������д�buffer2����ӡ
			fseek(temp1, max(i - LZ77_BUFFER1_SIZE, 0), 0);	// temp1�ص�����buffer1λ�ã�׼������buffer1 

		//	cout<<"buffer1:"<<endl ;
			for (j = 0; j < min(LZ77_BUFFER1_SIZE, i); j++)
			{
				ch1 = fgetc(temp1); buffer1[j] = ch1;//printf("%c",buffer1[j]);
			} //cout<<endl; //������Ҵ�buffer1����ӡ 	
			fseek(temp1, max(i - LZ77_BUFFER1_SIZE, 0), 0);	//temp1�ص�����buffer1λ�ã�׼������window 


		//	cout<<"window:"<<endl ;
			for (j = 0; j < LZ77_BUFFER2_SIZE + min(LZ77_BUFFER1_SIZE, i); j++)
			{
				ch1 = fgetc(temp1); window[j] = ch1;//printf("%c",window[j]);
			} //cout<<endl; 

			int longest = LZ77_compresser(buffer1, buffer2, temp2, LZ77_BUFFER2_SIZE, LZ77_BUFFER1_SIZE); //�����ƥ���ַ�����longest��Ĭ��Ϊ1 


			i = i + longest + 1; fseek(temp1, i, 0);	//temp1Ĭ��ָ����һλ���������������1 
		}//else���� 
	}

	fclose(temp1);//�ر�Ҫ����ѹ�����ļ�
	fclose(temp2);//�ر�ѹ�����Ŀ���ļ�

	FILE *temp3;
	if ((temp3 = fopen(fbit_changedname, "r")) == NULL) { cout << "the target file can not open!" << endl; exit(1); }
	fseek(temp1, 0, SEEK_END); int fileSize_changed = ftell(temp3); printf("ѹ�����ļ���СΪ%d\n", fileSize_changed); Sleep(1000);
	double rr = double(fileSize) / double(fileSize_changed);

	cout << "�ڲ��һ�������СΪ" << LZ77_BUFFER1_SIZE
		<< ",���л�������СΪ" << LZ77_BUFFER1_SIZE << "ʱ��"
		<< "�ļ�ѹ����Ϊ" << rr << endl;

	return 0;
} //���������� 


//���������ú�����������Ķ�    
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
	for (int i = 0; i <= latter_len; i++) {                                  //�����ƥ��
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
				//				cout << "I'm here!!\n";                                                                    //�������
			}
			//			cout << "λ�ã�" << distance << endl << "ƥ�䳤�ȣ�" << match_len << endl << "ʣ���ַ�" << left_letter << endl;
			//			cout << "I'm here!!!\n";                                                                       //�������
			break;
		}
			//	cout << "λ�ã�" << distance << endl << "ƥ�䳤�ȣ�" << match_len << endl << "ʣ���ַ�"<<left_letter<< endl;
	}

	//	FILE* compressed_file;
	//	while ((compressed_file = fopen("compressed_text.txt", "a")) == NULL) {//��׷����ʽ���ļ���������׷����ʽ�����±���ʱ����ˢ��txt���ݣ�
	//		cout<<"�ļ���ʧ��\n";
	//		exit(0);
	//	}
	if (match_len == 0) {
		if (left_letter >= '0' and left_letter <= '9') {      //�������ַ�����-15�����
		
		//	fprintf(compressed_file, "%c", left_letter );
			fprintf(compressed_file, "%c", left_letter - 15);
		}
		if (left_letter >= 'a' and left_letter <= 'f') {
			
		//	fprintf(compressed_file, "%c", left_letter );
			fprintf(compressed_file, "%c", left_letter + 24);  //������Сд��ĸ���ϰ���24�������������25��f���ܻᱻ��ɿո񣬲��ã��ʵ���Ϊ24��
//			cout << "I'm here!\n";                            //�������
		}
	}
	else {
	//	fprintf(compressed_file, "%c%c%c", distance , match_len , left_letter);//ʮλ����һ���ַ����
		fprintf(compressed_file, "%c%c%c", distance + 43, match_len + 43, left_letter);//ʮλ����һ���ַ����
		
	}
	return match_len;
}
