#include <bits/stdc++.h>
using namespace std;

struct Edge
{
  double distance;
  pair<int, int> u;
  pair<int, int> v;
};

bool compareEdges(const Edge &a, const Edge &b)
{
  return a.distance < b.distance;
}

double minimum_distance(int &x0, int &y0, int &x1, int &y1)
{
  double result = 0.;
  // write your code here
  result = pow((x0 - x1), 2) + pow((y0 - y1), 2);
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

    coordinates.emplace_back(x, y);
  }

  for (size_t i = 0; i < n; i += 1)
  {
    for (size_t j = 1; j < n; j += 1)
    {
      // we do want self loops, so we check if it's a self loop
      if (i != j)
        edge_list.emplace_back(minimum_distance(coordinates[i].first, coordinates[i].second, coordinates[j].first, coordinates[j].second), coordinates[i], coordinates[j]);
    }
  }

  // for (const Edge &edge : edge_list)
  // {
  // cout << "distance " << edge.distance << " u : " << edge.u.first << "," << edge.u.second << " v : " << edge.v.first << "," << edge.v.second << endl;
  // }

  // Sort the edges
  sort(edge_list.begin(), edge_list.end(), compareEdges);

  for (const Edge &edge : edge_list)
  {
    cout << "distance " << edge.distance << " u : " << edge.u.first << "," << edge.u.second << " v : " << edge.v.first << "," << edge.v.second << endl;
  }
  // std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
