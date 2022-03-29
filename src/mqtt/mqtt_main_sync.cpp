#include <iostream>
#include <cstdlib>
#include <string>
#include <thread>	// For sleep
#include <atomic>
#include <chrono>
#include <cstring>
#include "mqtt/client.h"
#include <unistd.h>

using namespace std;

const std::string DFLT_SERVER_ADDRESS	{ "tcp://192.168.28.162:1883" };
const std::string DFLT_CLIENT_ID		{ "async_publish" };

const string TOPIC { "test" };

const char* PAYLOAD1 = "Hello World!";
const char* PAYLOAD2 = "Hi there!";
const char* PAYLOAD3 = "Is anyone listening?";
const char* PAYLOAD4 = "Someone is always listening.";

const char* LWT_PAYLOAD = "Last will and testament.";

const int  QOS = 1;

const auto TIMEOUT = std::chrono::seconds(10);

/////////////////////////////////////////////////////////////////////////////

/**
 * A callback class for use with the main MQTT client.
 */
class callback : public virtual mqtt::callback
{
public:
	void connection_lost(const string& cause) override {
		cout << "\nConnection lost" << endl;
		if (!cause.empty())
			cout << "\tcause: " << cause << endl;
	}

	void delivery_complete(mqtt::delivery_token_ptr tok) override {
		cout << "\tDelivery complete for token: "
			<< (tok ? tok->get_message_id() : -1) << endl;
	}
};

/////////////////////////////////////////////////////////////////////////////

/**
 * A base action listener.
 */
class action_listener : public virtual mqtt::iaction_listener
{
protected:
	void on_failure(const mqtt::token& tok) override {
		cout << "Listener failure for token: "
			<< tok.get_message_id() << endl;
	}

	void on_success(const mqtt::token& tok) override {
		cout << "Listener success for token: "
			<< tok.get_message_id() << endl;
	}
};

/////////////////////////////////////////////////////////////////////////////

/**
 * A derived action listener for publish events.
 */
class delivery_action_listener : public action_listener
{
	atomic<bool> done_;

	void on_failure(const mqtt::token& tok) override {
		action_listener::on_failure(tok);
		cout<<"on_failure"<<endl;
		done_ = true;
	}

	void on_success(const mqtt::token& tok) override {
		action_listener::on_success(tok);
		cout<<"on_success " << tok.get_message_id()<<endl;
		done_ = true;
	}

public:
	delivery_action_listener() : done_(false) {}
	bool is_done() const { return done_; }
};

/////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	string	address  = (argc > 1) ? string(argv[1]) : DFLT_SERVER_ADDRESS,
			clientID = (argc > 2) ? string(argv[2]) : DFLT_CLIENT_ID;

	cout << "Initializing for server '" << address << "'..." << endl;
	mqtt::client client(address, clientID);

	callback cb;
	client.set_callback(cb);

	mqtt::connect_options conopts;
//	mqtt::message willmsg(TOPIC, LWT_PAYLOAD, 1, true);
//	mqtt::will_options will(willmsg);
//	conopts.set_will(will);

    conopts.set_connect_timeout(10);
    conopts.set_keep_alive_interval(3);

	cout << "  ...OK" << endl;

	try {
		cout << "\nConnecting..." << endl;
		client.connect(conopts);
		sleep(10);
		cout << "Sending next message..." << endl;

		for(int i = 0; i< 5;i++){
		    string content("this is ");
		    content += std::to_string(i);

            auto pubmsg = mqtt::make_message(TOPIC, content.c_str());
            cout<<"publish message ["<<content<<"]"<<endl;
            sleep(1);
            client.publish(pubmsg);

		}




		cout << "OK" << endl;

		// Double check that there are no pending tokens



		char a = getchar();
		// Disconnect
		cout << "\nDisconnecting..." << endl;

	}
	catch (const mqtt::exception& exc) {
		cerr << exc.what() << endl;
		return 1;
	}

 	return 0;
}

