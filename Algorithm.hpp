/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Algorithm.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 20:38:57 by mtelek            #+#    #+#             */
/*   Updated: 2025/09/14 20:38:57 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AlGORITHM_HPP
#define AlGORITHM_HPP

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <deque>
#include <set>
#include <ctime>
#include <iomanip>

#define LIMIT 3000

template <typename Container>
class Algorithm
{
	private:
		Container con;
		Container main;
		Container pend;
		Container rest;
		Container Jacobsthal;
		std::vector<std::pair<Container, int> > a;
		std::vector<std::pair<Container, int> > b;
		size_t pair_size;
		
		//ALGORITHM
		void getJacobsthal();
		void fordJohnson(bool &upscale);
		void performUpscale();
		void performDownscale();
		void switch_posi(size_t posi, size_t block_len);
		void fillUpMain();
		void fillUpPend();
		void fillUpRest();
		void groupMain(size_t block_len);
		void groupPend(size_t block_len);
		void InsertPend();
		size_t binarySearch(size_t block_len, const Container& numbers, size_t boundary);
		size_t findBoundary(int group_number);
		
		public:
		Algorithm();
		~Algorithm();
		Algorithm(const Algorithm &other);
		Algorithm &operator=(const Algorithm &other);
		
		int run();
		int	makingContainer(char **argv);
		void printContainer();
		bool is_sorted();
		size_t getSize() const;
};

#include "Algorithm.cpp"

#endif
