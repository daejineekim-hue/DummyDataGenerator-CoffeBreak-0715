#pragma once

#include <optional>
#include <string>
#include <vector>

#include "model/Sample.h"

namespace dummygen::repository {

// CRUD repository for Sample entities, persisted as a JSON array in a file.
// Every mutating call (create/update/remove) writes the full file back to
// disk immediately so state survives process restarts.
class SampleRepository {
public:
    explicit SampleRepository(std::string filePath);

    const model::Sample& create(const model::Sample& sample);
    std::vector<model::Sample> readAll() const;
    std::optional<model::Sample> readById(const std::string& id) const;
    bool update(const std::string& id, const model::Sample& updated);
    bool remove(const std::string& id);

private:
    std::string filePath_;
    std::vector<model::Sample> samples_;

    void load();
    void save() const;
};

}  // namespace dummygen::repository
