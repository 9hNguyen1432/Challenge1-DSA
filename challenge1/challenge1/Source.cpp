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
	sNode* NULtail;// Node kết thúc
};
sList initList() {
	sList L;
	L.MAX_LEVEL = 0;
	L.headNode = NULL;
	L.NULtail = NULL;
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
void creatsList(sList& L) {
	L.headNode->key = numeric_limits<int>::min();
}

void searchSNode(sList L, int key) {
	vector<sNode*> path;
	sNode* tempNode = L.headNode;
	while (L.headNode->nextNode[L.MAX_LEVEL - 1]!= NULL) {

	}
}

void insertSNode(sList &L, int key) {
	int lv = levelSNode(key, L.MAX_LEVEL);// xác định level của node
	sNode* n = createSNode(key, lv); // tạo node với lv tương ứng
	if (L.headNode->nextNode[0] == NULL) {// ds rỗng, chèn đầu
		for (int i = 0; i < lv; i++) {
			n->nextNode[i] = L.headNode->nextNode[i]; // lần lượt các lv của n trỏ vào vị trí head đang trỏ
			L.headNode->nextNode[i] = n; // trỏ các con trỏ ở từng lv của head về n
		}
	}
	else {
		// thêm vào bất kì vị trí:
		
	}
}
int main() {
	/*sList L;
	L.headNode = new sNode;
	cout << sizeof(sList);
	return 0;*/

	return 0;
}