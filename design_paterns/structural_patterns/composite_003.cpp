// The Composite Design Pattern is used to represent hierarchical structures of objects where both individual objects and groups of objects are treated uniformly. In this example, we will implement a file system using the Composite Design Pattern. The file system is a hierarchical structure that consists of files and directories. A directory can contain files and other directories, while a file is a leaf node in the hierarchy that cannot contain any other objects.

// To implement the file system, we will define an abstract base class FileSystemComponent that represents both files and directories. The FileSystemComponent class defines two pure virtual methods listContents() and getSize() that are implemented by both File and Directory classes. The File class represents a leaf node in the file system hierarchy and contains a name and size of the file. The Directory class represents a composite node in the file system hierarchy and contains a name and a list of child FileSystemComponent objects, which can be either files or directories.

// To build the file system hierarchy, we will create a FileSystem class that contains the root Directory object. The root Directory object can contain other directories, which in turn can contain files and other directories. We will create a sample file system hierarchy with a root directory named "/" and two subdirectories named "home" and "user1". The "home" directory contains two subdirectories named "user1" and "user2", and the "user1" directory contains two files named "file1.txt" and "file2.txt". The "user2" directory contains one file named "file3.txt".

// We will then implement methods in the FileSystem class to list the contents of the file system hierarchy and to calculate the total size of all files in the hierarchy. The FileSystem class will call the listContents() and getSize() methods on the root Directory object, which will recursively call the same methods on its child FileSystemComponent objects.

// Overall, the Composite Design Pattern allows us to treat individual files and directories in the file system hierarchy as well as groups of files and directories uniformly, making it easy to implement operations that apply to the entire file system hierarchy or to specific parts of the hierarchy.
/*
			 +------------------+
			 | FileSystemComponent |
			 +------------------+
			 | -name: string     |
			 +------------------+
			 | +listContents(): void   |
			 | +getSize(): int        |
			 +------------------+
					  ^
					  |
					  |
		  +-----------+-------------+
		  |                         |
  +----------------+     +---------------+
  | File           |     | Directory     |
  +----------------+     +---------------+
  | -size: int     |     | -children: vector<FileSystemComponent*> |
  +----------------+     +---------------+
  | +listContents(): void | | +add(FileSystemComponent*): void       |
  | +getSize(): int        | | +remove(FileSystemComponent*): void    |
  +----------------+     +---------------+
										  |
										  |
										  |
								  +---------------+
								  | FileSystem    |
								  +---------------+
								  | -root: Directory* |
								  +---------------+
								  | +listContents(): void     |
								  | +getSize(): int            |
								  +---------------+

*/





#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Abstract base class for FileSystemComponent
class FileSystemComponent {
public:
	virtual ~FileSystemComponent() {}
	virtual void listContents() = 0;
	virtual int getSize() = 0;
};

// File class represents a leaf node in the file system tree
class File : public FileSystemComponent {
public:
	File(string name, int size) : name(name), size(size) {}
	void listContents() {
		cout << name << endl;
	}
	int getSize() {
		return size;
	}
private:
	string name;
	int size;
};

// Directory class represents a composite node in the file system tree
class Directory : public FileSystemComponent {
public:
	Directory(string name) : name(name) {}
	void addComponent(FileSystemComponent* component) {
		children.push_back(component);
	}
	void removeComponent(FileSystemComponent* component) {
		for (auto it = children.begin(); it != children.end(); ++it) {
			if (*it == component) {
				children.erase(it);
				break;
			}
		}
	}
	void listContents() {
		cout << name << endl;
		for (auto component : children) {
			cout << "  ";
			component->listContents();
		}
	}
	int getSize() {
		int totalSize = 0;
		for (auto component : children) {
			totalSize += component->getSize();
		}
		return totalSize;
	}
private:
	string name;
	vector<FileSystemComponent*> children;
};

// FileSystem class represents the entire file system
class FileSystem {
public:
	FileSystem() {
		root = new Directory("/");
		Directory* home = new Directory("home");
		Directory* user1 = new Directory("user1");
		Directory* user2 = new Directory("user2");
		File* file1 = new File("file1.txt", 100);
		File* file2 = new File("file2.txt", 200);
		File* file3 = new File("file3.txt", 300);
		root->addComponent(home);
		home->addComponent(user1);
		home->addComponent(user2);
		user1->addComponent(file1);
		user1->addComponent(file2);
		user2->addComponent(file3);
	}
	void listContents() {
		root->listContents();
	}
	int getSize() {
		return root->getSize();
	}
private:
	Directory* root;
};

int main() {
	FileSystem fs;
	fs.listContents();
	cout << "Total size: " << fs.getSize() << " bytes" << endl;

	/////////// output ////////////
	//   /
	//   home
	//   user1
	//   file1.txt
	//   file2.txt
	//   user2
	//   file3.txt
	// Total size: 600 bytes
	///////////////////////////////


	return 0;
}


