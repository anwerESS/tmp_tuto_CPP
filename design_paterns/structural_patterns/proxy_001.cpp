// The Proxy pattern is a design pattern that provides a surrogate or placeholder for another object to control access to it. It is used when we want to add an additional level of indirection to an object to provide a level of separation or control between the client and the real object.

// In the Proxy pattern, we have two main classes: the Proxy and the RealSubject. The Proxy class has the same interface as the RealSubject, and it contains an instance of the RealSubject. The Proxy forwards requests from the client to the RealSubject, but it can also perform additional tasks before or after forwarding the request, such as checking permissions, caching data, or logging activity.

// The RealSubject is the object that the Proxy is acting as a stand-in for. It is the object that performs the actual work requested by the client. The client is not aware of the existence of the RealSubject, as it communicates only with the Proxy object, which provides a layer of indirection and control.

// The Proxy pattern is useful in situations where we want to restrict access to an object, or when we want to provide additional functionality without changing the underlying class. It can also be used to optimize performance by caching expensive operations or data.

// An example of the Proxy pattern is a proxy server, which acts as an intermediary between a client and a server. The proxy server can cache frequently requested data or resources, filter requests based on certain criteria, or restrict access to certain resources. Another example is lazy loading, where a proxy object is used to delay the creation or loading of an expensive object until it is actually needed.

// Overall, the Proxy pattern provides a way to add an additional layer of control or functionality to an object without changing its underlying class, allowing for greater flexibility and extensibility in our code.


//***********************************************************************************************/
// Here are some examples of how the Proxy pattern can be used in real life:

// 1. Caching: The proxy server can cache frequently accessed web pages and serve them directly to the client without having to go to the internet, reducing the amount of traffic on the network and improving response times.

// 2. Filtering: The proxy server can be configured to filter out certain types of web content, such as malware or inappropriate material, before it reaches the client.

// 3. Logging: The proxy server can log all requests and responses passing through it, providing administrators with valuable insights into network usage and potential security threats.

// 4. Security: The proxy server can act as a firewall, blocking certain types of incoming traffic and preventing unauthorized access to the network.

// Overall, the Proxy pattern is a powerful tool that can be used to provide an additional layer of control, functionality, or optimization to our code. It can be applied in a wide range of scenarios, from remote communication to security and performance optimization.

///////////////////////////////////////////////////////////
// In this example, we have three classes: Subject, RealSubject, and Proxy. The Subject class defines the interface that both the RealSubject and Proxy classes implement. The RealSubject class is the object that the Proxy acts as a stand-in for. The Proxy class forwards requests from the client to the RealSubject, but it can also perform additional tasks before or after forwarding the request, such as creating the RealSubject object if it hasn't been created yet.

// In the main function, we create a Proxy object and call its request method twice. The first time it's called, the Proxy creates a RealSubject object and forwards the request to it. The second time it's called, the Proxy just forwards the request to the already-existing RealSubject object.

// This example demonstrates how the Proxy pattern can be used to provide an additional layer of indirection and control between the client and the real object.

/*
		   +---------+             +---------+
		   | Subject |<---------+--|  Proxy  |
		   +---------+             +---------+
				^                        ^
				|                        |
				|                        |
		   +---------+             +-------------+
		   |RealSubject|           |VirtualProxy |
		   +---------+             +-------------+

*/


#include <iostream>
#include <string>

class Subject {
public:
	virtual ~Subject() {}
	virtual void request() = 0;
};

class RealSubject : public Subject {
public:
	void request() override {
		std::cout << "RealSubject: Handling request." << std::endl;
	}
};

class Proxy : public Subject {
public:
	Proxy() : m_realSubject(nullptr) {}

	~Proxy() {
		delete m_realSubject;
	}

	void request() override {
		if (!m_realSubject) {
			std::cout << "Proxy: Creating a RealSubject object." << std::endl;
			m_realSubject = new RealSubject;
		}
		std::cout << "Proxy: Forwarding request to RealSubject object." << std::endl;
		m_realSubject->request();
	}

private:
	RealSubject* m_realSubject;
};

int main() {
	Proxy proxy;
	proxy.request();
	proxy.request();

	//////////// output //////////
	// Proxy: Creating a RealSubject object.
	// Proxy: Forwarding request to RealSubject object.
	// RealSubject: Handling request.
	// Proxy: Forwarding request to RealSubject object.
	// RealSubject: Handling request.
	/////////////////////////////
	return 0;
}
