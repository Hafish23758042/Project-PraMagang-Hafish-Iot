import sqlite3, paho.mqtt.client as mqtt
from flask import Flask, jsonify, request
from flask_cors import CORS
import threading, json, datetime

app = Flask(__name__)
CORS(app)

DB_NAME = "database.db"
MQTT_BROKER = "broker.hivemq.com"

def init_db():
    conn = sqlite3.connect(DB_NAME)
    conn.execute('''CREATE TABLE IF NOT EXISTS logs 
                 (id INTEGER PRIMARY KEY AUTOINCREMENT, timestamp TEXT, 
                  water_level REAL, status TEXT, pump_status TEXT)''')
    conn.close()

def on_message(client, userdata, msg):
    try:
        data = json.loads(msg.payload.decode())
        conn = sqlite3.connect(DB_NAME)
        now = datetime.datetime.now().strftime("%H:%M:%S")
        conn.execute("INSERT INTO logs (timestamp, water_level, status, pump_status) VALUES (?, ?, ?, ?)",
                  (now, data['level'], data['status'], data['pump']))
        conn.commit()
        conn.close()
    except: pass

mqtt_c = mqtt.Client()
mqtt_c.on_message = on_message

@app.route('/api/data', methods=['GET'])
def get_data():
    conn = sqlite3.connect(DB_NAME)
    rows = conn.execute("SELECT * FROM logs ORDER BY id DESC LIMIT 10").fetchall()
    conn.close()
    logs = [{"time": r[1], "level": round(r[2], 1), "status": r[3], "pump": r[4]} for r in rows]
    return jsonify({"logs": logs})

@app.route('/api/control', methods=['POST'])
def control():
    cmd = request.json.get('command')
    mqtt_c.publish("sungai/kontrol", cmd)
    return jsonify({"status": "OK"})

if __name__ == '__main__':
    init_db()
    mqtt_c.connect(MQTT_BROKER, 1883)
    mqtt_c.subscribe("sungai/data")
    threading.Thread(target=lambda: mqtt_c.loop_forever(), daemon=True).start()
    app.run(host='0.0.0.0', port=5000)