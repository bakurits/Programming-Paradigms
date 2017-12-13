#include "gglist.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int testNum = 1;
int printResult (int res);
int test_list(int testNum) ;

int printResult (int res) {
  if (res) {
    //printf("Test %d Passed\n", testNum);
  } else {
    //printf("Test %d Failed\n", testNum);
  }  
  testNum++;
  return res;
}

int main(int argc, char * args[]){
  //printf("************** Starting List structure tests *************** \n");
  int num = atoi(args[1]);
  int res = test_list(num);

  char * outputFile = "out.txt";
  FILE * fp = fopen(outputFile, "w+");
  if (res) {
    fprintf(fp, "t\n");
    printf("t\n");
  } else {
    fprintf(fp, "f\n");
    printf("f\n");
  }

  fclose(fp);

  //printf("********* Tests Finished **********\n");
}

int testAppend1(){
  List l;
  ListNew(&l);
  int x = 10;
  ListAppend(&l, &x, sizeof(int));
  int y;
  ListGet(&l, 0, &y);
  return printResult(y == 10 && y == x);
}

int testAppend2(){
  List l;
  ListNew(&l);
  int x = 10;
  ListAppend(&l, &x, sizeof(int));
  x++;
  ListAppend(&l, &x, sizeof(int));
  x++;
  ListAppend(&l, &x, sizeof(int));
  int ans[10]; 
  ListGet(&l, 0, ans);
  ListGet(&l, 1, ans+1);
  ListGet(&l, 2, ans+2);
printf("results - %d, %d, %d\n", ans[0], ans[1], ans[2]);
  return printResult(ans[0] == 10 && ans[1] == 11 && ans[2] == 12);
}

int testAppend3(){
  List l;
  ListNew(&l);
  int ans = 0;
  for (int i=0; i<1000; i++) {
    ListAppend(&l, &i, sizeof(int));
    ans = ans + i;
  }
  int tmp;
  int sum = 0;
  for (int i=0; i<1000; i++) {
    ListGet(&l, i, &tmp);
    sum = sum + tmp;
  }

  return printResult(sum == ans);
}

int testAppend4(){
  List l;
  ListNew(&l);
  int k = 100;
  char c = 11;
  ListAppend(&l, &k, sizeof(int));
  ListAppend(&l, &c, sizeof(char));
  int arr1[10];
  ListGet(&l, 0, arr1);
  char arr2[10];
  ListGet(&l, 1, arr2);
  return printResult(arr1[0] == 100 && arr2[0] == 11);
}

int testAppend5(){
  List l;
  ListNew(&l);
  int k = 100;
  char c = 11;
  ListAppend(&l, &k, sizeof(int));
  ListAppend(&l, &c, sizeof(char));
  k++;
  c++;
  ListAppend(&l, &k, sizeof(int));
  ListAppend(&l, &c, sizeof(char));
  int arr1[10];
  ListGet(&l, 0, arr1);
  ListGet(&l, 2, arr1+1);
  char arr2[10];
  ListGet(&l, 1, arr2);
  ListGet(&l, 3, arr2+1);
  return printResult(arr1[0] == 100 && arr1[1] == 101 && arr2[0] == 11 && arr2[1] == 12);
}

int testAppend6(){
  List l;
  ListNew(&l);
  int sum1 = 0, sum2 = 0;
  char c = 0;
  for (int i=0; i<1000; i++) {
    ListAppend(&l, &i, sizeof(int));
    ListAppend(&l, &c, sizeof(char));
    sum1 = sum1 + i;
    sum2 = sum2 + c;
    c++;
  }
  int tmp1;
  char tmp2;
  for (int i=0; i<2000; i+=2) {
    ListGet(&l, i, &tmp1);
    ListGet(&l, i+1, &tmp2);
    sum1 = sum1 - tmp1;
    sum2 = sum2 - tmp2;
  }

  return printResult(sum1 == 0 && sum2 == 0);
}

int testAppend7(){
  List l;
  ListNew(&l);
  char * str = "abc";
  ListAppend(&l, str, strlen(str)+1);
  int tmp = 7;
  ListAppend(&l, &tmp, sizeof(int));
  tmp = 0;
  char res[4];
  ListGet(&l, 1, &tmp);
  ListGet(&l, 0, res);
  return printResult(tmp == 7 && strcmp(str, res) == 0);
}

int testAppend8(){
  List l;
  ListNew(&l);
  char * str = "abc";
  ListAppend(&l, str, strlen(str)+1);
  int tmp = 7;
  ListAppend(&l, &tmp, sizeof(int));
  tmp = 0;
  char * ptr = strdup("123qweqt8eq7wgdgdasjdgasd");
  ListAppend(&l, &ptr, sizeof(char *));  
  char res[4];
  ListGet(&l, 1, &tmp);
  ListGet(&l, 0, res);
  char * resPtr;
  ListGet(&l, 2, &resPtr);

  return printResult(tmp == 7 && strcmp(str, res) == 0 && strcmp(ptr, resPtr) == 0);
}

int testRemove9(){
  List l;
  ListNew(&l);
  int x = 10;
  ListAppend(&l, &x, sizeof(int));
  x++;
  ListAppend(&l, &x, sizeof(int));
  ListRemove(&l, 0);
  int y;
  ListGet(&l, 0, &y);
  return printResult(y == 11 && y == x);
}

int testRemove10(){
  List l;
  ListNew(&l);
  int x = 10;
  ListAppend(&l, &x, sizeof(int));
  x++;
  ListAppend(&l, &x, sizeof(int));
  x++;
  ListAppend(&l, &x, sizeof(int));

  ListRemove(&l, 2);
  ListRemove(&l, 0);
  int ans[10]; 
  ListGet(&l, 0, ans);

  return printResult(ans[0] == 11);
}

int testRemove11(){
  List l;
  ListNew(&l);
  int ans = 0;
  for (int i=0; i<1000; i++) {
    ListAppend(&l, &i, sizeof(int));
    if (i >= 500) {
      ans = ans + i;
    }
  }

  for (int i=0; i<500; i++) {
    ListRemove(&l, 0);
  }

  int tmp;
  int sum = 0;
  for (int i=0; i<500; i++) {
    ListGet(&l, i, &tmp);
    sum = sum + tmp;
  }

  return printResult(sum == ans);
}

int testRemove12(){
  List l;
  ListNew(&l);
  int k = 100;
  char c = 11;
  ListAppend(&l, &k, sizeof(int));
  ListAppend(&l, &c, sizeof(char));
  ListRemove(&l, 1);
  ListRemove(&l, 0);
  ListAppend(&l, &k, sizeof(int));
  ListAppend(&l, &c, sizeof(char));
  ListAppend(&l, &k, sizeof(int));
  ListAppend(&l, &c, sizeof(char));
  ListRemove(&l, 1);
  ListRemove(&l, 0);
  int arr1[10];
  ListGet(&l, 0, arr1);
  char arr2[10];
  ListGet(&l, 1, arr2);
  return printResult(arr1[0] == 100 && arr2[0] == 11);
}

int testRemove13(){
  List l;
  ListNew(&l);
  int k = 100;
  char c = 11;
  ListAppend(&l, &k, sizeof(int));
  ListAppend(&l, &c, sizeof(char));
  k++;
  c++;
  ListAppend(&l, &k, sizeof(int));
  ListAppend(&l, &c, sizeof(char));
  ListRemove(&l, 2);
  ListRemove(&l, 2);
  ListAppend(&l, &k, sizeof(int));
  ListAppend(&l, &c, sizeof(char));

  int arr1[10];
  ListGet(&l, 0, arr1);
  ListGet(&l, 2, arr1+1);
  char arr2[10];
  ListGet(&l, 1, arr2);
  ListGet(&l, 3, arr2+1);
  return printResult(arr1[0] == 100 && arr1[1] == 101 && arr2[0] == 11 && arr2[1] == 12);
}

int sum19 = 0;
void testPrint14F(void * d) {
  sum19 += *(int *)d;
}

int testPrint14(){
  List l;
  ListNew(&l);
  int sum1 = 0;
  char c = 0;
  for (int i=0; i<1000; i++) {
    ListAppend(&l, &i, sizeof(int));
    sum1 = sum1 + i;
  }

  ListPrint(&l, testPrint14F);
  return printResult(sum19 == sum1);
}

int sum20 = 0;
int counter20 = 0;
void testPrint15F(void * d) {
  if (counter20 % 2 == 0)
    sum20 += *(int *)d;
  else
    sum20 += *(char *)d;
  counter20++;
}

int testPrint15(){
  List l;
  ListNew(&l);
  int sum1 = 0;
  char c = 0;
  for (int i=0; i<1000; i++) {
    ListAppend(&l, &i, sizeof(int));
    ListAppend(&l, &c, sizeof(char));
    sum1 = sum1 + i + c;
  }

  ListPrint(&l, testPrint15F);
  return printResult(sum20 == sum1);
}

// test checks simple append/get. appeneded element is changed
int testInsert16(){
  List l;
  ListNew(&l);
  int x = 10;
  ListAppend(&l, &x, sizeof(int));
  ListInsert(&l, 0, &x, sizeof(int));
  x++;
  ListInsert(&l, 1, &x, sizeof(int));
  x++;
  ListInsert(&l, 2, &x, sizeof(int));
  int ans[10];
  ListGet(&l, 0, ans);
  ListGet(&l, 1, ans+1);
  ListGet(&l, 2, ans+2);

  return printResult(ans[0] == 10 && ans[1] == 11 && ans[2] == 12);
}

int testInsert17(){
  List l;
  ListNew(&l);
  int ans = 0;
  for (int i=0; i<1000; i++) {
    ListInsert(&l, i, &i, sizeof(int));
    ans = ans + i;
  }
  int tmp;
  int sum = 0;
  for (int i=0; i<1000; i++) {
    ListGet(&l, i, &tmp);
    sum = sum + tmp;
  }

  return printResult(sum == ans);
}

int testInsert18(){
  List l;
  ListNew(&l);
  char * str = "abc";
  int tmp = 7;
  ListAppend(&l, &tmp, sizeof(int));
  ListInsert(&l, 0, str, strlen(str)+1);
  tmp = 0;
  char res[4];
  ListGet(&l, 1, &tmp);
  ListGet(&l, 0, res);
  return printResult(tmp == 7 && strcmp(str, res) == 0);
}

/*
int testInsert19(){
  List l;
  ListNew(&l);
  int x = 10;
  ListAppend(&l, &x, sizeof(int));
  ListInsert(&l, 0, &x, sizeof(int));
  int y;
  ListGet(&l, 0, &y);
  return printResult(y == 10 && y == x);
}
*/
/*
int testInsert20(){
  List l;
  ListNew(&l);
  int k = 100;
  char c = 11;
  ListAppend(&l, &k, sizeof(int));
  ListInsert(&l, 1, &c, sizeof(char));
  k++;
  c++;
  ListAppend(&l, &c, sizeof(char));
  ListInsert(&l, 2, &k, sizeof(int));
  int arr1[10];
  ListGet(&l, 0, arr1);
  ListGet(&l, 2, arr1+1);
  char arr2[10];
  ListGet(&l, 1, arr2);
  ListGet(&l, 3, arr2+1);
  return printResult(arr1[0] == 100 && arr1[1] == 101 && arr2[0] == 11 && arr2[1] == 12);
}
*/


int test_list(int testNum){
  switch(testNum) {
    case 1: return testAppend1();
    case 2: return testAppend2();
    case 3: return testAppend3();
    case 4: return testAppend4();
    case 5: return testAppend5();
    case 6: return testAppend6();
    case 7: return testAppend7();
    case 8: return testAppend8();
    case 9: return testRemove9();
    case 10: return testRemove10();
    case 11: return testRemove11();
    case 12: return testRemove12();
    case 13: return testRemove13();

    case 14: return testPrint14();
    case 15: return testPrint15();

    case 16: return testInsert16();
    case 17: return testInsert17();
    case 18: return testInsert18();
//    case 19: return testInsert19();
//    case 20: return testInsert20();


  }
  return 0;

}
