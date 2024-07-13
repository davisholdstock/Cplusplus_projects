#include "main.h"
#include "LinkedListInterface.h"
#include "LinkedList.h"
#include <string>
#include <iostream>
#include <ostream>
#include <istream>
#include <stdio.h>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

#define CONSOLE 1

int main(int argc, char* argv[])
{
	VS_MEM_CHECK;

	//cout << endl << "Input File: " << argv[1];
	ifstream in(argv[1]);

	cout << endl << "Output File: " << (CONSOLE ? "cout" : argv[2]) << endl;
	ostream& out = CONSOLE ? cout : *(new ofstream(argv[2]));

	//ofstream out(argv[2]);

	LinkedList<string> myList;
	LinkedList<string> myListCopy;
	LinkedList<string>::Iterator iter = myList.begin();
	LinkedList<string>::Iterator iter_end = myList.end();
	
	// process input strings
	for (string line; getline(in, line);)
	{
	   string item1, item2;
	   if (line.size() == 0) continue;
	   out << endl << line;
	   istringstream iss(line);
	   iss >> item1;
	   if (item1 == "Insert")
	   {
		  while (iss >> item2)
		  {
			 myList.push_front(item2);
		  }
	   }
	   else if (item1 == "PrintList") //Print list out
	   {
		   out << " " << myList;
	   }
	   else if (item1 == "Clear") //Clear the list
	   {
		   myList.clear();
		   out << " OK";
	   }
	   else if (item1 == "Empty") //Check if the list is empty
	   {
		   out << (myList.empty() ? " true" : " false");
	   }
	   else if (item1 == "Delete") //Delete the first item in the list
	   {
		   myList.pop_front();
		   out << (myList.empty()? " Empty!" : " OK");
	   }
	   else if (item1 == "First") //Return the first item in the list
	   {

		   out << " " << (myList.empty()? "Empty!" : myList.front());
	   }
	   else if (item1 == "Remove") //Remove an item from the list
	   {
		   iss >> item2;
		   myList.remove(item2);
	   }
	   else if (item1 == "Reverse") //Print the list backwards
	   {
		   myList.reverse();
		   out << (myList.empty()? " Empty!" : " OK");
	   }
	   else if (item1 == "Size") //Print the size of the list
	   {
		   out << " " << myList.size();
	   }
	   else if (item1 == "Last") //Return the last item of the list
	   {
		   out << " " << (myList.empty() ? "Empty!" : myList.back());
	   }
	   else if (item1 == "Append") //Add to the back of the list
	   {
		   while (iss >> item2)
		   {
			   myList.push_back(item2);
		   }
	   }
	   else if (item1 == "Drop") //Delete the last item in the list
	   {
		   string s = (myList.empty() ? " Empty!" : " OK");
		   myList.pop_back();
		   out << s;
	   }
	   else if (item1 == "Copy") //Make a copy of the list
	   {
		   //myList.copy(myListCopy);
		   out << " OK";
	   }
	   else if (item1 == "PrintCopy") //Print the copy of the list
	   {
		   //out << " " << myListCopy;
	   }
	   else if (item1 == "Iterate") //Use iterator to print the list
	   {
		   myList.iterate(out, iter);
	   }
	   else if (item1 == "Find") //Find an item in the list
	   {
		   iss >> item2;
		   if (myList.find(iter, iter_end, item2) != NULL) out << "OK";
		   else out << " Not Found";
	   }
	   else if (item1 == "InsertAfter") //Insert an item after another item
	   {
		   string s = "";
		   iss >> s;
		   iss >> item2;
		   if (myList.find(iter, iter_end, item2) != NULL)
		   {
			   myList.find(iter, iter_end, item2);
			   out << " OK";
			   myList.insert_after(iter, s);
		   }
		   else out << " Not Found";
	   }
	   else if (item1 == "InsertBefore") //Insert an item before another item
	   {
		   string s = "";
		   iss >> s;
		   iss >> item2;
		   if (myList.find(iter, iter_end, item2) != NULL)
		   {
			   myList.find(iter, iter_end, item2);
			   out << " OK";
			   myList.insert(iter, s);
		   }
		   else out << " Not Found";
	   }
	   else if (item1 == "Erase") //Erase an item
	   {
		   iss >> item2;
		   if (myList.find(iter, iter_end, item2) != NULL)
		   {
			   myList.find(iter, iter_end, item2);
			   out << " OK";
			   myList.erase(iter);
		   }
		   else out << " Not Found";
	   }
	   else if (item1 == "Replace") //Replace an item with something else
	   {
		   string old = "";
		   iss >> old;
		   iss >> item2;
		   if (myList.find(iter, iter_end, old) != NULL)
		   {
			   out << " OK";
			   myList.replace(iter, iter_end, old, item2);
		   }
	   }
	}
	myList.clear();

	return 0;
}