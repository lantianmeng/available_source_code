# 关于智能指针 auto_ptr/unique_ptr/shared_ptr/weak_ptr
<br>[窥见C++11智能指针](https://cloud.tencent.com/developer/article/1486285)  腾讯技术工程官方号的专栏文章，写的详细而又深入浅出

1. auto_ptr
- 创建对象
  + 使用匿名指针  **推荐**
  auto_ptr<int> p(new int(10));
  + 使用裸指针
  int *p = new int(1);
  auto_ptr<int> p1(p);

- 避免多个auto_ptr对象指向同一个对象
<br>因为智能指针是在离开作用域时自动delete其拥有的指针的，删除同一个指针会导致未定义的行为
```
int *p = new int(1);
auto_ptr<int> p1(p);
auto_ptr<int> p2(p); 
```
- 不能管理动态数组  因为auto_ptr的内部的析构函数实现是使用delete，而不是delete []
```
int *p = new int[10]{0};
auto_ptr<int> p1(p); //p1析构时，只会删除第一个元素，造成内存泄漏
```
- 不支持赋值或复制
<br>因为赋值后发生控制权转移后，原auto_ptr为空
```
	auto_ptr<int> p_i(new int(10));
	auto_ptr<int> p_j = p_i; //控制权转移
	//*p_i += 10; //这里程序崩溃
```

2. unique_ptr
<br>其含义是同一块内存，只能由一个拥有者。即独占其所指向的对象
<br>基本用法同auto_ptr，但改变其一些缺点，主要如下：

- 赋值或复制时，编译时直接报错，而不是运行时崩溃.
- 提供指针所有权转移的方法：move方法，但原unique_ptr失效，继续使用则会出现类似auto_ptr的崩溃。故对unique_ptr应该慎用move
```
	unique_ptr<int> u_i(new int(10));  //匿名指针
	//unique_ptr<int> u_j = u_i; //这里编译时就报错,可避免指针所有权转移导致的崩溃
	
	unique_ptr<int> u_j = move(u_i);
	//*u_i += 10; //这里程序崩溃
```
- 可以管理动态数组 因为其析构函数支持delete [] 
<br>(vs中的实现可以研究下, 主要是c++11中的enable_if/type等的理解和使用)
```
	unique_ptr<int[]> u_k(new int[10]());
	int *ptemp = u_k.get();
	ptemp[1] = 5;
	ptemp[8] = 15;
	for (int i = 0; i < 10; ++i)
	{
		cout << " " << ptemp[i];
	}
```

3. shared_ptr
<br>使用引用计数的原理，即同一块内存设置一个引用计数，shared_ptr有赋值则引用计数加1，shared_ptr生命周期到期则减1，引用计数为0时则释放内存。故可以用于赋值或复制
- 提供make_shared来构建对象 用匿名指针或make_shared来构建是最安全的
```
    shared_ptr<int> s_i(new int(10));
	shared_ptr<int> s_j = std::make_shared<int>(10);
```

- shared_ptr作为函数参数的情况
  + 作为参数时给默认值  ```std::shared_ptr<A> data = nullptr```
  + shared_ptr作为函数形参时，要看成对象。如果用来返回值时，要加引用符号&
  + 作为局部变量 
  <br>[shared_ptr作为局部变量](https://www.cnblogs.com/kilen/p/7128600.html)  
  <br>[shared_ptr使用注意点，线程安全以及与weak_ptr配合使用](https://blog.csdn.net/man_sion/article/details/77196766)

- shared_ptr管理动态数组，需要自定义析构的方法
	
- 不能使用指向智能指针的指针，因为引用计数不会加1，容易产生野指针导致异常
```
	shared_ptr<int> s_k = s_j;
	shared_ptr<int> *p_s_k = &s_k;
	cout << (*p_s_k).use_count() << endl;
```

- 循环引用的问题
<br>常见的场景类A中有类B的子对象，类B中有类A的子对象（A引用B，B引用A）
```
    
	class SB;
    class SA
    {
    public:
    	int ia;
    	//shared_ptr<SB> b;
    	weak_ptr<SB> b;
    };
    
    class SB
    {
    public:
    	int ib;
    	shared_ptr<SA> a;
    }; 
	 
	shared_ptr<SA> c_a = std::make_shared<SA>();
	shared_ptr<SB> c_b = std::make_shared<SB>();

	c_a->b = c_b;
	c_b->a = c_a;//c_a c_b的强引用计数永远大于等于1，故不会释放申请的内存，导致内存泄漏
```
- 使用weak_ptr，则可以解决shared_ptr循环引用的问题
    <br>有些情况，A类只是需要引用B类，B类对象的创建不在A类，B类也不管理A类对象的释放，此种情况weak_ptr就应运而生了
	<br>使用shared_ptr赋值给weak_ptr，不会增加强引用计数（strong count），取而代之的是增加一个弱引用计数(weak count)，弱引用计数不会影响指针的生命周期

4. weak_ptr
<br>weak_ptr是为了配合shared_ptr而引入的一种智能指针，它指向一个由shared_ptr管理的对象而不影响所指对象的生命周期，也就是将一个weak_ptr绑定到一个shared_ptr不会改变shared_ptr的引用计数。
<br>weak_ptr并没有重载operator->和operator *操作符，因此不可直接通过weak_ptr使用对象，典型的用法是调用其lock函数来获得shared_ptr示例，进而访问原始对象。
```
	shared_ptr<int> sp_i = std::make_shared<int>(34);
	weak_ptr<int> w_i = sp_i;

	//sp_i.reset();
	if (w_i.expired())
	{
		cout << "shared ptr " << endl;
	}

	shared_ptr<int> sp_j = w_i.lock();//获取weak_ptr指向的对象， 如果对象存在，lock()函数返回一个指向共享对象的shared_ptr，否则返回一个空
```

5. 总结
<br>auto_ptr是C++98中推出来的，后续的其他智能指针对其进行了优化。后续不常用
<br>unique_ptr的优势在于可以极其方便的管理动态数组
<br>shared_ptr的优势在于使用引用计数，支持赋值和复制。比较常用，但需注意循环引用的问题
<br>weak_ptr是配合shared_ptr来使用的
