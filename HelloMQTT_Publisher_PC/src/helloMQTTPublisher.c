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

#define TIMEOUT     10000L

int main() {
    printf("Start MQTT publisher!\n");

    // Init the mqtt objects
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_deliveryToken token;

    int rc;

    // Create the mqtt client
    MQTTClient_create(&client, ADDRESS, CLIENTID,
                      MQTTCLIENT_PERSISTENCE_NONE, NULL);

    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    // Try to connect the client to the mqtt broker
    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }

    char * topic = "nibo/test/1234";
    char * payload = "Hello MQTT from VM";

    // Create a message object for publishing data over the mqtt broker
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    pubmsg.payload = payload;
    pubmsg.payloadlen = strlen(payload);
    pubmsg.qos = QOS;

    // If retained == 0, subscriber only receive the message if they are already subscribed to the topic
    // If retained == 1, the last published message is stored, thus new subscriber receive the last published message on connection
    pubmsg.retained = 0;


    // Publish the message under the given topic. You can use any string as topic.
    // MQTT Topics are organized hierarchically, seperated with slashes '/'
    MQTTClient_publishMessage(client, topic, &pubmsg, &token);

    printf("Waiting for up to %d seconds for publication of %s\n"
           "on topic %s for client with ClientID: %s\n",
           (int)(TIMEOUT/1000), payload, topic, CLIENTID);

    rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);

    printf("Message with delivery token %d delivered\n", token);

    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);

    return rc;

}
