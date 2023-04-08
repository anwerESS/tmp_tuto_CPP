// In this example, we have three classes: NetworkMonitor, RealNetworkMonitor, and NetworkMonitorProxy. The NetworkMonitor class defines the interface that both the RealNetworkMonitor and NetworkMonitorProxy classes implement. The RealNetworkMonitor class is the object that the NetworkMonitorProxy acts as a stand-in for. The NetworkMonitorProxy class forwards monitoring requests from the client to the real monitors, but it can also perform additional tasks before or after forwarding the request, such as creating the RealNetworkMonitor objects if they haven't been created yet.

// In the main function, we create a NetworkMonitorProxy object and call its monitor method. The NetworkMonitorProxy creates a RealNetworkMonitor object for each IP address in the list, and forwards the monitoring request to each RealNetworkMonitor object.

// This example demonstrates how the Proxy pattern can be used to provide an additional layer of indirection and control between the client and the real object in a network monitoring system.

/*
				  +---------------------+
				  |    NetworkMonitor   |
				  +---------------------+
				  |   + monitor() const  |
				  +---------------------+
							 ^
							 |
			   +-------------+------------+
			   |                          |
+------------------------+   +------------------------+
|   RealNetworkMonitor   |   |    NetworkMonitorProxy   |
+------------------------+   +------------------------+
|  - m_ipAddress: string  |   | - m_realMonitors: vector |
+------------------------+   +------------------------+
|    + monitor() const   |   |    + monitor() const     |
+------------------------+   +------------------------+
*/





#include <iostream>
#include <vector>

// Subject interface
class NetworkMonitor {
public:
	virtual ~NetworkMonitor() {}
	virtual void monitor() const = 0;
};

// RealSubject class
class RealNetworkMonitor : public NetworkMonitor {
public:
	RealNetworkMonitor(const std::string& ipAddress) : m_ipAddress(ipAddress) {}

	void monitor() const override {
		std::cout << "Monitoring network traffic on IP address " << m_ipAddress << std::endl;
	}

private:
	std::string m_ipAddress;
};

// Proxy class
class NetworkMonitorProxy : public NetworkMonitor {
public:
	NetworkMonitorProxy(const std::vector<std::string>& ipAddresses) {
		for (const auto& ipAddress : ipAddresses) {
			m_realMonitors.push_back(new RealNetworkMonitor(ipAddress));
		}
	}

	~NetworkMonitorProxy() {
		for (const auto& monitor : m_realMonitors) {
			delete monitor;
		}
	}

	void monitor() const override {
		std::cout << "Monitoring network traffic on all IP addresses:" << std::endl;
		for (const auto& monitor : m_realMonitors) {
			monitor->monitor();
		}
	}

private:
	std::vector<RealNetworkMonitor*> m_realMonitors;
};

int main() {
	std::vector<std::string> ipAddresses = {"192.168.1.1", "192.168.1.2", "192.168.1.3"};
	NetworkMonitorProxy proxy(ipAddresses);
	proxy.monitor();
	return 0;
}
