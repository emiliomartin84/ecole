#include <type_traits>

#include <catch2/catch.hpp>

#include "ecole/environment/configuring.hpp"
#include "ecole/observation/nothing.hpp"
#include "ecole/traits.hpp"

using namespace ecole;

#define STATIC_REQUIRE_SAME(A, B) STATIC_REQUIRE(std::is_same_v<A, B>)

TEST_CASE("Detect if observation function", "[trait]") {
	SECTION("Positive tests") { STATIC_REQUIRE(trait::is_observation_function_v<observation::Nothing>); }

	SECTION("Negative tests") {
		STATIC_REQUIRE_FALSE(trait::is_observation_function_v<ecole::NoneType>);
		STATIC_REQUIRE_FALSE(trait::is_observation_function_v<environment::Configuring<>>);
	}
}

TEST_CASE("Detect if environment", "[trait]") {
	SECTION("Positive tests") { STATIC_REQUIRE(trait::is_environment_v<environment::Configuring<>>); }

	SECTION("Negative tests") {
		STATIC_REQUIRE_FALSE(trait::is_environment_v<environment::ConfiguringDynamics>);
		STATIC_REQUIRE_FALSE(trait::is_environment_v<observation::Nothing>);
	}
}

TEST_CASE("Detect if dynamics", "[trait]") {
	SECTION("Positive tests") { STATIC_REQUIRE(trait::is_dynamics_v<environment::ConfiguringDynamics>); }

	SECTION("Negative tests") {
		STATIC_REQUIRE_FALSE(trait::is_dynamics_v<environment::Configuring<>>);
		STATIC_REQUIRE_FALSE(trait::is_dynamics_v<observation::Nothing>);
	}
}

TEST_CASE("Detect observation type", "[trait]") {
	STATIC_REQUIRE_SAME(trait::observation_of_t<observation::Nothing>, ecole::NoneType);
	STATIC_REQUIRE_SAME(trait::observation_of_t<environment::Configuring<>>, ecole::NoneType);
}

TEST_CASE("Detect action type", "[trait]") {
	STATIC_REQUIRE_SAME(trait::action_of_t<environment::Configuring<>>, environment::ParamDict);
	STATIC_REQUIRE_SAME(trait::action_of_t<environment::ConfiguringDynamics>, environment::ParamDict);
}

TEST_CASE("Detect action set type", "[trait]") {
	STATIC_REQUIRE_SAME(trait::action_set_of_t<environment::Configuring<>>, ecole::NoneType);
	STATIC_REQUIRE_SAME(trait::action_set_of_t<environment::ConfiguringDynamics>, ecole::NoneType);
}
