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
	int sizeOfList; // kích thước list
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
	return (1+i) % maxLevel;
}
void creatsList(sList& L) {
	L.headNode->key = numeric_limits<int>::min();
}

vector<sNode*> searchSNode(sList L, int key) {
	vector<sNode*> path;
	int curLevel = L.MAX_LEVEL - 1;
	sNode* tempNode = L.headNode;
	if (L.headNode->nextNode[curLevel] != NULL) {
		return path;
	}
	while (tempNode->nextNode[0]!= NULL) {
		if (key < tempNode->nextNode[curLevel]->key) {
			curLevel--;
		}
		else if(key = tempNode->nextNode[curLevel]->key) {
			return path; //vị trí bằng
		}
		else { // lớn hơn
			path.push_back(tempNode);
			tempNode = tempNode->nextNode[curLevel];
		}
	}
}

int insertSNode(sList &L, int key) {
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
		sNode** preNodeInsert=new sNode* [L.MAX_LEVEL-1]; // danh sách các node mà đứng trước node cần thêm theo từng level, dùng để thêm node vào sau đó.
		int curLevel = L.MAX_LEVEL - 1; // dùng để duyệt từ trên xuống
		sNode* tempNode = L.headNode;
		while (tempNode->nextNode[0] != NULL) { // dùng node tạm chạy từ đầu đến cuối, dừng khi chạy hết lv1
			if (key < tempNode->nextNode[curLevel]->key) { // nếu khóa thêm nhỏ hơn giá trị node sau node tạm.
				preNodeInsert[curLevel] = tempNode; // thêm node đó vào danh sách node trước.
				if (curLevel == 0) { // nếu đang ở lv1 thì thêm vào
					for (; curLevel < lv; curLevel++) {
						n->nextNode[curLevel] = preNodeInsert[curLevel]->nextNode[curLevel]; // từng lv tương ứng của node cần thêm trỏ vào node tiếp theo.
						preNodeInsert[curLevel]->nextNode[curLevel] = n;// các node trước trỏ vào node cần thêm
					}
					delete preNodeInsert;// xóa bộ nhớ
					return 0;
				}
				curLevel--;
			}
			else if (key = tempNode->nextNode[curLevel]->key) {// vị trí bằng
				return -1; //return chứng tỏ k thêm được
			}
			else { // lớn hơn
				tempNode = tempNode->nextNode[curLevel]; // chạy đến node tiếp theo 
			}
		}
	}
}
int main() {
	/*sList L;
	L.headNode = new sNode;
	cout << sizeof(sList);
	return 0;*/
	vector <int> sodem;
	//sodem[3] = 0;
	//sodem[2] = 1;
	//sodem[1] = 10;
	sodem.push_back(8);
	sodem[0] = 10;
	cout <<  sodem[0] << endl;
	return 0;
}