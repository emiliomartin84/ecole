#pragma once

#include "ecole/reward/abstract.hpp"
#include "ecole/scip/type.hpp"

namespace ecole::reward {

class NNodes : public RewardFunction {
public:
	void reset(scip::Model& model) override;
	Reward obtain_reward(scip::Model& model, bool done = false) override;

private:
	scip::long_int last_n_nodes = 0;
};

}  // namespace ecole::reward
