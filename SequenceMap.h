

#ifndef __SEQUENCE_MAP_H__
#define __SEQUENCE_MAP_H__



#include <iostream>
#include <vector>
#include <fstream>


using namespace std;


class SequenceMap{
public:
    //Stewart's Weiss Big Five starts here
    //default constructor
    SequenceMap() = default;
    //Destructor
    ~SequenceMap() = default;
    //Move constructor
    SequenceMap(SequenceMap &&rhs) = default;
    //Move assignment
    SequenceMap& operator=(SequenceMap &&rhs) = default;
    //copy constructor
    SequenceMap(const SequenceMap &rhs) = default;
    //copy assignment
    SequenceMap& operator=(SequenceMap &rhs) = default;
    //End of Big Five

    /*
    * Constructs A vector of SequenceMap from two strings provided
    */
    SequenceMap(const string &this_recognition_sequence, const string &this_enzyme_acro) : d_recognition_sequence{this_recognition_sequence}{
        d_enzyme_acro.push_back(this_enzyme_acro);
    }

    /*
    * Merge, assumes both Recognition Sequence are similar  to each other, then
    calls forth merge for enzyme acro within its object vector
    */
    void Merge(const SequenceMap &this_sequence){
        for(auto &i: this_sequence.d_enzyme_acro){
          d_enzyme_acro.push_back(i);
        }
    }

    /*
    * Operator < , compares strings in Sequence Map Recognition
    */
    bool  operator<(const SequenceMap &rhs) const{
        return(d_recognition_sequence < rhs.d_recognition_sequence);
    }

    /*
    * outstream operator
    */
    friend ostream& operator <<(ostream &os, SequenceMap &map_os){
        for(auto &i: map_os.d_enzyme_acro){
            os << i << " ";
        }
        return os;
    }




private:
  string d_recognition_sequence;
  vector<string> d_enzyme_acro;

};






#endif
