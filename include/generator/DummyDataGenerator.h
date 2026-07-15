#pragma once

#include <random>
#include <vector>

#include "model/Sample.h"
#include "repository/SampleRepository.h"

namespace dummygen::generator {

// Creates plausible-looking Sample records for testing and immediately
// persists them through SampleRepository, so the dummy data lands in the
// same JSON store the DataPersistence/DataMonitor PoCs use.
class DummyDataGenerator {
public:
    explicit DummyDataGenerator(repository::SampleRepository& repository);

    std::vector<model::Sample> generate(int count);

private:
    repository::SampleRepository& repository_;
    std::mt19937 rng_;

    int nextIdSuffix() const;
    model::Sample generateOne(int idSuffix);
};

}  // namespace dummygen::generator
