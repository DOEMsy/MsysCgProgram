#include <bits/stdc++.h>
#define fr(i,k) for(int i=0;i<k;i++)
#define frr(i,k,n) for(int i=k;i<n;i++)
//#define fr0inp() for(;tail<n;tail++)


using namespace std;

///---辅助操作函数---///

void exit_sl(int a){
    system("pause>nul");
    exit(a);
}

bool operator == (string a,string b)
{
    if(a.length()!=b.length())
        return 0;
    fr(i,a.length())
        if(a[i]!=b[i])
            return 0;
    return 1;
}

bool operator != (string a,string b)
{
    if(a.length()!=b.length())
        return 1;
    fr(i,a.length())
        if(a[i]!=b[i])
            return 1;
    return 0;
}







struct note{
    vector<string>str;
    vector<double>num;



    bool ishead=false;
    int len=0;
    void add(string s){
        str.push_back(s);
    }
    void add(int n){
        num.push_back(n);
    }
    void add(double d){
        num.push_back(d);
    }
    void add(char c){
        string s=" ";
        s[0]=c;
        str.push_back(s);
    }

    note *last;
    note *next;

    ///----输入----///
    void plinput(int a[],int l){///批量格式输入
        string inp0;            ///负数为字符串个数，正数为数字
        double inp1;            ///a[] 格式 ，L 总长度
        int i=0,inpnum=0;       ///要求abs(ai)求和等于L
        while(inpnum<l){
           // cout<<a[i]<<endl;
            if(a[i]<0){
                input_str(abs(a[i]));
                inpnum+=abs(a[i]);i++;
                if(inpnum>l){
                    cout<<"plinput:格式控制与总输入和不符合！"<<endl;
                    cout<<"  inpnum:"<<inpnum<<' '<<"l:"<<l<<endl;
                    cout<<"  i:"<<i-1<<' '<<"a[i]:"<<a[i-1]<<endl;
                    exit_sl(1);
                }
            }
            else if(a[i]>0){
                input_int(a[i]);
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
    }

    void input_str(int a){ ///输入a字符串
        fr(i,a){
            string s;
            cin>>s;
            str.push_back(s);
        }
    }

    void input_int(int a){ ///输入a个数字
        fr(i,a){
            int n;
            cin>>n;
            num.push_back(n);
        }
    }

    void output_str(int b =0,int e = -1)
    {
        if(e==-1)
            e = str.size();
        if(b>e){
            cout<<"output_str:错误！输出字符串首段大于尾端"<<endl;
            exit_sl(0);
        }
        if(e>str.size()){
            cout<<"output_str:错误！尾端越界"<<endl;
            exit_sl(0);
        }
        frr(i,b,e)
            cout<<str[i]<<' ';
        cout<<endl;
    }


}*head[10005];







///
///
///   -> 5 6 7 head 1 2 3 4 ->
note *newhead();
int counti(note *,note);///统计与其值完全相同的个数
note *hishead(note *); ///找到该节点的头节点


note *newhead() ///创建新头
{
    note *nhead = new note;
    nhead->next = nhead;  ///空头 自成环
    nhead->last = nhead;
    nhead->ishead = true;
    nhead->len = 0;
    return nhead;
}

int counti(note *head,note item)///统计与其值完全相同的个数
{
    if(head->ishead==false){
        cout<<"findin:错误！搜索引用的链表接入点不是头结点"<<endl;
        exit_sl(0);
    }

    int s = 0;
    note *p = head->next;                       ///如果不存在则返回头节点
    while(p!=head){
        bool same = true;
        if(p->num.size()==item.num.size())
            fr(i,p->num.size()){
                if(p->num[i]!=item.num[i]){
                    same = false;
                    break;
                }
            }
        if(same==false) continue;
        if(p->str.size()==item.str.size())
            fr(i,p->str.size()){
                if(p->str[i]!=item.str[i]){
                    same = false;
                    break;
                }
            }
        if(same==true) s++;
        p = p->next;
    }

}

void movenote(note *a,note *b)///将a移动到b的前面
{
    if(a->ishead==true){
        cout<<"movenote:错误！移动的节点是头结点"<<endl;
        exit_sl(0);
    }

    if(a==b) return;
    a->last->next = a->next;
    a->next->last = a->last;

//    cout<<a->num[0] <<' '<<b->num[0] <<endl;

    b->last->next = a;
    a->last = b->last;
    b->last = a;
    a->next = b;
}
void swapnote(note *a,note *b)
{
    if(a->ishead==true||b->ishead==true){
        cout<<"swapnote:错误！替换的节点是头结点"<<endl;
        exit_sl(0);
    }

    a->next->last = b;
    a->last->next = b;
    b->last->next = a;
    b->next->last = a;
    note *temp = b->next;
    b->next = a->next;
    a->next = temp;
    temp = b->last;
    b->last = a->last;
    a->last = temp;
}

void additem(note *position,note iteml) ///在位置前面添加数据
{
                                                ///循环链表，head->last 是尾部
    note *item = new note(iteml);

    item->next=position;
    position->last->next = item;
    item->last = position->last;
    position->last = item;
    hishead(position)->len++;
}

void deleitem(note *position) ///删除目标位置的数据
{
    if(position->ishead==true){
        cout<<"deleitem:错误！删除头节点不合法"<<endl;
        exit_sl(0);
    }

    position->last->next = position->next;
    position->next->last = position->last;
    delete position;
}

///----搜索函数--------///

note *findin(note *head,int num,int ati=0) ///在目标链表中查找第一个ati下标拥有目标值的节点的地址
{
    if(head->ishead==false){
        cout<<"findin:错误！搜索引用的链表接入点不是头结点"<<endl;
        exit_sl(0);
    }

    note *p = head->next;                       ///如果不存在则返回头节点
    while(p!=head){
        if(p->num.size()>ati&&p->num[ati]==num)
            break;
        p = p->next;
    }
    return p;
}

note *findin(note *head,double num,int ati=0) ///在目标链表中查找第一个ati下标拥有目标值的节点的地址
{
    if(head->ishead==false){
        cout<<"findin:错误！搜索引用的链表接入点不是头结点"<<endl;
        exit_sl(0);
    }

    note *p = head->next;                       ///如果不存在则返回头节点
    while(p!=head){
        if(p->num.size()>ati&&p->num[ati]==num)
            break;
        p = p->next;
    }
    return p;
}

note *findin(note *head,string str,int ati=0) ///在目标链表中查找第一个ati下标拥有目标值的节点的地址
{
    if(head->ishead==false){
        cout<<"findin:错误！搜索引用的链表接入点不是头结点"<<endl;
        exit_sl(0);
    }

    note *p = head->next;                       ///如果不存在则返回头节点
    while(p!=head){
        if(p->str.size()>ati&&p->str[ati]==str)
            break;
        p = p->next;
    }
    return p;
}

note *atitem(note *head,int n)///查找第n位学生（循环）
{
    if(head->ishead==false){
        cout<<"atitem:错误！引用的链表接入点不是头结点"<<endl;
        exit_sl(0);
    }

    int num=0;
    note *p = head->next; ///head不算位
    while(true){        ///0123456排开
        if(n==num)
            return p;
        if(p->ishead==false)
            num++;
        p = p->next;
    }

}

note *hishead(note* p) ///返回p的头节点
{
    note *h = p;
    while(h->ishead==false){
        h = h->next;
    }
    return h;
}


///----排序----///
///自定义排序函数

bool cmpda(note* a,note *b)
{
    return a->num[0]>b->num[0];
}

bool cmpxi(note *a,note *b)
{
    return a->num[0]<b->num[0];
}

void sort_list(note *head,bool (*cmpfunction)(note*,note*))
{
    if(head->ishead==false){
        cout<<"sort_list:错误！搜索引用的链表接入点不是头结点"<<endl;
        exit_sl(0);
    }

    note *p = head->next;
    while(p!=head){
        note *j = p->next;
        while(j!=head){
            if(!cmpfunction(p,j)){
                p->num.swap(j->num);
                p->str.swap(j->str);
            }
            j=j->next;
        }
        p=p->next;
    }
}








///----批量操作----///

void print_num_0(note *);
void print_str_0(note *);
void print_str_len(note *);
bool is_once_cycle(note *,note *);
void deletenumber_m(note *item);

void maps( note *position,void (*mapfunction)(note*),bool Zheng = true,bool (*iffunction)(note*,note*) = is_once_cycle)
{                                                     ///起始位置,操作函数，终止条件，正向？
    if(Zheng){                                        ///位置开始对整个链表操作
        note *p = position;
        while(true){
            if(p->ishead==false)
                mapfunction(p);
            p = p->next;
            if(iffunction(position,p))
                break;
        }
    }
    else{
        note *p = position;
        while(true){
            if(p->ishead==false)
                mapfunction(p);
            p = p->last;
            if(iffunction(position,p))
                break;
        }
    }
}
///--自定义的循环终止条件函数--
bool is_once_cycle(note *begin_position,note *p)///是否为一圈？（只循环一圈）
{
    if(p == begin_position)
        return true;
    return false;
}

bool is_one_leaved(note *begin_position,note *p)
{
    if(p->next==begin_position&&p->last==begin_position)
        return true;
    return false;
}

///--自定义可被批量的操作函数（要求无返回值，只有参数note*,int）

void print_str_0(note *item){
    cout<<item->str[0]<<' ';
}
void print_str_len(note *item){
    cout<<item->str[0]<<':';
    cout<<item->str.size()<<endl;
}
void print_num_0(note *item){
    cout<<item->num[0]<<' ';
}

void finddelete(note *item)
{
    double num = item->num[0];
    note *p = findin(head[1],num);
    if(p->ishead==false){
        deleitem(item);
        deleitem(p);
    }
}

int deletenum_m,deletenum_ml;///删除第m数,查数计数ml
void deletenumber_m(note *item)  ///约瑟夫环
{
    if(deletenum_ml == deletenum_m){
        cout<<item->num[0]<<' ';
        deleitem(item);
        deletenum_ml = 0;
    }
    deletenum_ml++;
}

void additemtoZERO(note *item)
{
    movenote(head[0],item);
}

///--参数修改-----------------
#define precision 0 ///输出小数点后几位

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout<<setiosflags(ios::fixed)<<setprecision(precision);

    ///---代码部分-----
    note strw;
    head[0] = newhead();
    head[1] = newhead();
    int n;
    strw.input_str(11);

    strw.str.clear();
    //scanf("please input the number of nodes for the 1st linked list: %d",&n);

    cin>>n;
            strw.input_str(8);

        strw.str.clear();
    fr(i,n){
        note item;item.input_int(1);
        //cout<<item.num[0]<<endl;
        additem(head[0],item);
    }
    //scanf("please input the number of nodes for the 1st linked list: %d",&n);
    strw.input_str(11);

    strw.str.clear();
    cin>>n;
        strw.input_str(8);

        strw.str.clear();
    fr(i,n){

        note item;item.input_int(1);
        additem(head[0],item);
    }

    maps(head[1],additemtoZERO,true,is_one_leaved);
    sort_list(head[0],cmpxi);
    maps(head[0],print_num_0);
    ///-------------------

    return 0;
}
