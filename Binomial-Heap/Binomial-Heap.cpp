#include <iostream>
using namespace std;

class Node {
public:
	int data;
	Node *child;
	Node *sibling;
	int degree;

	Node() {}
	Node(int x) {
		data = x;
		child = sibling = NULL;
		degree = 0;
	}
	void print(int indent) {
		for (int i = 0; i < indent; i++) cout << "\t";
		cout << data << endl;
		if (child != NULL) child->print(indent + 1);
		if (sibling != NULL) sibling->print(indent);
	}
};

class BHeap {
public:
	Node *root;

	BHeap() {
		root = NULL;
	}

	BHeap(Node *node) {
		root = node;
	}

	Node* mergeTrees(Node *h1, Node *h2) {
		/* Merging two binomial trees of the same order */

		if (h1->data > h2->data) {
			h1->sibling = h2->child;
			h2->child = h1;
			h2->degree++;
			return h2;
		}
		else {
			h2->sibling = h1->child;
			h1->child = h2;
			h1->degree++;
			return h1;
		}
	}
	Node* merge(Node *h1, Node *h2) {

		/* First step: copy every binimial trees from h1 and h2 to h3 */
		Node *h3 = NULL;

		if (h1 == NULL) return h2;
		if (h2 == NULL) return h1;

		if (h1->degree < h2->degree) {
			h3 = h1;
			h3->sibling = merge(h1->sibling, h2);
		}
		else {
			h3 = h2;
			h3->sibling = merge(h1, h2->sibling);
		}

		/* Second step: merge those binomial trees of the same order */
		Node *prev = NULL;
		Node *first = h3;
		Node *second = first->sibling;

		if (second != NULL) {
			Node *next = second->sibling;
			while (next != NULL) {
				if (next->degree > second->degree && first->degree == second->degree) {
						if (prev == NULL) {
							h3 = mergeTrees(first, second);
							h3->sibling = next;
							first = h3;
						}
						else {
							prev->sibling = mergeTrees(first, second);
							prev->sibling->sibling = next;
							first = prev->sibling;
						}
				}
				else {
					prev = first;
					first = first->sibling;
				}
				second = first->sibling;
				next = second->sibling;
			}

			if (first->degree == second->degree) {
				if (prev == NULL) {
					h3 = mergeTrees(first, second);
					h3->sibling = next;
				}
				else {
					prev->sibling = mergeTrees(first, second);
					prev->sibling->sibling = next;
				}
			}
		}

		return h3;
	}

	Node* insert(int x) {
		Node *h2 = new Node(x);
		root = merge(root, h2);
		return root;
	}

	Node* deletemin() {
		int min = root->data;
		Node *temp = root->sibling;
		Node *minNode = root;
		Node *prev = root;
		Node *minPrev = root;

		while (temp != NULL) {
			if (min > temp->data) {
				min = temp->data;
				minNode = temp;
				minPrev = prev;
			}
			prev = temp;
			temp = temp->sibling;
		}

		minPrev->sibling = minPrev->sibling->sibling;
		
		Node *p = minNode->child;
		Node *q = p->sibling;
		p->sibling = NULL;

		while (q != NULL) {
			temp = q;
			q = q->sibling;
			temp->sibling = p;
			p = temp;
		}

		return merge(root, p);

	}

	void printHeap() {
		cout << "\n ------------- \n";
		root->print(0);
	}
};

int main() {
	int a[] = { 16, 2, 4, 6, 15, 10, 8, 34, 18, 17, 27, 14, 11, 23, 21, 32, 22, 17, 25 };
	int n = 19;
	BHeap *h1 = new BHeap(new Node(a[n-1]));
	for (int i = n-2; i >= 0; i--) 
		h1->insert(a[i]);
	h1->printHeap();

	int b[] = { 9, 4, 6, 7, 10, 8, 17 };
	n = 7;

	BHeap *h2 = new BHeap(new Node(b[n - 1]));
	for (int i = n - 2; i >= 0; i--)
		h2->insert(b[i]);
	h2->printHeap();

	BHeap *h3 = new BHeap(h1->merge(h1->root, h2->root));
	h3->printHeap();

	BHeap *h4 = new BHeap(h3->deletemin());
	h4->printHeap();
}