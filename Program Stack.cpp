#include<iostream>
#include<conio.h>
#include<string>
#include<math.h>
#include<sstream>
#include<cstdlib>

using namespace std;

const int max_stack=40;
struct type_stack{
int top;
string data[max_stack];
};
    type_stack stack; 
    void init(type_stack &namastack){
         namastack.top = -1;
    }
    bool isFull(type_stack namastack, int max_stack){
    if(namastack.top == (max_stack-1))
          return true;
    else
          return false;
        }
    bool isEmpty(type_stack namastack){
    if(namastack.top == -1)
        return true;
    else
        return false;
    }
    void Push(type_stack &namastack, string data){
        namastack.top++;
        namastack.data[namastack.top]=data;
    }
    void Pop(type_stack &namastack){
        namastack.top--;
        }
    void CetakStack_LIFO(type_stack namastack){
        cout << "Data Stack (LIFO) : \n";
        for(int i=namastack.top; i>=0; i--){
        cout<<" "<<namastack.data[i]<<"\n";
        }
    }
    void inputElemen(type_stack &namastack){
        cout<<" Masukkan \n";
        cout<<"tekan enter setelah selesai menginputkan 1 element,  \n"<<
          "sampai menginputkan '=' \n";
        string dataElemen;
        dataElemen="";
        int elm=0; 
        while(dataElemen != "=") 
        {
            elm++;
            cout<<"elemen ke "<<elm<< " : ";
            cin>>dataElemen;
            if(dataElemen!="=") 
            Push(namastack,dataElemen); 
        }
    }
    bool isOpr(string opr)
    {
        if((opr=="*") || (opr=="/")||(opr=="%")||(opr=="+") || (opr=="-")||(opr=="^"))
        {
            return true;
        }
            else
            return false;
        }
        int presedence(string opr)
        {
        if((opr=="^")||(opr=="!"))
            return 4;
        else if((opr=="*") || (opr=="/")||(opr=="%"))
            return 3;
        else if((opr=="+") || (opr=="-"))
            return 2;
        else
            return 1;
        }
    void infixToPostfix(type_stack &infix, type_stack &postfix){
         string symbol;
         string topSymbolOpr;
         type_stack stackOperator;
         init(stackOperator);
         for(int k=0; k<=infix.top; k++)
         {
            symbol=infix.data[k];
            if((!isOpr(symbol)) && (symbol!="(") && (symbol!=")") ) //jika bukan operator, berarti symbol atau angka
            {
                Push(postfix,symbol);
            }
            else if(isOpr(symbol))
            {
                while((!isEmpty(stackOperator)) && (stackOperator.data[stackOperator.top]!="("))
                {
                    topSymbolOpr=stackOperator.data[stackOperator.top];
                    if(presedence(topSymbolOpr)>=presedence(symbol))
                    {
                        Pop(stackOperator);
                        Push(postfix,topSymbolOpr);
                    }
                    else
                        break;
                    }
                        Push(stackOperator,symbol);
            }
            else if(symbol=="(")
            {
                Push(stackOperator,symbol);
            }
            else if(symbol==")")
            {
                while((!isEmpty(stackOperator)) && (stackOperator.data[stackOperator.top]!="("))
            {
                topSymbolOpr=stackOperator.data[stackOperator.top];
                if(presedence(topSymbolOpr)>=presedence(symbol))
            {
                Pop(stackOperator);
                Push(postfix,topSymbolOpr);
            }
            else
                Push(stackOperator,symbol);
            }
            if(stackOperator.data[stackOperator.top]=="(")
                Pop(stackOperator);
            else
                cout<<"kurung '(' tidak ditemukan";
        }
        }
        while(!isEmpty(stackOperator))
        {
            topSymbolOpr=stackOperator.data[stackOperator.top];
            Pop(stackOperator);
            Push(postfix,topSymbolOpr);
        }
    }
    double hitungMat(double operand1, string opr, double operand2)
    {
    if(opr=="+")
        return (operand1 + operand2);
    else if(opr=="-")
        return (operand1 - operand2);
    else if(opr=="*")
        return (operand1 * operand2);
    else if(opr=="/")
        return (operand1 / operand2);
    else if(opr=="")
        return (double)((int)operand1 % (int)operand2);
    else if(opr=="^")
        return (pow(operand1,operand2));
    else
        return 0;
    }
    double strToDouble(string strangka)
    {
        std::istringstream stm;
        stm.str(strangka);
        double d;
        stm >>d;
        return (d);
    }
    string doubleToStr(double angka)
    {
        ostringstream ss;
        ss << angka;
        return (ss.str());
    }
    string ekskusiPostfix(type_stack &namastackPostfix)
    {
        type_stack stackHasil;
        init(stackHasil);
        string symbol;
        double operand1, operand2;
        for(int i=0; i<=namastackPostfix.top; i++)
        {
            symbol=namastackPostfix.data[i];
            if(!isOpr(symbol))
            {
                Push(stackHasil,symbol);
            }
            else if(isOpr(symbol))
            {
                operand2=strToDouble(stackHasil.data[stackHasil.top]);
                Pop(stackHasil);
                operand1=strToDouble(stackHasil.data[stackHasil.top]);
                Pop(stackHasil);
                double hasilHitungan;
                hasilHitungan=hitungMat(operand1,symbol,operand2);
                Push(stackHasil,doubleToStr(hasilHitungan));
            }
        }
        return stackHasil.data[stackHasil.top];
    }
int main(){
    type_stack stackInfix;
    type_stack stackPostfix;
    do
        {
        Menu :
          int menu;
          cout<< "             Menu Stack" << endl;
          cout<< endl;
          cout<< "1. Push "<<endl;
          cout<< "2. Pop "<<endl;
          cout<< "3. Baca "<<endl;
          cout<< "4. Selesai "<<endl;
          cout<< endl;
          cout<< "Masukkan Pilihan Anda : ";
          cin>>menu;
          switch(menu)
          {
          case 1:
           init(stackInfix);
           if(!isFull(stackInfix,max_stack))
           {
            inputElemen(stackInfix);
            cout<<endl;
            cout<<"expresi infix yang anda masukkan : ";
            cout<<"    "; for(int i=0; i <=stackInfix.top; i++){cout<<stackInfix.data[i];  }
            cout<<endl;
            cout<<endl;
           }
           else
           {
            cout<<"Maaf, Stack Telah Penuh..!";
           }
           cout<<endl;
           break;
          case 2:
           init(stackPostfix);
           infixToPostfix(stackInfix,stackPostfix);
           cout<<endl;
           cout<<"expresi Postfix  : ";
           cout<<"    "; for(int i=0; i <=stackPostfix.top; i++){cout<<stackPostfix.data[i];  }
           cout<<endl;
           cout<<endl;
           break;
          case 3:
           cout<<endl;
           cout<<"hasil Perhitungan expresi "; for(int i=0; i <=stackPostfix.top; i++){cout<<stackPostfix.data[i];  }
           cout<<"\nadalah :     "<<ekskusiPostfix(stackPostfix)<< endl<<endl;
           break;
          case 4:
           exit(0);
           break;
          default:
           cout <<"\n Input Menu Salah...!!!";
           cout<<"\n Press Any key to return to menu ";
           _getch();
           system("cls");
           goto Menu;
          }
         }while(1);
        }
