#include "stdafx.h"
#include "management.h"



void Management::add(Student a)				//��Ӻ���
{

	fstream fat_to("D:\\student.dat", ios::out | ios::binary | ios::app);		//��д��ʽ�������Ʒ�ʽ��׷�ӷ�ʽ���ļ�
	fat_to.write((char *)&a, sizeof(Student));				//д���ļ������ΪStudent��Ŀ��
	fat_to.close();							//�ر��ļ�
}

void Management::del(Student a)				//ɾ������
{
	fstream fat("D:\\student.dat", ios::in | ios::binary);			//�Զ���ʽ�������Ʒ�ʽ���ļ�
	fat.seekg(0, ios::beg);				//��λ�ļ���ָ�뵽�ļ���ͷ
	Student temp;						//������ʱStudent�����ͱ���temp
	fat.read((char *)&temp, sizeof(Student));			//��ȡ�ļ������ΪStudent��Ŀ��
	while (!fat.eof())					//ѭ����ȡ
	{
		_list.push_back(temp);			//�������β������temp
		fat.read((char *)&temp, sizeof(Student));		
	}
	fat.close();
	list<Student>::iterator i = _list.begin();		//ʹ�õ���������ȫ������
	for (; i != _list.end();)
	{
		if (i->id == a.id)
		{
			i = _list.erase(i);			//����ȫ�����ݣ���ѧ����ͬʱ��ʹ��erase����ɾ������
		}
		else
			i++;
	}
	fstream fat_to("D:\\student.dat", ios::out | ios::binary);			//��д��ʽ�������Ʒ�ʽ���ļ�
	for (i = _list.begin(); i != _list.end(); ++i)				//��������ȫ������д���ļ�
		fat_to.write((char *)&(*i), sizeof(Student));
	fat_to.close();
}



void Management::mod(Student a)					  //�޸ĺ���
{
	fstream fat("D:\\student.dat", ios::in | ios::binary);		//���´󲿷ָ�ɾ��������ͬ
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
		if (i->id == a.id)							//�����ҵ���ѧ����ͬʱ
		{
			strcpy_s(i->name, (LPCSTR)a.name);			//��ֵ��i������ѧ�š�������������Ƴɼ�
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

int position = 0;						//����ȫ�ֱ���position���������ݵ��������һ��

bool cmp(Student a, Student b);

void Management::sort(int flag)					//������
{
	fstream fat("D:\\student.dat", ios::in | ios::binary);		//�󲿷���ɾ��������ͬ
	fat.seekg(0, ios::beg);
	Student temp;
	fat.read((char *)&temp, sizeof(Student));
	while (!fat.eof())
	{
		_list.push_back(temp);
		fat.read((char *)&temp, sizeof(Student));
	}
	fat.close();
	position = flag;										//��������ֵ��position
	_list.sort(cmp);										//����cmp����
	list<Student>::iterator i = _list.begin();
	fstream fat_to("D:\\student.dat", ios::out | ios::binary);
	for (i = _list.begin(); i != _list.end(); ++i) 
		fat_to.write((char *)&(*i), sizeof(Student));
	fat_to.close();
}

bool cmp(Student a, Student b)				//cmp��������������������
{
	switch (position)
	{
	case 0:								//��С����
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
	case 5:								//�Ӵ�С
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

void Management::show()							//��ʾ����
{
	fstream fat("D:\\student.dat", ios::in | ios::binary | ios::app);		//���¸�ɾ������ǰ�벿����ͬ
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


