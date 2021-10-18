#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;
//khai báo cấu trúc node
struct sNode {
	int key;
	vector < sNode* > nextNode;
};
struct sList {
	int MAX_LEVEL; // cập nhập liên tục mỗi khi thêm, xóa phần tử.
	int sizeOfList; // kích thước list
	sNode* headNode;// Node bắt đầu
	sNode* NULtail;// Node kết thúc
};
int insertSNode(sList& L, int key, bool createFlag=false);
sList initList() {
	sList L;
	L.MAX_LEVEL = 0;
	L.headNode = new sNode;
	L.NULtail = new sNode;
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
	if (key == 0) {
		return 1;
	}
	int i = 0;
	while (key % 2 == 0) {
		key = key >> 1; //phép dịch bit, sang phải, nếu gặp số lẻ thì dừng, ví dụ 4 là 100, dịch lần 1 được 010, lần 2 được 001 -> dừng 
		i++; // đếm số lần dịch bit
	}
	return 1 + (i % maxLevel);
}
void deleteList(sList& L) {
	if (L.MAX_LEVEL != 0) {
		while (L.headNode != L.NULtail) {
			sNode* temp = L.headNode;
			L.headNode = L.headNode->nextNode[0];
			delete temp;
		}
		for (int i = 0; i < L.MAX_LEVEL; i++) {
			L.headNode->nextNode.pop_back();
			L.NULtail->nextNode.pop_back();
		}
		L.MAX_LEVEL = 0;
		L.sizeOfList = 0;
	}
}
void createSList(sList& L) {
	deleteList(L);
	cout << "Nhap so phan tu: ";
	cin >> L.sizeOfList;
	int key;
	L.MAX_LEVEL = 0.2 * L.sizeOfList;
	if (L.MAX_LEVEL == 0) {
		L.MAX_LEVEL = 1;
	}
	L.headNode->key = numeric_limits<int>::min();
	L.NULtail->key = numeric_limits<int>::max();
	for (int i = 0; i < L.MAX_LEVEL; i++) {
		L.NULtail->nextNode.push_back(NULL);
		L.headNode->nextNode.push_back(L.NULtail);
	}
	for (int i = 0; i < L.sizeOfList; i++) {
		cout << "nhap phan tu thu" << i << " : ";
		cin >> key;
		insertSNode(L, key, true);
	}
}

vector<sNode*> searchSNode(sList L, int key) {
	vector<sNode*> path;
	int curLevel = L.MAX_LEVEL - 1;
	sNode* tempNode = L.headNode;
	if (L.headNode->nextNode[curLevel] ==L.NULtail) {
		return path;
	}
	while (tempNode != L.NULtail || curLevel != 0 ) {
		if (key < tempNode->nextNode[curLevel]->key) {
			if (curLevel == 0) {
				return path;
			}
			curLevel--;
		}
		else if (key >= tempNode->nextNode[curLevel]->key) { // lớn hơn
			tempNode = tempNode->nextNode[curLevel];
			path.push_back(tempNode);
			if (key == tempNode->key) {
				return path;
			}
		}
	}
}
void displaySearch(sList L) {
	int key;
	cout << "Input search value: ";
	cin >> key;
	vector<sNode*> path = searchSNode(L, key); 
	if (path[path.size() - 1]->key == key) {
		cout << "Level of " << key << " : ";
		cout << path[path.size() - 1]->nextNode.size() << endl;
		cout << "Traverse path: ";
		for (int i = 0; i < path.size()-1; i++) {
			cout << path[i]->key << " ";
		}
	}
}
int insertSNode(sList& L, int key, bool creatFlag) {
	if (L.headNode->nextNode[0] == L.NULtail) {// ds rỗng, chèn đầu
		int lv = levelSNode(key, L.MAX_LEVEL);// xác định level của node
		sNode* n = createSNode(key, lv); // tạo node với lv tương ứng
		for (int i = 0; i < lv; i++) {
			n->nextNode[i] = L.headNode->nextNode[i]; // lần lượt các lv của n trỏ vào vị trí head đang trỏ
			L.headNode->nextNode[i] = n; // trỏ các con trỏ ở từng lv của head về n
		}
	}
	else {
		// thêm vào bất kì vị trí:
		sNode** preNodeInsert = new sNode * [L.MAX_LEVEL]; // danh sách các node mà đứng trước node cần thêm theo từng level, dùng để thêm node vào sau đó.
		int curLevel = L.MAX_LEVEL - 1; // dùng để duyệt từ trên xuống
		sNode* tempNode = L.headNode;
		while (true) { // dùng node tạm chạy từ đầu đến cuối, dừng khi chạy hết lv1
			if (key < tempNode->nextNode[curLevel]->key) { // nếu khóa thêm nhỏ hơn giá trị node sau node tạm.
				preNodeInsert[curLevel] = tempNode; // thêm node đó vào danh sách node trước.
				if (curLevel == 0) { // nếu đang ở lv1 thì thêm vào
					if (creatFlag == false) {
						L.sizeOfList++;
						int temp = L.MAX_LEVEL;
						L.MAX_LEVEL = 0.2 * L.sizeOfList;
						if (L.MAX_LEVEL != temp) {
							L.headNode->nextNode.push_back(L.NULtail);
							L.NULtail->nextNode.push_back(NULL);
						}
					}
					int lv = levelSNode(key, L.MAX_LEVEL);// xác định level của node
					sNode* n = createSNode(key, lv); // tạo node với lv tương ứng
					for (; curLevel < lv; curLevel++) {
						n->nextNode[curLevel] = preNodeInsert[curLevel]->nextNode[curLevel]; // từng lv tương ứng của node cần thêm trỏ vào node tiếp theo.
						preNodeInsert[curLevel]->nextNode[curLevel] = n;// các node trước trỏ vào node cần thêm
					}
					delete preNodeInsert;// xóa bộ nhớ
					return 0;
				}
				curLevel--;
			}
			else if (key == tempNode->nextNode[curLevel]->key) {// vị trí bằng
				return -1; //return chứng tỏ k thêm được
			}
			else { // lớn hơn
				tempNode = tempNode->nextNode[curLevel]; // chạy đến node tiếp theo 
			}
		}
	}
}
int deleteSNode(sList& L, int key) {
	if (L.headNode->nextNode[0] == L.NULtail) {// ds rỗng, báo rỗng
		return -1;
	}
	else {
		// tìm và xóa vị trí có giá trị key
		sNode** preNodeInsert = new sNode * [L.MAX_LEVEL]; // danh sách các node mà đứng trước node cần xóa theo từng level
		int curLevel = L.MAX_LEVEL - 1; // dùng để duyệt từ trên xuống
		sNode* curNode = L.headNode;
		while (true) {
			if (key <= curNode->nextNode[curLevel]->key) { // nếu khóa thêm nhỏ hơn hoặc bằng giá trị node sau node tạm.
				preNodeInsert[curLevel] = curNode; // thêm node đó vào danh sách node trước.
				if (curLevel == 0) { // nếu đang ở lv1 
					if (key == curNode->nextNode[curLevel]->key) { // nếu tim được khóa key
						sNode* tempNode = curNode->nextNode[curLevel];
						for (; curLevel < tempNode->nextNode.size(); curLevel++) {
							preNodeInsert[curLevel]->nextNode[curLevel] = tempNode->nextNode[curLevel];// các node trước trỏ vào node cần thêm
						}
						delete tempNode;
						delete preNodeInsert;// xóa bộ nhớ
						L.sizeOfList--;
						L.MAX_LEVEL = 0.2 * L.sizeOfList;
						return 0;
					}
					else {
						delete preNodeInsert;// xóa bộ nhớ
						return -1;
					}
				}
				curLevel--;
			}
			else { // lớn hơn
				curNode = curNode->nextNode[curLevel]; // chạy đến node tiếp theo 
			}
		}
	}
}
void disPlay(sList L) {
	int curLevel = L.MAX_LEVEL - 1;
	while (curLevel >= 0) {
		cout << "Level " << curLevel + 1 << " : ";
		sNode* curNode = L.headNode->nextNode[curLevel];
		while (curNode != L.NULtail) {
			cout << curNode->key << " ";
			curNode = curNode->nextNode[curLevel];
		}
		cout << endl;
		curLevel--;
	}
}
void sizeOfSList(sList L) {
	if (L.MAX_LEVEL == 0) {
		cout << "List is empty!!";
	}
	else {
		cout << "Max level: " << L.MAX_LEVEL<< endl;
		int curLevel = 0;
		while (curLevel < L.MAX_LEVEL) {
			cout << "size of level " << curLevel + 1 << " : ";
			int i = 0;
			sNode* curNode = L.headNode->nextNode[curLevel];
			while (curNode != L.NULtail) {
				i++;
				curNode = curNode->nextNode[curLevel];
			}
			cout << i << endl;
			curLevel++;
		}
	}
}
int main() {
	sList L = initList();
	createSList(L);
	disPlay(L);
	sizeOfSList(L);
	displaySearch(L);
	return 0;
}