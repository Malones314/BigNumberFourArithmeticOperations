/**
 *   Function Description：      BigNumberFourArithmeticOperations
 *   Environment：                Code::Blocks 17.12
 *   Author:                          Malones
 *   Date:                             2020.12.13
 */
#include<bits/stdc++.h>
using namespace std;
string number1, number2, resultPlus, resultSubtraction, resultMultiplication, resultDivision;
void sumBigNumber();
void subtractionBigNumber();
void multiplicationBigNumber();
void divisionBigNumber();
int main(){
    cin >> number1 >> number2;
    sumBigNumber();
    subtractionBigNumber();
    multiplicationBigNumber();
    divisionBigNumber();

    cout << number1 << " + " << number2 << " = " << resultPlus << endl;
    cout << number1 << " - " << number2 << " = " << resultSubtraction << endl;
    cout << number1 << " * " << number2 << " = " << resultMultiplication << endl;
    cout << number1 << " / " << number2 << " = " << resultDivision << endl;

    return 0;
}

/** \brief 大数加法
 */

void sumBigNumber(){
    int len1 = number1.length();
    int len2 = number2.length();
    int t = 0;
    int i, j;
    stack<int> sum;
    for( i = len1 - 1, j = len2-1; i > -1 && j > -1 ; i--, j--){
        sum.push( ( number1[i]-'0' + number2[j]-'0' + t )%10);
        t = ( number1[i]-'0' + number2[j]-'0' + t )/10;
    }
    while( i > -1){
        sum.push( ( number1[i] - '0' + t)%10);
        t = ( number1[i] - '0' + t)/10;
        i--;
    }
    while( j > -1){
        sum.push( ( number2[j] - '0' + t)%10);
        t = ( number2[j] - '0' + t)/10;
        j--;
    }
    if( t)
        sum.push(t);
    resultPlus.assign( sum.size(), '0');
    i = 0;
    while(!sum.empty()){
        resultPlus[i] = (sum.top()+'0');
        i++;
        sum.pop();
    }
    for( i = resultPlus.length() - 1, t = 0; i > 0; i--, t++ )
        if( t == 2){
            t = -1;
            resultPlus.insert( i, ",");
        }
}

/** \brief 大数减法
 */

void subtractionBigNumber(){
    int len1 = number1.length();
    int len2 = number2.length();
    string number1_ = number1;
    string number2_ = number2;
    stack<int>subtract;
    int i, j, t = 0;
    bool negative = false;
    if( len1 < len2){
        negative = true;
        string number3;
        number3 = number2_;
        number2_ = number1_;
        number1_ = number3;
    }else if( len1 == len2){
        for( i = 0; i < len1; i++){
            if(number1_[i] < number2_[i]){
                negative = true;
                string number3 = number1_;
                number1_ = number2_;
                number2_ = number3;
                break;
            }else if(number1_[i] == number2_[i])
                continue;
            else
                break;
        }
    }
    for( i = len1-1, j = len2-1; i > -1 && j > -1; i--, j--){
        if(number1_[i] < number2_[j]){
            number1_[i]+=10;
            number1_[i-1]--;
        }
        subtract.push(number1_[i]-number2_[j]);
    }
    while( i < number1_.length()){
        subtract.push( number1_[i]-'0');
        i--;
    }
    while(subtract.top() == 0 && subtract.size()!=1)   //等于1代表减法运算结果为0
        subtract.pop();
    resultSubtraction.assign( subtract.size(), '0');
    for( i = 0; !subtract.empty(); i++, subtract.pop() )
        resultSubtraction[i] = (subtract.top()+'0');
    for( i = resultSubtraction.length() - 1, t = 0; i > 0; i--, t++ )
        if( t == 2){
            t = -1;
            resultSubtraction.insert( i, ",");
        }
    if(negative)
        resultSubtraction.insert(0, "-");
}

/** \brief 大数乘法
 */     

void multiplicationBigNumber() {
    int len1 = number1.length();
    int len2 = number2.length();
    int i, j, t = 0;
    int result[len1+len2+1] = {0};
    int number1_[len1] = {0};
    int number2_[len2] = {0};
    for( j = 0, i = len1-1; i > -1; i--)
        number1_[j++] = number1[i] - '0';
    for( j = 0, i = len2-1; i > -1; i--)
        number2_[j++] = number2[i] - '0';
    for( j = 0; j < len2; j++)   //最后处理进位
        for( i = 0; i < len1; i++)
            result[i+j] += number1_[i] * number2_[j];
    //处理进位问题
    for( i = 0; i < len1 + len2; i++)
        if( result[i] > 9) {
            result[i+1] += result[i]/10;
            result[i]%=10;
        }
    for( i = len1 + len2; result[i] == 0 && i > 0; i-- )   //高位的0舍去, 且满足至少含有一个数字(0)
        resultMultiplication.assign( i, '0');
    for( j = 0; i > -1; i--)
        resultMultiplication[j++] = result[i]+'0';
    for( i = resultMultiplication.length() - 1, t = 0; i > 0; i--, t++ )
        if( t == 2){
            t = -1;
            resultMultiplication.insert( i, ",");
        }
}

/** \brief 两整型数组的减法
 *   \return 相减结果的长度
 */     

int Substract( int *p1, int *p2, int len1, int len2){   
    int i;
    if( len1 < len2)
        return -1;
    if( len1 == len2){
        for( i = len1-1; i >= 0; i--){
            if( p1[i] < p2[i])    //p1<p2
                return -1;
            else if( p1[i] > p2[i]) //p1>p2
                break;
        }
    }
    for( i = 0; i < len1; i++){   //两数相减
        p1[i] -= p2[i];
        if( p1[i] < 0){
            p1[i] += 10;
            p1[ i+1]--;
        }
    }
    for( i = len1-1; i >= 0; --i)
        if( p1[i])    //找到最高位第一个不为0
            return i+1;
    return 0;   //全部为0，说明两者相等
}
 
/** \brief 通过减法得来的大数除法
 */     
 
void divisionBigNumber(){   //无小数部分
    int len1 = number1.length();
    int len2 = number2.length();
    if( number2 == "0") {   //除数为0结果为Error
        resultDivision = "Error";
        return ;
    }
    if( number1 == "0") {  
        resultDivision = "0";
        return ;
    }
    if( len1 < len2) {
        resultDivision = "0";
        return ;
    }
    int len_max = len1 > len2 ? len1 : len2;
    len_max++;
    int L = len1 - len2;   //两大数相差位数
    int tmp;   //Subtract函数返回值
    int number1_[ len_max] = {0};      //被除数
    int number2_[ len_max] = {0};      //除数
    int result[ len_max] = {0};      //商的反转, 最终保存正确结果于resultDivision中
    int i, j, t;

    for( j = 0, i = len1-1; i > -1; j++, i-- )
        number1_[j] = number1[i] - '0';
    for( j = 0, i = len2-1; i > -1; j++, i-- )
        number2_[j] = number2[i] - '0';

    if( L>0) {   //两数位数不一样
        for( i = len1-1 ; i >= L; i--)
            number2_[i] = number2_[i-L];//朝高位移动
        for( ; i >= 0; i--)
            number2_[i]=0;    //低位补零
        len2 = len1;
    }
    for( j = 0; j < L+1; j++ ){   //重复调用，同时记录减成功的次数，即为商
        while( ( tmp = Substract( number1_, number2_+j, len1, len2-j)) >= 0) {
            len1 = tmp;   //结果长度
            result[L-j]++;   //每成功减一次，将商的相应位加1
        }
    }
    for( i = len_max-1; result[i] == 0 && i >= 0; i-- ) ;  //跳过高位0，获取商的位数

    resultDivision.assign( i+1, '0');

    for( j = 0; i >= 0; i--, j++)
        resultDivision[j] = result[i] + '0';

    for( i = resultDivision.length() - 1, t = 0; i > 0; i--, t++ )
        if( t == 2){
            t = -1;
            resultDivision.insert( i, ",");
        }
}
