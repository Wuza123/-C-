#pragma once
#include<iostream>
using namespace std;

template <class T>
class myArr 
{
public:
	//有参构造 参数 容量
	myArr(int capacity) {
		cout << "myArr有参构造调用";
		this->m_Capacity = capacity;
		this->m_Size = 0;
		this->pAddress = new T[this->m_Capacity];
	}
	//析构函数
	~myArr() {
		if (this->pAddress != NULL) {
			cout << "myArr析构调用";
			delete[] this->pAddress;
			this->pAddress = NULL;//防止野指针
		}
	}
	//拷贝构造
	myArr(const myArr& arr) {
		cout << "myArr拷贝构造调用";
		this->m_Capacity = arr.m_Capacity;
		this->m_Size = arr.m_Size;
		//this->pAddress = arr.pAddress;错误的

		//深拷贝
		this->pAddress = new T[arr.m_Capacity];
		//将arr中的数据拷贝过来
		for (int i = 0; i < arr.m_Size; i++) {
			this->pAddress[i] = arr.pAddress[i];
		}
	}
	myArr& operator=(const myArr arr) {
		cout << "myArr的operator=调用";
		//先判断原来堆区是否有数据，如果有，先释放
		if (this->pAddress != NULL) {
			delete[] this->pAddress;
			this->pAddress = NULL;
			this->m_Capacity = 0;
			this->m_Size = 0;
		}
		this->m_Capacity = arr.m_Capacity;
		this->m_Size = arr.m_Size;
		this->pAddress = new T[arr.m_Capacity];
		//将arr中的数据拷贝过来
		for (int i = 0; i < arr.m_Size; i++) {
			this->pAddress[i] = arr.pAddress[i];
		}
		return *this;
	}
	//尾插法
	void myPush(const T& val) {
		//判断是否满
		if (this->m_Capacity == this->m_Size) {
			return;
		}
		this->pAddress[this->m_Size] = val;
		this->m_Size++;
	}
	//尾删
	void myPop() {
		if (this->m_Size == 0) {
			return;
		}
		this->m_Size--;//逻辑上的尾删
	}
	//通过下标的方式访问数据，重载[]
	T& operator[](int index) {
		return this->pAddress[index];
	}
private:
	T* pAddress;//指向堆区开辟的真实数组
	int m_Capacity;//数组容量
	int m_Size;//数组数量

};