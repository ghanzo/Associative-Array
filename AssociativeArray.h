#ifndef Associative_h
#define Associative_h
#include "Queue.h"

template <typename V, typename K>
class AssociativeArray
{
    struct Node{
        V VValues  = V();
        K KValues  = K();
        bool inUse = false;
    };
    int siz = 0;
    V* values;
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
            temp[i].VValues = V();
            temp[i].KValues = K();
        }
        cap = capa;
        delete[] NodeArray;
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
    V& operator[](const K& index) const {
        if (index < 0) return dummy;
        if (index >= cap) return dummy;
        return NodeArray[index].VValues;
    };
    V& operator[](const K& index){
        //search for match, + hole
        for (int i = 0; i < cap; i++){
            if (NodeArray[i].inUse&&NodeArray[i].KValues == index){
                return NodeArray[i].VValues;
            }
        }
        for (int i = 0; i < cap; i++){
            if (!NodeArray[i].inUse){
                //create the node
                Node data;
                data.KValues = index;
                data.inUse   = true;
                data.VValues = V();
                NodeArray[i] = data;
                siz++;
                return NodeArray[i].VValues;
            }
        }
        //if no match and no hole
        capacity(cap * 2);
        Node data;
        data.KValues = index;
        data.inUse   = true;
        data.VValues = V();
        siz++;
        return NodeArray[cap].VValues;
    };
    
    V& operator[](int index){
        if (index < 0) return dummy;
        if (index >= cap) capacity(index * 2);
        return NodeArray[index].VValues;
    };
    bool containsKey(const K& key)const {
        for (int i = 0; i < cap; i++){
            if (NodeArray[i].KValues == key && NodeArray[i].inUse){return true;}
        }
        return false;
    };
    void deleteKey(const K& key){
        for (int i = 0; i < cap; i++){
            if (NodeArray[i].KValues == key){NodeArray[i].inUse = false; siz--;}
        }
    };
    int size()const {return siz;};
    Queue<K> keys(){
        Queue<K> AllStrings;
        for (int i = 0; i < cap; i++){
            if (NodeArray[i].inUse){AllStrings.push(NodeArray[i].KValues);};
        }
        return AllStrings;
    };
};

#endif
