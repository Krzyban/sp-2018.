//The boxes will have IDs which differ by
//exactly one character at the same position in both strings.
//For example, given the following box IDs:

//abcde
//fghij
//klmno
//pqrst
//fguij
//axcye
//wvxyz
//The IDs abcde and axcye are close, but they differ by two characters (the second and fourth).
//However, the IDs fghij and fguij differ by exactly one character, the third (h and u).
//Those must be the correct boxes.
//What letters are common between the two correct box IDs?
//(In the example above, this is found by removing the differing character from either ID, producing fgij.)


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MDN 254
#define MN 10

void read_data();
void compare();
void print();

int main()
{
  int a=250, word1=0, word2=0;
  FILE *fp = fopen("slowa","r");
  char **A = (char**) malloc(a*sizeof(char*));//zapisuje wyrazy do tablicy
  read_data(A,a,fp);
  fclose(fp);
  compare(A,a, &word1, &word2);
  print(A, word1, word2);
}

void read_data(char **A, int amount, FILE *fp)//amount=a
{
  char letters[MDN];
  int i=0;
  for (i=0;i<amount; i++)
  {
    fscanf(fp,"%s",letters);
    A[i] = (char*) malloc(sizeof(char)*MDN);
    strcpy(A[i],letters);//z letters do A
  }
}

void compare(char **A, int a, int *word1, int *word2)
{
  for(int i=1; i<a; i++)
  {
    for(int j=0; j<i; j++)//żeby nie porownywało bez sensu dodatkowo 0 z 1 i 1 z 0
    {
      int l=0;//zlicza ilośc prawidłowych literek ma być 25
      int c=0;//znacznik pozycji w wyrazie 0-25
      int x=0;//licznik błędów max 1
      while(x<2 && c<26)//c skacze po wyrazie ,a x sprawdza ilosc błędów
      {
        if(*(A[i]+c) == *(A[j]+c))//j jest do porównywania
        {
          c++;
          l++;
        }
        else
        {
          x++;
          c++;               
        }
      }
      if(l==25)
      {
        *word1=i;
        *word2=j;
      }
    }
  }
}

void print(char **A, int word1, int word2)
{
  for (int i=0; i<26; i++)
    if(*(A[word1]+i)==*(A[word2]+i))
      printf("%c",*(A[word2]+i));
}