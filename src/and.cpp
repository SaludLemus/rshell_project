#include "and.h"
using namespace std;

And::And() : Connector(), cmd_success(false), left_child(0), right_child(0) {}

And::And(Connector* left_child, Connector* right_child) : left_child(left_child), right_child(right_child) {}

void And::execute() {
	if (checkExistence()) { // valid
		left_child->execute();
		
		if (left_child->cmdSuccess) {// then execute right child
			right_child->execute();
			if (right_child->cmdSuccess)
				cmd_sucess = true; // both are true
		}
	}
	
	return;
}

bool And::checkExistence() { // no seg. fault
	if (left_child && right_child) return true;
	return false;
}
