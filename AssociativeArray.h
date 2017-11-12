#ifndef Associative_h
#define Associative_h
#include "Queue.h"

template <typename V, typename K>
class AssociativeArray
{
    struct Node{
        V value    = V();
        K key      = K();
        bool inUse = false;
        int size   = 1;
        Node(K key){
            value = V();
            inUse = true;
            this->key = key;
            size = 1;
        }
        Node(){};
    };
    int siz = 0;
    int cap = 2;
    V dummy = V();
    
    Node* NodeArray;
    
    void capacity(int capa){
        Node* temp = new Node[capa];
        for (int i = 0; i < cap; i++){
            temp[i] = NodeArray[i];
        }
        for (int i = cap; i < capa; i++){
            temp[i].inUse = false;
            temp[i].value = V();
            temp[i].key = K();
        }
        cap = capa;
//        delete[] NodeArray;
        NodeArray = temp;
    };
public:
    AssociativeArray(){
        NodeArray   = new Node[cap];
        for (int i  = 0; i < cap; i++) {
            NodeArray[i] = Node();
        }
    };
    AssociativeArray(int cap){
        this->cap = cap;
        NodeArray = new Node[cap];
        for (int i = 0; i < cap; i++) {
            NodeArray[i]   = Node();
        }
    };
    AssociativeArray<V,K>& operator=(const AssociativeArray<V,K>& original){
        if (this != &original)
        {
            delete[] NodeArray;
            cap = original.cap;
            siz = original.siz;
            NodeArray = new Node[cap];
            for (int i = 0; i < cap; i++)
                NodeArray[i] = original.NodeArray[i];
            dummy = original.dummy;
        }
        return *this;
    };
    AssociativeArray(const AssociativeArray<V,K>& original){
        cap       = original.cap;
        siz       = original.siz;
        NodeArray = new Node[cap];
        for (int i  = 0; i < cap; i++){
            NodeArray[i] = original.NodeArray[i];
        }
    };
    ~AssociativeArray() { delete[] NodeArray; } //destructor
    int capacity() const { return cap; }

    V& operator[](const K& key){
        //search for match, + hole
        for (int i = 0; i < cap; i++){
            if (NodeArray[i].inUse&&NodeArray[i].key == key){
                return NodeArray[i].value;
            }
        }
        for (int i = 0; i < cap; i++){
            if (!NodeArray[i].inUse){
                //create the node
                Node data(key);
                NodeArray[i] = data;
                siz++;
                return NodeArray[i].value;
            }
        }
        //if no match and no hole
        capacity(cap * 2);
        Node data(key);
        siz++;
        return NodeArray[cap].value;
    };
    
    bool containsKey(const K& key)const {
        for (int i = 0; i < cap; i++){
            if (NodeArray[i].key == key && NodeArray[i].inUse){return true;}
        }
        return false;
    };
    void deleteKey(const K& key){
        for (int i = 0; i < cap; i++){
            if (NodeArray[i].key == key){
                NodeArray[i].inUse = false;
                siz--;
            }
        }
    };
    int size()const {return siz;};
    Queue<K> keys(){
        Queue<K> AllStrings;
        for (int i = 0; i < cap; i++){
            if (NodeArray[i].inUse){
                AllStrings.push(NodeArray[i].key);
            };
        }
        return AllStrings;
    };
};

#endif
