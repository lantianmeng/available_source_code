# 字符串
1. 朴素的模式匹配算法
```
//字符串朴素的模式匹配算法
//s:主串
//t:子串
//pos:主串的第pos个位置
//返回值:主串的第pos个位置后找到字串t，则返回子串的位置;否则返回-1
int index(char* s, char* t, int pos)
{
	//assert(s!=nullptr && t!=nullptr);
	int s_len = strlen(s);
	int t_len = strlen(t);

	int i = pos;
	int j = 0;
	while (i < s_len && j < t_len)
	{
		if (s[i] == t[j])
		{
			++i;
			++j;
		}
		else
		{
			i = i - j + 1; //退回到上次首次匹配子串位置的下一个位置
			j = 0;         //退回到第一个字符
		}
	}

	if (j == t_len)
	{
		return i - t_len;
	}
	else
		return 0;
}

```
2. KMP模式匹配算法
```
void getNext(char* t, int* next)
{
	int len_t = strlen(t);
	int i = 0;
	int j = -1;

	next[0] = -1; //字符串t的下标为0时，next[0]为-1
	while (i < len_t)
	{
		if (j == -1 || t[i] == t[j])
		{
			++i;
			++j;
			next[i] = j;
		}
		else
		{
			j = next[j];
		}
	}
}

//()
int index_kmp(char* s, char* t, int pos)
{
	int len_s = strlen(s);
	int len_t = strlen(t);
	int i = 0;
	int j = 0;
	int next[1024]; //next 数组, t串的最大字符串长度为1024
	getNext(t, next);
	while (i < len_s && j < len_t)
	{
		if (j == 0 || s[i] == t[j])
		{
			++i;
			++j;
		}
		else
		{
			//i不回朔到0 j从next数据中获取
			j = next[j];
		}
	}

	if (j == len_t)
	{
		return i - j;
	}
	else
	{
		return 0;
	}
}
```
<br>注意点如下:
- next数组的推导
<br>代码实现中，需注意next[0]=-1,即第一个字符对应回朔位置为-1

- kmp模式匹配算法
<br>代码实现中需注意 j == 0 的判断

- 朴素模式匹配算法与kmp模式匹配算法的时间复杂度分析
