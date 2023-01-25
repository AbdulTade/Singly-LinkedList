# include <iostream>
# include "../headers/linkedlist.hpp"


int main() {
    
  LinkedList<std::string> ll{};
  ll.insertEnd("Hello");
  ll.insertEnd(std::string("world"));
  ll.insertEnd("here");
  ll.insertEnd("something");
  ll.insertBegin("I am at the beginning");

  for(auto it = ll.begin(); it != ll.end(); ++it)
  {
    std::cout << *it << std::endl;
  }

}