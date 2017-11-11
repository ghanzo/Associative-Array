#ifndef Associative_h
#define Associative_h
#include "Queue.h"

template <typename V, typename K>
class AssociativeArray
{
    struct Node{
        V VValues  = V();   /* rename => value */
        K KValues  = K();   /* rename => key   */
        bool inUse = false;     /* technically don't need this (is super inefficient), but whatever. You'd have to use a different algorithm so nevermind */
    };
    int siz = 0;        /* rename => size. avoid abbreviations like this (bad) */
    V* values;          /* unused - delete this */
    int cap = 2;
    V dummy = V();
    
    Node* NodeArray;    /* rename => nodeArray (or just nodes). capital identifiers are reserved for classes / types */
    
    void capacity(int capa){            /* ok */
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
    AssociativeArray(){                 /* ok */
        NodeArray   = new Node[cap];
        for (int i  = 0; i < cap; i++) {
            NodeArray[i] = Node();
        }
    };
    AssociativeArray(int cap){          /* ok */
        this->cap = cap;
        NodeArray = new Node[cap];
        for (int i = 0; i < cap; i++) {
            NodeArray[i]   = Node();
        }
    };

    AssociativeArray<V,K>& operator=(const AssociativeArray<V,K>& original){
        if (this != &original)          /* ok */
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
        cap       = original.cap;       /* ok */
        siz       = original.siz;
        NodeArray = new Node[cap];
        for (int i  = 0; i < cap; i++){
            NodeArray[i] = original.NodeArray[i];
        }
    };
    ~AssociativeArray() { delete[] NodeArray; } //destructor
    int capacity() const { return cap; }
    V& operator[](const K& index) const {   /* key is NOT an integer (necessarily). This is wrong. */
        if (index < 0) return dummy;        /* You have a key and do NOT know the index. You need to find the first index / element with a matching key. */ 
        if (index >= cap) return dummy;
        return NodeArray[index].VValues;
    };
    V& operator[](const K& index){          /* ditto. Also, rename index => key. The key is NOT an integer index (eg. i). */
        //search for match, + hole
        for (int i = 0; i < cap; i++){
            if (NodeArray[i].inUse&&NodeArray[i].KValues == index){
                return NodeArray[i].VValues;
            }
        }
        for (int i = 0; i < cap; i++){
            if (!NodeArray[i].inUse){
                //create the node

                /*
                    Should use constructor (if there is none, make one for Node):
                    nodes[i] = Node(key, V(), true);
                    ++siz;
                */
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
        Node data;                      /* ditto */
        data.KValues = index;
        data.inUse   = true;
        data.VValues = V();
        siz++;
        return NodeArray[cap].VValues;
    };
    
    V& operator[](int index){                   /* This is never called and is not part of assoc array contract. */
        if (index < 0) return dummy;            /* guessing this is left over from dynamic array - delete this */
        if (index >= cap) capacity(index * 2);
        return NodeArray[index].VValues;
    };
    bool containsKey(const K& key)const {       /* ok */
        for (int i = 0; i < cap; i++){
            if (NodeArray[i].KValues == key && NodeArray[i].inUse){return true;}
        }
        return false;
    };
    void deleteKey(const K& key){
        for (int i = 0; i < cap; i++){
            if (NodeArray[i].KValues == key){
                NodeArray[i].inUse = false; 
                siz--;
                /*
                    Not happy with this algorithm (it's crap), but it should technically, probably work (ok).
                */
            }
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
