#include <iostream>
#include <vector>
#include <limits>
#include <list>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T>* v)
{
	out << '[';
	for (auto it = v->begin(); it != v->end(); ++it) {
		if (it != v->begin())
			out << ',';
		out << *it;
	}
	out << ']';
	return out;
}

class graph {
	size_t				nr_vertices;
	list<pair<size_t, size_t>>	*adj;
	size_t				*costs;
	size_t				*parents;

public:
	graph(int nr_vertices)
	{
		this->nr_vertices	= nr_vertices;
		this->costs		= new size_t[nr_vertices];
		this->parents		= new size_t[nr_vertices];
		this->adj		= new list<pair<size_t, size_t>>[nr_vertices]();

		for (auto i = 0; i < nr_vertices; i++)
			this->costs[i] = numeric_limits<size_t>::max();
	}

	void add_edge(size_t v, size_t w, size_t cost)
	{
		this->adj[v].push_back(make_pair(w, cost));
	}

	void dijkstra(size_t start)
	{
		bool visited[this->nr_vertices] = { };
		list<size_t> queue;
		size_t v = start;

		this->costs[v] = 0;
		this->parents[v] = v;

		queue.push_front(v);
		while (!queue.empty()) {
			v = queue.front();
			queue.pop_front();

			if (!visited[v]) {
				visited[v] = true;
				cout << "visiting " << v << endl;
			}

			/*
			 * Update neighbours costs and find
			 * a node with minimum distance.
			 */
			size_t next_min = numeric_limits<size_t>::max();
			size_t next_v = v;

			for (auto it = adj[v].begin(); it != adj[v].end(); it++) {
				if (visited[it->first])
					continue;

				cout << "\tinv " << it->first << endl;
				size_t cost = this->costs[v] + it->second;

				if (cost < this->costs[it->first]) {
					this->costs[it->first] = cost;
					cout << "\t\tupdate " << it->first << " -> " << cost << endl;
					this->parents[it->first] = v;
				}

				if (next_min > cost) {
					next_min = cost;
					next_v = it->first;
				}
			}

			if (next_v != v) {
				queue.push_back(next_v);
			}
		}

		for (size_t i = 0; i < this->nr_vertices; i++) {
			cout << "start " << start << " to "
				<< i << " cost " << this->costs[i] << endl;
			cout << "\tpath ";

			size_t j = this->parents[i];
			cout << i;
			if (i == start)
				continue;
			do {
				if (j != start)
					cout << " " << j;
				j = this->parents[j];
			} while (j != start);
			cout << " " << start << endl;
		}
	}
};

int main(void)
{
	size_t start = 0;
	size_t nr_vertices = 5;

	/*
	 * (0) - 6 - (1)
	 *  |       / |  \
	 *  1    2    2    5
	 *  | /       |      \
	 * (4) - 1 - (3) - 5 - (2)
	 */

	graph g(nr_vertices);

	g.add_edge(0, 1, 6);
	g.add_edge(1, 0, 6);

	g.add_edge(1, 2, 5);
	g.add_edge(2, 1, 5);

	g.add_edge(2, 3, 5);
	g.add_edge(3, 2, 5);

	g.add_edge(3, 4, 1);
	g.add_edge(4, 3, 1);

	g.add_edge(4, 0, 1);
	g.add_edge(0, 4, 1);

	g.add_edge(4, 1, 2);
	g.add_edge(1, 4, 2);

	g.add_edge(3, 1, 2);
	g.add_edge(3, 1, 2);

	g.dijkstra(start);

	return 0;
}
