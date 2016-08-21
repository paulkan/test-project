#include <stdio.h>
#define COUNT 3

int already[COUNT];
int arr[COUNT];

void combination(int t)
{
  int i;
  if(t == COUNT)
  {
    for(i = 0; i < COUNT; i++)
      printf("%d", arr[i]);
    printf(" ");
  }
  for(i = 0; i < COUNT; i++)
  {
    if(!already[i])
    {
      arr[t] = i + 1;
      already[i] = 1;
      combination(t + 1);
      already[i] = 0;
    }
  }
}

int main()
{
  combination(0);
  printf("\n");
  return 0;
}