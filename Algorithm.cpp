/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Algorithm.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 20:38:51 by mtelek            #+#    #+#             */
/*   Updated: 2025/09/14 20:38:51 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Algorithm.hpp"

template <typename Container>
Algorithm<Container>::Algorithm() {}

template <typename Container>
Algorithm<Container>::~Algorithm() {}

template <typename Container>
Algorithm<Container>::Algorithm(const Algorithm<Container> &other) : con(other.con), main(other.main), pend(other.pend),
	rest(other.rest), Jacobsthal(other.Jacobsthal), a(other.a), b(other.b), pair_size(other.pair_size) {}

template <typename Container>
Algorithm<Container> &Algorithm<Container>::operator=(const Algorithm<Container> &other)
{
	if (this != &other)
	{
		con = other.con;
		main = other.main;
		pend = other.pend;
		rest = other.rest;
		Jacobsthal = other.Jacobsthal;
		a = other.a;
		b = other.b;
		pair_size = other.pair_size;
	}
	return (*this);
}

template <typename Container>
size_t Algorithm<Container>::getSize() const  {return (con.size()); }

template <typename Container>
bool Algorithm<Container>::is_sorted()
{
	if (con.empty() || con.size() == 1)
		return (true);
	for (typename Container::const_iterator it = con.begin(); it != con.end()-1; ++it)
	{
		if (*it > *(it+1))
			return (false);
	}
	return (true);
}

template <typename Container>
void Algorithm<Container>::printContainer()
{
	size_t limit = con.size() > 30 ? 30 : con.size();
	if (con.size() > 30)
		std::cout << "[";

	for (size_t i = 0; i < limit; ++i)
	{
		std::cout << con[i];
		if (i != limit - 1)
			std::cout << " ";
	}

	if (con.size() > 30)
		std::cout << "..]";
	std::cout << std::endl;
}

template <typename Container>
int Algorithm<Container>::makingContainer(char **argv)
{
	argv++;
	while(*argv)
	{
		int num = std::atoi(*argv);
		con.push_back(num);
		argv++;
	}
	return (0);
}

template <typename Container>
void Algorithm<Container>::getJacobsthal()
{
	Jacobsthal.clear();
	Jacobsthal.push_back(1);
	Jacobsthal.push_back(3);
	
	int i = 2;
	int next = 0;
	while (Jacobsthal.back() < LIMIT)
	{
		next = Jacobsthal[i-1] + 2 * Jacobsthal[i-2];
		Jacobsthal.push_back(next);
		i++;
	}
}

template <typename Container>
void Algorithm<Container>::switch_posi(size_t posi, size_t block_len)
{
	int start = posi - block_len;
	int half_posi = posi - ((block_len+1) / 2);
	while (half_posi >= start)
	{
		std::swap(con[posi], con[half_posi]);
		posi--;
		half_posi--;
	}
}

template <typename Container>
size_t Algorithm<Container>::binarySearch(size_t block_len, const Container& numbers, size_t boundary)
{
	int key = numbers.back();
	size_t effective_size = std::min(boundary, main.size());
	size_t num_blocks = (effective_size + block_len - 1) / block_len;
	size_t left = 0;
	size_t right = num_blocks;
	while (left < right)
	{
		size_t mid = left + (right - left) / 2;
		size_t last_idx = std::min((mid + 1) * block_len, effective_size) - 1;

		if (main[last_idx] < key)
			left = mid + 1;
		else
			right = mid;
	}
	size_t insert_pos = left * block_len;
	if (insert_pos > effective_size)
		insert_pos = effective_size;
	return (insert_pos);
}

template <typename Container>
size_t Algorithm<Container>::findBoundary(int group_number)
{
	size_t boundary = main.size();
	int element = -1;
	for (typename std::vector<std::pair<Container, int> >::const_iterator it = a.begin();
		 it != a.end(); ++it)
	{
		if (it->second == group_number && !it->first.empty())
		{
			element = it->first.back();
			break;
		}
	}
	if (element != -1)
	{
		typename Container::iterator at = std::find(main.begin(), main.end(), element);
		if (at != main.end())
			boundary = (at - main.begin()+1);
	}
	return (boundary);
}

template <typename Container>
void Algorithm<Container>::InsertPend()
{
	size_t i = 1;
	while (i < Jacobsthal.size() && !b.empty())
	{
		typename std::vector< std::pair< Container, int > >::iterator it = b.end();
		while (it != b.begin())
		{
			--it;
			if (it->second <= Jacobsthal[i])
			{
				size_t boundary = findBoundary(it->second);
				size_t insertPos = binarySearch(pair_size / 2, it->first, boundary);
				main.insert(main.begin() + insertPos, it->first.begin(), it->first.end());
				con = main;
				con.insert(con.end(), rest.begin(), rest.end());
				it = b.erase(it);
				if (it == b.begin())
					break;
			}
		}
		++i;
	}
}

template <typename Container>
void Algorithm<Container>::groupMain(size_t block_len)
{
	a.clear();
	size_t posi = 2 * block_len;
	int a_n = 2;
	while (posi < main.size())
	{
		Container temp;
		size_t end = std::min(posi + block_len, main.size());
		for (size_t i = posi; i < end; ++i)
			temp.push_back(main[i]);
		a.push_back(std::make_pair(temp, a_n++));
		posi += block_len;
	}
}

template <typename Container>
void Algorithm<Container>::groupPend(size_t block_len)
{
	b.clear();
	int b_n = 2;

	for (size_t i = 0; i < pend.size(); i += block_len)
	{
		Container temp;
		size_t block_end = std::min(i + block_len, pend.size());

		for (size_t j = i; j < block_end; ++j)
			temp.push_back(pend[j]);
		b.push_back(std::make_pair(temp, b_n++));
	}
}

template <typename Container>
void Algorithm<Container>::fillUpMain()
{
	main.clear();
	size_t posi = 0;
	size_t end = pair_size / 2;
	bool first = true;
	while (posi <= con.size()-1)
	{
		size_t start = posi;
		while (con.size() >= end && end > start)
			main.push_back(con[start++]);
		if (first == true)
		{
			posi += pair_size / 2;
			end += pair_size / 2;
			first = false;
		}
		else if (first == false)
		{
			end += pair_size;
			posi += pair_size;
		}
	}
}

template <typename Container>
void Algorithm<Container>::fillUpPend()
{
	pend.clear();
	size_t start = pair_size;
	size_t posi = start;
	size_t end = pair_size + pair_size/2;
	while (posi <= con.size()-1)
	{
		size_t start = posi;
		while (con.size() >= end && end > start)
			pend.push_back(con[start++]);
		end +=pair_size;
		posi += pair_size;
	}
}

template <typename Container>
void Algorithm<Container>::fillUpRest()
{
	rest.clear();
	size_t remainder = con.size() % (pair_size / 2);
	if (remainder == 0)
		return ;
	size_t start = con.size() - remainder;
	size_t end = con.size();
	while (start < end)
		rest.push_back(con[start++]);
}

template <typename Container>
void Algorithm<Container>::performUpscale()
{
	for (size_t pos = pair_size - 1; pos < con.size(); pos += pair_size)
	{
		size_t half_pos = (pos + 1) - (pair_size / 2) - 1;
		if (con[pos] < con[half_pos])
			switch_posi(pos, pair_size - 1);
	}
}

template <typename Container>
void Algorithm<Container>::performDownscale()
{
	pair_size /= 2;
	fillUpMain();
	if (con.size() > 2)
	{
		groupMain(pair_size/2);
		rest.clear();
		fillUpRest();
		fillUpPend();
		groupPend(pair_size/2);
		InsertPend();
	}
}

template <typename Container>
void Algorithm<Container>::fordJohnson(bool &upscale)
{
	if (pair_size > con.size() && upscale)
		upscale = false;
	if (upscale)
	{
		performUpscale();
		pair_size *= 2;
	}
	else
	{
		performDownscale();
		if (pair_size == 2)
		{
			con = main;
			return;
		}
	}
	fordJohnson(upscale);
}

template <typename Container>
int Algorithm<Container>::run()
{
	if (!is_sorted())
	{
		getJacobsthal();
		pair_size = 2;
		bool upscale = true;
		fordJohnson(upscale);
	}
	return (0);
}
