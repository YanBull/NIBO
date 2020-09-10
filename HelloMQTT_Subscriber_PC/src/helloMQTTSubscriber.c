#include <stdio.h>

// In the project settings the symbol 'MQTT_USE_SYNC' is defined
// This makes the compiler use the synchronous client of the MQTT-Library
// If you create a new project make sure to define this symbol under:
// Project Properties > C/C++ General > Paths and Symbols > Symbols > add (under GNU C) > 'MQTT_USE_SYNC'

// To use the MQTT-Library, you need to link the pthread lib.
// For that you need to specify the -pthread argument at the linker options:
// Project Properties > C/C++ Build > Settings > Tool Settings (Tab) > GCC C Linker > Miscellaneous > Linker Flags > enter '-pthread'

#include "MQTTClient.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/time.h>

// URL of the MQTT broker
// broker.hivemq.com is an open to use mqtt broker.
#define ADDRESS       "tcp://broker.hivemq.com"

// MQTT ID definitions
#define CLIENTID_PRE  "THWildau/T18/EmbC/"
#define GROUP_NAME    "1/"                   // enter your groupname here
#define GROUP_MEMBER  "1"                    // enter your identifier here

// MQTT Client ID
// Be sure to have a unique client id!
// Multiple clients with the same client ID cant connect at the same time
// Here the clientID is concatenated by the TH-Wildau-Prefix, your groupname and your personal group member id (e.g. your name)
// If you want to connect multiple clients, you can add a random number or the current time at the end of the ClientID-String.
#define CLIENTID      CLIENTID_PRE GROUP_NAME GROUP_MEMBER


// Quality of service defines, how the messages are transmitted.
// 0 --> At most once
//       The minimal QoS level is zero. This service level guarantees a best-effort delivery.
//       There is no guarantee of delivery. The recipient does not acknowledge receipt of the message
//       and the message is not stored and re-transmitted by the sender.
//       QoS level 0 is often called “fire and forget” and provides the same guarantee as the underlying TCP protocol.
// 1 --> At least once
//       QoS level 1 guarantees that a message is delivered at least one time to the receiver.
//       It is possible for a message to be sent or delivered multiple times.
// 2 --> Exactly once
//       QoS 2 is the highest level of service in MQTT.
//       This level guarantees that each message is received only once by the intended recipients.
//       QoS 2 is the safest and slowest quality of service level.
#define QOS         1

#define TIMEOUT       10000L

// MQTT functions declaration
volatile MQTTClient_deliveryToken deliveredtoken;
void delivered(void *context, MQTTClient_deliveryToken dt);
void connLost(void *context, char *cause);
int mqttMsgCallback(void *context, char *topicName, int topicLen, MQTTClient_message *message);


// Main subsription programm
int main(int argc, char *argv[]) {

    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;

    int rc;
    int ch;

    // Create the mqtt client
    MQTTClient_create(&client, ADDRESS, CLIENTID,
                      MQTTCLIENT_PERSISTENCE_NONE, NULL);

    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    // Declare the callback methods for the mqtt client
    MQTTClient_setCallbacks(client, NULL, connLost, mqttMsgCallback, delivered);

    // Try to connect the client to the mqtt broker
    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS) {
        printf("Failed to connect, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }
    printf("Subscribing to multiple topics \nfor client %s using QoS%d\n\n"
           "Press Q<Enter> to quit\n\n", CLIENTID, QOS);

    // Sbuscribe to one or multiple topics
    // MQTT-topics are build tree-like, seperated with '/'
    // You can use '#' to receive all messages below the specified topic-level
    // You can use '+' as a wildcard for a single level

    // Subscription to exact topic nibo/test/1234
    MQTTClient_subscribe(client, "nibo/test/1234", QOS);

    // Subscription to all topics that begin with nibo/test/,
    // thus e.g. messages under nibo/test/1234 are received as well as under nibo/test/9999
    MQTTClient_subscribe(client, "nibo/test/#", QOS);

    // Subscription to all topics that begin with nibo/test/, have any part after that and end with foo
    // thus e.g. messages under nibo/test/1234/foo are received as well as under nibo/test/9999/foo
    MQTTClient_subscribe(client, "nibo/test/+/foo", QOS);


    // Because you use the same mqtt client for each subscription, each received message
    // is handled by the same callback method.
    // You may have to check the topic in the callback method to trigger the correct action.


    // Block until program is terminated.
    do {
        ch = getchar();
    } while (ch != 'Q' && ch != 'q');

    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);

    printf("Close MQTT Programm");

    return rc;
}

int mqttMsgCallback(void *context, char *topicName, int topicLen, MQTTClient_message *message) {
    char *payloadptr;

    printf("MQTT message arrived\n");
    printf("     topic: %s\n", topicName);
    printf("   message: ");

    // Print the message payload
    payloadptr = message->payload;
    int i;
    for (i = 0; i < message->payloadlen; i++) {
        putchar(*payloadptr++);
    }
    putchar('\n');

    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);

    return 1;
}


void connLost(void *context, char *cause) {
    printf("\nConnection lost\n");
    printf("     cause: %s\n", cause);
}

void delivered(void *context, MQTTClient_deliveryToken dt) {
    printf("Message with token value %d delivery confirmed\n", dt);
    deliveredtoken = dt;
}
