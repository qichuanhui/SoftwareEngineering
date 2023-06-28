#include "youxi.h"
#include "zhongju.h"
#include"qiujie.h"

static char buffer[165000000];//�����ַ�
static int pos;//�����ַ����ĵ�ǰд��λ��
int game[9][9];
int answer[9][9];
int aflag;//�����ϱ�־
int tags[9][9] =
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

int occupys[9][10];
//������ʼ��
void init_shudus()
{
	aflag = 0;
	memset(occupys, 0, sizeof(occupys));
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
		{
			int tmp = answer[i][j];
			if (tmp)
			{
				occupys[tags[i][j]][tmp] = 1;//3*3����
			}
		}
}



bool checks(int n, int key)
{
	cout << key << endl;;
	/*��鵱ǰ�����Ƿ�ɽ������
	  n:	��ǰ��������
	  key�� ���÷��������*/
	int x = n / 9;//�к�
	int y = n % 9;//�к�
	for (int i = 0; i < 9; i++)
	{
		//cout << map[x][i] << " " << map[i][y] << endl;
		if (answer[x][i] == key)return false;
		else if (answer[i][y] == key)return false;
	}
	if (occupys[tags[x][y]][key])return false;
	return true;//��������������
}

void calculate(int n)
{
	if (n > 80)//�ѵ�������С����
	{
		aflag++;
		return;
	}
	else if (answer[n / 9][n % 9] != 0)//�����
	{
		calculate(n + 1);
	}
	else
	{
		for (int i = 1; i <= 9; i++)
		{
			if (checks(n, i) == true)
			{
				int x = n / 9;
				int y = n % 9;
				//�ݴ�ԭֵ
				int temp = occupys[tags[x][y]][i];
				//����
				answer[x][y] = i;
				occupys[tags[x][y]][i] = 1;
				calculate(n + 1);//�����ݹ����
				//�����ϣ�������
				if (aflag != 0)
					return;
				//��ԭ
				answer[x][y] = 0;
				occupys[tags[x][y]][i] = temp;
			}
		}
	}
}


void create_game(int num, int level, int minhole, int maxhole, bool only)
{
	if (level == 0)level = rand() % 3 + 1;
	if (minhole == 0)
	{
		if (level == 1)minhole = 20;
		else if (level == 2)minhole = 30;
		else minhole = 40;
	}
	if (maxhole == 0)
	{
		if (level == 1)maxhole = 30;
		else if (level == 2)maxhole = 40;
		else maxhole = 55;
	}
	create_shudu(num,"answer.txt");
	ifstream in("answer.txt");
	ofstream out("game.txt");
	stringstream buf;
	buf << in.rdbuf();//һ���Զ�ȡ
	string s = buf.str();
	//cout << s;
	int index = 0;//�ַ���s�ĵ�ǰ�±�
	memset(buffer, ' ', sizeof(buffer));//�ÿո��ʼ������ַ���
	pos = 0;
	int rands[81];
	srand((unsigned)time(NULL));
	while (index + 161 <= s.length())
	{
		int tempindex = index;
		for (int i = 0; i < 81; i++)rands[i] = 1;
		int hole = (rand()%(maxhole-minhole))+minhole;
		for (int i = 0; i < hole; i++)
		{
			int temp = rand()%81;
			while (rands[temp] == 0)
			{
				temp = rand() % 81;
			}
			rands[temp] = 0;
		}
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
			{
				if (!rands[(i + 1)*(j + 1) - 1])game[i][j] = '0' - '0';
				else game[i][j] = s.at(index) - '0';
				if(only)answer[i][j] = s.at(index) - '0';
				index += 2;//�����ո����ĩ���з�
			}
		if (only)
		{
			init_shudus();
			calculate(0);
			if (aflag != 1)
			{
				index = tempindex;
				continue;
			}
		}
		index += 1;//�������������֮��Ļ��з�
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				buffer[pos] = game[i][j] + '0';
				pos += 2;//�����ո�
			}
			buffer[pos++] = game[i][8] + '0';
			buffer[pos++] = '\n';
		}
		buffer[pos++] = '\n';
	}
	out.write(buffer, pos - 2);//��д�����Ļ��з�
	cout << "��Ϸ�������!" << endl;
	in.clear();
	in.close();
	out.clear();
	out.close();
}
