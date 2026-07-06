#include <bits/stdc++.h>
#include <iomanip>
using namespace std;

typedef vector<int> vi;

// Source from: https://github.com/stevenhalim/cpbook-code/blob/master/ch2/ourown/unionfind_ds.cpp
class UnionFind
{ // OOP style
private:
  vi p, rank, setSize; // vi p is the key part
  int numSets;

public:
  UnionFind(int N)
  {
    p.assign(N, 0);
    for (int i = 0; i < N; ++i)
      p[i] = i;
    rank.assign(N, 0);    // optional speedup
    setSize.assign(N, 1); // optional feature
    numSets = N;          // optional feature
  }

  int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
  bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }

  int numDisjointSets() { return numSets; }            // optional
  int sizeOfSet(int i) { return setSize[findSet(i)]; } // optional

  void unionSet(int i, int j)
  {
    if (isSameSet(i, j))
      return;                           // i and j are in same set
    int x = findSet(i), y = findSet(j); // find both rep items
    if (rank[x] > rank[y])
      swap(x, y); // keep x 'shorter' than y
    p[x] = y;     // set x under y
    if (rank[x] == rank[y])
      ++rank[y];              // optional speedup
    setSize[y] += setSize[x]; // combine set sizes at y
    --numSets;                // a union reduces numSets
  }
};

struct Edge
{
  // Definition of an Edge
  double distance;
  int u; // Store the index of the vertex (0 to n -1)
  int v; // Store the index of the vertex (0 to n -1)
};

bool compareEdges(const Edge &a, const Edge &b)
{
  // Compares if Edge b is more than Edge A
  return a.distance < b.distance;
}

double minimum_distance(int &x0, int &y0, int &x1, int &y1)
{
  double result = 0.;
  result = sqrt(pow((x0 - x1), 2) + pow((y0 - y1), 2));
  return result;
}

int main()
{
  size_t n;
  std::cin >> n;

  vector<pair<int, int>> coordinates; // vector of (x, y) coordinates
  vector<Edge> edge_list;

  for (size_t i = 0; i < n; i++) // loop for n number of coordinates
  {
    int x, y;
    cin >> x >> y;

    // Place the pair of coordinates in an array
    coordinates.emplace_back(x, y);
  }

  size_t k = 0;
  cin >> k;

  // We receive all the coordinates, then we create n^2 worth of points devoid of
  // self loops in O(n^2) time.
  for (size_t i = 0; i < n; i += 1)
  {
    for (size_t j = i + 1; j < n; j += 1) // Green pen starts i + 1!
    {
      double dist = minimum_distance(coordinates[i].first, coordinates[i].second, coordinates[j].first, coordinates[j].second);
      edge_list.push_back({dist,
                           (int)i, (int)j}); // so the i and j can be referred in the coordinates
    }
  }

  // for (const Edge &edge : edge_list)
  // {
  // cout << "distance " << edge.distance << " u : " << edge.u.first << "," << edge.u.second << " v : " << edge.v.first << "," << edge.v.second << endl;
  // }

  // Sort the edges
  sort(edge_list.begin(), edge_list.end(), compareEdges);

  cout << "Edge List " << endl;
  for (const Edge &edge : edge_list)
  {
    cout << "distance " << edge.distance << " Node u : " << edge.u << " Node v: " << edge.v << endl;
  }

  UnionFind uf(n);

  // Iterate through all the edges, in order
  for (size_t i = 0; i < edge_list.size(); i++)
  {

    Edge e = edge_list[i];
    int v = e.u; // get first endpoint ID
    int w = e.v; // get second endpoint ID

    // if (!uf.find(v,w))
    if (!uf.isSameSet(v, w))
    {
      if (k == (unsigned int)uf.numDisjointSets()) // means k clusters are already achieved
      {
        cout << "B result: " << fixed << std::setprecision(9) << edge_list[i].distance << endl; // so the next edge distance is the maximum possible minimum distance
        break;
      }
      uf.unionSet(v, w); // combine trees
    }
  }
}