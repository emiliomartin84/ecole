#pragma once

#include <memory>
#include <optional>

#include <xtensor/xtensor.hpp>
#include <xtensor/xview.hpp>

#include "ecole/observation/abstract.hpp"

namespace ecole::observation {

class StrongBranchingScores : public ObservationFunction<std::optional<xt::xtensor<double, 1>>> {
public:
	bool pseudo_candidates;

	StrongBranchingScores(bool pseudo_candidates = true);

	std::optional<xt::xtensor<double, 1>> obtain_observation(scip::Model& model) override;
};

}  // namespace ecole::observation
