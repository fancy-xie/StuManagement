#pragma once
#include "student.h"
#include<fstream>
#include<iostream>
#include<list>
using namespace std;



class Management				//建立Management类
{
public:
	void add(Student a);		//添加函数
	void del(Student a);		//删除函数
	void mod(Student a);		//修改函数
	void sort(int flag);		//排序函数
	void show();				//显示函数
	list<Student>_list;			//生成Student类list链表_list
};


