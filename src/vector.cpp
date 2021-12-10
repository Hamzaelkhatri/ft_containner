#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "vector.hpp"
using namespace std;
int main()
{
    // compare between ft::Vector and std::vector
    ft::vector<int> v1;
    std::vector<int> v2;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);

    v2.push_back(1);
    v2.push_back(2);
    v2.push_back(3);
    v2.push_back(4);
    v2.push_back(5);
    ft::vector<int> v3(10, 1);
    std::vector<int> v12(10, 1);
    v3.swap(v1);
    v12.swap(v2);

    // print vector content itertor
    ft::vector<int>::iterator it = v3.begin();
    std::vector<int>::iterator it2 = v12.begin();
    while (it != v3.end())
    {
        cout << *it << " ";
        it++;
    }
    cout << endl;
    while (it2 != v12.end())
    {
        cout << *it2 << " ";
        it2++;
    }
    cout << endl;

    // print v1 with iterator
    cout << "v1 with iterator" << endl;
    for (ft::vector<int>::iterator it = v1.begin(); it != v1.end(); ++it)
        cout << *it << " ";
    cout << endl;

    // print v2 with iterator
    cout << "v2 with iterator" << endl;
    for (std::vector<int>::iterator it = v2.begin(); it != v2.end(); ++it)
        cout << *it << " ";

    // clear v1 and v2
    v1.clear();
    v2.clear();
    // check if v1 and v2 are empty
    cout << endl
         << "v1 is empty: " << v1.empty() << endl;
    cout << "v2 is empty: " << v2.empty() << endl;

    // insert v1 and v2 with insert
    v1.insert(v1.begin(), 1);
    v1.insert(v1.begin(), 2);
    v1.insert(v1.begin(), 3);
    v1.insert(v1.begin(), 4);
    v1.insert(v1.begin(), 5);

    v2.insert(v2.begin(), 1);
    v2.insert(v2.begin(), 2);
    v2.insert(v2.begin(), 3);
    v2.insert(v2.begin(), 4);
    v2.insert(v2.begin(), 5);

    // print v1 with iterator
    cout << endl
         << "v1 with iterator" << endl;

    for (ft::vector<int>::iterator it = v1.begin(); it != v1.end(); ++it)
        cout << *it << " ";
    cout << endl;

    // print v2 with iterator
    cout << "v2 with iterator" << endl;
    for (std::vector<int>::iterator it = v2.begin(); it != v2.end(); ++it)
        cout << *it << " ";

    // print size of v1 and v2
    cout << endl
         << "v1 size: " << v1.size() << endl;
    cout << "v2 size: " << v2.size() << endl;

    // resize v1 and v2
    v1.resize(10);
    v2.resize(10);

    // recheck size of v1 and v2
    cout << endl
         << "v1 size: " << v1.size() << endl;
    cout << "v2 size: " << v2.size() << endl;

    // erase v1 and v2
    v1.erase(v1.begin());
    v1.erase(v1.begin());
    v1.erase(v1.begin());
    v1.erase(v1.begin());
    v1.erase(v1.begin());

    v2.erase(v2.begin());
    v2.erase(v2.begin());
    v2.erase(v2.begin());
    v2.erase(v2.begin());
    v2.erase(v2.begin());

    // check if v1 and v2 are empty
    cout << endl
         << "v1 is empty: " << v1.empty() << endl;
    cout << "v2 is empty: " << v2.empty() << endl;
    // add data with multiple constructors

    // use insert to add data v3
    v3.insert(v3.begin(), 2);
    v3.insert(v3.begin(), 3);
    v3.insert(v3.begin(), 4);

    // print v3 with iterator
    cout << endl
         << "v3 with iterator" << endl;
    for (ft::vector<int>::iterator it = v3.begin(); it != v3.end(); ++it)
        cout << *it << " ";

    std::vector<int> v4(10, 1);
    // use insert to add data v4
    v4.insert(v4.begin(), 2);
    v4.insert(v4.begin(), 3);
    v4.insert(v4.begin(), 4);

    // print v4 with iterator
    cout << endl
         << "v4 with iterator" << endl;
    for (std::vector<int>::iterator it = v4.begin(); it != v4.end(); ++it)
        cout << *it << " ";

    // print v3 with iterator
    cout << endl
         << "v3 with iterator" << endl;
    for (ft::vector<int>::iterator it = v3.begin(); it != v3.end(); ++it)
        cout << *it << " ";
    cout << endl;

    // print v4 with iterator
    cout << "v4 with iterator" << endl;
    for (std::vector<int>::iterator it = v4.begin(); it != v4.end(); ++it)
        cout << *it << " ";

    // print size of v3 and v4
    cout << endl
         << "v3 size: " << v3.size() << endl;
    cout << "v4 size: " << v4.size() << endl;

    // assign v3 and v4
    v3.assign(v4.begin(), v4.end());
    v4.assign(v3.begin(), v3.end());

    // print v3 with iterator
    cout << endl
         << "v3 with iterator" << endl;
    for (ft::vector<int>::iterator it = v3.begin(); it != v3.end(); ++it)
        cout << *it << " ";
    cout << endl;

    // print v4 with iterator
    cout << "v4 with iterator" << endl;
    for (std::vector<int>::iterator it = v4.begin(); it != v4.end(); ++it)
        cout << *it << " ";

    // free memory
    v1.clear();
    v2.clear();
    v3.clear();
    v4.clear();

    // get a bug with the following code
    v1.assign(v2.begin(), v2.end());
    v2.assign(v1.begin(), v1.end());
    v1.assign(v2.begin(), v2.end());
    v2.assign(v1.begin(), v1.end());

    // test all the functions of the class vector
    ft::vector<int> v5(10, 1);

    v5.push_back(2);
    v5.push_back(3);

    // print v5 with iterator
    cout << endl
         << "v5 with iterator" << endl;
    for (ft::vector<int>::iterator it = v5.begin(); it != v5.end(); ++it)
        cout << *it << " ";

    v5.insert(v5.begin(), 4);
    v5.insert(v5.begin(), 5);

    v5.erase(v5.begin());
    v5.erase(v5.begin());

    // print v5 with iterator
    cout << endl
         << "v5 with iterator" << endl;
    for (ft::vector<int>::iterator it = v5.begin(); it != v5.end(); ++it)
        cout << *it << " ";

    v5.resize(10);
    // print v5 with iterator
    cout << endl
         << "v5 with iterator" << endl;
    for (ft::vector<int>::iterator it = v5.begin(); it != v5.end(); ++it)
        cout << *it << " ";
    v5.clear();
    // print v5 with iterator
    cout << endl
         << "v5 with iterator" << endl;
    for (ft::vector<int>::iterator it = v5.begin(); it != v5.end(); ++it)
        cout << *it << " ";
    v5.assign(v5.end(), v5.begin());
    // print v5 with iterator
    cout << endl
         << "v5 with iterator" << endl;
    for (ft::vector<int>::iterator it = v5.begin(); it != v5.end(); ++it)
        cout << *it << " ";
    // print v5 with iterator
    // cout << endl
    //      << "v5 with iterator" << endl;
    // for (ft::vector<int>::iterator it = v5.begin(); it != v5.end(); ++it)
    //     cout << *it << " ";

    // // print v1 with iterator

    v5.reserve(10);
    // print v5 with iterator
    cout << endl
         << "v5 with iterator" << endl;
    for (ft::vector<int>::iterator it = v5.begin(); it != v5.end(); ++it)
        cout << *it << " ";
    v5.resize(10);
    // print v5 with iterator
    cout << endl
         << "v5 with iterator" << endl;
    for (ft::vector<int>::iterator it = v5.begin(); it != v5.end(); ++it)
        cout << *it << " ";
    // test operator=
    ft::vector<int> v6(10, 1);
    ft::vector<int> v7;
    v7 = v6;
    // print v6 with iterator
    cout << endl
         << "v6 with iterator" << endl;
    for (ft::vector<int>::iterator it = v6.begin(); it != v6.end(); ++it)
        cout << *it << " ";
    // print v7 with iterator
    cout << endl
         << "v7 with iterator" << endl;
    for (ft::vector<int>::iterator it = v7.begin(); it != v7.end(); ++it)
        cout << *it << " ";
    // vetor de string
    ft::vector<std::string> v8(10, "test");
    // print v8 with iterator
    cout << endl
         << "v8 with iterator" << endl;
    for (ft::vector<std::string>::iterator it = v8.begin(); it != v8.end(); ++it)
        cout << *it << " ";
    return 0;
}