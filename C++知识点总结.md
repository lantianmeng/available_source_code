# VS调试C++ 的技巧
<br>[详细的技巧](http://www.cnblogs.com/kekec/p/5635854.html)
<br>目前重点想学习18，调试时显示map vecter等数据 [这里也有方法介绍](https://blog.csdn.net/panpan_jiang1/article/details/84062034)
- dump文件 调试程序崩溃问题
<br>[vs调试dump文件](http://www.cnblogs.com/alphaxz/p/9008024.html)
  - 要添加生成dump文件的代码
  - 编译生成程序后，要保存pdb文件以及依赖的dll文件
  - 双击dump文件，注意进程名称（绝对路径，重点是**目录位置**）
  - 把pdb文件和exe文件放到进程名称所在的目录下面，如果开发环境机器上没有这个目录，那么就新建这个目录，否则无法加载符号，调试只能看汇编代码。
  - 点击使用仅限本机进行调试，就可以方便的看到源代码进行调试了。
- 内存泄漏   [调试以及解决方法](https://www.cnblogs.com/skynet/archive/2011/02/20/1959162.html)
<br>windows  
- 方法一：_CrtDumpMemoryLeaks()  这个方法要放在**main函数退出之前**
```
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main(int argc, char *argv[])
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	QApplication a(argc, argv);
	EDCDemo w;
	w.show();

	_CrtDumpMemoryLeaks();

	return a.exec();
}
```
- 方法二：_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); 这个方法要放在**main函数的入口处**
```
int main(int argc, char *argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	QApplication a(argc, argv);
	EDCDemo w;
	w.show();
	return a.exec();
}
```
<br>linux  valgrind命令
- 查看exe依赖的库文件，查看lib和dll中的符号
<br>[VS自带工具：dumpbin的使用查看Lib,dll等](https://blog.csdn.net/sinat_29890433/article/details/79556124)

# 基础知识点
<br>[C++指针和引用](https://www.cnblogs.com/tangxiaobo199181/p/7989464.html) ***评论区的一些解释，也要注意***
<br>[C++ const关键字](https://www.runoob.com/w3cnote/cpp-const-keyword.html)
<br>[const与类对象及类成员](https://www.cnblogs.com/cthon/p/9178701.html) ***const对象的数据成员，如果要修改，则需将其声明为mutable***
<br>[C/C++中的static关键字](https://blog.csdn.net/weixin_40311211/article/details/82851300)
```
//限定全局变量g_s只在当前文件可见（在test.cpp中使用g_s，编译报错）
static int g_s = 10;

//普通的全局变量的作用域也是在当前文件有效，但可以通过extern来扩展全局变量的作用域
int g_s = 10;

//静态局部变量
int foo()
{
	//i只初始化一次，且foo函数执行完后不释放
	static int i = 2;
	i += 1;
	return i;
}

//类的静态成员变量和静态成员函数
//静态成员变量:类的所有对象共享，存储在静态存储区而不是类对象所分配的内存区
//             初始化:  不是通过类的构造函数int A::m_a = 0;

//静态成员函数：访问私有的静态成员变量（不能访问普通成员）
//             普通成员函数可以直接调用静态成员函数和静态
class A
{
public:
	A():m_b(0) {}
	A(int b):m_b(b)  {}
	~A() {}
	
	static int get_a() { return m_a; }
	int get_plus() { return m_a + m_b; }
private:
	static int m_a;
	int m_b;
};

int A::m_a = 0;
```
1. c++ 两个类需要互相引用，导致头文件互相包含
  - 某一个类的头文件中对引用的类定义指针，然后对引用的类进行声明；cpp文件中包含引用类的路径
  ```
  //B.h
#pragma once 
 
class A;	//使用了A类对象的指针，只做简单的声明即可
  
class B 
{  
public: 
        A* a; /////////////
};

//B.cpp
#include "A.h"
  ```
  <br>C++声明带命名空间的类, 即如果被声明的类有命名空间，需注意**声明的方式**
  ```
  namespace YYYY
  {
      class A;	//类A带有命名空间YYYY，此时的声明要注意
  }
  
  class B 
  {  
  public: 
        YYYY::A* a; /////////////
  };
  
  //B.cpp
  #include "A.h"
  ```
  
  - 类组合时，引用的类**定义指针时，对类声明即可；引用的类定义为对象时，需包含引用类的头文件**
  ```
  //文件A.h中的代码 
#pragma once 
#include "B.h"         //使用了B类的对象，所以要包含头文件

  
class A 
{  
public: 
        B b; 	     ///////////////////
};  
  ```

2. 类型转换
+ 隐式类型转换
<br>基本类型的隐式类型转换
<br>类与基本类型的转换
```
class test_const
{
public:
	test_const() :m_b(0) {}

	//只有一个参数，且参数是基本类型，称为转换构造函数，即将基本类型转为类类型（隐式转）。
	//为了避免这种隐式转换造成问题，可使用explicit
	test_const(int b) :m_b(b) {}
	~test_const() {}

	//不改变数据成员的成员函数，其后面都应该加const
	int get_b() const { return m_b; }

	//将test_const类类型，转换为int型
	operator int() { return m_b; }
private:
	int m_b;
};

void show(const test_const& tt)
{
	std::cout << tt.get_b() << std::endl;
}

int main()
{
	test_const at(53);
	std::cout << at.get_b() << std::endl;

	//类对象赋值给基本类型时，即转换
	int test_convert = at;
	//这里传入int类型，而show()函数发生了
	show(test_convert);
	system("pause");
    return 0;
}

```
+ c++强制类型转换
- static_cast  编译时期的静态类型检测
	- 完成基础数据类型
	- 同一个继承体系中类型的向上转换 ,
	<br>**向上转换**即子类类型的引用或指针转换为父类类型
	<br>[可参考的例子](https://www.cnblogs.com/luntai/p/5879026.html)
	- 任意类型与空指针类型void*之间的转换。
- dynamic_cast 运行时检测 主要用于同一个继承体系中类型的向下转换
  <br>**向下转换**即父类类型的引用或指针转换为子类类型, 
  <br>一般是想知道基类指针或引用指向哪个具体的子类, 使用的方法是c++11  typeid  , 可参考的例子
  <br>观察者模式的pull方式会用到
  ```
  void bugao::update1(subject *obj)
  {
  	if (strcmp(typeid(*obj).name(), typeid(WeatherData1).name()) == 0)
  	{
  		WeatherData1 *pData = dynamic_cast<WeatherData1 *>(obj);
  		//WeatherData1 *pData = reinterpret_cast<WeatherData1 *>(obj);
  
  		address_name = pData->get_address_name();
  		temperature = pData->get_temperature();
  
  		show();
  	}
  }
  ```
  <br>**要注意** `WeatherData1 *pData = dynamic_cast<WeatherData1 *>(obj);`

3. 一些算法的应用
- 排序sort 与qsort 结合lamada表达式的使用
[浅谈C++中qsort与sort的使用方法与区别](https://blog.csdn.net/lkn910907/article/details/44085015)
[C++11 sort, vector, lambda——vector 自定义排序](https://blog.csdn.net/tropicofcancer9/article/details/64444209)

因为在实际的项目中，有首先按照优先级排序，如果优先级相同再根据另一个数据进行排序的情况
<br>[一组数据按照不同的优先级快速排序](https://blog.csdn.net/Gaibb123/article/details/86581145)
- find/find_if  结合lamada表达式的使用
[对vector使用std::find 和 std::find_if 算法](https://blog.csdn.net/wangshubo1989/article/details/50389811)

示例代码：（实际项目中有用到）
```
    class flag_data_unit
    {
    public:
    	flag_data_unit() :flag(0), priority(0), type(FLAG_CELL), level(""), rank(""), defect_code(""), defect_info("") {}
    	flag_data_unit(int flag_, int priority_, const string& level_, const string& rank_, const string& defect_code_)
    		:flag(flag_), 
    		priority(priority_), 
    		level(level_), 
    		rank(rank_), 
    		defect_code(defect_code_), 
    		defect_info(defect_code_)
    	{
    		type = FLAG_CELL;
    	}
    private:
    	int flag;
    	int priority;
    	FlagType type;
    	string level; //此flag限定的level，如果为空，表示正常判定.即取aoi判定的等级
    	string rank;  //此flag限定的rank，如果为空，表示正常判定.即取aoi判定的rank
    	string defect_code;
    	string defect_info;
    };
    
        std::vector < flag_data_unit > all_data;

	//按照priority排序(从小到大)，相同的priority则按type排序(array/cell/cf/sl)
	std::sort(all_data.begin(), all_data.end(), [](flag_data_unit & obj1, flag_data_unit & obj2)
	{
		if (obj1.GetPriority() < obj2.GetPriority())
		{
			return true;
		}
		else if (obj1.GetPriority() == obj2.GetPriority())
		{
			return obj1.GetType() < obj2.GetType();
		}
		return false;
	});
	
	//这里要注意，lamada表达式对参数flag的捕获
	std::vector < flag_data_unit >::iterator flag_data_all::GetDataUnit(int flag)
        {
	   std::vector < flag_data_unit >::iterator it = std::find_if(all_data.begin(), all_data.end(), [flag](flag_data_unit & obj){ return obj.GetFlag() == flag; });
	   return it;
	}
	
```
- 标准库算法中的谓词(predicate)
[C++ - 算法(algorithm) 的 谓词(predicate) 详解](https://blog.csdn.net/caroline_wendy/article/details/15378055)
<br>这里列举的例子，以及后面vector中使用标准库算法，谓词（predicate）都是使用的lamada表达式，也可以使用上文中的描述的其他方法

- C++ stl中的仿函数 
<br>[C++ STL（第二篇：仿函数）](https://blog.csdn.net/weixin_39640298/article/details/88750451)
<br>这里的一些概念需要理解：仿函数比函数指针好的原因，一元仿函数和二元仿函数（有些算法需要，故二者可能需要转换 bind1nd/bind2nd）
<br>[STL之仿函数实现详解](https://blog.csdn.net/u010710458/article/details/79734558)
<br>这里是stl自带的仿函数，也可以自定义仿函数
```
//代码例子，可以参考 5 求vector中最大元素
```
4. 类型别名using与typedef
- STL中的容器使用类型别名以及迭代器别名
```
class flag_data_all
{
	using  FlagDataType = std::vector < flag_data_unit >;
public:
	using FlagDataIterator = FlagDataType::iterator;
	
	FlagDataIterator GetDataUnit(int flag);
	bool IsRightIterator(FlagDataIterator it) { return it != all_data.end(); }
	void AddData(FlagDataIterator data_unit){ std::lock_guard<std::mutex> lck(mt); all_data.push_back(*data_unit); }
private:
	std::mutex mt;
	FlagDataType all_data;
};	

//迭代器别名，作为类成员函数的返回值，需写类作用域来限制，即flag_data_all::
flag_data_all::FlagDataIterator flag_data_all::GetDataUnit(int flag)
{
	std::lock_guard<std::mutex> lck(mt);
	FlagDataIterator it = std::find_if(all_data.begin(), all_data.end(), [flag](flag_data_unit & obj){ return obj.GetFlag() == flag; });
	return it;
}

```

5. vector 
- 循环遍历vector时删除某一个元素
<br>程序员面试宝典中也有讲到
```
 //注意上面不能写成
    /*
        for(vector<int>::iterator it=arr.begin(); it!=arr.end(); it ++)
        {
            if(* it == 8)
            {
                arr.erase(it);     //在erase后，it失效，并不是指向vector的下一个元素，it成了一个“野指针”。
            }
        }
    */
    
    for(vector<int>::iterator it=arr.begin(); it!=arr.end(); )
    {
        if(* it == 8)
        {
            it = arr.erase(it);
        }
        else
        {
            ++it;
        }
   }
```
- map遍历时删除的方法
```
        typedef std::map<SSessionId, boost::shared_ptr<CSessionData>>  SessionDataType;
	    SessionDataType m_sessionData;
		
		SessionDataType::iterator iter = m_sessionData.begin();
		while (iter != m_sessionData.end())
		{
			uint64_t currentTimestamp = CStreamMgr::GetCurrentStamp64();
			if (iter->second->getPlayCount() == 0 && (currentTimestamp - iter->second->getTimestamp()) >= m_noPlayInterval)
			{
				//正常停止流
				m_streamMgr->stopStream(iter->second);
				m_sessionData.erase(iter++);
				continue;
			}
			iter++;
		}

```

- list中遍历时删除的另一种方法(通过front/pop_front)
```
        //对于缓存list，线程中使用时，加锁swap交换数据给临时list后，释放锁；然后接着处理缓存中的数据
        std::list< SPIStreamSession > tmpList;
        {
            boost::mutex::scoped_lock lock( m_mutexExcept );
            tmpList.swap( m_exceptSessins );
        }

        while( !tmpList.empty() ) // m_bRun为FALSE也要做完spSession->fini()，因为m_exceptSessins已经swap出来了
        {
            const SPIStreamSession& spSession = tmpList.front();
            if ( spSession )
            {
                spSession->fini();
            }
            tmpList.pop_front();
        }
```
- vector，获取某个元素对应的迭代器，对应的下标
<br>[vector 迭代器，返回下标的方法](https://blog.csdn.net/meanong/article/details/80179680)

```
class rank_data_all
{
public:
	rank_data_all(){}
	rank_data_all(const string & config_rank);

	//获取下标值
	//返回值：rank在vector中的下标，如果vector中没有rank，则返回-1
	int GetIndex(const string& rank);

private:
	vector<string> all_rank;
};

int rank_data_all::GetIndex(const string& rank)
{
	int ret = -1;
	vector<string>::iterator it = std::find(all_rank.begin(), all_rank.end(), rank);
	if (it != all_rank.end())
	{
		ret = it - all_rank.begin();
	}
	return ret;
}

```
- vector，根据某个条件或数据，获取所有满足条件的子vector
```
#include <algorithm>
#include <functional>

struct tt_data
{
	tt_data(){ age = 0; name = ""; }
	tt_data(int age_, string name_) :age(age_), name(name_){}

	int age;
	string name;
};

using tt_data_vec = vector < tt_data > ;

tt_data_vec GetChildVectorBy(tt_data_vec src_data, int a)
{
    //获取满足条件的个数
	int ii_num = std::count_if(src_data.begin(), src_data.end(), [a](tt_data tt){return tt.age == a; });

	tt_data_vec temp(ii_num);
	std::copy_if(src_data.begin(), src_data.end(), temp.begin(), [a](tt_data tt){return tt.age == a; });
	return temp;
}

```
- 判断vector是否相等，以及求vector中元素的最大值（仿函数的应用）
<br>[判断两个vector是否相等](https://www.xuebuyuan.com/540427.html)
```
class shapeData
{
public:
       using PointsType = std::vector<QPoint>;
       bool operator==(shapeData shape_unit)const { return index == shape_unit.getIndex() && points == shape_unit.getPoints(); }
       
private:
	int index;
	PointsType points;
};

//shape类的比较函数(仿函数)
struct shape_comp
{
    bool operator()(const shapeData &s1, const shapeData &s2)
    {
    	return (s1.getIndex() < s2.getIndex());
    }
};

class PaintWidget
{
public:
        using ShapeDataType = std::vector<shapeData>;
	bool IsDataChanged();

        //所有shape的最大index值
	int getMaxIndex();
private:
        ShapeDataType all_shapes;
};

bool PaintWidget::IsDataChanged()
{
	bool ret = false;
	QString json_name;
	if (I_MainWindow->IsExistLabelData(json_name)) //判断与当前图片同名的json文件是否存在
	{
		//解析json文件
		PaintWidget::ShapeDataType shapes;
		read_json(json_name, shapes);
		if (shapes != all_shapes) //两个vector直接比较，需要重载==
			ret = true;
	}
	else
	{
		if (all_shapes.size() > 0)
			ret = true;
	}
	return ret;
}

int PaintWidget::getMaxIndex()
{
	int ret = -1;

	ShapeDataType::iterator iter = max_element(all_shapes.begin(), all_shapes.end(), shape_comp());
	if (iter != all_shapes.end())
	{
		ret = iter->getIndex();
	}

	return ret;
}

```
6. c++11 的lamada表达式
[C++11 Lambda表达汇总总结](https://www.cnblogs.com/smiler/p/4095723.html)

7. c++11中的hash容器/数据结构  unordered_set/unordered_map  
<br>[map与unordered_map的区别](https://www.cnblogs.com/strawqqhat/p/10602515.html)
<br>[哈希表和红黑树的对比](https://blog.csdn.net/zkangaroo/article/details/70151688)

# C++可变参数
1. 可变参数宏va_start/va_arg/va_end
```
std::shared_ptr<DemuraData> DemuraResultReport::CreateDemuraResultReport(std::string panel_id, std::string result, int nStationNo, ...)
{
	std::shared_ptr<DemuraData> demura_data;

	va_list   arg_ptr = NULL;   //定义可变参数指针 
	va_start(arg_ptr, nStationNo);   // nChannelNo为最后一个固定参数

	//在下面switch语句中调用下面代码，获取各个变量的值
	//int j = va_arg(arg_ptr, int);   //返回第一个可变参数，类型为int
	//char c = va_arg(arg_ptr, char);   //返回第二个可变参数，类型为char

	if (g_edctestfile.Find("B9C8_Demura") >= 0)
	{
		demura_data = std::make_shared<B9C8_Demura>(m_pEDCMan, nStationNo, panel_id, result);
	}

	va_end(arg_ptr);        //  清空参数指针

	return demura_data;
}

//测试可变参数传入的是指向类对象的指针,string,
void test_stage_data(int type, ...)
{
	va_list   arg_ptr = NULL;   //定义可变参数指针 
	va_start(arg_ptr, type);   // nChannelNo为最后一个固定参数

	CStageDataMap *stage_data = nullptr;
	std::string panel_id("");
	int nStationNo = 0;
	std::string user_name("");
	switch (type)
	{
	case 1:
		stage_data = (CStageDataMap *)va_arg(arg_ptr, void*);
		stage_data->GetPanelID(2, panel_id);
		nStationNo = va_arg(arg_ptr, int);
		user_name = va_arg(arg_ptr, const char*);

		std::cout << panel_id << "\t" << nStationNo << "\t" << user_name << std::endl;
		break;
	case 2:
		std::string ss = va_arg(arg_ptr, const char*);
		std::cout << ss;
	}
}
```

2. c++11 可变参数模板    **使用场景和代码细节还没弄清楚**
<br>[可变模板参数展开方式](https://www.cnblogs.com/qicosmos/p/4325949.html)
<br>[判断可变模板参数是否包含特定的类型](https://blog.csdn.net/sinat_35261315/article/details/80463480)
<br>[可变参数在观察者模式中的应用](https://www.cnblogs.com/feng-sc/p/5648381.html)

**std::bind**就是采用这里描述的可变参数模板展开的方式进行的

# 继承与多态
<br>[涉及到OOAD的一些概念要弄清楚](https://www.cnblogs.com/xinxue/p/5471708.html)
- 纯虚函数与普通虚函数 
<br>这两种虚函数的目的都是负责定义接口，而派生类可以覆盖该接口
  - 纯虚函数，即没有实现的虚函数（=0）；派生类必须覆盖，否则该派生类也是抽象基类，不能用来定义对象；
  <br>基类中的虚函数，可以有**缺省实现**，即派生类不重写该方法时，实际执行的是基类的缺省实现。
- 包含纯虚拟函数的类为**抽象基类**，即OOAD中的接口interface；抽象基类，不能用来定义对象，但可以声明指向抽象基类的指针或引用

- c++11 override的作用 final
- 两个概念 **接口继承与实现继承**  <br>[adapter模式 中有提到](https://www.cnblogs.com/jiese/p/3166396.html)  


# C++11 智能指针
[窥见C++11智能指针](https://cloud.tencent.com/developer/article/1486285)  腾讯技术工程官方号的专栏文章，写的详细而又深入浅出

<br>[自己总结的关于智能指针的用法](https://github.com/lantianmeng/available_source_code/blob/master/smart_point.md)

# memory pool
[开源代码](https://github.com/cacay/MemoryPool)
	
# c++11 thread
<br>[git上有实列](https://github.com/lantianmeng/available_source_code/blob/master/ConsoleApplication1/learn_c%2B%2B11/learn_c%2B%2B11.cpp)
<br>std::thread/std::packaged_task/std::async
<br>异步执行获取方法的返回值  async蛮方便
<br>[详细讲解](https://blog.csdn.net/ac_hell/article/details/72718363)

1. std::future / std::async / std::promise / std::packaged_task
- future 的get方法会阻塞，但可以通过wait_for等方法获取状态（可以设置超时，避免线程一直阻塞）
```
#include <future>

class Test_PackagedTask
{
public:
    Test_PackagedTask()
    {
		t_i = 0;
		//tsk(task3);
    }

    void task3()//模拟接收tems消息
    {
		t_i += 2;
		std::cout << "task 3 " << t_i << std::endl;

		pp_t.set_value(t_i);
    }
    
    void task4()
    {
    	std::cout << "task 4" << std::endl;
    
    	//std::this_thread::sleep_for(std::chrono::seconds(5));
    	std::this_thread::sleep_for(std::chrono::seconds(8));
    
    	task3();
    }
    
    void task2()
    {
    	++t_i;
    	std::cout << "task 2 " << t_i << std::endl;
    
    }
    
    void task1()//模拟接收plc信号
    {
    	std::cout << "task 1" << std::endl;
    
    	task2(); //模拟给tems发消息
    
    	//模拟等待tems回消息
    	std::future<int> fu1 = pp_t.get_future();
    	std::chrono::milliseconds span(6000);
    	std::future_status status;
    	do
    	{
    		status = fu1.wait_for(span);
    	} while (status == std::future_status::deferred);
    
    	if (status == std::future_status::timeout)
    	{
    		std::cout << "timeout " << t_i << std::endl;
    	}
    	else if (status == std::future_status::ready)
    	{
    		std::cout << "ready " << t_i << std::endl;
    	}
    }

private:
	int t_i = 0;
	//std::packaged_task<void()> tsk;

	std::promise<int> pp_t;
	
};
```
<br>[c++异步代码同步化](https://blog.csdn.net/jiange_zh/article/details/78162434)    **封装的思路值得学习**

- packaged_task
<br>[packaged_task 包装的是异步操作，即从异步操作中获取值](https://www.cnblogs.com/qicosmos/p/3534211.html)
<br>[作者一个项目经验的总结，里面提到的框架的设计，需要注意](https://www.cnblogs.com/qicosmos/p/3492802.html)

- 异步处理获取处理结果，下述方法比条件变量更好 
<br>[异步处理获取处理结果，使用std::future /std::promise/ std::packaged_task的几种场景](https://www.cnblogs.com/geloutingyu/p/8562283.html)
- std::future /std::promise/ std::packaged_task 作参数
<br>因为其拷贝构造函数以及opterator== 都被delete了，所以实参直接传入std::future /std::promise/ std::packaged_task对象时，编译会报错.但如果实参传入的是右值引用(std::move)，则可以正常编译
```
    std::packaged_task<int()> tsk([](){ return 7; });
	//test5(tsk);
	test5(std::move(tsk));

	void test5(std::packaged_task<int()> tsk)
	{
		std::thread t1(std::ref(tsk));
		t1.join();
	}
```

<br>[类型推导与右值引用](https://www.bbsmax.com/A/GBJrVLjBJ0/)
<br>[C++11 多线程之传递package_tast讨论](https://blog.csdn.net/t114211200/article/details/78073286)
<br>以上模板与泛型编程用到的比较多

<br>**腾讯rpc框架** [Tars框架Future/Promise使用](http://ju.outofmemory.cn/entry/342264)

2. 多线程以及同步 
<br>关于互斥锁，有以下两种使用方法
 - 大锁， 锁整个缓存
 ```
    //定时器函数，锁m_lockSessionData将整个map缓存（m_sessionData）锁住
 	bool CSessionMgr::timerCallback()
	{
		if (!m_streamMgr) return false;

		boost::mutex::scoped_lock lock(m_lockSessionData);
		SessionDataType::iterator iter = m_sessionData.begin();
		while (iter != m_sessionData.end())
		{
			uint64_t currentTimestamp = CStreamMgr::GetCurrentStamp64();
			if (iter->second->getPlayCount() == 0 && (currentTimestamp - iter->second->getTimestamp()) >= m_noPlayInterval)
			{
				//正常停止流
				m_streamMgr->stopStream(iter->second);
				m_sessionData.erase(iter++);
				continue;
			}
			iter++;
		}

		return true;
	}


 ```
 
 - 短暂锁，获取缓存数据（swap）后，锁释放。然后继续处理缓存数据
 ```
 
 //线程函数，加锁后将缓存中的数据复制给临时对象（块作用域，短暂锁住缓存m_sessions（map）/m_exceptSessins(list)）
 void CStreamMgr::exceptionThread()
{
    while( m_bRun )
    {
        SPIStreamSessionContainer tmpContainer;
        {
            boost::mutex::scoped_lock lock( m_mutex );
            tmpContainer = m_sessions;
        }
        uint64_t nowTime = time( NULL );
        nth_index_iterator<SPIStreamSessionContainer, 0>::type it = get<0>(tmpContainer).begin(), ite = get<0>(tmpContainer).end();
        for ( ; it != ite; ++it )
        {
            if ( !m_bRun )
                break;
            if ( *it )
            {
                (*it)->checkTimeOut( nowTime );
            }
        }
        if ( !m_bRun )
            break;

        std::list< SPIStreamSession > tmpList;
        {
            boost::mutex::scoped_lock lock( m_mutexExcept );
            tmpList.swap( m_exceptSessins );
        }

        while( !tmpList.empty() ) // m_bRun为FALSE也要做完spSession->fini()，因为m_exceptSessins已经swap出来了
        {
            const SPIStreamSession& spSession = tmpList.front();
            if ( spSession )
            {
                spSession->fini();
            }
            tmpList.pop_front();
        }
        if ( m_bRun )
        {
            boost::mutex::scoped_lock lock( m_mutexExcept );
            m_cond.timed_wait( lock, boost::posix_time::seconds( TIMER_INTERVAL ) );
        }
    }
}

 ```
 
# c++11 模板函数
<br>TA int/string(char*) TD int/string(char*)
//template<typename TA=int, typename TD=int>
	//bool PLC_WriteData(TA addr, TD data, int len);  

# 网络通信
## 网络连接状态 
1. tcp协议，server如何知道client掉线了
<br>[如何获取tcp的连接状态 ](https://www.cnblogs.com/gwwdq/p/9261615.html)
<br>tcp keepalive机制，应用层的心跳机制（可以不用管底层是tcp还是udp）

2. 服务端如何识别每个客户端
- 客户端跟服务器通讯内容，属于业务信令的设计和功能服务设计。你不能识别哪一个 TcpClient 是谁，那是你自己没有解析信令的问题。TCP不管业务，只管确保一对一可靠通讯就行了。
<br>即连接成功后，客户端给服务端发信令（如注册、登陆等），信令内容包含了客户端的唯一标识ID
- 通过ip和port
<br>即客户端调用Connect前，先绑定一个特定的ip和port（本地local ip和port，默认情况下port是随机分配的），Connect中的参数是服务器端的ip和监听port（Remote ip和）
<br>服务端收到客户端发送的信令（如注册、登陆等），可以通过get方法获取客户端的ip和port，然后和服务端中配置的各个ip和port做比较，判断是哪个客户端

客户端如何识别服务端掉线
[客户端怎么判断Socket连接已与服务器断开](https://blog.csdn.net/messigodlike/article/details/78523737)

3. tcp协议，发送数据过快会有粘包的情况。
故在定义发送/接收数据的格式时（特别时字符串），需要有头尾标志，这样接收者可以根据这些标志进行解析

4. ftp协议
<br>[开源ftp库](http://www.nbpfaus.net/~pfau/ftplib/)  可以使用，但没法打印ftp命令发送及接收的过程
<br>[libcurl](https://blog.csdn.net/byxdaz/article/details/84110209)
<br>[纯socket发送ftp命令，接收服务端的响应，来完成ftp的交互](https://blog.csdn.net/the_king_cloud/article/details/8090699)
<br>[boost实现ftp功能](https://blog.csdn.net/wy16223864/article/details/16362001)

ftp断点续传功能
- ftp两种模式 standard（port方式 主动方式），passive（PASV 被动方式） [ftp协议 百度百科](https://baike.baidu.com/item/FTP%E5%8D%8F%E8%AE%AE/7651119?fr=aladdin)
<br>控制通道与数据传送通道

5. 开源网络库
<br>[C/C++ 开源网络库](https://www.cnblogs.com/gjianw217/p/4256261.html)


# 数据结构与算法
[一些书籍](https://blog.csdn.net/salmon_zhang/article/details/88603207)

# C++ UI
<br>[C++ ui控件自绘](https://www.cnblogs.com/hrhguanli/p/4470716.html)
<br>**SOUI控件自绘开源库**   [soui demo以及其他的一些界面demo](https://github.com/soui-demo)

# C++后台服务
搜索“web后台服务 cgi”
<br>[c++后台实践：古老的CGI与web开发](https://www.cnblogs.com/hehe001/p/6156870.html)

# 构建知识体系
<br>[有讲解有说明](https://blog.csdn.net/loongembedded/article/details/65934877)很有参考意义，有目标有方法
<br>[c++知识体系](https://blog.csdn.net/LF_2016/article/details/52434575)
- 以面试题为目标，来补强知识体系
  - 搜集面试题
  - 对题目的答案进行编码实现，并对关联知识进行整理和总结

# C++ 访问数据库
<br>[C++连接主流数据库经验总结](https://blog.csdn.net/GIS_yuhua/article/details/100027392)

<br>[C++类库：OTL通用的数据库连接类库](http://www.cppblog.com/lovefeel2004/archive/2010/06/02/116946.aspx)
<br>[一个C++11实现的轻量级数据库访问库，支持MySQL和SQLite ](https://www.ctolib.com/topics-107358.html)

<br>[C++数据库访问类库SOCI、LiteSQL、POCO对比](https://blog.csdn.net/csdndenglu/article/details/90441230)
这里推荐的是poco

 *sqlapi++ 收费库，soci轻量级，liteSQL是自动生成代码，比较重。。poco除了数据库功能之外，还有包含了很多其他的库，是一个开发框架*

# 架构设计相关
1. 一些DDD和应用架构的基础知识
<br>[阿里高级技术专家方法论：如何写复杂业务代码？](https://mp.weixin.qq.com/s/pdjlf9I73sXDr30t-5KewA)
<br>[在单体应用的一些DDD实践经验](https://www.cnblogs.com/mq0036/p/9405781.html)

《领域驱动设计》
《架构整洁之道》

# 一些信息
<br>[写博客的收获和总结](https://juejin.im/post/5c02b2bce51d4533253f2f43)   此前六大设计原则也是该作者写的

# 开源库
<br>[腾讯Tars开源RPC框架](https://www.liangzl.com/get-article-detail-18305.html)

# 面试
<br>[C++后台开发面试](https://blog.csdn.net/jiange_zh/article/category/9265333)
<br>[互联网技术笔试总通不过？leetcode刷对了么](https://36kr.com/p/5084645)

<br>[玩铁的搬砖工 牛客网](https://www.nowcoder.com/discuss/178555?type=1 )
