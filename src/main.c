#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long file_size(FILE* file) {
    if (!file) { return 0; }
    fpos_t original = 0;
    if (fgetpos(file, &original) != 0) {
        printf("fgetpos() failed: %i\n", errno);
        return 0;
    }
    fseek(file, 0, SEEK_END);
    long out = ftell(file);
    if (fsetpos(file, &original) != 0) {
        printf("fsetpos() failed: %i\n", errno);
    }
    return out;
}

char* file_contents(char* path) {
    FILE* file = fopen(path, "r");
    if (!file) {
        printf("Could not open file at %s\n", path);
        return NULL;
    }
    long size = file_size(file);
    char* contents = malloc(size + 1);
    char* write_it = contents;
    size_t bytes_read = 0;
    while (bytes_read < size) {
        size_t bytes_read_this_iteration = fread(write_it, 1, size - bytes_read, file);
        if (ferror(file)) {
            printf("Error while reading: %i\n", errno);
            free(contents);
            return NULL;
        }
        bytes_read += bytes_read_this_iteration;
        write_it += bytes_read_this_iteration;

        if (feof(file)) { break; }
    }
    contents[bytes_read] = '\0';
    return contents;
}

void print_usage(char** argv) {
    printf("USAGE: %s <path_to_file_to_compile>\n", argv[0]);
}

typedef struct Error {
    enum ErrorType {
        ERROR_NONE = 0,
        ERROR_ARGUMENTS,
        ERROR_TYPE,
        ERROR_GENERIC,
        ERROR_SYNTAX,
        ERROR_TODO,
        ERROR_MAX,
    } type;
    char* msg;
} Error;

Error ok = { ERROR_NONE,NULL };

void print_error(Error err) {
    if (err.type == ERROR_NONE) {
        return;
    }
    printf("ERROR: ");
    assert(ERROR_MAX == 6);
    switch (err.type) {
    default:
        printf("Unknown error type...");
    case ERROR_TODO:
        printf("TODO (not implemented)");
        break;
    case ERROR_SYNTAX:
        printf("Invalid syntax");
        break;
    case ERROR_TYPE:
        printf("Mismatched types");
        break;
    case ERROR_ARGUMENTS:
        printf("Invalid arguments");
        break;
    case ERROR_NONE:
        break;
    case ERROR_GENERIC:
        break;
    }
    putchar('\n');
    if (err.msg) {
        printf("     : %s\n", err.msg);
    }
}

#define ERROR_CREATE(n, t, msg) \
	Error (n) = { (t), (msg) }

#define ERROR_PREP(n, t, message)	\
	(n).type = (t);					 \
	(n).msg = (message);            

const char* whitespace = " \r\n";
const char* delimiters = " \r\n,():";

typedef struct Token {
    char* beginning;
    char* end;
    struct Token* next;
} Token;

Token* token_create() {
    Token* token = malloc(sizeof(Token));
    assert(token && "Could not allocate memory for token");
    memset(token, 0, sizeof(Token));
    return token;
}

void tokens_free(Token* root) {
    while (root) {
        Token* token_to_free = root;
        root = root->next;
        free(token_to_free);
    }
}

void print_tokens(Token* root) {
    size_t count = 1;
    while (root) {
        if (count > 10000) { break; } // FIXME: Remove this limit.
        printf("Token %zu: ", count);
        if (root->beginning && root->end) {
            printf("%.*s", root->end - root->beginning, root->beginning);
        }
        putchar('\n');
        root = root->next;
        count++;
    }
}


/// Lex the next token from SOURCE, and point to it with BEG and END.
Error lex(char* source, Token* token) {
    Error err = ok;
    if (!source || !token) {
        ERROR_PREP(err, ERROR_ARGUMENTS, "Can not lex empty source.");
        return err;
    }
    token->beginning = source;
    token->beginning += strspn(token->beginning, whitespace); // Skip all the whitespace at the beginning.
    token->end = token->beginning;
    if (*(token->end) == '\0') { return err; }
    token->end += strcspn(token->beginning, delimiters); // Skip everything not in delimiters.
    if (token->end == token->beginning) {
        token->end += 1; // One byte if tokens are singular length.
    }
    return err;
}

//      Node-
//     /  |  \
//    0   1   2
//   / \
//  3   4
//
// Node
// `-- 0 -> 1 -> 2
//     `-- 3 -> 4

// TODO:
// |-- API to create new node.
// `-- API to add node as child.
typedef long long integer_t;
typedef struct Node {
    enum NodeType {
        NODE_TYPE_NONE,
        NODE_TYPE_INTEGER,
        NODE_TYPE_PROGRAM,
        NODE_TYPE_MAX,
    } type;
    union NodeValue {
        integer_t integer;
    } value;
    // Possible TODO: Parent?
    struct Node* children;
    struct Node* next_child;
} Node;

void print_node_impl(Node* node) {
    if (!node) { return; }
    assert(NODE_TYPE_MAX == 3 && "print_node() must handle all node types");
    // Print type + value.
    switch (node->type) {
    default:
        printf("UNKNOWN");
    case NODE_TYPE_NONE:
        printf("NONE");
        break;
    case NODE_TYPE_INTEGER:
        printf("INT:%lld", node->value.integer);
        break;
    case NODE_TYPE_PROGRAM:
        printf("PROGRAM");
        break;
    }
}

void print_node(Node* node, size_t indent_level) {
    if (!node) { return; }
    // Print indent.
    for (size_t i = 0; i < indent_level; ++i) {
        putchar(' ');
    }
    print_node_impl(node);
    putchar('\n');
    // Print children.
    Node* child = node->children;
    while (child) {
        print_node(child, indent_level + 4);
        child = child->next_child;
    }
}

// Predicates
#define nonep(node) ((node).type == NODE_TYPE_NONE)
#define integerp(node) ((node).type == NODE_TYPE_INTEGER)

// TODO: Make more efficient, possible way to do this is to keep track
// of allocated pointers and then freeing them all in one go.
void node_free(Node* root) {
    if (!root) { return; }
    Node* child = root->children;
    Node* next_child = NULL;
    while (child) {
        next_child = child->next_child;
        node_free(child);
        child = next_child;
    }
    free(root);
}

// TODO: 
// |-- API to create a new Binding.
// `-- API to add Binding to enviornment.
typedef struct Binding {
    char* id;
    Node* value;
    struct Binding* next;
} Binding;

// TODO: API to create new Environment.
typedef struct Environment {
    struct Environment* parent;
    Binding* bind;
} Environment;

void enviornment_set() {
    // Do this later with better env structure.
}

/// @return Boolean-like value; 1 for success, 0 for failure.
int token_string_equalp(char* string, Token* token) {
    if (!string || !token) { return 0; }
    char* beg = token->beginning;
    while (*string && token->beginning < token->end) {
        if (*string != *beg) {
            return 0;
        }
        string++;
        beg++;
    }
    return 1;
}

/// @return Boolean-like value; 1 upon success, 0 for failure.
int parse_integer(Token* token, Node* node) {
    if (!token || !node) { return 0; }
    if (token->end - token->beginning == 1 && *(token->beginning) == '0') {
        node->type = NODE_TYPE_INTEGER;
        node->value.integer = 0;
    } else if ((node->value.integer = strtoll(token->beginning, NULL, 10)) != 0) {
        node->type = NODE_TYPE_INTEGER;
    } else { return 0; }
    return 1;
}

Error parse_expr(char* source, Node* result) {
    size_t token_count = 0;
    Token current_token;
    current_token.next = NULL;
    current_token.beginning = source;
    current_token.end = source;
    Error err = ok;

    Node* root = calloc(1, sizeof(Node));
    assert(root && "Could not allocate memory for AST Root.");
    root->type = NODE_TYPE_PROGRAM;

    Node working_node;
    while ((err = lex(current_token.end, &current_token)).type == ERROR_NONE) {
        working_node.children = NULL;
        working_node.next_child = NULL;
        working_node.type = NODE_TYPE_NONE;
        working_node.value.integer = 0;
        size_t token_length = current_token.end - current_token.beginning;
        if (token_length == 0) { break; }
        if (parse_integer(&current_token, &working_node)) {
            // Look ahead for binary operators that include integers.
        }
        printf("Found node: ");
        print_node(&working_node, 0);
        putchar('\n');
    }
    return err;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        print_usage(argv);
        exit(0);
    }

    char* path = argv[1];
    char* contents = file_contents(path);
    if (contents) {
        //printf("Contents of %s:\n---\n\"%s\"\n---\n", path, contents);

        Node expression;
        Error err = parse_expr(contents, &expression);
        print_error(err);

        free(contents);
    }

    return 0;
}