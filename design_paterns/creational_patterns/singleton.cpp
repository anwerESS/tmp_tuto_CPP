// The Singleton design pattern is used when we need to ensure that there is only one instance of a class created and that this instance can be accessed globally by other objects in the system. Here are some use cases where the Singleton pattern can be applied:

// Configuration management: The Singleton pattern is often used to manage application configuration settings. By using a Singleton class to manage configuration settings, we can ensure that there is only one instance of the configuration object, and that all objects in the system can access the same configuration settings.

// Logging: Logging is an essential part of any application, and the Singleton pattern can be used to create a logger class that provides logging functionality to all other classes in the system.

// Database connections: Database connections are expensive to create, so it's often necessary to create a single instance of a database connection object that can be shared across multiple objects in the system.

// Caching: Caching is an important technique for improving application performance. The Singleton pattern can be used to create a cache object that can be shared by all objects in the system.

// Thread pools: Thread pools are often used in multi-threaded applications to improve performance. The Singleton pattern can be used to create a thread pool object that can be shared by all threads in the system.

// Hardware access: In some cases, we need to ensure that only one instance of a hardware device driver is created. The Singleton pattern can be used to create a device driver object that can be shared by all other objects in the system.

// https://refactoring.guru/design-patterns/singleton/cpp/example#example-0


#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

#include <mutex>


/////////////////// Logger Class //////////////////
class Logger {
private:
	std::ofstream logfile;
	static Logger* instance; // Static instance of the Logger class

	Logger() { // Private constructor
		// Get the current time to use in the log file name
		std::time_t now = std::time(nullptr);
		std::string filename = "log_" + std::to_string(now) + ".txt";
		logfile.open(filename); // Open the log file for writing
	}

	~Logger() { delete instance;}// Private destructor


    Logger(Logger &other) = delete; // Singletons should not be cloneable.
    void operator=(const Logger &) = delete; // Singletons should not be assignable

public:
	static Logger* getInstance() { // Static function to get the instance of the Logger class
		if (instance == nullptr) { // If the instance has not been created yet
			instance = new Logger(); // Create a new instance of the Logger class
		}
		return instance; // Return the instance of the Logger class
	}

	void log(std::string message) { // Function to add a log message to the log file
		std::time_t now = std::time(nullptr); // Get the current time
		std::string timestamp = std::ctime(&now); // Convert the current time to a string
		logfile << timestamp << " : " << message << std::endl; // Write the log message to the log file
	}
};

Logger* Logger::instance = nullptr; // Initialize the static instance of the Logger class to nullptr
//////////////////////////////////////////////

/////////////////// LoggerSafeThread Class //////////////////
class LoggerSafeThread {
private:
	std::ofstream logfile; // logfile member cannot be static because it needs to be unique for each instance of the LoggerSafeThread class.
	static LoggerSafeThread* instance; // Static instance of the LoggerSafeThread class
	static std::mutex mutex; // Static mutex to ensure thread-safety

	LoggerSafeThread() { // Private constructor
		// Get the current time to use in the log file name
		std::time_t now = std::time(nullptr);
		std::string filename = "log_" + std::to_string(now) + ".txt";
		logfile.open(filename); // Open the log file for writing
	}

	~LoggerSafeThread() { delete instance;}// Private destructor


    LoggerSafeThread(LoggerSafeThread &other) = delete; // Singletons should not be cloneable.
    void operator=(const LoggerSafeThread &) = delete; // Singletons should not be assignable

public:
	static LoggerSafeThread* getInstance() { // Static function to get the instance of the LoggerSafeThread class
		std::lock_guard<std::mutex> lock(mutex); // Lock the mutex to ensure thread-safety
		if (instance == nullptr) { // If the instance has not been created yet
			instance = new LoggerSafeThread(); // Create a new instance of the LoggerSafeThread class
		}
		return instance; // Return the instance of the LoggerSafeThread class
	}

	void log(std::string message) { // Function to add a log message to the log file
		std::lock_guard<std::mutex> lock(mutex); // Lock the mutex to ensure thread-safety
		std::time_t now = std::time(nullptr); // Get the current time
		std::string timestamp = std::ctime(&now); // Convert the current time to a string
		logfile << timestamp << " : " << message << std::endl; // Write the log message to the log file
	}
};

LoggerSafeThread* LoggerSafeThread::instance = nullptr; // Initialize the static instance of the LoggerSafeThread class to nullptr
std::mutex LoggerSafeThread::mutex; // Initialize the static mutex to unlock
//////////////////////////////////////////////


int main() {

	Logger* logger = Logger::getInstance(); // Get the singleton instance of the Logger class
	logger->log("This is a log message."); // Add a log message to the log file
	Logger::getInstance()->log("This is another msg");
	/////// log_1678863670.txt //////
	// Wed Mar 15 08:01:10 2023
	//  : This is a log message.
	// Wed Mar 15 08:01:10 2023
	//  : This is another msg

	return 0;
}
