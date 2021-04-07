/*
Input Format

The first line consists of two space separated integers, N and Q.
N specifies the number of lines in the HRML source program.
Q specifies the number of queries.

The following N lines consist of either an opening tag with zero or more attributes or a closing tag. There is a space after the tag-name, attribute-name, '=' and value.There is no space after the last value. If there are no attributes there is no space after tag name.

Q queries follow. Each query consists of string that references an attribute in the source program.More formally,
each query is of the form tag_i1.tag_i2.tag_i3.....tag_im~attrName
where m >= 1 and tag_i1, tag_i2, tag_i3, ..., tag_im are valid tags in the input.

Constraints
* 1 <= N <= 20
* 1 <= Q <= 20
* Each line in the source program contains, at most, 200 characters.
* Every reference to the attributes in the Q queries contains at most 200 characters.
* All tag names are unique and the HRML source program is logically correct, i.e. valid nesting.
* A tag can may have no attributes.

Output Format

Print the value of the attribute for each query. Print "Not Found!" without quotes if the attribute does not exist. 

Sample Input

10 10
<a value = "GoodVal">
<b value = "BadVal" size = "10">
</b>
<c height = "auto">
<d size = "3">
<e strength = "2">
</e>
</d>
</c>
</a>
a~value
b~value
a.b~size
a.b~value
a.b.c~height
a.c~height
a.d.e~strength
a.c.d.e~strength
d~sze
a.c.d~size

Sample Output

GoodVal
Not Found!
10
BadVal
Not Found!
auto
Not Found!
2
Not Found!
3

*/

#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

struct Node {
    string tagName;
    map<string, string> attributes;
    vector<Node*> children;
    Node* parent = nullptr;
    Node(string name) : tagName(name) {}
    
    enum Direction { None, Tag, Attr };
};

Node* root = nullptr;

vector<string> Tokenize(string& line) {
    vector<string> result;
    string parsedStr;
    parsedStr.reserve(200);
    for(unsigned int i = 1; i < line.length(); ++i) {
        switch(line[i]) {
            case ' ':
            case '"':
            case '>':
                if(parsedStr.length() > 0) {
                    result.push_back(parsedStr);
                    parsedStr.clear();
                }
                break;
            case '=':
                // omit
                break;
            default:
                parsedStr += line[i];
                break;
        }
    }
    return result;
}

void BuildIndex(int N) {
    string line;
    line.reserve(200);
    root = new Node("root");
    Node* current = root;
    vector<string> tokens;
    while(N-- > 0) {
        getline(cin, line);
        if (line[1] == '/') {
            current = current->parent;
        } else {
            tokens = Tokenize(line);
            Node* child = new Node(tokens.size() > 0 ? tokens[0] : "");
            for(unsigned int i = 1; i + 1 < tokens.size(); i+=2) {
                child->attributes[tokens[i]] = tokens[i+1];                
            }
            cout << "Insert Child" << endl;
            cout << "name: " << child->tagName << endl;
            for(const auto& pair : child->attributes) {
                cout << "attr: " << pair.first << "=" << pair.second << endl;          
            }
            current->children.push_back(child);
            child->parent = current;
            current = child;
        }
    }
}

void SearchQueries(int Q) {
    string line;
    line.reserve(200);
    string parsedStr;
    parsedStr.reserve(200);
    Node* current = nullptr;
    Node::Direction dir = Node::Direction::None; 
    while(Q-- > 0) {
        getline(cin, line);
        current = root;
        parsedStr.clear();
        dir = Node::Direction::Tag;
        for(unsigned int i = 0, j = 0; i < line.length(); ++i) {
            if (line[i] != '.' && line[i] != '~') {
                parsedStr += line[i];
            }
            
            if(line[i] == '.' || line[i] == '~' || i == line.length() - 1) {
                if(dir == Node::Direction::Tag) {
                    for(const auto& child : current->children) {
                        if(child->tagName == parsedStr) {
                            current = child;
                            parsedStr.clear();
                            break;
                        }
                    }
                } else if (dir == Node::Direction::Attr) {
                    for(const auto& pair : current->attributes) {
                        if(pair.first == parsedStr) {
                            cout << pair.second << endl;
                            parsedStr.clear();
                            break;
                        }
                    }
                }            
                if(parsedStr.length() > 0) {
                    cout << "Not Found!" << endl;
                    break;
                }
                if(line[i] == '.'){
                    dir = Node::Direction::Tag;
                } else if (line[i] == '~') {
                    dir = Node::Direction::Attr;
                } else {
                    dir = Node::Direction::None;
                }
            }
        }
    }
}

void PrintNodes(Node* node = root) {
    if(node != nullptr) {
        cout << "Print" << endl;
        cout << "name: " << node->tagName << endl;
        for(const auto& pair : node->attributes) {
            cout << "attr: " << pair.first << "=" << pair.second << endl;          
        }
        for(const auto& child : node->children) {
            PrintNodes(child);
        }    
    }
}

void DeleteNode(Node* node = root) {
    if(node != nullptr) {
        for(const auto& child : node->children) {
            DeleteNode(child);
        }
        delete node;
        node = nullptr;       
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int N, Q;
    cin >> N >> Q;
/*
When consuming whitespace-delimited input (e.g. int n; std::cin >> n;) any whitespace that follows, including a newline character, will be left on the input stream. Then when switching to line-oriented input, the first line retrieved with getline will be just that whitespace. In the likely case that this is unwanted behaviour
*/
    std::cin >> std::ws;
    
    BuildIndex(N);
    PrintNodes();
    SearchQueries(Q);
    DeleteNode();
    return 0;
}
