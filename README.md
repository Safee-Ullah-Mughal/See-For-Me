# SeeForMe

**SeeForMe** is a smart assistive vision system built using an **ESP32-CAM** and a custom mobile application. It performs **object detection** and **distance estimation** using **OpenCV**, then provides **text-to-speech (TTS)** feedback to help visually impaired users perceive their surroundings audibly and in real time.

---

## 📌 Features

* Object detection using OpenCV
* Real-time distance estimation
* Audio feedback via mobile app (TTS)
* Wireless camera feed from ESP32-CAM to smartphone
* Lightweight and affordable solution
* Fully mobile-based processing 

---

## 🔧 Hardware Components

* **ESP32-CAM**
* **Smartphone** (for processing and TTS playback)
* **Power Supply** (Battery for ESP32-CAM)

---

## 🛠️ Software & Tools Used

* **OpenCV** (for object detection and distance estimation)
* **ESP32-CAM** firmware (for video streaming)
* **Custom Android App** (handles video stream, detection, and audio feedback)
* **Arduino IDE** (for ESP32-CAM programming)
* **Android Studio** – Java for app development

---

## 📐 Working Principle

1. ESP32-CAM streams live video to the mobile app over Wi-Fi.
2. The mobile app uses OpenCV to detect objects and estimate distances.
3. The app converts this information into spoken feedback using TTS.
4. The user hears object names and approximate distances in real-time.

---

## 🎓 Project Info

* **University:** National University of Sciences and Technology (NUST)
* **School:** School of Electrical Engineering and Computer Science (SEECS)
* **Degree Program:** MS Information Technology 2k24
* **Team Members:**

  * Safee Ullah Mughal
  * Mohammad Noman
  * Zohaib Shehzad
  * Mahnoor Fiaz
  * Laila Ikram

---


## 🔒 Legal Notice

This project is a proprietary research prototype developed at the National University of Sciences and Technology (NUST), SEECS.  
All rights are reserved by the project authors. No part of this project — including code, designs, or documentation — may be copied, distributed, or reused without explicit written permission.


