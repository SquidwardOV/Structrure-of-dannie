struct Node {
    int date;
    Node* pref;
    Node* next;
};

struct Queue {
private:
    Node* head = new Node;
    Node* end = new Node;
    int size = 0;
public:
    void push_back(int date);
    void pop_front();
    int show();
    void clear();
    ~Queue();
};
