#ifndef RECEIVER_H
#define RECEIVER_H

//命令的接收类，即命令实际执行的类
class Light
{
public:
	void On(){ std::cout << "--On--" << std::endl; }
	void Off(){ std::cout << "--Off--" << std::endl; }
};

#endif