/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 20:39:01 by mtelek            #+#    #+#             */
/*   Updated: 2025/09/14 20:39:01 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Algorithm.hpp"

bool validArgs(int argc, char **argv)
{
	if (argc < 2)
		return (std::cerr << "Error: Parameters needed\n", false);

	for (int i = 1; i < argc; i++)
	{
		std::string str(argv[i]);

		if (str.empty())
			return (std::cerr << "Error: Invalid parameter\n", false);
		size_t start = 0;
		if (str[0] == '+')
		{
			if (str.size() == 1)
				return (std::cerr << "Error: Invalid parameter\n", false);
			start = 1;
		}
		for (size_t j = start; j < str.size(); j++)
		{
			if (!std::isdigit(str[j]))
				return (std::cerr << "Error: Invalid parameter\n", false);
		}
	}
	return (true);
}

int main(int argc, char **argv)
{
	if (!validArgs(argc, argv))
		return (1);

	//VECTOR
	{
		Algorithm<std::vector<int> > Vector;
		if (Vector.makingContainer(argv))
			return (1);
		std::cout << "Before: ";
		Vector.printContainer();
		clock_t start = clock();
		Vector.run();
		clock_t end = clock();
		std::cout << "After: ";
		Vector.printContainer();
		double duration = 1e6 * (double)(end - start) / CLOCKS_PER_SEC;
		std::cout << "Time to process a range of " << Vector.getSize() << " elements with std::vector: "
					<< std::fixed << std::setprecision(5) << duration << " us\n";
		if (!Vector.is_sorted())
			std::cout << "Error: Vector container have not been sorted correctly\n";
	}
	//DEQUE
	{
		Algorithm<std::deque<int> > Deque;
		Deque.makingContainer(argv);
		clock_t start = clock();
		Deque.run();
		clock_t end = clock();

		double duration = 1e6 * (double)(end - start) / CLOCKS_PER_SEC;
		std::cout << "Time to process a range of " << Deque.getSize() << " elements with std::deque: "
					<< std::fixed << std::setprecision(5) << duration << " us\n";
		if (!Deque.is_sorted())
			std::cout << "Error: Deque container have not been sorted correctly\n";
		std::cout << "Number of comparisons made per container: " << Deque.getComp() << std::endl;
	}
	return (0);
}
