/*
	First name	Tuck 
	Last name	Hong
	Student ID	01336059
	Username	tkh2017
*/

//IMPORTANT: before submitting your source code, please make sure to comment your main function (needed for automated testing)


#include <iostream>
#include <string>
#include <map>
#include <vector> //or #include <list>
#include <utility>

// do not use using namespace std

// do not alter the struct declaration
struct hufftreenode {
	char character;
	int frequency;
	hufftreenode* left;
	hufftreenode* right;
};

// do not alter the typedef
typedef hufftreenode* hufftreeptr;


// you can define and use any additional *structures* if you might need to

// YOUR CODE HERE FOR ADDIIONAL STRUCTS DECLARATION, IF ANY



/////////////////////////////////////////
// Functions declarations (prototypes) //
/////////////////////////////////////////

// do not alter these functions declarations

//utility function
bool valid_hufftree(const hufftreeptr hufftree);
 // returns true if the input hufftree is a valid Huffman tree
 // i.e. all the terminal nodes (leaves) have characters,
 // all the non-leaf nodes have two sub-trees each,
 // and the occurrence frequency of a non-leaf node equals
 // the sum of the occurrence frequencies of its two sub-trees.



std::string huffencode(const std::string& message, std::map<char, int>& freqtable, hufftreeptr& hufftree, std::map<char, std::string>& hufftable);
// encodes an input message (a string of characters) into an encoded message (string of bits) using the Huffman coding
// builds the Huffman tree and its associated encoding table (i.e. the association between the characters in the tree leaves and their encodings (string of bits))

std::string huffdecode(const std::string& encodedmessage, const hufftreeptr& hufftree);
// decodes an encoded message (a string of bits) into the original message (a string of characters) using the Huffman tree built during the encoding



// you can define and use any additional *functions* if you might need to

// YOUR CODE HERE FOR ADDIIONAL FUNCTIONS DECLARATION (NOT THE IMPLEMENTATION), IF ANY

hufftreeptr merge_tree(const hufftreeptr& t1, const hufftreeptr& t2);

void build_hufftable(std::map<char, std::string>& hufftable, hufftreeptr root, std::string& path);


///////////////////
// main function //
///////////////////

//IMPORTANT (Reminder): before submitting your source code, please make sure to comment your main function (needed for automated testing)
int main() {

	// YOUR CODE HERE FOR TESTING YOUR PROGRAM

	// an example of basic encoding/decoding
	std::string message, encodedmessage, decodedmessage;
	hufftreeptr hufftree;
	std::map<char, int> freqtable;
	std::map<char, std::string> hufftable;

	message = "go go gophers";

	// 1) encoding (compression)
	encodedmessage = huffencode(message, freqtable, hufftree, hufftable);
        
        //printing frequency table
        std::map<char, int>::iterator freqit;
        
        std::cout << "\nfrequencytable:" << std::endl;
        
        for(freqit = freqtable.begin(); freqit != freqtable.end(); freqit++) {
            
            std::cout << "(" << freqit->first << ", " << freqit->second << ")" << std::endl;
        }
        
        std::map<char, std::string>::iterator huffit;
    
        std::cout << "\nhufftable: " << std::endl;
        
        for(huffit = hufftable.begin(); huffit !=hufftable.end(); huffit++) {
            
            std::cout << "(" << huffit->first << ", " << huffit->second << ")" << std::endl;
        }
        
        std::cout << "\nencoded message is: " << std::endl;
        std::cout << encodedmessage << std::endl;
        std::cout << "size of encoded message is: " << std::endl;
        std::cout << encodedmessage.size() << std::endl;
        
	// freqtable should be as in Table 1.
	// hufftree might be as in Figure 2 (remember, the Huffman coding tree IS NOT UNIQUE. If we swap two siblings in a Huffman tree, it is still a Huffman tree of the same message.)
	// hufftable should correspond to hufftree, and might be as in Table 2 <' ',"100">, <'g',"00">, <'o',"01">, <'p',"1110">, <'h',"1101">, <'e',"101">, <'r',"1111">, <'s',"1100">.
	// encodedmessage might then be the 37-bits string "0001100000110000011110110110111111100" (i.e. "00.01.100.00.01.100.00.01.1110.1101.101.1111.1100")

	/*if(valid_hufftree(hufftree))  {
		std::cout << "valid Huffman tree." << std::endl;
	}
	else {
		std::cout << "not valid Huffman tree." << std::endl;
	}

	// 2) decoding (uncompression)
	decodedmessage = huffdecode(encodedmessage, hufftree);
	// should be "go go gophers"

	if(decodedmessage == message) {
		std::cout << "decoding OK." << std::endl;
	}
	else {
		std::cout << "decoding not OK." << std::endl;
	}*/

	return 0;
}


/////////////////////////////////////////////
// Functions definitions (implementations) //
/////////////////////////////////////////////

// YOUR CODE HERE FOR THE FUNCTIONS IMPLEMENTATIONS

std::string huffencode(const std::string& message, std::map<char, int>& freqtable, hufftreeptr& hufftree, std::map<char, std::string>& hufftable) {
    
    std::string bitstring;
    std::pair<std::map<char, int>::iterator, bool> ptr;
    
    //builds the frequency table
    for(int i = 0; i < message.size(); i++) {
        
        ptr = freqtable.insert(std::pair<char, int>(message[i], 1));
        
        if(!ptr.second) {
            
            (ptr.first)->second = (ptr.first)->second + 1;
        }
    }
    
    std::map<char, int>::iterator it;
    std::vector<hufftreeptr> forest;
    
    //builds a forest 
    for(it = freqtable.begin(); it != freqtable.end(); it++) {
        
        hufftreeptr tree = new hufftreenode;
        
        tree->character = it->first;
        tree->frequency = it->second;
        tree->left = NULL;
        tree->right = NULL;
        
        forest.push_back(tree);
    }
    
    //builds the huffman tree
    while(forest.size() > 1) {
        
        hufftreeptr tmp1 = forest[0];
        int index = 0;
        
        for(int i = 1; i < forest.size(); i++) {
            
            if(forest[i]->frequency < tmp1->frequency) {
                index = i;
                tmp1 = forest[i];
            }
        }
        
        forest.erase(forest.begin()+index);
        
        hufftreeptr tmp2 = forest[0];
        index = 0;

        for(int i = 1; i < forest.size(); i++) {
            
            if(forest[i]->frequency < tmp2->frequency) {
                index = i;
                tmp2 = forest[i];
            }
        }
        
        forest.erase(forest.begin()+index);
        
        hufftreeptr merged = merge_tree(tmp1, tmp2);

        forest.push_back(merged);
    }
    
    std::string path;
    
    //build hufftable
    build_hufftable(hufftable, forest[0], path);
    
    std::map<char, std::string>::iterator searchit;
    //obtain bitstring
    for(int i = 0; i < message.size(); i++) {
        
        searchit = hufftable.find(message[i]);
        bitstring.append(searchit->second);
    }
    
    return bitstring;
}

hufftreeptr merge_tree(const hufftreeptr& t1, const hufftreeptr& t2) {
    
    hufftreeptr node = new hufftreenode;
    
    node->frequency = t1->frequency + t2->frequency;
    node->left = t1;
    node->right = t2;
    
    return node;
}

void build_hufftable(std::map<char, std::string>& hufftable, hufftreeptr root, std::string& path) {
    
    int length = path.length();
    
    if(root->left == NULL && root->right == NULL) {
        
        hufftable[root->character] = path;
        return;
    }
    
    path.push_back('0');
    build_hufftable(hufftable, root->left, path);
    path.erase(path.begin()+length, path.end());
    
    path.push_back('1');
    build_hufftable(hufftable, root->right, path);
    path.erase(path.begin()+length, path.end());
}
    
    
