#include"qiujie.h"

static char buffer[165000000];//输出字符串缓冲区
static int pos;//输出字符串的当前写入位置

int map[9][9];
bool flag;//求解完毕标志
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
};//3*3方格的标号

int occupy[9][10];
//变量初始化
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
				occupy[tag[i][j]][tmp] = 1;//3*3方格
			}
		}
}



bool check(int n, int key)
{
	cout << key << endl;;
	/*检查当前方格是否可进行填充
	  n:	当前方格的序号
	  key： 填充该方格的数字*/
	int x = n / 9;//行号
	int y = n % 9;//列号
	for (int i = 0; i < 9; i++)
	{
		cout << map[x][i] << " " << map[i][y] << endl;
		if (map[x][i] == key)return false;
		else if (map[i][y] == key)return false;
	}
	if (occupy[tag[x][y]][key])return false;
	return true;//满足条件返回真
}

void calculation(int n)
{
	if (n > 80)//已到达最后的小格子
	{
		flag = true;
		return;
	}
	else if (map[n / 9][n % 9] != 0)//已填充
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
				//暂存原值
				int temp = occupy[tag[x][y]][i];
				//更新
				map[x][y] = i;
				occupy[tag[x][y]][i] = 1;
				calculation(n + 1);//继续递归求解
				//求解完毕，层层回退
				if (flag == true)
					return;
				//还原
				map[x][y] = 0;
				occupy[tag[x][y]][i] = temp;
			}
		}
	}
}

void solve_shudu(char* path)
{
	/*求解数独函数
	path:数独所在文件*/
	ifstream in(path);
	ofstream out("jieguo.txt");
	if (in.fail()) 
	{
		cout << "读取数独文件失败,请输入正确的文件名称" << endl;
		return;
	}
	stringstream buf;
	buf << in.rdbuf();//一次性读取
	string s = buf.str();
	//cout << s;
	int index = 0;//字符串s的当前下标
	memset(buffer, ' ', sizeof(buffer));//用空格初始化输出字符串
	pos = 0;
	while (index + 161 <= s.length())
	{
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
			{
				map[i][j] = s.at(index) - '0';
				index += 2;//跳过空格和行末换行符
			}
		index += 1;//跳过待求解问题之间的换行符
		init_shudu();
		calculation(0);
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				buffer[pos] = map[i][j] + '0';
				pos += 2;//跳过空格
			}
			buffer[pos++] = map[i][8] + '0';
			buffer[pos++] = '\n';
		}
		buffer[pos++] = '\n';
	}
	out.write(buffer, pos - 2);//不写入最后的换行符
	cout << "求解完毕!" << endl;

	in.clear();
	in.close();
	out.clear();
	out.close();
}