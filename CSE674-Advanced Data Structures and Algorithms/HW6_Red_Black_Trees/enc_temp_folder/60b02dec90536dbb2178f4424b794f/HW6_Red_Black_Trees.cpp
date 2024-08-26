//HW6 by Brijesh Verma
//SU Net ID: brverma  SUID: 826257344
// 
//CSE674 HW6  Due: 11:59PM, Dec. 1 Thursday
#include <iostream>
#include <stack>
using namespace std;

class node {
public:
	node* p_parent;
	node* p_Lchild;
	node* p_Rchild;
	int value;
	bool color; //true: red, false: black
	node() { p_parent = p_Lchild = p_Rchild = nullptr; }
	node(int i) { value = i; p_parent = p_Lchild = p_Rchild = nullptr; }
};

class tree {
public:
	node* root;
	tree() { root = nullptr; }
	void R_rotate(node* p);//R-rotate at node pointed by p
	void L_rotate(node* p);//L-rotate at node pointed by p
	//R_rotate and L_rotate will be called by insert_node, delete_node, delete_1, delete_2A, delete_2B, and delete_3.

	void add_node(int i);//same policy as HW5 for avl trees.

	void delete_node(int i);//same policy as HW5 for avl trees.



	void delete_1(node* p, bool b);
	//Case 1 of delete_node; p points to the parent of double black node; b is true if double black is the left child of its parent; else b is false.

	void delete_2A(node* p, bool b);
	//Case 2A of delete_node; p points to the parent of double black node; b is true if double black is the left child of its parent; else b is false.

	void delete_2B(node* p, bool b);
	//Case 2B of delete_node; p points to the parent of double black node; b is true if double black is the left child of its parent; else b is false.


	void delete_3(node* p, bool b);
	//Case 3 of delete_node; p points to the parent of double black node; b is true if double black is the left child of its parent; else b is false.


	//For the following, during traveral, print (value, color) of each node.
	void InorderPrint(node* p);//Print all nodes of a subtree rooted at node pointed by p; Example: (12 R) (7 B) (11 R) ...

};

int main() {
	tree T1;
	
		cout << " Red black tree 3  (8pts)" << endl;
		tree T3;
		T3.add_node(50);
		T3.add_node(100);
		T3.add_node(30);
		T3.add_node(200);
		T3.add_node(300);
		T3.add_node(250);
		T3.add_node(280);
		T3.InorderPrint(T3.root);
		cout << "    4pts" << endl;
		T3.delete_node(30);

		T3.InorderPrint(T3.root);
		cout << "    4pts" << endl;

		cout << endl;
		cout << " Red black tree 4 (9pts)" << endl;
		tree T4;
		T4.add_node(47);
		T4.add_node(32);
		T4.add_node(71);
		T4.add_node(20);
		T4.add_node(35);
		T4.add_node(65);
		T4.add_node(85);



		T4.add_node(34);
		T4.add_node(60);
		T4.add_node(82);
		T4.add_node(92);

		T4.InorderPrint(T4.root);
		cout << "    3pts" << endl;
		T4.delete_node(47);

		T4.InorderPrint(T4.root);
		cout << "    3pts" << endl;

		T4.delete_node(60);
		T4.delete_node(85);
		T4.InorderPrint(T4.root);
		cout << "    3pts" << endl;

		cout << endl;
		cout << endl;
		cout << " Red black tree 5 (12pts)" << endl;
		tree T5;
		T5.add_node(100);
		T5.add_node(200);
		T5.add_node(300);

		T5.add_node(400);
		T5.add_node(50);
		T5.add_node(150);

		T5.add_node(160);
		T5.add_node(130);
		T5.add_node(155);
		T5.InorderPrint(T5.root);
		cout << "    2pts" << endl;
		T5.delete_node(150);
		T5.InorderPrint(T5.root);
		cout << "    2pts" << endl;
		T5.delete_node(155);
		T5.InorderPrint(T5.root);
		cout << "    2pts" << endl;
		T5.delete_node(160);
		T5.InorderPrint(T5.root);
		cout << "    2pts" << endl;
		T5.delete_node(200);
		T5.InorderPrint(T5.root);
		cout << "    2pts" << endl;
		T5.delete_node(300);
		T5.InorderPrint(T5.root);
		cout << "    2pts" << endl;

		cout << endl;
		cout << endl;
		cout << " Red black tree 6 (13pts)" << endl;
		tree t6;
		t6.add_node(100);
		t6.add_node(50);
		t6.add_node(200);
		t6.add_node(300);
		t6.add_node(100);
		t6.delete_node(100);
		t6.InorderPrint(t6.root);
		cout << "    2pts" << endl;

		t6.add_node(100);
		t6.add_node(100);
		t6.add_node(100);
		t6.add_node(100);
		t6.add_node(100);

		t6.InorderPrint(t6.root);
		cout << "    3pts" << endl;
		t6.delete_node(200);
		t6.InorderPrint(t6.root);
		cout << "    2pts" << endl;

		t6.delete_node(300);
		t6.InorderPrint(t6.root);
		cout << "    2pts" << endl;


		t6.delete_node(100);
		t6.InorderPrint(t6.root);
		cout << "    2pts" << endl;


		t6.delete_node(100);
		t6.InorderPrint(t6.root);
		cout << "    2pts" << endl;


	return 0;
}

void tree::InorderPrint(node* p) { 
	stack<node*> s;
	node* curr = root;
	while (curr != NULL || s.empty() == false) {
		while (curr != NULL) {
			s.push(curr);
			curr = curr->p_Lchild;
		}
		curr = s.top();
		s.pop();
		cout << "(" << curr->value << " " << (curr->color ? 'R' : 'B') << ") ";
		curr = curr->p_Rchild;
	}
}

void tree::L_rotate(node* p) {
	//p points to the node at which the rotation will be performed.
	node* temp = p->p_Rchild->p_Lchild;
	p->p_Rchild->p_parent = p->p_parent;
	if (p->p_parent == nullptr) {
		root = p->p_Rchild;
	}
	else {
		if (p->p_parent->p_Lchild == p) {
			p->p_parent->p_Lchild = p->p_Rchild;
		}
		else {
			p->p_parent->p_Rchild = p->p_Rchild;
		}
	}

	p->p_parent = p->p_Rchild;
	p->p_parent->p_Lchild = p;
	p->p_Rchild = temp;
}

void tree::R_rotate(node* p) {
	//p points to the node at which the rotation will be performed.
	node* temp = p->p_Lchild->p_Rchild;
	p->p_Lchild->p_parent = p->p_parent;
	if (p->p_parent == nullptr) {
		root = p->p_Lchild;
	}
	else {
		if (p->p_parent->p_Lchild == p) {
			p->p_parent->p_Lchild = p->p_Lchild;
		}
		else {
			p->p_parent->p_Rchild = p->p_Lchild;
		}
	}

	p->p_parent = p->p_Lchild;
	p->p_parent->p_Rchild = p;
	p->p_Lchild = temp;

}

void tree::add_node(int i) {

	node* n = new node(i);
	n->color = true;
	if (root == nullptr) {
		n->color = false;
		root = n;
		return;
	}

	node* curr = root;
	while (curr != nullptr) {
		if (i <= curr->value) {	 // traverse left tree
			if (curr->p_Lchild == nullptr) {
				curr->p_Lchild = n;
				curr->p_Lchild->p_parent = curr;
				break;
			}
			else
				curr = curr->p_Lchild;
		}
		else {					// traverse right tree
			if (curr->p_Rchild == nullptr) {
				curr->p_Rchild = n;
				curr->p_Rchild->p_parent = curr;
				break;
			}
			else
				curr = curr->p_Rchild;
		}
	}
	curr = n;
	while(curr->p_parent->color == true) {	// parent is RED hence violation
		node* gp = curr->p_parent->p_parent;
		node* p = curr->p_parent;
		node* psibling = (gp->p_Lchild == curr->p_parent) ? gp->p_Rchild : gp->p_Lchild;

		if (psibling == nullptr || psibling->color == false) { // sibling is black
			if (gp->p_Lchild == p) {  // L-
				if (p->p_Lchild == curr) {  // L-L
					R_rotate(gp);
					p->color = !p->color;
					gp->color = !gp->color;
				}
				else {  // L-R
					L_rotate(p);
					R_rotate(gp);
					gp->color = !gp->color;
					curr->color = !curr->color;
				}
			}
			else {   // R- 
				if (p->p_Lchild == curr) {	// R-L
					R_rotate(p);
					L_rotate(gp);
					gp->color = !gp->color;
					curr->color = !curr->color;
				}
				else {		// R-R
					L_rotate(gp);
					p->color = !p->color;
					gp->color = !gp->color;
				}
			}
			return;
		}
		else { //sibling is red - then recolor
			gp->p_Lchild->color = !gp->p_Lchild->color;
			gp->p_Rchild->color = !gp->p_Rchild->color;
			if (gp != root) {
				gp->color = !gp->color;
				curr = gp;
			}
		}
					

	}

}

void tree::delete_node(int i) {
	node* curr = root;

	while (curr != nullptr) {
		if (i < curr->value)
			curr = curr->p_Lchild;	// move to left tree
		else if (i > curr->value)   // move to right tree
			curr = curr->p_Rchild;
		else if( i == curr->value) { // found node to be deleted

			// if tree has only one node ie root make root null
			if (curr == root && curr->p_Lchild == nullptr && curr->p_Rchild == nullptr) {	
				root = nullptr;
				return;
			}

			// deletion of node with both children
			if (curr->p_Lchild != nullptr && curr->p_Rchild != nullptr) {
				node* goleft = curr->p_Rchild;
				node* successor = goleft;
				while (goleft != nullptr) {
					if (goleft->p_Lchild != nullptr) {
						successor = goleft->p_Lchild;
					}
					goleft = goleft->p_Lchild;
				}
				curr->value = successor->value;
				if (successor->color == true) {  ///red leaf node deleted directly
					if (successor->p_parent->p_Lchild == successor)
						successor->p_parent->p_Lchild = nullptr;
					else
						successor->p_parent->p_Rchild = nullptr;
					successor->p_parent = nullptr;
					return;
				}
				else {		// black leaf node deletion
					if (successor->p_parent->p_Lchild == successor) {   // left node is DB
						if (successor->p_parent->p_Rchild->color == false) {  // case 1 2 
							//case 1
							if (successor->p_parent->p_Rchild->p_Lchild != nullptr && successor->p_parent->p_Rchild->p_Lchild->color == true ||
								successor->p_parent->p_Rchild->p_Rchild != nullptr && successor->p_parent->p_Rchild->p_Rchild->color == true) {
								delete_1(successor->p_parent, true);
							}
							//case 2 a b
							else {
								if (successor->p_parent->color == false)
									delete_2A(successor->p_parent, true);
								else
									delete_2B(successor->p_parent, true);
							}
						}
						else {	// case 3 
							delete_3(successor->p_parent, true);
						}
					}
					if (successor->p_parent->p_Rchild == successor) {   // right node is DB
						if (successor->p_parent->p_Lchild->color == false) {  // case 1 2 3
							//case 1
							if (successor->p_parent->p_Lchild->p_Lchild != nullptr && successor->p_parent->p_Lchild->p_Lchild->color == true ||
								successor->p_parent->p_Lchild->p_Rchild != nullptr && successor->p_parent->p_Lchild->p_Rchild->color == true) {
								delete_1(successor->p_parent, false);
							}
							//case 2 a b
							else {
								if (successor->p_parent->color == false)
									delete_2A(successor->p_parent, false);
								else
									delete_2B(successor->p_parent, false);
							}
						}
						else {	// case 3 
							delete_3(successor->p_parent, false);
						}
					}

					if (successor->p_parent->p_Lchild == successor)
						successor->p_parent->p_Lchild = nullptr;
					else
						successor->p_parent->p_Rchild = nullptr;
					successor->p_parent = nullptr;
					return;
				}
				
			}
			// Leaf node deletion
			else if (curr->p_Lchild == nullptr && curr->p_Rchild == nullptr ) { 
				// RED leaf node can be directly deleted
				if (curr->color == true) {
					if (curr->p_parent->p_Lchild == curr)
						curr->p_parent->p_Lchild = nullptr;
					else
						curr->p_parent->p_Rchild = nullptr;
					curr->p_parent = nullptr;
					return;
				}
				// BLACK leaf node deletion
				else {
					// TODO ::::::::::::::::::::::::::::::::::::::::::::::;
					if (curr->p_parent->p_Lchild == curr) {   // left node is DB
						if (curr->p_parent->p_Rchild->color == false) {  // case 1 2 
							//case 1
							if (curr->p_parent->p_Rchild->p_Lchild != nullptr && curr->p_parent->p_Rchild->p_Lchild->color == true ||
								curr->p_parent->p_Rchild->p_Rchild != nullptr && curr->p_parent->p_Rchild->p_Rchild->color == true) {
								delete_1(curr->p_parent, true);
							}
							//case 2 a b
							else {
								if (curr->p_parent->color == false)
									delete_2A(curr->p_parent, true);
								else
									delete_2B(curr->p_parent, true);
							}
						}
						else {	// case 3 
							delete_3(curr->p_parent, true);
						}
					}
					if (curr->p_parent->p_Rchild == curr) {   // right node is DB
						if (curr->p_parent->p_Lchild->color == false) {  // case 1 2 3
							//case 1
							if (curr->p_parent->p_Lchild->p_Lchild != nullptr && curr->p_parent->p_Lchild->p_Lchild->color == true ||
								curr->p_parent->p_Lchild->p_Rchild != nullptr && curr->p_parent->p_Lchild->p_Rchild->color == true) {
								delete_1(curr->p_parent, false);
							}
							//case 2 a b
							else {
								if (curr->p_parent->color == false)
									delete_2A(curr->p_parent, false);
								else
									delete_2B(curr->p_parent, false);
							}
						}
						else {	// case 3 
							delete_3(curr->p_parent, false);
						}
					}

					if (curr->p_parent->p_Lchild == curr)
						curr->p_parent->p_Lchild = nullptr;
					else
						curr->p_parent->p_Rchild = nullptr;
					curr->p_parent = nullptr;
					return;
				}
			}
			//if node has only one child node
			else {
				if (curr->p_Lchild != nullptr) {
					curr = curr->p_Lchild;
					// RED leaf node can be directly deleted
					if (curr->color == true) {
						if (curr->p_parent->p_Lchild == curr)
							curr->p_parent->p_Lchild = nullptr;
						else
							curr->p_parent->p_Rchild = nullptr;
						curr->p_parent = nullptr;
						return;
					}
					if (curr->p_parent->p_Lchild == curr) {   // left node is DB
						if (curr->p_parent->p_Rchild->color == false) {  // case 1 2 
							//case 1
							if (curr->p_parent->p_Rchild->p_Lchild != nullptr && curr->p_parent->p_Rchild->p_Lchild->color == true ||
								curr->p_parent->p_Rchild->p_Rchild != nullptr && curr->p_parent->p_Rchild->p_Rchild->color == true) {
								delete_1(curr->p_parent, true);
							}
							//case 2 a b
							else {
								if (curr->p_parent->color == false)
									delete_2A(curr->p_parent, true);
								else
									delete_2B(curr->p_parent, true);
							}
						}
						else {	// case 3 
							delete_3(curr->p_parent, true);
						}
					}

				}
				else {
					curr = curr->p_Rchild;
					// RED leaf node can be directly deleted
					if (curr->color == true) {
						if (curr->p_parent->p_Lchild == curr)
							curr->p_parent->p_Lchild = nullptr;
						else
							curr->p_parent->p_Rchild = nullptr;
						curr->p_parent = nullptr;
						return;
					}
					if (curr->p_parent->p_Rchild == curr) {   // right node is DB
						if (curr->p_parent->p_Lchild->color == false) {  // case 1 2 3
							//case 1
							if (curr->p_parent->p_Lchild->p_Lchild != nullptr && curr->p_parent->p_Lchild->p_Lchild->color == true ||
								curr->p_parent->p_Lchild->p_Rchild != nullptr && curr->p_parent->p_Lchild->p_Rchild->color == true) {
								delete_1(curr->p_parent, false);
							}
							//case 2 a b
							else {
								if (curr->p_parent->color == false)
									delete_2A(curr->p_parent, false);
								else
									delete_2B(curr->p_parent, false);
							}
						}
						else {	// case 3 
							delete_3(curr->p_parent, false);
						}
					}

				}

				if (curr->p_parent->p_Lchild == curr)
					curr->p_parent->p_Lchild = nullptr;
				else
					curr->p_parent->p_Rchild = nullptr;
				curr->p_parent = nullptr;
				return;
			}
			

			
		}
	}
}

void tree::delete_1(node* p, bool b) {
	node* parent = p->p_parent;
	node* psibling = nullptr;

	if ( p->p_parent->p_Lchild == p) {
		psibling = p->p_parent->p_Rchild;
		p->p_parent->p_Lchild = nullptr;
	}
	else {
		psibling = p->p_parent->p_Lchild;
		p->p_parent->p_Rchild = nullptr;
	}
	p->p_parent = nullptr;

	// L - 
	if ( parent->p_Lchild == psibling) {
		// L-L rotation
		if (psibling != nullptr && psibling->p_Rchild != nullptr && psibling->p_Rchild->color 
			&& psibling->p_Lchild != nullptr && psibling->p_Lchild->color) {
			R_rotate(parent);
			psibling->p_Lchild->color = !psibling->p_Lchild->color;
			psibling->color = parent->color;
			parent->color = false;
		}
		// R-L rotation
		else if (psibling != nullptr && psibling->p_Rchild != nullptr && psibling->p_Rchild->color && 
			(psibling->p_Lchild != nullptr || !psibling->p_Lchild->color)) {
			L_rotate(psibling);
			R_rotate(parent);
			parent->p_parent->color = parent->color;
			parent->color = false;
		}
	}
	// R- 
	else {
		// R-R rotation
		if (psibling != nullptr && psibling->p_Rchild != nullptr && psibling->p_Rchild->color && 
			psibling->p_Lchild != nullptr && psibling->p_Lchild->color) {
			L_rotate(parent);
			psibling->p_Rchild->color = !psibling->p_Rchild->color;
			psibling->color = parent->color;
			parent->color = false;
		}
		// L-R rotation
		else if (psibling != nullptr && psibling->p_Rchild != nullptr && psibling->p_Rchild->color && 
			(psibling->p_Lchild != nullptr || !psibling->p_Lchild->color)) {
			R_rotate(psibling);
			L_rotate(parent);
			parent->p_parent->color = parent->color;
			parent->color = false;
		}
	}
}

void tree::delete_2A(node* p, bool b) {
	if (b) {
		p->p_Lchild->color = true;
	}
	else {
		p->p_Rchild->color = true;
	}
	if (p == root)
		return;
	if (p->p_parent->p_Lchild == p) {   // left node is DB
		if (p->p_parent->p_Rchild->color == false) {  // case 1 2 
			//case 1
			if (p->p_parent->p_Rchild->p_Lchild != nullptr && p->p_parent->p_Rchild->p_Lchild->color == true ||
				p->p_parent->p_Rchild->p_Rchild != nullptr && p->p_parent->p_Rchild->p_Rchild->color == true) {   
				delete_1(p->p_parent, true);
			}
			//case 2 a b
			else {
				if (p->p_parent->color == false)	
					delete_2A(p->p_parent, true);
				else
					delete_2B(p->p_parent, true);
			}
		}
		else {	// case 3 
			delete_3(p->p_parent, true);
		}
	}
	if (p->p_parent->p_Rchild == p) {   // right node is DB
		if (p->p_parent->p_Lchild->color == false) {  // case 1 2 3
			//case 1
			if (p->p_parent->p_Lchild->p_Lchild != nullptr && p->p_parent->p_Lchild->p_Lchild->color == true ||
				p->p_parent->p_Lchild->p_Rchild != nullptr && p->p_parent->p_Lchild->p_Rchild->color == true) {
				delete_1(p->p_parent, false);
			}
			//case 2 a b
			else {
				if (p->p_parent->color == false)
					delete_2A(p->p_parent, false);
				else
					delete_2B(p->p_parent, false);
			}
		}
		else {	// case 3 
			delete_3(p->p_parent, false);
		}
	}

}

void tree::delete_2B(node* p, bool b) {
	p->color = false;
	if (b) {
		p->p_Rchild->color = true;
	}
	else {
		p->p_Lchild->color = true;
	}
}

void tree::delete_3(node* p, bool b) {
	if (b) {
		L_rotate(p);
		p->color = true;
		p->p_Rchild->color = false;
	}
	else {
		R_rotate(p);
		p->color = true;
		p->p_Lchild->color = false;
	}

	if (p->p_Lchild == nullptr) {   // left node is DB
		if (p->p_Rchild->color == false) {  // case 1 2 
			//case 1
			if (p->p_Rchild->p_Lchild != nullptr && p->p_Rchild->p_Lchild->color == true ||
				p->p_Rchild->p_Rchild != nullptr && p->p_Rchild->p_Rchild->color == true) {
				delete_1(p, true);
			}
			//case 2 a b
			else {
				if (p->color == false)
					delete_2A(p, true);
				else
					delete_2B(p, true);
			}
		}
		else {	// case 3 
			delete_3(p, true);
		}
	}
	if (p->p_Rchild == nullptr) {   // right node is DB
		if (p->p_Lchild->color == false) {  // case 1 2 3
			//case 1
			if (p->p_Lchild->p_Lchild != nullptr && p->p_Lchild->p_Lchild->color == true ||
				p->p_Lchild->p_Rchild != nullptr && p->p_Lchild->p_Rchild->color == true) {
				delete_1(p, false);
			}
			//case 2 a b
			else {
				if (p->color == false)
					delete_2A(p, false);
				else
					delete_2B(p, false);
			}
		}
		else {	// case 3 
			delete_3(p, false);
		}
	}

}


