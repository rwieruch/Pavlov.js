#include "StateActionEncoder.h"

StateActionEncoder::StateActionEncoder(
  std::vector<observation> *observations) : d_observations(observations)
{
  _parse_states_and_actions();
}

int StateActionEncoder::state_count() const {
  return d_int_to_state.size();
}

int StateActionEncoder::action_count() const {
  return d_int_to_action.size();
}

void StateActionEncoder::observations_to_int() const {
  obs_iter obs_it = d_observations -> begin();
  while (obs_it != d_observations -> end()) {
    int visits = obs_it -> state_transitions.size();

    trans_iter trans_it = obs_it -> state_transitions.begin();
    while (trans_it != obs_it -> state_transitions.end()) {
      trans_it -> encoded_state = d_state_to_int.find(trans_it -> state) -> second;
      trans_it -> encoded_state_ = d_state_to_int.find(trans_it -> state_) -> second;
      trans_it -> encoded_action = d_action_to_int.find(trans_it -> action) -> second;

      ++trans_it;
    }

    ++obs_it;
  }
}

std::map<std::string, std::string> StateActionEncoder::parse_encoded_policy(
  const std::vector<int> &encoded_policy) const
{
  std::map<std::string, std::string> policy;

  std::string state, action;
  for (int i = 0; i < encoded_policy.size(); ++i) {
    state = d_int_to_state[i];
    action = d_int_to_action[encoded_policy[i]];

    policy[state] = action;
  }

  return policy;
}

void StateActionEncoder::_parse_states_and_actions() {
  int state_index = 0;
  int action_index = 0;

  std::string state, action;

  obs_iter obs_it = d_observations -> begin();
  while (obs_it != d_observations -> end()) {
    trans_iter trans_it = obs_it -> state_transitions.begin();
    while (trans_it != obs_it -> state_transitions.end()) {
      state = trans_it -> state;
      action = trans_it -> action;

      if (d_state_to_int.find(state) == d_state_to_int.end()) {
        d_state_to_int[state] = state_index;
        d_int_to_state.push_back(state);
        state_index += 1;
      }

      if (d_action_to_int.find(action) == d_action_to_int.end()) {
        d_action_to_int[action] = action_index;
        d_int_to_action.push_back(action);
        action_index += 1;
      }

      ++trans_it;
    }
    ++obs_it;
  }
}