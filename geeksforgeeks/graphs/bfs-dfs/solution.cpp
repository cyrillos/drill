#include <iostream>
#include <vector>
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
	size_t		nr_vertices;
	list<size_t>	*adj;		// adjacency list

public:
	graph(int nr_vertices)
	{
		this->nr_vertices = nr_vertices;
		this->adj = new list<size_t>[nr_vertices]();
	}

	void add_edge(size_t v, size_t w)
	{
		this->adj[v].push_back(w);
	}

	vector<size_t> *dfs(size_t s)
	{
		bool *visited = new bool[this->nr_vertices]();
		list<size_t> queue;

		vector<size_t> *path = new vector<size_t>;

		queue.push_front(s);

		while (!queue.empty()) {
			s = queue.front();
			queue.pop_front();

			if (!visited[s]) {
				visited[s] = true;
				path->push_back(s);
			};

			for (auto it = adj[s].begin(); it != adj[s].end(); it++) {
				if (!visited[*it])
					queue.push_front(*it);
			}
		}

		return path;
	}

	vector<size_t>* bfs(size_t s)
	{
		bool *visited = new bool[this->nr_vertices]();
		list<size_t> queue;

		vector<size_t> *path = new vector<size_t>;

		queue.push_back(s);

		while (!queue.empty()) {
			s = queue.front();
			queue.pop_front();

			if (!visited[s]) {
				visited[s] = true;
				path->push_back(s);
			}

			for (auto it = adj[s].begin(); it != adj[s].end(); it++) {
				if (!visited[*it])
					queue.push_back(*it);
			}
		}

		return path;
	}
};

int main(void)
{
	vector<size_t> *path;
	size_t s = 0;
	graph g(5);

	g.add_edge(0, 1);
	g.add_edge(0, 3);
	g.add_edge(1, 2);
	g.add_edge(3, 4);
	g.add_edge(4, 2);


	path = g.bfs(s);
	cout << "bfs from vertex " << s << " => " << path << endl;

	path = g.dfs(s);
	cout << "dfs from vertex " << s << " => " << path << endl;

	return 0;
}
