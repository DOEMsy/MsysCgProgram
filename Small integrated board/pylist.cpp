
#include <bits/stdc++.h>
#define f(k) for(int z=0;z<k;z++)
#define fr(i,k) for(int i=0;i<k;i++)
#define frr(i,k,n) for(int i=k;i<n;i++)
//#define fr0inp() for(;tail<n;tail++)



using namespace std;

void exit_sl(int a){
    system("pause>nul");
    exit(a);
}


typedef string str;

///---element---------------------------------------------------------------------------///

class element{
public:
    double eint;    ///  1
    string estr;    /// -1
    int typeint;

    element(){typeint = -1;};
    element(double a){typeint = 1;eint = a;}    ///数字构造
    element(string a){typeint = -1;estr = a;}   ///字符串构造
    ~element(){};

    double eintf(){return eint;}
    string estrf(){return estr;}
    int type();                                 ///当前类型数字
    int len();                                  ///长度

    string tostring();                          ///复刻一个字符串
    double todouble();                          ///复刻一个数字
    string changetostring();                    ///转换成字符串
    double changetodouble();                    ///转换成数字

    void modify(double);                        ///赋值函数并改变类型
    void modify(string);

    element operator=(string);                 ///重载赋值&改变类型
    element operator=(double);
    element operator=(char []);

    bool operator == (double);
    bool operator == (string);
    bool operator == (element);

    bool operator > (double);
    bool operator > (string);
    bool operator > (element);

    bool operator < (double);
    bool operator < (string);
    bool operator < (element);

    void operator += (double);
    void operator += (element);
    void operator *= (double);
    void operator *= (element);

    element operator [](int);                   ///下标

    operator double();                          ///强制转换重载
    operator string();
};

int element::type(){return typeint;}
int element::len(){return tostring().length();}


string element::tostring(){
    if(typeint==1){
        stringstream ss;
        ss<<eint;
        ss>>estr;
    }
    return estr;
}

double element::todouble(){
    if(typeint==-1){
        stringstream ss;
        ss<<estr;
        ss>>eint;
    }
    return eint;
}


string element::changetostring(){
    if(typeint==1){
        stringstream ss;
        ss<<eint<<endl;
        ss>>estr;
        typeint = -1;
    }
    return estr;
}

double element::changetodouble(){
    if(typeint==-1){
        stringstream ss;
        ss<<estr;
        ss>>eint;
        typeint = 1;
    }
    return eint;
}

void element::modify(double a){
    typeint = 1;
    eint = a;
}

void element::modify(string a){
    typeint = -1;
    estr = a;
}

element element::operator = (double a){
    modify(a);
    return a;
}
element element::operator = (string a){
    modify(a);
    return a;
}
element element::operator = (char a[]){
    modify(a);
    return string(a);
}

element::operator string(){
    return tostring();
}

element::operator double(){
    return todouble();
}



bool element::operator == (double a){
    return todouble()==a;
}

bool element::operator == (string a){
    return tostring()==a;
}

bool element::operator == (element e){
    if(typeint==1)
        return todouble()==e.todouble();
    return tostring()==e.tostring();
}




bool element::operator > (double a){
    return todouble()>a;
}

bool element::operator > (string a){
    return tostring()>a;
}

bool element::operator > (element e){
    if(typeint==1)
        return todouble()>e.todouble();
    return tostring()>e.tostring();
}


bool element::operator < (double a){
    return todouble()<a;
}

bool element::operator < (string a){
    return tostring()<a;
}

bool element::operator < (element e){
    if(typeint==1)
        return todouble()<e.todouble();
    return tostring()<e.tostring();
}

element element::operator [](int i){
    if(i>=len()){
        cout<<"element::[] :错误！下标引用越界"<<endl;
        exit_sl(1);
    }

    char c[5];
    c[0] = tostring()[i];
    c[1] = '\0';
    element e = str(c);
    return e;
}



///---pylist---------------------------------------------------------------------------///

#define _Nofound -1
#define _All -1

class pylist{
public:
    vector<element>eles;

    pylist(){}
    ~pylist(){}

    int len();                  ///返回长度
    void append(double);        ///尾部添加元素
    void append(string);
    void append(element);
    pylist& operator << (element);

    void insert(int,double);    ///在指定位置插入元素
    void insert(int,string);
    void insert(int,element);

    void del(int);              ///删除指定位置元素
    void del(int,int);

    int find(element);       ///返回搜索目标的位置

    element& operator [](int); ///下标重载
    pylist sublist(int,int);   ///子列表 _All代表从端头开始

    string tostring();          ///转换成字符串
};


int pylist::len(){return eles.size();}

void pylist::append(double a){
    element e(a);
    eles.push_back(e);
}

void pylist::append(string a){
    element e(a);
    eles.push_back(e);
}

void pylist::append(element e){
    eles.push_back(e);
}

pylist& pylist::operator << (element e){
    append(e);
    pylist &l=(*this);
    return l;
}

void pylist::insert(int i,double a){
    if(i<0||i>=len()){
        cout<<"pylist::insert :错误！插入越界"<<endl;
        exit_sl(1);
    }
    eles.insert(eles.begin()+i,a);
}

void pylist::insert(int i,string a){
    if(i<0||i>=len()){
        cout<<"pylist::insert :错误！插入越界"<<endl;
        exit_sl(1);
    }
    eles.insert(eles.begin()+i,a);
}

void pylist::insert(int i,element e){
    if(i<0||i>=len()){
        cout<<"pylist::insert :错误！插入越界"<<endl;
        exit_sl(1);
    }
    eles.insert(eles.begin()+i,e);
}

void pylist::del(int i){
    if(i<0||i>=len()){
        cout<<"pylist::del :错误！删除越界"<<endl;
        exit_sl(1);
    }
    eles.erase(eles.begin()+i);
}

void pylist::del(int i,int j){
    if(!(0<=i&&i<j&&j<=len())){
        cout<<"pylist::del :错误！删除越界"<<endl;
        exit_sl(1);
    }
    eles.erase(eles.begin()+i,eles.begin()+j);
}

int pylist::find(element e){
    fr(i,len()){
        if(e==eles[i])
            return i;
    }
    return _Nofound;
}

element& pylist::operator [](int i){
    if(i<0||i>=len()){
        cout<<"pylist::[] :错误！下标越界 "<<i<<">="<<len()<<endl;
        exit_sl(1);
    }
    return eles[i];
}

pylist pylist::sublist(int i,int j){    /// i 起点 ， j 长度

    if(i==_All) i=0;
    if(j==_All) j=len()-i;

    if(i<0||i+j>len()||j<0){
        cout<<"pylist::sublist :错误！子链表越界！"<<endl;
        exit_sl(1);
    }
    pylist sublist;
    frr(k,i,i+j)  sublist<<eles[k];
    return sublist;
}

string pylist::tostring(){
    stringstream ss;
    fr(i,len()){
        ss<<eles[i].tostring()<<' ';
    }
    string s=ss.str();
    return s;
}


///---输入---------------------------------------------------------------------------------------///
pylist input(){  ///读入一行作为pylist返回
    string inp;
    getline(cin,inp);


    stringstream ss;
    ss<<inp;
    pylist lis;

    while(ss>>inp){
        lis<<inp;
    }
    return lis;
}

pylist input(int a[],int l){  ///格式化输入一行，对前l个元素进行a格式化读入，舍弃后面元素 要求l = ∑abs（ai）
    string inp;
    getline(cin,inp);

    stringstream ss;
    ss<<inp;
    pylist lis;
    //cout<<l<<endl;
    int i=0,inpnum=0;       ///要求abs(ai)求和等于L
    while(inpnum<l&&!ss.eof()){
        // cout<<a[i]<<endl;
        if(a[i]<0){
            f(abs(a[i])){
                ss>>inp;
                //cout<<inp<<' ';
                element e(inp);
                lis<<e;
                //cout<<lis.tostring()<<endl;
            }
            inpnum+=abs(a[i]);i++;
            if(inpnum>l){
                cout<<"plinput:格式控制与总输入和不符合！"<<endl;
                cout<<"  inpnum:"<<inpnum<<' '<<"l:"<<l<<endl;
                cout<<"  i:"<<i-1<<' '<<"a[i]:"<<a[i-1]<<endl;
                exit_sl(1);
            }
        }
        else if(a[i]>0){
            f(abs(a[i])){
                ss>>inp;
                //cout<<inp<<' ';
                element e(inp);
                lis<<e.todouble();
                //cout<<lis.tostring()<<endl;
            }
            inpnum+=abs(a[i]);i++;
            if(inpnum>l){
                cout<<"plinput:格式控制与总输入和不符合！"<<endl;
                cout<<"  inpnum:"<<inpnum<<' '<<"l:"<<l<<endl;
                cout<<"  i:"<<i-1<<' '<<"a[i]:"<<a[i-1]<<endl;
                exit_sl(1);
            }
        }
        else{
            cout<<"plinput:输入格式控制有误，不可以有0！"<<endl;
            exit_sl(1);
        }
    }
    return lis;
}




///---输出---------------------------------------------------------------------------------------///
int presicion = 2;

void print(element e,char end='\n'){
    cout<<setiosflags(ios::fixed)<<setprecision(presicion)<<e.tostring()<<end;
}
void print(string a,char end='\n'){
    cout<<setiosflags(ios::fixed)<<setprecision(presicion)<<a<<end;
}
void print(pylist l,char end='\n'){
    cout<<setiosflags(ios::fixed)<<setprecision(presicion)<<l.tostring()<<end;
}

void print(double a,char end='\n'){
    cout<<setiosflags(ios::fixed)<<setprecision(presicion)<<a<<end;
}

void print(long long a,char end='\n'){
    cout<<setiosflags(ios::fixed)<<setprecision(presicion)<<a<<endl;
}


///---重载运算符号------------------------------------------------------------------------------///
string operator +(string s1,string s2){
    string s(s1);
    return s.append(s2);
}

string operator +(string s,double a){
    stringstream ss;
    ss<<a;
    s.append(ss.str());
    return s;
}

string operator +(double a,string s){
    stringstream ss;
    ss<<a;
    return ss.str()+s;
}

element operator +(element e1,element e2){
    if(e1.type()==1&&e2.type()==1)    //全数字
        return element(e1.eintf()+e2.eintf());

    return element(e1.tostring()+e2.tostring());
}
element operator +(element e,int a){
    element e1(e.eintf()+a);
    return e1;
}
void element::operator +=(double a){
    if(type()==1)  eint+=a;
    else    estr+=a;
}
void element::operator +=(element e){
    if(type()==1&&e.type()==1)
        eint+=e.eintf();
    e.changetostring();
    estr+=e.tostring();
}


element operator -(element e1,element e2){
    return e1.todouble() - e2.todouble();
}
element operator -(int a,element e){
    return a - e.todouble();
}
element operator -(element e,int a){
    return e.todouble() - a;
}
element operator -(element e){
    return -e.todouble();
}



element operator +(element e1,double a){
    element e;
    if(e1.type()==1)
        e = e1.eintf()+a;
    else
        e = e1.estrf()+a;
    return e;
}

element operator +(double a,element e1){
    element e;
    if(e1.type()==1)
        e = e1.eintf()+a;
    else
        e = a+e1.estrf();
    return e;
}

element operator +(element e1,string s){
    element e;
    e = e1.tostring()+s;
    return e;
}

element operator +(string s,element e1){
    element e;
    e = s+e1.tostring();
    return e;
}

element operator *(element e1,element e2){
    element e(e1.todouble()*e2.todouble());
    return e;
}
element operator *(element e,double a){
    return element(e.todouble()*a);
}
element operator *(double a,element e){
    return element(e.todouble()*a);
}
void element::operator*=(double a){
    changetodouble();
    eint*=a;
}
void element::operator*=(element e){
    changetodouble();
    eint*=e.todouble();
}

pylist operator + (pylist a,pylist b){
    pylist c = a;
    fr(i,b.len()) c<<b[i];
    return c;
}
string operator + (pylist a,string s){
    return a.tostring()+s;
}
string operator + (string s,pylist a){
    return s+a.tostring();
}

///---功能性函数-------------------------------------------------------------------------------///

long long operator !(element e){
    long long sum = 1;
    frr(i,1,e+1){
        sum*=i;
    }
    return sum;
}


int main()
{
    pylist t = input();
    pylist s = input();



    if(t[2]>3) print(str("teacher ")+t[1]+" is excellent");
    else print(str("teacher ")+t[1]+" is not excellent");
    if(s[2]<=element(90).changetodouble()) print(str("student ")+s[1]+" is not excellent");
    else print(str("student ")+s[1]+" is excellent");
    return 0;
}
