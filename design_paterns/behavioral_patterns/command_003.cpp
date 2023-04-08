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
#include <memory>
#include <vector>

class Command {
public:
	virtual ~Command() {}
	virtual void Execute() = 0;
	virtual void Undo() = 0;
	virtual void Redo() = 0;
};


class Document {
public:
	void Save() {
		std::cout << "Document is saved." << std::endl;
	}
	void Copy() {
		std::cout << "Document is copied." << std::endl;
	}
	void Cut() {
		std::cout << "Document is cut." << std::endl;
	}
};


class SaveCommand : public Command {
public:
	SaveCommand(Document* doc) : document_(doc) {}
	void Execute() override {
		document_->Save();
	}
	void Undo() override {}
	void Redo() override {}
private:
	Document* document_;
};


class CopyCommand : public Command {
public:
	CopyCommand(Document* doc) : document_(doc) {}
	void Execute() override {
		document_->Copy();
	}
	void Undo() override {}
	void Redo() override {}
private:
	Document* document_;
};


class CutCommand : public Command {
public:
	CutCommand(Document* doc) : document_(doc) {}
	void Execute() override {
		document_->Cut();
	}
	void Undo() override {}
	void Redo() override {}
private:
	Document* document_;
};



class Invoker {
public:
	void SetCommand(Command* command) {
		command->Execute();
		commands_.push_back(command);
		current_command_ = commands_.size() - 1;
	}

	void Undo() {
		if (current_command_ >= 0) {
			commands_[current_command_]->Undo();
			current_command_--;
		}
	}

	void Redo() {
		if (current_command_ < commands_.size() - 1) {
			current_command_++;
			commands_[current_command_]->Redo();
		}
	}

private:
	std::vector<Command*> commands_;
	int current_command_ = -1;
};



int main() {
	std::unique_ptr<Document> document = std::make_unique<Document>();
	std::unique_ptr<Command> saveCommand = std::make_unique<SaveCommand>(document.get());
	std::unique_ptr<Command> copyCommand = std::make_unique<CopyCommand>(document.get());
	std::unique_ptr<Command> cutCommand = std::make_unique<CutCommand>(document.get());

	Invoker invoker;
	invoker.SetCommand(saveCommand.get());
	invoker.SetCommand(copyCommand.get());
	invoker.SetCommand(cutCommand.get());

	std::cout << "Undoing..." << std::endl;
	invoker.Undo();

	std::cout << "Redoing..." << std::endl;
	invoker.Redo();

	return 0;
}
