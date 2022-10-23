#define NULL 0

#include <iostream>
#include <string>

using namespace std;

// maximum number of nodes supported by symbol table
const int max_node_number = 1000;

class Node {
public:
	string id, scope, type;
	Node* next;
	int line_nr;

	Node() { next = NULL; }

	Node(string key, string value, string type, int line_nr) {
		this->id = key;
		this->scope = value;
		this->type = type;
		this->line_nr = line_nr;
		next = NULL;
	}

	void print_node() { cout << "id: " << id << " type: " << type << " scope: " << scope << " line: " << line_nr << endl; }

	friend class SymbolTable;
};

class SymbolTable {
	Node* header[max_node_number];

public:
	SymbolTable() { for (int i = 0; i < max_node_number; i++) header[i] = NULL; }
	int hash_function(string id);
	bool insert_node(string id, string scope, string type, int line_nr);
	string search_node(string id);
};

string SymbolTable::search_node(string id)
{
	int index = hash_function(id);
	Node* start = header[index];

	if (start == NULL) return "Couldn't find node with id: " + id;

    while (start != NULL) {
		if (start->id == id) {
			start->print_node();
			return "[FOUND NODE]: " + start->id + " " + start->scope + " " + start->type;
		}
		start = start->next;
	}

	return "Couldn't find node with id: " + id;
}

bool SymbolTable::insert_node(string id, string scope, string type, int line_nr)
{
	int index = hash_function(id);
	Node* p = new Node(id, scope, type, line_nr);

	if (header[index] == NULL) {
		header[index] = p;
		cout << id << " " << scope << " " << type << " [INSERTED]";
		return true;
	}

	else {
		Node* start = header[index];
		while (start->next != NULL) start = start->next;
		start->next = p;
		cout << id << " " << scope << " " << type << " [INSERTED]";
		return true;
	}

	return false;
}

int SymbolTable::hash_function(string id)
{
	int ascii_total = 0;
	for (int i = 0; i < id.length(); i++) { ascii_total = ascii_total + id[i]; }
	return (ascii_total % 103);
}

int main()
{
	SymbolTable symbol_table;

	if (symbol_table.insert_node("if", "local", "keyword", 111)) cout << " OK" << endl << endl;
	else cout << "Insertion ERROR" << endl;

	if (symbol_table.insert_node("number", "local", "variable", 29)) cout << " OK " << endl << endl;

	else cout << "Insertion ERROR" << endl;

	cout << symbol_table.search_node("if") << endl;
	cout << symbol_table.search_node("asd") << endl;


	return 0;
}
