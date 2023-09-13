
struct Node
{
	int data;
	Node* next;
	Node(int dat) {
		this->data = dat;
		this->next = nullptr;
	}
	Node() {
		this->data = 0;
		this->next = nullptr;
	}
};

struct Queue {


	int size;
	Node* head = new Node;
	Node* tail = new Node;



	Queue();
	Queue(int* arr, size_t size);

	int remove();
	void add(int a);
	int show();
	void clear();

	~Queue();

};

