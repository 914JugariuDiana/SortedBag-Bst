#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	currentFrequency = 1;
	cnode = bag.head;
	if (cnode != nullptr)
		while (cnode->leftChild != nullptr)
			cnode = cnode->leftChild;
}

TComp SortedBagIterator::getCurrent() {
	if (cnode == nullptr)
		throw exception();

	return cnode->value;
}

bool SortedBagIterator::valid() {
	if (cnode == nullptr)
		return false;
	return true;
}

void SortedBagIterator::next() {
	if (cnode == nullptr)
		throw exception();

	if (currentFrequency < cnode->frequency) {
		currentFrequency++;
		return;
	}

	currentFrequency = 1;
	if (cnode->rightChild != nullptr) {
		cnode = cnode->rightChild;
		while (cnode->leftChild != nullptr)
			cnode = cnode->leftChild;
		return;
	}
	if (cnode != bag.head and cnode->parent->leftChild == cnode) {
		cnode = cnode->parent;
		return;
	}
	if (cnode != bag.head and cnode->parent->rightChild == cnode) {
		while (cnode != bag.head and cnode->parent->rightChild == cnode) {
			cnode = cnode->parent;
		}
		if (cnode != bag.head) {
			cnode = cnode->parent;
			return;
		}
	}
	if (cnode == bag.head) {
		cnode = nullptr;
		return;
	}
}

void SortedBagIterator::first() {
	currentFrequency = 1;
	cnode = bag.head;
	if (cnode != nullptr)
		while (cnode->leftChild != nullptr)
			cnode = cnode->leftChild;
}

//TElem SortedBagIterator::remove()
//{
//	if (bag.head == nullptr)
//		throw exception();
//	TComp currentElem = getCurrent();
//	next();
//	bag.remove(currentElem);
//	return (TElem) currentElem;
//}

