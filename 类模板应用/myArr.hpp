#pragma once
#include<iostream>
using namespace std;

template <class T>
class myArr 
{
public:
	//�вι��� ���� ����
	myArr(int capacity) {
		cout << "myArr�вι������";
		this->m_Capacity = capacity;
		this->m_Size = 0;
		this->pAddress = new T[this->m_Capacity];
	}
	//��������
	~myArr() {
		if (this->pAddress != NULL) {
			cout << "myArr��������";
			delete[] this->pAddress;
			this->pAddress = NULL;//��ֹҰָ��
		}
	}
	//��������
	myArr(const myArr& arr) {
		cout << "myArr�����������";
		this->m_Capacity = arr.m_Capacity;
		this->m_Size = arr.m_Size;
		//this->pAddress = arr.pAddress;�����

		//���
		this->pAddress = new T[arr.m_Capacity];
		//��arr�е����ݿ�������
		for (int i = 0; i < arr.m_Size; i++) {
			this->pAddress[i] = arr.pAddress[i];
		}
	}
	myArr& operator=(const myArr arr) {
		cout << "myArr��operator=����";
		//���ж�ԭ�������Ƿ������ݣ�����У����ͷ�
		if (this->pAddress != NULL) {
			delete[] this->pAddress;
			this->pAddress = NULL;
			this->m_Capacity = 0;
			this->m_Size = 0;
		}
		this->m_Capacity = arr.m_Capacity;
		this->m_Size = arr.m_Size;
		this->pAddress = new T[arr.m_Capacity];
		//��arr�е����ݿ�������
		for (int i = 0; i < arr.m_Size; i++) {
			this->pAddress[i] = arr.pAddress[i];
		}
		return *this;
	}
	//β�巨
	void myPush(const T& val) {
		//�ж��Ƿ���
		if (this->m_Capacity == this->m_Size) {
			return;
		}
		this->pAddress[this->m_Size] = val;
		this->m_Size++;
	}
	//βɾ
	void myPop() {
		if (this->m_Size == 0) {
			return;
		}
		this->m_Size--;//�߼��ϵ�βɾ
	}
	//ͨ���±�ķ�ʽ�������ݣ�����[]
	T& operator[](int index) {
		return this->pAddress[index];
	}
private:
	T* pAddress;//ָ��������ٵ���ʵ����
	int m_Capacity;//��������
	int m_Size;//��������

};