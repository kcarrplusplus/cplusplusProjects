/*
    Bracketology 101

    There’s a certain insanity in the air this time of the 
    year that gets us thinking about tournament brackets. 
    Consider a tournament with 16 competitors, seeded 1-16, 
    and arranged in the single-elimination bracket pictured 
    above (identical to a “region” of the NCAA Division 1 
    basketball tournament). Assume that when the X-seed 
    plays the Y-seed, the X-seed has a Y/(X+Y) probability of 
    winning. E.g. in the first round, the 5-seed has a 12/17 
    chance of beating the 12-seed.

    Suppose the 2-seed has the chance to secretly swap two teams’ 
    placements in the bracket before the tournament begins. So, 
    for example, say they choose to swap the 8- and 16-seeds. 
    Then the 8-seed would play their first game against the 
    1-seed and have a 1/9 chance of advancing to the next round, 
    and the 16-seed would play their first game against the 9-seed 
    and have a 9/25 chance of advancing.

    What seeds should the 2-seed swap to maximize their (the 2-seed’s) 
    probability of winning the tournament, and how much does the swap 
    increase that probability? Give your answer to six significant 
    figures.

    source: https://www.janestreet.com/puzzles/current-puzzle/
*/
#include <iostream>
#include <vector>
#include <math.h>
#include <unordered_map>
#include <algorithm>
using namespace std;

double probabilityOfWinning(int seedX, int seedY) {
    return (double) seedX / (seedX + seedY);
}

unordered_map<int, double> createProbabilityHashMapSeed(int seed, vector<int> vec) {
    unordered_map<int, double> m;
    for (int i = 0; i < vec.size(); i++) {
        if (vec.at(i) != seed) {
            int higherSeed, lowerSeed;
            if (seed > vec[i]) {
                lowerSeed = seed;
                higherSeed = vec[i];
            } else {
                lowerSeed = vec[i];
                higherSeed = seed;
            }
            m[vec.at(i)] = probabilityOfWinning(lowerSeed, higherSeed);
        }
    }
    return m;
}

double calculateTeamSeedTouranmentWinProbability(int seed, vector<int> vec, unordered_map<int, double> m) {
    vector<int> copyVec = vec;
    double probability = 1.0;
    
    while (copyVec.size() >= 2) {
        vector<int> newVec;
        for (int i = 0; i < copyVec.size() - 1; i++) {
            int higherSeed, lowerSeed;
            if (copyVec[i] > copyVec[i+1]) {
                lowerSeed = copyVec[i+1];
                higherSeed = copyVec[i];
            } else {
                lowerSeed = copyVec[i];
                higherSeed = copyVec[i+1];
            }
            if (lowerSeed == seed) {
                probability *= m[higherSeed];
            } 
            newVec.push_back(lowerSeed);
        }
        copyVec = newVec;
    }
    return probability;
}

vector<int> nextLayer(vector<int> vec) {
    vector<int> newVect;
    int leng = vec.size()*2+1;
    for (int i = 0; i < vec.size(); i++) {
        newVect.push_back(vec[i]);
        newVect.push_back(leng - vec[i]);
    }
    return newVect;
}

vector<int> seeding(int numTeams) {
    int rounds = log(numTeams) / log(2) -1;

    vector<int> vect;
    vect.push_back(1);
    vect.push_back(2);

    for (int i = 0; i < rounds; i++) {
        vect = nextLayer(vect);
    } 
    return vect;
}

int main() {

    cout.precision(6);

    vector<int> v = seeding(16);
    unordered_map<int, double> m = createProbabilityHashMapSeed(2, v);
    // // print k v pairs of map to verify
    // for (const auto& it: m)
    //   cout << it.first << " " << it.second << endl;

    // check why initial probabilty is 0
    double topProbabilityForSeed = calculateTeamSeedTouranmentWinProbability(2, v, m);
    cout << "Probability for normal bracket is " << topProbabilityForSeed << "\n";
    
    int numToSwap;
    for (int i = 2; i < v.size(); i++) {
        if (v[i] != 2) {
            swap(v[1], v[i]);
            double swapProbabilityWinForWin = calculateTeamSeedTouranmentWinProbability(2, v, m);
            if (swapProbabilityWinForWin > topProbabilityForSeed) {
                numToSwap = v[i];
                topProbabilityForSeed = swapProbabilityWinForWin;
                cout << "Probability for swap bracket between seed 16 and " << v[1] << " is " << topProbabilityForSeed << " %\n";
            }
            swap(v[1], v[i]);
        }
        
    }
    return 0;
}