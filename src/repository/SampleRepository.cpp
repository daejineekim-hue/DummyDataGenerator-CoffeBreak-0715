#include "repository/SampleRepository.h"

#include <algorithm>
#include <fstream>
#include <sstream>

namespace dummygen::repository {

using json::JsonValue;
using model::Sample;

SampleRepository::SampleRepository(std::string filePath) : filePath_(std::move(filePath)) {
    load();
}

void SampleRepository::load() {
    samples_.clear();
    std::ifstream in(filePath_);
    if (!in.is_open()) {
        return;  // No file yet: start with an empty store.
    }
    std::ostringstream buffer;
    buffer << in.rdbuf();
    std::string text = buffer.str();
    if (text.empty()) {
        return;
    }
    JsonValue root = JsonValue::parse(text);
    for (const auto& item : root.items()) {
        samples_.push_back(Sample::fromJson(item));
    }
}

void SampleRepository::save() const {
    JsonValue root = JsonValue::makeArray();
    for (const auto& sample : samples_) {
        root.push_back(sample.toJson());
    }
    std::ofstream out(filePath_, std::ios::trunc);
    out << root.dump();
}

const Sample& SampleRepository::create(const Sample& sample) {
    samples_.push_back(sample);
    save();
    return samples_.back();
}

std::vector<Sample> SampleRepository::readAll() const { return samples_; }

std::optional<Sample> SampleRepository::readById(const std::string& id) const {
    auto it = std::find_if(samples_.begin(), samples_.end(),
                            [&id](const Sample& s) { return s.id == id; });
    if (it == samples_.end()) return std::nullopt;
    return *it;
}

bool SampleRepository::update(const std::string& id, const Sample& updated) {
    auto it = std::find_if(samples_.begin(), samples_.end(),
                            [&id](const Sample& s) { return s.id == id; });
    if (it == samples_.end()) return false;
    *it = updated;
    save();
    return true;
}

bool SampleRepository::remove(const std::string& id) {
    auto it = std::find_if(samples_.begin(), samples_.end(),
                            [&id](const Sample& s) { return s.id == id; });
    if (it == samples_.end()) return false;
    samples_.erase(it);
    save();
    return true;
}

}  // namespace dummygen::repository
