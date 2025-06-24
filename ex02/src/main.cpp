//
// Created by Eliam on 23/06/2025.
//

#include <iostream>
#include "../includes/PmergeMe.hpp"

long timeDiffMicroseconds(const timeval& start, const timeval& end)
{
	return (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec);
}

void printBefore(int argc, char **argv)
{
	for (int i = 1; i < argc; i++)
		std::cout << argv[i] << " ";
	std::cout << std::endl;
}

void printList(const std::list<int>& lst)
{
	std::list<int>::const_iterator it;
	for (it = lst.begin(); it != lst.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

int main(int argc, char **argv)
{
    // Vérification du nombre d'arguments
    if (argc < 2)
    {
        std::cerr << RED << "Usage: " << argv[0] << " <list of numbers>" << RESET << std::endl;
        return 1;
    }

    Pmerge sort;
    struct timeval start, end;

    // Tri avec std::list et mesure du temps
    gettimeofday(&start, NULL);
    std::list<int> lt = sort.sortList(argc, argv);
    gettimeofday(&end, NULL);
    long elapsed_us = timeDiffMicroseconds(start, end);

    std::cout << "Before :   ";
    printBefore(argc, argv);
    std::cout << "After :    ";
    printList(lt);
    std::cout << "Time to process a range of " << argc - 1 << " elements with std::list : " << elapsed_us << " us" << std::endl;

    // Tri avec std::vector et mesure du temps
    gettimeofday(&start, NULL);
    sort.sortVector(argc, argv);
    gettimeofday(&end, NULL);
    elapsed_us = timeDiffMicroseconds(start, end);
    std::cout << "Time to process a range of " << argc - 1 << " elements with std::vector : " << elapsed_us << " us" << std::endl;

    return 0;
}