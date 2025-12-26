# 🌊 Smart River Monitoring & Early Warning System (Edge AI Version)
**Repository Project Hafish Arrusal Isfalana - Pra Magang PT. Makerindo 2025**

Sistem pemantauan ketinggian air sungai berbasis IoT yang mengintegrasikan **Edge Intelligence**, **Dashboard Real-time**, dan fitur **Smart Override Control**. Sistem ini dirancang untuk mendeteksi potensi banjir secara presisi dan mengambil tindakan otomatis melalui kontrol aktuator (Relay) secara cerdas.

Proyek ini dikembangkan sebagai bagian dari kegiatan **Pra-Magang tahun 2025**.

---

## 🌟 Fitur Unggulan Terkini
* **Edge AI Processing**: Klasifikasi status air (Aman, Waspada, Bahaya) diproses langsung di ESP32 untuk respon instan.
* **Modern Confirmation Dialog**: Implementasi **SweetAlert2** untuk kendali pompa manual. Pengguna mendapatkan dialog konfirmasi "Iya/Tidak" yang estetik sebelum perintah dieksekusi.
* **Responsive Mobile-First UI**: Dashboard dioptimalkan untuk layar smartphone. Tabel riwayat log memiliki fitur *horizontal scroll* agar data tetap rapi di layar kecil.
* **Enhanced Visual Feedback**: Status pompa pada tabel kini memiliki pembeda warna yang kontras: **Hijau (ON)** dan **Merah (OFF)**.
* **Real-time Charting**: Visualisasi data menggunakan Chart.js dengan skala tetap (0-400 cm) untuk pemantauan tren yang akurat.
* **Database Integration**: Pencatatan log aktivitas menggunakan SQLite & Flask dengan pengurutan data terbaru di posisi teratas.

---

## 🧠 Logika Sistem (AI Threshold)
Sistem secara otomatis mengkategorikan data berdasarkan jarak permukaan air ke sensor:

| Jarak (cm) | Status AI | Indikator Pompa | Warna UI |
| :--- | :--- | :--- | :--- |
| **< 50 cm** | ✅ **AMAN** | ⚪ MATI | Hijau |
| **50 - 99 cm** | ⚠️ **WASPADA** | ⚪ MATI | Kuning |
| **≥ 100 cm** | 🚨 **BAHAYA** | 🔵 NYALA (ON) | Merah |

---

## 🛠️ Stack Teknologi
* **Microcontroller**: ESP32 (DevKit V1).
* **Sensor & Hardware**: Ultrasonic HC-SR04, Relay Module, LED Pompa.
* **Firmware**: C++ (Arduino Framework) via PlatformIO.
* **Frontend**: Vue.js 3, **SweetAlert2** (Notifikasi), Chart.js, CSS3 (Grid & Flexbox).
* **Backend**: Python (Flask), SQLite3, Paho-MQTT.
* **Communication**: MQTT Protocol (Broker: HiveMQ).

---

## 🚀 Panduan Menjalankan Sistem

### 1. Menjalankan Alat (VS Code & Wokwi)
1.  **Buka project** di VS Code.
2.  Pastikan ekstensi **PlatformIO** dan **Wokwi Simulator** sudah terinstal.
3.  Lakukan **Build firmware** (`Ctrl` + `Alt` + `B`).
4.  Jalankan Backend dengan mengeksekusi file `backend/app.py`. Server akan berjalan di `http://127.0.0.1:5000`.
5.  Buka file `diagram.json`, lalu klik **Tombol Hijau (Start Simulation)**.

### 2. Menjalankan Dashboard Monitoring
1.  Buka browser dan akses `http://127.0.0.1:5000`.
2.  Dashboard akan memuat data secara real-time setiap 3 detik.
3.  **Uji Kontrol**: Klik tombol **PAKSA ON/OFF**. Akan muncul dialog konfirmasi modern dari SweetAlert2.
4.  **Uji Mobile**: Gunakan fitur *Inspect Element* (Mode Device) untuk melihat tampilan tabel responsif di HP.

---

## 📂 Struktur Proyek
```text
├── .pio/               # Dependency PlatformIO
├── src/                # Folder Source Code
│   └── main.cpp        # Firmware ESP32 (Logika AI & Manual Override)
├── backend/
<<<<<<< HEAD
│   └── app.py          # Flask API, MQTT Bridge, & Database Handler
├── web/                # Frontend Dashboard
│   ├── index.html      # UI Dashboard (Vue.js & SweetAlert2)
│   ├── style.css       # Mobile Responsive Style
│   └── script.js       # Vue.js Logic & Dialog Handling
=======
│   ├── app.py          # Flask API & MQTT Bridge
├── web/                # Frontend Dashboard
│   ├── index.html      # UI Dashboard
│   ├── style.css       # Style Glassmorphism
│   └── script.js       # Vue.js Logic & MQTT Client
>>>>>>> c42a8df0d90a51fdc919c253e8c005a9e85e5b77
├── database.db         # SQLite Database (Log Histori)
├── diagram.json        # Konfigurasi Sirkuit Virtual Wokwi
└── README.md           # Dokumentasi Proyek
```

## 📸 Dokumentasi Project

<p align="center">
  <img src="assets/DOKUMENTASI DEMO PROJECT 1.png" width="90%" alt="Demo 1">
  <img src="assets/DOKUMENTASI DEMO PROJECT 2.png" width="90%" alt="Demo 2">
  <img src="assets/DOKUMENTASI DEMO PROJECT 3.png" width="90%" alt="Demo 3">
  <img src="assets/DOKUMENTASI DEMO PROJECT 4.png" width="90%" alt="Demo 4">
  <img src="assets/DOKUMENTASI DEMO PROJECT 5.png" width="90%" alt="Demo 5">
</p>
