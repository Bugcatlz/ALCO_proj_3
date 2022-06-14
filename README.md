# ALCO_proj_3
 
## 前提
1. fetch 為一個cycle
2. execute add為 5 cycle mul為 19 cycle
3. write 為一個cycle
4. 若是有WAW WAR 的dependency 需要等在write的下一個cycle才可以取得最新的值
5. RS 需要再instruction結束後的下一個cycle才會釋放出空間
6. register的初值分別為 0、2、4、6、8

## Input
```
ADDI F1, F2, 1
SUB F1, F3, F4
DIV F1, F2, F3
MUL F2, F3, F4
ADD F2, F4, F2
ADDI F4, F1, 2
MUL F5, F5, F5
ADD F1, F4, F4
```
並放入到Input.txt中

## 程式碼解釋
--- 
## Global Variable

### A. 相關參數
```
int numAddRS = 3;
int numMulRS = 2;
int addCycle = 5;
int mulCycle = 19;
```
分別為ADD和mul Reservation Station的個數和一個instruction所需的cycle

ADD 的RS大小為3且需要一個instruction需要5個cycle

ADD 的RS大小為19且需要一個instruction需要5個cycle

### B. registers
```
Register* registers[6];
```
為六個pointer指向Register的陣列分別對應R1~R6

## Instruction

### A. Instruction
--- 
### Private:

### 1. myRegIndex
```c++
vector <int> myRegIndex
```
用來存放所屬的register的index
ex: `ADDI F1, F2, 1`
則會存放1、2

### 2. myReg
```c++
vector < Register* > myReg
```
用來存放這個Instruction所使用到的Register

### 3. myOperator
```c++
string myOperator
```
用來存放這個Instruction的operator

### 4. myImmediate
```c++
int myImmediate
```
用來存放這個Instruction中immediate的值

### Public
### 1. Constructor

```c
Instruction()
	{}
```
為預設的constructor

```c++
Instruction(string myOperator, int reg1, int reg2, int reg3)
		:myOperator(myOperator)
{
    myRegIndex.push_back(reg1);
    myRegIndex.push_back(reg2);
    myRegIndex.push_back(reg3);
}
```
為用來建構一個Instruction包含三個Register的Constructor

Ex: `SUB F1, F3, F4`

```C++
Instruction(string myOperator, int reg1, int reg2, string imm)
    :myOperator(myOperator),
    myImmediate(stoi(imm))
{
    myRegIndex.push_back(reg1);
    myRegIndex.push_back(reg2);
}
```
為用來建構一個Instruction包含二個Register和一個Immediate的Constructor

Ex: `ADDI F1, F2, 1`

#### 2. getAddress
```C++
int getAddress()
{
	return myAddress;
}
```
回傳這個Instruction的address

### 3. exection
```c++
void exection()
{
    if (myOperator == "ADD")
    {
        *myReg[0] = *myReg[1] + *myReg[2];
    }
    else if (myOperator == "ADDI")
    {
        *myReg[0] = *myReg[1] + myImmediate;
    }
    else if (myOperator == "DIV")
    {
        *myReg[0] = *myReg[1] / *myReg[2];
    }
    else if (myOperator == "MUL")
    {
        *myReg[0] = *myReg[1] * *myReg[2];
    }
    Register* r = getOutputRegister();
    r->getName().clear();
}
```
判斷當myOperator為特定的Operator時，

執行相對應的運算，並將output的register的renaming清除，

且執行完後呼叫clear，來清除

### 4. getLabel
```c++
string getLabel()
	{
		return myLabel;
	}
```
回傳myLabel
