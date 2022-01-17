#include "LinkedList.cpp"

using namespace std;

bool cmp(int data1, int data2)
{
	return data1 > data2;
}


void cr(DLList<int> &m, int pos) {
	if(!m.remove_at(pos)) { return; };
	cout << "After remove at " << pos << " :";
	PrintDLL(m);
	cout << endl;
}

void cr(DLList<int> &m, Node<int> *node) {
	if(!m.remove_node(node)) { return; }
	cout << "After remove Node: ";
	PrintDLL(m);
	cout << endl;
}

void cf(DLList<int> &m, int e) {
	Node<int>* curr = m.find_node(e);
	if(curr == NULL) return;
	cout << "Node " << curr->data << " has been found " << endl;
}

void cfa(DLList<int> &m, int e) {
	DLList<int> curr = m.find_all(e);
	if(curr.size()==0) return;
	cout << curr.size() << " nodes " << e << " has been found:"; 
	PrintDLL(curr);
	cout << endl;
}

void test_delete(DLList<int> &m) {
	cout << "Before remove:";
	PrintDLL(m);
	cout << endl;
	Node<int> *temp = m.head; 
	cr(m, temp->next->next);
	temp = m.head;
	cr(m,6);
}

void test_find(DLList<int> &m) {
	cf(m,2);
	cf(m,0);
	cfa(m,4);
	cfa(m,8);
	cfa(m,9);
	
}
int main()
{
	// I'm here
	// Something change
	DLList<int> m(4);
	m.push_front(2);
	m.push_front(8);
	m.push_back(3);
	m.push_back(1);
	m.insert_order(4, cmp);
	m.insert_at(6,7);
	//Node<int>* temp = m.head;
//	MergeSort(temp, 5,cmp);
	//test_delete(m);
	PrintDLL(m);
	m.head = mergeSort(m.head, cmp);
	cout << endl;
	PrintDLL(m);
	cout << endl << "Size:" << m.size() << endl;
	test_find(m);
}

