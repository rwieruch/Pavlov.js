#include <vector>
#include "DataStructures.h"

using namespace std;

class RewardParser {
  public:
    RewardParser(vector<observation> &obs, int state_count);
    vector<double> rewards() const;

  private:
    vector<observation> d_obs;
    int d_state_count;
};

inline RewardParser::RewardParser(vector<observation> &obs, int state_count)
  : d_obs(obs),
    d_state_count(state_count) {}
