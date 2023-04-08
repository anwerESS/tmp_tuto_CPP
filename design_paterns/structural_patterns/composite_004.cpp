#include <iostream>
#include <string>
#include <vector>
#include <memory>

class JsonValue {
public:
	virtual ~JsonValue() = default;
	virtual std::string toString() const = 0;
};

class JsonNumber : public JsonValue {
public:
	JsonNumber(double value) : value_{value} {}
	std::string toString() const override {
		return std::to_string(value_);
	}
private:
	double value_;
};

class JsonString : public JsonValue {
public:
	JsonString(std::string value) : value_{value} {}
	std::string toString() const override {
		return "\"" + value_ + "\"";
	}
private:
	std::string value_;
};

class JsonObject : public JsonValue {
public:
	void add(std::string key, std::shared_ptr<JsonValue> value) {
		properties_.push_back(std::make_pair(key, value));
	}
	std::string toString() const override {
		std::string result = "{";
		bool first = true;
		for (const auto& property : properties_) {
			if (!first) {
				result += ",";
			}
			result += "\"" + property.first + "\":" + property.second->toString();
			first = false;
		}
		result += "}";
		return result;
	}
private:
	std::vector<std::pair<std::string, std::shared_ptr<JsonValue>>> properties_;
};

class JsonArray : public JsonValue {
public:
	void add(std::shared_ptr<JsonValue> value) {
		elements_.push_back(value);
	}
	std::string toString() const override {
		std::string result = "[";
		bool first = true;
		for (const auto& element : elements_) {
			if (!first) {
				result += ",";
			}
			result += element->toString();
			first = false;
		}
		result += "]";
		return result;
	}
private:
	std::vector<std::shared_ptr<JsonValue>> elements_;
};

class JsonNull : public JsonValue {
public:
	std::string toString() const override {
		return "null";
	}
};

int main() {
	auto jsonNumber = std::make_shared<JsonNumber>(3.14);
	auto jsonString = std::make_shared<JsonString>("hello");
	auto jsonArray = std::make_shared<JsonArray>();
	jsonArray->add(std::make_shared<JsonString>("world"));
	jsonArray->add(std::make_shared<JsonNumber>(42));
	auto jsonObject = std::make_shared<JsonObject>();
	jsonObject->add("number", jsonNumber);
	jsonObject->add("string", jsonString);
	jsonObject->add("array", jsonArray);
	jsonObject->add("null", std::make_shared<JsonNull>());
	std::cout << jsonObject->toString() << std::endl;
	return 0;
}
