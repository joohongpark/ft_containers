#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <iostream> // FIXME: 추후 제거

template <class Tp, class Compare, class Allocator>
class AVLTree {
    private:
        template <class T>
        struct Node {
            T data;
            Node* parent;
            Node* leftleaf;
            Node* rightleaf;
            long height;
            void init(T _data, Node* _parent) {
                this->data = _data;
                this->parent = _parent;
                this->leftleaf = NULL;
                this->rightleaf = NULL;
                this->height = 0;
            }
        };
    public:
        typedef Node<Tp>                                                    node_type;
        typedef Allocator                                                   allocator_type;
        typedef typename allocator_type::template rebind<node_type>::other  node_allocator_type; // http://egloos.zum.com/sweeper/v/2966785
        typedef Tp                                                          value_type;
        typedef Compare                                                     value_compare;
    private:
        node_allocator_type                                                 _alloc;
        node_type*                                                          root;
    public:
        AVLTree();
        void insert(Tp val);
        Tp getmin(Node<Tp>* pointer = NULL);
        Tp getmax(Node<Tp>* pointer = NULL);
        void delval(Tp val);
        long getbf(Node<Tp>* node);
        int nodetype(Node<Tp>* node, Node<Tp>* rnode, Node<Tp>* rrnode);
        void rewind(Node<Tp>* node);
        void leftrotate(Node<Tp>* node);
        void rightrotate(Node<Tp>* node);
        void __debug(long depth = 0, Node<Tp>* pointer = NULL) {
            if (pointer == NULL) {
                pointer = this->root;
            }
            if (pointer->rightleaf != NULL) {
                __debug(depth + 1, pointer->rightleaf);
            }
            for (long i = 0; i < depth; i++) {
                std::cout << " ";
            }
            std::cout << pointer->data << std::endl;
            if (pointer->leftleaf != NULL) {
                __debug(depth + 1, pointer->leftleaf);
            }
        }
};
template <class Tp, class Compare, class Allocator>
AVLTree<Tp, Compare, Allocator>::AVLTree() : root(NULL) {}


template <class Tp, class Compare, class Allocator>
void AVLTree<Tp, Compare, Allocator>::insert(Tp val) {
    Node<Tp>* pointer = this->root;
    while (true) {
        if (pointer == NULL) {
            this->root = _alloc.allocate(1);
            this->root->init(val, NULL);
            rewind(pointer);
            break ;
        } else if (pointer->data == val) { // NOTE: Compare 사용해서 비교 해야 함
            // NOTE: 별도로 처리가 필요한지 확인 필요
        } else if (pointer->data > val) { // NOTE: Compare 사용해서 비교 해야 함
            if (pointer->leftleaf == NULL) {
                pointer->leftleaf = _alloc.allocate(1);
                pointer->leftleaf->init(val, pointer);
                rewind(pointer->leftleaf);
                break ;
            } else {
                pointer = pointer->leftleaf;
            }
        } else {
            if (pointer->rightleaf == NULL) {
                pointer->rightleaf = _alloc.allocate(1);
                pointer->rightleaf->init(val, pointer);
                rewind(pointer->rightleaf);
                break ;
            } else {
                pointer = pointer->rightleaf;
            }
        }
    }
}

template <class Tp, class Compare, class Allocator>
Tp AVLTree<Tp, Compare, Allocator>::getmin(Node<Tp>* pointer) {
    // NOTE: 원소가 없을때에는?
    if (pointer == NULL) {
        pointer = this->root;
    }
    while (pointer != NULL) {
        if (pointer->leftleaf != NULL) {
            pointer = pointer->leftleaf;
        } else {
            return pointer->data;
        }
    }
    return Tp();
}

template <class Tp, class Compare, class Allocator>
Tp AVLTree<Tp, Compare, Allocator>::getmax(Node<Tp>* pointer) {
    // NOTE: 원소가 없을때에는?
    if (pointer == NULL) {
        pointer = this->root;
    }
    while (pointer != NULL) {
        if (pointer->rightleaf != NULL) {
            pointer = pointer->rightleaf;
        } else {
            return pointer->data;
        }
    }
    return Tp();
}

template <class Tp, class Compare, class Allocator>
void AVLTree<Tp, Compare, Allocator>::delval(Tp val) {
    Node<Tp>* pointer = this->root;
    while (pointer != NULL) {
        if (pointer->data == val) { // NOTE: Compare 사용해서 비교 해야 함
            if (pointer->leftleaf == NULL && pointer->rightleaf == NULL) {
                if (pointer->parent != NULL) {
                    if (pointer->parent->leftleaf == pointer) {
                        pointer->parent->leftleaf = NULL;
                        _alloc.deallocate(pointer, 1);
                    } else {
                        pointer->parent->rightleaf = NULL;
                        _alloc.deallocate(pointer, 1);
                    }
                } else {
                    _alloc.deallocate(this->root, 1);
                    this->root = NULL;
                }
                break ;
            } else if (pointer->leftleaf == NULL && pointer->rightleaf != NULL) {
                if (pointer->parent != NULL) {
                    pointer->rightleaf->parent = pointer->parent;
                    if (pointer->parent->leftleaf == pointer) {
                        pointer->parent->leftleaf = pointer->rightleaf;
                    } else {
                        pointer->parent->rightleaf = pointer->rightleaf;
                    }
                } else {
                    this->root = pointer->rightleaf;
                    //delete pointer; // NOTE: delete 대신 Allocator 써야 함
                    _alloc.deallocate(pointer, 1);
                }
                break ;
            } else if (pointer->leftleaf != NULL && pointer->rightleaf == NULL) {
                if (pointer->parent != NULL) {
                    pointer->leftleaf->parent = pointer->parent;
                    if (pointer->parent->leftleaf == pointer) {
                        pointer->parent->leftleaf = pointer->leftleaf;
                    } else {
                        pointer->parent->rightleaf = pointer->leftleaf;
                    }
                } else {
                    this->root = pointer->leftleaf;
                    //delete pointer; // NOTE: delete 대신 Allocator 써야 함
                    _alloc.deallocate(pointer, 1);
                }
                break ;
            } else {
                val = getmin(pointer->rightleaf);
                pointer->data = val;
                pointer = pointer->rightleaf;
            }
        } else {
            if (pointer->data < val) { // NOTE: Compare 사용해서 비교 해야 함
                pointer = pointer->rightleaf;
            } else {
                pointer = pointer->leftleaf;
            }
        }
    }
}

template <class Tp, class Compare, class Allocator>
long AVLTree<Tp, Compare, Allocator>::getbf(Node<Tp>* node) {
    long leftheight = 0;
    long rightheight = 0;
    if (node->leftleaf != NULL) {
        leftheight = node->leftleaf->height;
    }
    if (node->rightleaf != NULL) {
        rightheight = node->rightleaf->height;
    }
    if (leftheight > rightheight) {
        node->height = leftheight + 1;
    } else {
        node->height = rightheight + 1;
    }
    return (leftheight - rightheight);
}

template <class Tp, class Compare, class Allocator>
int AVLTree<Tp, Compare, Allocator>::nodetype(Node<Tp>* node, Node<Tp>* rnode, Node<Tp>* rrnode) {
    int rtn = 0;
    if (node->rightleaf == rnode) {
        rtn = 2;
    }
    if (rnode->rightleaf == rrnode) {
        rtn += 1;
    }
    return (rtn);
}

template <class Tp, class Compare, class Allocator>
void AVLTree<Tp, Compare, Allocator>::rewind(Node<Tp>* node) {
    Node<Tp>* rnode = NULL;
    Node<Tp>* rrnode = NULL;
    long cnt = 0;
    while (node != NULL) {
        cnt++;
        long bf = getbf(node);
        if (bf > 1 || bf < -1) {
            int nt = nodetype(node, rnode, rrnode);
            if (nt == 0) {
                rightrotate(node);
                getbf(node);
                getbf(rnode);
                node = rnode;
            } else if (nt == 1) {
                leftrotate(rnode);
                rightrotate(node);
                getbf(node);
                getbf(rnode);
                getbf(rrnode);
                node = rrnode;
            } else if (nt == 2) {
                rightrotate(rnode);
                leftrotate(node);
                getbf(node);
                getbf(rnode);
                getbf(rrnode);
                node = rrnode;
            } else {
                leftrotate(node);
                getbf(node);
                getbf(rnode);
                node = rnode;
            }
            rnode = NULL;
            rrnode = NULL;
        } else {
            rrnode = rnode;
            rnode = node;
            node = node->parent;
        }
    }
    
}

template <class Tp, class Compare, class Allocator>
void AVLTree<Tp, Compare, Allocator>::leftrotate(Node<Tp>* node) {
    Node<Tp>* up = node->rightleaf;
    Node<Tp>* a = up->leftleaf; // NULL일수도 있음

    // 1. up - p 연결
    if (node->parent == NULL) {
        this->root = up;
        up->parent = NULL;
    } else {
        if (node->parent->leftleaf == node) {
            node->parent->leftleaf = up;
        } else {
            node->parent->rightleaf = up;
        }
        up->parent = node->parent;
    }

    // 2. up의 오른쪽노드를 a에서 node로 변경
    up->leftleaf = node;
    node->parent = up;

    // 3. node의 왼쪽 노드를 A로
    node->rightleaf = a;
    if (a != NULL) {
        a->parent = node;
    }
}

template <class Tp, class Compare, class Allocator>
void AVLTree<Tp, Compare, Allocator>::rightrotate(Node<Tp>* node) {
    Node<Tp>* up = node->leftleaf;
    Node<Tp>* a = up->rightleaf; // NULL일수도 있음

    // 1. up - p 연결
    if (node->parent == NULL) {
        this->root = up;
        up->parent = NULL;
    } else {
        if (node->parent->leftleaf == node) {
            node->parent->leftleaf = up;
        } else {
            node->parent->rightleaf = up;
        }
        up->parent = node->parent;
    }

    // 2. up의 오른쪽노드를 a에서 node로 변경
    up->rightleaf = node;
    node->parent = up;

    // 3. node의 왼쪽 노드를 A로
    node->leftleaf = a;
    if (a != NULL) {
        a->parent = node;
    }
}

#endif
