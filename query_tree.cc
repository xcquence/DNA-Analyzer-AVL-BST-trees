

#include "AvlTree.h"
#include "BinarySearchTree.h"
// You will have to add #include "SequenceMap.h"
#include "SequenceMap.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdlib>

using namespace std;

namespace {

/*
* Simple Getters to get our enzyme acro and Recognition Sequence
*/

bool getRecognitionSeq(string &db_line, string &this_recognition_sequence){
    //find our current '/' within the file
    size_t this_index = db_line.find("/");
    if(this_index == string::npos){
        return false;
    }

    this_recognition_sequence = db_line.substr(0, this_index);
    db_line = db_line.substr(this_index+1);
    return true;
}

string getEnyzmeAcro(string &db_line){

    size_t this_index = db_line.find("/");
    string enzyme = db_line.substr(0, this_index);
    db_line = db_line.substr(this_index + 1);
    return enzyme;
}


//Testing our QueryTree
template <typename TreeType>
void TestQueryTree(TreeType &a_tree){

    string this_recognition_sequence;

    while(getline(cin, this_recognition_sequence)){
    SequenceMap query{this_recognition_sequence, ""};
    SequenceMap *Enyzme = a_tree.find(query);

    if(Enyzme == nullptr){
      cout << "Not Found within" << endl;
    }
    else{
      cout << *Enyzme << endl;
    }
  }
}


// @db_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void QueryTree(const string &db_filename, TreeType &a_tree) {

    string db_line;
    ifstream thisFile;
    thisFile.open(db_filename);

    if(thisFile.fail()){
        cout <<"Cannot open file" << endl;
        abort();
    }

    for(unsigned int i = 0; i < 10; i++){
        getline(thisFile, db_line);
    }

    while(getline(thisFile, db_line)){

        string this_enzyme_acro = getEnyzmeAcro(db_line);
        string this_recognition_sequence;
        while(getRecognitionSeq(db_line, this_recognition_sequence)){
            SequenceMap sequence_map{this_recognition_sequence, this_enzyme_acro};
            a_tree.insert(sequence_map);
        }
    }

    thisFile.close();
    TestQueryTree(a_tree);

}



}  // namespace

int
main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string param_tree(argv[2]);
  cout << "Input filename is " << db_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST") {
    // Note that you will replace BinarySearchTree<int> with BinarySearchTree<SequenceMap>
    BinarySearchTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  } else if (param_tree == "AVL") {
    // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
    AvlTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  } else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
