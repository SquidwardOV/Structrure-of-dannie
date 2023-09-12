struct Node {
	int date;
	Node* ptr;

};

struct Stack {
private:
	int size = 0;
	Node *head = new Node;
public:
	void add(int date);
	void remove();
	int show();
	void clear();
	~Stack();
	Stack(int* arr, int score);
	Stack();


};

