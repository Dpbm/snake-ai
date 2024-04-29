#include <gtest/gtest.h>
#include "../genetic/population.h"
#include "../game/players/player.h"

using Genetic::Population;
using Genetic::Individual;
using Players::Directions;

namespace {
  TEST(ValueTest, OnlyTwoIndividualsSelectParentsTest){
    Population p(2);
    Individual* ind1 = new Individual{nullptr, nullptr, 0, 0, Directions::LEFT, 0};
    Individual* ind2 = new Individual{nullptr, nullptr, 0, 0, Directions::LEFT, 0};

    p.append_individual(ind1);
    p.append_individual(ind2);

    Individual** parents = p.select_parents();
    ASSERT_EQ(parents[0], ind1);
    ASSERT_EQ(parents[1], ind2);
    delete[] parents;
  }
  
  TEST(ValueTest, ThreeIndividualsSelectParentsTest){
    Population p(3);
    Individual* ind1 = new Individual{nullptr, nullptr, 0, 0, Directions::LEFT, 0};
    Individual* ind2 = new Individual{nullptr, nullptr, 0, 0, Directions::LEFT, 0};
    Individual* ind3 = new Individual{nullptr, nullptr, 100, 0, Directions::LEFT, 0};

    p.append_individual(ind1);
    p.append_individual(ind2);
    p.append_individual(ind3);

    Individual** parents = p.select_parents();
    ASSERT_EQ(parents[0], ind3);
    ASSERT_EQ(parents[1], ind1);
    delete[] parents;
  }
  
  TEST(ValueTest, ThreeIndividualsMultipleFitValuesAscOrderSelectParentsTest){
    Population p(3);
    Individual* ind1 = new Individual{nullptr, nullptr, 40, 0, Directions::LEFT, 0};
    Individual* ind2 = new Individual{nullptr, nullptr, 9000, 0, Directions::LEFT, 0};
    Individual* ind3 = new Individual{nullptr, nullptr, 100, 0, Directions::LEFT, 0};

    p.append_individual(ind1);
    p.append_individual(ind2);
    p.append_individual(ind3);

    Individual** parents = p.select_parents();
    ASSERT_EQ(parents[0], ind2);
    ASSERT_EQ(parents[1], ind3);
    delete[] parents;
  }
  
  TEST(ValueTest, ThreeIndividualsMultipleFitValuesDescOrderSelectParentsTest){
    Population p(3);
    Individual* ind1 = new Individual{nullptr, nullptr, 40, 0, Directions::LEFT, 0};
    Individual* ind2 = new Individual{nullptr, nullptr, 100, 0, Directions::LEFT, 0};
    Individual* ind3 = new Individual{nullptr, nullptr, 9000, 0, Directions::LEFT, 0};

    p.append_individual(ind1);
    p.append_individual(ind2);
    p.append_individual(ind3);

    Individual** parents = p.select_parents();
    ASSERT_EQ(parents[0], ind3);
    ASSERT_EQ(parents[1], ind2);
    delete[] parents;
  }

  TEST(ValueTest, SixIndividualsMultipleFitValuesSelectParentsTest){
    Population p(6);
    Individual* ind1 = new Individual{nullptr, nullptr, 40, 0, Directions::LEFT, 0};
    Individual* ind2 = new Individual{nullptr, nullptr, 1000, 0, Directions::LEFT, 0};
    Individual* ind3 = new Individual{nullptr, nullptr, 200, 0, Directions::LEFT, 0};
    Individual* ind4 = new Individual{nullptr, nullptr, 3037, 0, Directions::LEFT, 0};
    Individual* ind5 = new Individual{nullptr, nullptr, 912, 0, Directions::LEFT, 0};
    Individual* ind6 = new Individual{nullptr, nullptr, 0, 0, Directions::LEFT, 0};

    p.append_individual(ind1);
    p.append_individual(ind2);
    p.append_individual(ind3);
    p.append_individual(ind4);
    p.append_individual(ind5);
    p.append_individual(ind6);

    Individual** parents = p.select_parents();
    ASSERT_EQ(parents[0], ind4);
    ASSERT_EQ(parents[1], ind2);
    delete[] parents;
  }
  
}
