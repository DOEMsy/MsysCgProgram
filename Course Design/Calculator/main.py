import  logging
logging.basicConfig(level=logging.INFO)
from re import *
from math import *
from os import *
import time


def pause(text="按任意键继续",sleeptime=0):
    print(text)
    if sleeptime==0:
        system("pause>nul")
    else:
        time.sleep(sleeptime)

##判断字符串是否为小数
def isnumber(num):
    regex = compile(r"^(-?\d+)(\.\d*)?$")
    if match(regex,num):
        return True
    else:
        return False

##判断是否是数字
def isnum(num):
    if isnumber(num):
        return True
    elif match(compile(r"^-?\d+$"),num):
        return True
    else:
        return False

##判断是否是整数
def isint(num):
    if match(compile(r"^-?\d+$"),num):
        return True
    else:
        return False

def iscomhow(stris):
    lis = stris.split()
    if len(lis)==3: #进制转换

        for l in lis:
            if not isnum(l):
                return 0
            
        
        if lis[0] in ['2','8','10','16'] and lis[2] in ['2','8','10','16'] and isint(lis[1]):
            return 3
        else:
            return 0
    
    elif len(lis)==2: #三角函数
        if  lis[0]  in  ['tan','cos','sin','arctan','arcsin','arccos'] and isnum(lis[1]):
            if lis[0] in ['arcsin','arccos'] and not -1.0<=float(lis[1])<=1.0:
                return 0
            return 2
        else:
            return 0
    
    else:
        return 1
            


#自定义栈
class PyStack(object):

    def __init__(self,initSize=20,incSize=10):
        self.initSize=incSize
        self.incSize=incSize
        self.stackList=[]
        self.top=self.bottom=0

    def push(self,ele):
        if self.top-self.bottom>=self.initSize:
            self.incSize+=self.initSize
        self.stackList.append(ele)
        self.top+=1

    def pop(self):
        if self.top-self.bottom>0:
            self.top-=1
            ret=self.stackList.pop()
            return ret
        else:
            return None

    def len(self):
        return  self.top-self.bottom


class History(object):
    def __init__(self):
        self.lis_inp = []
        self.lis_oup = []
    
    def display(self):
        l = len(self.lis_oup)
        if l==0:
            print("无历史计算：-----------------")
        else:
            print("历史计算：-------------------")
            i = 0
            while i<l:
                print("          "+str(i+1)+"_  {"+str(self.lis_inp[i])+'}='+str(self.lis_oup[i]))
                i+=1
            print(" ")
    
    def clear(self):
        self.lis_inp=[]
        self.lis_oup=[]
    
    def push(self,inp,oup):
        self.lis_inp.append(inp)
        self.lis_oup.append(oup)

history = History()





class Comp(object):     

    def __init__(self):
        tempnum = '100551'
    
    
    def com1(self,stris):   #计算计算式
        #stris = input("  -请输入基础计算式（在负数前请加0）：")
        eList=self.equation2List(stris)
        midEList=self.mid2EndSuffix(eList)
        logging.info(midEList)
        lastResult=self.calEndSuffixResult(midEList)
        print("运算结果为："+str(lastResult))
        history.push(inp=stris,oup=lastResult)
        

    
    def com2(self,stris):   #计算三角函数
        #stris = input("  -请输入计算的三角函数 fun x 形式（三角函数中x为角度，arc中x为数字）：")
        fun,x = stris.split()
        x = float(x)
        if fun == "tan":
            result = tan(x/180*pi)+0.0000000000000001
        elif fun == "sin":
            result = sin(x/180*pi)+0.0000000000000001
        elif fun == "cos":
            result = cos(x/180*pi)+0.0000000000000001
        elif fun == "arccos":
            result = acos(x)
        elif fun == "arctan":
            result = atan(x)
        elif fun == "arcsin":
            result = asin(x)
        print("运行结果为："+str(result))
        history.push(inp=stris,oup=result)



    def com3(self,stris):   #进制转换
        #stris = input("  -请依次输入当前进制，数字，目标进制(支持2,8,10,16)：")
        a,x,b = stris.split()
        a = int(a)
        b = int(b)
        num = int(x,a)
        if b==2:
            result = bin(num)
        elif b==8:
            result = oct(num)
        elif b==10:
            result = num
        elif b==16:
            result = hex(num)
        print("运行结果为："+str(result))
        history.push(inp=stris,oup=result)


    ##算式转化为中缀表达式列表
    def equation2List(self,equation):    
        result=[]
        buffNum=[]
        for i in equation:
            if i.isdigit() or i=='.':
                buffNum.append(i)
            else:
                if len(buffNum)>0:
                    result.append("".join(buffNum))
                    buffNum.clear()
                result.append(i)
        if len(buffNum)>0:
            result.append("".join(buffNum))
            buffNum.clear()
        logging.info(result)
        return result

    ##中缀表达式转后缀表达式
    ## 1+2*(3+4)=15
    ##1 2 3 4 + * +
    def mid2EndSuffix(self,list):
        resultList=[]
        stack=PyStack()
        for i in list:
            if isnumber(i):
                resultList.append(i)
            elif ')' == i:
                while stack.len()>0:
                    item=stack.pop()
                    logging.debug(")pop==%s"%(item))
                    if '('==item:
                        break
                    else:
                        resultList.append(item)
            elif '+' == i or '-' == i:
                if stack.len() == 0:
                    stack.push(i)
                    logging.debug("+-None=push==%s"%i)
                else:
                    while stack.len()>0:
                        item2=stack.pop()
                        logging.debug("+-=pop==%s"%item2)
                        if '(' == item2:
                            stack.push(item2)
                            logging.debug("+-=(push==%s"%item2)
                            break
                        else:
                            resultList.append(item2)
                    stack.push(i)
                    logging.debug("+-lastpush==%s"%i)
            elif '*' == i or '/' == i or '(' == i:
                stack.push(i)
                logging.debug("*/(push==%s"%i)
            else:
                print("输入格式有误")
        while stack.len()>0:
            item3=stack.pop()
            logging.debug("last==pop=%s"%item3)
            resultList.append(item3)
        return  resultList

    ##后缀表达式计算结果
    def   calEndSuffixResult(self,list):
        stack=PyStack()
        sumEnd=0
        if len(list)==0:
            return sumEnd
        for i  in list:
            if isnumber(i):
                stack.push(float(i))
            elif '+'==i:
                a=stack.pop()
                b=stack.pop()
                stack.push(b+a)
            elif '-'==i:
                a = stack.pop()
                b = stack.pop()
                stack.push(b - a)
            elif '*'==i:
                a = stack.pop()
                b = stack.pop()
                stack.push(b * a)
            elif '/'==i:
                a = stack.pop()
                b = stack.pop()
                if a==0:
                    print('%d/%d分子不能为0'%(b,a))
                else:
                    stack.push(b/a)
        return stack.pop()

comption = Comp()

while True:
    system("cls")
    history.display()
    #print("   1, +-*/ 简单计算式")
    #print("   2, 三角函数")
    #print("   3, 进制转换")
    #print("   0, 退出")
    #h = int(input("请选择计算方式："))
    
    print("计算器输入规则：")
    print(" -支持基础计算式（+-*/），在负数前请加数字补位，如0-1")
    print(" -支持三角函数计算,输入形式 fun x")
    print(" -支持进制转换，按格式 原进制 数字 目标进制 输入，只支持整数以及（2,8,10,16）进制")
    print("\n请输入：")
    stris = input()

    ###通过对stris正则表达式判断，得到h值#
    h = iscomhow(stris)
    
    if h==1:
        comption.com1(stris)
    elif h==2:
        comption.com2(stris)
    elif h==3:
        comption.com3(stris)
    elif h==0:
        print("算式错误，请重新输入")
        pause()
        continue
    else:
        continue