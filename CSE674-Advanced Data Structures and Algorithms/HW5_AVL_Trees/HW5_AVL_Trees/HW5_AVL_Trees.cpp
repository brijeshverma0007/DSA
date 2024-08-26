//HW5 by Brijesh Verma
//SU Net ID: brverma  SUID: 826257344

//HW5  AVL Tree
//Due: Wednesday (Nov. 16) at 11:59PM
//This homework requires more efforts. You should get started as soon as possible.
//You are not allowed to use any extra function.
//You are not allowed to add extra members to either class node or class avl_tree.

#include <iostream>
#include <stack>

using namespace std;

//You need to use the following node class for each node of the AVL tree
class node {
public:
	int value;
	int height;//this is tree height. Leaf node is 1; empty node (i.e., NIL) is 0
	node* parent;//nullptr for root
	node* l_child;
	node* r_child;
	//node() {};
	node(int i) { value = i; height = 1; parent = l_child = r_child = nullptr; }
};

class avl_tree {
public:
	node* root;
	avl_tree() {
		root = nullptr;
	}

	//************************************************************************************
	//Implement the following member functions
	void add_node(int i);
	//in case of a tie, go to the left branch.

	void delete_node(int i);
	//Delete the node with value i.  in case of multiple nodes with value i, delete the first node encountered.
	//If it is not a trivial case, always replace it with successor


	//If the node to delete is a leaf node, just delete it.
	//If the node is parent of only a left leaf node, replace it with the leaf node.
	//For all other cases, replace it with in-oreder successor

	void in_order_traversal(node* p); //such as (2 5) (3 3) (5 2) (6 1) .....  (value height)
	//Height of leaf node is 1.

	pair<node*, int> height_update(node* p);
	/*
	This function will be invoked by add_node and delete_node.
	p points to the first node that we need to check for possible height update.  We then need to check possible height update toward root.
	All nodes whose heights need to be updated will be performed in this function.
	In case of a violation, the function will return
	{address of Action Node, pattern}, where violation pattern = 1, 2, 3, 4 for RR, RL LL, LR, respectively.
	In case of no violation, the function will return {nullptr, 0}.
	*/
	void L_Rotate(node* p);
	//p points to the node at which the rotation will be performed.

	void R_Rotate(node* p);
	//p points to the node at which the rotation will be performed.
};


int main() {
	cout << "avl_tree 1 (10pts)" << endl;
	avl_tree t1;
	t1.add_node(45);
	t1.add_node(50);
	t1.add_node(46);
	t1.add_node(30);
	t1.add_node(34);
	t1.add_node(48);
	t1.add_node(25);
	t1.add_node(60);
	t1.add_node(47);
	t1.in_order_traversal(t1.root); //2pts
	cout << "    2pts" << endl;
	t1.delete_node(60);
	t1.in_order_traversal(t1.root); //3pts
	cout << "    3pts" << endl;
	t1.add_node(70);
	t1.add_node(40);
	t1.add_node(32);
	t1.add_node(10);
	t1.in_order_traversal(t1.root); //2pts
	cout << "    2pts" << endl;
	t1.delete_node(70);
	t1.in_order_traversal(t1.root); //3pts
	cout << "    3pts" << endl;



	cout << endl;
	cout << "avl_tree 2 (10pts)" << endl;
	avl_tree t2;
	t2.add_node(100);
	t2.add_node(50);
	t2.add_node(200);
	t2.add_node(30);
	t2.add_node(80);
	t2.add_node(150);
	t2.add_node(300);
	t2.add_node(10);
	t2.add_node(40);
	t2.add_node(90);
	t2.add_node(170);
	t2.add_node(5);
	t2.in_order_traversal(t2.root); //3pts
	cout << "    3pts" << endl;
	t2.delete_node(300);
	t2.in_order_traversal(t2.root); //7pts
	cout << "    7pts" << endl;



	cout << endl;
	cout << "avl_tree 3 (15pts)" << endl;
	avl_tree t3;
	t3.add_node(100);
	t3.add_node(50);
	t3.add_node(200);
	t3.add_node(300);
	t3.add_node(100);
	t3.delete_node(100);
	t3.in_order_traversal(t3.root); // 2pts
	cout << "    2pts" << endl;
	t3.add_node(100);
	t3.add_node(100);
	t3.add_node(100);
	t3.add_node(100);
	t3.add_node(100);
	t3.in_order_traversal(t3.root); //3pts
	cout << "    3pts" << endl;
	t3.delete_node(200);
	t3.in_order_traversal(t3.root); //2pts
	cout << "    2pts" << endl;
	t3.delete_node(300);
	t3.in_order_traversal(t3.root); //2pts
	cout << "    2pts" << endl;
	t3.delete_node(100);
	t3.in_order_traversal(t3.root); //3pts
	cout << "    3pts" << endl;
	t3.delete_node(100);
	t3.in_order_traversal(t3.root); //3pts
	cout << "    3pts" << endl;

	return 0;
}

void avl_tree::add_node(int i) {
	//in case of a tie, go to the left branch.
	if (root == nullptr) {
		root = new node(i);
	}
	else {
		node* curr = root;

		while (1) {
			if (i <= curr->value) {
				if (curr->l_child == nullptr) {
					node* n = new node(i);
					n->parent = curr;
					curr->l_child = n;
					while (curr != nullptr) {
						pair<node*, int> p = height_update(curr);
						pair<node*, int> pp;
						node* temp = nullptr;
						switch (p.second)
						{
						case 1:
							temp = p.first;
							R_Rotate(p.first);
							pp = height_update(p.first);
							break;

						case 2:
							temp = p.first->r_child;
							R_Rotate(p.first->r_child);
							pp = height_update(temp);
							temp = p.first;
							L_Rotate(p.first);
							pp = height_update(temp);
							break;

						case 3:
							temp = p.first;
							L_Rotate(p.first);
							pp = height_update(temp);
							break;
							
						case 4:
							temp = p.first->l_child;
							L_Rotate(p.first->l_child);
							pp = height_update(temp);
							temp = p.first;
							R_Rotate(p.first);
							pp = height_update(temp);
							break;

						
						}
						curr = p.first;
					}
					return;
				}
				else curr = curr->l_child;
			}
			else {
				if (curr->r_child == nullptr) {
					node* n = new node(i);
					n->parent = curr;
					curr->r_child = n;
					while (curr != nullptr) {
						pair<node*, int> p = height_update(curr);
						pair<node*, int> pp;
						node* temp = nullptr;
						switch (p.second)
						{
						case 1:
							temp = p.first;
							R_Rotate(p.first);
							pp = height_update(temp);
							break;

						case 2:
							temp = p.first->r_child;
							R_Rotate(p.first->r_child);
							pp = height_update(temp);
							temp = p.first;
							L_Rotate(p.first);
							pp = height_update(temp);
							break;

						case 3:
							temp = p.first;
							L_Rotate(p.first);
							pp = height_update(temp);
							break;

						case 4:
							temp = p.first->l_child;
							L_Rotate(p.first->l_child);
							pp = height_update(temp);
							temp = p.first;
							R_Rotate(p.first);
							pp = height_update(temp);
							break;
						}
						curr = p.first;
					}
					return;
				}
				else curr = curr->r_child;
			}
		}
	}
}


void avl_tree::delete_node(int i) {
	
	node* curr = root;

	while (curr != nullptr) {
		if (i == curr->value) {
			if (curr->height == 1) {	// leaf node
				node* parent = curr->parent;
				curr->parent = nullptr;
				if (parent->l_child->value == i) 
					parent->l_child = nullptr;
				else 
					parent->r_child = nullptr;

				pair<node*, int> p = height_update(curr);
				while (p.first != nullptr) {
					//pair<node*, int> pp;
					node* temp = nullptr;
					switch (p.second)
					{
					case 1:
						temp = p.first;
						R_Rotate(p.first);
						p = height_update(p.first);
						break;

					case 2:
						temp = p.first->r_child;
						R_Rotate(p.first->r_child);
						p = height_update(temp);
						temp = p.first;
						L_Rotate(p.first);
						p = height_update(temp);
						break;

					case 3:
						temp = p.first;
						L_Rotate(p.first);
						p = height_update(temp);
						break;

					case 4:
						temp = p.first->l_child;
						L_Rotate(p.first->l_child);
						p = height_update(temp);
						temp = p.first;
						R_Rotate(p.first);
						p = height_update(temp);
						break;
					}
				}
				return;
			}
			if ((curr->height == 2) && ((curr->l_child == nullptr && curr->r_child != nullptr) ||
								(curr->l_child != nullptr && curr->r_child == nullptr) )) {
				pair<node*, int> p;
				if (curr->l_child != nullptr) {
					curr->value = curr->l_child->value;
					curr->l_child->parent = nullptr;
					curr->l_child = nullptr;
					 p = height_update(curr);
				}
				else {
					curr->value = curr->r_child->value;
					curr->r_child->parent = nullptr;
					curr->r_child = nullptr;
					p = height_update(curr);
				}
				while (p.first != nullptr) {
					//pair<node*, int> pp;
					node* temp = nullptr;
					switch (p.second)
					{
					case 1:
						temp = p.first;
						R_Rotate(p.first);
						p = height_update(p.first);
						break;

					case 2:
						temp = p.first->r_child;
						R_Rotate(p.first->r_child);
						p = height_update(temp);
						temp = p.first;
						L_Rotate(p.first);
						p = height_update(temp);
						break;

					case 3:
						temp = p.first;
						L_Rotate(p.first);
						p = height_update(temp);
						break;

					case 4:
						temp = p.first->l_child;
						L_Rotate(p.first->l_child);
						p = height_update(temp);
						temp = p.first;
						R_Rotate(p.first);
						p = height_update(temp);
						break;
					}
				}
				return;
			}
			else {
				node* goleft = curr->r_child;
				node* successor= goleft;
				while (goleft != nullptr) {
					if (goleft->l_child != nullptr) {
						successor = goleft->l_child;
					}
					goleft = goleft->l_child;
				}
				curr->value = successor->value;
				node* parent = successor->parent;
				int succValue = successor->value;
				successor->parent = nullptr;
				if (parent->l_child->value == succValue)
					parent->l_child = nullptr;
				else
					parent->r_child = nullptr;

				pair<node*, int> p = height_update(parent);
				while (curr != nullptr) {
					pair<node*, int> pp;
					node* temp = nullptr;
					switch (p.second)
					{
					case 1:
						temp = p.first;
						R_Rotate(p.first);
						pp = height_update(p.first);
						break;

					case 2:
						temp = p.first->r_child;
						R_Rotate(p.first->r_child);
						pp = height_update(temp);
						temp = p.first;
						L_Rotate(p.first);
						pp = height_update(temp);
						break;

					case 3:
						temp = p.first;
						L_Rotate(p.first);
						pp = height_update(temp);
						break;

					case 4:
						temp = p.first->l_child;
						L_Rotate(p.first->l_child);
						pp = height_update(temp);
						temp = p.first;
						R_Rotate(p.first);
						pp = height_update(temp);
						break;
					}
					curr = pp.first;
				}
				return;
			}
		}
		else if (i < curr->value) {
			curr = curr->l_child;
		}
		else {
			curr = curr->r_child;
		}
	}
	
}

//Delete the node with value i.  in case of multiple nodes with value i, delete the first node encountered.
//If it is not a trivial case, always replace it with successor


//If the node to delete is a leaf node, just delete it.
//If the node is parent of only a left leaf node, replace it with the leaf node.
//For all other cases, replace it with in-oreder successor

void avl_tree::in_order_traversal(node* p) { //such as (2 5) (3 3) (5 2) (6 1) .....  (value height) 
	//Height of leaf node is 1.

	stack<node*> s;
	node* curr = root;
	while (curr != NULL || s.empty() == false){
		while (curr != NULL){
			s.push(curr);
			curr = curr->l_child;
		}
		curr = s.top();
		s.pop();
		cout << "(" << curr->value << " " << curr->height << ") ";
		curr = curr->r_child;
	}
}

pair<node*, int> avl_tree::height_update(node* p) {
	while (p != nullptr) {
		int lheight = p->l_child == nullptr ? 0 : p->l_child->height;
		int rheight = p->r_child == nullptr ? 0 : p->r_child->height;
		if (abs(rheight - lheight) > 1) {
			if (rheight > lheight ) {	// R - Right child greater
				int lheight2 = p->r_child->l_child == nullptr ? 0 : p->r_child->l_child->height;
				int rheight2 = p->r_child->r_child == nullptr ? 0 : p->r_child->r_child->height;
				if (lheight2 > rheight2) {	
					return make_pair(p, 2);		// R-L Violation
				}
				else {		
					return make_pair(p, 1);		// R-R Violation
				}
			}
			else {		 // L - Right child greater
				int lheight2 = p->l_child->l_child == nullptr ? 0 : p->l_child->l_child->height;
				int rheight2 = p->l_child->r_child == nullptr ? 0 : p->l_child->r_child->height;
				if (lheight2 > rheight2) {
					return make_pair(p, 3);		// L-L Violation
				}
				else {
					return make_pair(p, 4);		// L-R Violation
				}
			}
		}
		else {	// update nodes height when diff is <= 1
			p->height = rheight > lheight ? rheight + 1 : lheight + 1;
		}
		p = p->parent;
	}
	return make_pair(nullptr, 0);
}
/*
This function will be invoked by add_node and delete_node.
p points to the first node that we need to check for possible height update.  We then need to check possible height update toward root.
All nodes whose heights need to be updated will be performed in this function.
In case of a violation, the function will return
{address of Action Node, pattern}, where violation pattern = 1, 2, 3, 4 for RR, RL LL, LR, respectively.
In case of no violation, the function will return {nullptr, 0}.
*/

void avl_tree::L_Rotate(node* p) {
	//p points to the node at which the rotation will be performed.
	node* temp = p->r_child->l_child;
	p->r_child->parent = p->parent;
	if (p->parent == nullptr) {
		root = p->r_child;
	}
	else {
		if (p->parent->l_child == p) {
			p->parent->l_child = p->r_child;
		}
		else {
			p->parent->r_child = p->r_child;
		}
	}
	
	p->parent = p->r_child;
	p->parent->l_child = p;
	p->r_child = temp;
}


void avl_tree::R_Rotate(node* p) {
	//p points to the node at which the rotation will be performed.
	node* temp = p->l_child->r_child;
	p->l_child->parent = p->parent;
	if (p->parent == nullptr) {
		root = p->l_child;
	}
	else {
		if (p->parent->l_child == p) {
			p->parent->l_child = p->l_child;
		}
		else {
			p->parent->r_child = p->l_child;
		}
	}
	
	p->parent = p->l_child;
	p->parent->r_child = p;
	p->l_child = temp;

}