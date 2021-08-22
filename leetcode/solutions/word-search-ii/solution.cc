#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <cstring>
#include <set>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v)
{
	out << '[';
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it != v.begin())
			out << ',';
		out << *it;
	}
	out << ']';
	return out;
}

template<typename K, typename V>
ostream& operator<<(ostream& out, unordered_map<K,V> v)
{
       out << '{';
       for (auto it = v.begin(); it != v.end(); ++it) {
               if (it != v.begin())
                       out << ", ";
               out << '[' << it->first << "]: " << it->second;
       }
       out << '}';
       return out;
}

#define ALPHABET_SIZE 26

struct trie_node {
	struct trie_node *links[ALPHABET_SIZE];
	string* word;
};

static struct trie_node *trie_node_alloc(void)
{
	struct trie_node *node = new struct trie_node();
	return node;
}

static inline ssize_t trie_opcode(unsigned char c)
{
	return c - 'a';
}

static void trie_insert(struct trie_node *root, string& s)
{
	struct trie_node *node = root;
	ssize_t word_end_pos = s.size() - 1;

	for (ssize_t i = 0; i < (ssize_t)s.size(); i++) {
		ssize_t pos = trie_opcode(s[i]);
		if (node->links[pos] == nullptr) {
			auto nd = trie_node_alloc();
			if (nd == nullptr)
				return;
			node->links[pos] = nd;
		}
		node = node->links[pos];
	}
	node->word = &s;
}

class Solution {
public:
	struct bactrack_args {
		vector<vector<char>>& board;
		struct trie_node *parent;
		ssize_t rows, cols;
		set<string *>& found;
		vector<string>& res;
	};

	void backtrack(struct bactrack_args& args, ssize_t r, ssize_t c) {
		if (r < 0 || c < 0 || r >= args.rows || c >= args.cols)
			return;
		// visited
		if (args.board[r][c] == '#')
			return;

		auto v = args.board[r][c];
		auto node = args.parent->links[trie_opcode(v)];
		if (node == nullptr)
			return;
		auto prev_parent = args.parent;

		//
		// several words may appear twice
		if (node->word) {
			if (args.found.find(node->word) == args.found.end()) {
				args.found.insert(node->word);
				args.res.emplace_back(*node->word);
			}
		}

		//
		// mark as visited
		args.board[r][c] = '#';
		args.parent = node;

		backtrack(args, r + 1, c);
		backtrack(args, r - 1, c);
		backtrack(args, r, c + 1);
		backtrack(args, r, c - 1);

		//
		// restore back
		args.board[r][c] = v;
		args.parent = prev_parent;
	}

	vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
		struct trie_node *root = trie_node_alloc();
		ssize_t rows = board.size();
		ssize_t cols = board[0].size();
		set<string *> found;
		vector<string> res;

		struct bactrack_args args = {
			.board	= board,
			.parent	= root,
			.rows	= rows,
			.cols	= cols,
			.found	= found,
			.res	= res,
		};

		//
		// Build a Trie tree and consider each
		// cell as possible word start
		for (ssize_t i = 0; i < (ssize_t)words.size(); i++)
			trie_insert(root, words[i]);

		for (ssize_t r = 0; r < rows; r++) {
			for (ssize_t c = 0; c < cols; c++) {
				auto opcode = trie_opcode(board[r][c]);
				if (root->links[opcode] == nullptr)
					continue;
				backtrack(args, r, c);
			}
		}
		return res;
	}
};

int main()
{
	struct {
		vector<vector<char>> board;
		vector<string> words;
	} data[] = {
		{
			.board = {
				{'o','a','a','n'},
				{'e','t','a','e'},
				{'i','h','k','r'},
				{'i','f','l','v'},
			},
			.words = {
				{"oath"},
				{"pea"},
				{"eat"},
				{"rain"},
			}, // => [oath,eat]
		}, {
			.board = {
				{'o','a','b','n'},
				{'o','t','a','e'},
				{'a','h','k','r'},
				{'a','f','l','v'},
			},
			.words = {
				{"oa"},
				{"oaa"},
			}, // => [oa,oaa]
		}, {
			.board = {
				{'o','a','a','n'},
				{'e','t','a','e'},
				{'i','h','k','r'},
				{'i','f','l','v'},
			},
			.words = {
				{"oath"},
				{"pea"},
				{"eat"},
				{"rain"},
				{"oathi"},
				{"oathk"},
				{"oathf"},
				{"oate"},
				{"oathii"},
				{"oathfi"},
				{"oathfii"},
			},
			// => ["oath","oathk","oathf","oathfi",
			// "oathfii","oathi","oathii","oate","eat"]
		}, {
			.board = {
				{'a','b'},
				{'a','a'},
			},
			.words = {
				{"a"},
				{"aba"},
				{"baa"},
				{"bab"},
				{"aaab"},
				{"aaa"},
				{"aaaa"},
				{"aaba"},
			},
			// ["a", "aba","aaa","aaab","baa","aaba"]
		},
	};
	Solution solution;
	for (auto& d: data) {
		cout << d.board << ", " << d.words << " => " <<
			solution.findWords(d.board, d.words) << endl;
	}
	return 0;
}
