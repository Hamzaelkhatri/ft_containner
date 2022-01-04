#ifndef STACK_HPP
#define STACK_HPP

#include "./vector.hpp"

class vector;
namespace ft
{
    template <class T, class Container = ft::vector<T> >
    class	stack
    {
    public:
		typedef T value_type;
		typedef size_t size_type;
		typedef Container container_type;
		// default constructor / constructor with parameter
		explicit stack(const container_type &ctnr = container_type()) 
		{
			c = ctnr;
		}

		// destructor
		virtual ~stack() {}

		// Member functions

		bool empty(void) const
		{
			return (this->c.empty());
		}
		size_t size(void) const
		{
			return (this->c.size());
		}

		value_type &top(void)
		{
			return (this->c.back());
		}

		value_type const &top(void) const
		{
			return (this->c.back());
		}

		void push(value_type const &val)
		{
			this->c.push_back(val);
		}

		void pop(void)
		{
			this->c.pop_back();
		}

		template <typename T1, typename T2>
		friend bool operator==(stack< T1, T2> const &lhs, stack< T1, T2> const &rhs);

		template <typename T1, typename T2>
		friend bool operator!=(stack< T1, T2> const &lhs, stack< T1, T2> const &rhs);

		template <typename T1, typename T2>
		friend bool operator<(stack< T1, T2> const &lhs, stack< T1, T2> const &rhs);

		template <typename T1, typename T2>
		friend bool operator<=(stack< T1, T2> const &lhs, stack< T1, T2> const &rhs);

		template <typename T1, typename T2>
		friend bool operator>(stack< T1, T2> const &lhs, stack< T1, T2> const &rhs);

		template <typename T1, typename T2>
		friend bool operator>=(stack< T1, T2> const &lhs, stack< T1, T2> const &rhs);

	protected:
		Container c;
	}; 
    // class stack
	// Non-member funT2ion overloads for the stack class

	template <typename T1, typename T2>
	bool operator==(stack <T1, T2> const &lhs, stack <T1, T2> const &rhs)
	{
		return (lhs.c == rhs.c);
	}

	template <typename T1, typename T2>
	bool operator!=(stack< T1, T2> const &lhs, stack <T1, T2> const &rhs)
	{
		return (lhs.c != rhs.c);
	}

	template <typename T1, typename T2>
	bool operator<(stack <T1, T2> const &lhs, stack <T1, T2> const &rhs)
	{
		return (lhs.c < rhs.c);
	}

	template <typename T1, typename T2>
	bool operator<=(stack< T1, T2> const &lhs, stack <T1, T2> const &rhs)
	{
		return (lhs.c <= rhs.c);
	}

	template <typename T1, typename T2>
	bool operator>(stack< T1, T2> const &lhs, stack <T1, T2> const &rhs)
	{
		return (lhs.c > rhs.c);
	}

	template <typename T1, typename T2>
	bool operator>=(stack <T1, T2> const &lhs, stack <T1, T2> const &rhs)
	{
		return (lhs.c >= rhs.c);
	}
} // namespace ft

#endif