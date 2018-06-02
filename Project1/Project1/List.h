#pragma once

#include "Flags.h"
//#include "Functions.h"
//#include "Logs.h"

#include <iostream>
#include <iomanip>      // std::setw
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

template <typename Type>
class List
{
public:

	void show(int details = 0) const;				// Function show all elements from list in console.
	void show_back() const;			// Function show all elements from list in console.
	void showHorizontally() const;	// Function show all elements from list in console
	bool empty() const;
	int get_size();
	
	bool find(Type value);
	int find_index_of_value(int value);
	void edit_value_at(int index, Type new_value);
	Type get_value_at(int index);
	Type top() const;
	
	void push_front(Type value);
	void push_back(Type value);
	void push_random_place(Type value);
	void push_at(const unsigned int index, Type value);

	void pop_front();
	void pop_back();
	void pop_random_place();
	void pop_at(int index);
	void pop_value(Type value);
	
	List<Type>();
	~List<Type>();

private:
	class element
	{
	public:
		element *next;
		element *previous;
		Type value;

		element(element *previousElement, element *nextElement, Type valueOfElement)
		{
			next = nextElement;
			previous = previousElement;
			value = valueOfElement;
		}

		element()
		{
			next = NULL;
			previous = NULL;
		}
	};	

	bool isEmpty;		// flag is set when list is empty 
	unsigned int size;
	element *first;		// pointer on the first element
	element *last;		// pointer on the last element
};

template<typename Type>
	inline void List<Type>::show(int details) const
	{
		int counter = 0;
		element *ptr;
		ptr = first;

		while (ptr != NULL)
		{
			if (details == 0)
			{
				std::cout << std::setw(5) << counter << " -->  " << ptr->value << std::endl;

				ptr = ptr->next;

				counter++;
			}
			else if (details == 1)
			{
				std::cout << std::setw(5) << counter << " -->  " << ptr->value << " Previous ptr " << ptr->previous 
				<< " Next ptr " << ptr->next << std::endl;

				ptr = ptr->next;

				counter++;
			}
			else
			{
				#ifdef SHOW_ERROR
				std::cout << "ERROR: List<Type>::show(): Wrong argument." << std::endl;
				#endif // SHOW_ERROR
				return;
			}
		}
	}

template<typename Type>
	inline void List<Type>::show_back() const
	{
		int counter = size-1;
		element *ptr;
		ptr = last;

		while (ptr != NULL)
		{
			std::cout << std::setw(5) << counter << " -->  " << ptr->value << std::endl;
			ptr = ptr->previous;
			counter--;
		}
	}

template<typename Type>
	inline void List<Type>::showHorizontally() const
	{
		element *ptr;
		ptr = first;

		while (ptr != NULL)
		{
			std::cout << std::setw(6) << ptr->value;
			ptr = ptr->next;
		}
	}

template<typename Type>
	inline bool List<Type>::empty() const
	{
		if (first == NULL)
			return true;
		else
			return false;
	}

template<typename Type>
	inline int List<Type>::get_size()
	{
		int counter = 0;

		element *ptr = first;
		while (ptr != NULL)
		{
			counter++;
			ptr = ptr->next;
		}
		return counter;
	}

template<typename Type>
	inline Type List<Type>::top() const
	{
		if (empty() == true)
		{
			#ifdef SHOW_LOGS
			cout << "LOG: list: function \"top\" return NUll as 0" << endl;
			#endif // SHOW_LOGS

			return 0;
		}

		return last->value;
	}

template<typename Type>
	inline bool List<Type>::find(Type value)
	{
		element *temp = first;
		
		while (temp != NULL)
		{
			if (temp->value == value)
			{
				return true;
			}
			temp = temp->next;
		}

		return false;
	}

template<typename Type>
	inline int List<Type>::find_index_of_value(int value)
	{
		element *temp = first;
		int index = 0;

		while (temp != NULL)
		{
			if (temp->value == value)
			{
				return index;
			}
			temp = temp->next;
			index++;
		}
		return -1;
	}

template<typename Type>
	inline void List<Type>::edit_value_at(int index, Type new_value)
	{
		element *ptr = first;
		for (int i = 0; ptr != NULL && i < index; i++)
		{
			ptr = ptr->next;
		}

		if (ptr == NULL)
		{

			#ifdef SHOW_LOGS
			cout << "LOG: list: function \"edit_value_at\" can't find element in list" << endl;
			#endif // SHOW_LOGS

			return;
		}

		ptr->value = new_value;
		return;
	}

template<typename Type>
	inline void List<Type>::push_front(Type newElement)
	{
		#ifdef LOG_LIST
		std::cout << "--> push_front(" << newElement << ") has been called" << std::endl;
		#endif // LOG_LIST

		if (first == NULL)
		{
			first = new element(NULL, NULL, newElement);
			last = first;
		}
		else
		{
			element *temp = first;
			first = new element(NULL, temp, newElement);
			temp->previous = first;

		}

		size++;
	}

template<typename Type>
	inline void List<Type>::push_back(Type value)
	{
		#ifdef LOG_LIST
			cout << "--> push_back(" << value << ") has been called" << endl;
		#endif // LOG_LIST

		if (last == NULL)
		{
			last = new element(NULL, NULL, value);
			first = last;
		}
		else
		{
			element *temp = last;
			last = new element(temp, NULL, value);
			last->next = NULL;
			last->previous = temp;
			last->value = value;

			temp->next = last;
		}
		size++;
	}

template<typename Type>
	inline void List<Type>::push_random_place(Type value)
	{
		#ifdef LOG_LIST
			cout << "--> push_random_place(" <<value << ") has been called" << endl;
		#endif // LOG_LIST

		if (size == 0)
		{
			push_front(value);
			return;
		}

		int index = rand() % size;

		push_at(index, value);

	}

template<typename Type>
	inline void List<Type>::push_at(const unsigned int index, Type value)
	{
		#ifdef LOG_LIST
		cout << "--> push_at(" << index << "," << value << ") has been called" << endl;
		#endif // LOG_LIST

		if (size == 0)
		{
			push_front(value);
			return;
		}else
		if (index >= size)
		{
			push_back(value);
			return;
		}
		else
		if (index == 0)
		{
			push_front(value);
			return;
		}
		else
		if (index == size - 1)
		{
			push_back(value);
			return;
		}
		else
		{
			//
			//if the index is closer to the end than the beginning,
			//we start iterations from the back
			//

			if (index > (size / 2))
			{
				element* ptr = last;
				int back_index = size - index;

				for (int i = 0; i < back_index-1 ; i++)
				{
					ptr = ptr->previous;
				}

				element *temp = new element();

				temp->next = ptr;
				temp->previous = ptr->previous;


				ptr->previous = temp;
				temp->previous->next = temp;

				temp->value = value;
			}
			else
			{
				element* ptr = first;
				for (int i = 0; i < index; i++)
				{
					ptr = ptr->next;
				}

				element *temp = new element();

				temp->next = ptr;
				temp->previous = ptr->previous;


				ptr->previous = temp;
				temp->previous->next = temp;

				temp->value = value;
			}

			size++;
			return;
		}
	}

template<typename Type>
	inline void List<Type>::pop_front()
	{
		#ifdef LOG_LIST
			cout << "--> pop_front() has been called" << endl;
		#endif // LOG_LIST

		if (first != NULL)
		{
			if (last == first)
			{
				delete first;
				first = NULL;
				last = NULL;
			}
			else
			{
				element *temp = first;
				first = first->next;
				first->previous = NULL;
				delete temp;
			}
			size--;
		}
		else
		{
			#ifdef SHOW_LOGS
			cout << "LOG: list: can't call pop() on list. List is empty" << endl;
			#endif // SHOW_LOGS
		}
	}

template<typename Type>
	inline void List<Type>::pop_back()
	{
		#ifdef LOG_LIST
		cout << "--> pop_back() has been called" << endl;
		#endif // LOG_LIST

		if (last != NULL)
		{
			if (last == first)
			{
				delete first;
				first = NULL;
				last = NULL;
			}
			else
			{
				element *temp = last;
				last = last->previous;
				last->next = NULL;
				delete temp;
			}
			size--;
		}
		else
		{
			#ifdef SHOW_LOGS
			cout << "LOG: list: can't call pop() on list. List is empty" << endl;
			#endif // SHOW_LOGS
		}
		
	}

template<typename Type>
	inline void List<Type>::pop_random_place()
	{
		#ifdef LOG_LIST
		cout << "--> pop_random_place() has been called" << endl;
		#endif // LOG_LIS

		if (empty() == false)
		{
			int index = 255;
			if (size != 0)
			{
				index = rand() % (size);
			}	

			#ifdef LOG_LIST
			cout << "\tsize: " << size << endl;
			cout << "\t pop from index nr: " << index << endl;
			#endif // LOG_LIS

			if (last == first)
			{
				delete first;
				first = NULL;
				last = NULL;
				size--;
			}
			else
			{
				
				element *temp = first;
				while (index != 0 && --index)
				{
					temp = temp->next;
				}

				if (temp->next == NULL)
				{
					pop_back();
				}else
				if (temp->previous == NULL)
				{
					pop_front();
				}
				else
				{
					temp->next->previous = temp->previous;
					temp->previous->next = temp->next;
					delete temp;
					size--;
				}
			}

			
		}
		else
		{
			#ifdef SHOW_LOGS
			cout << "LOG: list: can't call pop() on list. List is empty" << endl;
			#endif // SHOW_LOGS
		}
	}

template<typename Type>
	inline void List<Type>::pop_at(int index)
	{
		#ifdef LOG_LIST
		cout << "--> pop_at(" << index << ") has been called" << endl;
		#endif // LOG_LIS

		if (empty() == true)
		{
			#ifdef SHOW_MESSAGES
			cout << "--> pop_at(" << index << ") List is empty" << std::endl;
			#endif // SHOW_MESSAGES
		}

		if (index == 0)
		{
			pop_front();
			
			return;
		}

		if (index == (get_size()-1))
		{
			pop_back();

			return;
		}

		element *temp = first;

		while (index--)
		{
			temp = temp->next;

			if (temp == NULL)
			{
				#ifdef SHOW_ERROR
				std::cout << "ERROR: Graph::pop_at(" << index << "), index out of range.\n";
				#endif //SHOW_ERROR
				return;
			}
		}

		temp->next->previous = temp->previous;

		temp->previous->next = temp->next;

		delete temp;

		size--;

		return;
	}

template<typename Type>
	inline void List<Type>::pop_value(Type value)
	{
		#ifdef LOG_LIST
		cout << "--> pop_value(" << value << ") has been called" << endl;
		#endif // LOG_LIS

		element *temp = first;

		int index = 0;

		while (temp != NULL)
		{
			if (temp->value == value)
			{
				pop_at(index);

				break;
			}

			temp = temp->next;

			index++;
		}
	}

template<typename Type>
	inline Type List<Type>::get_value_at(int index)
	{
		element *ptr = first;
		for (int i = 0; ptr !=NULL && i < index; i++)
		{
			ptr = ptr->next;
		}

		if (ptr == NULL)
		{
			#ifdef LOG_LIST
			cout << "ERROR: Linia  " << __LINE__ << " List.h" << endl;
			#endif // LOG_LIST

			#ifdef SHOW_LOGS
			cout << "LOG: list: function \"get_value_at\" return NUll as 0" << endl;
			#endif // SHOW_LOGS
			
			return Type(-1);
		}
		return ptr->value;
	}

template<typename Type>
	inline List<Type>::List()
	{
		isEmpty = true;
		first = NULL;
		last = NULL;
		size = 0;

		//
		//initialize random seed
		//It is unign guring push and pop value in random pleace in struct
		//
		srand(time(NULL));
	}

template<typename Type>
	inline List<Type>::~List()
	{
		int counter = 0;
		while (first != NULL)
		{
			pop_front();

			#ifdef SHOW_LOGS
			cout << "delete counter: " << counter++ << endl;
			#endif // SHOW_LOGS
		}
	}