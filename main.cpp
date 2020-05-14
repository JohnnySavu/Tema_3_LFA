#include <bits/stdc++.h>
#include "Automata.cpp"

using namespace std;

int main()
{
    ifstream f("input.in");
    int n;
    string s1, s2;
    int cont = 2;
    unordered_map<char, int> stari;
    Automata aut;
    stari['S'] = 1; //il fac pe s nodul de inceput 
    stari['*'] = 2; //nodul pe care il adaug
    aut.start_node  = 1;
    aut.final_nodes.insert(2); //2 e nodul final
    aut.n_final_nodes = 1; //am un singur nod final
    aut.n_edges = n; //mereu adaug o noua muchie deci vor fi n muchii
    f >> n;
    while (n --)
    {
        f >> s1 >> s2;
        //cout << s2;
        if (stari.find(s1[0]) == stari.end()) // nu am inca nodul resp
        {
            cont ++;
            stari[s1[0]] = cont;
        }
        if (s2.size() == 1) // pot avea doar a-z, epsilon, A-Z
        {
            if (s2[0] >= 'A' and s2[0] <= 'Z')
            {
                if (stari.find(s2[0]) == stari.end()) // nu am inca nodul resp
                {
                    cont ++;
                    stari[s2[0]] = cont;
                }
                aut.edge[stari[s1[0]]]['$'].push_back(stari[s2[0]]); // adaug muchia
                aut.lang.insert('$'); //adaug in limbaj
            }
            else
            {
                aut.edge[stari[s1[0]]][s2[0]].push_back(2); // il duc in noul nod creat
                aut.lang.insert(s2[0]); //asta e pt minimizare 
            }
        }
        else // am de genul a-zA-Z
        {
                if (stari.find(s2[1]) == stari.end()) // nu am inca nodul resp
                {
                    cont ++;
                    stari[s2[1]] = cont;
                }  
                aut.edge[stari[s1[0]]][s2[0]].push_back(stari[s2[1]]); // adaug muchia
                aut.lang.insert(s2[0]); //asta e pt minimizare
        }
    }
    aut.n_nodes = stari.size(); //asta e numarul de noduri
    aut.toNFA();
    aut.toDFA();
    aut.minimizeDFA();
    aut.print();

}
