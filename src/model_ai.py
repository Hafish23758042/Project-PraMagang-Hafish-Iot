import paho.mqtt.client as mqtt

BROKER = "broker.hivemq.com"
TOPIC = "iot/flood/level"

def classify(level):
    if level < 50:
        return "AMAN"
    elif level < 100:
        return "WASPADA"
    else:
        return "BAHAYA"

def on_message(client, userdata, msg):
    level = float(msg.payload.decode())
    status = classify(level)
    print(f"Water Level: {level:.2f} cm | Status: {status}")

client = mqtt.Client()
client.connect(BROKER, 1883, 60)
client.subscribe(TOPIC)
client.on_message = on_message

print("Monitoring Flood Level...")
client.loop_forever()
