#include <bits/stdc++.h>
using namespace std;

class Restoring {
    private:

        int digits = 0;

        string toBinary(int n) {
            string str;
            int t = abs(n);
            int dig;
            while(t!=0) {
                dig = t%2;
                str =  to_string(dig) + str;
                t = t/2;
            }
            while(str.size()<digits) {
                str = '0' + str;
            }
            if(n<0) {
                str = twosComplement(str);
            }
            return str;
        }

        int toInteger(string bin) {
            if(bin[0]=='1') {
                bin = twosComplement(bin);
                return -stoi(bin,0,2);
            }
            return stoi(bin,0,2);
        }

        string addBinary(string b1, string b2) {
            string sum = "";
            int i = b1.size()-1;
            int j = b2.size()-1;
            int carry = 0;
            while(i>=0 || j>=0) {
                if(j==-1) {
                    if(carry==0) {
                        sum = b1[i] + sum;
                    }
                    else {
                        if(b1[i]=='0') {
                            sum = '1' + sum;
                            carry = 0;
                        }
                        else {
                            sum = '0' + sum;
                            carry = 1;
                        }
                    }
                    i--;
                }
                else if(i==-1) {
                    if(carry==0) {
                        sum = b2[j] + sum;
                    }
                    else {
                        if(b2[j]=='0') {
                            sum = '1' + sum;
                            carry = 0;
                        }
                        else {
                            sum = '0' + sum;
                            carry = 1;
                        }
                    }
                    j--;
                }
                else {
                    if(carry==0) {
                        if(b1[i]=='0' && b2[j]=='0') {
                            sum = '0' + sum;
                        }
                        else if((b1[i]=='0' && b2[j]=='1') || (b1[i]=='1' && b2[j]=='0')) {
                            sum = '1' + sum;
                        }
                        else {
                            sum = '0' + sum;
                            carry = 1;
                        }
                    }
                    else {
                        if(b1[i]=='0' && b2[j]=='0') {
                            sum = '1' + sum;
                            carry = 0;
                        }
                        else if((b1[i]=='0' && b2[j]=='1') || (b1[i]=='1' && b2[j]=='0')) {
                            sum = '0' + sum;
                        }
                        else {
                            sum = '1' + sum;
                        }
                    }
                    i--;
                    j--;
                }
            }
            if(carry==1) {
                sum = '1' + sum;
            }
            return sum;
        }

        string twosComplement(string b) {
            string comp = "";
            for(int i = 0; i<b.size(); i++) {
                if(b[i]=='0')
                    comp += '1';
                else
                    comp += '0';
            }
            return addBinary(comp,"1");
        }

        char rightShift(string &bin) {
            string temp = bin[0] + bin;
            char leak = temp[temp.size()-1];
            bin = temp.substr(0,temp.size()-1);
            return leak;
        }

        char leftShift(string &bin) {
            char leak = bin[0];
            bin = bin.substr(1) + '?';
            return leak;
        }

        void setDigits(int n) {
            string str;
            int t = abs(n);
            int dig;
            while(t!=0) {
                dig = t%2;
                str =  to_string(dig) + str;
                t = t/2;
            }
            digits = str.size() + 2;
        }

    public:

        string restoringDiv(int q, int m) {
            if(q<m) {
                cout << "Quotient is 0" << endl;
                cout << "Remainder is " << m << endl;
                return "0";
            }
            //M is divisor, Q is dividend
            int a = 0;
            setDigits(max(abs(m),abs(q)));
            string A = toBinary(a);
            string M = toBinary(m);
            string negM = toBinary(-m);
            string Q = toBinary(q);
            int n = digits;
            string comment = "Initiliaze";
            cout << "n\tA\t\t\t\t\tQ\t\t\t\tComment" << endl;
            cout << n << "\t " << A << "\t\t\t\t" << Q << "\t\t\t\t" << comment << endl;
            while(n!=0) {
                char leak = leftShift(Q);
                leftShift(A);
                A[A.size()-1] = leak;
                comment = "Left Shift AQ";
                cout << n << "\t " << A << "\t\t\t\t" << Q << "\t\t\t\t" << comment << endl;
                string restoreValue = A;
                comment = "A = A - M";
                cout << n << "\t " << A << "\t\t\t\t" << Q << "\t\t\t\t" << comment << endl;
                cout << n << "\t+" << negM << endl;
                cout << "-----------------" << endl;
                A = addBinary(A,negM);
                if(A.size()!=digits) {
                    A = A.substr(A.size()-digits);
                }
                cout << n << "\t " << A << "\t\t\t\t" << Q << endl;
                if(A[0]=='0') {
                    comment = "Q0 <-- 1";
                    Q[Q.size()-1] = '1';
                    cout << n << "\t " << A << "\t\t\t\t" << Q << "\t\t\t\t" << comment << endl;
                }
                else {
                    comment = "Q0 <-- 0";
                    Q[Q.size()-1] = '0';
                    cout << n << "\t " << A << "\t\t\t\t" << Q << "\t\t\t\t" << comment << endl;
                    comment = "Restore A";
                    A = restoreValue;
                    cout << n << "\t " << A << "\t\t\t\t" << Q << "\t\t\t\t" << comment << endl;
                }
                n--;
            }
            comment = "Completed";
            cout << n << "\t " << A << "\t\t\t\t" << Q << "\t\t\t\t" << comment << endl;
            cout << "\nQuotient is in Q, Remainder is in A" << endl;
            cout << "Quotient is " << Q << " which is equal to " << toInteger(Q) << endl;
            cout << "Remainder is " << A << " which is equal to " << toInteger(A) << endl;
            return Q;
        }
};

int main() {
    Restoring b;
    int denominator = 52;
    int numerator = 133;
    string prod = b.restoringDiv(numerator,denominator);
    return 0;
}