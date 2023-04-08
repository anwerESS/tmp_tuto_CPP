// The Command Design Pattern is a behavioral design pattern that allows you to encapsulate requests or operations as objects, allowing you to parameterize clients with different requests, queue or log requests, and support undoable operations. In this pattern, you create a separate object for each command, which provides a way to invoke the method in the object that holds it.

// To implement the Command Design Pattern, you'll need to create the following classes:

// 1. Command - this is an abstract base class that defines an interface for executing an operation.

// 2. ConcreteCommand - this is a derived class that implements the interface defined by the Command class.

// 3. Invoker - this is a class that invokes the command object to execute the operation.

// 4. Receiver - this is a class that performs the actual operation.

// The Command Design Pattern is useful in situations where you need to decouple an object that issues a request from the object that performs the action requested. This pattern provides a way to encapsulate a request as an object, which allows you to parameterize clients with different requests, queue or log requests, and support undoable operations.

// Here are some examples of real-world scenarios where the Command Design Pattern can be applied:

// 1. GUI Applications: In a GUI application, the user interface often consists of multiple buttons that execute different commands. The Command Design Pattern can be used to encapsulate each command as an object, allowing you to execute the commands when the corresponding buttons are clicked. This pattern also enables the implementation of undo and redo operations for user actions.

// 2. Remote Control Systems: In a remote control system, commands are sent to a device from a remote controller. The Command Design Pattern can be used to encapsulate each command as an object, which can be sent over a network to the device for execution. This pattern also enables the implementation of logging and replaying of commands.

// 3. Database Transactions: In a database system, transactions need to be executed atomically. The Command Design Pattern can be used to encapsulate each transaction as an object, which can be executed as a single unit of work. This pattern also enables the implementation of undo and redo operations for transactions.

// 4. Text Editors: In a text editor, commands such as insert, delete, and replace need to be executed on text. The Command Design Pattern can be used to encapsulate each command as an object, which can be executed on the text when the corresponding keyboard shortcuts or menu items are selected. This pattern also enables the implementation of undo and redo operations for text editing.

// Overall, the Command Design Pattern is useful in any situation where you need to decouple an object that issues a request from the object that performs the action requested, and you want to support operations such as undo, redo, queueing, and logging of commands.

#include <iostream>
#include <vector>
#include <memory>

// Receiver Class
class Document
{
public:
	void Save()
	{
		std::cout << "Document is saved." << std::endl;
	}
	void Copy()
	{
		std::cout << "Document is copied." << std::endl;
	}
	void Cut()
	{
		std::cout << "Document is cut." << std::endl;
	}
};

// Command Interface
class ICommand
{
public:
	virtual ~ICommand() {}
	virtual void Execute() = 0;
};

// Concrete Command Classes
class SaveCommand : public ICommand
{
public:
	SaveCommand(std::shared_ptr<Document> doc) : document_(doc) {}
	void Execute() override
	{
		document_->Save();
	}

private:
	std::shared_ptr<Document> document_;
};

class CopyCommand : public ICommand
{
public:
	CopyCommand(std::shared_ptr<Document> doc) : document_(doc) {}
	void Execute() override
	{
		document_->Copy();
	}

private:
	std::shared_ptr<Document> document_;
};

class CutCommand : public ICommand
{
public:
	CutCommand(std::shared_ptr<Document> doc) : document_(doc) {}
	void Execute() override
	{
		document_->Cut();
	}

private:
	std::shared_ptr<Document> document_;
};


// Invoker Class
class Menu
{
public:
	void SetCommand(std::shared_ptr<ICommand> command)
	{
		command_ = command;
	}
	void Click()
	{
		command_->Execute();
	}

private:
	std::shared_ptr<ICommand> command_;
};

int main()
{
	auto document = std::make_shared<Document>();
	auto saveCommand = std::make_shared<SaveCommand>(document);
	auto copyCommand = std::make_shared<CopyCommand>(document);
	auto cutCommand = std::make_shared<CutCommand>(document);

	auto saveMenu = std::make_shared<Menu>();
	saveMenu->SetCommand(saveCommand);
	saveMenu->Click();

	auto editMenu = std::make_shared<Menu>();
	editMenu->SetCommand(copyCommand);
	editMenu->Click();

	editMenu->SetCommand(cutCommand);
	editMenu->Click();

	return 0;
}
