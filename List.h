#pragma once

template<typename T>
class List
{
private:
	struct Node {
		int data;
		Node* previous;
		Node* next;
	};

	Node* head;
	Node* tail;
	size_t size;

	void Copy(const List& other);
	void Move(List&& other)noexcept;


public:
	List();
	List(const List& other);
	List(List&& other)noexcept;

	~List();

	List& operator=(const List& other);
	List& operator=(List&& other);

	void PushBack(const int& value);
	void PushFront(const int& value);

	void PopBack();
	void PopFront();

	int& Front();
	const int& Front()const;
	//якщо ми повертаємо посилання на змінну тобто lvalue то потрібно прописувати два варіанти методу const і простий
	int& Back();
	const int& Back()const;

	void Remove(const int& value);
	bool Find(const int& value);

	void Reverse();

	void Reserve();
	void Clear();

	bool IsEmpty()const;
	size_t Size()const;

	void Show()const;

	class Iterator {
	private:
		Node* node;
	public:
		Iterator(Node*node)
			:node(node) { }

		Iterator& operator++()
		{
			node = node->next;
			return *this;
		}
		Iterator operator++(int) {
			Iterator temp(*this);
			++* this;
			return temp;
		}

		Iterator& operator--()
		{
			node = node->previous;
			return *this;
		}
		Iterator operator--(int) {
			Iterator temp(*this);
			--* this;
			return temp;
		}

		T* operator->() {
			return &node->data;
		}

		T& operator*() { return &node->data; }

		bool operator!=(const Iterator& other) { return node != other.node; }
	};
	//Iterator methods

	Iterator& Begin();
	Iterator& End();
};

#include<iostream>
#include<utility>	//для ф-ції swap
template<typename T>
void List<T>::Copy(const List& other)
{
	if (other.size == 0)
		return;

	head = new Node{ other.head->data,nullptr,nullptr };
	tail = new Node{ other.tail->data,nullptr,nullptr };

	Node* current = head;
	Node* otherCurrent = other.head->next;

	while (otherCurrent != nullptr) {
		//тут не так як в однозв'язному списку тут відразу йде заповнення наступного 
		current->next = new Node{ otherCurrent->data,current,nullptr };
		//помилка була в тому що ми не присвоювали tail щось
		if (otherCurrent->data == tail->data) {
			tail->previous = current;
		}
		current = current->next;
		otherCurrent = otherCurrent->next;
	}

	size = other.Size();
}

template<typename T>
void List<T>::Move(List&& other) noexcept
{
	head = other.head;
	tail = other.tail;
	size = other.size;

	other.head = nullptr;
	other.tail = nullptr;
	other.size = 0;
}

template<typename T>
List<T>::List()
	:head(nullptr), tail(nullptr), size(0)
{ }

template<typename T>
List<T>::List(const List& other)
	:List()
{
	if (other.Size() != 0)
		Copy(other);
}

template<typename T>
List<T>::List(List&& other) noexcept
{
	Move(std::move(other));
}

template<typename T>
List<T>::~List()
{
	Clear();
}

template<typename T>
List<T>& List<T>::operator=(const List& other)
{
	if (this != &other) {
		Clear();
		Copy(other);
	}

	return *this;
}

template<typename T>
List<T>& List<T>::operator=(List&& other)
{
	if (this != &other) {
		Clear();
		Move(std::move(other));
	}
	return *this;
}

template<typename T>
void List<T>::PushBack(const int& value)
{
	if (size == 0) {
		head = new Node{ value,nullptr,nullptr };
		tail = head;
	}
	else {
		tail->next = new Node{ value,tail,nullptr };
		tail = tail->next;
	}
	size++;
}

template<typename T>
void List<T>::PushFront(const int& value)
{
	if (size == 0) {
		head = new Node{ value,nullptr,nullptr };
		tail = head;
	}
	else {
		head = new Node{ value,nullptr,head };
		head->next->previous = head;
	}
	size++;
}

template<typename T>
void List<T>::PopBack()
{
	if (size == 0)
		return;

	else if (size == 1) {
		delete tail;
		head = nullptr;
		tail = nullptr;
	}
	else {
		Node* temp = tail;
		tail = tail->previous;
		tail->next = nullptr;
		delete temp;
	}
	size--;

}

template<typename T>
void List<T>::PopFront()
{
	if (Size() == 0)
		return;

	if (Size() == 1) {
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	else {
		Node* temp = head;
		head = head->next;
		head->previous = nullptr;
		delete temp;
	}
}

template<typename T>
int& List<T>::Front()
{
	return head->data;
}

template<typename T>
const int& List<T>::Front() const
{
	return head->data;
}

template<typename T>
int& List<T>::Back()
{
	return tail->data;
}

template<typename T>
const int& List<T>::Back() const
{
	return tail->data;
}

template<typename T>
void List<T>::Remove(const int& value)
{
	Node* current = head;

	while (current != nullptr) {
		// тут в if було одне = а не ==
		if (current->data == value) {
			if (head == current) {
				PopFront();
			}
			else if (tail == current) {
				PopBack();
			}
			else {
				current->previous->next = current->next;
				current->next->previous = current->previous;
				delete current;
			}
			size--;
			return;
		}
		current = current->next;
	}
}

template<typename T>
bool List<T>::Find(const int& value)
{
	Node* current = head;
	for (size_t i = 0; i < Size(); i++) {
		if (current->data == value)
			return true;

		current = current->next;
	}
	return false;
}

template<typename T>
void List<T>::Reverse()
{
	tail = head;
	Node* current = head;
	Node* temp = nullptr;

	while (current != nullptr) {
		temp = current->previous;
		current->previous = current->next;
		current->next = temp;
		/*std::swap(current->previous, current->next);*/


		current = current->previous;
	}

	if (temp != nullptr)
		head = temp->previous;
}

template<typename T>
void List<T>::Clear()
{
	while (head != nullptr) {
		Node* temp = head;
		head = head->next;
		delete temp;
	}

	tail = nullptr;
	size = 0;
}

template<typename T>
size_t List<T>::Size() const
{
	return size;
}

template<typename T>
void List<T>::Show() const
{
	if (size == 0) {
		std::cout << "List is empty\n";
		return;
	}

	Node* current = head;

	while (current != nullptr) {
		std::cout << current->data << " ";
		current = current->next;
	}
	std::cout << "\n";
}

template<typename T>
typename List<T>::Iterator& List<T>::Begin() {
	Iterator temp(head);
	return temp;
}

template<typename T>
typename List<T>::Iterator& List<T>::End() {
	Iterator temp(tail->next);
	return temp;
}