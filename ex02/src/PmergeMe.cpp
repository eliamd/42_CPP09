//
// Created by Eliam on 23/06/2025.
//

#include "../includes/PmergeMe.hpp"
#include <ostream>

#include <climits>
#include <cmath>
#include <cstddef>

Pmerge::Pmerge() {}

Pmerge::Pmerge( Pmerge const &other ) {*this = other;}

Pmerge & Pmerge::operator=( Pmerge const &other )
{
	if (this != &other)
	{
		_lt = other._lt;
		_vt = other._vt;
	}
	return *this;
}

Pmerge::~Pmerge() {}

void ListfordJohnsonSort(std::list<int>& lst) {
	if (lst.size() <= 1)
		return;

	std::list<std::pair<int, int> > pairs;
	std::list<int>::iterator it = lst.begin();

	// verif impaire
	int leftover = -1;
	bool hasLeftover = false;

	// creation des paires en ordre croissant
	while (it != lst.end()) {
		int first = *it;
		++it;

		if (it != lst.end()) {
			int second = *it;
			++it;
			if (first > second)
				std::swap(first, second);
			pairs.push_back(std::make_pair(first, second));
		} else {
			// si impaire, garde l'element seul pour l'inserer a la fin
			leftover = first;
			hasLeftover = true;
		}
	}

	// tri des seconds
	std::list<int> sortedSeconds;
	std::list<std::pair<int, int> >::iterator pit;
	for (pit = pairs.begin(); pit != pairs.end(); ++pit)
		sortedSeconds.push_back(pit->second);
	ListfordJohnsonSort(sortedSeconds);

	// insert des first dans l'ordre
	for (pit = pairs.begin(); pit != pairs.end(); ++pit) {
		int small = pit->first;
		std::list<int>::iterator pos = sortedSeconds.begin();
		while (pos != sortedSeconds.end() && *pos <= small)
			++pos;
		sortedSeconds.insert(pos, small);
	}

	// insert de l'element seul a la bonne place
	if (hasLeftover) {
		std::list<int>::iterator pos = sortedSeconds.begin();
		while (pos != sortedSeconds.end() && *pos <= leftover)
			++pos;
		sortedSeconds.insert(pos, leftover);
	}


	lst = sortedSeconds;
}

std::list<int> Pmerge::sortList( int vl, char **value )
{
	for (int i = 1; i < vl; ++i)
	{
		long v = std::atol(value[i]);
		if (v > INT_MAX || v < 0)
		{
			std::cerr << "Error: '" << v << "'. Value is either < 0 or > INT_MAX." << std::endl;
			return std::list<int>();
		}
		_lt.push_back(v);
	}
	ListfordJohnsonSort(_lt);
	return _lt;
}

void VectorfordJohnsonSort(std::vector<int>& arr) {
	int n = arr.size();
	if (n <= 1) return;

	std::vector<std::pair<int, int> > pairs;
	std::vector<int> leftovers;

	// creation des paires en ordre croissant
	for (int i = 0; i + 1 < n; i += 2) {
		int a = arr[i];
		int b = arr[i + 1];
		if (a > b) std::swap(a, b);
		pairs.push_back(std::make_pair(a, b));
	}

	// verif impaire
	if (n % 2 == 1)
		leftovers.push_back(arr[n - 1]);

	// tri des seconds
	std::vector<int> maxElements;
	for (std::size_t i = 0; i < pairs.size(); ++i)
		maxElements.push_back(pairs[i].second);
	VectorfordJohnsonSort(maxElements);

	// creation de la liste result avec les seconds
	std::vector<int> result = maxElements;

	// insert first
	for (std::size_t i = 0; i < pairs.size(); ++i) {
		int small = pairs[i].first;
		std::vector<int>::iterator pos = std::upper_bound(result.begin(), result.end(), small);
		result.insert(pos, small);
	}

	// insert impaire
	for (std::size_t i = 0; i < leftovers.size(); ++i) {
		std::vector<int>::iterator pos = std::upper_bound(result.begin(), result.end(), leftovers[i]);
		result.insert(pos, leftovers[i]);
	}

	arr = result;
}

void Pmerge::sortVector( int vl, char **value )
{
	for (int i = 1; i < vl; ++i)
	{
		long v = std::atol(value[i]);
		if (v > INT_MAX || v < 0)
		{
			std::cerr << "Error: '" << v << "'. Value is either < 0 or > INT_MAX." << std::endl;
			return ;
		}
		_vt.push_back(v);
	}
	VectorfordJohnsonSort(_vt);
}
