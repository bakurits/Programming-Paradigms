#include<iostream>
using namespace std;
void swap(char * &str1, char * &str2){
char *temp = str1;
str1 = str2;
str2 = temp;
}
int main(){
char *str1 = "butkashio";
char *str2 = "imnairio";
swap(str1, str2);
cout<<"shedi qalo "<<str1<<endl;
cout<<"ara var "<<str2<<endl;
return 0;
}