#include<iostream>
#include"List.h"
														//однозв'язний список
														//next->
				
														//двозв'язний список
														//<-prev  |  next->
int main() {
	List<int> list1;

	for (size_t i = 0; i < 5; i++)
		list1.PushBack(i);

	for (size_t i = 5; i < 10; i++)
		list1.PushFront(i);
	List<int> list2(list1);

	list1.Show();
	std::cout << "\n";
	list2.PopBack();
	list2.PopFront();
	
	list2.Show();
	std::cout << "=======================\n\n";


	list2.Remove(0);

	std::cout << "\n";
	list2.Show();

	list2.Reverse();
	list2.Show();
	std::cout << "\n";


	for (List<int>::Iterator it = list2.Begin(); it != list2.End(); ++it) {
		std::cout << *it<< " ";
	}
	std::cout << "\n";

	for (List<int>::Iterator it = list2.Begin(); it != list2.End(); ++it) {
		*it = rand() % 100;
	}

	for (List<int>::Iterator it = list2.Begin(); it != list2.End(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << "\n";

}