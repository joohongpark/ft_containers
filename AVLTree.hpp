#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <iostream> // FIXME: 추후 제거
#include <memory>

template <class Tp, class Compare, class Allocator = std::allocator<Tp> >
class AVLTree {
    private:
        template <class T>
        struct Node {
            T data;
            Node* parent;
            Node* leftleaf;
            Node* rightleaf;
            long height;
            Node(T& _data, Node* _parent) : data(_data), parent(_parent) {
                this->leftleaf = NULL;
                this->rightleaf = NULL;
                this->height = 0;
            }
        };
    public:
        typedef Node<Tp>                                                            node_type;
        typedef Allocator                                                           origin_allocator_type;
        typedef typename origin_allocator_type::template rebind<node_type>::other   node_allocator_type; // http://egloos.zum.com/sweeper/v/2966785
        typedef Compare                                                             value_compare;
    private:
        node_allocator_type                                                         alloc;
        value_compare                                                               comp;
        node_type*                                                                  root;
    public:
        AVLTree();
        ~AVLTree();
        Tp*         insert(Tp& val);
        void        delval(Tp& val);
        Tp*         getmin(node_type* pointer = NULL); // NOTE: 없으면 NULL
        Tp*         getmax(node_type* pointer = NULL); // NOTE: 없으면 NULL
        Tp*         find(Tp& val); // NOTE: 없으면 NULL
    private:
        long        getbf(node_type* node);
        int         nodetype(node_type* parent, node_type* node, node_type* child);
        void        rewind(node_type* node);
        void        leftrotate(node_type* node);
        void        rightrotate(node_type* node);
    public:
        void __debug(long depth = 0, node_type* pointer = NULL) {
            if (pointer == NULL) {
                pointer = this->root;
            }
            if (pointer->rightleaf != NULL) {
                __debug(depth + 1, pointer->rightleaf);
            }
            for (long i = 0; i < depth; i++) {
                std::cout << " ";
            }
            std::cout << pointer->data.first << " [" << pointer->data.second << "]" << std::endl;
            if (pointer->leftleaf != NULL) {
                __debug(depth + 1, pointer->leftleaf);
            }
        }
};

template <class Tp, class Compare, class Allocator>
AVLTree<Tp, Compare, Allocator>::AVLTree() : alloc(), comp(), root(NULL) {}

template <class Tp, class Compare, class Allocator>
AVLTree<Tp, Compare, Allocator>::~AVLTree() {
    node_type* pointer = this->root;
    while (pointer != NULL) {
        if (pointer->leftleaf != NULL) {
            pointer = pointer->leftleaf;
        } else {
            if (pointer->rightleaf != NULL) {
                pointer = pointer->rightleaf;
            } else {
                node_type* parent = pointer->parent;
                if (parent != NULL) {
                    if (parent->leftleaf == pointer) {
                        parent->leftleaf = NULL;
                    } else {
                        parent->rightleaf = NULL;
                    }
                }
                std::cout << "del " << pointer->data.first << std::endl;
                alloc.deallocate(pointer, 1);
                pointer = parent;
            }
        }
    }
}

template <class Tp, class Compare, class Allocator>
Tp* AVLTree<Tp, Compare, Allocator>::insert(Tp& val) {
    node_type* pointer = this->root;
    Tp* rtn = NULL;
    while (true) {
        if (pointer == NULL) {
            this->root = alloc.allocate(1);
            alloc.construct(this->root, val, static_cast<node_type *>(NULL));
            rewind(pointer);
            rtn = &(this->root->data);
            break ;
        } else if (comp(val, pointer->data)) {
            if (pointer->leftleaf == NULL) {
                pointer->leftleaf = alloc.allocate(1);
                alloc.construct(pointer->leftleaf, val, pointer);
                rewind(pointer->leftleaf);
                rtn = &(pointer->leftleaf->data);
                break ;
            } else {
                pointer = pointer->leftleaf;
            }
        } else if (comp(pointer->data, val)) {
            if (pointer->rightleaf == NULL) {
                pointer->rightleaf = alloc.allocate(1);
                alloc.construct(pointer->rightleaf, val, pointer);
                rewind(pointer->rightleaf);
                rtn = &(pointer->rightleaf->data);
                break ;
            } else {
                pointer = pointer->rightleaf;
            }
        } else {
            break ;
        }
    }
    return (rtn);
}

template <class Tp, class Compare, class Allocator>
Tp* AVLTree<Tp, Compare, Allocator>::getmin(node_type* pointer) {
    Tp* rtn = NULL;
    if (pointer == NULL) {
        pointer = this->root;
    }
    while (pointer != NULL) {
        if (pointer->leftleaf != NULL) {
            pointer = pointer->leftleaf;
        } else {
            rtn = &(pointer->data);
            break ;
        }
    }
    return (rtn);
}

template <class Tp, class Compare, class Allocator>
Tp* AVLTree<Tp, Compare, Allocator>::getmax(node_type* pointer) {
    Tp* rtn = NULL;
    if (pointer == NULL) {
        pointer = this->root;
    }
    while (pointer != NULL) {
        if (pointer->rightleaf != NULL) {
            pointer = pointer->rightleaf;
        } else {
            rtn = &(pointer->data);
            break ;
        }
    }
    return (rtn);
}

template <class Tp, class Compare, class Allocator>
Tp* AVLTree<Tp, Compare, Allocator>::find(Tp& val) {
    Tp* rtn = NULL;
    node_type* pointer = this->root;
    while (true) {
        if (pointer == NULL) {
            break ;
        } else if (comp(val, pointer->data)) {
            if (pointer->leftleaf == NULL) {
                break ;
            } else {
                pointer = pointer->leftleaf;
            }
        } else if (comp(pointer->data, val)) {
            if (pointer->rightleaf == NULL) {
                break ;
            } else {
                pointer = pointer->rightleaf;
            }
        } else {
            rtn = &(pointer->data);
            break ;
        }
    }
    return (rtn);
}

template <class Tp, class Compare, class Allocator>
void AVLTree<Tp, Compare, Allocator>::delval(Tp& val) {
    node_type* pointer = this->root;
    while (pointer != NULL) {
        if (comp(pointer->data, val)) {
            pointer = pointer->rightleaf;
        } else if (comp(val, pointer->data)) {
            pointer = pointer->leftleaf;
        } else {
            if (pointer->leftleaf == NULL && pointer->rightleaf == NULL) {
                if (pointer->parent != NULL) {
                    if (pointer->parent->leftleaf == pointer) {
                        pointer->parent->leftleaf = NULL;
                        alloc.deallocate(pointer, 1);
                    } else {
                        pointer->parent->rightleaf = NULL;
                        alloc.deallocate(pointer, 1);
                    }
                    rewind(pointer->parent);
                } else {
                    alloc.deallocate(this->root, 1);
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
                    rewind(pointer->rightleaf);
                } else {
                    this->root = pointer->rightleaf;
                    alloc.deallocate(pointer, 1);
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
                    rewind(pointer->leftleaf);
                } else {
                    this->root = pointer->leftleaf;
                    alloc.deallocate(pointer, 1);
                }
                break ;
            } else {
                val = *(getmin(pointer->rightleaf));
                pointer->data = val;
                pointer = pointer->rightleaf;
            }
        }
    }
}

template <class Tp, class Compare, class Allocator>
long AVLTree<Tp, Compare, Allocator>::getbf(node_type* node) {
    long leftheight = 0;
    long rightheight = 0;
    if (node->leftleaf != NULL) {
        leftheight = node->leftleaf->height + 1;
    }
    if (node->rightleaf != NULL) {
        rightheight = node->rightleaf->height + 1;
    }
    if (leftheight > rightheight) {
        node->height = leftheight;
    } else {
        node->height = rightheight;
    }
    return (leftheight - rightheight);
}

template <class Tp, class Compare, class Allocator>
int AVLTree<Tp, Compare, Allocator>::nodetype(node_type* parent, node_type* node, node_type* child) {
    int rtn = 0;
    if (parent->rightleaf == node) {
        rtn = 2;
    }
    if (node->rightleaf == child) {
        rtn += 1;
    }
    return (rtn);
}

template <class Tp, class Compare, class Allocator>
void AVLTree<Tp, Compare, Allocator>::rewind(node_type* node) {
    node_type* child = NULL;
    while (node != NULL) {
        node_type* parent = node->parent;
        long bf = getbf(node);
        if (parent == NULL || bf > 1 || bf < -1) {
            if (bf > 1) {
                node = node->leftleaf;
            } else if (bf < -1) {
                node = node->rightleaf;
            } else {
                break ;
            }
        } else {
            bf = getbf(parent);
            if (child == NULL) {
                if (node->rightleaf != NULL) {
                    child = node->rightleaf;
                } else {
                    child = node->leftleaf;
                }
            }
            if (bf > 1 || bf < -1) {
                if ((parent->leftleaf == node && bf > 1) || (parent->rightleaf == node && bf < -1)) {
                    int nt = nodetype(parent, node, child);
                    if (nt == 0) {
                        rightrotate(parent);
                        getbf(parent);
                        getbf(node);
                        node = parent;
                    } else if (nt == 1) {
                        leftrotate(node);
                        rightrotate(parent);
                        getbf(parent);
                        getbf(node);
                        getbf(child);
                        node = child;
                    } else if (nt == 2) {
                        rightrotate(node);
                        leftrotate(parent);
                        getbf(parent);
                        getbf(node);
                        getbf(child);
                        node = child;
                    } else {
                        leftrotate(parent);
                        getbf(parent);
                        getbf(node);
                        node = parent;
                    }
                } else {
                    if (parent->leftleaf == node) {
                        node = parent->rightleaf;
                    } else {
                        node = parent->leftleaf;
                    }
                    child = NULL;
                }
            } else {
                child = node;
                node = node->parent;
            }
        }
    }
}

template <class Tp, class Compare, class Allocator>
void AVLTree<Tp, Compare, Allocator>::leftrotate(node_type* node) {
    node_type* up = node->rightleaf;
    node_type* a = up->leftleaf; // NULL일수도 있음

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
void AVLTree<Tp, Compare, Allocator>::rightrotate(node_type* node) {
    node_type* up = node->leftleaf;
    node_type* a = up->rightleaf; // NULL일수도 있음

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
