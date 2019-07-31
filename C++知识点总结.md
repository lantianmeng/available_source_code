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
<br>windows  _CrtDumpMemoryLeaks() , linux  valgrind命令
  
# 基础知识点
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

2. c++强制类型转换
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
6. c++11 的lamada表达式
[C++11 Lambda表达汇总总结](https://www.cnblogs.com/smiler/p/4095723.html)

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
- shared_ptr 与 weak_ptr
<br>[shared_ptr的实例讲解](https://www.cnblogs.com/shengjianjun/p/3691928.html)
  - shared_ptr 对象初始化（new，reset，make_shared） **new与make_shared的区别**
  - weak_ptr的使用场景
  - shared_ptr作为函数参数的情况
    - 作为参数时给默认值  ```std::shared_ptr<A> data = nullptr```
	- shared_ptr作为函数形参时，要看成对象。如果用来返回值时，要加引用符号&
	- 作为局部变量 
	<br>[shared_ptr作为局部变量](https://www.cnblogs.com/kilen/p/7128600.html)  
	<br>[shared_ptr使用注意点](https://blog.csdn.net/man_sion/article/details/77196766)
- unique_ptr 独占所指向的对象, 同一时刻只能有一个 unique_ptr 指向给定对象

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
```
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
# c++11 模板函数
<br>TA int/string(char*) TD int/string(char*)
//template<typename TA=int, typename TD=int>
	//bool PLC_WriteData(TA addr, TD data, int len);  

# VS+Qt开发
<br> [安装与创建工程](https://blog.csdn.net/zc881124/article/details/37695879)
<br> [VS+Qt开发](https://blog.csdn.net/lhl1124281072/article/category/7608337)

# 设计模式
[面向对象设计的六大原则](https://juejin.im/post/5b9526c1e51d450e69731dc2)
开闭原则、单一职责原则、依赖倒置原则、接口分离原则、迪米特法则、里氏替换原则。。 设计原则是设计模式的基石
## MVC设计模式
<br>[mvc的解读，涉及不采用c++多态的解释引发我的思考](https://www.cnblogs.com/tt-player/p/3644532.html)	

## 单利模式
[这里讲的很清楚](https://blog.csdn.net/cjbct/article/details/79266057)
<br>[此文讲解的很详细](https://blog.csdn.net/u011726005/article/details/82356538)   github中也有收录该文
1. 懒汉模式：需要使用时才初始化，以时间换空间
- 线程安全的实现
  - 两次判null，第二次时加锁，即双检查锁（C++11使用call_once(once_flag为static)）
  - 在instance()的方法实现时，定义静态成员变量，而不是new一个静态指针
2. 饿汉模式：类产生时，就实例化对象。以空间换时间
- instance为静态成员
- instance为静态指针，初始化时new；

3. 当instance为静态指针时，要提供delete的方法或者声明一个内部Garbo类，析构函数中调用delete或者使用智能指针unique_ptr，则自动释放

4. 构造函数为什么私有化（private）？ 构造函数为private时，意味着只能在类内部调用构造函数，即只能在类内部构造对象.
拷贝构造函数以及operator=为private，表示程序只能生成单利类一个对象，该对象不能复制（不能作为函数参数或返回值）

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
<br>**SOUI控件自绘开源库**

# C++后台服务
搜索“web后台服务 cgi”
<br>[c++后台实践：古老的CGI与web开发](https://www.cnblogs.com/hehe001/p/6156870.html)

# 构建知识体系
<br>[有讲解有说明](https://blog.csdn.net/loongembedded/article/details/65934877)很有参考意义，有目标有方法
<br>[c++知识体系](https://blog.csdn.net/LF_2016/article/details/52434575)
- 以面试题为目标，来补强知识体系
  - 搜集面试题
  - 对题目的答案进行编码实现，并对关联知识进行整理和总结

# UML
## UML工具 
1. visual paradim for uml ,Online版（web）和社区版（pc）免费使用，但功能有限制
除了UML图，还有一些软件工程实践的其他图（srum画布，数据库相关的ER图，敏捷过程中的用户故事）
2. processon  draw.io
3. PlantUML
4. starUml
## UML的基本知识
<br> [w3c uml](https://www.w3cschool.cn/uml_tutorial/uml_tutorial-c1gf28pd.html)
1. 面向对象分析与设计
- 面向对象的分析的最重要的目的是要设计一个系统来识别对象。确定对象后，确定它们之间的关系（对象的协作），并最终产生的设计。
- 面向对象的分析与设计的目的可以描述为：
  - 确定一个系统中的对象.（OOA）
  - 确定它们之间的关系. （OOD）
  - 做一个设计，使用面向对象的语言可以转换为可执行文件.（OOP）
- UML 的核心是图表，大致可以将这些图归类为结构图和行为图。
  - 结构图是由静态图，如类图，对象图等静态图；组件图（系统的静态实现视图） 部署图（节点以及节点之间的关系） 用例图
  - 行为图是由像序列图，协作图等动态图；状态图  活动图
- UML的要素   
  事物、关系、图
  - 结构事物
<br>类 class：属性和方法的集合
<br>接口 interface：类或组件 对外可见的动作，提供的服务（操作）
<br>协作：
<br>用例：
<br>组件：描述物理系统的一部分
<br>节点：在运行时存在的物理元素
   - 行为事物
<br>交互：消息
<br>状态机：对象的某种状态
  - 分组事物
<br>包 package：
  - 关系
  [示例1](https://www.cnblogs.com/hoojo/p/uml_design.html)    [示例2](https://www.cnblogs.com/alex-blog/articles/2704214.html)   [示例3 通俗易懂](https://blog.csdn.net/qq_39627843/article/details/82560798)
<br>泛化/继承：实线+三角形    三角形指向父类
<br>实现：虚线+三角形   三角形指向接口 
<br>组合：实线+实心菱形 菱形指向整体
组合也是关联关系的一种特例，是一种contains-a的关系，这种关系比聚合更强，也称为强聚合；
他同样体现整体与部分间的关系，但此时整体与部分是不可分的，整体的生命周期结束也就意味着部分的生命周期结束；
表现在代码层面，和关联关系是一致的，只能从语义级别来区分；
<br>聚合：实线+空菱形  菱形指向整体
是关联关系的一种特例，整体与部分的关系，即has-a 的关系，
但此时整体与部分之间是可分离的，他们可以具有各自的生命周期，部分可以属于多个整体对象，也可以为多个整体对象共享
代码层面就是类B是类A的属性，表现在代码层面，和关联关系是一致的，只能从语义级别来区分；
<br>关联：实线箭头（无箭头表示是双向关联）
是一种拥有的关系, 它使一个类知道另一个类的属性和方法
他体现的是两个类、或者类与接口之间语义级别的一种强依赖关系，比如我和我的朋友；
这种关系比依赖更强、不存在依赖关系的偶然性、关系也不是临时性的，一般是长期性的，而且双方的关系一般是平等的、关联可以是单向、双向的；
表现在代码层面，为被关联类B以类属性的形式出现在关联类A中，也可能是关联类A引用了一个类型为被关联类B的全局变量； 
<br>依赖：虚线箭头  箭头指向被使用类
可以简单的理解，就是一个类A使用到了另一个类B，是一种使用的关系,  即一个类的实现需要另一个类的协助
而这种使用关系是具有偶然性的、、临时性的、非常弱的，但是B类的变化会影响到A；
比如某人要过河，需要借用一条船，此时人与船之间的关系就是依赖；
表现在代码层面，为类B作为参数被类A在某个method方法中使用； 
  - 图
  类图、用例图、对象图、顺序图、协作图（uml 2.0为通信图）、活动图、状态图、组件图、部署图
    - [用例图的实例](https://blog.csdn.net/tiger_ibm/article/details/19337971)   
	- [用例图的实例2，这种风格很好](https://www.cnblogs.com/shinings/archive/2009/04/21/1440765.html)
2. 软件过程与UML图
- 软件过程中的一些文档
<br>[UML图与软件开发过程那点关系](https://www.cnblogs.com/tianguook/p/4044342.html)
<br> 在需求分析阶段,主要是Use Case Diagram（用例图）来填充，是面向系统分析人员，需求人员甚至是用户；
<br> 在设计阶段，即概要设计和详细设计说明书中是UML图的主要载体，他们可以以UML图为主，比如类图，交互图，活动图，状态图，顺序图等，面向分析人员和 编程人员；
<br> 而在其它文档中，就可以根基实际情况，实际需要，灵活应变，填充适当的UML图。
- 实例说明
  - [uml 在需求分析阶段的应用](https://www.cnblogs.com/fuhaots2009/p/3430666.html)
 <br>系统工作过程： 项目开始阶段的工作，包含立项、可行性分析等
 <br>用户需求：与系统相关的人员，了解人员执行的各个动作（收集）
 <br>需求分析及描述：以用户需求为基础，确定其中要实现的系统功能，然后再同用户进行更加深入的讨论交流，确定哪些需求是功能性，那些是非功能性的，哪些是软件系统的需求，哪些不是，哪些需求是可以实现的，哪些需求是无法实现或暂时无法实现。
 <br>用例分析：为了能够正确的找出系统的用例，需要确定系统的边界，找出系统的执行者  系统的边界/系统的执行者，系统的用例，所有的用例结合起来即系统的用例图
 <br>领域模型分析：这里所说的领域是用例的业务领域，就是描述一个现实世界中的某个问题的一些名词和术语。建立领域模型的第一步是找出描述这些问题的概念和术语，尽力能找到的所有的名词，动词，动词词组。根据这些可以形成类图
 <br>业务流程分析: 顺序图、活动图、状态图等，对具体的业务进行动态行为的分析
  - [基于UML的需求分析和系统设计](https://www.cnblogs.com/yunzhu/p/uml.html)
 <br>**《UML团队开发流程与管理》赖信仁** ,这本书与我之前看到过的任何一本UML的书籍都不同，它并没有详细介绍每种UML图形的各种元素和属性，而是重点讲述每种UML图形的使用场景，以及具体项目过程中如何进行分析和设计，并使用相应的UML图形精确传达设计意图。也就是说，它不是讲述UML是什么，而是结合具体项目实战讲述UML图形应该何时用、以及怎么用。
 <br>这个例子中的活动图、序列图、通信图的场景，具有很好的实用性
  - 需求分析之用例图 包含用例说明或用例描述 
  <br>[我们应该怎样做需求分析：用例说明](https://fangang.iteye.com/blog/1482165)
  - 业务流程分析之活动图、状态图<>
  <br>[活动图的详细介绍以及举例说明](https://blog.csdn.net/onlyou930/article/details/72629372)    
  Activity与Action
  分叉与汇合
  <br>[活动图实例](https://www.cnblogs.com/xiaolongbao-lzh/p/4591953.html) 前面部分与上一帖有重复，后面的几个例子是很有借鉴价值的
 
# 一些信息
<br>[写博客的收获和总结](https://juejin.im/post/5c02b2bce51d4533253f2f43)   此前六大设计原则也是该作者写的
