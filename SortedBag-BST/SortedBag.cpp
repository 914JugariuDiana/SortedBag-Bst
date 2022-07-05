#include "SortedBag.h"
#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r) {
	head = nullptr;
	relation = r;
	currentSize = 0;
}

void SortedBag::add(TComp e) {
	currentSize++;
	bool ok = false;
	Node* n = new (Node);
	n->parent = nullptr;
	n->leftChild = nullptr;
	n->rightChild = nullptr;
	n->value = e;
	n->frequency = 1;
	if (head == nullptr){
		head = n;
		n->parent = nullptr;
		ok = true;
		return;
	}

	Node* search = head;
	while (!ok)
	{
		if (e == search->value) {
			search->frequency++;
			ok = true;
			delete n;
		}
		else if (relation(search->value, e)) {
			if (search->rightChild == nullptr) {
				search->rightChild = n;
				n->parent = search;
				ok = true;
			}
			else {
				search = search->rightChild;
			}
		}
		else if (relation(e, search->value)) {
			if (search->leftChild == nullptr) {
				search->leftChild = n;
				n->parent = search;
				ok = true;
			}
			else {
				search = search->leftChild;
			}
		}
	}
}

bool SortedBag::remove(TComp e) {
	if (!search(e))
		return false;

	currentSize--;
	Node* search = head;
	while (1)
	{
		if (e == search->value) {
			if (search->frequency > 1) {
				search->frequency--;
				return true;
			}
			else
			{
				if (search->leftChild == nullptr and search->rightChild == nullptr) {
					if (search == head) {
						head = nullptr;
					}
					else if (search == search->parent->leftChild)
						search->parent->leftChild = nullptr;
					else
						search->parent->rightChild = nullptr;
				}
				else if (search->leftChild == nullptr) {
					if (search == head) {
						head = search->rightChild;
						search->rightChild->parent = nullptr;
					}
					else if (search == search->parent->leftChild)
						search->parent->leftChild = search->rightChild;
					else if (search == search->parent->rightChild)
						search->parent->rightChild = search->rightChild;
				}
				else if (search->rightChild == nullptr) {
					if (search == head) {
						head = search->leftChild;
						search->leftChild->parent = nullptr;
					}
					else if (search == search->parent->leftChild)
						search->parent->leftChild = search->leftChild;
					else if (search == search->parent->rightChild)
						search->parent->rightChild = search->leftChild;
				}
				else {
					Node* searchHighestLeft = search->leftChild;
					while (searchHighestLeft->rightChild != nullptr)
						searchHighestLeft = searchHighestLeft->rightChild;
					searchHighestLeft->parent->rightChild = searchHighestLeft->leftChild;
					if (search == head) {
						head = searchHighestLeft;

						if (searchHighestLeft->leftChild != nullptr)
							searchHighestLeft->leftChild->parent = searchHighestLeft->parent;
						searchHighestLeft->parent = nullptr;
						searchHighestLeft->rightChild = search->rightChild;
						if (search->rightChild != nullptr)
							search->rightChild->parent = searchHighestLeft;
						searchHighestLeft->leftChild = search->leftChild;
						if (search->leftChild != nullptr)
							search->leftChild->parent = searchHighestLeft;
						search->leftChild = nullptr;
						search->rightChild = nullptr;
						search->parent = nullptr;
						delete search;
						return true;
					}
					else if (search->parent->leftChild == search) {
						search->parent->leftChild = searchHighestLeft;
					}
					else if (search->parent->rightChild == search) {
						search->parent->rightChild = searchHighestLeft;
					}
					if (search->leftChild == searchHighestLeft) {
						searchHighestLeft->rightChild = search->rightChild;
						searchHighestLeft->parent = search->parent;
					}
					else {
						if (searchHighestLeft->leftChild != nullptr)
							searchHighestLeft->leftChild->parent = searchHighestLeft->parent;
						searchHighestLeft->parent = search->parent;
						search->parent->rightChild = searchHighestLeft;
						searchHighestLeft->rightChild = search->rightChild;
						search->rightChild->parent = searchHighestLeft;
						searchHighestLeft->leftChild = search->leftChild;
						search->leftChild->parent = searchHighestLeft;
					}
				}
				Node* s = search->parent;
				search->leftChild = nullptr;
				search->rightChild = nullptr;
				search->parent = nullptr;
				delete search;
				return true;
			}
		}
		else if (relation(search->value, e)) {
				search = search->rightChild;
		}
		else if (relation(e, search->value)) {
				search = search->leftChild;
		}
	}
}

bool SortedBag::search(TComp elem) const {
	Node* search = head;

	if (head == nullptr)
		return false;

	while (1)
	{
		if (elem == search->value) {
			return true;
		}
		else if (relation(search->value, elem)) {
			if (search->rightChild == nullptr) {
				return false;
			}
			else {
				search = search->rightChild;
			}
		}
		else if (relation(elem, search->value)) {
			if (search->leftChild == nullptr) {
				return false;
			}
			else {
				search = search->leftChild;
			}
		}
	}
}

int SortedBag::nrOccurrences(TComp elem) const {
	if (search(elem) == false)
		return 0;

	Node* search = head;
	while (1)
	{
		if (elem == search->value) {
			return search->frequency;
		}
		else if (relation(search->value, elem)) {
			search = search->rightChild;
		}
		else if (relation(elem, search->value)) {
			search = search->leftChild;
		}
	}
}

int SortedBag::size() const {
	return currentSize;
}

bool SortedBag::isEmpty() const {
	return currentSize == 0;
}

SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}

SortedBag::~SortedBag() {
	Node* deleteNode = head;
	while (deleteNode != head) {
		if (deleteNode->leftChild != nullptr) {
			deleteNode = deleteNode->leftChild;
		}
		else if (deleteNode->rightChild != nullptr) {
			deleteNode = deleteNode->rightChild;
		}
		else {
			Node* toDelete = deleteNode;
			deleteNode = deleteNode->parent;
			if (deleteNode->leftChild == toDelete)
				deleteNode->leftChild = nullptr;
			else
				deleteNode->rightChild = nullptr;
			delete toDelete;
		}
	}
}
