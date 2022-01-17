//Simply put, when you want to use algorithms that requires random access, forget linked list.
//When you want to use algorithms that requires heavy insertionand removal, forget arrays.

#include <cmath>

#include<iostream>
template <typename T>
struct Node
{
	T data;
	Node* next = NULL;
	Node* prev = NULL;

	Node(T _data) : data(_data) {};
};

template <typename T>
bool cmp(T const& t1, T const& t2)
{
	return t1 > t2;
}

template <typename T>
class DLList
{
private:
	bool isSort = false;
	int len;
public:
	Node<T>* head;
	Node<T>* tail;
	DLList<T> (T data)
	{

		len = 1;
		head = new Node<T>(data);
		head->next = NULL;
		head->prev = NULL;

		tail = head;
	}
	//Insert
	int push_front(T data)
	{
		Node<T>* newNode = new Node<T>(data);
		newNode->next = head;

		head->prev = newNode;

		head = newNode;
		++len;
		return 1;
	}

	int push_back(T data)
	{
		Node<T>* newNode = new Node<T>(data);
		newNode->prev = tail;

		tail->next = newNode;

		tail = newNode;
		++len;
		return 1;
	}

	int insert(T data, Node<T>*& frNode)
	{
		Node<T>* newNode = new Node<T>(data);

		newNode->next = frNode;
		
		newNode->prev = frNode->prev;
		
		frNode->prev->next = newNode;
		frNode->prev = newNode;

		++len;
		return 1;
	}

	int insert_at(T data, int pos)
	{
		if (pos > len + 1|| pos <= 0)
		{
			std::cout << "Error Insert" << std::endl;
			return 0;
		}
		if (pos == 1) { push_front(data); return 1; }
		if (pos == len + 1) { push_back(data); return 1; }
		Node<T>* temp = head;
		for (int i = 1; i < pos; i++)
			temp = temp->next;

		insert(data, temp);
		return 1;
	}

	int insert_order(T data, bool (*cmp)(T,T))
	{
		Node<T>* temp = head;

		while (temp != NULL)
		{
			
			if (cmp(temp->data, data))
			{
				if (temp == head){ push_front(data); return 1; }	
				insert(data, temp);
				return 1;
			}
			if (temp == tail)
			{
				push_back(data);
				return 1;
			}
			temp = temp->next;
		}

		return 0;
	}
	

	//Delete
	int pop_front() {
		if(len==0) {
			std::cout << "List is empty" << std::endl;
			return 0;
		}
		if(head == tail ) {
			delete head;
			head = tail = NULL;
			len--;
			return 1;
		}
		Node<T>* temp = head;
		head = head->next;
		head -> prev = NULL;
		delete temp;
		
		len--;
		return 1;
	}
	
	int pop_back() {
		if(len==0) {
			std::cout << "List is empty" << std::endl;
			return 0;
		}
		if(head == tail ) {
			delete head;
			head = tail = NULL;
			len--;
			return 1;
		}
		Node<T>* temp = tail;
		tail = tail->prev;
		tail -> next = NULL;
		delete temp;
		
		len--;
		
		return 1;
	}
	
	int remove_node(Node<T>* node) {
		if(node == NULL) { 
			std::cout << "Node does not exist" << std::endl;
			return 0; 
		}
		if(node == head) { pop_front(); return 1; };
		if(node == tail) { pop_back(); return 1; };

		
		node->prev->next = node ->next;
		node->next->prev = node ->prev;
		
		delete node;
				
		len--;
		return 1;
		
	}
	
	int remove_at(int pos) {
		if(len==0) {
			std::cout << "List is empty" << std::endl;
			return 0;
		}
		if(pos<0 || pos >=len) {
			std::cout << "Out of range" << std::endl;
			return 0;
		}
		if(pos==0) { pop_front(); return 1; }
		if(pos==len-1) { pop_back(); return 1; }
		Node<T>* temp;
		if(pos<=len/2) {
			temp = head;
			for(int i=1; i<=pos; ++i) {
				temp=temp->next;
			}
		} else {
			temp = tail;
			for(int i=len-1; i>pos; --i) {
				temp=temp->prev;
			}
		}	
		len--;
		if (remove_node(temp)==1) {return 1;}
		return 0;

	}
	
	int size() { return len; }
	
	Node<T> *find_node(T element)
	{
		if (len == 0)
		{
			std::cout << "List is empty" << std::endl;
			return NULL;
		}
		Node<T> *curr =head;
		while (curr != NULL)
		{
			if (curr->data == element)
			{
				return curr;
			}
			curr = curr->next;
		}
		std::cout << "Node does not exist" << std::endl;
		return NULL;
	}
	
	DLList<T> find_all(T element)
	{
		DLList<T> res(0);
		res.head = res.tail = NULL;
		res.len = 0;
		if (len == 0)
		{
			std::cout << "List is empty" << std::endl;
			return res;
		}
	
		Node<T> *curr = head;
		while (curr != NULL)
		{
			if (curr->data == element)
			{
				if (res.head == NULL)
				{
					Node<T> *temp = new Node<T>(curr->data);
					res.head = res.tail = temp;
					res.len = 1;
				}
				else
				{
					res.push_back(curr->data);
				}
			}
			curr = curr->next;
		}
		if (res.len == 0)
		{
			std::cout << "Nodes does not exist" << std::endl;
		}
		return res;
	}

};

template <typename T>
inline void PrintDLL(DLList<T>& list)
{
	Node<T>* temp = list.head;
	while (temp != NULL)
	{
		std::cout << temp->data << " ";
		temp = temp->next;
	}
}

//template <typename T>
//inline Node<T>* midNode(Node<T>* head)
//{
//	Node<T>* tortoise = head;
//	Node<T>* hare = head->next;
//
//	while ((tortoise->next != NULL) && (hare != NULL && hare->next != NULL))
//	{
//		tortoise = tortoise->next;
//		hare = hare->next->next;
//	}
//
//	return tortoise;
//}

//singly linked list
/*template <typename T>
inline Node<T>* Merge(Node<T>** head1, Node<T>** head2, bool (*cmp)(T,T))
{
	Node<T>* merged = new Node<T>(head1->data);
	Node<T>* dummy = merged;
	while (head1 != NULL || head2 != NULL)
	{
		if (cmp(head1->data, head2->data))
		{
			dummy->next = head1;
			head1 = head1->next;
			dummy = dummy->next;
		}
		else
		{
			dummy->next = head2;
			head2 = head2->next;
			dummy = dummy->next;
		}
		dummy = dummy->next;
	}
	while (head1 != NULL)
	{
		merged->next = head1;
		head1 = head1->next;
		merged = merged->next;
	}
	while (head2 != NULL)
	{
		merged->next = head2;
		head2 = head2->next;
		merged = merged->next;
	}
	return merged->next;
}
template <typename T>
inline Node<T>* MergeSort(Node<T>* head,const int len, bool (*cmp)(T,T))
{
	if (head->next == NULL)
		return head;
	Node<T>* middle = new Node<T>(head->data);
	Node<T>* head2 = new Node<T>(head->data);
	middle = midNode(head);
	head2 = middle->next;
	middle->next = NULL;
	//head2->prev = NULL;
	Node<T>* sorthead = Merge(&MergeSort(head, len, cmp), &MergeSort(head2, len, cmp), cmp);
	return sorthead;
}
*/

//doubly linked list
template <typename T>
inline Node<T>* split(Node<T>* head)
{
	Node<T>* fast = head, * slow = head;
	while (fast->next && fast->next->next)
	{
		fast = fast->next->next;
		slow = slow->next;
	}
	Node<T>* temp = slow->next;
	slow->next = NULL;
	return temp;
}

template <typename T>
inline Node<T>* merge(Node<T>* first, Node<T>* second, bool (*cmp)(T, T))
{
	// If first linked list is empty 
	if (!first)
		return second;

	// If second linked list is empty 
	if (!second)
		return first;

	// Pick the smaller value 
	if (first->data < second->data)
	{
		first->next = merge(first->next, second, cmp);
		first->next->prev = first;
		first->prev = NULL;
		return first;
	}
	else
	{
		second->next = merge(first, second->next, cmp);
		second->next->prev = second;
		second->prev = NULL;
		return second;
	}
}

template <typename T>
inline Node<T>* mergeSort(Node<T>* head, bool (*cmp)(T, T))
{
	if (!head || !head->next)
		return head;
	Node<T>* second = split(head);

	// Recur for left and right halves 
	head = mergeSort(head, cmp);
	second = mergeSort(second, cmp);

	// Merge the two sorted halves 
	return merge(head, second, cmp);
}
