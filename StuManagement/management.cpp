#include "stdafx.h"
#include "management.h"



void Management::add(Student a)				//添加函数
{

	fstream fat_to("D:\\student.dat", ios::out | ios::binary | ios::app);		//以写方式、二进制方式、追加方式打开文件
	fat_to.write((char *)&a, sizeof(Student));				//写入文件，宽度为Student类的宽度
	fat_to.close();							//关闭文件
}

void Management::del(Student a)				//删除函数
{
	fstream fat("D:\\student.dat", ios::in | ios::binary);			//以读方式、二进制方式打开文件
	fat.seekg(0, ios::beg);				//定位文件流指针到文件开头
	Student temp;						//生成临时Student类类型变量temp
	fat.read((char *)&temp, sizeof(Student));			//读取文件，宽度为Student类的宽度
	while (!fat.eof())					//循环读取
	{
		_list.push_back(temp);			//在链表的尾部插入temp
		fat.read((char *)&temp, sizeof(Student));		
	}
	fat.close();
	list<Student>::iterator i = _list.begin();		//使用迭代器遍历全部数据
	for (; i != _list.end();)
	{
		if (i->id == a.id)
		{
			i = _list.erase(i);			//查找全部数据，当学号相同时，使用erase函数删除数据
		}
		else
			i++;
	}
	fstream fat_to("D:\\student.dat", ios::out | ios::binary);			//以写方式、二进制方式打开文件
	for (i = _list.begin(); i != _list.end(); ++i)				//将处理后的全部数据写入文件
		fat_to.write((char *)&(*i), sizeof(Student));
	fat_to.close();
}



void Management::mod(Student a)					  //修改函数
{
	fstream fat("D:\\student.dat", ios::in | ios::binary);		//以下大部分跟删除函数相同
	fat.seekg(0, ios::beg);
	Student temp;
	fat.read((char *)&temp, sizeof(Student));
	while (!fat.eof()) 
	{
		_list.push_back(temp);
		fat.read((char *)&temp, sizeof(Student));
	}
	fat.close();
	list<Student>::iterator i = _list.begin();
	for (; i != _list.end();++i)
	{
		if (i->id == a.id)							//当查找到的学号相同时
		{
			strcpy_s(i->name, (LPCSTR)a.name);			//赋值给i姓名、学号、高数、程序设计成绩
			strcpy_s(i->sex, (LPCSTR)a.sex);
			i->math = a.math;
			i->cpp = a.cpp;
		}
	}
	fstream fat_to("D:\\student.dat", ios::out | ios::binary);
	for (i = _list.begin(); i != _list.end(); ++i) 
		fat_to.write((char *)&(*i), sizeof(Student));
	fat_to.close();
}

int position = 0;						//设置全局变量position，用来传递点击的是哪一列

bool cmp(Student a, Student b);

void Management::sort(int flag)					//排序函数
{
	fstream fat("D:\\student.dat", ios::in | ios::binary);		//大部分与删除函数相同
	fat.seekg(0, ios::beg);
	Student temp;
	fat.read((char *)&temp, sizeof(Student));
	while (!fat.eof())
	{
		_list.push_back(temp);
		fat.read((char *)&temp, sizeof(Student));
	}
	fat.close();
	position = flag;										//将列数赋值给position
	_list.sort(cmp);										//调用cmp函数
	list<Student>::iterator i = _list.begin();
	fstream fat_to("D:\\student.dat", ios::out | ios::binary);
	for (i = _list.begin(); i != _list.end(); ++i) 
		fat_to.write((char *)&(*i), sizeof(Student));
	fat_to.close();
}

bool cmp(Student a, Student b)				//cmp函数用来根据列数排序
{
	switch (position)
	{
	case 0:								//从小到大
		return a.id < b.id;
		break;
	case 1:
		return 0;
		break;
	case 2:
		return 0;
		break;
	case 3:
		return a.math < b.math;
		break;
	case 4:
		return a.cpp < b.cpp;
		break;
	case 5:								//从大到小
		return a.id > b.id;
		break;
	case 6:
		return 0;
		break;
	case 7:
		return 0;
		break;
	case 8:
		return a.math > b.math;
		break;
	case 9:
		return a.cpp > b.cpp;
		break;
	default:
		return 0;
	}
}

void Management::show()							//显示函数
{
	fstream fat("D:\\student.dat", ios::in | ios::binary | ios::app);		//以下跟删除函数前半部分相同
	fat.seekg(0, ios::beg);
	Student temp;
	fat.read((char *)&temp, sizeof(Student));
	while (!fat.eof()) 
	{
		_list.push_back(temp);
		fat.read((char *)&temp, sizeof(Student));
	}
	fat.close();
}


