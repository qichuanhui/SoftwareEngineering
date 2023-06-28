#include<iostream>
#include "zhongju.h"

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


int main(int argc, char* argv[])
{
	clock_t start = clock();
	if (argc < 3)//������������
	{
		cout << "��������ȷ��ָ�" << endl;
		help();
		return 0;
	}

	if (strcmp(argv[1], "-c") == 0)
	{
		/*
		���argv[2]������Ϸ������ض�Ӧ������
		������Ϸ�������-1
		*/
		int num = convert_num(argv[2]);
		if (num == -1)//argv[2]���Ϸ�
		{
			cout << "��������ȷ��ָ�" << endl;
			return 0;
		}
		else//argv[2]�Ϸ�
		{
			create_shudu(num);
		}
	}
	else if (strcmp(argv[1], "-s") == 0)
	{
		cout << "�������ָ����δʵ�֣������ڴ�" << endl;
	}
	else if (strcmp(argv[1], "-n") == 0)
	{
		cout << "������Ϸָ����δʵ�֣������ڴ�" << endl;
	}
	else//argv[1]�Ȳ���"-c"��Ҳ����"-s",Ҳ����"-n"
	{
		cout << "��������ȷ��ָ�" << endl;
		return 0;
	}
}

