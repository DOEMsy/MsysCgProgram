#include <bits/stdc++.h>
#define fr(i,k) for(int i=0;i<k;i++)
#define frr(i,k,n) for(int i=k;i<n;i++)
//#define fr0inp() for(;tail<n;tail++)


using namespace std;

///---������������---///

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

    ///----����----///
    void plinput(int a[],int l){///������ʽ����
        string inp0;            ///����Ϊ�ַ�������������Ϊ����
        double inp1;            ///a[] ��ʽ ��L �ܳ���
        int i=0,inpnum=0;       ///Ҫ��abs(ai)��͵���L
        while(inpnum<l){
           // cout<<a[i]<<endl;
            if(a[i]<0){
                input_str(abs(a[i]));
                inpnum+=abs(a[i]);i++;
                if(inpnum>l){
                    cout<<"plinput:��ʽ������������Ͳ����ϣ�"<<endl;
                    cout<<"  inpnum:"<<inpnum<<' '<<"l:"<<l<<endl;
                    cout<<"  i:"<<i-1<<' '<<"a[i]:"<<a[i-1]<<endl;
                    exit_sl(1);
                }
            }
            else if(a[i]>0){
                input_int(a[i]);
                inpnum+=abs(a[i]);i++;
                if(inpnum>l){
                    cout<<"plinput:��ʽ������������Ͳ����ϣ�"<<endl;
                    cout<<"  inpnum:"<<inpnum<<' '<<"l:"<<l<<endl;
                    cout<<"  i:"<<i-1<<' '<<"a[i]:"<<a[i-1]<<endl;
                    exit_sl(1);
                }
            }
            else{
                cout<<"plinput:�����ʽ�������󣬲�������0��"<<endl;
                exit_sl(1);
            }
        }
    }

    void input_str(int a){ ///����a�ַ���
        fr(i,a){
            string s;
            cin>>s;
            str.push_back(s);
        }
    }

    void input_int(int a){ ///����a������
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
            cout<<"output_str:��������ַ����׶δ���β��"<<endl;
            exit_sl(0);
        }
        if(e>str.size()){
            cout<<"output_str:����β��Խ��"<<endl;
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
int counti(note *,note);///ͳ������ֵ��ȫ��ͬ�ĸ���
note *hishead(note *); ///�ҵ��ýڵ��ͷ�ڵ�


note *newhead() ///������ͷ
{
    note *nhead = new note;
    nhead->next = nhead;  ///��ͷ �Գɻ�
    nhead->last = nhead;
    nhead->ishead = true;
    nhead->len = 0;
    return nhead;
}

int counti(note *head,note item)///ͳ������ֵ��ȫ��ͬ�ĸ���
{
    if(head->ishead==false){
        cout<<"findin:�����������õ��������㲻��ͷ���"<<endl;
        exit_sl(0);
    }

    int s = 0;
    note *p = head->next;                       ///����������򷵻�ͷ�ڵ�
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

void movenote(note *a,note *b)///��a�ƶ���b��ǰ��
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
void swapnote(note *a,note *b)
{
    if(a->ishead==true||b->ishead==true){
        cout<<"swapnote:�����滻�Ľڵ���ͷ���"<<endl;
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

void additem(note *position,note iteml) ///��λ��ǰ���������
{
                                                ///ѭ������head->last ��β��
    note *item = new note(iteml);

    item->next=position;
    position->last->next = item;
    item->last = position->last;
    position->last = item;
    hishead(position)->len++;
}

void deleitem(note *position) ///ɾ��Ŀ��λ�õ�����
{
    if(position->ishead==true){
        cout<<"deleitem:����ɾ��ͷ�ڵ㲻�Ϸ�"<<endl;
        exit_sl(0);
    }

    position->last->next = position->next;
    position->next->last = position->last;
    delete position;
}

///----��������--------///

note *findin(note *head,int num,int ati=0) ///��Ŀ�������в��ҵ�һ��ati�±�ӵ��Ŀ��ֵ�Ľڵ�ĵ�ַ
{
    if(head->ishead==false){
        cout<<"findin:�����������õ��������㲻��ͷ���"<<endl;
        exit_sl(0);
    }

    note *p = head->next;                       ///����������򷵻�ͷ�ڵ�
    while(p!=head){
        if(p->num.size()>ati&&p->num[ati]==num)
            break;
        p = p->next;
    }
    return p;
}

note *findin(note *head,double num,int ati=0) ///��Ŀ�������в��ҵ�һ��ati�±�ӵ��Ŀ��ֵ�Ľڵ�ĵ�ַ
{
    if(head->ishead==false){
        cout<<"findin:�����������õ��������㲻��ͷ���"<<endl;
        exit_sl(0);
    }

    note *p = head->next;                       ///����������򷵻�ͷ�ڵ�
    while(p!=head){
        if(p->num.size()>ati&&p->num[ati]==num)
            break;
        p = p->next;
    }
    return p;
}

note *findin(note *head,string str,int ati=0) ///��Ŀ�������в��ҵ�һ��ati�±�ӵ��Ŀ��ֵ�Ľڵ�ĵ�ַ
{
    if(head->ishead==false){
        cout<<"findin:�����������õ��������㲻��ͷ���"<<endl;
        exit_sl(0);
    }

    note *p = head->next;                       ///����������򷵻�ͷ�ڵ�
    while(p!=head){
        if(p->str.size()>ati&&p->str[ati]==str)
            break;
        p = p->next;
    }
    return p;
}

note *atitem(note *head,int n)///���ҵ�nλѧ����ѭ����
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

note *hishead(note* p) ///����p��ͷ�ڵ�
{
    note *h = p;
    while(h->ishead==false){
        h = h->next;
    }
    return h;
}


///----����----///
///�Զ���������

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
        cout<<"sort_list:�����������õ��������㲻��ͷ���"<<endl;
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








///----��������----///

void print_num_0(note *);
void print_str_0(note *);
void print_str_len(note *);
bool is_once_cycle(note *,note *);
void deletenumber_m(note *item);

void maps( note *position,void (*mapfunction)(note*),bool Zheng = true,bool (*iffunction)(note*,note*) = is_once_cycle)
{                                                     ///��ʼλ��,������������ֹ����������
    if(Zheng){                                        ///λ�ÿ�ʼ�������������
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
///--�Զ����ѭ����ֹ��������--
bool is_once_cycle(note *begin_position,note *p)///�Ƿ�ΪһȦ����ֻѭ��һȦ��
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

///--�Զ���ɱ������Ĳ���������Ҫ���޷���ֵ��ֻ�в���note*,int��

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

int deletenum_m,deletenum_ml;///ɾ����m��,��������ml
void deletenumber_m(note *item)  ///Լɪ��
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

///--�����޸�-----------------
#define precision 0 ///���С�����λ

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout<<setiosflags(ios::fixed)<<setprecision(precision);

    ///---���벿��-----
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
