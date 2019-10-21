#include <iostream>
#include <stack>
#include <vector>
#include <map>
#include <cmath>
using namespace std;
bool isNumber(char a){
    char letras[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    for( int i  = 0; i < 26; i++)
        if (letras[i] == a)
            return true;
    return false;
}
bool inMap(map <char,string> letras, char a) {
    if (letras.empty()) {
        return false;
    } else {
        if (letras[a] != "")
            return true;
        else
            return false;
    }
}
bool isNum(char a){
    char numeros[10] = {'1','2','3','4','5','6','7','8','9','0'};
    for(int i = 0; i < 10; i++)
        if(a == numeros[i])
            return true;
    return false;
}
bool mayor(stack<string> a,string b) {
    map<string, int> operadores;
    operadores["+"] = 1;
    operadores["-"] = 1;
    operadores["*"] = 2;
    operadores["/"] = 2;
    operadores["^"] = 3;
    operadores[")"] = 0;
    operadores["("] = 0;

    for (int i = 0; i < a.size(); i++) {
        if (operadores[a.top()] >= operadores[b])
            return true;
        a.pop();
    }
    return false;

}
double calcularres(vector<string>a){
    if(a.size() == 3){
         if(a[2] == "+"){
            return stof(a[0])+stof(a[1]);
        }
        else if(a[2] == "/"){
            return stof(a[0])/stof(a[1]);
        }
        else if(a[2] == "*"){
            return stof(a[0])*stof(a[1]);
        }
        else if(a[2] == "-"){
            return stof(a[0])-stof(a[1]);
        }
        else if(a[2] == "^"){
            return pow(stof(a[0]),stof(a[1]));
        }

    }
    else{
        vector<string> neo;
        string c;
        int i;
        for(i= 0; i < a.size(); i++){
            if(a[i] == "+"){
                 c = to_string(stof(a[i-2]) + stof(a[i-1])) ;
                 break;
            }
            else if(a[i] == "/"){
                c = to_string(stof(a[i-2])/stof(a[i-1]));
                break;
            }
            else if(a[i] == "*"){
                c = to_string(stof(a[i-2])*stof(a[i-1]));
                break;
            }
            else if(a[i] == "-"){
                c = to_string(stof(a[i-2]) - stof(a[i-1]));
                break;
            }
            else if(a[i] == "^"){
                c = to_string(pow(stof(a[i-2]),stof(a[i-1])));
                break;
            }
        }
        int j= i-2;
        for(int k = 0; k  < j; k++){
            neo.push_back(a[k]);
        }
        neo.push_back(c);
        int p;
        ++i;
        for( p= j+1;  p < a.size()-2 ; p++){
            neo.push_back(a[i]);
            i++;
        }
        return calcularres(neo);
    }
    // Falta un return
}

int main() {
    string exp;
    string newexp;
    cin >> exp;
    string val;
    int j = 0;
    map <char,string> letras;
    for(int i = 0; i < exp.size(); i++){
        if(isNumber(exp[i])){
            if(inMap(letras, exp[i])){
                for(int k = 0; k < letras[exp[i]].size() ; k++) {
                    newexp.resize(newexp.size()+1);
                    newexp[j] = letras[exp[i]][k];
                    j++;
                }
            }
            else{
                cout << "Ingrese el valor de " << exp[i] << ":";
                cin >> val;
                letras[exp[i]] =val;
                for(int k = 0; k < letras[exp[i]].size() ; k++) {
                    newexp.resize(newexp.size()+1);
                    newexp[j] = letras[exp[i]][k];
                    j++;
                }
            }
        }
        else{
            newexp.resize(newexp.size()+1);
            newexp[j] = exp[i];
            j++;
        }
    }
    string num;
    vector <string> solve;
    stack <string> solver;

    string op;
    for(int i = 0 ; i < newexp.size(); i++){
        if(isNum(newexp[i])){
            num = num + newexp[i];
        }
        else{
            if(!num.empty()){
                solve.push_back(num);
                num = "";
            }
            if(solver.empty()){
                    op.resize(1);
                    op[0]=newexp[i];
                    solver.push(op);
                }
            else {
                if (newexp[i] == '(') {
                    solver.push("(");
                }
                else if(newexp[i] == ')'){
                    solve.push_back(solver.top());
                    solver.pop();
                    solver.push(")");
                }
                else {
                    op[0] = newexp[i];
                    if (mayor(solver,op)) {
                        solve.push_back(solver.top());
                        solver.pop();
                        solver.push(op);
                    } else {
                        solver.push(op);
                    }
                    op = " ";
                }
            }
        }
    }
    if(!num.empty()){
        solve.push_back(num);
        num = "";
    }
    int s = solver.size();
    for(int i =0; i <  s ; i++){
        solve.push_back(solver.top());
        solver.pop();
    }
    vector<string> final;
    for(int i  = 0; i < solve.size();i++){
        if(solve[i] != "(" && solve[i] != ")" ){
            final.push_back(solve[i]);
        }
    }
    double resultado;
    // No está dando los resultados correctos en algunos casos:
    // Probar con ((7*3)/4+6*(A^2)/B)*(5)
    // A: 123 B: 11
    // Resultado esperado: 41287.2 Actual: 41266.2
    // o 7/4*((A+B)*A)+3 con A: 11 B: 12
    resultado = calcularres(final);
    cout << endl <<  resultado;


}
