#include <iostream>
using namespace std;

template <class T>
void mySwap(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}
template <class T>
void mySort(T arr[], int len) {
	for (int i = 0; i < len; i++) {
		int max = i;
		for (int j = i + 1; j < len; j++) {
			if (arr[max] < arr[j]) {
				max = j;
			}
		}
		if (max != i) {
			swap(arr[i], arr[max]);
		}
	}
}
template <class T>
void myPrint(T arr[], int len) {
	for (int i = 0; i < len; i++) {
		cout << arr[i];
	}
}
int main() {
	char test1[] = "acfes";
	int num = sizeof(test1) / sizeof(char);
	mySort(test1, num);
	myPrint(test1, num);
	int test2[] = { 1,4,2,9,7 };
	mySort(test2, 5);
	myPrint(test2, 5);
	return 0;
}