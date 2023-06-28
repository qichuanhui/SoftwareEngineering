#include"qiujie.h"

static char buffer[165000000];//����ַ���������
static int pos;//����ַ����ĵ�ǰд��λ��

int map[9][9];
bool flag;//�����ϱ�־
int tag[9][9] =
{
	{0, 0, 0, 1, 1, 1, 2, 2, 2},
	{0, 0, 0, 1, 1, 1, 2, 2, 2},
	{0, 0, 0, 1, 1, 1, 2, 2, 2},
	{3, 3, 3, 4, 4, 4, 5, 5, 5},
	{3, 3, 3, 4, 4, 4, 5, 5, 5},
	{3, 3, 3, 4, 4, 4, 5, 5, 5},
	{6, 6, 6, 7, 7, 7, 8, 8, 8},
	{6, 6, 6, 7, 7, 7, 8, 8, 8},
	{6, 6, 6, 7, 7, 7, 8, 8, 8},
};//3*3����ı��

int occupy[9][10];
//������ʼ��
void init_shudu()
{
	flag = false;
	memset(occupy, 0, sizeof(occupy));
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
		{
			int tmp = map[i][j];
			if (tmp)
			{
				occupy[tag[i][j]][tmp] = 1;//3*3����
			}
		}
}



bool check(int n, int key)
{
	cout << key << endl;;
	/*��鵱ǰ�����Ƿ�ɽ������
	  n:	��ǰ��������
	  key�� ���÷��������*/
	int x = n / 9;//�к�
	int y = n % 9;//�к�
	for (int i = 0; i < 9; i++)
	{
		cout << map[x][i] << " " << map[i][y] << endl;
		if (map[x][i] == key)return false;
		else if (map[i][y] == key)return false;
	}
	if (occupy[tag[x][y]][key])return false;
	return true;//��������������
}

void calculation(int n)
{
	if (n > 80)//�ѵ�������С����
	{
		flag = true;
		return;
	}
	else if (map[n / 9][n % 9] != 0)//�����
	{
		calculation(n + 1);
	}
	else
	{
		for (int i = 1; i <= 9; i++)
		{
			if (check(n, i) == true)
			{
				int x = n / 9;
				int y = n % 9;
				//�ݴ�ԭֵ
				int temp = occupy[tag[x][y]][i];
				//����
				map[x][y] = i;
				occupy[tag[x][y]][i] = 1;
				calculation(n + 1);//�����ݹ����
				//�����ϣ�������
				if (flag == true)
					return;
				//��ԭ
				map[x][y] = 0;
				occupy[tag[x][y]][i] = temp;
			}
		}
	}
}

void solve_shudu(char* path)
{
	/*�����������
	path:���������ļ�*/
	ifstream in(path);
	ofstream out("jieguo.txt");
	if (in.fail()) 
	{
		cout << "��ȡ�����ļ�ʧ��,��������ȷ���ļ�����" << endl;
		return;
	}
	stringstream buf;
	buf << in.rdbuf();//һ���Զ�ȡ
	string s = buf.str();
	//cout << s;
	int index = 0;//�ַ���s�ĵ�ǰ�±�
	memset(buffer, ' ', sizeof(buffer));//�ÿո��ʼ������ַ���
	pos = 0;
	while (index + 161 <= s.length())
	{
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
			{
				map[i][j] = s.at(index) - '0';
				index += 2;//�����ո����ĩ���з�
			}
		index += 1;//�������������֮��Ļ��з�
		init_shudu();
		calculation(0);
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				buffer[pos] = map[i][j] + '0';
				pos += 2;//�����ո�
			}
			buffer[pos++] = map[i][8] + '0';
			buffer[pos++] = '\n';
		}
		buffer[pos++] = '\n';
	}
	out.write(buffer, pos - 2);//��д�����Ļ��з�
	cout << "������!" << endl;

	in.clear();
	in.close();
	out.clear();
	out.close();
}