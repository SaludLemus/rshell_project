#ifndef connector_h_
#define connector_h_

class Connector {
	public:
		Connector() {cmdSuccess = false;}
		Connector(bool success) : cmdSuccess(success) {}
		~Connector() {}
	protected:
		bool cmdSuccess; // true if cmd worked, else false (for && and ||)
	public:
		virtual void execute() = 0; // execute depends on connectors or single command
		virtual bool checkExistence() = 0; // true if child exists
		virtual bool checkStatus();
	private:
};

#endif
