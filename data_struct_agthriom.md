# 数据结构与算法
- 为什么要学习why？
<br>[工作后，为什么还要学习数据结构与算法](https://www.jianshu.com/p/1a63970ab025)
- 如何学习how？
<br>[我是如何学习数据结构与算法的](https://www.cnblogs.com/kubidemanong/archive/2018/10/05/9746328.html)
<br>我也在学习数据结构与算法，先是过一遍概念，大致地了解一下，然后开始刷题，刷题的时候知道需要哪些知识点再着重学习。
<br>这个非常注重实践，牛客网和leetcode是刷题的好去处。
<br>[知乎 如何学习数据结构与算法](https://www.zhihu.com/question/21318658)
- 有何用途
<br>[数据结构与算法的一些应用](https://www.cnblogs.com/chenweichu/articles/5703046.html)

# 排序
- 冒泡排序
```
void bubble_sort(int *pArray, int nSize)
{
     for(int i = 0; i < nSize - 1; i++) //一次循环将最大数沉底，进行nSize-1次沉底，就可以让数组由小到大排序
     {
          for(int j = 0; j < nSize - 1 - i; j++) //进行一次沉底操作，需要与其他数比较
          {
               if(pArray[j] > pArray[j+1])
               {
                    int temp = pArray[j];
                    pArray[j] = pArray[j+1];
                    pArray[j+1] = temp;
               }
          }
     }
}
```
- 选择排序
```
void select_sort(int *pArray, int nSize)
{
     for(int i = 0; i < nSize; i++)
     {
          int min = i;  //min标记最小数的下标
          for(int j = i + 1; j < nSize; j++)//从i+1开始，查找比pArray[min]小的数
          {
               if(pArray[j] < pArray[min])
               {
                    min = j;
               }
          }
         
          int temp = pArray[i];   //pArray[i] 与 pArray[min]交换，即pArray[i]中存放最小数
          pArray[i] = pArray[min];
          pArray[min] = temp;
     }
}
```

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
//bImprove为true时，表示使用的是改进的kmp模式匹配算法
void getNext(char* t, int* next, bool bImprove = false)
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
			
			if (!bImprove)
			{
				next[i] = j;
			}
			else
			{
				//kmp改善后的算法
				if (t[i] != t[j])
				{
					next[i] = j;
				}
				else
				{
				        //这里需注意，要避免缓存的位置为-1从而导致崩溃
					next[i] = next[j];
				}
			}
		}
		else
		{
			j = next[j];
		}
	}
}

//()
int index_kmp(char* s, char* t, int pos, bool bImprove = false)
{
	int len_s = strlen(s);
	int len_t = strlen(t);
	int i = 0;
	int j = 0;
	int next[1024]; //next 数组, t串的最大字符串长度为1024
	getNext(t, next, bImprove);
	while (i < len_s && j < len_t)
	{
		if (j == -1 || s[i] == t[j])
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
		return -1;
	}
}
```
<br>注意点如下:
- next数组的推导
<br>代码实现中，需注意next[0]=-1,即第一个字符对应回朔位置为-1

- kmp模式匹配算法
<br>代码实现中需注意 j == -1 的判断

- 朴素模式匹配算法与kmp模式匹配算法的时间复杂度分析

- 改进的kmp模式匹配算法
<br>需注意，赋值的条件
