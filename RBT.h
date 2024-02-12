//pragma once

template <typename T> class BST;
template <typename T> class  Node;

template <typename T> class Node 
{
	public:
		Node(T nValue) {
			value = nValue;
			std::hash<T> hashed;
			key = hashed(nValue);
			size = 1;
			right_ = NULL;
			left_ = NULL;
		}

		Node* left_;
		Node* right_;
		T value;
		short key;
		short size;

	private:
		//create new node
		void add(T newValue) {
			std::hash<T> ke;
			short hashed = ke(newValue);
			if (hashed == key) {
				return;
			}
			if (hashed < key) {
				if (left_ == nullptr) {
					left_ = new Node<T>(newValue);
				}
				else {
					left_->add(newValue);
				}
			}
			else {
				if (right_ == nullptr) {
					right_ = new Node<T>(newValue);
				}
				else {
					right_->add(newValue);
				}
			}
			if (left_ && right_) {
				size = 1 + left_->size + right_->size;
			}
			else if (left_) {
				size = 1 + left_->size;
			}
			else if (right_) {
				size = 1 + right_->size;
			}
			else {
				size = 1;
			}
		}

		//check if value is already in tree
		bool is_present(T w)
		{
			std::hash<T> want;
			int hashed = want(w);
			if (hashed == key) {
				return true;
			}
			if (hashed < key) {
				if (left_ != nullptr && left_->is_present(w)) {
					return true;
				}
			}
			else {
				if (right_ != nullptr && right_->is_present(w)) {
					return true;
				}
			}
			return false;
		}

		//delete node
		void remove(Node*& root, short k)
		{
			Node* parent = nullptr;
			Node* del = root;

			while (del->key != k) {
				if (k < del->key) {
					parent = del;
					del = del->left_;
				}
				else {
					parent = del;
					del = del->right_;
				}
			}
			
			if (del->right_==nullptr && del->left_==nullptr) { //no children
				if (del != root) {
					if (parent->left_ == del) {
						parent->left_ = nullptr;
					}
					else {
						parent->right_ = nullptr;
					}
					parent->size--;
				}
				else {
					root = nullptr;
				}
				delete del;
			}
			else if (del->right_ && del->left_) { //2 children
				T min = right_->minimum();
				std::hash<T> hash;
				remove(root, hash(min));
				del->value = min;
				del->key = hash(min);
				parent->size--;
			}
			else { //1 child 
				Node* child;
				if (del->left_) {
					child = del->left_;
				}
				else {
					child = del->right_;
				}
				if (del != root) {
					if (parent->left_ == del) {
						parent->left_ = child;
					}
					else {
						parent->right_ = child;
					}
					parent->size--;
				}
				else {
					root = child;
				}
				delete del;
				
			}
		}

		//get smallest value in tree
		T minimum() 
		{
			if (left_ == nullptr) {
				return value;
			}
			else {
				return left_->minimum();
			}
		}

		void display()
		{
			if (left_ != nullptr) {
				left_->display();
			}
			std::cout << value << " ";
			if (right_ != nullptr) {
				right_->display();
			}
		}
		
		template <typename U> friend class  BST;
};

template <typename T>
class BST 
{
	public:
		BST(T val) 
			: root_(new Node<T>(val)){}

		~BST() {
			delete root_;
		}

		void insert(T val) {
			root_->add(val);
		}

		bool search(T w) {
			return root_->is_present(w);
		}

		void rem(T val) {
			std::hash<T> hash;
			if (root_->is_present(val)) {
				root_->remove(root_, hash(val));
			}
		}

		void print()
		{
			root_->display();
		}

		T min()
		{
			return root_->minimum();
		}

		Node<T>* root() {
			return root_;
		}

		int size() {
			return root_->size;
		}

	private:
		Node <T> *root_;

		template <typename U> friend class  Node;

};
