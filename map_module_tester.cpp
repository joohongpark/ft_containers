#include "map_module_tester.hpp"

template <typename K, typename V>
void print_map(ft::map<K, V>& map) {
    std::cout << "[";
    for (typename ft::map<K, V>::iterator iter = map.begin(); iter != map.end(); iter++) {
        std::cout << "(" << (*(iter)).first << ", " << (*(iter)).second << ") ";
    }
    std::cout << "]" << std::endl;
}

void map_constructors() {
    std::cout << "[" << __func__ << "]" << std::endl;
    ft::map<int, char> default_construct;
    std::cout << "check" << std::endl;
    ft::map<int, char> range_construct(default_construct.begin(), default_construct.end()); // empty
    std::cout << "check" << std::endl;
    ft::map<int, char> copy_construct(range_construct); // empty
    std::cout << "check" << std::endl;
    print_map(default_construct);
    print_map(range_construct);
    print_map(copy_construct);

    default_construct[10] = 'a';
    default_construct[20] = 'b';
    default_construct[30] = 'c';

    ft::map<int, char> range_construct_1(default_construct.begin(), default_construct.end());
    ft::map<int, char> copy_construct_1(range_construct);

    print_map(default_construct);
    print_map(range_construct_1);
    print_map(copy_construct_1);
}

void map_assign_operator() {
    std::cout << "[" << __func__ << "]" << std::endl;
    ft::map<int, char> m;

    m[10] = 'a';
    m[20] = 'b';
    m[30] = 'c';

    ft::map<int, char> assign_op_target;

    assign_op_target = m;

    print_map(assign_op_target);
}

void map_iterators() {
    std::cout << "[" << __func__ << "]" << std::endl;
    ft::map<int, char> m;

    m[10] = 'a';
    m[20] = 'b';
    m[30] = 'c';
    
    // begin() / end() / * operator
    for (ft::map<int, char>::iterator iter = m.begin(); iter != m.end(); iter++) {
        std::cout << "(" << (*(iter)).first << ", " << (*(iter)).second << ") ";
    }
    std::cout << std::endl;
    
    // const operator, -> operator check
    for (ft::map<int, char>::const_iterator iter = m.begin(); iter != m.end(); iter++) {
        std::cout << "(" << iter->first << ", " << iter->second << ") ";
    }
    std::cout << std::endl;

    // ++, --, operation
    ft::map<int, char>::iterator a = m.begin();
    ft::map<int, char>::iterator b = m.end();
    a++;
    b--;
    std::cout << "(" << a->first << ", " << a->second << ") ";
    std::cout << "(" << b->first << ", " << b->second << ") ";

    // reverse operator test
    for (ft::map<int, char>::reverse_iterator iter = m.rbegin(); iter != m.rend(); iter++) {
        std::cout << "(" << iter->first << ", " << iter->second << ") ";
    }
    std::cout << std::endl;
}

void map_capacity_functions() {
    std::cout << "[" << __func__ << "]" << std::endl;
    ft::map<int, char> m;

    // size(), empty() test
    std::cout << "1 : " << m.size() << ", " <<  m.empty() << std::endl;

    m[10] = 'a';
    m[20] = 'b';
    m[30] = 'c';

    // size(), empty() test
    std::cout << "1 : " << m.size() << ", " <<  m.empty() << std::endl;

    print_map(m); // print m
}

void map_element_access_functions() {
    std::cout << "[" << __func__ << "]" << std::endl;
    ft::map<int, char> m;

    m[10] = 'a';
    m[20] = 'b';
    m[30] = 'c';

    print_map(m); // print m

    m[10]++;
    m[20]++;
    m[30]++;

    print_map(m); // print m
}

void map_inserts() {
    std::cout << "[" << __func__ << "]" << std::endl;
    ft::map<char, int> map_origin;
    for (char c = 'a'; c < 'z'; c++) {
        map_origin[c] = c * 10;
    }

    ft::map<char, int> map_single_element;
    ft::map<char, int> map_hint;
    ft::map<char, int> map_range;
    for (char c = 'a'; c < 'z'; c++) {
        map_single_element[c] = c * 20;
        map_hint[c] = c * 20;
        map_range[c] = c * 20;
    }

    // single element test
    ft::pair<ft::map<char, int>::iterator, bool> p1 = map_single_element.insert(ft::make_pair('a', 'a' * 20));
    ft::pair<ft::map<char, int>::iterator, bool> p2 = map_single_element.insert(ft::make_pair('A', 100));

    std::cout << p1.second << " / " << "(" << p1.first->first << ", " << p1.first->second << ")" << std::endl;
    std::cout << p2.second << " / " << "(" << p2.first->first << ", " << p2.first->second << ")" << std::endl;

    // with hint test
    ft::map<char, int>::iterator i1 = map_hint.insert(map_hint.begin(), ft::make_pair('a', 'a' * 20));
    ft::map<char, int>::iterator i2 = map_hint.insert(map_hint.begin(), ft::make_pair('A', 100));

    std::cout << "(" << i1->first << ", " << i1->second << ")" << std::endl;
    std::cout << "(" << i2->first << ", " << i2->second << ")" << std::endl;

    // range test
    map_range.insert(map_hint.begin(), map_hint.end());

    print_map(map_single_element); // print map_single_element
    print_map(map_hint); // print map_hint
    print_map(map_range); // print map_range
}

void map_erases() {
    std::cout << "[" << __func__ << "]" << std::endl;
    ft::map<char, int> mymap;
    ft::map<char, int>::iterator it;

    // insert some values:
    mymap['a'] = 10;
    mymap['b'] = 20;
    mymap['c'] = 30;
    mymap['d'] = 40;
    mymap['e'] = 50;
    mymap['f'] = 60;

    it = mymap.find('b');
    mymap.erase(it);                   // erasing by iterator
    mymap.erase('c');                  // erasing by key
    it = mymap.find('e');
    mymap.erase( it, mymap.end() );    // erasing by range

    print_map(mymap); // print mymap
}

void map_swap_clear() {
    std::cout << "[" << __func__ << "]" << std::endl;
    ft::map<int, char> m1;
    ft::map<int, char> m2;

    m1[10] = 'a';
    m1[20] = 'b';
    m1[30] = 'c';

    char* p1 = &m1[30];

    m2.swap(m1);
    print_map(m1);
    print_map(m2);

    char* p2 = &m2[30];

    std::cout << (p1 == p2) << std::endl; // swap 동작 시 저장된 자료에 대해 재할당이 발생하면 안된다. 그래서 1이어야 한다.

    m2.clear();
    print_map(m1);
    print_map(m2);
}

void map_find() {
    std::cout << "[" << __func__ << "]" << std::endl;
    ft::map<char,int> mymap;
    ft::map<char,int>::iterator it;

    mymap['a'] = 50;
    mymap['b'] = 100;
    mymap['c'] = 150;
    mymap['d'] = 200;

    it = mymap.find('b');
    if (it != mymap.end()) {
        mymap.erase(it);
    }

    // print content:
    std::cout << "elements in mymap:" << std::endl;
    std::cout << "a => " << mymap.find('a')->second << std::endl;
    std::cout << "c => " << mymap.find('c')->second << std::endl;
    std::cout << "d => " << mymap.find('d')->second << std::endl;
}

void map_count() {
    std::cout << "[" << __func__ << "]" << std::endl;
    ft::map<char, int> mymap;

    mymap ['a'] = 101;
    mymap ['c'] = 202;
    mymap ['f'] = 303;

    for (char c = 'a'; c < 'h'; c++) {
        std::cout << c;
        if (mymap.count(c) > 0) {
            std::cout << " is an element of mymap." << std::endl;
        } else {
            std::cout << " is not an element of mymap." << std::endl;
        }
    }
}
void map_lower_bound() {
    std::cout << "[" << __func__ << "]" << std::endl;
    ft::map<char, int> mymap;
    ft::map<char, int>::iterator itlow, itup;

    mymap['a'] = 20;
    mymap['b'] = 40;
    mymap['c'] = 60;
    mymap['d'] = 80;
    mymap['e'] = 100;

    itlow = mymap.lower_bound('b');  // itlow points to b
    itup = mymap.upper_bound('d');   // itup points to e (not d!)

    mymap.erase(itlow, itup);        // erases [itlow,itup)

    // print content:
    for (ft::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it) {
        std::cout << it->first << " => " << it->second << std::endl;
    }
}

void map_upper_bound() {
    std::cout << "[" << __func__ << "]" << std::endl;
    ft::map<char, int> mymap;
    ft::map<char, int>::iterator itlow,itup;

    mymap['a'] = 20;
    mymap['b'] = 40;
    mymap['c'] = 60;
    mymap['d'] = 80;
    mymap['e'] = 100;

    itlow=mymap.lower_bound ('b');  // itlow points to b
    itup=mymap.upper_bound ('d');   // itup points to e (not d!)

    mymap.erase(itlow,itup);        // erases [itlow,itup)

    // print content:
    for (ft::map<char, int>::iterator it=mymap.begin(); it != mymap.end(); ++it)
        std::cout << it->first << " => " << it->second << std::endl;
}

void map_equal_range() {
    std::cout << "[" << __func__ << "]" << std::endl;
    ft::map<char, int> mymap;

    mymap['a'] = 10;
    mymap['b'] = 20;
    mymap['c'] = 30;

    ft::pair<ft::map<char, int>::iterator, ft::map<char, int>::iterator> ret;
    ret = mymap.equal_range('b');

    std::cout << "lower bound points to: " << ret.first->first << " => " << ret.first->second << std::endl;

    std::cout << "upper bound points to: " << ret.second->first << " => " << ret.second->second << std::endl;
}

void map_relational_operators() {
    std::cout << "[" << __func__ << "]" << std::endl;
    ft::map<char, int> foo;
    ft::map<char, int> bar;

    foo['a'] = 10;
    foo['b'] = 20;
    foo['c'] = 30;

    bar['a'] = 10;
    bar['b'] = 20;
    bar['c'] = 40;

    if (foo==bar) std::cout << "foo and bar are equal\n";
    if (foo!=bar) std::cout << "foo and bar are not equal\n";
    if (foo< bar) std::cout << "foo is less than bar\n";
    if (foo> bar) std::cout << "foo is greater than bar\n";
    if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
    if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
}
