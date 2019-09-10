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
