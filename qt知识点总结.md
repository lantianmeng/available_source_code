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

# 问题点
1. 槽函数不响应
- VS的工程中添加class，继承Qt类。默认没有Q_OBJECT宏。也就无法使用signals。
- 把Q_OBJECT宏补上去，重新编译报错如下：
<br>error C1083: 无法打开源文件: “GeneratedFiles\Debug\moc_SettingWidget.cpp”: No such file or directory	
<br>清理了重新生成也不行。
<br>**解决方法**：随便修改一下目标类的.h文件，目的是让该.h文件变成(xxx.h*)。然后保存，再 生成/编译即可
