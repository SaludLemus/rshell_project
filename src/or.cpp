#include "or.h"

Or::Or() : Connector(), left_child(0), right_child(0) {}

Or::Or(Connector* left_child, Connector* right_child) : Connector(succeed), left_child(left_child), right_child(right_child) {}

void Or::execute() {
	if (checkExistence()) {
		left_child->execute(); // run left child's cmd
		
		if (left_child->cmdSuccess == false) {
			right_child->execute(); // execute right child if left child fails
			cmdSuccess = true;
		}
	}
	return;
}

bool Or::checkExistence() {
	if (left_child && right_child) return true;
	return false;
}
