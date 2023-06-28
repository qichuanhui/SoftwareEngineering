#include<iostream>
#include "zhongju.h"
#include "qiujie.h"
#include "youxi.h"
using namespace std;

/*
��������������
*/

void help()
{

}
int convert_num(char* s)
{
	/*�����������תΪint��*/
	int len = strlen(s);
	if (len >= 7 && strcmp(s, "1000000"))//����1e6�������Ƿ�
		return -1;
	else if (s[0] == '0')//0��ǰ׺0�Ƿ�
		return -1;
	int num = 0;
	for (int i = 0; i < len; i++)
	{
		if (!isdigit(s[i]))//�������ַ��Ƿ�
			return -1;
		else   num = num * 10 + s[i] - '0';
	}
	return num;
}
int find_min(char* s)
{
	/*����С�ڶ�����תΪint��*/
	int len = strlen(s);
	if (s[0] == '0')//0��ǰ׺0�Ƿ�
		return -1;
	int num = 0;
	for (int i = 0; i < len; i++)
	{
		if (s[i] == '-')break;
		else if (!isdigit(s[i]))//�������ַ��Ƿ�
			return -1;
		else   num = num * 10 + s[i] - '0';
	}
	return num;
}
int find_max(char* s)
{
	/*������ڶ�����תΪint��*/
	int i;
	int len = strlen(s);
	for (i = 0; i < len; i++)
	{
		if (s[i] == '-')
		{
			i++;
			break;
		}
	}
	if (s[i] == '0')//0��ǰ׺0�Ƿ�
		return -1;
	int num = 0;
	for (; i < len; i++)
	{
		if (!isdigit(s[i]))//�������ַ��Ƿ�
			return -1;
		else   num = num * 10 + s[i] - '0';
	}
	return num;
}
int main(int argc, char* argv[])
{
	clock_t start = clock();
	if (argc < 3)//������������
	{
		cout << "��������ȷ��ָ�" << endl;
		help();
		return 0;
	}

	if (strcmp(argv[1], "-c") == 0)//�����վ�
	{	
		if (argc != 3)//������������
		{
			cout << "-c�������Ϊ�վָ���" << endl;
			help();
			return 0;
		}
		//���argv[2]������Ϸ������ض�Ӧ������������Ϸ�������-1
		int num = convert_num(argv[2]);
		if (num == -1)//argv[2]���Ϸ�
		{
			cout << "�������Ϸ���-c�����Ϊ�վָ���,��Χ1-1000000" << endl;
			return 0;
		}
		else//argv[2]�Ϸ�
		{
			if (create_shudu(num))
			{
				cout << "���������վֳɹ�" << endl;
			}
		}
	}
	else if (strcmp(argv[1], "-s") == 0)//������
	{
		if (argc != 3)//������������
		{
			cout << "-s�������Ϊ����·��" << endl;
			help();
			return 0;
		}
		solve_shudu(argv[2]);
	}
	else if (strcmp(argv[1], "-n") == 0)//����������Ϸ
	{
		int level = 0;//�Ѷ�
		int minhole = 0;//��С����
		int maxhole = 0;//������
		bool only = false;
		int num = convert_num(argv[2]);
		if (num < 0 || num>10000)
		{
			cout << "�������Ϸ���-n�����Ϊ��Ϸ����,��Χ1-10000" << endl;
			return 0;
		}
		if (argc > 3)
		{
			if (strcmp(argv[3], "-m") == 0)//��Ϸ�Ѷ�
			{
				level = convert_num(argv[4]);
				if (level <1||level>3)//argv[4]���Ϸ�
				{
					cout << "�Ѷ�ѡ����󣬽���1-3�����Ѷ�" << endl;
					return 0;
				}
			}
			else if (strcmp(argv[3], "-r") == 0)//��Ϸ�ڿ���
			{
				minhole = find_min(argv[4]);
				maxhole = find_max(argv[4]);
				if (maxhole==-1||minhole < 20 || maxhole>55 || minhole > maxhole)
				{
					cout << "���������ڶ�������ΧΪ20-55" << endl;
					return 0;
				}
			}
			else if (strcmp(argv[3], "-u") == 0)//��Ϸ��Ψһ
			{
				only = true;
			}
		}
		if (argc > 5)
		{
			if (strcmp(argv[3], "-m") == 0)//��Ϸ�Ѷ�
			{
				level = convert_num(argv[4]);
				if (level < 1 || level>3)//argv[4]���Ϸ�
				{
					cout << "�Ѷ�ѡ����󣬽���1-3�����Ѷ�" << endl;
					return 0;
				}
			}
			if (strcmp(argv[3], "-r") == 0)//��Ϸ�ڿ���
			{
				minhole = find_min(argv[4]);
				maxhole = find_max(argv[4]);
			}
		}
		create_game(num, level , minhole , maxhole, only);
	}
	else//argv[1]�Ȳ���"-c"��Ҳ����"-s",Ҳ����"-n"
	{
		cout << "��������ȷ��ָ�" << endl;
		return 0;
	}
}

