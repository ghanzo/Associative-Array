#ifndef Queue_h
#define Queue_h

template <typename V>
class Queue
{
    struct node
    {
        V     value = V();
        node* next  = nullptr;
    };
    node *head = nullptr;
    node *tail = nullptr;
    node *temp = nullptr;
    int siz = 0;
public:
    Queue(){};
    Queue(const Queue<V>& other){*this = other;};
    Queue<V>& operator=(const Queue<V>& original){
        if (this != &original)
        {
            //Deallocate existing list
            while (head)
            {
                node* p = head->next;
                delete head;
                head = p;
            }
            //Build new Queue
            node* tail = 0; //temporary tail
            for (node* p = original.head; p; p= p->next)
            {
                node* temp  = new node;
                temp->value = p->value;
                temp->next  = 0;
                //confused here
                if (tail) tail->next = temp;
                else head   = temp;
                tail        = temp;
            }
            siz = original.siz;
        }
        return *this;
    };
    void push(const V& e)
    {
        temp = new node;
        temp-> value = e;
        if (head == nullptr){
            head =  temp;
            tail =  temp;
        }
        else {
            tail-> next = temp;}
        tail = temp;
        siz++;
    };
    void pop(){
        if   (tail!= head){
            temp = head->next;
            delete head;
            head = temp;}
        else {tail = nullptr;
            head = nullptr;}
        siz--;
    };
    V& front(){return head->value;};
    V& back(){return tail->value;};
    int size() const{return siz;};
    bool empty() const{if(siz == 0)return true; else return false;};
    void clear(){
        while (head!= nullptr)
        {
            node* p = head->next;
            delete head;
            head = p;
        }
        if (head == nullptr) tail= nullptr;
        siz = 0;
    };
    ~Queue(){clear();};
};


#endif /* Queue_h */
