#include <iostream>
#include <string>
#include <vector>
using namespace std;

class grafixCorrupt{
public:
    int selectWord(vector<string> dictionary, string candidate){
        int maxMatched = 0, lowestIdx = 0;
        for(int idx=0; idx < dictionary.size(); idx++){
            int matched = 0;
            string word = dictionary[idx];
            for(int i=0; i<candidate.length(); i++){
            	if(word[i] == candidate[i])
                    matched++;
            }
            
            if(matched > maxMatched){
                maxMatched = matched;
                lowestIdx = idx;
            }
        }
    	return !lowestIdx ? -1 : lowestIdx;    
    }
};
