/**
@file asd.cc

Plik do modyfikacji w w ramach cwiczenia 4 z AISDI.
Zawiera niekompletne implementacje metod klasy TreeMap.
Jest tez prosta funkcja testujaca (void test()), ktora
jest wolana w funkcji main. Mozna w niej zaimplementowac
wlasne testy.
NALEZY ZMODYFIKOWAC I UZUPELNIC CIALA METOD KLASY TreeMap.

@author
Pawel Cichocki, Michal Nowacki

@date
last revision
- 2005.12.01 Pawel Cichocki: TreeNodeDetail class
- 2005.12.01 Michal Nowacki: lab #4
- 2005.11.17 Michal Nowacki: lab #3, copy operator and constructor
- 2005.11.04 Pawel Cichocki: copied comments from the header
- 2005.11.03 Pawel Cichocki: const_iterator done properly now
- 2005.10.27 Pawel Cichocki: cosmetic changes
- 2005.10.26 Michal Nowacki: removed some method bodies
- 2005.10.25 Pawel Cichocki: wrote it

COPYRIGHT:
Copyright (c) 2005 Instytut Informatyki, Politechnika Warszawska
ALL RIGHTS RESERVED
*******************************************************************************/

#include "stdafx.h"
#include <assert.h>
#include <algorithm>

#include <iostream>

#include "TreeMap.h"

static TreeMap::Val DEFAULT_VALUE = "Automatically generated node";
static TreeMap::Key DEFAULT_KEY = -1;

/// A helper class.
class TreeMapDetail //Helper
{
protected:
    friend class TreeMap;

    /// Stupid example of a method that modifies a protected field in 
    /// the TreeMap class. Feel free to remove this method or add new
    /// ones here.
    static void erase (TreeMap* tm, const TreeMap::Key& k) {
        tm->root = NULL; // we just modified a protected field in tree map
    }
};

//////////////////////////////////////////////////////////////////////////////
// TreeMap and TreeMap::iterator methods
//////////////////////////////////////////////////////////////////////////////

/*ToDo:
 -> konstruktorki
 -> ew destruktorka, w zaleznosci od rozwiazania kwiestii roota
 -> unsafe_insert
 -> findy
 -> erase
 -> =
 -> end
 -> eqi prawie napewno sie sypna :c*/


TreeMap::TreeMap () {
    root = NULL;
    TreeNode * sentinel = new TreeNode (std::make_pair(DEFAULT_KEY, DEFAULT_VALUE));
    sentinel->left = root;
};

/// Content of existing TreeMap object is copied into the new object. 
TreeMap::TreeMap (const TreeMap& m) {
    ///@todo Implement this
};

TreeMap::~TreeMap () {
    clear ();
};

// Inserts an element into the map.
// @returns A pair whose bool component is true if an insertion was
//          made and false if the map already contained an element
//          associated with that key, and whose iterator component coresponds to
//          the address where a new element was inserted or where the element
//          was already located.
std::pair<TreeMap::iterator, bool> TreeMap::insert (const std::pair<Key, Val>& entry) {
    iterator insertIterator = find (entry.first);

    if (insertIterator == end ())                                        //nie ma jeszcze takiego klucza
        return std::make_pair (unsafe_insert (entry), (bool)true);

    return std::make_pair (insertIterator, (bool)false);
}

// Inserts an element into the map.
// This method assumes there is no value asociated with
// such a key in the map.

TreeMap::iterator TreeMap::unsafe_insert (const std::pair<Key, Val>& entry) {
    ///@todo  Finnish this
    assert (0);
    return iterator (root);
}

// Returns an iterator addressing the location of the entry in the map
// that has a key equivalent to the specified one or the location succeeding the
// last element in the map if there is no match for the key.
TreeMap::iterator TreeMap::find (const Key& k) {
    ///@todo Implement this
    assert (0);
    return end ();
}

TreeMap::const_iterator TreeMap::find (const Key& k) const {
    ///@todo Implement this
    assert (0);
    return end ();
}

// Inserts an element into a map with a specified key value
// if one with such a key value does not exist.
// @returns Reference to the value component of the element defined by the key.
TreeMap::Val& TreeMap::operator[](const Key& k) {
    iterator found = find (k);

    if (found == end ())
        found = unsafe_insert (std::make_pair (k, DEFAULT_VALUE));

    return found->second;
}

// Tests if a map is empty.
bool TreeMap::empty () const {
    return (begin ()) == end ();
}

// Returns the number of elements in the map.
TreeMap::size_type TreeMap::size () const {
    TreeMap::size_type number = 0;

    for (const_iterator i = begin (); i != end (); i++)
        number++;

    return number;
}

// Returns the number of elements in a map whose key matches a parameter-specified key.
TreeMap::size_type TreeMap::count (const Key& _Key) const {
    if (find (_Key) == end ())
        return 0;

    return 1;  // this is not a multimap
}

// Removes an element from the map.
// @returns The iterator that designates the first element remaining beyond any elements removed.
TreeMap::iterator TreeMap::erase (TreeMap::iterator i) {
    ///@todo Implement this
    assert (0);
    return end ();
}

// Removes a range of elements from the map.
// The range is defined by the key values of the first and last iterators
// first is the first element removed and last is the element just beyond the last elemnt removed.
// @returns The iterator that designates the first element remaining beyond any elements removed.
TreeMap::iterator TreeMap::erase (TreeMap::iterator f, TreeMap::iterator l) {
    ///@todo Implement this
    assert (0);
    return end ();
}

// Removes an element from the map.
// @returns The number of elements that have been removed from the map.
//          Since this is not a multimap itshould be 1 or 0.
TreeMap::size_type TreeMap::erase (const Key& key) {
    iterator toKill = find (key);

    if (toKill != end ()) {
        erase (toKill);
        return 1;
    }

    return 0;
}

// Erases all the elements of a map.
void TreeMap::clear () {
    TreeMapDetail::erase (this, 0);

    erase (begin (), end ());
}

bool TreeMap::struct_eq (const TreeMap& another) const {
    if (size () != another.size ())
        return false;

    const_iterator thisIterator = begin ();
    const_iterator anotherIterator = another.begin ();

    while (thisIterator != end ()) {

        if (thisIterator.node->data != anotherIterator.node->data)
            return false;

        ++thisIterator;
        ++anotherIterator;
    }

    return true;
}

//@ACHTUNG kk this is so random i dont believe its actually gonna work, but its good for start
bool TreeMap::info_eq (const TreeMap& another) const {
    if (size () != another.size ())
        return false;

    const_iterator thisIterator = begin ();

    while (thisIterator != end ()) {

        if (another.find (thisIterator->first) == another.end () || another.find (thisIterator->first)->second != thisIterator->second) {
            std::cout << "\nWykrzaczing with parameters:\n"
                << "another.find (thisIterator->first) == another.end () has value of: " << (another.find (thisIterator->first) == another.end ())
                << "\nanother.find (thisIterator->first)->second != thisIterator->second) has value of: " << (another.find (thisIterator->first)->second != thisIterator->second)
                << "\n\nWykrzaczejszyn executed for parameters:"
                << "\nFor this: key == " << thisIterator->first << ", value == " << thisIterator->second << "\n\n";
            return false;
        }

        thisIterator++;
    }

    return true;
}

// preincrement
TreeMap::const_iterator& TreeMap::const_iterator::operator ++() {
    if (node->parent == NULL)
        return *this;

    if (node->right != NULL) {
        node = node->right;
        
        while (node->left != NULL) {
            node = node->left;
        }
        
        return *this;
    }

    if (node->parent->left == node) {
        node = node->parent;
        return *this;
    }

    //return end:
    do {                       //zrobic tak, ze root to left sentinela zapamietaj!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        node = node->parent;
    }
    while (node->parent->right == node);

    return *this;
}

// postincrement
TreeMap::const_iterator TreeMap::const_iterator::operator++(int) {
    const_iterator notIncremented (node);    //Trzeba zinkrementowac, ale zwrocic sprzed inkrementacji
    ++(*this);
    return notIncremented;
}

// predecrement
TreeMap::const_iterator& TreeMap::const_iterator::operator--() {
    if (node->parent == NULL) {                 //if end we must reach last elemento
        node = node->left;
        while (node->right != NULL) {
            node = node->right;
        }
    }

    if (node->left != NULL) {
        node = node->left;

        while (node->right != NULL) {
            node = node->right;
        }

        return *this;
    }

    if (node->parent->right == node) {
        node = node->parent;
        return *this;
    }

    //first element, return itself:
    return *this;
}

// postdecrement
TreeMap::const_iterator TreeMap::const_iterator::operator--(int) {
    const_iterator notDecremented (node);
    --(*this);
    return notDecremented;
}


/// Assignment operator copy the source elements into this object.
TreeMap& TreeMap::operator=(const TreeMap& other) {
    ///@todo Implement this
    return *this;
}

/// Returns an iterator addressing the first element in the map
TreeMap::iterator TreeMap::begin () {
    Node * actualNode = root;

    while (actualNode->left != NULL) {
        actualNode = actualNode->left;
    }

    return iterator (actualNode);
}

TreeMap::const_iterator TreeMap::begin () const {
    Node * actualNode = root;

    while (actualNode->left != NULL) {
        actualNode = actualNode->left;
    }

    return const_iterator (actualNode);
}

/// Returns an iterator that addresses the location succeeding the last element in a map
TreeMap::iterator TreeMap::end () {
    ///@todo Implement this
    return iterator (NULL);
}

/// Returns an iterator that addresses the location succeeding the last element in a map
TreeMap::const_iterator TreeMap::end () const {
    ///@todo Implement this
    return iterator (NULL);
}

//////////////////////////////////////////////////////////////////////////////
// Tests
//////////////////////////////////////////////////////////////////////////////

/// A helper function that outputs a key-value pair.
void print (const std::pair<int, std::string>& p) {
    std::cout << p.first << ", " << p.second << std::endl;
}

#include <map>

/// The big mean test function ;)
void test () {
    // A typedef used by the test.
    typedef std::map<int, std::string> TEST_MAP;
    //typedef SmallMap<int, std::string> TEST_MAP;
    //typedef TreeMap TEST_MAP;

    std::cout << "Testy uzytkownika" << std::endl;

    TEST_MAP m;

    m[2] = "Merry";
    m[4] = "Jane";
    m[8] = "Korwin Krul";
    m[4] = "Magdalena";

    for_each (m.begin (), m.end (), print);
    //system("PAUSE");

}

//////////////////////////////////////////////////////////////////////////////
// main - jest w pliku /materialy/AISDI/z2/main.cc
//////////////////////////////////////////////////////////////////////////////

//int main()
//{
//   std::cout << "AISDI cwiczenie 4: wchodze do funkcji main." << std::endl;

//   test();
//   // Biblioteka z bardziej rygorystyczna wersja tych testow bedzie udostepniona na nastepnych zajeciach.
//   Test2();
//   //system("PAUSE");
//   return EXIT_SUCCESS;
//}
