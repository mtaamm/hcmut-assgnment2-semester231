#include "main.h"

int MAXSIZE;

struct letter{
    char c;
    int f;
    letter(char c, int f): c(c), f(f){};
};

struct huffCode {
    char c;
    string code;
    huffCode(char c, string code) : c(c), code(code){};
};

class huffmanTree {
public:
	friend class restaurant;
	class huffNode{
    public:
        virtual ~huffNode(){};
		virtual int weight() = 0;
		virtual bool isLeaf() = 0;
        virtual int balance() = 0;
	};
    class leafHuffNode:public huffNode {
    public:
        ~leafHuffNode(){};
        char c;
        int wgt;
        leafHuffNode(letter &a) : c(a.c), wgt(a.f) {};
        int weight() {return wgt;}
        bool isLeaf() {return 1;}
        int balance() {return 0;}
    };
    class interHuffNode:public huffNode {
    public:
        ~interHuffNode(){};
        huffNode* lc;
        huffNode* rc;
        int wgt;
        interHuffNode(huffNode* lc, huffNode* rc) : lc(lc), rc(rc), wgt(lc->weight()+rc->weight()) {};
        int weight() {return wgt;}
        bool isLeaf() {return 0;}
        int getHeightRec(huffNode* node);
        int balance() {return getHeightRec(lc)-getHeightRec(rc);}
    };
private:
    huffNode* root=NULL;
public:
    huffmanTree() {};
    ~huffmanTree() {clear();}
    huffmanTree(letter &a) {root=new leafHuffNode(a);}
    huffNode* getRoot() {return root;}
    huffmanTree(huffmanTree* l, huffmanTree* r) {
        root=new interHuffNode(l->getRoot(), r->getRoot());
    }
    int weight() {return root->weight();}
    huffmanTree(vector<letter> &v);
    void inoderRec(huffNode* node);
    void inoder() {inoderRec(root);}
    void encodeRec(huffNode* node, vector<huffCode> &v, string s);
    vector <huffCode> encode();
    void clearRec(huffNode* node);
    void clear();
    void reBalanceRec(huffNode* &node, int &numRotate);
    void reBalance() {int numRotate=0; reBalanceRec(root, numRotate);}
    interHuffNode* rotateLeft(huffNode* node) {
        interHuffNode* inter=(interHuffNode*) node;
        interHuffNode* newRoot=(interHuffNode*) inter->rc;
        if (newRoot->lc==NULL) {
            newRoot->lc=inter;
            inter->rc=NULL;
        } else {
            huffNode* tmp=newRoot->lc;
            newRoot->lc=inter;
            inter->rc=tmp;
        }
        return newRoot;
    }
    interHuffNode* rotateRight(huffNode* node) {
        interHuffNode* inter=(interHuffNode*) node;
        interHuffNode* newRoot=(interHuffNode*) inter->lc;
        if (newRoot->rc==NULL) {
            newRoot->rc=inter;
            inter->lc=NULL;
        } else {
            huffNode* tmp=newRoot->rc;
            newRoot->rc=inter;
            inter->lc=tmp;
        }
        return newRoot;
    }
};

class BST {
public:
    class BSTNode {
    public:
        int data;
        BSTNode* left;
        BSTNode* right;
        BSTNode(int data): data(data), left(NULL), right(NULL){};
        BSTNode(int data, BSTNode* left, BSTNode* right): data(data), left(), right(right){};
    };
private:
    BSTNode* root=NULL;
public:
    BST (int data) {root=new BSTNode(data);}
    ~BST() {clear();}
    void addRec(BSTNode* &node, int val);
    void add(int val);
    void removeRec(BSTNode* &node, int val);
    void remove(int val);
    void clearRec(BSTNode* node);
    void clear();
    void inoderRec(BSTNode* node);
    void inoder();
    void postOderRec(BSTNode* node, vector<int> &v);
    vector<int> postOder();
    long int calcPermutation();
};

template <class T>
class MinHeap {
private:
    T* list=NULL;
    int count;
public:
    MinHeap() {list=new T[MAXSIZE]; count=0;}
    MinHeap(MinHeap& m);
    ~MinHeap() {delete[] list;}
    void reheapUp(int index);
    void reheapDown(int  index);
    void insert(T val);
    int findHeap(T &val);
    int size() {return count;}
    T operator [](int index) {return list[index];}
    T pop();
    void remove(int index);
    void preOder(int index);
};

class Restaurant {
public:
    class GHouse {
    public:
        class GZone {
        public:
            int ID;
            BST* bst=NULL;
            vector<int> v;
            GZone(int id, int result) {ID=id; bst=new BST(result); v.push_back(result);}
            ~GZone() {delete bst;}
            void add(int result);
            void kokusenZone();
            void print() {bst->inoder();}
        };
    public:
        GZone** listZone=NULL;
        GHouse() {
            listZone=new GZone*[MAXSIZE];
            for (int i=0; i<MAXSIZE; i++) listZone[i]=NULL;
        }
        ~GHouse() {
            for (int i=0; i<MAXSIZE; i++) delete listZone[i];
            delete[] listZone;
        }
        void add(int result);
        void kokusen();
        void limitless(int num);
    };
    class SHouse {
    public:
        class SZone {
        public:
            vector<int> v;
            int ID, updateVal, numPrint;
            SZone(){};
            SZone(int id, int result, int update) {ID=id; numPrint=0; v.push_back(result); updateVal=update;}
            void add(int result, int maxUpdateVal) {v.push_back(result); updateVal=maxUpdateVal;}
            void remove(int num, int maxUpdateVal);
            bool operator <(SZone &a);
            bool operator ==(SZone &a) {return ID==a.ID;}
            string operator *() {return print();}
            string print();
        };
        MinHeap<SZone*> minHeap;
        SZone** listZone=NULL;
        int maxUpdateVal;
        SHouse() {
            listZone=new SZone*[MAXSIZE]; maxUpdateVal=INT16_MIN;
            for (int i=0; i<MAXSIZE; i++) listZone[i]=NULL;
        }
        ~SHouse() {
            for (int i=0; i<MAXSIZE; i++) delete listZone[i];
            delete[] listZone;
        }
        void add(int result);
        vector<int> listIdToDelete(int num);
        void keiteiken(int num);
        void cleave(int num);
    };
private:
	huffmanTree* currentHuffTree=NULL;
    GHouse* gHouse=NULL;
    SHouse* sHouse=NULL;
public:
	Restaurant(){};
	~Restaurant() {delete currentHuffTree; delete gHouse; delete sHouse;}
	int calcResult(vector<letter> &v, string caeName);
	void lapse(string name);
	void kokusen();
	void keiteiken(int num);
	void hand();
	void limitless(int num);
	void cleave(int num);
};

bool comp(letter &a, letter &b) {
    if (a.f==b.f) {
        if ((a.c>='A'&&a.c<='Z'&&b.c>='A'&&b.c<='Z')||(a.c>='a'&&a.c<='z'&&b.c>='a'&&b.c<='z'))
        return a.c<b.c;
        else return a.c>b.c;
    } return a.f<b.f;
}

int findChar(vector<letter> &v, int st, int en, char a) {
    for (int i=st; i<en; i++) {
        if (v[i].c==a) return i;
    }
    return -1;
}
char caesar(char a, int k) {
    if (a>=65&&a<=90) return (a - 65 + k) % 26 + 65;
    else return (a - 97 + k) % 26 + 97;
}
vector<letter> prepareName1(string name) {
    vector<letter> v;
    for (unsigned int i=0; i<name.size(); i++) {
        int id=findChar(v, 0, v.size(), name[i]);
        if (id==-1) v.push_back(letter(name[i], 1));
        else v[id].f++;
    }
	return v;
}
void lastPrepare(vector<letter> &v) {
    for (unsigned int i=0; i<v.size(); i++) {
        v[i].c=caesar(v[i].c, v[i].f);
    }
    for (unsigned int i=0; i<v.size(); i++) {
        int check=findChar(v, i+1, v.size(), v[i].c);
        while (check!=-1) {
            v[i].f+=v[check].f;
            v.erase(v.begin()+check);
            check=findChar(v, i+1, v.size(), v[i].c);
        }
    }
    sort(v.begin(), v.end(), comp);
}

string caesarName(string name, vector<letter> &v) {
	int fArr[58];
	int n=v.size();
	for (int i=0; i<n; i++) fArr[v[i].c-65]=v[i].f;
	for (unsigned int i=0; i<name.size(); i++) name[i]=caesar(name[i], fArr[name[i]-65]);
	return name;
}

vector<long int> calcFact(int n) {
    vector<long int> v; v.push_back(1);
    for (int i=1; i<n; i++) v.push_back(v[i-1]*i);
    return v;
}

long int nCr(vector<long int> &v, int n, int r) {
    if (r>n) return 0;
    return v[n]/(v[n-r]*v[r]);
}

long int countWay(vector<int> &v, vector<long int> &fact) {
    int N=v.size();
    if (N<=2) return 1;
    vector<int> leftSubTree;
    vector<int> rightSubTree;
    int root=v[N-1];
    for (int i=N-2; i>=0; i--) {
        if (v[i]<root) leftSubTree.push_back(v[i]);
        else rightSubTree.push_back(v[i]);
    }
    reverse(leftSubTree.begin(), leftSubTree.end());
    reverse(rightSubTree.begin(), rightSubTree.end());
    int NLeft=leftSubTree.size();
    long int countLeft=countWay(leftSubTree, fact);
    long int countRight=countWay(rightSubTree, fact);
    return nCr(fact, N-1, NLeft)*countLeft*countRight;
}

void BST::addRec(BSTNode* &node, int val) {
    if (node==NULL) {node=new BSTNode(val); return;}
    if (val<node->data) addRec(node->left, val);
    else addRec(node->right, val);
}
void BST::add(int val) {addRec(root, val);}

void BST::removeRec(BSTNode* &node, int val) {
    if (node==NULL) return;
    if (val<node->data) {removeRec(node->left, val); return;}
    else if (val>node->data) {removeRec(node->right, val); return;}
    if (node->left==NULL||node->right==NULL) {
        BSTNode* tmp=(node->left?node->left:node->right);
        delete node; node=tmp; return;
    } else {
        BSTNode* succParent=node;
        BSTNode* tmp=node->right;
        while (tmp->left!=NULL) {
            succParent=tmp; tmp=tmp->left;
        }
        if (succParent!=node) succParent->left=tmp->right;
        else succParent->right=tmp->right;
        node->data=tmp->data;
        delete tmp; return;
    }
}

void BST::remove(int val) {removeRec(root, val);}

void BST::clearRec(BSTNode* node) {
    if (node==NULL) return;
    if (node->left!=NULL) clearRec(node->left);
    if (node->right!=NULL) clearRec(node->right);
    delete node;
}

void BST::clear() {clearRec(root); root=NULL;}

void BST::inoderRec(BSTNode *node) {
    if (node==NULL) return;
    inoderRec(node->left);
    cout<<node->data<<'\n';
    inoderRec(node->right);
}

void BST::inoder() {inoderRec(root);}

void BST::postOderRec(BSTNode *node, vector<int> &v) {
    if (node==NULL) return;
    v.push_back(node->data);
    postOderRec(node->left, v);
    postOderRec(node->right, v);
}

vector<int> BST::postOder() {vector<int> v; postOderRec(root, v); return v;}

long int BST::calcPermutation() {
    vector<int> post=postOder();
    int N=post.size();
    vector<long int> fact=calcFact(N);
    return countWay(post, fact);
}

template <class T>
MinHeap<T>::MinHeap(MinHeap &m) {
    list=new T[MAXSIZE]; count=m.size();
    for (int i=0; i<count; i++) list[i]=m[i];
}

template <class T>
void MinHeap<T>::reheapUp(int index)
{
    if (index==0) return;
    if (*list[index]<*list[(index-1)/2]) {
        swap(list[index], list[(index-1)/2]);
        reheapUp((index-1)/2);
    }
}

template <class T>
void MinHeap<T>::reheapDown(int index) {
    if (2*index+1<count) {
        if (2*index+2<count) {
            if (*list[2*index+1]<*list[2*index+2]) {
                if (*list[2*index+1]<*list[index]) {
                    swap(list[2*index+1], list[index]);
                    index=2*index+1;
                } else return;
            } else {
                if (*list[2*index+2]<*list[index]) {
                    swap(list[2*index+2], list[index]);
                    index=2*index+2;
                } else return;
            }
        } else {
            if (*list[2*index+1]<*list[index]) {
                swap(list[2*index+1], list[index]);
                index=2*index+1;
            } else return;
        }
    } else return;
    reheapDown(index);
}

template <class T>
void MinHeap<T>::insert(T val) {
    if (count==0) {list[count++]=val; return;}
    list[count++]=val; reheapUp(count-1);
}

template <class T>
int MinHeap<T>::findHeap(T &val) {
    for (int i=0; i<count; i++) {
        if (list[i]==val) return i;
    } return -1;
}

template <class T>
T MinHeap<T>::pop() {
    if (count==1) {count--; return list[0];}
    T data=list[0];
    swap(list[0], list[--count]);
    reheapDown(0);
    return data;
}

template <class T>
void MinHeap<T>::remove(int index) {
    if (count==1) {count--; return;}
    if (index==count-1) {count--; return;}
    swap (list[index], list[--count]);
    reheapDown(index);
}

template <class T>
void MinHeap<T>::preOder(int index) {
    if (index>=count) return;
    cout<<*(*list[index]);
    preOder(2*index+1);
    preOder(2*index+2);
}

void insertHuffNodeToVector(vector<huffmanTree*> &v, huffmanTree* h) {
    for (unsigned int i=0; i<v.size(); i++) {
        if (h->weight()<v[i]->weight()) {
            v.insert(v.begin()+i, h); return;
        }
    }
    v.push_back(h);
}

int huffmanTree::interHuffNode::getHeightRec(huffNode* node) {
    if (node==NULL) return 0;
    if (node->isLeaf()) return 1;
    interHuffNode* inter=(interHuffNode*)node;
    int hLeft=getHeightRec(inter->lc);
    int hRight=getHeightRec(inter->rc);
    return (hLeft>hRight?(1+hLeft):(1+hRight));
}

huffmanTree::huffmanTree(vector<letter> &v) {
    vector<huffmanTree*> q;
    for (unsigned int i=0; i<v.size(); i++) {
        huffmanTree* h=new huffmanTree(v[i]);
        q.push_back(h);
    }
    while (q.size()>1) {
        huffmanTree* left=q[0]; q.erase(q.begin());
        huffmanTree* right=q[0]; q.erase(q.begin());
        huffmanTree* h=new huffmanTree(left, right);
        h->reBalance();
        insertHuffNodeToVector(q, h);
    }
    root=q[0]->getRoot();
}

void huffmanTree::inoderRec(huffNode* node) {
    if (node->isLeaf()) {
        leafHuffNode* leaf= (leafHuffNode*)node;
        cout<<leaf->c<<endl;
    } else {
        interHuffNode* inter= (interHuffNode*) node;
        inoderRec(inter->lc);
        cout<<inter->wgt<<endl;
        inoderRec(inter->rc);
    }
}

void huffmanTree::encodeRec(huffNode *node, vector<huffCode> &v, string s) {
    if (node->isLeaf()) {
        leafHuffNode* leaf=(leafHuffNode*)node;
        v.push_back(huffCode(leaf->c, s));
    } else {
        interHuffNode* inter=(interHuffNode*)node;
        encodeRec(inter->lc, v, s+'0');
        encodeRec(inter->rc, v, s+'1');
    }
}

vector<huffCode> huffmanTree::encode() {
    vector<huffCode> v;
    encodeRec(root, v, "");
    return v;
}

void huffmanTree::clearRec(huffNode *node) {
    if (node==NULL) return;
    if (node->isLeaf()) delete (leafHuffNode*)node;
    else {
        interHuffNode* inter=(interHuffNode*)node;
        clearRec(inter->lc);
        clearRec(inter->rc);
        delete inter;
    }
}

void huffmanTree::clear() {clearRec(root); root=NULL;}

void huffmanTree::reBalanceRec(huffNode *&node, int &numRotate) {
    if (node==NULL||numRotate>2) return;
    if (abs(node->balance())>1) {
        interHuffNode* inter=(interHuffNode*)node;
        if (inter->balance()>1) {
            interHuffNode* leftChild=(interHuffNode*) inter->lc;
            if (leftChild->balance()<0) inter->lc=rotateLeft(leftChild);
            node=rotateRight(node);
        } else {
            interHuffNode* rightChild=(interHuffNode*) inter->rc;
            if (rightChild->balance()>0) inter->rc=rotateRight(rightChild);
            node=rotateLeft(node);
        }
        numRotate++;
    }
    if (node->isLeaf()) return;
    interHuffNode* inter=(interHuffNode*)node;
    reBalanceRec(inter->lc, numRotate);
    reBalanceRec(inter->rc, numRotate);
    //quay lại root hay không?
    if (abs(node->balance())>1) reBalanceRec(node, numRotate);
}

int binToDec(string s) {
	int res=0;
	for (unsigned int i=0; i<s.size(); i++) res+=(s[s.size()-1-i]-48)*pow(2, i);
	return res;
}

void Restaurant::GHouse::GZone::add(int result) {
    bst->add(result);
    v.push_back(result);
}

void Restaurant::GHouse::GZone::kokusenZone() {
    long int Y=bst->calcPermutation();
    int num=Y%MAXSIZE, n=v.size();
    if (num>=n) {bst->clear(); v.clear(); return;}
    else {
        for (int i=0; i<num; i++) {
            bst->remove(v[0]);
            v.erase(v.begin());
        }
    }
}

void Restaurant::GHouse::add(int result) {
    int id=result%MAXSIZE+1;
    if (listZone[id-1]==NULL) listZone[id-1]=new GZone(id, result);
    else listZone[id-1]->add(result);
}

void Restaurant::GHouse::kokusen() {
    for (int i=0; i<MAXSIZE; i++) {
        if (listZone[i]!=NULL) {
            listZone[i]->kokusenZone();
            if (listZone[i]->v.size()==0) {delete listZone[i]; listZone[i]=NULL;}
        }
    }
}

void Restaurant::GHouse::limitless(int num) {
    if (num>MAXSIZE) return;
    if (listZone[num-1]!=NULL) listZone[num-1]->print();
}

void Restaurant::SHouse::SZone::remove(int num, int maxUpdateVal) {
    int n=v.size();
    if (num>=n) num=n;
    for (int i=0; i<num; i++) {
        cout<<v[0]<<'-'<<ID<<endl;
        v.erase(v.begin());
    }
    if (!v.empty()) updateVal=maxUpdateVal;
}

bool Restaurant::SHouse::SZone::operator<(SZone &a)
{
    if (v.size()==a.v.size()) return updateVal<a.updateVal;
    else return v.size()<a.v.size();
}

string Restaurant::SHouse::SZone::print() {
    int n=v.size();
    if (numPrint>n) numPrint=n;
    string s="";
    for (int i=v.size()-1; i>=n-numPrint; i--)
        s+=to_string(ID)+'-'+to_string(v[i])+'\n';
    return s;
}

void Restaurant::SHouse::add(int result) {
    int id=result%MAXSIZE+1;
    if (listZone[id-1]==NULL) {
        listZone[id-1]=new SZone(id, result, maxUpdateVal++);
        minHeap.insert(listZone[id-1]);
    } else {
        listZone[id-1]->add(result, maxUpdateVal++);
        minHeap.reheapDown(minHeap.findHeap(listZone[id-1]));
    }
}

vector<int> Restaurant::SHouse::listIdToDelete(int num) {
    vector<int> v;
    MinHeap <SZone*> copyHeap(minHeap);
    for (int i=0; i<num; i++) v.push_back(copyHeap.pop()->ID);
    return v;
}

void Restaurant::SHouse::keiteiken(int num) {
    int numZone=(num>minHeap.size()?minHeap.size():num);
    vector<int> v=listIdToDelete(numZone);
    for (int i=0; i<numZone; i++) {
        int id=v[i];
        listZone[id-1]->remove(num, maxUpdateVal++);
        if (listZone[id-1]->v.size()==0) {
            minHeap.remove(minHeap.findHeap(listZone[id-1]));
            delete listZone[id-1]; listZone[id-1]=NULL;
        } else minHeap.reheapDown(minHeap.findHeap(listZone[id-1]));
    }
}

void Restaurant::SHouse::cleave(int num) {
    for (int i=0; i<minHeap.size(); i++) minHeap[i]->numPrint=num;
    minHeap.preOder(0);
}

int Restaurant::calcResult(vector<letter> &v, string caeName) {
    if (currentHuffTree!=NULL) delete currentHuffTree;
    currentHuffTree=new huffmanTree(v);
	vector<huffCode> codeList=currentHuffTree->encode();
	string s="";
	string code[58];
	for (unsigned int i=0; i<codeList.size(); i++) code[codeList[i].c-65]=codeList[i].code;
	for (int i=caeName.size()-1; i>=0&&s.size()<10; i--) s=code[caeName[i]-65]+s;
    reverse(s.begin(), s.end());
	s=s.substr(0, 10);
	return binToDec(s);
}

void Restaurant::lapse(string name) {
    vector<letter> v = prepareName1(name);
	if (v.size()<3) return;
	string caeName=caesarName(name, v);
	lastPrepare(v);
	int result=calcResult(v, caeName);
    if (result&1) {
        if (gHouse==NULL) gHouse=new GHouse;
        gHouse->add(result);
    } else {
        if (sHouse==NULL) sHouse=new SHouse;
        sHouse->add(result);
    }
}

void Restaurant::kokusen() {
    if (gHouse==NULL) return;
    gHouse->kokusen();
}

void Restaurant::keiteiken(int num) {
    if (sHouse==NULL||num<1) return;
    sHouse->keiteiken(num);
}

void Restaurant::hand() {
    if (currentHuffTree==NULL) return;
    currentHuffTree->inoder();
}

void Restaurant::limitless(int num) {
    if (gHouse==NULL||num<1) return;
    gHouse->limitless(num);
}

void Restaurant::cleave(int num)
{
    if (sHouse==NULL||num<1) return;
    sHouse->cleave(num);
}

void simulate(string filename) {
	Restaurant* res = new Restaurant;
	ifstream ss(filename);
	string str, maxsize, name, num;
    int i=1;
	while(ss >> str) {
		if (str=="MAXSIZE") {
			ss >> maxsize;
			MAXSIZE = stoi(maxsize);
		} else if (str=="LAPSE") {
			ss >> name;
			res->lapse(name);
		} else if (str=="KOKUSEN") {
			res->kokusen();
		} else if (str=="KEITEIKEN") {
			ss >> num;
			try {res->keiteiken(stoi(num));}
            catch(std::invalid_argument) {cout<<"invalid_argument; keiteiken "<<num<<"at line "<<i; return;}
		} else if (str=="HAND") {
			res->hand();
		} else if (str=="LIMITLESS") {
			ss >> num;
			try {res->limitless(stoi(num));}
            catch(std::invalid_argument) {cout<<"invalid_argument; limitless "<<num<<"at line "<<i; return;}
		} else {
			ss >> num;
			try {res->cleave(stoi(num));}
            catch(std::invalid_argument) {cout<<"invalid_argument; cleave "<<num<<"at line "<<i; return;}
		} i++;
	}
	delete res;
    ss.close();
	return;
}
