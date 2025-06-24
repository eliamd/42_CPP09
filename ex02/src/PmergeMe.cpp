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

    // Variables pour gérer un éventuel élément restant (si taille impaire)
    int leftover = -1;
    bool hasLeftover = false;

    // Création des paires de la liste (toujours dans l'ordre croissant)
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
            // Si un élément reste seul, on le garde pour l'insérer à la fin
            leftover = first;
            hasLeftover = true;
        }
    }

    // On trie récursivement les seconds de chaque paire
    std::list<int> sortedSeconds;
    std::list<std::pair<int, int> >::iterator pit;
    for (pit = pairs.begin(); pit != pairs.end(); ++pit)
        sortedSeconds.push_back(pit->second);
    ListfordJohnsonSort(sortedSeconds);

    // On insère les premiers éléments de chaque paire à leur place
    for (pit = pairs.begin(); pit != pairs.end(); ++pit) {
        int small = pit->first;
        std::list<int>::iterator pos = sortedSeconds.begin();
        while (pos != sortedSeconds.end() && *pos <= small)
            ++pos;
        sortedSeconds.insert(pos, small);
    }

    // Si un élément était seul, on l'insère à la bonne place
    if (hasLeftover) {
        std::list<int>::iterator pos = sortedSeconds.begin();
        while (pos != sortedSeconds.end() && *pos <= leftover)
            ++pos;
        sortedSeconds.insert(pos, leftover);
    }

    // On remplace la liste d'origine par la liste triée
    lst = sortedSeconds;
}

std::list<int> Pmerge::sortList( int vl, char **value )
{
    // Remplir la liste _lt avec les valeurs converties depuis les arguments
    for (int i = 1; i < vl; ++i)
    {
        long v = std::atol(value[i]);
        // Vérification des bornes pour chaque valeur
        if (v > INT_MAX || v < 0)
        {
            std::cerr << RED << "Error: '" << v << "'. Value is either < 0 or > INT_MAX." << std::endl;
            return std::list<int>();
        }
        _lt.push_back(v);
    }
    // Tri de la liste avec l'algorithme personnalisé
    ListfordJohnsonSort(_lt);
    return _lt;
}

void VectorfordJohnsonSort(std::vector<int>& arr) {
    int n = arr.size();
    if (n <= 1) return;

    // Création des paires de valeurs consécutives (toujours dans l'ordre croissant)
    std::vector<std::pair<int, int> > pairs;
    std::vector<int> leftovers;

    for (int i = 0; i + 1 < n; i += 2) {
        int a = arr[i];
        int b = arr[i + 1];
        if (a > b) std::swap(a, b);
        pairs.push_back(std::make_pair(a, b));
    }

    // Si la taille du tableau est impaire, on garde le dernier élément à part
    if (n % 2 == 1)
        leftovers.push_back(arr[n - 1]);

    // On trie récursivement les seconds de chaque paire
    std::vector<int> maxElements;
    for (std::size_t i = 0; i < pairs.size(); ++i)
        maxElements.push_back(pairs[i].second);
    VectorfordJohnsonSort(maxElements);

    // On commence la liste triée avec les seconds triés
    std::vector<int> result = maxElements;

    // Insertion des premiers éléments de chaque paire à leur place
    for (std::size_t i = 0; i < pairs.size(); ++i) {
        int small = pairs[i].first;
        std::vector<int>::iterator pos = std::upper_bound(result.begin(), result.end(), small);
        result.insert(pos, small);
    }

    // Insertion du dernier élément s'il y en avait un en trop
    for (std::size_t i = 0; i < leftovers.size(); ++i) {
        std::vector<int>::iterator pos = std::upper_bound(result.begin(), result.end(), leftovers[i]);
        result.insert(pos, leftovers[i]);
    }

    // On remplace le tableau d'origine par le tableau trié
    arr = result;
}

void Pmerge::sortVector( int vl, char **value )
{
    // Remplir le vecteur _vt avec les valeurs converties depuis les arguments
    for (int i = 1; i < vl; ++i)
    {
        long v = std::atol(value[i]);
        // Vérification des bornes pour chaque valeur
        if (v > INT_MAX || v < 0)
        {
            std::cerr << RED << "Error: '" << v << "'. Value is either < 0 or > INT_MAX." << std::endl;
            return ;
        }
        _vt.push_back(v);
    }
    // Tri du vecteur avec l'algorithme personnalisé
    VectorfordJohnsonSort(_vt);
}