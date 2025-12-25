# 🌊 Smart River Monitoring & Early Warning System (Edge AI Version)
**Repository Project Hafish Pra Magang PT. Makerindo 2026**

Sistem pemantauan ketinggian air sungai berbasis IoT yang mengintegrasikan **Edge Intelligence**, **Dashboard Real-time**, dan fitur **Smart Override Control**. Sistem ini dirancang untuk mendeteksi potensi banjir secara presisi dan mengambil tindakan otomatis melalui kontrol aktuator (Relay) secara cerdas.

Proyek ini dikembangkan oleh **Hafish Arrusal Isfalana** dari **Politeknik Negeri Lampung** sebagai bagian dari kegiatan **Pra-Magang tahun 2025**.

---

## 🌟 Fitur Unggulan
* **Edge AI Processing**: Klasifikasi status air (Aman, Waspada, Bahaya) diproses langsung di ESP32 untuk respon instan.
* **Smart Manual Override**: Fitur kendali paksa (ON/OFF) via Dashboard yang dilengkapi dengan **Auto-Return Timer** (kembali ke mode otomatis setelah 10 detik).
* **Real-time Dashboard**: Visualisasi data ketinggian air menggunakan Chart.js dan Vue.js dengan UI Glassmorphism yang futuristik.
* **Database Integration**: Pencatatan log aktivitas sensor dan status pompa secara historis menggunakan SQLite & Flask.
* **MQTT Connectivity**: Komunikasi data dua arah yang ringan menggunakan protokol MQTT (Broker HiveMQ).

---

## 🧠 Logika Sistem (AI Threshold)
Sistem secara otomatis mengkategorikan data berdasarkan jarak permukaan air ke sensor yang diproses langsung pada *edge device*:

| Jarak (cm) | Status AI | Indikator Pompa |
| :--- | :--- | :--- |
| **< 50 cm** | ✅ **AMAN** | ⚪ MATI |
| **50 - 99 cm** | ⚠️ **WASPADA** | ⚪ MATI |
| **≥ 100 cm** | 🚨 **BAHAYA** | 🔵 MENYALA (ON) |

---

## 🛠️ Stack Teknologi
* **Microcontroller**: ESP32 (DevKit V1).
* **Sensor & Hardware**: Ultrasonic HC-SR04, Relay Module, LED Pompa.
* **Firmware**: C++ (Arduino Framework) via PlatformIO.
* **Frontend**: Vue.js 3, MQTT.js (WebSockets), CSS3, Vue.js 3, Chart.js, Tailwind CSS/Glassmorphism.
* **Backend**: Python (Flask), SQLite3, Paho-MQTT.
* **Communication**: MQTT Protocol (Broker: HiveMQ).

---

## 🚀 Panduan Menjalankan Sistem

### 1. Menjalankan Alat (VS Code & Wokwi)
1. **Buka project** di VS Code.
2. Pastikan ekstensi **PlatformIO** dan **Wokwi Simulator** sudah terinstal.
3. Lakukan **Build firmware** dengan menekan tombol `Ctrl` + `Alt` + `B`.
4. Jalankan Backend dengan menjalankan file **app.py**, dan otomatis membuat database
4. Klik file `diagram.json` pada sidebar explorer.
5. Klik **Tombol Hijau (Start Simulation)** pada editor untuk menjalankan simulator Wokwi.
6. Pantau **Serial Monitor** untuk memastikan pesan `Connected to Broker` telah muncul.


### 2. Menjalankan Dashboard Monitoring
1. Masuk ke direktori folder `web/`.
2. Buka file `index.html` menggunakan browser (**Chrome** atau **Edge** sangat disarankan).
3. Dashboard akan otomatis terhubung ke broker MQTT dan mendengarkan data dari ESP32 secara real-time.
4. **Ubah nilai jarak** pada sensor ultrasonik di simulator Wokwi, lalu amati perubahan status serta animasi pompa di Dashboard secara instan.

---

## 📂 Struktur Proyek

├── .pio/               # Dependency PlatformIO
├── src/                # Folder Source Code
│   └── main.cpp        # Firmware ESP32 (Logika AI & Manual Override)
├── backend/
│   ├── app.py          # Flask API & MQTT Bridge
│   └── database.db     # SQLite Database (Log Histori)
├── web/                # Frontend Dashboard
│   ├── index.html      # UI Dashboard
│   ├── style.css       # Style Glassmorphism
│   └── script.js       # Vue.js Logic & MQTT Client
├── diagram.json        # Konfigurasi Sirkuit Virtual Wokwi
└── README.md           # Dokumentasi Proyek

## 📸 Dokumentasi Project

<p align="center">
  <img src="assets/DOKUMENTASI DEMO PROJECT 1.png" width="90%" alt="Demo 1">
  <img src="assets/DOKUMENTASI DEMO PROJECT 2.png" width="90%" alt="Demo 2">
  <img src="assets/DOKUMENTASI DEMO PROJECT 3.png" width="90%" alt="Demo 3">
  <img src="assets/DOKUMENTASI DEMO PROJECT 4.png" width="90%" alt="Demo 4">
  <img src="assets/DOKUMENTASI DEMO PROJECT 5.png" width="90%" alt="Demo 5">
</p>
