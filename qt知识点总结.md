[qt知识图谱](https://blog.csdn.net/kyl282889543/article/details/86759561)

# 知识点
1. 添加信号/槽的两种方法
- 使用qt默认的命名方式  on_接收对象名称_事件  ，如on_btnOk_clicked()
- 使用connect
```
class CSignal : public QWidget
{
	Q_OBJECT
public:
	CSignal(QWidget *parent = 0);
	~CSignal();

	void Init();   
private slots:
    //void OnBtnOK();
	//void OnBtnCancel();
    //void OnBtnQuit();
	void on_test1_clicked();
private:
	Ui::MySignal ui;
};

void CSignal::Init()
{
	//connect(m_AllSignal.BtnOK, SIGNAL(clicked()), this, SLOT(OnBtnOK()));
	//connect(m_AllSignal.BtnCancel, SIGNAL(clicked()), this, SLOT(OnBtnCancel()));
	//connect(m_AllSignal.BtnQuit, SIGNAL(clicked()), this, SLOT(on_BtnQuit_clicked()));
}

void CSignal::on_test1_clicked()
{
	//close();
	QMessageBox msg;
	msg.setText("hello");
	msg.exec();
}
```
- 使用connect需要注意，signals/slots中带参数时，易出问题导致槽函数不响应
    + 带参数时，携带形参的名字
	<br>如：connect(this, SIGNAL(update_msg(const QString& msg)), this, SLOT(on_update_msg(const QString& msg)));  中的“msg”，会导致槽函数不响应
    + 带参数时，参数的类型，qt识别不了该对象（在vs的“输出”窗口，会出现QMetaObject的报错 ）
	<br>[qRegisterMetaType的使用](https://blog.csdn.net/wadfji/article/details/54406767)
```
	class CSignal : public QWidget
    {
    	Q_OBJECT
    public:
	void Init();  
	signals:
	void update_msg(const QString& msg);
    private slots:
	void on_update_msg(const QString& msg);
    private:
    	Ui::MySignal ui;
    };
	
	void CSignal::Init()
    {
    	//connect(this, SIGNAL(update_msg(const QString& msg)), this, SLOT(on_update_msg(const QString& msg)));//**这是错误的方式**
		connect(this, SIGNAL(update_msg(const QString&)), this, SLOT(on_update_msg(const QString&))); //这是正确的方式
    }
    
    void CSignal::on_update_msg(const std::string& msg)
    {
	ui.showMsg->setText(msg.c_str());//更新msg到界面的showMsg label上面
    }
```
   
```
	
	//在CPP文件的开头声明std::string类型
	#include <QMetaType>   
    Q_DECLARE_METATYPE(std::string);

	void CSignal::Init()
    {
    	connect(this, SIGNAL(update_msg(const std::string& msg)), this, SLOT(on_update_msg(const std::string& msg)));//**这是错误的方式**，qt识别不了std::string类型
		//正确的方式，可以用QString
		connect(this, SIGNAL(update_msg(const QString&)), this, SLOT(on_update_msg(const QString&))); //这是正确的方式
		
		//可以用qRegisterMetaType来注册std::string类型  
		qRegisterMetaType<std::string>();
	    connect(this, SIGNAL(update_msg(const std::string&)), this, SLOT(on_update_msg(const std::string&)));
		
		//如果是自定义的类型，类/结构体，必须使用qRegisterMetaType来注册该类/结构体类型
		//方式同上，先声明，再注册
		Q_DECLARE_METATYPE(vector<PLC_PT_PARAM>);
		
	    qRegisterMetaType<vector<PLC_PT_PARAM>>();
	    connect(INST_CSignals, SIGNAL(plcPtChanged(vector<PLC_PT_PARAM>)), this, SLOT(OnPlcPtChanged(vector<PLC_PT_PARAM>)));
    }

```
- Qt5中，connect的新用法:lamada表达式和指向成员函数的指针
[Qt的信号槽机制介绍(含Qt5与Qt4的差异对比)](https://blog.csdn.net/qq78442761/article/details/80653472)
```
private:// Qt5的槽函数，声明为private即可，不需要槽函数声明为private slots
	void on_Bold_update_state(int nState);
	void on_Italic_update_state(int nState);
	void on_selection_changed();
private slots:
	void on_update_msg(const std::string& msg);
	
	//qt5 槽函数的新方式
	connect(ui.cbBold, &QCheckBox::stateChanged, [=](int nState){m_bCheckedBold = nState == Qt::CheckState::Checked ? true : false;});
	connect(ui.cbBold, &QCheckBox::stateChanged, this, &CSignal::on_Bold_update_state);
```

2. 子线程（回调函数）需要更新数据到界面
- 直接调用控件的方法，更新数据   
<br> label button，这种简单的控件以及操作频率低时，没有问题；但存在风险，容易导致崩溃
- 自定义信号和槽
<br>如上述CSignal类，自定义了信号update_msg，以及槽函数on_update_msg  ,再Init方法中，调用connect将信号update_msg与槽on_update_msg关联起来
<br>当子线程/回调函数触发的时候，发射信号update_msg
```
void on_recv_msg()
{
    string temp = "hello world";

	//更新界面
	//ui.showMsg->setText(temp.c_str());
	emit update_msg(temp.c_str());
}
```
<br>信号与槽，可以在不同的窗口
如上述CSignal窗口中，定义信号update_usg， 但在EDCDemo主窗口中定义槽函数on_update_msg(msg更新到test按钮上)
```
class EDCDemo : public QMainWindow
{
	Q_OBJECT

public:
	EDCDemo(QWidget *parent = 0);
	~EDCDemo();

	void WidgetsInit();

private slots:
void on_update_msg(const QString& msg);  //接收数据，更新到按钮
private:
	Ui::EDCDemoClass ui;
	CSignal *m_signal;
	std::shared_ptr<std::thread> recv_msg_callback;
};

void EDCDemo::WidgetsInit()
{
    connect(m_signal, SIGNAL(update_msg(const QString& )), this, SLOT(on_update_msg(const QString& )));
}


void EDCDemo::on_update_msg(const QString& msg)
{
	ui.test->setText(msg);
}

```
3. 布局管理器
<br>[使用qt designer进行布局](https://blog.csdn.net/jxwzh/article/details/81673223)，自己建一个工程，尝试一个各种布局
<br>使用布局后，就是一个整体来移动和改变大小。如果要单独改变某个控件的大小，需要先break layout(qt designer工具栏/快捷键 ctrl+0)
- Splitter   
<br>选中所需的控件，点击工具栏上的H Splitter/V Splitter
<br>使用QSplitter，通过代码去进行布局
- Grid Layout

- 各个布局方式，可以同时使用，进行嵌套布局

- 使用代码进行布局
<br>[内容、间距和QSpaceItem](https://blog.csdn.net/hyongilfmmm/article/details/83028903)
```
	cbBold = new QCheckBox("bold");
	cbItalic = new QCheckBox("italic");
	lyStyle = new QHBoxLayout;
	lyStyle->addWidget(cbBold);
	lyStyle->addWidget(cbItalic); 
	
	rbBlack = new QRadioButton("black");
	rbRed = new QRadioButton("red");
	lyColor = new QVBoxLayout;
	lyColor->addWidget(rbBlack);
	lyColor->addWidget(rbRed);

	inputText = new QPlainTextEdit("hello\nwelcome");
	
    QVBoxLayout * main_ly = new QVBoxLayout;
	main_ly->addLayout(lyStyle);
	main_ly->addSpacing(50);  //添加一个间距
	main_ly->addLayout(lyColor);
	main_ly->addSpacing(100);
	main_ly->addWidget(inputText);
	setLayout(main_ly);
```
- QStackedLayout  可以用于多个页面进行切换
<br>[QStackedLayout示列](https://blog.csdn.net/naibozhuan3744/article/details/80728783)  可用于切换菜单的界面，如pc版的微信，即可使用这个版本

4. QT new控件，但不delete，为什么没有内存泄露
<br>[从 Qt 的 delete 说开来](https://blog.csdn.net/dbzhang800/article/details/6300025)
<br>[WINDOWS下内存泄漏检测工具VLD(Visual Leak Detector)的使用](https://blog.csdn.net/xp178171640/article/details/80828530)  vld检测qt程序的内存泄漏
- 以下情况new之后，不需delete
  + QObject及其派生类的对象，如果其parent非0，那么其parent析构时会析构该对象
  + 有些类的对象可以接收设置一些特别的标记 [窗口接收close消息后自动释放资源](https://www.cnblogs.com/findumars/p/6201221.html)
  <br>QWidget及其派生类的对象，可以设置 Qt::WA_DeleteOnClose 标志位(当close时会析构该对象)
  <br>QAbstractAnimation派生类的对象，可以设置 QAbstractAnimation::DeleteWhenStopped
  <br>QRunnable::setAutoDelete()
  <br>MediaSource::setAutoDelete()
  ```
  class test_new :public QWidget
{
	QOBJECT_H
public:
	test_new()
	{
		//1. parent 指定this
		//lable = new QLabel("hello",this);
		lable = new QLabel("hello");
		lable->setGeometry(0, 0, 100, 100);
		lable->setAttribute(Qt::WA_DeleteOnClose);  //3. 这种方式还是有内存泄漏，因为Qt::WA_DeleteOnClose在窗口触发close消息时才有效
		//lable->show();  //单独显示窗口，点击close后，上述标识才有效
                
		v = new VBoxLayout(this);  //4. 让V-layout作为子窗口，label添加到v-layout中即可
		v.addWidget(label);
		setLayout(v);
		
		setWindowTitle("test_new");

		//connect(this, &QWidget::closeEvent, [=] {delete lable; });
	}
	//2. 析构函数中删除
	//~test_new(){ delete lable; }
	//~test_new(){ lable->close(); }
private:
	QLabel *lable;
	QVBoxLayout v;
};
  ```
- 理解QObject管理父子关系 ** 主要是上述连接**
  <br>如果没有指定parent，则需要delete。（指定parent后，可能会影响对某些事件的捕获。因为事件被父窗口捕获后，不会传递到子窗口，导致不会响应）
  <br>窗口的父子关系理顺，才能考虑是使用传入parent，还是设置Qt::WA_DeleteOnClose属性
# 问题点
1. 槽函数不响应
- VS的工程中添加class，继承Qt类。默认没有Q_OBJECT宏。也就无法使用signals。
- 把Q_OBJECT宏补上去，重新编译报错如下：
<br>error C1083: 无法打开源文件: “GeneratedFiles\Debug\moc_SettingWidget.cpp”: No such file or directory	
<br>清理了重新生成也不行。
<br>**解决方法**：随便修改一下目标类的.h文件，目的是让该.h文件变成(xxx.h*)。然后保存，再 生成/编译即可
2. Qt QComboBox之无法将参数 2 从“overloaded-function”转换为“const char *”上下文不允许消除重载函数的歧义
- 原因
<br>QComboBox 有些信号是重载的，如currentIndexChanged信号，其参数有int型和QString类型这2种
<br>使用Qt5风格的connect连接信号和槽时（```connect(ui.cb_City, &QComboBox::currentIndexChanged, this, [=](int index){});```），就会出现上述错误
- 解决方法如下：
<br>[可以参考的解决方法](https://blog.csdn.net/sz76211822/article/details/98586105)
<br>信号的指针类型进行强制转换：
```
connect(ui.cb_City, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, [=](int index){});
```
