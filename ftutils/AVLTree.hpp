#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <memory>

namespace ft {
    template <class Tp, class Compare, class Allocator = std::allocator<Tp> >
    class AVLTree {
        private:
            template <class T>
            struct Node {
                typedef T                                                               value_type;
                T data;
                Node* parent;
                Node* leftleaf;
                Node* rightleaf;
                long height;
                Node(const T& _data, Node* _parent) : data(_data), parent(_parent) {
                    this->leftleaf = NULL;
                    this->rightleaf = NULL;
                    this->height = 0;
                }
                static void node_swap(Node* a, Node* b) {
                    long height_tmp = a->height;
                    a->height = b->height;
                    b->height = height_tmp;
                    Node* parent_tmp = a->parent;
                    a->parent = b->parent;
                    b->parent = parent_tmp;
                    Node* leftleaf_tmp = a->leftleaf;
                    a->leftleaf = b->leftleaf;
                    b->leftleaf = leftleaf_tmp;
                    Node* rightleaf_tmp = a->rightleaf;
                    a->rightleaf = b->rightleaf;
                    b->rightleaf = rightleaf_tmp;
                    if (a->parent != NULL) {
                        if (a->parent->leftleaf == b) {
                            a->parent->leftleaf = a;
                        } else {
                            a->parent->rightleaf = a;
                        }
                    }
                    if (b->parent != NULL) {
                        if (b->parent->leftleaf == a) {
                            b->parent->leftleaf = b;
                        } else {
                            b->parent->rightleaf = b;
                        }
                    }
                    if (a->leftleaf != NULL) {
                        a->leftleaf->parent = a;
                    }
                    if (b->leftleaf != NULL) {
                        b->leftleaf->parent = b;
                    }
                    if (a->rightleaf != NULL) {
                        a->rightleaf->parent = a;
                    }
                    if (b->rightleaf != NULL) {
                        b->rightleaf->parent = b;
                    }
                }
            };

        public:
            typedef Node<Tp>                                                            node_type;
            typedef Allocator                                                           origin_allocator_type;
            typedef typename origin_allocator_type::template rebind<node_type>::other   node_allocator_type;
            typedef Compare                                                             value_compare;
            typedef typename node_allocator_type::size_type                             size_type;

        private:
            node_allocator_type                                                         alloc;
            value_compare                                                               comp;
            node_type*                                                                  root;

        public:
            // construct/copy/destroy/operator:
            AVLTree();
            AVLTree(const AVLTree& avltree);
            ~AVLTree();
            AVLTree&            operator=(const AVLTree& avltree);
        
            // Tree 필수 메소드 (레퍼런스로 받으면 테스트 시 인수에 리터럴을 못넣지만 map 내에서 호출할 때를 위함)
            Tp*                 insert(const Tp& val);          // 값 삽입 (이미 존재하면 NULL 반환)
            bool                have(const Tp& val) const;      // 값 존재유무 확인 (객체 멤버변수가 변하지 않음을 보증)
            Tp*                 find(const Tp& val);            // 값 탐색 (존재하지 않으면 NULL 반환)
            bool                delval(Tp& val);                // 값 삭제 (값이 존재해서 삭제되면 true 반환)
            void                clear();

            // for iterator
            node_type*          getnode(const Tp& val);         // 값을 가지고 있는 노드 반환
            static node_type*   getmin(node_type* pointer);     // 최소값 노드 반환
            static node_type*   getmax(node_type* pointer);     // 최대값 노드 반환
            static node_type*   getprev(node_type* pointer);    // 인수로 주어진 노드에서 다음 노드 반환
            static node_type*   getnext(node_type* pointer);    // 인수로 주어진 노드에서 이전 노드 반환
            node_type*          begin();                        // 트리의 최소값 노드 반환
            node_type*          cbegin() const;                 // 트리의 최소값 노드 반환 (const)
            node_type*          end();                          // 트리의 최대값 노드 반환
            node_type*          cend() const;                   // 트리의 최대값 노드 반환 (const)

            // etc
            size_type           max_size() const;               // 할당자의 max_size 리턴
        
        private:
            long                getbf(node_type* node);
            int                 nodetype(node_type* parent, node_type* node, node_type* child);
            void                rewind(node_type* node);
            void                leftrotate(node_type* node);
            void                rightrotate(node_type* node);
    };
}

namespace ft {
    template <class Tp, class Compare, class Allocator>
    AVLTree<Tp, Compare, Allocator>::AVLTree() : alloc(), comp(), root(NULL) {}

    template <class Tp, class Compare, class Allocator>
    AVLTree<Tp, Compare, Allocator>::AVLTree(const AVLTree& avltree) : alloc(avltree.alloc), comp(avltree.comp), root(NULL) {
        if (this != &avltree) {
            *this = avltree;
        }
    }

    template <class Tp, class Compare, class Allocator>
    AVLTree<Tp, Compare, Allocator>::~AVLTree() {
        clear();
    }

    template <class Tp, class Compare, class Allocator>
    AVLTree<Tp, Compare, Allocator>& AVLTree<Tp, Compare, Allocator>::operator=(const AVLTree& avltree) {
        if (this != &avltree) {
            node_type* pointer = getmax(avltree.root);
            while (pointer != NULL) {
                this->insert(pointer->data);
                pointer = getprev(pointer);
            }
        }
        return (*this);
    }

    template <class Tp, class Compare, class Allocator>
    Tp* AVLTree<Tp, Compare, Allocator>::insert(const Tp& val) {
        node_type* pointer = this->root;
        Tp* rtn = NULL;
        while (true) {
            if (pointer == NULL) {
                this->root = alloc.allocate(1);
                alloc.construct(this->root, val, static_cast<node_type *>(NULL));
                rtn = &(this->root->data);
                rewind(pointer);
                break ;
            } else if (comp(val, pointer->data)) {
                if (pointer->leftleaf == NULL) {
                    pointer->leftleaf = alloc.allocate(1);
                    alloc.construct(pointer->leftleaf, val, pointer);
                    rtn = &(pointer->leftleaf->data);
                    rewind(pointer->leftleaf);
                    break ;
                } else {
                    pointer = pointer->leftleaf;
                }
            } else if (comp(pointer->data, val)) {
                if (pointer->rightleaf == NULL) {
                    pointer->rightleaf = alloc.allocate(1);
                    alloc.construct(pointer->rightleaf, val, pointer);
                    rtn = &(pointer->rightleaf->data);
                    rewind(pointer->rightleaf);
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
    typename AVLTree<Tp, Compare, Allocator>::node_type* AVLTree<Tp, Compare, Allocator>::getnode(const Tp& val) {
        node_type* pointer = this->root;
        while (pointer != NULL) {
            if (comp(val, pointer->data)) {
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
                break ;
            }
        }
        return (pointer);
    }

    template <class Tp, class Compare, class Allocator>
    typename AVLTree<Tp, Compare, Allocator>::node_type* AVLTree<Tp, Compare, Allocator>::getmin(node_type* pointer) {
        node_type* rtn = NULL;
        while (pointer != NULL) {
            if (pointer->leftleaf != NULL) {
                pointer = pointer->leftleaf;
            } else {
                rtn = pointer;
                break ;
            }
        }
        return (rtn);
    }

    template <class Tp, class Compare, class Allocator>
    typename AVLTree<Tp, Compare, Allocator>::node_type* AVLTree<Tp, Compare, Allocator>::getmax(node_type* pointer) {
        node_type* rtn = NULL;
        while (pointer != NULL) {
            if (pointer->rightleaf != NULL) {
                pointer = pointer->rightleaf;
            } else {
                rtn = pointer;
                break ;
            }
        }
        return (rtn);
    }

    template <class Tp, class Compare, class Allocator>
    typename AVLTree<Tp, Compare, Allocator>::node_type* AVLTree<Tp, Compare, Allocator>::getprev(node_type* pointer) {
        if (pointer == NULL) {
            return (NULL);
        }
        if (pointer->leftleaf != NULL) {
            return (getmax(pointer->leftleaf));
        }
        node_type* parent = pointer->parent;
        while (parent != NULL) {
            if (parent->rightleaf == pointer) {
                break ;
            } else {
                pointer = parent;
                parent = pointer->parent;
            }
        }
        return (parent);
    }

    template <class Tp, class Compare, class Allocator>
    typename AVLTree<Tp, Compare, Allocator>::node_type* AVLTree<Tp, Compare, Allocator>::getnext(node_type* pointer) {
        if (pointer == NULL) {
            return (NULL);
        }
        if (pointer->rightleaf != NULL) {
            return (getmin(pointer->rightleaf));
        }
        node_type* parent = pointer->parent;
        while (parent != NULL) {
            if (parent->leftleaf == pointer) {
                break ;
            } else {
                pointer = parent;
                parent = pointer->parent;
            }
        }
        return (parent);
    }

    template <class Tp, class Compare, class Allocator>
    void AVLTree<Tp, Compare, Allocator>::clear() {
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
                    alloc.deallocate(pointer, 1);
                    pointer = parent;
                }
            }
        }
        this->root = NULL;
    }

    template <class Tp, class Compare, class Allocator>
    bool AVLTree<Tp, Compare, Allocator>::have(const Tp& val) const {
        bool rtn = false;
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
                rtn = true;
                break ;
            }
        }
        return (rtn);
    }

    template <class Tp, class Compare, class Allocator>
    Tp* AVLTree<Tp, Compare, Allocator>::find(const Tp& val) {
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
    typename AVLTree<Tp, Compare, Allocator>::size_type AVLTree<Tp, Compare, Allocator>::max_size() const {
        return (alloc.max_size());
    }

    template <class Tp, class Compare, class Allocator>
    typename AVLTree<Tp, Compare, Allocator>::node_type* AVLTree<Tp, Compare, Allocator>::begin() {
        return (getmin(this->root));
    }

    template <class Tp, class Compare, class Allocator>
    typename AVLTree<Tp, Compare, Allocator>::node_type* AVLTree<Tp, Compare, Allocator>::cbegin() const {
        node_type* pointer = this->root;
        while (pointer != NULL) {
            if (pointer->leftleaf != NULL) {
                pointer = pointer->leftleaf;
            } else {
                return (pointer);
            }
        }
        return (NULL);
    }

    template <class Tp, class Compare, class Allocator>
    typename AVLTree<Tp, Compare, Allocator>::node_type* AVLTree<Tp, Compare, Allocator>::end() {
        return (getmax(this->root));
    }

    template <class Tp, class Compare, class Allocator>
    typename AVLTree<Tp, Compare, Allocator>::node_type* AVLTree<Tp, Compare, Allocator>::cend() const {
        node_type* pointer = this->root;
        while (pointer != NULL) {
            if (pointer->rightleaf != NULL) {
                pointer = pointer->rightleaf;
            } else {
                return (pointer);
            }
        }
        return (NULL);
    }

    template <class Tp, class Compare, class Allocator>
    bool AVLTree<Tp, Compare, Allocator>::delval(Tp& val) {
        bool rtn = false;
        node_type* pointer = this->root;
        node_type* target = NULL;
        Tp* val_p = &val;
        while (pointer != NULL) {
            if (comp(pointer->data, *val_p)) {
                pointer = pointer->rightleaf;
            } else if (comp(*val_p, pointer->data)) {
                pointer = pointer->leftleaf;
            } else {
                rtn = true;
                if (target != NULL) {
                    node_type::node_swap(target, pointer);
                    pointer = target;
                }
                if (pointer->leftleaf == NULL && pointer->rightleaf == NULL) {
                    if (pointer->parent != NULL) {
                        if (pointer->parent->leftleaf == pointer) {
                            pointer->parent->leftleaf = NULL;
                        } else {
                            pointer->parent->rightleaf = NULL;
                        }
                        rewind(pointer->parent);
                    } else {
                        this->root = NULL;
                    }
                    alloc.deallocate(pointer, 1);
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
                    }
                    alloc.deallocate(pointer, 1);
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
                    }
                    alloc.deallocate(pointer, 1);
                    break ;
                } else {
                    target = pointer;
                    val_p = &(getmin(pointer->rightleaf)->data);
                    pointer = pointer->rightleaf;
                }
            }
        }
        return (rtn);
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
        node_type* a = up->leftleaf;
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
        up->leftleaf = node;
        node->parent = up;
        node->rightleaf = a;
        if (a != NULL) {
            a->parent = node;
        }
    }

    template <class Tp, class Compare, class Allocator>
    void AVLTree<Tp, Compare, Allocator>::rightrotate(node_type* node) {
        node_type* up = node->leftleaf;
        node_type* a = up->rightleaf;
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
        up->rightleaf = node;
        node->parent = up;
        node->leftleaf = a;
        if (a != NULL) {
            a->parent = node;
        }
    }
}
#endif
