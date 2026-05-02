#include <iostream>
#include "tree_entry.hpp"

int main()
{
  BiTree< int > lhs_root;
  BiTree< int > four;
  BiTree< int > three;
  BiTree< int > two;
  BiTree< int > six;
  BiTree< int > five;

  lhs_root = {1, nullptr, &four, nullptr};
  four = {4, &three, &six, &lhs_root};
  three = {3, &two, nullptr, &four};
  two = {2, nullptr, nullptr, &three};
  six = {6, &five, nullptr, &four};
  five = {5, nullptr, nullptr, &six};

  BiTree< int > pattern_root;
  BiTree< int > one;

  pattern_root = {2, &one, nullptr, nullptr};
  one = {1, nullptr, nullptr, &pattern_root};

  auto first_entry = begin< int >(&lhs_root, &pattern_root);
  std::cout << first_entry.incl.first->val << " " << first_entry.incl.second->val << "\n";
}
