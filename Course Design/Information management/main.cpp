#include <bits/stdc++.h>
#include <windows.h>
#define fr(i,k) for(int i=0;i<k;i++)
#define frr(i,k,n) for(int i=k;i<n;i++)

#pragma execution_character_set("utf-8")

///参数调整
#define bottonnum 5 ///按键数
    ///域宽
#define numW 12   ///学号
#define nameW 8   ///姓名
#define scoreW 6     ///分数

using namespace std;





///************************************************************************///
///--- @Programfunction ---辅助操作函数-----------------------------------///


    ///程序调试&&运行错误退出
void exit_sl(int a=0){
    system("pause>nul");
    exit(a);
}

    ///string == 重载
bool operator == (string a,string b)
{
    if(a.length()!=b.length())
        return 0;
    fr(i,a.length())
        if(a[i]!=b[i])
            return 0;
    return 1;
}

bool operator < (string a,string b)
{
    int la = a.length();
    int lb = b.length();
    if(la!=lb)
        return la<lb;

    fr(i,la){
        if(a[i]!=b[i])
            return a[i]<b[i];
    }

    return 0;
}


    ///string != 重载
bool operator != (string a,string b)
{
    if(a.length()!=b.length())
        return 1;
    fr(i,a.length())
        if(a[i]!=b[i])
            return 1;
    return 0;
}


    ///顿字输出语句
void print(string s,char end='\n')
{
    int l = s.length();
    int time = 230/l;
    fr(i,l){
        cout<<s[i];
        Sleep(time);
    }
    cout<<end;
}

    ///模仿jv string + 运算
string operator + (string a,string b)
{
    return a.append(b);
}

    ///暂停
void pause(bool printstr = true)
{
    if(printstr)
        print("-按任意键继续");
    system("pause>nul");
}

    ///清屏
void clearscreen(int Sleeptime = 0)
{
    Sleep(Sleeptime);
    system("cls");
}


    ///string -> double 转换
double todouble(string s)
{
    int l = s.length();
    fr(i,l)
        if(!(('0'<=s[i]&&s[i]<='9')||s[i]=='.'))
            return -1;

    stringstream ss;
    ss<<s<<endl;
    double b;
    ss>>b;
    return b;
}









///***********************************************************************///
///--- @List ---链表和链表操作函数---------------------------------------///


class note   ///链表节点单元
{
public:
    ///结构体内文本类数据，- 为任意数据
    ///0 num   1 name
    vector<string>strs;
    ///结构体内数字类数据，- 为任意数据
    ///0 all   [1:6) score
    vector<double>nums;

    bool ishead;  ///是否为头节点
    int len;          ///链表长度

    note *next;
    note *last;

    note(){ishead=false;len=0;strs.push_back("-");strs.push_back("-");}
    ~note(){};

    void output(bool TestMode = false,ostream &out = cout) ///输出结构体
    {
        if(!TestMode){
            out<<setw(numW)<<left<<strs[0];
            out<<setw(nameW)<<left<<strs[1];
            frr(i,1,6)
                out<<setw(scoreW)<<left<<nums[i];
            out<<setw(scoreW+1)<<left<<nums[0];
            cout<<endl;
        }
        else{
            out<<strs[0]<<' ';
            out<<strs[1]<<' ';
            frr(i,1,6)
                out<<nums[i]<<' ';
            cout<<endl;
        }
    }

    void input_scores(int l = 5,istream &in = cin) ///输入分数
    {
        string inp;
        nums.push_back(0);
        fr(i,l){
            in>>inp;
            nums.push_back(todouble(inp));
            nums[0]+=todouble(inp);
        }
    }
};

note *newhead();
void movenote(note *a,note *b);
void swapnote(note *a,note *b);
note copynote(note *a);
note *atitem(note *head,int n);
void deleitem(note *position);
note *hishead(note* p);

    ///创建新头
note *newhead()
{
    note *nhead = new note;
    nhead->next = nhead;  ///空头 自成环
    nhead->last = nhead;
    nhead->ishead = true;
    nhead->len = 0;
    return nhead;
}

     ///重载note::strs == 比较
bool operator == (note a,note b)
{
    int la = a.strs.size(),lb = b.strs.size();
    if(la!=lb)
        return false;
    fr(i,la){
        if(a.strs[i]!=b.strs[i]&&a.strs[i]!="-"&&b.strs[i]!="-") /// - 语句表示万能语句，可以与所有语句相等
            return false;
    }

    return true;
}

    ///将a移动到b的前面
void movenote(note *b,note *a)
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

    ///交换a与b的位置
void swapnote(note *a,note *b)
{
    if(a->ishead==true||b->ishead==true){
        cout<<"swapnote:错误！交换的节点是头结点"<<endl;
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

    ///返回note a 的复制元素
note copynote(note *a)
{
    if(a->ishead==true){
        cout<<"swapnote:错误！复制的节点是头结点"<<endl;
        exit_sl(0);
    }

    note item;

    item.strs=a->strs;
    item.nums=a->nums;
    return item;
}

    ///在位置前面添加数据
void additem(note *position,note iteml)
{
                                        ///循环链表，head->last 是尾部
    note *item = new note(iteml);

    item->next=position;
    position->last->next = item;
    item->last = position->last;
    position->last = item;
    //hishead(position)->len++;
    item->len=item->last->len+1;
}

    ///在位置前面添加数据
void additem(note *position,note *item)
{
                                        ///循环链表，head->last 是尾部
    item->next=position;
    position->last->next = item;
    item->last = position->last;
    position->last = item;
    //hishead(position)->len++;
    item->len=item->last->len+1;
}

    ///删除目标位置的数据
void deleitem(note *position)
{
    if(position->ishead==true){
        cout<<"deleitem:错误！删除头节点不合法"<<endl;
        exit_sl(0);
    }


    position->last->next = position->next;
    position->next->last = position->last;
    delete position;
}

    ///返回链表长度
int len(note *head)
{
    if(head->ishead==false){
        cout<<"len:错误！引用的链表接入点不是头结点"<<endl;
        exit_sl(0);
    }

    if(head->last==head)
        return 0;

    return head->last->len;
}



///----搜索函数--------///

    ///查找第n位学生（循环），返回其地址
note *atitem(note *head,int n)
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

    ///搜索并返回p的头节点
note *hishead(note* p)
{
    note *h = p;
    while(h->ishead==false){
        h = h->next;
    }
    return h;
}

    ///返回一个与值匹配的节点
note *finditem(note *head,note item)
{
    note *p = head->next;
    while(p!=head){
        if(*p==item)
            return p;
        p=p->next;
    }
    return NULL;
}

    ///用缓存链表载入一群与值匹配的节点,是否为复制,是否允许重复？
void *finditems(note *head,note *forits,note item,bool copy = true,bool mult = false)
{
    note *p = head->next;
    while(p!=head){
        if(*p==item){
            if(copy){
                if(mult==true)
                    additem(forits,copynote(p));
                else if(mult==false&&finditem(forits,*p)==NULL)
                    additem(forits,copynote(p));

                p=p->next;
            }
            else{
                note *frps=p;
                p=p->next;
                movenote(forits,frps);
            }
        }
        else{
            p=p->next;
        }
    }
}

///----排序----///

    ///对链表使用cmp排序方式（插入排序法 On2）
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
                p->nums.swap(j->nums);
                p->strs.swap(j->strs);
            }
            j=j->next;
        }
        p=p->next;
    }
}



bool is_once_cycle(note *begin_position,note *p);
void printitem(note *p);

///----批量操作----///

    ///对链表执行mapf操作，终止条件iffun：起始位置,操作函数，终止条件，正向？
void maps( note *position, void (*mapfunction)(note*), bool Zheng = true, bool (*iffunction)(note*,note*) = is_once_cycle)
{
    if(Zheng){                                        ///从position位置开始对整个链表操作
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

    ///打印链表
void PrintList(note *head)
{
    maps(head,printitem);
    cout<<"------------------------------------------------------------"<<endl;
}

///--自定义的循环终止条件函数--
bool is_once_cycle(note *begin_position,note *p)///是否为一圈？（只循环一圈）
{
    if(p == begin_position)
        return true;
    return false;
}

bool is_one_left(note *bp,note *p)
{
    if(bp->next = bp)
        return true;
    return false;
}

///--自定义可被批量的操作函数（要求无返回值，只有参数note*）
void printitem(note *p)    ///打印节点
{
    p->output();
}









///******************************************************************************************///
///--- @Inerface ---界面&程序表面--------------------------------------------------------------------///


char Text[20][20] = {"总分","程序","高数","数逻","离散","思政"};
note *listhead,*forits; ///主链表头，缓存链表头

    ///输出横幅
void TextLine(bool TestMode = false)
{
    if(len(listhead)){
        if(!TestMode){
            cout<<"------------------------------------------------------------"<<endl;
            cout<<setw(numW)<<left<<"学号";
            cout<<setw(nameW)<<left<<"姓名";
            frr(i,1,6)
                cout<<setw(scoreW)<<left<<Text[i];
                cout<<setw(scoreW+1)<<left<<Text[0];
            cout<<endl;
        }else{
            cout<<"学号"<<' ';
            cout<<"姓名"<<' ';
            frr(i,1,6)
                cout<<Text[i]<<' ';
            cout<<endl;

        }
    }
    else{
        cout<<"***数据为空***"<<endl;
    }
}


    ///排序规则
int SortMODE = 0;


     ///主菜单
void Menu()
{
    cout<<"排序规则：";
    if(SortMODE == 0) cout<<"总分";
    else if(SortMODE == 1) cout<<"学号";
    else cout<<Text[SortMODE-1];
    cout<<endl;


    cout<<"┌─────────────-┐"<<endl;
    cout<<"│1.搜索数据    │"<<endl;
    cout<<"│2.添加数据    │"<<endl;
    cout<<"│3.修改数据    │"<<endl;
    cout<<"│4.删除数据    │"<<endl;
    cout<<"│5.排序方式    │"<<endl;
    cout<<"│0.退出        │"<<endl;
    cout<<"└─────────────-┘"<<endl;
}

    ///欢迎界面
void Hello()
{
    clearscreen();
    cout<<"-----------------------"<<endl;
    cout<<"  欢迎来到班级管理系统"<<endl;
    cout<<"-----------------------"<<endl;
    print("-按任意键进入");
    pause(false);
    cout<<endl;
}

    ///搜索界面
void Find()
{
    note item1,item2;
    print("-请输入要查找同学的学号或姓名:");
    string inp;
    cin>>inp;
    item1.strs[0]=inp;
    item2.strs[1]=inp;

    maps(forits,deleitem,true,is_one_left);///清空缓存
    forits = newhead();

    finditems(listhead,forits,item1);
    finditems(listhead,forits,item2);

    if(!len(forits)){
        print("-未搜索到目标数据！");
    }
    else{
        print("-搜索结果如下：");
        TextLine();
        PrintList(forits);
    }
    pause();

    maps(forits,deleitem,true,is_one_left);///清空缓存
    forits = newhead();
}

    ///删除界面
void Dele()
{
    string inp;
    print("-请输入要删除的同学的学号(可批量,输入*结束):");

    int sum=0;
    while(true){

        note item;
        cin>>inp;
        if(inp == "*")
            break;
        if(inp == "-")
            inp = "&";
        item.strs[0]=inp;
        note *p = finditem(listhead,item);

        cout<<inp<<' ';
        if(p == NULL){
            print("学生不存在");
        }
        else{
            deleitem(p);
            print("删除成功！");
            sum++;
        }

    }
    print("-数据删除成功!成功删除",' ');
    cout<<sum;
    print("个数据");
    pause();
}

    ///添加界面
void Add()
{
    print("-请在一行内依次输入 学号 姓名 程序 高数 数逻 离散 思政");
    print("-每行输入一个同学，输入 * 结束:");
    int sum = 0;
    while(true){
        note item;
        string inp;
        cin>>inp;
        if(inp == "*")
            break;
        item.strs[0]=inp;
        cin>>item.strs[1];
        item.input_scores();

        additem(listhead,item);///向链表里添加节点
        sum++;
    }

    print("-数据输入成功!共输入",' ');
    cout<<sum;
    print("个数据");
    pause();
}

    ///修改界面
void Change()
{
    string inp;
    print("-请输入要修改的同学的学号:");
    cin>>inp;
    note item;item.strs[0]=inp;
    note *p = finditem(listhead,item);  ///在主链中寻找节点
    if(p!=NULL){
    print("-目标学生数据如下");
    print("-请对应格式重新输入该学生数据");
    print("-输入 - 的位置无改动:");
    p->output(true);

    cin>>inp;
    if(inp!="-")
        p->strs[0]=inp;
    cin>>inp;
    if(inp!="-")
        p->strs[1]=inp;

    frr(i,1,5){
        cin>>inp;
        if(inp!="-")
            p->nums[i]=todouble(inp);
    }
    print("-修改成功！");
    }
    else{
        print("-未找到目标数据！");
    }
    pause();
}

    ///输出学生排行榜
void PrintStus()
{
    clearscreen();
    TextLine();
    PrintList(listhead);
}

    ///改变排序界面
void Changesort()
{
    int bottonnum_1=3,bottonnum_2=5;
    clearscreen();
    cout<<"------切换排序方式------"<<endl;
    cout<<"     1.按总分排序（默认）"<<endl;
    cout<<"     2.按学号排序"<<endl;
    cout<<"     3.按单科排序"<<endl;
    print("-请输入排序方式序号：");

    int b;
    string inp;
    do{
        getline(cin,inp);
        b=inp[0]-'0';
        if(0<=b&&b<=bottonnum_1)
            break;
    }while(true);

    if(b==1||b==2){
        SortMODE = b-1;
    }
    else{
        cout<<"-----------------------------------"<<endl;
        cout<<"1.程序 2.高数 3.数逻 4.离散 5.思政"<<endl;
        print("-请输入排序引用的单科序号：");
        do{
        getline(cin,inp);
        b=inp[0]-'0';
        if(0<=b&&b<=bottonnum_2)
            break;
        }while(true);

        SortMODE = b+1;
    }
    print("-修改成功！");
    pause();

}


///--自定义数据排序方式--//

bool cmp_all(note *a,note *b)       //总分
{
    return a->nums[0]>b->nums[0];
}

bool cmp_stunum(note *a,note *b)    //学号
{
    return a->strs[0] < a->strs[0];
}

bool cmp_sco1(note *a,note *b)      //分数1
{
    return a->nums[1]>b->nums[1];
}

bool cmp_sco2(note *a,note *b)      //2
{
    return a->nums[2]>b->nums[2];
}

bool cmp_sco3(note *a,note *b)      //3
{
    return a->nums[3]>b->nums[3];
}

bool cmp_sco4(note *a,note *b)      //4
{
    return a->nums[4]>b->nums[4];
}

bool cmp_sco5(note *a,note *b)      //5
{
    return a->nums[5]>b->nums[5];
}

    ///对序列使用Sm方式排序
void Sort(note *head,int Sm=0)
{
    bool (*cmpFuntion)(note*,note*);

    switch(Sm){
    case 0:cmpFuntion = cmp_all;break;
    case 1:cmpFuntion = cmp_stunum;break;

    case 2:cmpFuntion = cmp_sco1;break;
    case 3:cmpFuntion = cmp_sco2;break;
    case 4:cmpFuntion = cmp_sco3;break;
    case 5:cmpFuntion = cmp_sco4;break;
    case 6:cmpFuntion = cmp_sco5;break;
    }

    sort_list(head,cmpFuntion);
}



///--数据同步--//
#define datefile "date.dat"

    ///从数据库中同步数据
void structin()
{
    ifstream datf(datefile,ios::in);

    string inp;
    while(datf>>inp){       ///定向datf流输入

        note item;
        item.strs[0]=inp;
        datf>>item.strs[1];
        item.input_scores(5,datf);

        additem(listhead,item);
    }
    datf.close();
}

    ///向数据库更新数据
void structout()
{
    ofstream datf(datefile,ios::out);

    note *p = listhead->next;
    while(p!=listhead){
        p->output(true,datf);
        p=p->next;
    }
    datf.close();
}






int main()
{
    cout<<setiosflags(ios::fixed)<<setprecision(1);


    listhead = newhead();
    forits = newhead();

    Hello();                        ///@Hello 加载欢迎界面
    structin();                     ///@structin 载入数据
    string inp;
    while(true){
        Sort(listhead,SortMODE);    ///@Sort 重排序
        PrintStus();                ///@PrintStus 输出学生信息
        Menu();                     ///@Menu 加载菜单界面
        print("-请输入操作：");
        int b;
        do{
            getline(cin,inp);
            b=inp[0]-'0';
            if(0<=b&&b<=bottonnum)
                break;
        }while(true);

        switch(b){
        case 0:
            exit(0);                ///@exit 退出
        case 1:
            Find();break;           ///@Find 查找
        case 2:
            Add();break;            ///@Add 添加
        case 3:
            Change();break;         ///@Change 修改
        case 4:
            Dele();break;           ///@Dele 删除
        case 5:
            Changesort();break;     ///@Changesort 修改排序方式
        }
        structout();                ///@structout 同步数据
    }
    return 0;
}
