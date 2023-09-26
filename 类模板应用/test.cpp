#include "myArr.hpp"

void test01() {
	myArr<int>arr1(5);
	myArr<int>arr2(arr1);//øΩ±¥ππ‘Ï
	myArr<int>arr3(100);
	arr3 = arr1;
}
int main() {
	test01();
}