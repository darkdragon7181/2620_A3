//
// CS 2620 Assignment 2 Solution
//
// Howard Cheng
//
// This class is an implementation of a string class.  The strings are
// implemented with dynamic arrays.
//

#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
using namespace std;

class myString {
public:
  ///////////////////////////////////////////////////////
  // constructors
  ///////////////////////////////////////////////////////

  // default: initializes to empty string
  myString();

  // convert from a null-terminated string
  myString(const char *s);

  // convert from a single character
  myString(char c);

  // copy constructor
  myString(const myString& s);

  ///////////////////////////////////////////////////////
  // destructor
  ///////////////////////////////////////////////////////

  ~myString();

  ///////////////////////////////////////////////////////
  // other member functions
  ///////////////////////////////////////////////////////

  // assignment operator
  myString& operator=(const myString& s);

  // returns the length of the string
  int length() const;

  // index operators
  //char& at(int i);
  //const char& at(int i) const;   // for constant myStrings

  // returns a substring starting at index k of length n
  myString substr(int k, int n) const;

  // erases n characters starting at index k
  myString& erase(int k, int n);

  // inserts the string s into current string starting at index k
  myString& insert(int k, const myString& s);

  // returns index to the first occurrence of the string s inside
  // the current string, or npos if it does not occur
  int find(const myString &s) const;

  ///////////////////////////////////////////////////////
  // friends
  ///////////////////////////////////////////////////////
  
  //friend istream& getline(istream& is, myString& s);

  ///////////////////////////////////////////////////////
  // Constants
  ///////////////////////////////////////////////////////

  // indicate invalid index
  static const int npos = -1;


  ////////////////////////////////////////////
  // operator overloading
  // added by Navraj (Raj) Saini
  //////////////////////////////////////////
  myString operator+ (const myString& s);
  myString& operator+=(const myString& s);
  
  char& operator[](int i);//done
  const char& operator[](int i) const;//done
  
  bool operator==(const myString& s);
  bool operator!=(const myString& s);
  bool operator<(const myString&s);
  bool operator<=(const myString&s);
  bool operator>(const myString&s);
  bool operator>=(const myString&s);

  /////////////////////////////////////////
  // friend functions
  // added by Navraj (Raj) Saini
  ///////////////////////////////////////
  friend ostream& operator<<(ostream& os, const myString& s);
  friend istream& operator>>(ostream& in, myString& s);
  
private:
  char *A;         // a pointer to the array
  int len;         // length of string

  // helper function to resize the string, also sets len and cap
  void resize(int newlen);
};

// reads a string until the end of line

ostream& operator<<(ostream& os, const myString& s);
istream& operator>>(ostream& in, myString& s);

#endif
