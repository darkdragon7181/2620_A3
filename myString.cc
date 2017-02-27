//
// CS 2620 Assignment 2 Solution
//
// Howard Cheng
// Sep 26, 2013
//
// This class is an implementation of a string class.  The strings are
// implemented with dynamic arrays.
//

#include "myString.h"
#include <cassert>
#include <cctype>

using namespace std;


///////////////////////////////////////////////////////
// constructors
///////////////////////////////////////////////////////

// default: initializes to empty string
myString::myString()
  : A(nullptr), len(0) 
{
}

// convert from a null-terminated string
myString::myString(const char *s)
  : A(nullptr), len(0)     // setting these so resize() works properly
{
  int newlen = 0;
  while (s[newlen] != '\0')
    newlen++;
  resize(newlen);
  for (int i = 0; i < len; i++) {
    A[i] = s[i];
  }
}

// convert from a single character
myString::myString(char c)
  : A(nullptr), len(0)
{
  resize(1);
  A[0] = c;
}

// copy constructor
myString::myString(const myString& s)
  : A(nullptr), len(0)
{
  resize(s.len);
  for (int i = 0; i < len; i++) {
    A[i] = s.A[i];
  }
}

///////////////////////////////////////////////////////
// destructor
///////////////////////////////////////////////////////

myString::~myString()
{
  delete[] A;
  A = nullptr;         // not necessary, but just being safe
}

///////////////////////////////////////////////////////
// other member functions
///////////////////////////////////////////////////////

// assignment operator
myString& myString::operator=(const myString& s)
{
  if (this != &s) {       // prevent self assignment
    resize(s.len);
    for (int i = 0; i < len; i++) {
      A[i] = s.A[i];
    }
  }
  return *this;
}

// returns the length of the string
int myString::length() const
{
  return len;
}

// index operator for non-constant myString
// changed the at function to the operator[] overload
// by Navraj (Raj) Saini
char& myString::operator[](int i)
{
  assert(0 <= i && i < len);
  return A[i];
}

// index operator for constant myString
// changed to the operator[] overload
// by Navraj (Raj) Saini
const char& operator[](int i) const
{
  assert(0 <= i && i < len);
  return A[i];
}

// returns a substring starting at index k of length n
myString myString::substr(int k, int n) const
{
  assert(0 <= k && k+n <= len);
  
  myString s;
  s.resize(n);     // make sure we have enough space
  for (int i = 0; i < n; i++) {
    s.A[i] = A[k+i];    // now copy
  }
  return s;
}

// erases n characters starting at index k
myString& myString::erase(int k, int n)
{
   assert(0 <= k && k+n <= len);

   // first we remove the n characters by shifting down
   for (int i = k+n; i < len; i++) {
      A[i-n] = A[i];
   }

   // now resize
   resize(len-n);
  
   return *this;
}

// inserts the string s into current string starting at index k
myString& myString::insert(int k, const myString& s)
{
   assert(0 <= k && k <= len);

   int oldlen = len;   // save it because resize() changes it

   // first we make sure we have enough space
   resize(len+s.len);

   // now make room for new string
   for (int i = oldlen-1; i >= k; i--) {
      A[i+s.len] = A[i];
   }
  
   // now insert the new string
   for (int i = 0; i < s.len; i++) {
      A[k+i] = s.A[i];
   }

   return *this;
}

// returns index to the first occurrence of the string s inside
// the current string, or npos if it does not occur
int myString::find(const myString &s) const
{
   for (int i = 0; i <= len - s.len; i++) {
      int match = 0;     // number of matching characters from position i
      while (match < s.len && A[i+match] == s.A[match]) {
	 match++;
      }

      // everything matches
      if (match == s.len) {
	 return i;
      }
   }

   // haven't found it yet, so it is not there
   return npos;
}


// helper function to resize the string, also sets len and cap
void myString::resize(int newlen)
{
   char *temp = new char[newlen];

   // now copy: take care not to go out of bound on either string
   for (int i = 0; i < len && i < newlen; i++) {
      temp[i] = A[i];
   }

   // now deallocate A and make it point to new array
   delete[] A;
   A = temp;
  
   len = newlen;
}

// reads a string until the end of line: this routine does all the necessary
// error checks.  There is no need to do that for your assignment.

// was the getline function... changed to the input operator
// by Navraj (Raj) Saini
istream& operator>>(istream& is, myString& s)
{
   char c;

   // remember whether we have been through the loop before, because we need
   // to remove the old string on the first try (but we can't do that before
   // we try reading, because if the first input operation fails we do not
   // want to change s).  This is the "correct" behaviour in C++, but not
   // necessary for the assignment.
   bool first_time = true;
   int n = 0;
   do {
      is.get(c);

      if (!is.good())
	 break;

      if (first_time)
	 s.resize(0);

      if (c != '\n') {
	 s.resize(n*2);
	 s.A[n] = c;
	 n++;
      }

      first_time = false;
   } while (c != '\n');

   if (first_time) {
      // we haven't read anything, so set fail bit
      is.setstate(ios::failbit);
   } else {
      // read something, make sure fail bit is cleared
      is.clear(is.rdstate() & ~ios::failbit);
   }
   return is;
}

//added by Navraj (Raj) Saini
ostream& operator<<(ostream& os, const myString& s)
{
   int i = 0;
   while (s[i] != '\n')
   {
      os << s[i];
      i++;
   }
}

//added by Navraj (Raj) Saini
bool myString::operator==(const myString& s)
{
   if (this.lenght() != s.lenght())
      return false;
   else 
   {
      for (int i = 0; i < s.length(); i++)
      {
	 if (this[i] != s[i])
	    {
	       return false;
	    }
      }
      return true;
   }
}

bool myString::operator!=(const myString& s)
{
   if (this.length() == s.lenght())
   {
      for (int i = 0; i < s.lenght(); i++)
      {
	 if(this[i] != s[i])
	    return true;
	 return false;
      }
   }
   return true;
}

bool operator<(const myString&s)
{
   if (this.lenght() < s.lenght())
   {
      return true;
   }
   else if (this.lenght() == s.length())
   {
      for (int i = 0; i < s.lenght(); i++)
      {
	 if (this[i] > s[i])
	    return false;
      }
      return true;
   }
   else
      return false;
}
bool operator<=(const myString&s);
bool operator>(const myString&s);
bool operator>=(const myString&s);
myString myString::operator+ (const myString& s)
{
   myString n(this.lenght()+s.length());
   int j = this.length();
   
   n.len = this.length()+s.length();
   //copy over all the values from the first myString to new myString
   for (int k = 0; k < this.length(); k++)
      n[i] = this[i];

   //add the s string to the end of the myString
   for (int i = 0; i < s.lenght(); i++)
   {
      n[j] = s[i];
      j++;
   }
   return n;
}
myString& myString::operator+=(const myString& s)
{
   this.resize(this.length()+s.length());
   int j = this.length();
   for (int i = 0; i < s.lenght(); i++)
   {
      this[j] = s[i];
      j++;
   }
   return this;
}
