# Project-PraMagang-Hafish-Iot
Repository Project Pra Magang PT. Makerindo 2026

# 🌊 FloodGuard: Smart River Monitoring & Early Warning System

**FloodGuard** adalah sistem pemantauan ketinggian air sungai berbasis IoT (Internet of Things) yang dirancang untuk mendeteksi potensi banjir secara dini. Sistem ini mengintegrasikan **ESP32** dan sensor **HC-SR04** untuk pengambilan data, yang kemudian ditransmisikan menggunakan protokol **MQTT** untuk dianalisis oleh model **AI (Python)**.

Proyek ini dikembangkan oleh **Hafish Arrusal Isfalana** dari **Politeknik Negeri Lampung** sebagai bagian dari kegiatan **Pra-Magang tahun 2025**.

---

## 🚀 Fitur Utama
* **Real-time Distance Sensing**: Pengukuran jarak permukaan air secara presisi menggunakan sensor ultrasonik.
* **MQTT Protocol Integration**: Pengiriman data nirkabel yang ringan dari ESP32 ke Model AI secara real-time.
* **AI-Powered Classification**: Logika cerdas pada Python untuk menentukan status level air.
* **3-Level Warning System**: 
    * ✅ **Aman**: Kondisi air normal.
    * ⚠️ **Waspada**: Ketinggian air meningkat, perlu pemantauan.
    * 🚨 **Bahaya Banjir**: Ketinggian air kritis, peringatan bahaya segera aktif.
* **Virtual Simulation**: Dapat diuji sepenuhnya melalui simulator Wokwi tanpa perangkat fisik.

## 🛠️ Stack Teknologi
* **Microcontroller**: ESP32
* **Sensor**: Ultrasonik HC-SR04
* **Communication**: MQTT (Message Queuing Telemetry Transport)
* **IDE & Tools**: VS Code, PlatformIO, Wokwi Simulator
* **Languages**: C++ (Embedded) & Python (AI Model & MQTT Subscriber)

---

## 🏗️ Panduan Penggunaan (Cara Menjalankan)

Ikuti langkah-langkah berikut untuk menjalankan simulasi proyek:

1.  **Build Firmware**:
    * Buka proyek di **VS Code** dengan extension **PlatformIO**.
    * Klik ikon centang (**Build**) untuk mengompilasi kode firmware ESP32.

2.  **Persiapan Simulator**:
    * Cari dan buka file `diagram.json` di root folder proyek untuk mengaktifkan integrasi **Wokwi**.

3.  **Mulai Simulasi**:
    * Tekan tombol **Play/Start Simulation** pada panel Wokwi. ESP32 akan mulai mengirimkan data sensor ke broker MQTT.

4.  **Menjalankan Model AI (MQTT Subscriber)**:
    * Buka terminal di VS Code dan jalankan skrip Python untuk menerima data dan memberikan klasifikasi:
        ```bash
        python src/model_ai.py
        ```

5.  **Monitoring Output**:
    * Lihat terminal untuk memantau data ketinggian air secara real-time beserta notifikasi status (**Aman/Waspada/Bahaya**).

---

## 📂 Struktur Proyek
```text
├── .pio/               # Konfigurasi & Dependency PlatformIO
├── src/                # Kode sumber ESP32 (MQTT Publisher), model_ai.py (AI Logic & MQTT Subscriber)
├── diagram.json        # Konfigurasi sirkuit virtual Wokwi
├── platformio.ini      # Library (PubSubClient, etc.)
└── README.md           # Dokumentasi Proyek