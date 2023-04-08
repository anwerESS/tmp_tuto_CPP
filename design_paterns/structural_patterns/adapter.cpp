// The Adapter design pattern is a structural pattern that allows objects with incompatible interfaces to work together. It acts as a bridge between two incompatible interfaces, translating one interface into another that the client expects. This pattern is used when an existing class (the Adaptee) has a different interface than what the client expects (the Target). The Adapter pattern provides a way to use the existing class and its interface without modifying its source code.

// In real life, the Adapter pattern can be seen in a variety of contexts. Here are some examples:

// Media Adapters: Many electronic devices have different ports for different types of media, such as HDMI, VGA, or DisplayPort. Adapters can be used to convert one type of media to another so that devices with different ports can work together.

// Language Adapters: When software applications written in different programming languages need to work together, language adapters can be used to translate data between them.

// Legacy System Integration: In many cases, companies have legacy systems that are still in use but have interfaces that are no longer compatible with newer systems. Adapters can be used to bridge the gap between the legacy system and the newer system, allowing them to work together seamlessly.

// Third-party Library Integration: When using third-party libraries, sometimes the interface of the library doesn't match the requirements of the client code. An adapter can be used to provide a compatible interface to the client code, allowing it to use the library without modification.


// In this example, we have a LegacyAPI class that has an existing interface that expects data in XML format, and a API interface that we want to use instead, which allows us to send data in JSON format. We create a JsonToXmlAdapter class that adapts the API interface to the LegacyAPI interface by implementing the sendData() method in terms of the existing sendDataXML() method and converting the JSON data to XML format. Finally, we use the adapter to send the JSON data to the LegacyAPI using the sendData() method from the API interface. The conversion from JSON to XML is implemented using a simple unordered map to store the key-value pairs and manually constructing the XML string.

#include <iostream>
#include <string>
#include <unordered_map>

// Adaptee: defines the existing interface that needs to be adapted.
class LegacyAPI
{
public:
	void sendDataXML(const std::string &data)
	{
		std::cout << "Sending XML data: " << data << std::endl;
	}
};

// Target: defines the domain-specific interface that Client uses.
class API
{
public:
	virtual void sendData(const std::unordered_map<std::string, std::string> &data) = 0;
};

// Adapter: adapts the interface of Adaptee to the Target interface.
class JsonToXmlAdapter : public API
{
public:
	JsonToXmlAdapter(LegacyAPI &api)
		: legacyAPI_(api) {}

	void sendData(const std::unordered_map<std::string, std::string> &data) override
	{
		std::string xmlData = convertToJsonToXml(data);
		legacyAPI_.sendDataXML(xmlData);
	}

private:
	LegacyAPI &legacyAPI_;

	std::string convertToJsonToXml(const std::unordered_map<std::string, std::string> &data)
	{
		// Implementation of conversion from JSON to XML.
		std::string xmlData = "<data>";
		for (auto &[key, value] : data)
		{
			xmlData += "<" + key + ">" + value + "</" + key + ">";
		}
		xmlData += "</data>";
		return xmlData;
	}
};

// Client code that uses Target interface.
void sendData(API &api, const std::unordered_map<std::string, std::string> &data)
{
	api.sendData(data);
}

int main()
{
	// Create a LegacyAPI.
	LegacyAPI legacyAPI;

	// Adapt the JSON data to the XML-based LegacyAPI.
	JsonToXmlAdapter adapter(legacyAPI);

	// Send the JSON data using the adapter.
	std::unordered_map<std::string, std::string> jsonData = {{"name", "John"}, {"age", "42"}};
	sendData(adapter, jsonData);

	/////////// output /////////
	/// Sending XML data: <data><age>42</age><name>John</name></data>
	////////////////////////////
	return 0;
}
