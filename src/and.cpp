#include "connector.h"
using namespace std;

And::And() : Connector(), cmd_success(false), left_child(0), right_child(0) {}

And::And(bool cmd_success, Connector* left_child, Connector* right_child) : Connector(), cmd_success(cmd_success), left_child(left_child), right_child(right_child) {}

void And::execute() {
	if (checkExistence()) { // valid
		left_child->execute();
		
		if (left_child->cmdSuccess) {// then execute right child
			right_child->execute();
			cmd_sucess = true; // both are true
		}
	}
	
	return;
}




bool And::checkExistence() { // no seg. fault
	if (left_child && right_child) return true;
	return false;
}
