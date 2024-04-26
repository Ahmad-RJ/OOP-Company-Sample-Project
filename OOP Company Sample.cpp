#include <iostream>
#include <string>
using namespace std;
class Project;
class Department;
class Employee;
class Name {
	string fname;
	string lname;
public:
	Name(string f, string l) {
		fname = f;
		lname = l;
	}
	Name(const Name& obj) {
		fname = obj.fname;
		lname = obj.lname;
	}
	void DisplayName() {
		cout << "Name: " << fname << " " << lname << endl;
	}
};
class Address {
	int houseNo;
	char block;
	int streetNo;
	string city;
public:
	Address(int houseNo, char block, int streetNo, string city) {
		this->houseNo = houseNo;
		this->block = block;
		this->streetNo = streetNo;
		this->city = city;
	}
	Address(const Address& obj) {
		this->houseNo = obj.houseNo;
		this->block = obj.block;
		this->streetNo = obj.streetNo;
		this->city = obj.city;
	}
	void DisplayAddress() {
		cout << "Address: " << endl;
		cout << "House #" << houseNo << ", Block " << block << ", Street #" << streetNo << ", " << city << "." << endl;
	}
	int gethouseno() {
		return houseNo;
	}
	int getstreetno() {
		return streetNo;
	}
	char getblock() {
		return block;
	}
	string getcity() {
		return city;
	}
};
class Project {
	int ID;
	int employeesworkingon;
	string projectdescription;
	Employee* employee[10];
public:
	Project(int id, string projdes, int empc = 0) {
		ID = id;
		projectdescription = projdes;
		employeesworkingon = empc;
	}
	void displayprojectinfo() {
		cout << "Project ID: " << ID << endl;
		cout << "Project Description: " << projectdescription << endl;
		cout << "Number of Employees Working on Project: " << employeesworkingon << endl;
	}
	int getID() {
		return ID;
	}
	void IncEmployeesWorkingOn() {
		employeesworkingon++;
	}
	void DecEmployeesWorkingOn() {
		employeesworkingon--;
	}
	string getname() {
		return projectdescription;
	}
	bool AddEmployee(Employee* emp);
	bool RemoveEmployee(Employee* emp);
	void DisplayAllEmployees();
};
class Employee {
	int ID;
	Name name;
	Address permanentAddr;
	bool assignedtoDept;
	int projectCount;
	Project* project[3];
	Department* dept;
public:
	Employee(int id, string fname, string lname, int houseNo, char block, int streetno, string city, bool assigned = false, int pc = 0, Department* d = NULL) : name(fname, lname), permanentAddr(houseNo, block, streetno, city) {
		ID = id;
		assignedtoDept = assigned;
		projectCount = pc;
		dept = d;
		for (int i = 0; i < 3; i++) {
			project[i] = NULL;
		}
	}
	void setassigned(bool cond) {
		assignedtoDept = cond;
	}
	bool getassigned() {
		return assignedtoDept;
	}
	int getID() {
		return ID;
	}
	void getname() {
		name.DisplayName();
	}
	void DisplayEmployeeInfo();
	bool AddProject(Project* proj);
	bool RemoveProject(int projectID);
	bool setDept(Department* d);
	void displayallprojects();
	void displayDept();
	Department* getdept();
};
class Department {
	int ID;
	string name;
	int employeeCount;
	Employee* employee[50];
public:
	Department(int id, string n, int empc = 0) {
		ID = id;
		name = n;
		employeeCount = empc;
	}
	string GetName() {
		return name;
	}
	int getID() {
		return ID;
	}
	void displaydepartmentinfo() {
		cout << "Department ID: " << ID << endl;
		cout << "Department Name: " << name << endl;
		cout << "Number of Employees in Department: " << employeeCount << endl;
	}
	bool AddEmployee(Employee* emp);
	bool RemoveEmployee(Employee* emp);
	void displayallemployees();
};
bool Project::AddEmployee(Employee* emp) {
	if (employeesworkingon < 10) {
		for (int i = 0; i < employeesworkingon; i++) {
			if (employee[i] == emp) {
				return false;
				break;
			}
		}
		employee[employeesworkingon++] = emp;
		return true;
	}
	else {
		return false;
	}
}
bool Project::RemoveEmployee(Employee* emp) {
	bool check = false;
	int p = 0;
	for (int i = 0; i < employeesworkingon; i++) {
		if (employee[i] == emp) {
			employee[i] = 0;
			check = true;
			p = i;
			break;
		}
	}
	if (check == true) {
		employeesworkingon--;
		for (int i = p; i < employeesworkingon + 1; i++) {
			employee[i] = employee[i + 1];
		}
		return true;
	}
	else {
		cout << "Employee Not Found! :(" << endl;
		return false;
	}
}
void Project::DisplayAllEmployees() {
	cout << "All Employees working on Project: " << endl;
	bool check = false;
	for (int i = 0; i < employeesworkingon; i++) {
		if (employee[i] != NULL) {
			check = true;
			employee[i]->getname();
		}
	}
	if (check == false) {
		cout << "No Employees Found." << endl;
	}
}
void Department::displayallemployees() {
	cout << "Department has following Employees: " << endl;
	bool check = false;
	for (int i = 0; i < employeeCount; i++) {
		if (employee[i] != NULL) {
			employee[i]->getname();
			check = true;
		}
	}
	if (check == false) {
		cout << "No Employee Found.";
	}
}
bool Department::AddEmployee(Employee* emp) {
	if (employeeCount < 50) {
		for (int i = 0; i < employeeCount; i++) {
			if (employee[i] == emp) {
				return false;
				break;
			}
		}
		employee[employeeCount++] = emp;
		emp->setDept(this);
		return true;
	}
	else {
		return false;
	}
}
bool Department::RemoveEmployee(Employee* emp) {
	bool check = false;
	int p = 0;
	for (int i = 0; i < employeeCount; i++) {
		if (employee[i] == emp) {
			employee[i] = 0;
			check = true;
			p = i;
			break;
		}
	}
	if (check == true) {
		employeeCount--;
		emp->setDept(NULL);
		for (int i = p; i < employeeCount + 1; i++) {
			employee[i] = employee[i + 1];
		}
		return true;
	}
	else {
		cout << "Employee Not Found! :(" << endl;
		return false;
	}
}
bool Employee::AddProject(Project* proj) {
	if (projectCount < 3) {
		for (int i = 0; i < projectCount; i++) {
			if (project[i] == proj) {
				return false;
				break;
			}
		}
		if (proj->AddEmployee(this) == false) {
			return false;
		}
		else
			project[projectCount++] = proj;
		return true;
	}
	else {
		return false;
	}
}
bool Employee::RemoveProject(int projectID) {
	bool check = false;
	int p = 0;
	for (int i = 0; i < projectCount; i++) {
		if (project[i]->getID() == projectID) {
			project[i]->RemoveEmployee(this);
			project[i] = 0;
			check = true;
			p = i;
			break;
		}
	}
	if (check == true) {
		projectCount--;
		for (int i = p; i < projectCount + 1; i++) {
			project[i] = project[i + 1];
		}
		return true;
	}
	else {
		cout << "Project Not Found! :(" << endl;
		return false;
	}
}
bool Employee::setDept(Department* d) {
	dept = d;
	if (d != NULL) {
		this->setassigned(true);
	}
	else {
		this->setassigned(false);
	}
	return true;
}
void Employee::DisplayEmployeeInfo() {
	name.DisplayName();
	cout << "Employee ID: " << ID << endl;
	permanentAddr.DisplayAddress();
	if (dept != nullptr) {
		cout << "Employee's Department: " << dept->GetName() << endl;
	}
	else {
		cout << "Employee's Department: None." << endl;
	}
	cout << "Projects of Employee: " << endl;
	for (int i = 0; i < projectCount; i++) {
		cout << project[i]->getname() << endl;
	}
}
void Employee::displayallprojects() {
	cout << "Employee is working on following projects: " << endl;
	bool check = false;
	for (int i = 0; i < projectCount; i++) {
		if (project[i] != NULL) {
			cout << project[i]->getname() << endl;
			check = true;
		}
	}
	if (check == false) {
		cout << "No Projects Found." << endl;
	}
}
void Employee::displayDept() {
	if (dept != NULL) {
		cout << dept->GetName() << endl;
	}
	else
		cout << "None." << endl;
}
Department* Employee::getdept() {
	return dept;
}
int main() {
	Department* dArr[10] = { NULL };
	Project* pArr[15] = { NULL };
	Employee* eArr[55] = { NULL };
	int deptcont = 0, projcont = 0, empcont = 0, input = 0;
	while (input != 15) {
		cout << "Choose an action to perform: " << endl;
		cout << " 1 - Create Department" << endl << " 2 - Create Employee" << endl << " 3 - Create Project" << endl << " 4 - Display A Department given its ID, (if it exists)" << endl << " 5 - Display An Employee given its ID, (if it exists)" << endl;
		cout << " 6 - Display A Project given its ID, (if it exists)" << endl << " 7 - Add an Employee to a Department, provided the IDs" << endl << " 8 - Add a Project to an Employee, provided the IDs" << endl << " 9 - Display all projects of An Employee given his / her ID" << endl;
		cout << "10 - Display all employees of a Department given its ID" << endl << "11 - Remove an Employee from a Department, provided the IDs" << endl << "12 - Remove a Project from an Employee, provided the IDs" << endl << "13 - Display all Employees working on a project, provided Project ID" << endl;
		cout << "14 - Display the Department of an Employee, provided Employee ID" << endl << "15 - Exit" << endl << "Input Option Number: ";
		cin >> input;
		if (input == 1) {
			if (deptcont < 10) {
				int id = 0, i = 0;
				string name;
				cout << "Enter Department ID: ";
				cin >> id;
				if (deptcont > 0) {
					while (i < deptcont) {
						if (id == dArr[i]->getID()) {
							cout << "Department with same ID already exists! Try another ID" << endl;
							cout << "Enter Department ID: ";
							cin >> id;
							i = -1;
						}
						i++;
					}
				}
				cout << "Enter Department Name: ";
				cin.ignore();
				getline(cin, name);
				dArr[deptcont] = new Department(id, name);
				deptcont++;
				cout << endl << "New Department created successfully!" << endl << endl;
			}
			else {
				cout << "Maximum Number of Departments already created." << endl << endl;
			}
		}
		if (input == 2) {
			if (empcont < 55) {
				int id = 0, i = 0, houseNo = 0, streetNo = 0;
				string fname, lname, city;
				char block;
				cout << "Enter Employee ID: ";
				cin >> id;
				if (empcont > 0) {
					while (i < empcont) {
						if (id == eArr[i]->getID()) {
							cout << "Employee with same ID already exists! Try another ID" << endl;
							cout << "Enter Employee ID: ";
							cin >> id;
							i = -1;
						}
						i++;
					}
				}
				cout << "Enter Employee's First Name: ";
				cin.ignore();
				getline(cin, fname);
				cout << "Enter Employee's Last Name: ";
				
				getline(cin, lname);
				cout << "Enter Employee's Address Details as followed: " << endl << "House Number: ";
				cin >> houseNo;
				cout << "Block: ";
				cin >> block;
				cout << "Street Number: ";
				cin >> streetNo;
				cout << "City: ";
				cin >> city;
				eArr[empcont] = new Employee(id, fname, lname, houseNo, block, streetNo, city);
				empcont++;
				cout << endl << "New Employee created successfully!" << endl << endl;
			}
			else {
				cout << "Maximum Number of Employees already created." << endl << endl;
			}
		}
		if (input == 3) {
			if (projcont < 15) {
				int id = 0, i = 0;
				string name;
				cout << "Enter Project ID: ";
				cin >> id;
				if (projcont > 0) {
					while (i < projcont) {
						if (id == pArr[i]->getID()) {
							cout << "Project with same ID already exists! Try another ID" << endl;
							cout << "Enter Project ID: ";
							cin >> id;
							i = -1;
						}
						i++;
					}
				}
				cout << "Enter Project Name: ";
				cin.ignore();
				getline(cin, name);
				pArr[projcont] = new Project(id, name);
				projcont++;
				cout << endl << "New Project created successfully!" << endl << endl;
			}
			else {
				cout << "Maximum Number of Projects already created." << endl << endl;
			}
		}
		if (input == 4) {
			if (deptcont > 0) {
				int id = 0;
				bool check = false;
				cout << "Enter Department ID to display Department Information: ";
				cin >> id;
				for (int i = 0; i < deptcont; i++) {
					if (id == dArr[i]->getID()) {
						cout << endl;
						dArr[i]->displaydepartmentinfo();
						cout << endl;
						check = true;
						break;
					}
				}
				if (check == false) {
					cout << "Invalid Department ID! Try again." << endl << endl;
				}
			}
			else {
				cout << "No Department found!" << endl << endl;
			}
		}
		if (input == 5) {
			if (empcont > 0) {
				int id = 0;
				bool check = false;
				cout << "Enter Employee ID to display Employee Information: ";
				cin >> id;
				for (int i = 0; i < empcont; i++) {
					if (id == eArr[i]->getID()) {
						cout << endl;
						eArr[i]->DisplayEmployeeInfo();
						cout << endl;
						check = true;
						break;
					}
				}
				if (check == false) {
					cout << "Invalid Employee ID! Try again." << endl << endl;
				}
			}
			else {
				cout << "No Employee found!" << endl << endl;
			}
		}
		if (input == 6) {
			if (projcont > 0) {
				int id = 0;
				bool check = false;
				cout << "Enter Project ID to display Project Information: ";
				cin >> id;
				for (int i = 0; i < projcont; i++) {
					if (id == pArr[i]->getID()) {
						cout << endl;
						pArr[i]->displayprojectinfo();
						cout << endl;
						check = true;
						break;
					}
				}
				if (check == false) {
					cout << "Invalid Project ID! Try again." << endl << endl;
				}
			}
			else {
				cout << "No Project found!" << endl << endl;
			}
		}
		if (input == 7) {
			if (deptcont > 0 && empcont > 0) {
				bool check = false, check2 = false;
				int deptid = 0, empid = 0;
				cout << "Enter Department ID: ";
				cin >> deptid;
				for (int i = 0; i < deptcont; i++) {
					if (dArr[i]->getID() == deptid) {
						check = true;
						cout << "Enter Employee ID: ";
						cin >> empid;
						for (int j = 0; j < empcont; j++) {
							if (eArr[j]->getID() == empid) {
								check2 = true;
								if (eArr[j]->getassigned() == true) {
									for (int x = 0; x < deptcont; x++) {
										if (dArr[x] == eArr[j]->getdept()) {
											dArr[x]->RemoveEmployee(eArr[j]);
										}
									}
								}
								if (dArr[i]->AddEmployee(eArr[j]) == true) {
									cout << "Employee Added to Department Successfully!" << endl << endl;
								}
								else
									cout << "Either Employee already is enrolled in selected Department or Maximum Employees already exist in selected Department." << endl << endl;
							}
						}
					}
				}
				if (check == false) {
					cout << "Invalid Department ID! Try again." << endl;
				}
				if (check2 == false) {
					cout << "Invalid Employee ID! Try again." << endl;
				}
			}
			else {
				cout << "Either No Department or No Employee found!" << endl << endl;
			}
		}
		if (input == 8) {
			if (projcont > 0 && empcont > 0) {
				int projid = 0, empid = 0;
				bool check = false, check2 = false;
				cout << "Enter Project ID: ";
				cin >> projid;
				for (int i = 0; i < projcont; i++) {
					if (pArr[i]->getID() == projid) {
						check = true;
						cout << "Enter Employee ID: ";
						cin >> empid;
						for (int j = 0; j < empcont; j++) {
							if (eArr[j]->getID() == empid) {
								check2 = true;
								if (eArr[j]->AddProject(pArr[i]) == true) {
									cout << "Project Added to Employee Successfully!" << endl << endl;
								}
								else
									cout << "Either Project is already assigned to selected Employee or Maximum Projects are already assigned to selected Employee." << endl << endl;
							}
						}
					}
				}
				if (check == false) {
					cout << "Invalid Project ID! Try again." << endl;
				}
				if (check2 == false) {
					cout << "Invalid Employee ID! Try again." << endl;
				}
			}
			else {
				cout << "Either No Project or No Employee found!" << endl << endl;
			}
		}
		if (input == 9) {
			if (projcont > 0 && empcont > 0) {
				int id = 0;
				bool check = false;
				cout << "Enter Employee ID to display Employee's all Projects: ";
				cin >> id;
				for (int i = 0; i < empcont; i++) {
					if (id == eArr[i]->getID()) {
						check = true;
						eArr[i]->displayallprojects();
						cout << endl;
						break;
					}
				}
				if (check == false) {
					cout << "Invalid Employee ID! Try again." << endl << endl;
				}
			}
			else {
				cout << "Either No Employee or Project found!" << endl << endl;
			}
		}
		if (input == 10) {
			if (empcont > 0 && deptcont > 0) {
				int id = 0;
				bool check = false;
				cout << "Enter Department ID to display its Employees: ";
				cin >> id;
				for (int i = 0; i < deptcont; i++) {
					if (id == dArr[i]->getID()) {
						check = true;
						dArr[i]->displayallemployees();
						cout << endl;
						break;
					}
				}
				if (check == false) {
					cout << "Invalid Employee ID! Try again." << endl << endl;
				}
			}
			else {
				cout << "Either No Employee or Department found!" << endl << endl;
			}
		}
		if (input == 11) {
			if (deptcont > 0 && empcont > 0) {
				bool check = false, check2 = false;
				int deptid = 0, empid = 0;
				cout << "Enter Department ID: ";
				cin >> deptid;
				for (int i = 0; i < deptcont; i++) {
					if (dArr[i]->getID() == deptid) {
						check = true;
						cout << "Enter Employee ID: ";
						cin >> empid;
						for (int j = 0; j < empcont; j++) {
							if (eArr[j]->getID() == empid) {
								check2 = true;
								if (dArr[i]->RemoveEmployee(eArr[j]) == true) {
									cout << "Employee Removed from Department Successfully!" << endl << endl;
								}
								else
									cout << "Either Employee already is enrolled in selected Department or Maximum Employees already exist in selected Department." << endl << endl;
							}
						}
					}
				}
				if (check == false) {
					cout << "Invalid Department ID! Try again." << endl;
				}
				if (check2 == false) {
					cout << "Invalid Employee ID! Try again." << endl;
				}
			}
			else {
				cout << "Either No Department or No Employee found!" << endl << endl;
			}
		}
		if (input == 12) {
			if (projcont > 0 && empcont > 0) {
				int projid = 0, empid = 0;
				bool check = false, check2 = false;
				cout << "Enter Project ID: ";
				cin >> projid;
				for (int i = 0; i < projcont; i++) {
					if (pArr[i]->getID() == projid) {
						check = true;
						cout << "Enter Employee ID: ";
						cin >> empid;
						for (int j = 0; j < empcont; j++) {
							if (eArr[j]->getID() == empid) {
								check2 = true;
								if (eArr[j]->RemoveProject(projid) == true) {
									cout << "Project Removed from Employee Successfully!" << endl << endl;
								}
								else
									cout << "Either Project is already assigned to selected Employee or Maximum Projects are already assigned to selected Employee." << endl << endl;
							}
						}
					}
				}
				if (check == false) {
					cout << "Invalid Project ID! Try again." << endl;
				}
				if (check2 == false) {
					cout << "Invalid Employee ID! Try again." << endl;
				}
			}
			else {
				cout << "Either No Project or No Employee found!" << endl << endl;
			}
		}
		if (input == 13) {
			if (projcont > 0 && empcont > 0) {
				int id = 0;
				bool check = false;
				cout << "Enter Project ID to display its all Employees: ";
				cin >> id;
				for (int i = 0; i < projcont; i++) {
					if (id == pArr[i]->getID()) {
						check = true;
						pArr[i]->DisplayAllEmployees();
						cout << endl;
						break;
					}
				}
				if (check == false) {
					cout << "Invalid Employee ID! Try again." << endl << endl;
				}
			}
			else {
				cout << "Either No Employee or Project found!" << endl << endl;
			}
		}
		if (input == 14) {
			if (empcont > 0 && deptcont > 0) {
				int id = 0;
				bool check = false;
				cout << "Enter Employee ID to display Employee's Department: ";
				cin >> id;
				for (int i = 0; i < empcont; i++) {
					if (id == eArr[i]->getID()) {
						check = true;
						cout << "Department: ";
						eArr[i]->displayDept();
						cout << endl;
						break;
					}
				}
				if (check == false) {
					cout << "Invalid Employee ID! Try again." << endl << endl;
				}
			}
			else {
				cout << "Either No Employee or Department found!" << endl << endl;
			}
		}
	}
	return 0;
}