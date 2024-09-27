# 🔋 Smart Energy Tracker - ESP32

**Smart Energy Tracker** is a web application that integrates IoT sensors to monitor real-time electricity consumption of household devices, utilizes machine learning to predict next month's electricity bill, and educates users about the environmental impact of their energy usage. This project aims to promote energy efficiency and environmental awareness by enabling users to make informed decisions to reduce costs, conserve energy, and contribute to sustainability.

---

## 🌟 Project Overview

The **Smart Energy Tracker** solves the problem of inefficient electricity usage and high financial costs by:
- Monitoring household device electricity consumption using **IoT sensors** (ACS712 and ZMPT101B).
- Using **machine learning** to predict future electricity bills based on historical data and user behavior.
- Detecting **irregular consumption patterns** to provide alerts about potential hazards such as faulty appliances or unsafe usage.
- Educating users about the **environmental impact** of their energy consumption, thereby promoting energy conservation.

The core system gathers real-time electricity data, processes it, and provides insights into usage patterns, helping users optimize energy consumption and avoid potential risks.

---

## 🔧 Technologies & Components Used

- **ESP32 NodeMCU**: The microcontroller used to receive electricity consumption data and send it to the server.
- **ACS712 (Current Sensor)**: Measures the current consumption of household devices.
- **ZMPT101B (Voltage Sensor)**: Measures the voltage of household devices.
- **Machine Learning**: Predicts next month's electricity bill based on historical consumption patterns.
- **Irregular Pattern Detection**: Monitors device consumption and raises alerts in case of anomalies or potential hazards.
- **React.js**: Frontend framework for building the user interface.
- **MySQL**: Stores the electricity consumption data for real-time monitoring, future predictions, and irregular pattern detection.

---

## 🛠️ Features

- **Real-time Monitoring**: Track live electricity consumption for every connected household device.
- **Bill Prediction**: Uses machine learning models to predict your next month's electricity bill based on past data.
- **Irregular Pattern Detection**: Detects unusual consumption patterns, providing alerts about potential hazards such as faulty devices or unsafe electrical usage.
- **Environmental Insights**: Provides users with valuable information about how their energy consumption impacts the environment.
- **Energy Efficiency Tips**: Offers recommendations to reduce electricity usage and lower costs.

---

## 📡 Data Flow

1. **Electricity Consumption Tracking**:
    - The current and voltage sensors (ACS712 and ZMPT101B) capture the consumption data of household devices.
  
2. **ESP32 NodeMCU**:
    - The ESP32 processes the data using the **C program** and sends it to the web server via **PHP**.

3. **Data Storage**:
    - The consumption data is stored in the database for real-time monitoring, future prediction, and irregular pattern detection.

4. **Machine Learning & Hazard Alerts**:
    - A machine learning algorithm analyzes the data to predict future electricity bills and generates insights on energy usage.
    - Anomaly detection algorithms monitor the data for irregular consumption patterns and trigger alerts for potential hazards.

---

## 🌍 Environmental Impact

This project not only helps reduce electricity costs but also promotes environmental sustainability by educating users about the impact of their electricity consumption on the environment. The insights provided aim to encourage users to adopt energy-efficient habits and make informed decisions to lower their carbon footprint.

---

## 🛠️ Files in the Repository

- **C Program**: This code reads electricity consumption data from the ACS712 and ZMPT101B sensors.
- **PHP Program**: This script handles the data transmission from ESP32 to the server for storage and processing.

---

## 🤝 Contributing

Contributions are welcome! Feel free to fork the repository, create a new branch, and submit a pull request.

---

## 📜 License

This project is licensed under the **MIT License**.

---

👨‍💻 Developed with passion to promote energy efficiency, safety, and sustainability!
