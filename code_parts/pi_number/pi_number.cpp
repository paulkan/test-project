#include <iostream>
#include <string> 
#include <sstream>
#include <cstdio>

// Define this macro because of bug in MinGW compiler 
// (https://gcc.gnu.org/bugzilla/show_bug.cgi?id=52015)
#define TO_STR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()
using namespace std;

/**
 * A Spigot Algorithm for the Digits of Pi (based on 
 * http://www.mathpropress.com/stan/bibliography/spigot.pdf) 
 * 
 * @author paulkan (02.10.2016)
 * 
 * @param N - length of Pi number
 */
string getPiUpToN(long n)
{
  // we will add numbers to pi string
  string pi = "";
  int len = n * 10 / 3;	         // size of the array
  int boxes[len] = {0};
  int unavDigits = 0;            // counter of temporary unavailable digits
  
  for (int i = 0; i < len; i++)  // initiate array with 2
  {
    boxes[i] = 2;
  }
  
  for (int i = 0; i < n; i++)
  {
    int carriedOver = 0;
    int sum = 0;
    int q = 0;                            // new digit of Pi number
    for (int j = len - 1; j >= 0; j--)    // work backwards
    {
      boxes[j] *= 10;
      sum = boxes[j] + carriedOver;
      int res = sum / (j * 2 + 1);        // result of the devision sum on denominator
      boxes[j] = sum % (j * 2 + 1);       // remainder from the devision sum on denominator
      carriedOver = res * j;              // j - numerator
    }
    boxes[0] = sum % 10;            

    q = sum / 10;	                  // assign new digit

    if (q == 9)                           // process invalid numbers
    {
      unavDigits++;
    } 
    else if (q == 10) 
    {
      q = 0;
      for (int k = 1; k <= unavDigits; k++) 
      {
        int replaced = 0;
        sscanf(pi.substr(i - k, i - k + 1).c_str(), "%d", &replaced);
        if (replaced == 9) 
        {
          replaced = 0;
        } 
        else 
        {
          replaced++;
        }
        pi.erase(i - k, 1);
        pi.insert(i - k, TO_STR(replaced));
      }
      unavDigits = 1;
    }
    else 
    {
      unavDigits = 1;
    }
    pi.append(TO_STR(q));
  }

  if (pi.length() >= 2) 
  {
    pi.insert(1, ".");	        // add dot after 3
  }
  return pi;
}

int main(int argc, char *argv[])
{
  long countOfDigits = 0;
  cout << "Please enter the count of Pi's digits to be generated: ";
  cin >> countOfDigits;
  cout << endl << getPiUpToN(countOfDigits);
}