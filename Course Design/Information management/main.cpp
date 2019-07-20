#include <bits/stdc++.h>
#include <windows.h>
#define fr(i,k) for(int i=0;i<k;i++)
#define frr(i,k,n) for(int i=k;i<n;i++)

#pragma execution_character_set("utf-8")

///��������
#define bottonnum 5 ///������
    ///���
#define numW 12   ///ѧ��
#define nameW 8   ///����
#define scoreW 6     ///����

using namespace std;





///************************************************************************///
///--- @Programfunction ---������������-----------------------------------///


    ///�������&&���д����˳�
void exit_sl(int a=0){
    system("pause>nul");
    exit(a);
}

    ///string == ����
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


    ///string != ����
bool operator != (string a,string b)
{
    if(a.length()!=b.length())
        return 1;
    fr(i,a.length())
        if(a[i]!=b[i])
            return 1;
    return 0;
}


    ///����������
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

    ///ģ��jv string + ����
string operator + (string a,string b)
{
    return a.append(b);
}

    ///��ͣ
void pause(bool printstr = true)
{
    if(printstr)
        print("-�����������");
    system("pause>nul");
}

    ///����
void clearscreen(int Sleeptime = 0)
{
    Sleep(Sleeptime);
    system("cls");
}


    ///string -> double ת��
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
///--- @List ---����������������---------------------------------------///


class note   ///����ڵ㵥Ԫ
{
public:
    ///�ṹ�����ı������ݣ�- Ϊ��������
    ///0 num   1 name
    vector<string>strs;
    ///�ṹ�������������ݣ�- Ϊ��������
    ///0 all   [1:6) score
    vector<double>nums;

    bool ishead;  ///�Ƿ�Ϊͷ�ڵ�
    int len;          ///������

    note *next;
    note *last;

    note(){ishead=false;len=0;strs.push_back("-");strs.push_back("-");}
    ~note(){};

    void output(bool TestMode = false,ostream &out = cout) ///����ṹ��
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

    void input_scores(int l = 5,istream &in = cin) ///�������
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

    ///������ͷ
note *newhead()
{
    note *nhead = new note;
    nhead->next = nhead;  ///��ͷ �Գɻ�
    nhead->last = nhead;
    nhead->ishead = true;
    nhead->len = 0;
    return nhead;
}

     ///����note::strs == �Ƚ�
bool operator == (note a,note b)
{
    int la = a.strs.size(),lb = b.strs.size();
    if(la!=lb)
        return false;
    fr(i,la){
        if(a.strs[i]!=b.strs[i]&&a.strs[i]!="-"&&b.strs[i]!="-") /// - ����ʾ������䣬����������������
            return false;
    }

    return true;
}

    ///��a�ƶ���b��ǰ��
void movenote(note *b,note *a)
{
    if(a->ishead==true){
        cout<<"movenote:�����ƶ��Ľڵ���ͷ���"<<endl;
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

    ///����a��b��λ��
void swapnote(note *a,note *b)
{
    if(a->ishead==true||b->ishead==true){
        cout<<"swapnote:���󣡽����Ľڵ���ͷ���"<<endl;
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

    ///����note a �ĸ���Ԫ��
note copynote(note *a)
{
    if(a->ishead==true){
        cout<<"swapnote:���󣡸��ƵĽڵ���ͷ���"<<endl;
        exit_sl(0);
    }

    note item;

    item.strs=a->strs;
    item.nums=a->nums;
    return item;
}

    ///��λ��ǰ���������
void additem(note *position,note iteml)
{
                                        ///ѭ������head->last ��β��
    note *item = new note(iteml);

    item->next=position;
    position->last->next = item;
    item->last = position->last;
    position->last = item;
    //hishead(position)->len++;
    item->len=item->last->len+1;
}

    ///��λ��ǰ���������
void additem(note *position,note *item)
{
                                        ///ѭ������head->last ��β��
    item->next=position;
    position->last->next = item;
    item->last = position->last;
    position->last = item;
    //hishead(position)->len++;
    item->len=item->last->len+1;
}

    ///ɾ��Ŀ��λ�õ�����
void deleitem(note *position)
{
    if(position->ishead==true){
        cout<<"deleitem:����ɾ��ͷ�ڵ㲻�Ϸ�"<<endl;
        exit_sl(0);
    }


    position->last->next = position->next;
    position->next->last = position->last;
    delete position;
}

    ///����������
int len(note *head)
{
    if(head->ishead==false){
        cout<<"len:�������õ��������㲻��ͷ���"<<endl;
        exit_sl(0);
    }

    if(head->last==head)
        return 0;

    return head->last->len;
}



///----��������--------///

    ///���ҵ�nλѧ����ѭ�������������ַ
note *atitem(note *head,int n)
{
    if(head->ishead==false){
        cout<<"atitem:�������õ��������㲻��ͷ���"<<endl;
        exit_sl(0);
    }

    int num=0;
    note *p = head->next; ///head����λ
    while(true){        ///0123456�ſ�
        if(n==num)
            return p;
        if(p->ishead==false)
            num++;
        p = p->next;
    }

}

    ///����������p��ͷ�ڵ�
note *hishead(note* p)
{
    note *h = p;
    while(h->ishead==false){
        h = h->next;
    }
    return h;
}

    ///����һ����ֵƥ��Ľڵ�
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

    ///�û�����������һȺ��ֵƥ��Ľڵ�,�Ƿ�Ϊ����,�Ƿ������ظ���
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

///----����----///

    ///������ʹ��cmp����ʽ���������� On2��
void sort_list(note *head,bool (*cmpfunction)(note*,note*))
{
    if(head->ishead==false){
        cout<<"sort_list:�����������õ��������㲻��ͷ���"<<endl;
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

///----��������----///

    ///������ִ��mapf��������ֹ����iffun����ʼλ��,������������ֹ����������
void maps( note *position, void (*mapfunction)(note*), bool Zheng = true, bool (*iffunction)(note*,note*) = is_once_cycle)
{
    if(Zheng){                                        ///��positionλ�ÿ�ʼ�������������
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

    ///��ӡ����
void PrintList(note *head)
{
    maps(head,printitem);
    cout<<"------------------------------------------------------------"<<endl;
}

///--�Զ����ѭ����ֹ��������--
bool is_once_cycle(note *begin_position,note *p)///�Ƿ�ΪһȦ����ֻѭ��һȦ��
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

///--�Զ���ɱ������Ĳ���������Ҫ���޷���ֵ��ֻ�в���note*��
void printitem(note *p)    ///��ӡ�ڵ�
{
    p->output();
}









///******************************************************************************************///
///--- @Inerface ---����&�������--------------------------------------------------------------------///


char Text[20][20] = {"�ܷ�","����","����","����","��ɢ","˼��"};
note *listhead,*forits; ///������ͷ����������ͷ

    ///������
void TextLine(bool TestMode = false)
{
    if(len(listhead)){
        if(!TestMode){
            cout<<"------------------------------------------------------------"<<endl;
            cout<<setw(numW)<<left<<"ѧ��";
            cout<<setw(nameW)<<left<<"����";
            frr(i,1,6)
                cout<<setw(scoreW)<<left<<Text[i];
                cout<<setw(scoreW+1)<<left<<Text[0];
            cout<<endl;
        }else{
            cout<<"ѧ��"<<' ';
            cout<<"����"<<' ';
            frr(i,1,6)
                cout<<Text[i]<<' ';
            cout<<endl;

        }
    }
    else{
        cout<<"***����Ϊ��***"<<endl;
    }
}


    ///�������
int SortMODE = 0;


     ///���˵�
void Menu()
{
    cout<<"�������";
    if(SortMODE == 0) cout<<"�ܷ�";
    else if(SortMODE == 1) cout<<"ѧ��";
    else cout<<Text[SortMODE-1];
    cout<<endl;


    cout<<"����������������������������-��"<<endl;
    cout<<"��1.��������    ��"<<endl;
    cout<<"��2.�������    ��"<<endl;
    cout<<"��3.�޸�����    ��"<<endl;
    cout<<"��4.ɾ������    ��"<<endl;
    cout<<"��5.����ʽ    ��"<<endl;
    cout<<"��0.�˳�        ��"<<endl;
    cout<<"����������������������������-��"<<endl;
}

    ///��ӭ����
void Hello()
{
    clearscreen();
    cout<<"-----------------------"<<endl;
    cout<<"  ��ӭ�����༶����ϵͳ"<<endl;
    cout<<"-----------------------"<<endl;
    print("-�����������");
    pause(false);
    cout<<endl;
}

    ///��������
void Find()
{
    note item1,item2;
    print("-������Ҫ����ͬѧ��ѧ�Ż�����:");
    string inp;
    cin>>inp;
    item1.strs[0]=inp;
    item2.strs[1]=inp;

    maps(forits,deleitem,true,is_one_left);///��ջ���
    forits = newhead();

    finditems(listhead,forits,item1);
    finditems(listhead,forits,item2);

    if(!len(forits)){
        print("-δ������Ŀ�����ݣ�");
    }
    else{
        print("-����������£�");
        TextLine();
        PrintList(forits);
    }
    pause();

    maps(forits,deleitem,true,is_one_left);///��ջ���
    forits = newhead();
}

    ///ɾ������
void Dele()
{
    string inp;
    print("-������Ҫɾ����ͬѧ��ѧ��(������,����*����):");

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
            print("ѧ��������");
        }
        else{
            deleitem(p);
            print("ɾ���ɹ���");
            sum++;
        }

    }
    print("-����ɾ���ɹ�!�ɹ�ɾ��",' ');
    cout<<sum;
    print("������");
    pause();
}

    ///��ӽ���
void Add()
{
    print("-����һ������������ ѧ�� ���� ���� ���� ���� ��ɢ ˼��");
    print("-ÿ������һ��ͬѧ������ * ����:");
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

        additem(listhead,item);///����������ӽڵ�
        sum++;
    }

    print("-��������ɹ�!������",' ');
    cout<<sum;
    print("������");
    pause();
}

    ///�޸Ľ���
void Change()
{
    string inp;
    print("-������Ҫ�޸ĵ�ͬѧ��ѧ��:");
    cin>>inp;
    note item;item.strs[0]=inp;
    note *p = finditem(listhead,item);  ///��������Ѱ�ҽڵ�
    if(p!=NULL){
    print("-Ŀ��ѧ����������");
    print("-���Ӧ��ʽ���������ѧ������");
    print("-���� - ��λ���޸Ķ�:");
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
    print("-�޸ĳɹ���");
    }
    else{
        print("-δ�ҵ�Ŀ�����ݣ�");
    }
    pause();
}

    ///���ѧ�����а�
void PrintStus()
{
    clearscreen();
    TextLine();
    PrintList(listhead);
}

    ///�ı��������
void Changesort()
{
    int bottonnum_1=3,bottonnum_2=5;
    clearscreen();
    cout<<"------�л�����ʽ------"<<endl;
    cout<<"     1.���ܷ�����Ĭ�ϣ�"<<endl;
    cout<<"     2.��ѧ������"<<endl;
    cout<<"     3.����������"<<endl;
    print("-����������ʽ��ţ�");

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
        cout<<"1.���� 2.���� 3.���� 4.��ɢ 5.˼��"<<endl;
        print("-�������������õĵ�����ţ�");
        do{
        getline(cin,inp);
        b=inp[0]-'0';
        if(0<=b&&b<=bottonnum_2)
            break;
        }while(true);

        SortMODE = b+1;
    }
    print("-�޸ĳɹ���");
    pause();

}


///--�Զ�����������ʽ--//

bool cmp_all(note *a,note *b)       //�ܷ�
{
    return a->nums[0]>b->nums[0];
}

bool cmp_stunum(note *a,note *b)    //ѧ��
{
    return a->strs[0] < a->strs[0];
}

bool cmp_sco1(note *a,note *b)      //����1
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

    ///������ʹ��Sm��ʽ����
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



///--����ͬ��--//
#define datefile "date.dat"

    ///�����ݿ���ͬ������
void structin()
{
    ifstream datf(datefile,ios::in);

    string inp;
    while(datf>>inp){       ///����datf������

        note item;
        item.strs[0]=inp;
        datf>>item.strs[1];
        item.input_scores(5,datf);

        additem(listhead,item);
    }
    datf.close();
}

    ///�����ݿ��������
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

    Hello();                        ///@Hello ���ػ�ӭ����
    structin();                     ///@structin ��������
    string inp;
    while(true){
        Sort(listhead,SortMODE);    ///@Sort ������
        PrintStus();                ///@PrintStus ���ѧ����Ϣ
        Menu();                     ///@Menu ���ز˵�����
        print("-�����������");
        int b;
        do{
            getline(cin,inp);
            b=inp[0]-'0';
            if(0<=b&&b<=bottonnum)
                break;
        }while(true);

        switch(b){
        case 0:
            exit(0);                ///@exit �˳�
        case 1:
            Find();break;           ///@Find ����
        case 2:
            Add();break;            ///@Add ���
        case 3:
            Change();break;         ///@Change �޸�
        case 4:
            Dele();break;           ///@Dele ɾ��
        case 5:
            Changesort();break;     ///@Changesort �޸�����ʽ
        }
        structout();                ///@structout ͬ������
    }
    return 0;
}
