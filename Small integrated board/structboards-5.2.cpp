
#include <bits/stdc++.h>
#define f(k) for(int i=0;i<k;i++)
#define fr(i,k) for(int i=0;i<k;i++)
#define frr(i,k,n) for(int i=k;i<n;i++)
//#define fr0inp() for(;tail<n;tail++)


using namespace std;

void exit_sl(int a){
    system("pause>nul");
    exit(a);
}


class note
{

public:

    vector<string>strs; ///字符串组
    vector<double>nums; ///数组
    double allin; ///数组和

    note(){allin=0;}
    ~note(){strs.clear();nums.clear();}

///----输入----///
    void plinput(int a[],int l){///批量格式输入
                                ///负数为字符串个数，正数为数字
                                ///a[] 格式 ，L 总长度
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
            strs.push_back(s);
        }
    }

    void input_int(int a){ ///输入a个数字
        fr(i,a){
            int n;
            cin>>n;
            nums.push_back(n);
            allin+=n;
        }
    }

    ///尾部添加项目
    void additem(double a){
        nums.push_back(a);
        allin+=a;
    }
    void additem(int a){
        nums.push_back(a);
        allin+=a;
        //cout<<nums[nums.size()-1]<<endl;
    }
    void additem(string a){
        strs.push_back(a);
    }


///---输出---///
    void ploutput(int a[],int l,char c=' ',bool ishuanh = true){
                                        ///批量混合输出字符串和数字，按顺序读取
                                        ///负数为字符串个数，正数为数字
                                        ///a[] 格式 ，L 总长度
        int i=0,outnum=0;               ///要求abs(ai)求和等于L
        int stri=0,numi=0;
        while(outnum<l){
           // cout<<a[i]<<endl;
            if(a[i]<0){
                if(stri<0||stri+abs(a[i])>strs.size()){
                    cout<<"ploutput(strs):操作越界"<<endl;
                    cout<<"  outnum:"<<outnum<<' '<<"l:"<<l<<endl;
                    cout<<"  i:"<<i-1<<' '<<"a[i]:"<<a[i-1]<<endl;
                    exit_sl(1);
                }
                output_strs(stri,stri+abs(a[i]),c,false);
                stri+=abs(a[i]);
                outnum+=abs(a[i]);i++;
                if(outnum>l){
                    cout<<"poutnput:格式控制与总输入和不符合！"<<endl;
                    cout<<"  outnum:"<<outnum<<' '<<"l:"<<l<<endl;
                    cout<<"  i:"<<i-1<<' '<<"a[i]:"<<a[i-1]<<endl;
                    exit_sl(1);
                }
            }
            else if(a[i]>0){
                if(numi<0||numi+abs(a[i])>strs.size()){
                    cout<<"ploutput(nums):操作越界"<<endl;
                    cout<<"  outnum:"<<outnum<<' '<<"l:"<<l<<endl;
                    cout<<"  i:"<<i-1<<' '<<"a[i]:"<<a[i-1]<<endl;
                    exit_sl(1);
                }
                output_nums(numi,abs(a[i]),c,false);
                numi+=abs(a[i]);
                outnum+=abs(a[i]);i++;
                if(outnum>l){
                    cout<<"ploutput:格式控制与总输入和不符合！"<<endl;
                    cout<<"  outnum:"<<outnum<<' '<<"l:"<<l<<endl;
                    cout<<"  i:"<<i-1<<' '<<"a[i]:"<<a[i-1]<<endl;
                    exit_sl(1);
                }
            }
            else{
                cout<<"ploutput:输出格式控制有误，不可以有0！"<<endl;
                exit_sl(1);
            }
        }
        if(ishuanh==true&&c!='\n')
            cout<<endl;
    }

    void output_strs(int a,int b,char c=' ',bool ishuanh=true){ ///输出多个字符串,c为间隔字符
        if(a<0||b>strs.size()){                                  ///ishuanh为是否换行
            cout<<"output_strs:操作越界"<<endl;
            exit_sl(1);
        }
        frr(i,a,b){
            cout<<strs[i];
            //if(i!=b-1)
                cout<<c;
        }
        if(ishuanh==true&&c!='\n')
            cout<<endl;
    }

    void output_nums(int a,int b,char c=' ',bool ishuanh=true){ ///输出多个数字
        if(a<0||b>nums.size()){
            cout<<"output_nums:操作越界"<<endl;
            exit_sl(1);
        }
        frr(i,a,b){
            cout<<nums[i];
            //if(i!=b-1)
                cout<<c;
        }
        if(ishuanh==true&&c!='\n')
            cout<<endl;
    }

///---功能函数---///

    double ever_average(){ ///求平均值
        return allin/nums.size();
    }
    ///计数
    int counti(string s,bool isbf = false) ///isal为是否部分拥有符合
    {
        if(isbf==false){
            int l = strs.size();
            int ans=0;
            fr(i,l)
                if(s==strs[i])
                    ans++;
            return ans;
        }

        else{
            int l = strs.size();
            int ans = 0;
            fr(i,l){
                int p = strs[i].find(s);
                if(p!=string::npos)
                    ans++;
            }
            return ans;
        }
    }

    int counti(double s)
    {
        int l = nums.size();
        int ans=0;
        fr(i,l)
            if(s==nums[i])
                ans++;
        return ans;
    }

    int counti(int s)
    {
        int l = nums.size();
        int ans=0;
        fr(i,l)
            if(s==nums[i])
                ans++;
        return ans;
    }

    ///指定查找替换
    void strtihuan(string s,string f,int i) ///h为替换字符串的下标 替换目标字符串中所有符合的子字符串
    {
        if(s.length()!=f.length())
        {
            cout<<"strtihuan:替换字符长度不符！"<<endl;
            exit_sl(1);
        }
        int fl = f.length();

        while(true)
        {
            int p = strs[i].find(s);
            if(p!=string::npos)
            {
                frr(j,p,p+fl)
                    strs[i][j] = f[j-p];
            }
            else break;
        }

    }
    void strtihuanall(string s,string f,bool isbf = true) ///isal为是否替换子字符串
    {
        if(s.length()!=f.length())
        {
            cout<<"strtihuan:替换字符长度不符！"<<endl;
            exit_sl(1);
        }

        if(isbf==false)
        {
            int l = strs.size();
            fr(i,l)
            if(s==strs[i])
                strs[i] = f;
        }

        else
        {
            int l = strs.size();
            int fl = f.length();
            fr(i,l)
            {
                while(true)
                {
                    int p = strs[i].find("s");
                    if(p!=string::npos)
                    {
                        frr(j,p,p+fl)
                        strs[i][j] = f[j-p];
                    }
                    else break;
                }
            }
        }
    }



}notes[1000005];

int tail=0;///尾部坐标

///-----功能性函数和重载运算符----///
bool operator == (string a,string b)
{
    int la=a.length(),lb=b.length();
    if(la!=lb)
        return false;
    fr(i,la){
        if(a[i]!=b[i])
            return false;
    }
    return true;
}


///-----查找拥有指定元素的结构体------///

int searchin(int s)///查找含有s（只要有str[i]==s就可以）的notes，如果没有则返回-1
{
    int p=0;
    while(!(notes[p].nums.empty()&&notes[p].strs.empty())){
        int l = notes[p].nums.size();
        fr(j,l){
            if(notes[p].nums[j]==s)
                return p;
        }
        p++;
    }
    return -1;
}
int searchin(int s,int i)///要求必须第i位为s
{
    int p=0;
    while(!(notes[p].nums.empty()&&notes[p].strs.empty())){
        if(i<notes[p].nums.size()&&notes[p].nums[i]==s)
            return p;
        p++;
    }
    return -1;
}
int searchin(string s)
{
    int p=0;
    while(!(notes[p].nums.empty()&&notes[p].strs.empty())){
        int l = notes[p].strs.size();
        fr(j,l){
            if(notes[p].strs[j]==s)
                return p;
        }
        p++;
    }
    return -1;
}
int searchin(string s,int i)
{
    int p=0;
    while(!(notes[p].nums.empty()&&notes[p].strs.empty())){
        if(i<notes[p].strs.size()&&notes[p].strs[i]==s)
            return p;
        p++;
    }
    return -1;
}

///-----结构体求和--------///

double sumat(int i,int j,int xiang)///求notes[i]到notes[j-1]某项和
{
    if(i<0||j>=tail){
        cout<<"sumat:求和函数越界！"<<endl;
        exit_sl(0);
    }
    double sum = 0;
    frr(h,i,j){
        sum+=notes[h].nums[xiang];
    }
    return sum;
}

double sumat(int i,int j)///求notes[i]到notes[j]的和的和
{
    if(i<0||j>=tail){
        cout<<"sumat:求和函数越界！"<<endl;
        exit_sl(0);
    }
    double sum=0;
    frr(h,i,j){
        sum+=notes[h].allin;
    }
    return sum;
}



///-----排序规则----///

bool cmp_all(note a,note b) ///合值大靠前
{
    return a.allin>b.allin;
}

bool cmp_aver(note a,note b) ///平均值大靠前
{
    double ava=a.ever_average();
    double avb=b.ever_average();
    return ava>avb;
}

bool cmp_ooo(note a,note b) ///自定义排序
{
    return a.nums[2]<b.nums[2];
}

bool cmp_sss(note a,note b)
{
    string s[4]={"A","B","C","D"};
    fr(i,4)
        if(a.counti(s[i])!=b.counti(s[i]))
            return a.counti(s[i])>b.counti(s[i]);
}


#define hasnum false ///是否有个数输入
#define defulanum 1000 ///如果没有个数输入的话，默认输入
#define precision 0 ///输出小数点后几位
int main()
{

    cin.tie(0);
    ios::sync_with_stdio(false);
    cout<<setiosflags(ios::fixed)<<setprecision(precision);

    int n;
    if(hasnum)  cin>>n;///输入输入条目个数
    else n=defulanum;

///----代码区 ↓ 不支持使用C输入函数
    ///tail为末尾坐标，不要新定义
    ///在改变数组大小的时候一定要改变tail值

    int a[] = {-1,1,-1};
    notes[0].plinput(a,3);
    notes[0].ploutput(a,3,'\n');
    notes[0].nums[0]++;
    notes[0].ploutput(a,3);

///----代码区 ↑

    return 0;
}
