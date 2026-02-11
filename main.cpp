#include <bits/stdc++.h>
#include <random>
using namespace std;

void left_shift(string &num){
    for(int i=0; i<num.size()-1; i++){
        num[i] = num[i+1];
    }
    return;
}

void operation_xor(string &imm_dividend, string &P){
    for(int i=0; i<P.size(); i++){
        if(imm_dividend[i] == P[i])imm_dividend[i] = '0';
        else imm_dividend[i] = '1';
    }
    return;
}

string generate_frame(string &data, string &P){

    string padding = string(P.size()-1, '0');
    string new_data = data + padding;

    string divisor = P;
    string remainder;
    string imm_dividend = string(1, '0');
    for(int i=0; i<P.size()-1; i++)imm_dividend.push_back(new_data[i]);

    for(int i=0; i < data.size(); i++){
        left_shift(imm_dividend);
        imm_dividend[P.size()-1] = new_data[P.size()-1+i];
        if(imm_dividend[0] == '0')continue;
        operation_xor(imm_dividend, divisor);
    }

    string new_padding = string(P.size()-1, '0');
    for(int i=0; i<new_padding.size(); i++){
        new_padding[i] = imm_dividend[i+1];
    }

    string frame = data + new_padding;
    return frame;
}

string generate_random_string(int len){
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<int> dist(0, 1);

    string s;
    s.reserve(len);
    for (int i = 0; i < len; i++)
        s.push_back('0' + dist(gen));
    return s;
}

void pretty_print(string &frame, int k){
    cout<<"_DATA:__";
    for(int i=0; i<k; i++)cout<<frame[i];
    cout<<"__EXTRA_BITS:__";
    for(int i=k; i<frame.size(); i++)cout<<frame[i];
    return;
}

void generate_error(string &frame){
    /* 
    This creates error at just one bit.
    Can be changed for multiple error bits!
    */
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<int> dist(0, frame.size() - 1);

    int error_index = dist(gen);
    if(frame[error_index] == '0')frame[error_index] = '1';
    else frame[error_index] = '0';
    return;
}

string check_CRC(string &frame, string &P, int &k){
    string remainder;
    string imm_dividend = string(1, '0');
    for(int i=0; i<P.size()-1; i++)imm_dividend.push_back(frame[i]);

    for(int i=0; i < k; i++){
        left_shift(imm_dividend);
        imm_dividend[P.size()-1] = frame[P.size()-1+i];
        if(imm_dividend[0] == '0')continue;
        operation_xor(imm_dividend, P);
    }

    string new_padding = string(P.size()-1, '0');
    for(int i=0; i<new_padding.size(); i++){
        new_padding[i] = imm_dividend[i+1];
    }

    for(int i=0; i<P.size()-1; i++){
        remainder.push_back(imm_dividend[i+1]);
    }

    return remainder;
}

int32_t main(){

    /* Code for part (a) */
    int k = 10;
    string data = generate_random_string(k);
    cout << "The current message (data) is: " << data<< endl;

    /* Code for part (b) */
    string P = "110101"; 
    cout << "CRC Pattern: " << P << endl;
    string T = generate_frame(data, P);
    cout << "The generate frame is : " << T << endl;
    cout << "For better visuals: \n"; pretty_print(T, k); cout<<endl;

    string zero_remainder_string = string(P.size()-1, '0');
    cout << "Remainder without error: " << check_CRC(T, P, k) << endl;
    if(check_CRC(T, P, k) == zero_remainder_string) cout << "CRC_Check Passed " << endl;
    else cout << "CRC_Check Failed !" << endl;

    /* code for part (c) */
    generate_error(T);
    cout << "The errored frame is : " << T << endl;
    cout << "For better visuals: \n"; pretty_print(T, k); cout<<endl;


    /* code for part (d) */
    cout << "Remainder after error: " << check_CRC(T, P, k) << endl;
    if(check_CRC(T, P, k) == zero_remainder_string) cout << "CRC_Check Passed " << endl;
    else cout << "CRC_Check Failed !" << endl;

    return 0;
}