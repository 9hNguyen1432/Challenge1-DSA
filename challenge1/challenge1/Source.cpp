#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;
//khai báo cấu trúc node
struct sNode{
	int key;
	vector < sNode* > nextNode;
};
struct sList {
	int MAX_LEVEL; // cập nhập liên tục mỗi khi thêm, xóa phần tử.
	vector<int> sizeOfLevel; // kích thước tầng
	sNode* headNode;// Node bắt đầu
	sNode* tailNode;// Node kết thúc
};
sList initList() {
	sList L;
	L.MAX_LEVEL = 0;
	L.headNode = NULL;
	L.tailNode = NULL;
	return L;
}
sNode* createSNode(int key, int level) {
	sNode* SN = new sNode;
	SN->key = key;
	for (int i = 0; i < level; i++) {
		SN->nextNode.push_back(NULL);
	}
	return SN;
}
int levelSNode(int key, int maxLevel) {
	int i = 0;
	while (key % 2 == 0) {
		key = key >> 1; //phép dịch bit, sang phải, nếu gặp số lẻ thì dừng, ví dụ 4 là 100, dịch lần 1 được 010, lần 2 được 001 -> dừng 
		i++; // đếm số lần dịch bit
	}
	return (1+i)%maxLevel;
}
void insertSNode(sList* L, int key);
int main() {
	/*sList L;
	L.headNode = new sNode;
	cout << sizeof(sList);
	return 0;*/

	return 0;
}