#pragma once
#include "student.h"
#include<fstream>
#include<iostream>
#include<list>
using namespace std;



class Management				//����Management��
{
public:
	void add(Student a);		//��Ӻ���
	void del(Student a);		//ɾ������
	void mod(Student a);		//�޸ĺ���
	void sort(int flag);		//������
	void show();				//��ʾ����
	list<Student>_list;			//����Student��list����_list
};


