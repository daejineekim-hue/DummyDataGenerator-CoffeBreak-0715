#include "model/Sample.h"

namespace dummygen::model {

using json::JsonValue;

JsonValue Sample::toJson() const {
    JsonValue obj = JsonValue::makeObject();
    obj["id"] = JsonValue::makeString(id);
    obj["name"] = JsonValue::makeString(name);
    obj["avgProcessTimeMin"] = JsonValue::makeNumber(avgProcessTimeMin);
    obj["yieldRate"] = JsonValue::makeNumber(yieldRate);
    obj["stock"] = JsonValue::makeNumber(stock);
    return obj;
}

Sample Sample::fromJson(const JsonValue& value) {
    Sample sample;
    sample.id = value.at("id").asString();
    sample.name = value.at("name").asString();
    sample.avgProcessTimeMin = value.at("avgProcessTimeMin").asNumber();
    sample.yieldRate = value.at("yieldRate").asNumber();
    sample.stock = static_cast<int>(value.at("stock").asNumber());
    return sample;
}

}  // namespace dummygen::model
