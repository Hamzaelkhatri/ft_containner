#include <iostream>
#include <map>
#include <string>
using namespace std;
int main()
{
    map<char, int, greater<int> > m;
    map<char, int>::iterator it;
    m.insert(pair<char, int>('a', 10));
    m.insert(pair<char, int>('d', 20));
    m.insert(pair<char, int>('b', 30));
    m.insert(pair<char, int>('c', 40));
    cout << "Size of the map: " << m.size() << endl;
    cout << "map contains:\n";
    for (it = m.begin(); it != m.end(); ++it)
        cout << (*it).first << " => " << (*it).second << '\n';
    for (char c = 'a'; c <= 'd'; c++)
    {
        cout << "There are " << m.count(c) << " element(s) with key " << c << ":";
        map<char, int>::iterator it;
        for (it = m.equal_range(c).first; it != m.equal_range(c).second; ++it)
            cout << ' ' << (*it).second;
        cout << endl;
    }
    if (m.count('a'))
        cout << "The key a is present\n";
    else
        cout << "The key a is not present\n";
    if (m.count('f'))
        cout << "The key f is present\n";
    else
        cout << "The key f is not present\n";
    it = m.find('b');
    m.erase(it);
    cout << "Size of the map: " << m.size() << endl;
    cout << "map contains:\n";
    for (it = m.begin(); it != m.end(); ++it)
        cout << (*it).first << " => " << (*it).second << '\n';
    return 0;
}