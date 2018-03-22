
#include "AvlTree.h"
#include "BinarySearchTree.h"
#include "SequenceMap.h"
// You will have to add #include "SequenceMap.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <math.h>
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

/*
Calculating Nodes, AverageDepth, Ratio Average Depth to LogN base 2 of the selected
tree. This is 2(b) of the assignment following numbers : 2 , 3a, 3b.
*/

template<typename TreeType>
string calculateNodesAndInternalPathLength(TreeType &a_tree){
    stringstream ss;
    int NumberOfNodes = a_tree.NumberOfNodes();
    float AverageDepth = (float)a_tree.InternalPathLength()/NumberOfNodes;
    float RatioAverageDepthtoLOGN = AverageDepth/(log2(NumberOfNodes));

    ss << "2: <integer> " << NumberOfNodes <<endl;
    ss << "3a: <float> " << AverageDepth << endl;
    ss << "3b: <float> " << RatioAverageDepthtoLOGN << endl;

    return ss.str();

}

/*
Searching our queried SequenceMap to see if we have found the recognition sequence along with its
Enyzme Acronym. This is 2(b) part of the assignment following numbers: 4a, 4b.
Little warning: 4b does not show floating numbers since we are incrementing the variables in int data
type.
*/
template<typename TreeType>
string SearchQuerySequence(TreeType &a_tree, const string &sequence_filename){

    stringstream ss;
    string this_recognition_sequence;
    ifstream thisFile;

    thisFile.open(sequence_filename);

    int count = 0;
    int success = 0;
    int counted_queries = 0;

    while(getline(thisFile, this_recognition_sequence)){
        counted_queries++;
        SequenceMap query{this_recognition_sequence, ""};
        bool isFound = a_tree.contains(query, success);

        if(isFound){
            count++;
        }


    }
    ss << "4a: <integer> " << count << endl;
    ss << "4b: <float> " << (float)success/(float)counted_queries << endl;

    thisFile.close();
    return ss.str();
}

/*
Calculates our successful removal of our recognition sequence. This is part 2(b) of
the assignment along with the following numbers: 5a, 5b.
*/
template<typename TreeType>
string RemovedSequences(TreeType& a_tree, const string &sequence_filename){

    stringstream ss;
    string this_recognition_sequence;
    ifstream thisFile;

    thisFile.open(sequence_filename);


    int count = 0;
    int success_remove= 0;
    int counted_queries = 0;

    while(getline(thisFile, this_recognition_sequence)){
        bool isRemoved = false;
        counted_queries++;
        SequenceMap query{this_recognition_sequence, ""};
        a_tree.remove(query, count, isRemoved);
        if(isRemoved == true){
          success_remove++;
        }

        getline(thisFile, this_recognition_sequence);
      }

      ss << "5a: <integer>" << success_remove << endl;
      ss << "5b: <float>" << (float)count/counted_queries << endl;

      thisFile.close();
      return ss.str();

    }

/*
Calculating Nodes, AverageDepth, Ratio Average Depth to LogN base 2 of the selected
tree. This is 2(b) of the assignment following numbers : 6a , 6b, 6c.
*/
template<typename TreeType>
string calculateNodesAndInternalPathLength2(TreeType &a_tree){
    stringstream ss;
    int NumberOfNodes = a_tree.NumberOfNodes();
    float AverageDepth = (float)a_tree.InternalPathLength()/NumberOfNodes;
    float RatioAverageDepthtoLOGN = AverageDepth/(log2(NumberOfNodes));

    ss << "6a: <integer> " << NumberOfNodes <<endl;
    ss << "6b: <float>" << AverageDepth << endl;
    ss << "6c: <float> " << RatioAverageDepthtoLOGN << endl;

    return ss.str();

}




// @db_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree) {
  // Code for running Part2(b)

    string db_line;
    ifstream thisFile;
    thisFile.open(db_filename);

    if(thisFile.fail()){
      cout << "Cannot open file" << endl;
      abort();
    }

    //Skip the first 10 lines of rebase210.txt
    //Skipping header
    for(unsigned int i = 0; i < 10; i++){
      getline(thisFile, db_line);
    }

    while(getline(thisFile, db_line)){
        string this_enzyme_acro = getEnyzmeAcro(db_line);
        string this_recognition_sequence;
        while(getRecognitionSeq(db_line,this_recognition_sequence)){
            SequenceMap sequence_map{this_recognition_sequence,this_enzyme_acro};
            a_tree.insert(sequence_map);
        }

    }

    thisFile.close();


    cout << calculateNodesAndInternalPathLength(a_tree);
    cout << SearchQuerySequence(a_tree,seq_filename);
    cout << RemovedSequences(a_tree,seq_filename);
    cout << calculateNodesAndInternalPathLength2(a_tree);
}

}  // namespace

int
main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string seq_filename(argv[2]);
  const string param_tree(argv[3]);
  cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST") {
    // Note that you will replace BinarySearchTree<int> with BinarySearchTree<SequenceMap>
    BinarySearchTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  } else if (param_tree == "AVL") {
    // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
    AvlTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  } else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
